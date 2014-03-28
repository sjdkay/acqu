// This code gets executed by the online analysis
// every Nth events (see online config Period: statement)

void PeriodMacro(){
  // Dump the current FP scalers to a nfs exported file system
  if((FPD_ScalerCurr->Integral()) > 0){
    FILE  *fp=fopen("/exports/a2raid5/tagscaler.txt","w");
    for(int n=1;n<=352;n++){
      fprintf(fp,"%d\n", FPD_ScalerCurr->GetBinContent(n));
    }
    fclose(fp);
  }
}
