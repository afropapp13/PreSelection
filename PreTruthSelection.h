#ifndef PreTruthSelection_h
#define PreTruthSelection_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include "ubana/MyClasses/Constants.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace Constants;

class PreTruthSelection {

private:
   TString fWhichSample;

public :

   //TTree           *fChain;   //!pointer to the analyzed TTree or TChain
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain

   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   std::vector<double>  *EventWeight;
   Int_t           isData;
   Int_t           RunNumber;
   Int_t           SubRunNumber;
   Int_t           EventNumber;
   Int_t           ientry;
   Int_t           EventPassedSwTrigger;

   std::vector<int>     *MCParticle_Mother;
   std::vector<int>     *MCParticle_StatusCode;
   std::vector<int>     *MCParticle_PdgCode;
   std::vector<int>     *MCParticle_TrackId;
   std::vector<double>  *MCParticle_Vx;
   std::vector<double>  *MCParticle_Vy;
   std::vector<double>  *MCParticle_Vz;
   std::vector<double>  *MCParticle_EndX;
   std::vector<double>  *MCParticle_EndY;
   std::vector<double>  *MCParticle_EndZ;
   std::vector<std::string>  *MCParticle_Process;
   std::vector<double>  *MCParticle_E;
   std::vector<double>  *MCParticle_P;
   std::vector<double>  *MCParticle_Mass;
   std::vector<int>     *MCParticle_AssMCTruth_Origin;
   std::vector<int>     *MCParticle_AssMCTruth_NParticles;
   std::vector<int>     *MCParticle_AssMCTruth_Nu_PdgCode;
   std::vector<int>     *MCParticle_AssMCTruth_Lepton_PdgCode;
   std::vector<int>     *MCParticle_AssMCTruth_CCNC;
   std::vector<int>     *MCParticle_AssMCTruth_Mode;
   std::vector<int>     *MCParticle_AssMCTruth_InteractionType;

   std::vector<int>     *MCTruth_CCNC;
   std::vector<int>     *MCTruth_Mode;
   std::vector<int>     *MCTruth_InteractionType;

   // List of branches

   TBranch        *b_EventWeight;   //!

   TBranch        *b_isData;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_SubRunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_ientry;   //!
   TBranch        *b_EventPassedSwTrigger;   //!
   TBranch        *b_MCParticle_Mother;   //!
   TBranch        *b_MCParticle_StatusCode;   //!
   TBranch        *b_MCParticle_PdgCode;   //!
   TBranch        *b_MCParticle_TrackId;   //!
   TBranch        *b_MCParticle_Vx;   //!
   TBranch        *b_MCParticle_Vy;   //!
   TBranch        *b_MCParticle_Vz;   //!
   TBranch        *b_MCParticle_EndX;   //!
   TBranch        *b_MCParticle_EndY;   //!
   TBranch        *b_MCParticle_EndZ;   //!
   TBranch        *b_MCParticle_Process;   //!
   TBranch        *b_MCParticle_E;   //!
   TBranch        *b_MCParticle_P;   //!
   TBranch        *b_MCParticle_Mass;   //!
   TBranch        *b_MCParticle_AssMCTruth_Origin;   //!
   TBranch        *b_MCParticle_AssMCTruth_NParticles;   //!
   TBranch        *b_MCParticle_AssMCTruth_Nu_PdgCode;   //!
   TBranch        *b_MCParticle_AssMCTruth_Lepton_PdgCode;   //!
   TBranch        *b_MCParticle_AssMCTruth_CCNC;   //!
   TBranch        *b_MCParticle_AssMCTruth_Mode;   //!
   TBranch        *b_MCParticle_AssMCTruth_InteractionType;   //!

   TBranch        *b_MCTruth_CCNC;   //!
   TBranch        *b_MCTruth_Mode;   //!
   TBranch        *b_MCTruth_InteractionType;   //!

   //PreTruthSelection(TTree *tree=0);
   PreTruthSelection(TString WhichSample,TChain *tree=0);

   virtual ~PreTruthSelection();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);

   //virtual void     Init(TTree *tree);
   virtual void     Init(TChain *tree);

   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual string ToString(int num);
};

#endif

#ifdef PreTruthSelection_cxx
PreTruthSelection::PreTruthSelection(TString WhichSample,TChain *tree) : fChain(0) 
//PreTruthSelection::PreTruthSelection(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//   if (tree == 0) {
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(CCQEPath+File+".root");
//      if (!f || !f->IsOpen()) {
//         f = new TFile(CCQEPath+File+".root");
//      }
//      //TDirectory * dir = (TDirectory*)f->Get(CCQEPath+File+".root:/CaliTTCreatorFinder");
//      //dir->GetObject("myTTree",tree);
//      f->GetObject("myTTree",tree);

//   }
//   Init(tree);

	fWhichSample = WhichSample;

	TString CCQEPath = "/pnfs/uboone/persistent/users/apapadop/"+fWhichSample+"/"+UBCodeVersion+"/";

	TString Name = CCQEPath+"my"+fWhichSample+"_"+WhichRun+"_"+UBCodeVersion+"_Part";

	TChain* fmyLocalChain = new TChain("myTTree");

	int NFiles = 15;
	for (int i = 1; i < NFiles+1; i++) {
		fmyLocalChain->Add(Name+ToString(i)+".root");
	}

	tree = fmyLocalChain;
	std::cout << std::endl << std::endl << "Total # " +fWhichSample + " " + WhichRun + " Entries = " << tree->GetEntries() << std::endl << std::endl;
	Init(tree);	

}

PreTruthSelection::~PreTruthSelection()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PreTruthSelection::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PreTruthSelection::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

//void PreTruthSelection::Init(TTree *tree)
void PreTruthSelection::Init(TChain *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   EventWeight = 0;

   MCParticle_Mother = 0;
   MCParticle_StatusCode = 0;
   MCParticle_PdgCode = 0;
   MCParticle_TrackId = 0;
   MCParticle_Vx = 0;
   MCParticle_Vy = 0;
   MCParticle_Vz = 0;
   MCParticle_EndX = 0;
   MCParticle_EndY = 0;
   MCParticle_EndZ = 0;
   MCParticle_Process = 0;
   MCParticle_E = 0;
   MCParticle_P = 0;
   MCParticle_Mass = 0;
   MCParticle_AssMCTruth_Origin = 0;
   MCParticle_AssMCTruth_NParticles = 0;
   MCParticle_AssMCTruth_Nu_PdgCode = 0;
   MCParticle_AssMCTruth_Lepton_PdgCode = 0;
   MCParticle_AssMCTruth_CCNC = 0;
   MCParticle_AssMCTruth_Mode = 0;
   MCParticle_AssMCTruth_InteractionType = 0;

   MCTruth_CCNC = 0;
   MCTruth_Mode = 0;
   MCTruth_InteractionType = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventWeight", &EventWeight, &b_EventWeight);

   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("SubRunNumber", &SubRunNumber, &b_SubRunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("ientry", &ientry, &b_ientry);
   fChain->SetBranchAddress("MCParticle_Mother", &MCParticle_Mother, &b_MCParticle_Mother);
   fChain->SetBranchAddress("MCParticle_StatusCode", &MCParticle_StatusCode, &b_MCParticle_StatusCode);
   fChain->SetBranchAddress("MCParticle_PdgCode", &MCParticle_PdgCode, &b_MCParticle_PdgCode);
   fChain->SetBranchAddress("MCParticle_TrackId", &MCParticle_TrackId, &b_MCParticle_TrackId);
   fChain->SetBranchAddress("MCParticle_Vx", &MCParticle_Vx, &b_MCParticle_Vx);
   fChain->SetBranchAddress("MCParticle_Vy", &MCParticle_Vy, &b_MCParticle_Vy);
   fChain->SetBranchAddress("MCParticle_Vz", &MCParticle_Vz, &b_MCParticle_Vz);
   fChain->SetBranchAddress("MCParticle_EndX", &MCParticle_EndX, &b_MCParticle_EndX);
   fChain->SetBranchAddress("MCParticle_EndY", &MCParticle_EndY, &b_MCParticle_EndY);
   fChain->SetBranchAddress("MCParticle_EndZ", &MCParticle_EndZ, &b_MCParticle_EndZ);
   fChain->SetBranchAddress("MCParticle_Process", &MCParticle_Process, &b_MCParticle_Process);
   fChain->SetBranchAddress("MCParticle_E", &MCParticle_E, &b_MCParticle_E);
   fChain->SetBranchAddress("MCParticle_P", &MCParticle_P, &b_MCParticle_P);
   fChain->SetBranchAddress("MCParticle_Mass", &MCParticle_Mass, &b_MCParticle_Mass);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_Origin", &MCParticle_AssMCTruth_Origin, &b_MCParticle_AssMCTruth_Origin);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_NParticles", &MCParticle_AssMCTruth_NParticles, &b_MCParticle_AssMCTruth_NParticles);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_Nu_PdgCode", &MCParticle_AssMCTruth_Nu_PdgCode, &b_MCParticle_AssMCTruth_Nu_PdgCode);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_Lepton_PdgCode", &MCParticle_AssMCTruth_Lepton_PdgCode, &b_MCParticle_AssMCTruth_Lepton_PdgCode);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_CCNC", &MCParticle_AssMCTruth_CCNC, &b_MCParticle_AssMCTruth_CCNC);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_Mode", &MCParticle_AssMCTruth_Mode, &b_MCParticle_AssMCTruth_Mode);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_InteractionType", &MCParticle_AssMCTruth_InteractionType, &b_MCParticle_AssMCTruth_InteractionType);

   fChain->SetBranchAddress("MCTruth_CCNC", &MCTruth_CCNC, &b_MCTruth_CCNC);
   fChain->SetBranchAddress("MCTruth_Mode", &MCTruth_Mode, &b_MCTruth_Mode);
   fChain->SetBranchAddress("MCTruth_InteractionType", &MCTruth_InteractionType, &b_MCTruth_InteractionType);

   Notify();
}

Bool_t PreTruthSelection::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PreTruthSelection::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PreTruthSelection::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

string PreTruthSelection::ToString(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

#endif // #ifdef PreTruthSelection_cxx
