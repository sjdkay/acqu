//--Author	JRM Annand   13th Jan 2007
//--Description
//                *** Acqu++ <-> Root ***
// Online/Offline Analysis of Sub-Atomic Physics Experimental Data
//
// Check plots of TAPS Veto spectra
//

CheckTrigger(){
  Char_t* hname[] = {
    "Trigger",
    "TaggHelicity",
    "Multiplicity",
    "Multiplicity_NHits",
    "ScEsum",
    "ScInt4",
    "ScFC",
    "ScG175",
    "ScFarady",
    "ScP2Faraday",
    "ScP2Tagger",
    "ScCBOR1",
    "ScTAPSA",
    "ScTAPSped",
 };
  Char_t* xname[] = {
    "L1 (0-16) & L2 (16-31) CB Trigger Pattern",
    "L1 Tagger (0-7), Beam Helicity (8-15)",
    "Hits in multiplicity circuit",
    "Number multiplicity hits",
    "CB Energy Sum rate (Hz)",
    "Interrupt rate (Hz)",
    "Fast Clear (Hz)",
    "Tagger G175 Rate (kHz)",
    "Faraday Cup rate (Hz)",
    "P2/Faraday-Cup Ratio",
    "P2/Tagger-G175 Ratio",
    "ScCBOR1",
    "ScTAPSA",
    "ScTAPSped",
};
  Char_t* hname2[] = {
    "TwoD2000v1400",
    "TwoD20401v2005M0",
  };
  Char_t* xname2[] = {
    " CB - Tagger Synchronised = Straight Line",
    " CB - TAPS Synchronised = Small Dot",
  };
  Int_t log[] = { 1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
  Int_t col[] = { 4,4,4,4,2,2,2,2,5,5,5,5,3,3,3,3,2,2,2,2,5,5,5 };
 //
  TH1F* h1;
  TCanvas* canv;
  canv = new TCanvas("Scaler-Spectra","Scaler Spectra & Synchronisation",240,180,1240,890);
  canv->SetFillStyle(4000);
  canv->Divide(4,4,0.01,0.01);
  for( Int_t i=0; i<14; i++ ){
      h1 = (TH1F*)(gROOT->FindObject(hname[i]));
      if( !h1 ){ printf("No root histogram %s\n",hname[i]); continue; }
      h1->SetLineColor( 1 );
      h1->SetFillColor( col[i] );
      canv->cd(i+1);
      if( log[i]==1 ) canv->GetPad(i+1)->SetLogy();
      h1->GetXaxis()->SetTitle(xname[i]);
      h1->Draw();
  }
  TH2F* h2;
  for( Int_t i=0; i<2; i++ ){
    h2 = (TH2F*)(gROOT->FindObject(hname2[i]));
    if( !h2 ){ printf("No root histogram %s\n",hname[i]); continue; }
    canv->cd(i+14);
    if( log[i] ) canv->GetPad(i+1)->SetLogz();
    h2->GetXaxis()->SetTitle(xname2[i]);
    h2->Draw("COLZ");
  }
}


void TriggerClear(){
  printf("Not yet implemented\n");
}

void SaveTrigger(){
  printf("Not yet implemented\n");
}
