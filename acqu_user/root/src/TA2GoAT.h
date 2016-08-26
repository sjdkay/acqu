#ifndef __TA2GoAT_h__
#define __TA2GoAT_h__


#include "TFile.h"
#include "TTree.h"
#include "TA2AccessSQL.h"

#define TA2GoAT_MAX_TAGGER	 4096
#define TA2GoAT_MAX_PARTICLE 128
#define TA2GoAT_MAX_HITS	 860
#define TA2GoAT_MAX_ERROR	 256
#define TA2GoAT_NULL         1e6

enum {
    EG_OUTPUT_FOLDER = 30250,
    EG_INPUT_NAME,
    EG_FILE_NAME,
    EG_BEAM_HELICITY,
    EG_TAGGED_ENERGY,
};

static const Map_t RootTreeConfigKeys[] = {
    // General keys
    {"RootTree-Output-Folder:"       	, EG_OUTPUT_FOLDER},
    {"RootTree-Input-Name:"           	, EG_INPUT_NAME},
    {"RootTree-File-Name:"           	, EG_FILE_NAME},
    {"Beam-Helicity:"               	, EG_BEAM_HELICITY},
    {"Save-Tagged-Energy:"          	, EG_TAGGED_ENERGY},
    // Termination
    {NULL       	 		, -1           }
};

class	TA2GoAT	: public TA2AccessSQL
{
private:
		TFile*		file;				// outFile
        TTree*		treeTracks;	        // Raw particle information (filled each event)
		TTree*		treeTagger;			// Tagger information (filled each event)
        TTree*		treeLinPol;         // Tagger information (filled each event)
        TTree* 		treeTrigger;		// Trigger information (filled each event)
        TTree* 		treeDetectorHits;	// Detector system hit patterns (filled each event)
        TTree*      treeVertex;         // Two track vertex information
        TTree*		treeScalers; 		// Scaler read information (filled each scaler read)
        TTree*      treeMoeller;        // Moeller information (filled each moeller read)
        TTree*      treeSetupParameters;// Calibration parameters (filled once)
 	TTree*	    treeMWPCHitsChris;	// Hit positions in the wire chambers

    	char        outputFolder[256];
    	char        inputName[64];
    	char        fileName[64];

    	//Particles    
    	Int_t		nParticles;		
        Double_t*	clusterEnergy;
        Double_t* 	theta;
        Double_t*	phi;
    	Double_t*	time;
        Int_t*      clusterSize;
        Int_t*		centralCrystal;
		Int_t*		centralVeto;

        //Detectors
        Int_t*	    detectors;

    	//Charged detector energies
        Double_t*	vetoEnergy;
        Double_t*	MWPC0Energy;
        Double_t*	MWPC1Energy;

        // TAPS PSA Short-gate Energy
        Double_t*   shortEnergy;

        //Pseudo Vertex Info
        Double_t*   pseudoVertexX;
        Double_t*   pseudoVertexY;
        Double_t*   pseudoVertexZ;

        //Vertex Info
        Int_t       nVertex;
        Double_t*   vertexX;
        Double_t*   vertexY;
        Double_t*   vertexZ;

	//Wire Chamber Hits Info
	Int_t       nChamberHitsin1;
        Double_t*   Chamber1X;
        Double_t*   Chamber1Y;
        Double_t*   Chamber1Z;

	Int_t       nChamberHitsin2; 
        Double_t*   Chamber2X;
        Double_t*   Chamber2Y;
        Double_t*   Chamber2Z;


    	//Tagger
    	Int_t		nTagged;
        Double_t*	taggedEnergy;
        Int_t*		taggedChannel;
        Double_t*	taggedTime;
        Int_t       saveTaggedEnergy;
    	
    	//LinPol
    	Int_t 		plane;
    	Double_t	edge;
    	Double_t	edgeSetting;
             
    	//Hits
        Int_t		nNaIHits;
        Int_t*		NaIHits;
        Int_t*		NaICluster;
        Double_t*   NaIEnergy;
        Double_t*   NaITime;
        Int_t		nPIDHits;
        Int_t*		PIDHits;
        Double_t*   PIDEnergy;
        Double_t*   PIDTime;
        Int_t		nMWPCHits;
        Int_t*		MWPCHits;
        Int_t		nBaF2Hits;
        Int_t*		BaF2Hits;
        Int_t*		BaF2Cluster;
        Double_t*   BaF2Energy;
        Double_t*   BaF2Time;
        Int_t		nVetoHits;
        Int_t*		VetoHits;
        Double_t*   VetoEnergy;
        Double_t*   VetoTime;

    	//Trigger 
        Double_t 	energySum;	// or Detector Energies
        Int_t 		multiplicity;
    	Int_t 		nTriggerPattern;
        Int_t* 		triggerPattern;

        Int_t  	 	nHelicityBits;
        Bool_t  	helicity;
        Bool_t  	helicityInverted;
        Int_t  	 	helicityADC;

        Char_t  	helicityBits[8][8];
        Bool_t  	helicityInhibit[8];
        Bool_t  	helicityBeam[8];

        Int_t 		nErrors;
        Int_t* 		errorModuleID;
        Int_t* 		errorModuleIndex;
        Int_t* 		errorCode;
    
    	//Scalers
    	Int_t		eventNumber;
    	Int_t		eventID;    

        //Moeller
        Bool_t      moellerRead;
        UInt_t**    moellerPairs;
        
        //MC
        Long64_t    MCEventID;
        Long64_t    MCRndID;

		// Display histograms
		TH2*		Check_CBdE_E;
		TH2*		Check_CBPhiCorr;
    
		TH2*		Check_CBdE_E_1PID;
		TH2*		Check_CBPhiCorr_1PID;
		
		TH2*		Check_CBdE_E_pi0;
		TH2*		Check_CBPhiCorr_pi0;

		TH2*		Check_TAPSdE_E;
		TH2*		Check_TAPSPhiCorr;
    
		TH2*		Check_TAPSdE_E_1Veto;
		TH2*		Check_TAPSPhiCorr_1Veto;
		
		TH2*		Check_CBHits;
		TH2*		Check_CBADCHits;
		TH2*		Check_CBTDCHits;
		
		TH2*		Check_PIDHits;
		TH2*		Check_PIDADCHits;
		TH2*		Check_PIDTDCHits;
				
		TH2*		Check_TAPSHits;
		TH2*		Check_TAPSADCHits;
		TH2*		Check_TAPSTDCHits;

		TH2*		Check_VetoHits;
		TH2*		Check_VetoADCHits;
		TH2*		Check_VetoTDCHits;


	protected:    	

		void TriggerReconstruction(); // Trigger reconstruction routine
    	void TriggerMC();    //Generates the trigger for the MC
    	void TriggerHW();    //Generates the trigger from hardware information
    	void DefineHistograms();	// Define histograms
    	void WriteHistograms();
		void DataCheckHistograms(); // Routine to fill data check histograms
    
	public:
	TA2GoAT(const char*, TA2Analysis*);
	~TA2GoAT();
	
	virtual void LoadVariable();            	//Creates histograms
    	virtual void SetConfig(Char_t*, Int_t); //Parses general information from configuration file
    	virtual void ParseMisc(char* line);     //Parses additional information from configuration file
    	virtual void Reconstruct();             //Event reconstruction
    	virtual void PostInit();                //Initialisation etc.
    	virtual void Finish();                	//Initialisation etc.

	ClassDef(TA2GoAT, 1)
};


#endif
