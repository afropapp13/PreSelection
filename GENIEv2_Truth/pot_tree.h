#ifndef pot_tree_h
#define pot_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

// Header file for the classes stored in the TTree if any.

class pot_tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          subrun;
   Double_t        totpot;
   Double_t        totgoodpot;
   Int_t           totspills;
   Int_t           goodspills;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_subrun;   //!
   TBranch        *b_totpot;   //!
   TBranch        *b_totgoodpot;   //!
   TBranch        *b_totspills;   //!
   TBranch        *b_goodspills;   //!

   pot_tree(TTree *tree=0);
   virtual ~pot_tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef pot_tree_cxx
pot_tree::pot_tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

	TString FileFullPath = "/pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root"; 

   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(FileFullPath);
      if (!f || !f->IsOpen()) {
         f = new TFile(FileFullPath);
      }
      TDirectory * dir = (TDirectory*)f->Get(FileFullPath+":/potana");
      dir->GetObject("pot_tree",tree);

   }
   Init(tree);
}

pot_tree::~pot_tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pot_tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t pot_tree::LoadTree(Long64_t entry)
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

void pot_tree::Init(TTree *tree)
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
   fChain->SetBranchAddress("totpot", &totpot, &b_totpot);
   fChain->SetBranchAddress("totgoodpot", &totgoodpot, &b_totgoodpot);
   fChain->SetBranchAddress("totspills", &totspills, &b_totspills);
   fChain->SetBranchAddress("goodspills", &goodspills, &b_goodspills);
   Notify();
}

Bool_t pot_tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pot_tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pot_tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef pot_tree_cxx
