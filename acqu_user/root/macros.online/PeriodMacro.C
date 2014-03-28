// This code gets executed by the online analysis
// every Nth events (see online config Period: statement)

void PeriodMacro() {
  // Dump the current FP scalers to a nfs exported file system
  if((FPD_ScalerCurr->Integral()) > 0){
    FILE  *fp=fopen("/exports/a2raid5/tagscaler.txt","w");
    for(int n=1;n<=352;n++){
      fprintf(fp,"%d\n", FPD_ScalerCurr->GetBinContent(n));
    }
    fclose(fp);
  }
  
  // calculate the background-subtracted pairspec data
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
