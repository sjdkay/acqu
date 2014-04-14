// This code gets executed by the online analysis
// every Nth events (see online config Period: statement)

void PeriodMacro() {
  // Dump the current FP scalers to a nfs exported file system
  if(gROOT->FindObject("FPD_ScalerCurr")){
    if((FPD_ScalerCurr->Integral()) > 0){
      FILE  *fp=fopen("scratch/tagscaler.txt","w");
      //FILE  *fp=fopen("/exports/a2raid5/tagscaler.txt","w");
      for(int n=1;n<=352;n++){
	fprintf(fp,"%d\n", FPD_ScalerCurr->GetBinContent(n));
      }
      fclose(fp);
    }
  }

  // calculate the background-subtracted pairspec data
  if(gROOT->FindObject("PairSpec_Open")){
    if((PairSpec_Open->Integral())>0) {
      stringstream cmd;
      cmd << "caput -a BEAM:PAIRSPEC:TaggEff 352";
      for(int n=1; n<=352; n++) {
	Double_t open = PairSpec_Open->GetBinContent(n);
	Double_t gated = PairSpec_Gated->GetBinContent(n);
	Double_t gated_dly = PairSpec_GatedDly->GetBinContent(n);
	Double_t taggeff = (gated-gated_dly)/open;
	if(!TMath::Finite(taggeff))
          taggeff = 0;
	cmd << taggeff << " ";
      }
      cmd << " > /dev/null";
      system(cmd.str().c_str());
    }
  }

  // determine percent of events with a hardware error
  if(gROOT->FindObject("NHardwareError")){
    if((NHardwareError->Integral()) > 0){
      stringstream cmd;
      Double_t per_err = (100*(1.-((NHardwareError->GetBinContent(1))/(NHardwareError->Integral()))));
      cmd << "caput GEN:MON:EventsWithError.A " << per_err << " > /dev/null";
      system(cmd.str().c_str());
      NHardwareError->Reset();
    }
  }
}
