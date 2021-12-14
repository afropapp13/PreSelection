#ifndef mctruth_tree_h
#define mctruth_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class mctruth_tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          subrun;
   UInt_t          event;
   UInt_t          truth_index;
   Int_t           n_particles;
   Int_t           origin;
   Int_t           mode;
   Int_t           interaction_type;
   Int_t           ccnc;
   Int_t           target;
   Int_t           hit_nucl;
   Int_t           hit_quark;
   Float_t         hadronic_mass;
   Float_t         interaction_x;
   Float_t         interaction_y;
   Float_t         interaction_q2;
   Float_t         interaction_pt;
   Float_t         interaction_theta;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_subrun;   //!
   TBranch        *b_event;   //!
   TBranch        *b_truth_index;   //!
   TBranch        *b_n_particles;   //!
   TBranch        *b_origin;   //!
   TBranch        *b_mode;   //!
   TBranch        *b_interaction_type;   //!
   TBranch        *b_ccnc;   //!
   TBranch        *b_target;   //!
   TBranch        *b_hit_nucl;   //!
   TBranch        *b_hit_quark;   //!
   TBranch        *b_hadronic_mass;   //!
   TBranch        *b_interaction_x;   //!
   TBranch        *b_interaction_y;   //!
   TBranch        *b_interaction_q2;   //!
   TBranch        *b_interaction_pt;   //!
   TBranch        *b_interaction_theta;   //!

   mctruth_tree(TTree *tree=0);
   virtual ~mctruth_tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef mctruth_tree_cxx
mctruth_tree::mctruth_tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root:/mcana");
      dir->GetObject("mctruth_tree",tree);

   }
   Init(tree);
}

mctruth_tree::~mctruth_tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t mctruth_tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t mctruth_tree::LoadTree(Long64_t entry)
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

void mctruth_tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("subrun", &subrun, &b_subrun);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("truth_index", &truth_index, &b_truth_index);
   fChain->SetBranchAddress("n_particles", &n_particles, &b_n_particles);
   fChain->SetBranchAddress("origin", &origin, &b_origin);
   fChain->SetBranchAddress("mode", &mode, &b_mode);
   fChain->SetBranchAddress("interaction_type", &interaction_type, &b_interaction_type);
   fChain->SetBranchAddress("ccnc", &ccnc, &b_ccnc);
   fChain->SetBranchAddress("target", &target, &b_target);
   fChain->SetBranchAddress("hit_nucl", &hit_nucl, &b_hit_nucl);
   fChain->SetBranchAddress("hit_quark", &hit_quark, &b_hit_quark);
   fChain->SetBranchAddress("hadronic_mass", &hadronic_mass, &b_hadronic_mass);
   fChain->SetBranchAddress("interaction_x", &interaction_x, &b_interaction_x);
   fChain->SetBranchAddress("interaction_y", &interaction_y, &b_interaction_y);
   fChain->SetBranchAddress("interaction_q2", &interaction_q2, &b_interaction_q2);
   fChain->SetBranchAddress("interaction_pt", &interaction_pt, &b_interaction_pt);
   fChain->SetBranchAddress("interaction_theta", &interaction_theta, &b_interaction_theta);
   Notify();
}

Bool_t mctruth_tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void mctruth_tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t mctruth_tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef mctruth_tree_cxx
