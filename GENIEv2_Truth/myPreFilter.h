#ifndef myPreFilter_h
#define myPreFilter_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "string"
#include "vector"
#include "vector"
#include "vector"

class myPreFilter {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          Run;
   UInt_t          SubRun;
   UInt_t          Event;
   string          *Process;
   string          *Endprocess;
   Int_t           N_particles;
   Int_t           Origin;
   Int_t           Mode;
   Int_t           Interaction_type;
   Int_t           Ccnc;
   Int_t           Target;
   Int_t           Hit_nucl;
   Int_t           Hit_quark;
   Float_t         Hadronic_mass;
   Float_t         Interaction_x;
   Float_t         Interaction_y;
   Float_t         Interaction_q2;
   Float_t         Interaction_pt;
   Float_t         Interaction_theta;
   vector<unsigned int> *Truth_index;
   vector<unsigned int> *P_index;
   vector<unsigned int> *Status;
   vector<unsigned int> *Trackid;
   vector<unsigned int> *Pdgcode;
   vector<unsigned int> *Mother;
   vector<int>     *Rescatter;
   vector<float>   *Start_X;
   vector<float>   *Start_Y;
   vector<float>   *Start_Z;
   vector<float>   *Start_T;
   vector<float>   *End_X;
   vector<float>   *End_Y;
   vector<float>   *End_Z;
   vector<float>   *End_T;
   vector<float>   *Px;
   vector<float>   *Py;
   vector<float>   *Pz;
   vector<float>   *P;
   vector<float>   *Pt;
   vector<float>   *E;
   vector<float>   *Mass;
   vector<float>   *End_px;
   vector<float>   *End_py;
   vector<float>   *End_pz;
   vector<float>   *End_e;

   // List of branches
   TBranch        *b_Run;   //!
   TBranch        *b_SubRun;   //!
   TBranch        *b_Event;   //!
   TBranch        *b_Process;   //!
   TBranch        *b_Endprocess;   //!
   TBranch        *b_N_particles;   //!
   TBranch        *b_Origin;   //!
   TBranch        *b_Mode;   //!
   TBranch        *b_Interaction_type;   //!
   TBranch        *b_Ccnc;   //!
   TBranch        *b_Target;   //!
   TBranch        *b_Hit_nucl;   //!
   TBranch        *b_Hit_quark;   //!
   TBranch        *b_Hadronic_mass;   //!
   TBranch        *b_Interaction_x;   //!
   TBranch        *b_Interaction_y;   //!
   TBranch        *b_Interaction_q2;   //!
   TBranch        *b_Interaction_pt;   //!
   TBranch        *b_Interaction_theta;   //!
   TBranch        *b_Truth_index;   //!
   TBranch        *b_P_index;   //!
   TBranch        *b_Status;   //!
   TBranch        *b_Trackid;   //!
   TBranch        *b_Pdgcode;   //!
   TBranch        *b_Mother;   //!
   TBranch        *b_Rescatter;   //!
   TBranch        *b_Start_X;   //!
   TBranch        *b_Start_Y;   //!
   TBranch        *b_Start_Z;   //!
   TBranch        *b_Start_T;   //!
   TBranch        *b_End_X;   //!
   TBranch        *b_End_Y;   //!
   TBranch        *b_End_Z;   //!
   TBranch        *b_End_T;   //!
   TBranch        *b_Px;   //!
   TBranch        *b_Py;   //!
   TBranch        *b_Pz;   //!
   TBranch        *b_P;   //!
   TBranch        *b_Pt;   //!
   TBranch        *b_E;   //!
   TBranch        *b_Mass;   //!
   TBranch        *b_End_px;   //!
   TBranch        *b_End_py;   //!
   TBranch        *b_End_pz;   //!
   TBranch        *b_End_e;   //!

   myPreFilter(TTree *tree=0);
   virtual ~myPreFilter();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef myPreFilter_cxx
myPreFilter::myPreFilter(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreFilter_GENIEv2Overlay9_Combined_v08_00_00_52.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreFilter_GENIEv2Overlay9_Combined_v08_00_00_52.root");
      }
      f->GetObject("myPreFilter",tree);

   }
   Init(tree);
}

myPreFilter::~myPreFilter()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t myPreFilter::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t myPreFilter::LoadTree(Long64_t entry)
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

void myPreFilter::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   Process = 0;
   Endprocess = 0;
   Truth_index = 0;
   P_index = 0;
   Status = 0;
   Trackid = 0;
   Pdgcode = 0;
   Mother = 0;
   Rescatter = 0;
   Start_X = 0;
   Start_Y = 0;
   Start_Z = 0;
   Start_T = 0;
   End_X = 0;
   End_Y = 0;
   End_Z = 0;
   End_T = 0;
   Px = 0;
   Py = 0;
   Pz = 0;
   P = 0;
   Pt = 0;
   E = 0;
   Mass = 0;
   End_px = 0;
   End_py = 0;
   End_pz = 0;
   End_e = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Run", &Run, &b_Run);
   fChain->SetBranchAddress("SubRun", &SubRun, &b_SubRun);
   fChain->SetBranchAddress("Event", &Event, &b_Event);
   fChain->SetBranchAddress("Process", &Process, &b_Process);
   fChain->SetBranchAddress("Endprocess", &Endprocess, &b_Endprocess);
   fChain->SetBranchAddress("N_particles", &N_particles, &b_N_particles);
   fChain->SetBranchAddress("Origin", &Origin, &b_Origin);
   fChain->SetBranchAddress("Mode", &Mode, &b_Mode);
   fChain->SetBranchAddress("Interaction_type", &Interaction_type, &b_Interaction_type);
   fChain->SetBranchAddress("Ccnc", &Ccnc, &b_Ccnc);
   fChain->SetBranchAddress("Target", &Target, &b_Target);
   fChain->SetBranchAddress("Hit_nucl", &Hit_nucl, &b_Hit_nucl);
   fChain->SetBranchAddress("Hit_quark", &Hit_quark, &b_Hit_quark);
   fChain->SetBranchAddress("Hadronic_mass", &Hadronic_mass, &b_Hadronic_mass);
   fChain->SetBranchAddress("Interaction_x", &Interaction_x, &b_Interaction_x);
   fChain->SetBranchAddress("Interaction_y", &Interaction_y, &b_Interaction_y);
   fChain->SetBranchAddress("Interaction_q2", &Interaction_q2, &b_Interaction_q2);
   fChain->SetBranchAddress("Interaction_pt", &Interaction_pt, &b_Interaction_pt);
   fChain->SetBranchAddress("Interaction_theta", &Interaction_theta, &b_Interaction_theta);
   fChain->SetBranchAddress("Truth_index", &Truth_index, &b_Truth_index);
   fChain->SetBranchAddress("P_index", &P_index, &b_P_index);
   fChain->SetBranchAddress("Status", &Status, &b_Status);
   fChain->SetBranchAddress("Trackid", &Trackid, &b_Trackid);
   fChain->SetBranchAddress("Pdgcode", &Pdgcode, &b_Pdgcode);
   fChain->SetBranchAddress("Mother", &Mother, &b_Mother);
   fChain->SetBranchAddress("Rescatter", &Rescatter, &b_Rescatter);
   fChain->SetBranchAddress("Start_X", &Start_X, &b_Start_X);
   fChain->SetBranchAddress("Start_Y", &Start_Y, &b_Start_Y);
   fChain->SetBranchAddress("Start_Z", &Start_Z, &b_Start_Z);
   fChain->SetBranchAddress("Start_T", &Start_T, &b_Start_T);
   fChain->SetBranchAddress("End_X", &End_X, &b_End_X);
   fChain->SetBranchAddress("End_Y", &End_Y, &b_End_Y);
   fChain->SetBranchAddress("End_Z", &End_Z, &b_End_Z);
   fChain->SetBranchAddress("End_T", &End_T, &b_End_T);
   fChain->SetBranchAddress("Px", &Px, &b_Px);
   fChain->SetBranchAddress("Py", &Py, &b_Py);
   fChain->SetBranchAddress("Pz", &Pz, &b_Pz);
   fChain->SetBranchAddress("P", &P, &b_P);
   fChain->SetBranchAddress("Pt", &Pt, &b_Pt);
   fChain->SetBranchAddress("E", &E, &b_E);
   fChain->SetBranchAddress("Mass", &Mass, &b_Mass);
   fChain->SetBranchAddress("End_px", &End_px, &b_End_px);
   fChain->SetBranchAddress("End_py", &End_py, &b_End_py);
   fChain->SetBranchAddress("End_pz", &End_pz, &b_End_pz);
   fChain->SetBranchAddress("End_e", &End_e, &b_End_e);
   Notify();
}

Bool_t myPreFilter::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void myPreFilter::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t myPreFilter::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef myPreFilter_cxx
