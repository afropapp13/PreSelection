#ifndef PreSelection_h
#define PreSelection_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

#include "ubana/MyClasses/Constants.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace Constants;

class PreSelection {

private:
	TString fWhichSample;

public :

   //TTree           *fChain;   //!pointer to the analyzed TTree or TChain
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain

   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   std::vector<double>  *EventWeight;
   std::vector<double>  *T2KEventWeight;
   Int_t           isData;
   Int_t           RunNumber;
   Int_t           SubRunNumber;
   Int_t           EventNumber;
   Int_t           ientry;
   Int_t           EventPassedSwTrigger;
   Int_t           NumberTracks;
   std::vector<double>  *Track_Length;
   std::vector<double>  *Track_Phi;
   std::vector<double>  *Track_Theta;
   std::vector<double>  *Track_StartX;
   std::vector<double>  *Track_StartY;
   std::vector<double>  *Track_StartZ;
   std::vector<double>  *Track_EndX;
   std::vector<double>  *Track_EndY;
   std::vector<double>  *Track_EndZ;
   std::vector<double>  *Track_Momentum_MCS;
   std::vector<double>  *Track_Momentum;
   std::vector<int>     *Track_IsBeamEvent;
   std::vector<int>     *Track_MCParticle_Mother;
   std::vector<int>     *Track_MCParticle_PdgCode;
   std::vector<double>  *Track_MCParticle_Vx;
   std::vector<double>  *Track_MCParticle_Vy;
   std::vector<double>  *Track_MCParticle_Vz;
   std::vector<double>  *Track_MCParticle_EndX;
   std::vector<double>  *Track_MCParticle_EndY;
   std::vector<double>  *Track_MCParticle_EndZ;
   std::vector<std::string>  *Track_MCParticle_Process;
   std::vector<double>  *Track_MCParticle_E;
   std::vector<double>  *Track_MCParticle_P;
   std::vector<double>  *Track_MCParticle_Mass;
   std::vector<double>  *Track_MCParticle_Purity;
   std::vector<int>     *Track_MCParticle_Origin;
/*   std::vector<int>     *Track_AssMCTruth_NParticles;
   std::vector<int>     *Track_AssMCTruth_Nu_PdgCode;
   std::vector<int>     *Track_AssMCTruth_Lepton_PdgCode;
   std::vector<int>     *Track_AssMCTruth_CCNC;
   std::vector<int>     *Track_AssMCTruth_Mode;*/
   std::vector<int>     *Track_MCParticle_InteractionType;
   std::vector<int>     *Track_MCParticle_Mode;
/*   std::vector<double>  *Track_AssMCTruth_QSqr;
   std::vector<double>  *Track_AssMCTruth_X;
   std::vector<double>  *Track_AssMCTruth_Y;
   std::vector<double>  *Track_AssMCTruth_W;*/
/*   std::vector<int>     *Track_Calorimetry_Plane2_PlaneID;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_ResidualRange;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_dEdx;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_dQdx;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_TruncdEdx;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_TruncdQdx;
   std::vector<double>  *Track_Calorimetry_Plane2_CaliKineticEnergy;
   Int_t           Track_ParticleId_Pdg;
   std::vector<double>  *Track_ParticleId_MinChi2;
   std::vector<double>  *Track_ParticleId_Chi2Proton;
   std::vector<double>  *Track_ParticleId_Chi2Kaon;
   std::vector<double>  *Track_ParticleId_Chi2Pion;
   std::vector<double>  *Track_ParticleId_Chi2Muon;
   std::vector<double>  *Track_ParticleId_PIDA;
   std::vector<double>  *Track_ParticleId_Ndf;
   std::vector<double>  *Track_ParticleId_DeltaChi2;
   std::vector<double>  *Track_ParticleId_MissingE;
   std::vector<double>  *Track_ParticleId_MissingEavg;
   std::vector<double>  *Track_ParticleId_PlaneID;*/
   Int_t           NumberFlashesBeam;
   std::vector<double>  *FlashesBeam_Time;
   std::vector<double>  *FlashesBeam_Twidth;
/*   std::vector<double>  *FlashesBeam_AbsTime;
   std::vector<int>     *FlashesBeam_Frame;*/
   std::vector<double>  *FlashesBeam_Ycenter;
   std::vector<double>  *FlashesBeam_Ywidth;
   std::vector<double>  *FlashesBeam_Zcenter;
   std::vector<double>  *FlashesBeam_Zwidth;
   std::vector<double>  *FlashesBeam_TotalPE;
/*   std::vector<std::vector<double> > *FlashesBeam_WireCenters;
   std::vector<std::vector<double> > *FlashesBeam_WireWidths;
   std::vector<double>  *FlashesBeam_FastToTotal;*/
/*   std::vector<double>  *MCParticle_AssMCTruth_QSqr;
   std::vector<double>  *MCParticle_AssMCTruth_X;
   std::vector<double>  *MCParticle_AssMCTruth_Y;
   std::vector<double>  *MCParticle_AssMCTruth_W;*/

   std::vector<double> *Track_ParticleId_MIPScore_ThreePlanePID;
   std::vector<double> *Track_ParticleId_MuonScore_ThreePlanePID;
   std::vector<double> *Track_ParticleId_ProtonScore_ThreePlanePID;
   std::vector<double> *Track_ParticleId_PionScore_ThreePlanePID;

   std::vector<double> *Track_ParticleId_MIPScore_Chi2_YPlane;
   std::vector<double> *Track_ParticleId_MuonScore_Chi2_YPlane;
   std::vector<double> *Track_ParticleId_ProtonScore_Chi2_YPlane;
   std::vector<double> *Track_ParticleId_PionScore_Chi2_YPlane;

   std::vector<double> *Track_ParticleId_MIPScore_Chi2_UPlane;
   std::vector<double> *Track_ParticleId_MuonScore_Chi2_UPlane;
   std::vector<double> *Track_ParticleId_ProtonScore_Chi2_UPlane;
   std::vector<double> *Track_ParticleId_PionScore_Chi2_UPlane;

   std::vector<double> *Track_ParticleId_MIPScore_Chi2_VPlane;
   std::vector<double> *Track_ParticleId_MuonScore_Chi2_VPlane;
   std::vector<double> *Track_ParticleId_ProtonScore_Chi2_VPlane;
   std::vector<double> *Track_ParticleId_PionScore_Chi2_VPlane;

   std::vector<int>     *MCTruth_CCNC;
   std::vector<int>     *MCTruth_Mode;
   std::vector<int>     *MCTruth_InteractionType;

   Int_t           NumberNuMuPFParticles;
   vector<int>     *PFParticle_NumberNuMuDaughters;
   vector<vector<int> > *PFParticle_NumberNuMuDaughtersPdgCode;
   vector<vector<double>> *TracksFromCurrentPFParticleStartX;

   std::vector<double>  *MCParticle_Vx;
   std::vector<int>     *MCParticle_StatusCode;
   std::vector<int>     *MCParticle_PdgCode;
   std::vector<double>     *MCParticle_P;

   std::vector<double> *PFParticle_NuScore;
   std::vector<double> *PFParticle_FlashScore;

   // List of branches

   TBranch        *b_EventWeight;   //!
   TBranch        *b_T2KEventWeight;   //!

   TBranch        *b_isData;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_SubRunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_ientry;   //!
   TBranch        *b_EventPassedSwTrigger;   //!
   TBranch        *b_NumberTracks;   //!
   TBranch        *b_Track_Length;   //!
   TBranch        *b_Track_Phi;   //!
   TBranch        *b_Track_Theta;   //!
   TBranch        *b_Track_StartX;   //!
   TBranch        *b_Track_StartY;   //!
   TBranch        *b_Track_StartZ;   //!
   TBranch        *b_Track_EndX;   //!
   TBranch        *b_Track_EndY;   //!
   TBranch        *b_Track_EndZ;   //!
   TBranch        *b_Track_Momentum_MCS;   //!
   TBranch        *b_Track_Momentum;   //!
   TBranch        *b_Track_IsBeamEvent;   //!
   TBranch        *b_Track_MCParticle_StatusCode;   //!
   TBranch        *b_Track_MCParticle_Mother;   //!
   TBranch        *b_Track_MCParticle_PdgCode;   //!
   TBranch        *b_Track_MCParticle_Vx;   //!
   TBranch        *b_Track_MCParticle_Vy;   //!
   TBranch        *b_Track_MCParticle_Vz;   //!
   TBranch        *b_Track_MCParticle_EndX;   //!
   TBranch        *b_Track_MCParticle_EndY;   //!
   TBranch        *b_Track_MCParticle_EndZ;   //!
   TBranch        *b_Track_MCParticle_Process;   //!
   TBranch        *b_Track_MCParticle_E;   //!
   TBranch        *b_Track_MCParticle_P;   //!
   TBranch        *b_Track_MCParticle_Mass;   //!
   TBranch        *b_Track_MCParticle_Purity;   //!
   TBranch        *b_Track_MCParticle_Origin;   //!
/*   TBranch        *b_Track_AssMCTruth_NParticles;   //!
   TBranch        *b_Track_AssMCTruth_Nu_PdgCode;   //!
   TBranch        *b_Track_AssMCTruth_Lepton_PdgCode;   //!
   TBranch        *b_Track_AssMCTruth_CCNC;   //!
   TBranch        *b_Track_AssMCTruth_Mode;*/   //!
   TBranch        *b_Track_MCParticle_InteractionType;   //!
   TBranch        *b_Track_MCParticle_Mode;   //!
/*   TBranch        *b_Track_AssMCTruth_QSqr;   //!
   TBranch        *b_Track_AssMCTruth_X;   //!
   TBranch        *b_Track_AssMCTruth_Y;   //!
   TBranch        *b_Track_AssMCTruth_W;*/   //!
/*   TBranch        *b_Track_Calorimetry_Plane2_PlaneID;   //!
   TBranch        *b_Track_Calorimetry_Plane2_ResidualRange;   //!
   TBranch        *b_Track_Calorimetry_Plane2_dEdx;   //!
   TBranch        *b_Track_Calorimetry_Plane2_dQdx;   //!
   TBranch        *b_Track_Calorimetry_Plane2_TruncdEdx;   //!
   TBranch        *b_Track_Calorimetry_Plane2_TruncdQdx;   //!
   TBranch        *b_Track_Calorimetry_Plane2_CaliKineticEnergy;   //!
   TBranch        *b_Track_ParticleId_Pdg;   //!
   TBranch        *b_Track_ParticleId_MinChi2;   //!
   TBranch        *b_Track_ParticleId_Chi2Proton;   //!
   TBranch        *b_Track_ParticleId_Chi2Kaon;   //!
   TBranch        *b_Track_ParticleId_Chi2Pion;   //!
   TBranch        *b_Track_ParticleId_Chi2Muon;   //!
   TBranch        *b_Track_ParticleId_PIDA;   //!
   TBranch        *b_Track_ParticleId_Ndf;   //!
   TBranch        *b_Track_ParticleId_DeltaChi2;   //!
   TBranch        *b_Track_ParticleId_MissingE;   //!
   TBranch        *b_Track_ParticleId_MissingEavg;   //!
   TBranch        *b_Track_ParticleId_PlaneID;   //!*/
   TBranch        *b_NumberFlashesBeam;   //!
   TBranch        *b_FlashesBeam_Time;   //!
   TBranch        *b_FlashesBeam_Twidth;   //!
/*   TBranch        *b_FlashesBeam_AbsTime;   //!
   TBranch        *b_FlashesBeam_Frame;*/   //!
   TBranch        *b_FlashesBeam_Ycenter;   //!
   TBranch        *b_FlashesBeam_Ywidth;   //!
   TBranch        *b_FlashesBeam_Zcenter;   //!
   TBranch        *b_FlashesBeam_Zwidth;   //!
   TBranch        *b_FlashesBeam_TotalPE;   //!
/*   TBranch        *b_FlashesBeam_WireCenters;   //!
   TBranch        *b_FlashesBeam_WireWidths;   //!
   TBranch        *b_FlashesBeam_FastToTotal;*/   //!
/*   TBranch        *b_MCParticle_AssMCTruth_QSqr;   //!
   TBranch        *b_MCParticle_AssMCTruth_X;   //!
   TBranch        *b_MCParticle_AssMCTruth_Y;   //!
   TBranch        *b_MCParticle_AssMCTruth_W;*/   //!

   TBranch        *b_Track_ParticleId_MIPScore_ThreePlanePID;
   TBranch        *b_Track_ParticleId_MuonScore_ThreePlanePID;
   TBranch        *b_Track_ParticleId_ProtonScore_ThreePlanePID;
   TBranch        *b_Track_ParticleId_PionScore_ThreePlanePID;

   TBranch        *b_Track_ParticleId_MIPScore_Chi2_YPlane;
   TBranch        *b_Track_ParticleId_MuonScore_Chi2_YPlane;
   TBranch        *b_Track_ParticleId_ProtonScore_Chi2_YPlane;
   TBranch        *b_Track_ParticleId_PionScore_Chi2_YPlane;

   TBranch        *b_Track_ParticleId_MIPScore_Chi2_UPlane;
   TBranch        *b_Track_ParticleId_MuonScore_Chi2_UPlane;
   TBranch        *b_Track_ParticleId_ProtonScore_Chi2_UPlane;
   TBranch        *b_Track_ParticleId_PionScore_Chi2_UPlane;

   TBranch        *b_Track_ParticleId_MIPScore_Chi2_VPlane;
   TBranch        *b_Track_ParticleId_MuonScore_Chi2_VPlane;
   TBranch        *b_Track_ParticleId_ProtonScore_Chi2_VPlane;
   TBranch        *b_Track_ParticleId_PionScore_Chi2_VPlane;

   TBranch        *b_MCTruth_CCNC;   //!
   TBranch        *b_MCTruth_Mode;   //!
   TBranch        *b_MCTruth_InteractionType;   //!

   TBranch        *b_NumberNuMuPFParticles;   //!
   TBranch        *b_PFParticle_NumberNuMuDaughters;   //!
   TBranch        *b_PFParticle_NumberNuMuDaughtersPdgCode;   //!
   TBranch        *b_TracksFromCurrentPFParticleStartX;   //!

   TBranch        *b_MCParticle_Vx;   //!
   TBranch        *b_MCParticle_StatusCode;   //!
   TBranch        *b_MCParticle_PdgCode;   //!
   TBranch        *b_MCParticle_P;   //!

   TBranch        *b_PFParticle_NuScore;   //!
   TBranch        *b_PFParticle_FlashScore;   //!

   //PreSelection(TTree *tree=0);
   PreSelection(TString WhichSample="", TChain *tree=0);

   virtual ~PreSelection();
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

#ifdef PreSelection_cxx
PreSelection::PreSelection(TString WhichSample, TChain *tree) : fChain(0) 
//PreSelection::PreSelection(TTree *tree) : fChain(0) 
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
	std::cout << endl << "Total # " + fWhichSample + " " + WhichRun + " Entries = " << tree->GetEntries() << std::endl << std::endl;
	Init(tree);	

}

PreSelection::~PreSelection()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PreSelection::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PreSelection::LoadTree(Long64_t entry)
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

//void PreSelection::Init(TTree *tree)
void PreSelection::Init(TChain *tree)
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
   T2KEventWeight = 0;

   Track_Length = 0;
   Track_Phi = 0;
   Track_Theta = 0;
   Track_StartX = 0;
   Track_StartY = 0;
   Track_StartZ = 0;
   Track_EndX = 0;
   Track_EndY = 0;
   Track_EndZ = 0;
   Track_Momentum_MCS = 0;
   Track_Momentum = 0;
   Track_IsBeamEvent = 0;
   Track_MCParticle_Mother = 0;
   Track_MCParticle_PdgCode = 0;
   Track_MCParticle_Vx = 0;
   Track_MCParticle_Vy = 0;
   Track_MCParticle_Vz = 0;
   Track_MCParticle_EndX = 0;
   Track_MCParticle_EndY = 0;
   Track_MCParticle_EndZ = 0;
   Track_MCParticle_Process = 0;
   Track_MCParticle_E = 0;
   Track_MCParticle_P = 0;
   Track_MCParticle_Mass = 0;
   Track_MCParticle_Purity = 0;
   Track_MCParticle_Origin = 0;
/*   Track_AssMCTruth_NParticles = 0;
   Track_AssMCTruth_Nu_PdgCode = 0;
   Track_AssMCTruth_Lepton_PdgCode = 0;
   Track_AssMCTruth_CCNC = 0;
   Track_AssMCTruth_Mode = 0;*/
   Track_MCParticle_InteractionType = 0;
   Track_MCParticle_Mode = 0;
/*   Track_AssMCTruth_QSqr = 0;
   Track_AssMCTruth_X = 0;
   Track_AssMCTruth_Y = 0;
   Track_AssMCTruth_W = 0;*/
   /*Track_Calorimetry_Plane2_PlaneID = 0;
   Track_Calorimetry_Plane2_ResidualRange = 0;
   Track_Calorimetry_Plane2_dEdx = 0;
   Track_Calorimetry_Plane2_dQdx = 0;
   Track_Calorimetry_Plane2_TruncdEdx = 0;
   Track_Calorimetry_Plane2_TruncdQdx = 0;
   Track_Calorimetry_Plane2_CaliKineticEnergy = 0;
   Track_ParticleId_MinChi2 = 0;
   Track_ParticleId_Chi2Proton = 0;
   Track_ParticleId_Chi2Kaon = 0;
   Track_ParticleId_Chi2Pion = 0;
   Track_ParticleId_Chi2Muon = 0;
   Track_ParticleId_PIDA = 0;
   Track_ParticleId_Ndf = 0;
   Track_ParticleId_DeltaChi2 = 0;
   Track_ParticleId_MissingE = 0;
   Track_ParticleId_MissingEavg = 0;
   Track_ParticleId_PlaneID = 0;*/
   FlashesBeam_Time = 0;
   FlashesBeam_Twidth = 0;
/*   FlashesBeam_AbsTime = 0;
   FlashesBeam_Frame = 0;*/
   FlashesBeam_Ycenter = 0;
   FlashesBeam_Ywidth = 0;
   FlashesBeam_Zcenter = 0;
   FlashesBeam_Zwidth = 0;
   FlashesBeam_TotalPE = 0;
/*   FlashesBeam_WireCenters = 0;
   FlashesBeam_WireWidths = 0;
   FlashesBeam_FastToTotal = 0;*/
/*   MCParticle_AssMCTruth_QSqr = 0;
   MCParticle_AssMCTruth_X = 0;
   MCParticle_AssMCTruth_Y = 0;
   MCParticle_AssMCTruth_W = 0;*/

   Track_ParticleId_MIPScore_ThreePlanePID = 0;
   Track_ParticleId_MuonScore_ThreePlanePID = 0;
   Track_ParticleId_ProtonScore_ThreePlanePID = 0;
   Track_ParticleId_PionScore_ThreePlanePID = 0;

   Track_ParticleId_MIPScore_Chi2_YPlane = 0;
   Track_ParticleId_MuonScore_Chi2_YPlane = 0;
   Track_ParticleId_ProtonScore_Chi2_YPlane = 0;
   Track_ParticleId_PionScore_Chi2_YPlane = 0;

   Track_ParticleId_MIPScore_Chi2_UPlane = 0;
   Track_ParticleId_MuonScore_Chi2_UPlane = 0;
   Track_ParticleId_ProtonScore_Chi2_UPlane = 0;
   Track_ParticleId_PionScore_Chi2_UPlane = 0;

   Track_ParticleId_MIPScore_Chi2_VPlane = 0;
   Track_ParticleId_MuonScore_Chi2_VPlane = 0;
   Track_ParticleId_ProtonScore_Chi2_VPlane = 0;
   Track_ParticleId_PionScore_Chi2_VPlane = 0;

   MCTruth_CCNC = 0;
   MCTruth_Mode = 0;
   MCTruth_InteractionType = 0;

   PFParticle_NumberNuMuDaughters = 0;
   PFParticle_NumberNuMuDaughtersPdgCode = 0;
   TracksFromCurrentPFParticleStartX = 0;

   MCParticle_Vx = 0;
   MCParticle_StatusCode = 0;
   MCParticle_PdgCode = 0;
   MCParticle_P = 0;

   PFParticle_NuScore = 0;
   PFParticle_FlashScore = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventWeight", &EventWeight, &b_EventWeight);
   fChain->SetBranchAddress("T2KEventWeight", &T2KEventWeight, &b_T2KEventWeight);

   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("SubRunNumber", &SubRunNumber, &b_SubRunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("ientry", &ientry, &b_ientry);
   fChain->SetBranchAddress("EventPassedSwTrigger", &EventPassedSwTrigger, &b_EventPassedSwTrigger);
   fChain->SetBranchAddress("NumberTracks", &NumberTracks, &b_NumberTracks);
   fChain->SetBranchAddress("Track_Length", &Track_Length, &b_Track_Length);
   fChain->SetBranchAddress("Track_Phi", &Track_Phi, &b_Track_Phi);
   fChain->SetBranchAddress("Track_Theta", &Track_Theta, &b_Track_Theta);
   fChain->SetBranchAddress("Track_StartX", &Track_StartX, &b_Track_StartX);
   fChain->SetBranchAddress("Track_StartY", &Track_StartY, &b_Track_StartY);
   fChain->SetBranchAddress("Track_StartZ", &Track_StartZ, &b_Track_StartZ);
   fChain->SetBranchAddress("Track_EndX", &Track_EndX, &b_Track_EndX);
   fChain->SetBranchAddress("Track_EndY", &Track_EndY, &b_Track_EndY);
   fChain->SetBranchAddress("Track_EndZ", &Track_EndZ, &b_Track_EndZ);
   fChain->SetBranchAddress("Track_Momentum_MCS", &Track_Momentum_MCS, &b_Track_Momentum_MCS);
   fChain->SetBranchAddress("Track_Momentum", &Track_Momentum, &b_Track_Momentum);
   fChain->SetBranchAddress("Track_IsBeamEvent", &Track_IsBeamEvent, &b_Track_IsBeamEvent);
   fChain->SetBranchAddress("Track_MCParticle_Mother", &Track_MCParticle_Mother, &b_Track_MCParticle_Mother);
   fChain->SetBranchAddress("Track_MCParticle_PdgCode", &Track_MCParticle_PdgCode, &b_Track_MCParticle_PdgCode);
   fChain->SetBranchAddress("Track_MCParticle_Vx", &Track_MCParticle_Vx, &b_Track_MCParticle_Vx);
   fChain->SetBranchAddress("Track_MCParticle_Vy", &Track_MCParticle_Vy, &b_Track_MCParticle_Vy);
   fChain->SetBranchAddress("Track_MCParticle_Vz", &Track_MCParticle_Vz, &b_Track_MCParticle_Vz);
   fChain->SetBranchAddress("Track_MCParticle_EndX", &Track_MCParticle_EndX, &b_Track_MCParticle_EndX);
   fChain->SetBranchAddress("Track_MCParticle_EndY", &Track_MCParticle_EndY, &b_Track_MCParticle_EndY);
   fChain->SetBranchAddress("Track_MCParticle_EndZ", &Track_MCParticle_EndZ, &b_Track_MCParticle_EndZ);
   fChain->SetBranchAddress("Track_MCParticle_Process", &Track_MCParticle_Process, &b_Track_MCParticle_Process);
   fChain->SetBranchAddress("Track_MCParticle_E", &Track_MCParticle_E, &b_Track_MCParticle_E);
   fChain->SetBranchAddress("Track_MCParticle_P", &Track_MCParticle_P, &b_Track_MCParticle_P);
   fChain->SetBranchAddress("Track_MCParticle_Mass", &Track_MCParticle_Mass, &b_Track_MCParticle_Mass);
   fChain->SetBranchAddress("Track_MCParticle_Purity", &Track_MCParticle_Purity, &b_Track_MCParticle_Purity);
   fChain->SetBranchAddress("Track_MCParticle_Origin", &Track_MCParticle_Origin, &b_Track_MCParticle_Origin);
/*   fChain->SetBranchAddress("Track_AssMCTruth_NParticles", &Track_AssMCTruth_NParticles, &b_Track_AssMCTruth_NParticles);
   fChain->SetBranchAddress("Track_AssMCTruth_Nu_PdgCode", &Track_AssMCTruth_Nu_PdgCode, &b_Track_AssMCTruth_Nu_PdgCode);
   fChain->SetBranchAddress("Track_AssMCTruth_Lepton_PdgCode", &Track_AssMCTruth_Lepton_PdgCode, &b_Track_AssMCTruth_Lepton_PdgCode);
   fChain->SetBranchAddress("Track_AssMCTruth_CCNC", &Track_AssMCTruth_CCNC, &b_Track_AssMCTruth_CCNC);
   fChain->SetBranchAddress("Track_AssMCTruth_Mode", &Track_AssMCTruth_Mode, &b_Track_AssMCTruth_Mode);*/
   fChain->SetBranchAddress("Track_MCParticle_InteractionType", &Track_MCParticle_InteractionType, &b_Track_MCParticle_InteractionType);
   fChain->SetBranchAddress("Track_MCParticle_Mode", &Track_MCParticle_Mode, &b_Track_MCParticle_Mode);
/*   fChain->SetBranchAddress("Track_AssMCTruth_QSqr", &Track_AssMCTruth_QSqr, &b_Track_AssMCTruth_QSqr);
   fChain->SetBranchAddress("Track_AssMCTruth_X", &Track_AssMCTruth_X, &b_Track_AssMCTruth_X);
   fChain->SetBranchAddress("Track_AssMCTruth_Y", &Track_AssMCTruth_Y, &b_Track_AssMCTruth_Y);
   fChain->SetBranchAddress("Track_AssMCTruth_W", &Track_AssMCTruth_W, &b_Track_AssMCTruth_W);*/
   /*fChain->SetBranchAddress("Track_Calorimetry_Plane2_PlaneID", &Track_Calorimetry_Plane2_PlaneID, &b_Track_Calorimetry_Plane2_PlaneID);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_ResidualRange", &Track_Calorimetry_Plane2_ResidualRange, &b_Track_Calorimetry_Plane2_ResidualRange);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_dEdx", &Track_Calorimetry_Plane2_dEdx, &b_Track_Calorimetry_Plane2_dEdx);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_dQdx", &Track_Calorimetry_Plane2_dQdx, &b_Track_Calorimetry_Plane2_dQdx);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_TruncdEdx", &Track_Calorimetry_Plane2_TruncdEdx, &b_Track_Calorimetry_Plane2_TruncdEdx);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_TruncdQdx", &Track_Calorimetry_Plane2_TruncdQdx, &b_Track_Calorimetry_Plane2_TruncdQdx);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_CaliKineticEnergy", &Track_Calorimetry_Plane2_CaliKineticEnergy, &b_Track_Calorimetry_Plane2_CaliKineticEnergy);
   fChain->SetBranchAddress("Track_ParticleId_Pdg", &Track_ParticleId_Pdg, &b_Track_ParticleId_Pdg);
   fChain->SetBranchAddress("Track_ParticleId_MinChi2", &Track_ParticleId_MinChi2, &b_Track_ParticleId_MinChi2);
   fChain->SetBranchAddress("Track_ParticleId_Chi2Proton", &Track_ParticleId_Chi2Proton, &b_Track_ParticleId_Chi2Proton);
   fChain->SetBranchAddress("Track_ParticleId_Chi2Kaon", &Track_ParticleId_Chi2Kaon, &b_Track_ParticleId_Chi2Kaon);
   fChain->SetBranchAddress("Track_ParticleId_Chi2Pion", &Track_ParticleId_Chi2Pion, &b_Track_ParticleId_Chi2Pion);
   fChain->SetBranchAddress("Track_ParticleId_Chi2Muon", &Track_ParticleId_Chi2Muon, &b_Track_ParticleId_Chi2Muon);
   fChain->SetBranchAddress("Track_ParticleId_PIDA", &Track_ParticleId_PIDA, &b_Track_ParticleId_PIDA);
   fChain->SetBranchAddress("Track_ParticleId_Ndf", &Track_ParticleId_Ndf, &b_Track_ParticleId_Ndf);
   fChain->SetBranchAddress("Track_ParticleId_DeltaChi2", &Track_ParticleId_DeltaChi2, &b_Track_ParticleId_DeltaChi2);
   fChain->SetBranchAddress("Track_ParticleId_MissingE", &Track_ParticleId_MissingE, &b_Track_ParticleId_MissingE);
   fChain->SetBranchAddress("Track_ParticleId_MissingEavg", &Track_ParticleId_MissingEavg, &b_Track_ParticleId_MissingEavg);
   fChain->SetBranchAddress("Track_ParticleId_PlaneID", &Track_ParticleId_PlaneID, &b_Track_ParticleId_PlaneID);*/
   fChain->SetBranchAddress("NumberFlashesBeam", &NumberFlashesBeam, &b_NumberFlashesBeam);
   fChain->SetBranchAddress("FlashesBeam_Time", &FlashesBeam_Time, &b_FlashesBeam_Time);
   fChain->SetBranchAddress("FlashesBeam_Twidth", &FlashesBeam_Twidth, &b_FlashesBeam_Twidth);
/*   fChain->SetBranchAddress("FlashesBeam_AbsTime", &FlashesBeam_AbsTime, &b_FlashesBeam_AbsTime);
   fChain->SetBranchAddress("FlashesBeam_Frame", &FlashesBeam_Frame, &b_FlashesBeam_Frame);*/
   fChain->SetBranchAddress("FlashesBeam_Ycenter", &FlashesBeam_Ycenter, &b_FlashesBeam_Ycenter);
   fChain->SetBranchAddress("FlashesBeam_Ywidth", &FlashesBeam_Ywidth, &b_FlashesBeam_Ywidth);
   fChain->SetBranchAddress("FlashesBeam_Zcenter", &FlashesBeam_Zcenter, &b_FlashesBeam_Zcenter);
   fChain->SetBranchAddress("FlashesBeam_Zwidth", &FlashesBeam_Zwidth, &b_FlashesBeam_Zwidth);
   fChain->SetBranchAddress("FlashesBeam_TotalPE", &FlashesBeam_TotalPE, &b_FlashesBeam_TotalPE);
/*   fChain->SetBranchAddress("FlashesBeam_WireCenters", &FlashesBeam_WireCenters, &b_FlashesBeam_WireCenters);
   fChain->SetBranchAddress("FlashesBeam_WireWidths", &FlashesBeam_WireWidths, &b_FlashesBeam_WireWidths);
   fChain->SetBranchAddress("FlashesBeam_FastToTotal", &FlashesBeam_FastToTotal, &b_FlashesBeam_FastToTotal);*/
/*   fChain->SetBranchAddress("MCParticle_AssMCTruth_QSqr", &MCParticle_AssMCTruth_QSqr, &b_MCParticle_AssMCTruth_QSqr);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_X", &MCParticle_AssMCTruth_X, &b_MCParticle_AssMCTruth_X);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_Y", &MCParticle_AssMCTruth_Y, &b_MCParticle_AssMCTruth_Y);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_W", &MCParticle_AssMCTruth_W, &b_MCParticle_AssMCTruth_W);*/

   fChain->SetBranchAddress("Track_ParticleId_MIPScore_ThreePlanePID", &Track_ParticleId_MIPScore_ThreePlanePID, &b_Track_ParticleId_MIPScore_ThreePlanePID);
   fChain->SetBranchAddress("Track_ParticleId_MuonScore_ThreePlanePID", &Track_ParticleId_MuonScore_ThreePlanePID, &b_Track_ParticleId_MuonScore_ThreePlanePID);
   fChain->SetBranchAddress("Track_ParticleId_ProtonScore_ThreePlanePID", &Track_ParticleId_ProtonScore_ThreePlanePID, &b_Track_ParticleId_ProtonScore_ThreePlanePID);
   fChain->SetBranchAddress("Track_ParticleId_PionScore_ThreePlanePID", &Track_ParticleId_PionScore_ThreePlanePID, &b_Track_ParticleId_PionScore_ThreePlanePID);

   fChain->SetBranchAddress("Track_ParticleId_MIPScore_Chi2_YPlane", &Track_ParticleId_MIPScore_Chi2_YPlane, &b_Track_ParticleId_MIPScore_Chi2_YPlane);
   fChain->SetBranchAddress("Track_ParticleId_MuonScore_Chi2_YPlane", &Track_ParticleId_MuonScore_Chi2_YPlane, &b_Track_ParticleId_MuonScore_Chi2_YPlane);
   fChain->SetBranchAddress("Track_ParticleId_ProtonScore_Chi2_YPlane", &Track_ParticleId_ProtonScore_Chi2_YPlane, &b_Track_ParticleId_ProtonScore_Chi2_YPlane);
   fChain->SetBranchAddress("Track_ParticleId_PionScore_Chi2_YPlane", &Track_ParticleId_PionScore_Chi2_YPlane, &b_Track_ParticleId_PionScore_Chi2_YPlane);

   fChain->SetBranchAddress("Track_ParticleId_MIPScore_Chi2_UPlane", &Track_ParticleId_MIPScore_Chi2_UPlane, &b_Track_ParticleId_MIPScore_Chi2_UPlane);
   fChain->SetBranchAddress("Track_ParticleId_MuonScore_Chi2_UPlane", &Track_ParticleId_MuonScore_Chi2_UPlane, &b_Track_ParticleId_MuonScore_Chi2_UPlane);
   fChain->SetBranchAddress("Track_ParticleId_ProtonScore_Chi2_UPlane", &Track_ParticleId_ProtonScore_Chi2_UPlane, &b_Track_ParticleId_ProtonScore_Chi2_UPlane);
   fChain->SetBranchAddress("Track_ParticleId_PionScore_Chi2_UPlane", &Track_ParticleId_PionScore_Chi2_UPlane, &b_Track_ParticleId_PionScore_Chi2_UPlane);

   fChain->SetBranchAddress("Track_ParticleId_MIPScore_Chi2_VPlane", &Track_ParticleId_MIPScore_Chi2_VPlane, &b_Track_ParticleId_MIPScore_Chi2_VPlane);
   fChain->SetBranchAddress("Track_ParticleId_MuonScore_Chi2_VPlane", &Track_ParticleId_MuonScore_Chi2_VPlane, &b_Track_ParticleId_MuonScore_Chi2_VPlane);
   fChain->SetBranchAddress("Track_ParticleId_ProtonScore_Chi2_VPlane", &Track_ParticleId_ProtonScore_Chi2_VPlane, &b_Track_ParticleId_ProtonScore_Chi2_VPlane);
   fChain->SetBranchAddress("Track_ParticleId_PionScore_Chi2_VPlane", &Track_ParticleId_PionScore_Chi2_VPlane, &b_Track_ParticleId_PionScore_Chi2_VPlane);

   fChain->SetBranchAddress("MCTruth_CCNC", &MCTruth_CCNC, &b_MCTruth_CCNC);
   fChain->SetBranchAddress("MCTruth_Mode", &MCTruth_Mode, &b_MCTruth_Mode);
   fChain->SetBranchAddress("MCTruth_InteractionType", &MCTruth_InteractionType, &b_MCTruth_InteractionType);

   fChain->SetBranchAddress("NumberNuMuPFParticles", &NumberNuMuPFParticles, &b_NumberNuMuPFParticles);

   fChain->SetBranchAddress("PFParticle_NumberNuMuDaughters", &PFParticle_NumberNuMuDaughters, &b_PFParticle_NumberNuMuDaughters);
   fChain->SetBranchAddress("PFParticle_NumberNuMuDaughtersPdgCode", &PFParticle_NumberNuMuDaughtersPdgCode, &b_PFParticle_NumberNuMuDaughtersPdgCode);
   fChain->SetBranchAddress("TracksFromCurrentPFParticleStartX", &TracksFromCurrentPFParticleStartX, &b_TracksFromCurrentPFParticleStartX);

   fChain->SetBranchAddress("MCParticle_Vx", &MCParticle_Vx, &b_MCParticle_Vx);
   fChain->SetBranchAddress("MCParticle_StatusCode", &MCParticle_StatusCode, &b_MCParticle_StatusCode);
   fChain->SetBranchAddress("MCParticle_PdgCode", &MCParticle_PdgCode, &b_MCParticle_PdgCode);
   fChain->SetBranchAddress("MCParticle_P", &MCParticle_P, &b_MCParticle_P);

   fChain->SetBranchAddress("PFParticle_NuScore", &PFParticle_NuScore, &b_PFParticle_NuScore);
   fChain->SetBranchAddress("PFParticle_FlashScore", &PFParticle_FlashScore, &b_PFParticle_FlashScore);

   Notify();
}

Bool_t PreSelection::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PreSelection::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PreSelection::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

string PreSelection::ToString(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

#endif // #ifdef PreSelection_cxx
