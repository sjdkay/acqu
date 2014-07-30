// D.Watts 24th Jan 2004
// J.R.M. Annand 24th Jan 2004...generalise for single & multi-value

#include <sstream>
#include <fstream>
#include <iostream>


void mplot(int cstart, int nx = 1, int ny = 1, int multi = -1, int log = 0 )
{
// plot multiple spectra (of the same type)
// cstart = start ADC index
// nx = # spectra in X direction, default = 1
// ny = # spectra in Y direction, default = 1
// multi for multi-hit ADC 0=1st hit; 1=2nd hit etc. default -1 = not multi hit
// log for log Y axis, default = linear
//
    char hist_name[16];
    char h[8];
    TH1F* hist;
    TAxis* xaxis;
    int w=1;   
//      
    TCanvas* rawcanv = new TCanvas("PID_QDCs","CB-Test", 20, 20, 1200, 960);
    rawcanv->SetFillStyle(4000);
    rawcanv->Divide(nx, ny, 0.0001, 0.0001);
    //    if( log ){ 
      //    }
    if( multi != -1){
	sprintf(h,"M");
	sprintf(h+1,"%d\0",multi);
    }
    else strcpy(h,"");
//       

    ofstream myfile;
    myfile.open ("qdc-ept-fits.txt");
    for (int t=cstart; t<(cstart+nx*ny); t++)
    {
	sprintf(hist_name,"ADC%d",t);
	strcat(hist_name,h);
	rawcanv->cd(w);
	if( log ) rawcanv->GetPad(w)->SetLogy();
	hist = (TH1F*)gROOT->FindObject(hist_name);
	if( hist ){
	  hist->SetLineColor(1);
	  hist->SetFillColor(2);
          stringstream ss;
	  ss << "fit_" << t;
	  TF1 *myfit = new TF1(ss.str().c_str(),"gaus(0)", 800, 3000);
	  myfit->SetParameter(1, 1500);
	  myfit->SetParameter(2, 100);
	  hist->Fit(myfit, "rq");
	  myfile << hist_name << " " << myfit->GetParameter(1) << endl;
	  cout << hist_name << " " << myfit->GetParameter(1) << endl;
	  hist->Draw();
	  
	}
	else printf("Histogram %s not found\n",hist_name);
	w++;
//              xaxis = (TAxis)adcspect->GetXaxis();
//              xaxis->SetRange(0, 4096);
    }
    rawcanv->Update();
    rawcanv->Draw();
    myfile.close();
    return;
}
//                                           
