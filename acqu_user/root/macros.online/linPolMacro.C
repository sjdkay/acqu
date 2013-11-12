//Dump the current FP scalers to a nfs exported file system

void linPolMacro(){
  FILE  *fp=fopen("/exports/a2raid5/tagscaler.txt","w");
  for(int n=1;n<=352;n++){
    fprintf(fp,"%d\n", FPD_ScalerCurr->GetBinContent(353-n));
    //fprintf(fp,"%d\n", FPD_ScalerAcc->GetBinContent(n));
  }
  fclose(fp);
}
