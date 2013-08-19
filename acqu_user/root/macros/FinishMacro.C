void FinishMacro(Char_t* file = NULL)
{
    	TString name;
	printf("\nEnd-of-Run macro executing:\n");

	if( !file) file = "ARHistograms.root";
	TFile f1(file,"RECREATE");
	gROOT->GetList()->Write();
	f1.Close();
  	printf("done.\n",file);
  	printf("All histograms saved to %s\n",file);
}
