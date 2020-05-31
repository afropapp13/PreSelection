#define PreTruthSelection_cxx
#include "PreTruthSelection.h"
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>
#include <TFile.h>
#include <TSpline.h>
#include <TProfile.h>
#include <TTree.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "ubana/myClasses/Tools.h"

using namespace std;
using namespace Constants;

void PreTruthSelection::Loop() {

	if (fChain == 0) { return; } 
	Long64_t nentries = fChain->GetEntriesFast(); Long64_t nbytes = 0, nb = 0;

	TH1D::SetDefaultSumw2();

	// --------------------------------------------------------------------------------------------------------------------------------------------------

	// Output Files

	TString FileName = "../myEvents/mySamples/"+UBCodeVersion+"/PreTruthSelection_"+fWhichSample+"_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

	// ----------------------------------------------------------------------------------------------------------------------------------------

	// TTree

	TTree* tree = new TTree("myPreTruthSelection","myPreTruthSelection");

	// ------------------------------------------------------------------------------------------------------------------------------------------

	double Weight;
	double T2KWeight;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	int NumberMCParticles;
	int CC1p;

	std::vector<int> MCParticle_Mode;
	std::vector<double> MCParticle_Mom;
//	std::vector<double> MCParticle_KE;
	std::vector<double> MCParticle_Phi;
	std::vector<double> MCParticle_CosTheta;
//	std::vector<double> MCParticle_Length;
//	std::vector<double> MCParticle_StartX;
//	std::vector<double> MCParticle_StartY;
//	std::vector<double> MCParticle_StartZ;
//	std::vector<double> MCParticle_EndPointX;
//	std::vector<double> MCParticle_EndPointY;
//	std::vector<double> MCParticle_EndPointZ;
	std::vector<int> MCParticle_StartContainment;
	std::vector<int> MCParticle_EndContainment;
	std::vector<int> MCParticle_Pdg;

	// -------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("Weight",&Weight);
	tree->Branch("T2KWeight",&T2KWeight);

	// -------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("NumberMCParticles",&NumberMCParticles);
	tree->Branch("CC1p",&CC1p);
	tree->Branch("MCParticle_Mode",&MCParticle_Mode);
	tree->Branch("MCParticle_Mom",&MCParticle_Mom);
//	tree->Branch("MCParticle_KE",&MCParticle_KE);
	tree->Branch("MCParticle_Phi",&MCParticle_Phi);
	tree->Branch("MCParticle_CosTheta",&MCParticle_CosTheta);
//	tree->Branch("MCParticle_Length",&MCParticle_Length);
//	tree->Branch("MCParticle_StartX",&MCParticle_StartX);
//	tree->Branch("MCParticle_StartY",&MCParticle_StartY);
//	tree->Branch("MCParticle_StartZ",&MCParticle_StartZ);
//	tree->Branch("MCParticle_EndPointX",&MCParticle_EndPointX);
//	tree->Branch("MCParticle_EndPointY",&MCParticle_EndPointY);
//	tree->Branch("MCParticle_EndPointZ",&MCParticle_EndPointZ);
	tree->Branch("MCParticle_StartContainment",&MCParticle_StartContainment);
	tree->Branch("MCParticle_EndContainment",&MCParticle_EndContainment);
	tree->Branch("MCParticle_Pdg",&MCParticle_Pdg);

	// -----------------------------------------------------------------------------------------------------------------------------------------

	Tools tools;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	// Event Counters

	int EventCounter = 0;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {
//	for (Long64_t jentry=0; jentry<1002;jentry++) {
//	for (Long64_t jentry=0; jentry<10002;jentry++) {

		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;
		Long64_t ientry = LoadTree(jentry); if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;

		// ---------------------------------------------------------------------------------------------------------------------------------

//		double weight = 1.;
		double weight = EventWeight->at(0); // spline bug fix from v3.0.4 to v3.0.6
		Weight = weight;

		double T2Kweight = T2KEventWeight->at(0); // MicroBooNE tune based on T2K 
		T2KWeight = T2Kweight;

		// ------------------------------------------------------------------------------------------------------------------------------

		// MCParticles

		MCParticle_Mode.clear();
		MCParticle_Mom.clear();
//		MCParticle_KE.clear();
		MCParticle_Phi.clear();
		MCParticle_CosTheta.clear();
//		MCParticle_Length.clear();
//		MCParticle_StartX.clear();
//		MCParticle_StartY.clear();
//		MCParticle_StartZ.clear();
//		MCParticle_EndPointX.clear();
//		MCParticle_EndPointY.clear();
//		MCParticle_EndPointZ.clear();
		MCParticle_StartContainment.clear();
		MCParticle_EndContainment.clear();
		MCParticle_Pdg.clear();

		int NMCParticles = MCParticle_Vx->size();

		int StableMCParticles = 0;
		int fCC1p = 0;
		int TrueMuonCounter = 0, TrueProtonCounter = 0, TrueChargedPionCounter = 0;

		// Loop over the MCParticles and determine the populations

		for (int WhichMCParticle = 0; WhichMCParticle < NMCParticles; WhichMCParticle++) {

			// Demand stable final state particles

			if (MCParticle_StatusCode->at(WhichMCParticle) == 1) {
			
				double MCParticleStartX = MCParticle_Vx->at(WhichMCParticle);
				double MCParticleStartY = MCParticle_Vy->at(WhichMCParticle);
				double MCParticleStartZ = MCParticle_Vz->at(WhichMCParticle);
				
				double MCParticleEndX = MCParticle_EndX->at(WhichMCParticle);
				double MCParticleEndY = MCParticle_EndY->at(WhichMCParticle);
				double MCParticleEndZ = MCParticle_EndZ->at(WhichMCParticle);								

				TVector3 TVector3TrueStart(MCParticleStartX,MCParticleStartY,MCParticleStartZ);
				TVector3 TVector3TrueEnd(MCParticleEndX,MCParticleEndY,MCParticleEndZ);
				TVector3 TVector3TrueChange = TVector3TrueEnd - TVector3TrueStart;
				bool TrueStartContainment = tools.inFVVector(TVector3TrueStart);
				bool TrueEndContainment = tools.inFVVector(TVector3TrueEnd);

				double TrueLength = TVector3TrueChange.Mag();
				double TrueTheta = TVector3TrueChange.Theta();
				double TrueTheta_Deg = TVector3TrueChange.Theta()*180./TMath::Pi();
				double TruePhi = TVector3TrueChange.Phi();
				double TruePhi_Deg = TVector3TrueChange.Phi()*180./TMath::Pi();
				double TrueCosTheta = TVector3TrueChange.CosTheta();
				double TrueMomentum_GeV = MCParticle_P->at(WhichMCParticle); // GeV
				double TrueMomentum_MeV = 1000. * TrueMomentum_GeV; // MeV
				double TrueKE_MeV = tools.PToKE(MCParticle_PdgCode->at(WhichMCParticle),TrueMomentum_MeV); // MeV
				double TrueKE_GeV = TrueKE_MeV / 1000.; // GeV
				
				double MCParticleMomentum = MCParticle_P->at(WhichMCParticle);

				if (MCParticle_PdgCode->at(WhichMCParticle) == MuonPdg && MCParticleMomentum > ArrayNBinsMuonMomentum[0])
					{ TrueMuonCounter++; }

				if (MCParticle_PdgCode->at(WhichMCParticle) == ProtonPdg && MCParticleMomentum > ArrayNBinsProtonMomentum[0]) 
					{ TrueProtonCounter++; }

				if (fabs(MCParticle_PdgCode->at(WhichMCParticle)) == AbsChargedPionPdg && MCParticleMomentum > ChargedPionMomentumThres) 
					{ TrueChargedPionCounter++; }

				MCParticle_Mode.push_back(MCTruth_Mode->at(0));
				MCParticle_Mom.push_back(TrueMomentum_GeV);
//				MCParticle_KE.push_back(TrueKE_GeV);
				MCParticle_Phi.push_back(TruePhi_Deg);
				MCParticle_CosTheta.push_back(TrueCosTheta);
//				MCParticle_Length.push_back(TrueLength);
//				MCParticle_StartX.push_back(TVector3TrueStart.X());
//				MCParticle_StartY.push_back(TVector3TrueStart.Y());
//				MCParticle_StartZ.push_back(TVector3TrueStart.Z());
//				MCParticle_EndPointX.push_back(TVector3TrueEnd.X());
//				MCParticle_EndPointY.push_back(TVector3TrueEnd.Y());
//				MCParticle_EndPointZ.push_back(TVector3TrueEnd.Z());
				MCParticle_StartContainment.push_back(TrueStartContainment);
				MCParticle_EndContainment.push_back(TrueEndContainment);
				MCParticle_Pdg.push_back(MCParticle_PdgCode->at(WhichMCParticle));

				StableMCParticles++;

			} // End of the demand stable final state particles and primary interactions

		} // end of the loop over the MCParticles

		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 0) { fCC1p = 1; }
		CC1p = fCC1p;

		NumberMCParticles = StableMCParticles;

		EventCounter++;
		tree->Fill();

	} // End of the loop over the number of events

	// -------------------------------------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------------------------------------------------------

	// To be printed at the end of the run

	int precision = 2;

	std::cout.precision(precision);
	std::cout << "\n\nTotal of " << EventCounter << " events processed" << std::endl << std::endl;

	// --------------------------------------------------------------------------------------------------------------------------------------------

	OutputFile->cd();
	OutputFile->Write();
	OutputFile->Close();
	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;

} // end of the program

// --------------------------------------------------------------------------------------------------------------------------------------------
