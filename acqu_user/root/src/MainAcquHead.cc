
#include <fstream>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <cstdlib>
#include <string>
#include <sstream>

#include <TAcquRoot.h>
#include <TA2DataServer.h>
#include <TA2DataFormat.h>

using namespace std;

// our personal data container of interesting header info
struct header_info_t {
  string Time;
  string Description;
  string RunNote;
  string OutFile;
  Int_t  RunNumber;
  Bool_t IsMaybeMk2; // check for the Mk2 marker
  Bool_t IsSane;     // check if fields have meaningful contents
}; 

Int_t Map2Key(const Char_t* function, const Map_t* map)
{
  // Return integer matched to string from map array
  // -1 return on error
  if( !map ) return -1;
  const Char_t* f;
  for( Int_t i=0; ; i++ ){
    f = map[i].fFnName;
    if( !f ) return -1;
    if( !strcmp(function, f)  ) return map[i].fFnKey;
  }
}

string sanitize(const char* in) {
  string s(in);
  const string whitespace = " \t\f\v\n\r";
  int start = s.find_first_not_of(whitespace);
  int end = s.find_last_not_of(whitespace);
  if(start == -1 && end == -1)
    return string("");
  s.erase(0,start);
  s.erase((end - start) + 1);
  return s;
}

header_info_t GetHeaderInfo(const string& filename, const string& format) {
  // create a fake AcquRoot analysis, provide input file
  // feed in the following DataServer config file:
  // Input-Streams:	1 32768 0
  // Stream-Spec:	File Mk2 0 32768 32 0 400
  // File-Name:	Run_Compton_May13_1620.dat 	0	0
  TAcquRoot* ar = new TAcquRoot("AcquRoot", kTRUE);
  ar->SetLogFile("/dev/null");
  TA2DataServer* ds = new TA2DataServer("DataServer", ar);
  ds->SetLogFile("/dev/null");
  
  char cfgInputStreams[] = "1 32768 0"; // needed to prevent const-correctness warning...
  ds->SetConfig(cfgInputStreams, Map2Key("Input-Streams:", TA2DataServer::kDataSrvKeys));
  
  
  stringstream ss;
  ss << "File " << format << " 0 32768 32 0 400";
  char cfgStreamSpec[ss.str().length()];
  strcpy(cfgStreamSpec, ss.str().c_str());
  ds->SetConfig(cfgStreamSpec, Map2Key("Stream-Spec:", TA2DataServer::kDataSrvKeys));
  
  char cfgFileName[filename.length()+10];  
  strcpy(cfgFileName, filename.c_str());
  strcat(cfgFileName, " 0 1"); // read one record, start=0, stop=1
  ds->SetConfig(cfgFileName, Map2Key("File-Name:", TA2DataServer::kDataSrvKeys));
  ds->StartSources();
  usleep(100000);
  ds->Start();
  
  while(1) {
    const TThread::EState state = ds->GetThreadState(); 
    if(state != TThread::kRunningState) {
      break;
    }
  }
  
  TA2DataFormat* df = ds->GetDataFormat(0);  
  
  // sanitize the strings...due to C struct alignment...
  header_info_t info;
  info.Time = sanitize(df->GetTime());
  info.Description = sanitize(df->GetDescription());
  info.RunNote = sanitize(df->GetRunNote());
  info.OutFile = sanitize(df->GetOutFile());
  info.RunNumber = df->GetRunNumber();
  info.IsMaybeMk2 = df->IsMaybeMk2();
  info.IsSane  = true;
  // check a few conditions for saneness
  info.IsSane &= info.Time.length() == 24;
  info.IsSane &= info.OutFile.length() != 0;
  info.IsSane &= info.RunNumber >= 0; 
  
  return info;
}

void PrintHeaderInfo(const header_info_t& info) {
  cout << "Time: "        << info.Time  << endl;
  cout << "Description: " << info.Description << endl;
  cout << "RunNote: "     << info.RunNote << endl;
  cout << "OutFile: "     << info.OutFile << endl;
  cout << "RunNumber: "   << info.RunNumber  << endl;
  cout << "Mk2?: "         << info.IsMaybeMk2 << endl;
  cout << "Sane?: "        << info.IsSane << endl;
}

int main(int argc, char **argv)
{
  if(argc != 2) {
    cerr << "Please provide input file as argument" << endl;
    exit(EXIT_FAILURE);
  }
  string filename(argv[1]);
  // ensure the file is readable, otherwise the fake 
  // AcquRoot will exit...
  ifstream file(filename.c_str());
  if(!file.is_open()) {
    cerr << "Error: Cannot open file '" << filename << "': " << strerror(errno) << endl; 
    exit(EXIT_FAILURE);
  }
  
  // heurestically guess Mk1 or Mk2
  header_info_t header_mk1 = GetHeaderInfo(filename, "Mk1");
  header_info_t header_mk2 = GetHeaderInfo(filename, "Mk2");
  
  if(header_mk1.IsSane && 
     !header_mk1.IsMaybeMk2 && // header_mk2.IsMaybeMk2 is identical...
     !header_mk2.IsSane) {
    // sane mk1, insane mk2 => clear mk1 signature
    PrintHeaderInfo(header_mk1);
  }
  else if(!header_mk1.IsSane && 
          header_mk1.IsMaybeMk2 && // header_mk2.IsMaybeMk2 is identical...
          header_mk2.IsSane)  {
    // insane mk1, sane mk2 => clear mk2 signature
    PrintHeaderInfo(header_mk2);
  }
  else {
    cerr << "Error: No clear Mk1/Mk2 signature found." << endl;
    cout << "===>> Printing Mk1 header info: " << endl;
    PrintHeaderInfo(header_mk1);
    cout << "===>> Printing Mk2 header info: " << endl;
    PrintHeaderInfo(header_mk2);    
    exit(EXIT_FAILURE);
  }
}
