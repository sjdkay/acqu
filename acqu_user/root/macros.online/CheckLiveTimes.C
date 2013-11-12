//--Author	JRM Annand   13th Jan 2007
//--Description
//                *** Acqu++ <-> Root ***
// Online/Offline Analysis of Sub-Atomic Physics Experimental Data
//
// Check plots of TAPS Veto spectra
//

CheckLiveTimes(){
  Char_t* hname[] = {
    "LiveTotal",
    "LiveTrig",
    "LiveTaggA",
    "LiveTaggB",
    "LiveADC1A",
    "LiveADC1B",
    "LiveADC2A",
    "LiveADC2B",
    "LiveTDCA",
    "LiveTDCB",
    "LiveMWPCA",
    "LiveMWPCB",
    "LiveTAPS",
    "LiveTAPS1",
    "LiveTrigTAPS",
    "LiveBafA",
    "LiveBafB",
    "LiveBafC",
    "LiveBafD",
    "LiveBafE",
    "LiveBafF",
    "LiveVetoAB",
    "LiveVetoCD",
    "LiveVetoEF",
    "LivePbWO4",
 };
  Char_t* xname[] = {
    "Livetme Total",
    "Livetme Trig",
    "Livetme TaggA",
    "Livetme TaggB",
    "Livetme ADC1A",

    "Livetme ADC1B",
    "Livetme ADC2A",
    "Livetme ADC2B",
    "Livetme TDCA",
    "Livetme TDCB",

    "Livetme MWPCA",
    "Livetme MWPCB",
    "Livetme TAPS",
    "Livetme TAPS1",
    "Livetme TrigTAPS",

    "Livetme BafA",
    "Livetme BafB",
    "Livetme BafC",
    "Livetme BafD",
    "Livetme BafE",

    "Livetme BafF",
    "Livetme VetoAB",
    "Livetme VetoCD",
    "Livetme VetoEF",
    "Livetme PbWO4",
};
  Int_t log[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
  Int_t col[] = { 4,4,5,5,2,2,2,2,2,2,5,5,3,3,3,4,4,4,4,4,4,2,2,2,5 };
 //
  TH1F* h1;
  TCanvas* canv;
  canv = new TCanvas("Livetimes-Spectra","LiveTime Spectra",240,180,1240,890);
  canv->SetFillStyle(4000);
  canv->Divide(5,5,0.01,0.01);
  for( Int_t i=0; i<25; i++ ){
      h1 = (TH1F*)(gROOT->FindObject(hname[i]));
      if( !h1 ){ printf("No root histogram %s\n",hname[i]); continue; }
      h1->SetLineColor(1);
      h1->SetFillColor( col[i] );
      canv->cd(i+1);
      if( log[i]==1 ) canv->GetPad(i+1)->SetLogy();
      h1->GetXaxis()->SetTitle(xname[i]);
      h1->Draw();
  }
}


void LiveTimesClear(){
  printf("Not yet implemented\n");
}

void SaveLiveTimes(){
  printf("Not yet implemented\n");
}
