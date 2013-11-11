#include "TA2PairSpec.h"
#include <sstream>
#include <iostream>

// Valid Keywords for command-line setup of CB apparatus
enum { EPairSpecScalerBlock = 2000, EPairSpecVuprom };
static const Map_t kPairSpecKeys[] = {
  {"ScalerBlock:",  EPairSpecScalerBlock},   
  {"Vuprom:",       EPairSpecVuprom},
  {NULL,            -1}
};

ClassImp(TA2PairSpec)

using namespace std;

//-----------------------------------------------------------------------------

TA2PairSpec::TA2PairSpec( const char* name, TA2System* analysis  )
               :TA2Detector( name, analysis)
{
  // TODO: All these numbers should be file configurable...
  fNchannels = 352; // number of channels
  fNHistograms = 3;
  fScalerOffset = 2000; // offset of scaler block
  fScalerBlockSize = 32;
  fVupromSumSize = 0; 
  fScalerIndex = new UInt_t[fNHistograms*fNchannels]; // three different histograms!
  
  // buffers for histogram contents 
  fScalerOpen = new UInt_t[fNchannels+1]; 
  fScalerOpen[fNchannels] = EBufferEnd;
  fScalerGated = new UInt_t[fNchannels+1];
  fScalerGated[fNchannels] = EBufferEnd;  
  fScalerGatedDly = new UInt_t[fNchannels+1];
  fScalerGatedDly[fNchannels] = EBufferEnd;  
  
  AddCmdList( kPairSpecKeys );                  // for SetConfig()
}


//-----------------------------------------------------------------------------

TA2PairSpec::~TA2PairSpec() 
{
    delete[] fScalerOpen;
    delete[] fScalerGated;
    delete[] fScalerGatedDly;
}

//-----------------------------------------------------------------------------

void TA2PairSpec::SetConfig(Char_t* line, Int_t key)
{
  // Any special command-line input for Crystal Ball apparatus
  std::stringstream ss(line);
  switch (key) {
  case EPairSpecScalerBlock: {
    UInt_t start;
    if(!(ss >> start)) {
      PrintError(line, "TA2PairSpec Start of ScalerBlock", EErrFatal);
    }
    
    // you can specify a custom permutation,
    // by default it's the identity permutation
    vector<UInt_t> perm;
    perm.resize(fScalerBlockSize);
    for(UInt_t i=0;i<fScalerBlockSize;i++) {
      if(!(ss >> perm[i])) {
        perm[i] = i;
      }
    }
    
    // generate the map "ordered channel (three histograms)" -> "ScalerIndex"
    for(UInt_t i=0;i<fScalerBlockSize;i++) {
      for(UInt_t j=0;j<fNHistograms;j++) {
        UInt_t ch = j*fNchannels+start+perm[i]; // respect the permutation
        UInt_t vupOffset = fScalerBlockSize*fNHistograms*(fVupromSumSize-fVupromSize);
        UInt_t offset = fScalerBlockSize*(fVupromSize*j+fScalerBlockIdx);        
        UInt_t idx = fScalerOffset+vupOffset+offset+i;
        fScalerIndex[ch] = idx;
        //cout << ch << " -> " << idx << endl;
      }      
    }
    fScalerBlockIdx++;
    break;
  }
  case EPairSpecVuprom: {
    if(!(ss >> fVupromSize)) {
      PrintError(line, "TA2PairSpec Size of Vuprom", EErrFatal);
    }
    fVupromSumSize += fVupromSize;
    fScalerBlockIdx=0;
    break;
  }
  default: {
    // default main apparatus SetConfig()
    TA2Detector::SetConfig( line, key );
    break;
  }
  }
}

//-----------------------------------------------------------------------------

void TA2PairSpec::LoadVariable( )
{
  // Input name - variable pointer associations for any subsequent
  // cut or histogram setup.
  // LoadVariable( "name", pointer-to-variable, type-spec );
  // NB scaler variable pointers need the preceeding &
  //    array variable pointers do not.
  // type-spec ED prefix for a Double_t variable
  //           EI prefix for an Int_t variable
  // type-spec SingleX for a single-valued variable
  //           MultiX  for a multi-valued variable

  //                            name                     pointer          type-spec
  TA2DataManager::LoadVariable("ScalerOpen",     fScalerOpen,     EIScalerX);
  TA2DataManager::LoadVariable("ScalerGated",    fScalerGated,    EIScalerX);
  TA2DataManager::LoadVariable("ScalerGatedDly", fScalerGatedDly, EIScalerX);
  TA2Detector::LoadVariable();
}



//-----------------------------------------------------------------------------

void TA2PairSpec::PostInit( )
{
  TA2DataManager::PostInit();
}

//-----------------------------------------------------------------------------

void TA2PairSpec::Decode()
{
  if(!gAR->IsScalerRead())
    return;
  
  for(UInt_t i=0;i<fNchannels;i++) {
    fScalerOpen[i] = fScaler[fScalerIndex[i+0*fNchannels]];
    //cout << "i="<<i<<" open: "<<fScalerOpen[i] << endl;
  }
  for(UInt_t i=0;i<fNchannels;i++) {
    fScalerGated[i] = fScaler[fScalerIndex[i+1*fNchannels]];
  }
  for(UInt_t i=0;i<fNchannels;i++) {
    fScalerGatedDly[i] = fScaler[fScalerIndex[i+2*fNchannels]];
  }
}

//-----------------------------------------------------------------------------

inline void TA2PairSpec::Cleanup()
{
 // Clear any arrays holding variables
 //TA2DataManager::Cleanup();

}

//-----------------------------------------------------------------------------
