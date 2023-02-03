#define NeutrinoSelectionFilter_cxx
#include "NeutrinoSelectionFilter.h"
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TH1D.h>
#include <TH2D.h>

#include <fstream>
#include <iomanip>
#include <vector>

#include "../myClasses/Tools.h"

using namespace std;

//----------------------------------------//

void NeutrinoSelectionFilter::Loop() {

	//----------------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

	//----------------------------------------//

	// Output Files

	TString filename = "/sbnd/data/users/apapadop/myPreSelection/preselection_"+SBNDCodeVersion+".root";
	TFile* outfile = new TFile(filename,"recreate");
	cout << endl << "File " << filename << " to be created"<< endl << endl;

	//----------------------------------------//

	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	//----------------------------------------//

	// TTree Declarations

	TTree* truetree = new TTree("truepreselection","truepreselection");
/*	TTree* recotree = new TTree("recopreselection","recopreselection");	*/

	//----------------------------------------//

	// Common True & Reco branches	

	int ismc;
	double pot;
	int run;
	int subrun;
	int event;

	truetree->Branch("ismc",&ismc);
	truetree->Branch("pot",&pot);
	truetree->Branch("run",&run);
	truetree->Branch("subrun",&subrun);
	truetree->Branch("event",&event);
/*
	recotree->Branch("ismc",&ismc);
	recotree->Branch("pot",&pot);	
	recotree->Branch("run",&run);
	recotree->Branch("subrun",&subrun);
	recotree->Branch("event",&event);		
*/
	//----------------------------------------//

	// True Branches

	vector<double> true_Ev;     truetree->Branch("true_Ev",&true_Ev);
	vector<double> true_vx;     truetree->Branch("true_vx",&true_vx);
	vector<double> true_vy;     truetree->Branch("true_vy",&true_vy);
	vector<double> true_vz;     truetree->Branch("true_vz",&true_vz);
	vector<double> true_pvx;    truetree->Branch("true_pvx",&true_pvx);
	vector<double> true_pvy;    truetree->Branch("true_pvy",&true_pvy);
	vector<double> true_pvz;    truetree->Branch("true_pvz",&true_pvz);	
	vector<int>    true_mode;   truetree->Branch("true_mode",&true_mode);
	vector<int>    true_hitnuc; truetree->Branch("true_hitnuc",&true_hitnuc);		

	vector< vector<int> >    true_particle_pdg; 	 truetree->Branch("true_particle_pdg",&true_particle_pdg);
	vector< vector<double> > true_particle_p; 	     truetree->Branch("true_particle_p",&true_particle_p);
	vector< vector<double> > true_particle_phi;	     truetree->Branch("true_particle_phi",&true_particle_phi);
	vector< vector<double> > true_particle_costheta; truetree->Branch("true_particle_costheta",&true_particle_costheta);
	vector< vector<double> > true_particle_startx;	 truetree->Branch("true_particle_startx",&true_particle_startx);
	vector< vector<double> > true_particle_starty;	 truetree->Branch("true_particle_starty",&true_particle_starty);
	vector< vector<double> > true_particle_startz;	 truetree->Branch("true_particle_startz",&true_particle_startz);

	//----------------------------------------//

	// Reco Branches	
/*
	int CC; recotree->Branch("CC",&CC);	
	int NC;	recotree->Branch("NC",&NC);						
*/
	//----------------------------------------//

	Tools tools;

	//----------------------------------------//

	// Counters

	int totalcounter = 0;
	int true_ccincl = 0;	

	//----------------------------------------//

	// Loop over the events

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		//----------------------------------------//
      
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
      	nb = fChain->GetEntry(jentry);   nbytes += nb;

		//----------------------------------------//

		if (jentry%1000 == 0) cout << jentry/1000 << " k " << setprecision(3) << double(jentry)/double(fChain->GetEntries())*100. << " %"<< endl;

		//----------------------------------------//

		// Common True & Reco Branches

		true_Ev.clear();
		true_vx.clear();
		true_vy.clear();
		true_vz.clear();
		true_pvx.clear();
		true_pvy.clear();
		true_pvz.clear();		
		true_mode.clear();
		true_hitnuc.clear();									

		//----------------------------------------//

		// True Branches

		true_particle_pdg.clear();
		true_particle_p.clear();
		true_particle_phi.clear();
		true_particle_costheta.clear();
		true_particle_startx.clear();
		true_particle_starty.clear();
		true_particle_startz.clear();

		//----------------------------------------//

		// Common branches

		ismc = rec_hdr_ismc;
		pot = rec_hdr_pot;
		run = rec_hdr_run;
		subrun = rec_hdr_subrun;
		event = rec_hdr_subevt;	

		//----------------------------------------//

		// Loop over the true neutrino interactions in a given event

		for (int nnu = 0; nnu < (int)rec_mc_nnu; nnu++) {

			totalcounter++;			

			//----------------------------------------//	

			// True fully contained CC numu inclusive selection
			// Later, at an event selection stage,
			// we will demand only true CC νμ + n -> μ- + p + π0 primary interactions
			// Demand only numu CC events contained in the fiducial volume		

			if (
				ismc && rec_mc_nu_iscc[nnu] == 1 && rec_mc_nu_pdg[nnu] == 14 && 
				tools.inFV(rec_mc_nu_position_x[nnu], rec_mc_nu_position_y[nnu], rec_mc_nu_position_z[nnu]) == 1
			) {

				//----------------------------------------//	

				true_ccincl++;			
				
				// Store the true neutrino info

				true_Ev.push_back(rec_mc_nu_E[nnu]);
				true_vx.push_back(rec_mc_nu_position_x[nnu]);
				true_vy.push_back(rec_mc_nu_position_y[nnu]);
				true_vz.push_back(rec_mc_nu_position_z[nnu]);
				true_pvx.push_back(rec_mc_nu_momentum_x[nnu]);
				true_pvy.push_back(rec_mc_nu_momentum_y[nnu]);
				true_pvz.push_back(rec_mc_nu_momentum_z[nnu]);				
				true_mode.push_back(rec_mc_nu_genie_mode[nnu]);
				true_hitnuc.push_back(rec_mc_nu_hitnuc[nnu]);				

				//----------------------------------------//

				int NPrimaries = rec_mc_nu_nprim[nnu];

				// Loop over the primary MC particles
				// after the primary neutrino interaction

				for (int iprim = 0; iprim < NPrimaries; iprim++) {

	//cout << "rec_mc_nu_prim_genp_x["<< iprim << "] = " << rec_mc_nu_prim_genp_x[iprim] << endl;

				}


	//			for (int iprim = 0; iprim < NPrimaries; iprim++) {

	//cout << "rec_mc_nu_prim_genp_x["<< iprim << "] = " << rec_mc_nu_prim_genp_x[iprim] << endl;
	//cout << "rec_mc_nu_prim_genp_y["<< iprim << "] = " << rec_mc_nu_prim_genp_y[iprim] << endl;
	//cout << "rec_mc_nu_prim_genp_z["<< iprim << "] = " << rec_mc_nu_prim_genp_z[iprim] << endl;
	//cout << "rec_mc_nu_prim_gen_x["<< iprim << "] = " << rec_mc_nu_prim_gen_x[iprim] << endl;
	//cout << "rec_mc_nu_prim_gen_y["<< iprim << "] = " << rec_mc_nu_prim_gen_y[iprim] << endl;
	//cout << "rec_mc_nu_prim_gen_z["<< iprim << "] = " << rec_mc_nu_prim_gen_z[iprim] << endl;
	//cout << "rec_mc_nu_prim_genE["<< iprim << "] = " << rec_mc_nu_prim_genE[iprim] << endl;
	//cout << "rec_mc_nu_prim_pdg["<< iprim << "] = " << rec_mc_nu_prim_pdg[iprim] << endl;

	//			}

			} // End of the if-statement that the numu CC inclusive requirement is satified

		} // End of the loop over the true neutrino interactions in a given event

		truetree->Fill();		

//cout << endl;
		
	} // End of the loop over the events

	//----------------------------------------//

	cout << endl << "The file initially contains " << totalcounter << " true neutrino interactions" << endl;
	cout << true_ccincl << " are passing the true inclusive selection" << endl;	

	//----------------------------------------//

	outfile->cd();
	truetree->Write();
	outfile->Close();
	cout << endl << "File " << filename << " has been created"<< endl << endl;

	//----------------------------------------//

} // End of the program