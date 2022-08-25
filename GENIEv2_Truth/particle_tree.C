#define particle_tree_cxx
#include "particle_tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TLorentzVector.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "ubana/myClasses/Constants.h"
#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/STV_Tools.h"

using namespace std;
using namespace Constants;

void particle_tree::Loop() {

   //----------------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

   //----------------------------------------//

	// Output Files

	TString FileName = "/uboone/data/users/apapadop/PeLEETuples/PreFilter_GENIEv2Overlay9_Combined_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

   //----------------------------------------//

   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;   

   //----------------------------------------//
   //----------------------------------------//   

   TFile *fmctruth = (TFile*)gROOT->GetListOfFiles()->FindObject("/pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root");   
   TDirectory * dirmctruth = (TDirectory*)fmctruth->Get("/pnfs/uboone/persistent/users/apapadop/Truth_Fake_Data_5.root:/mcana");
   TTree* tmctruth = (TTree*)dirmctruth->Get("mctruth_tree");

   int           n_particles;
   int           origin;
   int           mode;
   int           interaction_type;
   int           ccnc;
   int           target;
   int           hit_nucl;
   int           hit_quark;
   float         hadronic_mass;
   float         interaction_x;
   float         interaction_y;
   float         interaction_q2;
   float         interaction_pt;
   float         interaction_theta;  

   tmctruth->SetBranchAddress("n_particles", &n_particles);
   tmctruth->SetBranchAddress("origin", &origin);
   tmctruth->SetBranchAddress("mode", &mode);
   tmctruth->SetBranchAddress("interaction_type", &interaction_type);
   tmctruth->SetBranchAddress("ccnc", &ccnc);
   tmctruth->SetBranchAddress("target", &target);
   tmctruth->SetBranchAddress("hit_nucl", &hit_nucl);
   tmctruth->SetBranchAddress("hit_quark", &hit_quark);
   tmctruth->SetBranchAddress("hadronic_mass", &hadronic_mass);
   tmctruth->SetBranchAddress("interaction_x", &interaction_x);
   tmctruth->SetBranchAddress("interaction_y", &interaction_y);
   tmctruth->SetBranchAddress("interaction_q2", &interaction_q2);
   tmctruth->SetBranchAddress("interaction_pt", &interaction_pt);
   tmctruth->SetBranchAddress("interaction_theta", &interaction_theta);    

   Long64_t nentriesmctruth = tmctruth->GetEntriesFast();  
   Long64_t nbytesmctruth = 0, nbmctruth = 0;   

   //----------------------------------------//
   //----------------------------------------//

	// TTree
	TTree* tree = new TTree("myPreFilter","myPreFilter");

   //----------------------------------------//

	unsigned int Run = 1;
	unsigned int SubRun = 1;
	unsigned int Event = 1;
   string *Process;   
   string *Endprocess;
   int           N_particles = -99;
   int           Origin = -99;
   int           Mode = -99;
   int           Interaction_type = -99;
   int           Ccnc = -99;
   int           Target = -99;
   int           Hit_nucl = -99;
   int           Hit_quark = -99;
   float         Hadronic_mass = -99;
   float         Interaction_x = -99;
   float         Interaction_y = -99;
   float         Interaction_q2 = -99;
   float         Interaction_pt = -99;
   float         Interaction_theta = -99;    

   std::vector<unsigned int> Truth_index;
   std::vector<unsigned int> P_index;
   std::vector<unsigned int> Status;
   std::vector<unsigned int> Trackid;         
   std::vector<unsigned int> Pdgcode;
   std::vector<unsigned int> Mother;
   std::vector<int> Rescatter;
   std::vector<float> Start_X;
   std::vector<float> Start_Y;                 
   std::vector<float> Start_Z;
   std::vector<float> Start_T;
   std::vector<float> End_X;
   std::vector<float> End_Y;                 
   std::vector<float> End_Z;
   std::vector<float> End_T;      
   std::vector<float> Px;
   std::vector<float> Py;
   std::vector<float> Pz; 
   std::vector<float> P;
   std::vector<float> Pt; 
   std::vector<float> E;
   std::vector<float> Mass; 
   std::vector<float> End_px;
   std::vector<float> End_py;
   std::vector<float> End_pz; 
   std::vector<float> End_e;                    

   //----------------------------------------//	

	tree->Branch("Run",&Run);
	tree->Branch("SubRun",&SubRun);
	tree->Branch("Event",&Event);	
   tree->Branch("Process",&Process);   
   tree->Branch("Endprocess",&Endprocess);   
   tree->Branch("N_particles", &N_particles);
   tree->Branch("Origin", &Origin);
   tree->Branch("Mode", &Mode);
   tree->Branch("Interaction_type", &Interaction_type);
   tree->Branch("Ccnc", &Ccnc);
   tree->Branch("Target", &Target);
   tree->Branch("Hit_nucl", &Hit_nucl);
   tree->Branch("Hit_quark", &Hit_quark);
   tree->Branch("Hadronic_mass", &Hadronic_mass);
   tree->Branch("Interaction_x", &Interaction_x);
   tree->Branch("Interaction_y", &Interaction_y);
   tree->Branch("Interaction_q2", &Interaction_q2);
   tree->Branch("Interaction_pt", &Interaction_pt);
   tree->Branch("Interaction_theta", &Interaction_theta); 

	tree->Branch("Truth_index",&Truth_index);
	tree->Branch("P_index",&P_index);   
	tree->Branch("Status",&Status);
	tree->Branch("Trackid",&Trackid);         
	tree->Branch("Pdgcode",&Pdgcode);	
   tree->Branch("Mother",&Mother);   
   tree->Branch("Rescatter",&Rescatter);
   tree->Branch("Start_X",&Start_X);
   tree->Branch("Start_Y",&Start_Y);      
   tree->Branch("Start_Z",&Start_Z);
   tree->Branch("Start_T",&Start_T);
   tree->Branch("End_X",&End_X);
   tree->Branch("End_Y",&End_Y);      
   tree->Branch("End_Z",&End_Z);
   tree->Branch("End_T",&End_T);   
   tree->Branch("Px",&Px);
   tree->Branch("Py",&Py);
   tree->Branch("Pz",&Pz);
   tree->Branch("P",&P);
   tree->Branch("Pt",&Pt);
   tree->Branch("E",&E);      
   tree->Branch("Mass",&Mass);
   tree->Branch("End_px",&End_px);
   tree->Branch("End_py",&End_py);
   tree->Branch("End_pz",&End_pz);
   tree->Branch("End_e",&End_e);

   //----------------------------------------//

   int EventCounter = 0;

   //----------------------------------------//               

   // Loop over the events

   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      //----------------------------------------//

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   
      nbytes += nb;     

      //----------------------------------------//
      
		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

      //----------------------------------------//

      if ( !(Run == run && SubRun == subrun && Event == event) ) {

         if (jentry != 0) { tree->Fill(); }       
         
         // Grab infor from the mctruth TTree now
         nbmctruth = tmctruth->GetEntry(EventCounter);   
         nbytesmctruth += nbmctruth; 

         //cout << "New event!" << endl;
         EventCounter++;

         Run = run;
         SubRun = subrun;
         Event = event;
         Process = process;
         Endprocess = endprocess; 
         N_particles = n_particles;
         Origin =  origin;
         Mode =  mode;
         Interaction_type = interaction_type;
         Ccnc = ccnc;
         Target = target;
         Hit_nucl = hit_nucl;
         Hit_quark = hit_quark;
         Hadronic_mass = hadronic_mass;
         Interaction_x = interaction_x;
         Interaction_y = interaction_y;
         Interaction_q2 = interaction_q2;
         Interaction_pt = interaction_pt;
         Interaction_theta = interaction_theta;                                            

         Truth_index.clear();
         P_index.clear();         
         Status.clear();
         Trackid.clear();
         Pdgcode.clear();
         Mother.clear();    
         Rescatter.clear();
         Start_X.clear();
         Start_Y.clear();                                                  
         Start_Z.clear();
         Start_T.clear();
         End_X.clear();
         End_Y.clear();                                                  
         End_Z.clear();
         End_T.clear();
         Px.clear();
         Py.clear();                  
         Pz.clear();
         P.clear();
         Pt.clear();
         E.clear();
         Mass.clear();
         End_px.clear();
         End_py.clear();                  
         End_pz.clear();
         End_e.clear();

      }    

      //----------------------------------------// 

      Truth_index.push_back(truth_index);
      P_index.push_back(p_index);      
      Status.push_back(status);
      Trackid.push_back(trackid);   
      Pdgcode.push_back(pdgcode);
      Mother.push_back(mother);
      Rescatter.push_back(rescatter);
      Start_X.push_back(start_x);
      Start_Y.push_back(start_y);                                       
      Start_Z.push_back(start_z);
      Start_T.push_back(start_t);
      End_X.push_back(end_x);
      End_Y.push_back(end_y);                                       
      End_Z.push_back(end_z);
      End_T.push_back(end_t); 
      Px.push_back(px);
      Py.push_back(py);                  
      Pz.push_back(pz);
      P.push_back(p);
      Pt.push_back(pt);
      E.push_back(e);
      Mass.push_back(mass);
      End_px.push_back(end_px);
      End_py.push_back(end_py);                  
      End_pz.push_back(end_pz);
      End_e.push_back(end_e);           

      //----------------------------------------//
 

//cout << "run = " << run << " subrun = " << subrun << " event = " << event << " pdgcode = " << pdgcode << endl;

      //----------------------------------------//     

 

      //----------------------------------------//      

   } // End of the loop over the events

   //----------------------------------------//

	OutputFile->cd();
	OutputFile->Write();
	OutputFile->Close();
	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;
	std::cout << std::endl << "Events = " << EventCounter << std::endl << std::endl;      

   //----------------------------------------//

} // End of the program