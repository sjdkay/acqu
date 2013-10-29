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
    "ScLiveTime",
    "ScLiveTDC1",
    "ScLiveWC",
    "ScLiveADC1",
    "ScLiveADC2",
    "ScLiveTAPS",
    "ScLiveTagg",
    "ScLiveTrigger",
 };
  Char_t* hname2[] = {
    "TwoD2000v1400",
    "TwoD20401v2005M0",
  }
  Int_t log[] = { 1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
  Int_t col[] = { 4,4,4,4,2,2,2,2,2,2,2,5,5,5,5,5,5,5,5,4,4,4,3,3,3,3,3,3,3 };
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
    "Total LiveTime (%)",
    "LiveTime a2TDCdaq1(%)",
    "Livetime a2WCdaq1 (%)",
    "Livetime a2SADCdaq1 (%)",
    "Livetime a2SADCdaq2 (%)",
    "LiveTime TAPS (%)",
    "LiveTime taggerdaq1(%)",
    "LiveTime a2CBtrigger (%)",
  };
  Char_t* xname2[] = {
    " CB - Tagger Synchronised = Straight Line",
    " CB - TAPS Synchronised = Small Dot",
  }
  TH1F* h1;
  TCanvas* canv;
  //
  canv = new TCanvas("Trigger-Spectra",
		     "Trigger Conditions & Synchronisation (1 bin ~ 20s)",
		     240,180,1240,890);
  canv->SetFillStyle(4000);
  canv->Divide(7,3,0.01,0.01);
  for( Int_t i=0; i<19; i++ ){
      h1 = (TH1F*)(gROOT->FindObject(hname[i]));
      if( !h1 ){
	printf("No root histogram %s\n",hname[i]);
	continue;
      }
      h1->SetLineColor( 1 );
      h1->SetFillColor( col[i] );
      canv->cd(i+1);
      if( log[i]==1 ) canv->GetPad(i+1)->SetLogy();
      h1->GetXaxis()->SetTitle(xname[i]);
      h1->Draw();
  }
  //  return;
  TH2F* h2;
  for( Int_t i=0; i<2; i++ ){
    h2 = (TH2F*)(gROOT->FindObject(hname2[i]));
    if( !h2 ){
      printf("No root histogram %s\n",hname[i]);
      continue;
    }
    canv->cd(i+20);
    if( log[i] ) canv->GetPad(i+1)->SetLogz();
    h2->GetXaxis()->SetTitle(xname2[i]);
    h2->Draw("COLZ");
  }
  return;
  canv1 = new TCanvas("Live-Times","Live Time & Beam Evolution (1 bin ~ 20s)",
		      240,180,1240,890);
  canv1->SetFillStyle(4000);
  canv1->Divide(5,2,0.01,0.01);
  for( Int_t i=11; i<21; i++ ){
    Int_t j = i - 10;
      h1 = (TH1F*)(gROOT->FindObject(hname[i]));
      if( !h1 ){
	printf("No root histogram %s\n",hname[i]);
	continue;
      }
      if((h1)&&(i==0)){
	for (Int_t j=0;j<16;j++){
	  (TAxis*)(h1->GetXaxis())->SetBinLabel((j+1),TriggerChannels[j]);
	}
	(TAxis*)(h1->GetXaxis())->LabelsOption("v");
	(TAxis*)(h1->GetXaxis())->SetLabelOffset(-0.22);
	(TAxis*)(h1->GetXaxis())->SetLabelSize(0.08);
      }
      h1->SetLineColor( 1 );
      h1->SetFillColor( col[i] );
      canv1->cd(j);
      if( log[i] ) canv1->GetPad(j)->SetLogy();
      h1->GetXaxis()->SetTitle(xname[i]);
      h1->Draw();
  }
}


void TriggerClear(){
  /*  TA2Detector* t = (TA2Detector*)(gAN->GetGrandChild("TrigSynch"));
  if(t) t->ZeroAll();
  else printf("TrigSynch detector not found\n");
  */
  printf("Not yet implemented\n");
}

void SaveTrigger(){
  //  TA2Detector* t = (TA2Detector*)(gAN->GetGrandChild("VetoBaF2"));
  //  t->SaveHist();
  printf("Not yet implemented\n");
}
