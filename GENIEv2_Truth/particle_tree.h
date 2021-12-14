//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov  4 13:53:27 2021 by ROOT version 6.12/06
// from TTree particle_tree/MCParticle Tree
// found on file: /pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root
//////////////////////////////////////////////////////////

#ifndef particle_tree_h
#define particle_tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "string"

class particle_tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   UInt_t          run;
   UInt_t          subrun;
   UInt_t          event;
   UInt_t          truth_index;
   UInt_t          p_index;
   Int_t           status;
   Int_t           trackid;
   Int_t           pdgcode;
   Int_t           mother;
   string          *process;
   string          *endprocess;
   Float_t         weight;
   Int_t           rescatter;
   Float_t         start_x;
   Float_t         start_y;
   Float_t         start_z;
   Float_t         start_t;
   Float_t         end_x;
   Float_t         end_y;
   Float_t         end_z;
   Float_t         end_t;
   Float_t         px;
   Float_t         py;
   Float_t         pz;
   Float_t         p;
   Float_t         pt;
   Float_t         e;
   Float_t         mass;
   Float_t         end_px;
   Float_t         end_py;
   Float_t         end_pz;
   Float_t         end_e;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_subrun;   //!
   TBranch        *b_event;   //!
   TBranch        *b_truth_index;   //!
   TBranch        *b_p_index;   //!
   TBranch        *b_status;   //!
   TBranch        *b_trackid;   //!
   TBranch        *b_pdgcode;   //!
   TBranch        *b_mother;   //!
   TBranch        *b_process;   //!
   TBranch        *b_endprocess;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_rescatter;   //!
   TBranch        *b_start_x;   //!
   TBranch        *b_start_y;   //!
   TBranch        *b_start_z;   //!
   TBranch        *b_start_t;   //!
   TBranch        *b_end_x;   //!
   TBranch        *b_end_y;   //!
   TBranch        *b_end_z;   //!
   TBranch        *b_end_t;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_p;   //!
   TBranch        *b_pt;   //!
   TBranch        *b_e;   //!
   TBranch        *b_mass;   //!
   TBranch        *b_end_px;   //!
   TBranch        *b_end_py;   //!
   TBranch        *b_end_pz;   //!
   TBranch        *b_end_e;   //!

   particle_tree(TTree *tree=0);
   virtual ~particle_tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef particle_tree_cxx
particle_tree::particle_tree(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("/pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root:/mcana");
      dir->GetObject("particle_tree",tree);      

   }
   Init(tree);
}

particle_tree::~particle_tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t particle_tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t particle_tree::LoadTree(Long64_t entry)
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

void particle_tree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   process = 0;
   endprocess = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("subrun", &subrun, &b_subrun);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("truth_index", &truth_index, &b_truth_index);
   fChain->SetBranchAddress("p_index", &p_index, &b_p_index);
   fChain->SetBranchAddress("status", &status, &b_status);
   fChain->SetBranchAddress("trackid", &trackid, &b_trackid);
   fChain->SetBranchAddress("pdgcode", &pdgcode, &b_pdgcode);
   fChain->SetBranchAddress("mother", &mother, &b_mother);
   fChain->SetBranchAddress("process", &process, &b_process);
   fChain->SetBranchAddress("endprocess", &endprocess, &b_endprocess);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("rescatter", &rescatter, &b_rescatter);
   fChain->SetBranchAddress("start_x", &start_x, &b_start_x);
   fChain->SetBranchAddress("start_y", &start_y, &b_start_y);
   fChain->SetBranchAddress("start_z", &start_z, &b_start_z);
   fChain->SetBranchAddress("start_t", &start_t, &b_start_t);
   fChain->SetBranchAddress("end_x", &end_x, &b_end_x);
   fChain->SetBranchAddress("end_y", &end_y, &b_end_y);
   fChain->SetBranchAddress("end_z", &end_z, &b_end_z);
   fChain->SetBranchAddress("end_t", &end_t, &b_end_t);
   fChain->SetBranchAddress("px", &px, &b_px);
   fChain->SetBranchAddress("py", &py, &b_py);
   fChain->SetBranchAddress("pz", &pz, &b_pz);
   fChain->SetBranchAddress("p", &p, &b_p);
   fChain->SetBranchAddress("pt", &pt, &b_pt);
   fChain->SetBranchAddress("e", &e, &b_e);
   fChain->SetBranchAddress("mass", &mass, &b_mass);
   fChain->SetBranchAddress("end_px", &end_px, &b_end_px);
   fChain->SetBranchAddress("end_py", &end_py, &b_end_py);
   fChain->SetBranchAddress("end_pz", &end_pz, &b_end_pz);
   fChain->SetBranchAddress("end_e", &end_e, &b_end_e);
   Notify();
}

Bool_t particle_tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void particle_tree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t particle_tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef particle_tree_cxx
