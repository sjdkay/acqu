{
    TCanvas* watcher = new TCanvas("watcher","Watch Me");

    watcher->Divide(2,1);

    watcher->cd(1);
    FPD_TimeOR->Draw();

    watcher->cd(2);
    gPad->SetLogz();
    NaI_Hits_v_TimeOR->Draw("colz");

    TTimer* update_timer = new TTimer("watcher->Update();watcher->Draw();",2000);

    update_timer->Start();
}
