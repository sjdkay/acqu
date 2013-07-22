#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TH2.h"

void PhotonDistributions(Char_t* name = "TA2Pi0Compton2012.root") {

	Char_t* filename = Form("/work0/cristina/%s",name);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("Pi0ComptonTree");

	gStyle->SetOptStat(1111);

	Int_t NPhoton;
	Double_t PhotonTheta[100], PhotonPhi[100], PhotonEnergy[100], PhotonTime[100];

	tree1->SetBranchAddress("NPhoton",		&NPhoton);

	tree1->SetBranchAddress("PhotonPhi",		&PhotonPhi);
	tree1->SetBranchAddress("PhotonTheta",		&PhotonTheta);
	tree1->SetBranchAddress("PhotonEnergy",		&PhotonEnergy);
	tree1->SetBranchAddress("PhotonTime",		&PhotonTime);

	TH1D *a0 = new TH1D("PhotonPhi",	"PhotonPhi",	360,	-180,	180);
	TH1D *a1 = new TH1D("PhotonTheta",	"PhotonTheta",	180,	   0,	180);
	TH1D *a2 = new TH1D("PhotonEnergy",	"PhotonEnergy",	400,	   0,	400);
	TH1D *a3 = new TH1D("PhotonTime",	"PhotonTime",	200,	-100,	100);


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);
		
		for (Int_t a = 0; a < NPhoton; a++){

			a0->Fill(PhotonPhi[a]);
			a1->Fill(PhotonTheta[a]);
			a2->Fill(PhotonEnergy[a]);
			a3->Fill(PhotonTime[a]);

		}	
	}
	
	canvas1 = new TCanvas("canvas1","PhotonDistributions");
	canvas1->Divide(2,2);

	canvas1->cd(1);
	a0->Draw();

	canvas1->cd(2);
	a1->Draw();

	canvas1->cd(3);
	a2->Draw();

	canvas1->cd(4);
	a3->Draw();

}

void Pi0Distributions(Char_t* name = "TA2Pi0Compton2012.root") {

	Char_t* filename = Form("/work0/cristina/%s",name);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("Pi0ComptonTree");

	gStyle->SetOptStat(1111);

	Int_t NPi0;
	Double_t Pi0Theta[100], Pi0Phi[100], Pi0Energy[100], Pi0Time[100];

	tree1->SetBranchAddress("NPi0",		&NPi0);

	tree1->SetBranchAddress("Pi0Phi",	&Pi0Phi);
	tree1->SetBranchAddress("Pi0Theta",	&Pi0Theta);
	tree1->SetBranchAddress("Pi0Energy",	&Pi0Energy);
	tree1->SetBranchAddress("Pi0Time",	&Pi0Time);

	TH1D *a0 = new TH1D("Pi0Phi",		"Pi0Phi",	360,	-180,	180);
	TH1D *a1 = new TH1D("Pi0Theta",		"Pi0Theta",	180,	   0,	180);
	TH1D *a2 = new TH1D("Pi0Energy",	"Pi0Energy",	400,	   0,	400);
	TH1D *a3 = new TH1D("Pi0Time",		"Pi0Time",	200,	-100,	100);


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);
		
		for (Int_t a = 0; a < NPi0; a++){

			a0->Fill(Pi0Phi[a]);
			a1->Fill(Pi0Theta[a]);
			a2->Fill(Pi0Energy[a]);
			a3->Fill(Pi0Time[a]);

		}	
	}
	
	canvas1 = new TCanvas("canvas1","Pi0Distributions");
	canvas1->Divide(2,2);

	canvas1->cd(1);
	a0->Draw();

	canvas1->cd(2);
	a1->Draw();

	canvas1->cd(3);
	a2->Draw();

	canvas1->cd(4);
	a3->Draw();

}

void ProtonDistributions(Char_t* name = "TA2Pi0Compton2012.root") {

	Char_t* filename = Form("/work0/cristina/%s",name);
	TFile *file1 = new TFile(filename);
	TTree *tree1 = (TTree*)file1->Get("Pi0ComptonTree");

	gStyle->SetOptStat(1111);

	Int_t NProton;
	Double_t ProtonTheta[100], ProtonPhi[100], ProtonEnergy[100], ProtonTime[100];

	tree1->SetBranchAddress("NProton",		&NProton);

	tree1->SetBranchAddress("ProtonPhi",		&ProtonPhi);
	tree1->SetBranchAddress("ProtonTheta",		&ProtonTheta);
	tree1->SetBranchAddress("ProtonEnergy",		&ProtonEnergy);
	tree1->SetBranchAddress("ProtonTime",		&ProtonTime);

	TH1D *a0 = new TH1D("ProtonPhi",	"ProtonPhi",	360,	-180,	180);
	TH1D *a1 = new TH1D("ProtonTheta",	"ProtonTheta",	180,	   0,	180);
	TH1D *a2 = new TH1D("ProtonEnergy",	"ProtonEnergy",	400,	   0,	400);
	TH1D *a3 = new TH1D("ProtonTime",	"ProtonTime",	200,	-100,	100);


	Int_t nentries = (Int_t)tree1->GetEntries();
	for (Int_t i=0;i<nentries;i++) {

		tree1->GetEntry(i);
		
		for (Int_t a = 0; a < NProton; a++){

			a0->Fill(ProtonPhi[a]);
			a1->Fill(ProtonTheta[a]);
			a2->Fill(ProtonEnergy[a]);
			a3->Fill(ProtonTime[a]);

		}	
	}
	
	canvas1 = new TCanvas("canvas1","ProtonDistributions");
	canvas1->Divide(2,2);

	canvas1->cd(1);
	a0->Draw();

	canvas1->cd(2);
	a1->Draw();

	canvas1->cd(3);
	a2->Draw();

	canvas1->cd(4);
	a3->Draw();

}

