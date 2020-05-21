#define PreSelection_cxx
#include "PreSelection.h"
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

#include "ubana/MyClasses/Tools.h"
#include "ubana/MyClasses/SelectionCuts.h"
#include "ubana/MyClasses/Constants.h"

using namespace std;
using namespace Constants;

double ThreePlaneChi2(TVector3 TrackStart,TVector3 TrackEnd,double Chi2_Plane0,double Chi2_Plane1,double Chi2_Plane2);

void PreSelection::Loop() {

	if (fChain == 0) { return; } 
	Long64_t nentries = fChain->GetEntriesFast(); Long64_t nbytes = 0, nb = 0;

	TH1D::SetDefaultSumw2();

	std::vector<TVector3> VectorTrackStart;
	std::vector<TVector3> VectorTrackEnd;

	std::vector<TVector3> VectorMCParticleStart;
	std::vector<TVector3> VectorMCParticleEnd;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Momentum from range

	TFile *fSpines = TFile::Open("Proton_Muon_Range_dEdx_LAr_TSplines.root","READ");
	TSpline3* sMuonRange2T = (TSpline3*)fSpines->Get("sMuonRange2T");
	TSpline3* sProtonRange2T = (TSpline3*)fSpines->Get("sProtonRange2T");

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Output Files

	TString FileName = "../myEvents/mySamples/"+UBCodeVersion+"/PreSelection_"+fWhichSample+"_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// TTree

	TTree* tree = new TTree("myPreSelection","myPreSelection");

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//	int PassedSwTrigger;
	double Weight;
	double T2KWeight;
	int CC1p;
	int MCParticle_Mode;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	double NuScore;
	double FlashScore; 

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int NBeamFlashes;
	std::vector<double> BeamFlashes_YCenter;
	std::vector<double> BeamFlashes_ZCenter;
	std::vector<double> BeamFlashes_TotalPE;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<double> CandidateMuP_Distance;
	std::vector<double> Vertex_X;
	std::vector<double> Vertex_Y;
	std::vector<double> Vertex_Z;

	std::vector<int> CandidateMu_Mode;
	std::vector<double> CandidateMu_P;
	std::vector<double> CandidateMu_Phi;
	std::vector<double> CandidateMu_CosTheta;
	std::vector<double> CandidateMu_Chi2_YPlane;
	std::vector<double> CandidateMu_ThreePlaneLogLikelihood;
	std::vector<double> CandidateMu_ThreePlaneChi2;
	std::vector<int> CandidateMu_StartContainment;
	std::vector<int> CandidateMu_EndContainment;
	std::vector<int> CandidateMu_MCParticle_Pdg;
	std::vector<double> CandidateMu_MCParticle_Purity;

	std::vector<double> True_CandidateMu_P;
	std::vector<double> True_CandidateMu_Phi;
	std::vector<double> True_CandidateMu_CosTheta;
	std::vector<int> True_CandidateMu_StartContainment;
	std::vector<int> True_CandidateMu_EndContainment;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<int> CandidateP_Mode;
	std::vector<double> CandidateP_P;
	std::vector<double> CandidateP_Phi;
	std::vector<double> CandidateP_CosTheta;
	std::vector<double> CandidateP_Chi2_YPlane;
	std::vector<double> CandidateP_ThreePlaneLogLikelihood;
	std::vector<double> CandidateP_ThreePlaneChi2;
	std::vector<int> CandidateP_StartContainment;
	std::vector<int> CandidateP_EndContainment;
	std::vector<int> CandidateP_MCParticle_Pdg;
	std::vector<double> CandidateP_MCParticle_Purity;

	std::vector<double> True_CandidateP_P;
	std::vector<double> True_CandidateP_Phi;
	std::vector<double> True_CandidateP_CosTheta;
	std::vector<int> True_CandidateP_StartContainment;
	std::vector<int> True_CandidateP_EndContainment;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("Weight",&Weight);
	tree->Branch("T2KWeight",&T2KWeight);
	tree->Branch("CC1p",&CC1p);
	tree->Branch("MCParticle_Mode",&MCParticle_Mode);

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("NuScore",&NuScore);
	tree->Branch("FlashScore",&FlashScore);

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("NBeamFlashes",&NBeamFlashes);
	tree->Branch("BeamFlashes_YCenter",&BeamFlashes_YCenter);
	tree->Branch("BeamFlashes_ZCenter",&BeamFlashes_ZCenter);
	tree->Branch("BeamFlashes_TotalPE",&BeamFlashes_TotalPE);

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("CandidateMuP_Distance",&CandidateMuP_Distance);
	tree->Branch("Vertex_X",&Vertex_X);
	tree->Branch("Vertex_Y",&Vertex_Y);
	tree->Branch("Vertex_Z",&Vertex_Z);

	tree->Branch("CandidateMu_P",&CandidateMu_P);
	tree->Branch("CandidateMu_Phi",&CandidateMu_Phi);
	tree->Branch("CandidateMu_CosTheta",&CandidateMu_CosTheta);
	tree->Branch("CandidateMu_Chi2_YPlane",&CandidateMu_Chi2_YPlane);
	tree->Branch("CandidateMu_ThreePlaneLogLikelihood",&CandidateMu_ThreePlaneLogLikelihood);
	tree->Branch("CandidateMu_ThreePlaneChi2",&CandidateMu_ThreePlaneChi2);
	tree->Branch("CandidateMu_StartContainment",&CandidateMu_StartContainment);
	tree->Branch("CandidateMu_EndContainment",&CandidateMu_EndContainment);
	tree->Branch("CandidateMu_MCParticle_Pdg",&CandidateMu_MCParticle_Pdg);
	tree->Branch("CandidateMu_MCParticle_Purity",&CandidateMu_MCParticle_Purity);

	tree->Branch("True_CandidateMu_P",&True_CandidateMu_P);
	tree->Branch("True_CandidateMu_Phi",&True_CandidateMu_Phi);
	tree->Branch("True_CandidateMu_CosTheta",&True_CandidateMu_CosTheta);
	tree->Branch("True_CandidateMu_StartContainment",&True_CandidateMu_StartContainment);
	tree->Branch("True_CandidateMu_EndContainment",&True_CandidateMu_EndContainment);

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("CandidateP_P",&CandidateP_P);
	tree->Branch("CandidateP_Phi",&CandidateP_Phi);
	tree->Branch("CandidateP_CosTheta",&CandidateP_CosTheta);
	tree->Branch("CandidateP_Chi2_YPlane",&CandidateP_Chi2_YPlane);
	tree->Branch("CandidateP_ThreePlaneLogLikelihood",&CandidateP_ThreePlaneLogLikelihood);
	tree->Branch("CandidateP_ThreePlaneChi2",&CandidateP_ThreePlaneChi2);
	tree->Branch("CandidateP_StartContainment",&CandidateP_StartContainment);
	tree->Branch("CandidateP_EndContainment",&CandidateP_EndContainment);
	tree->Branch("CandidateP_MCParticle_Pdg",&CandidateP_MCParticle_Pdg);
	tree->Branch("CandidateP_MCParticle_Purity",&CandidateP_MCParticle_Purity);

	tree->Branch("True_CandidateP_P",&True_CandidateP_P);
	tree->Branch("True_CandidateP_Phi",&True_CandidateP_Phi);
	tree->Branch("True_CandidateP_CosTheta",&True_CandidateP_CosTheta);
	tree->Branch("True_CandidateP_StartContainment",&True_CandidateP_StartContainment);
	tree->Branch("True_CandidateP_EndContainment",&True_CandidateP_EndContainment);

	// ------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Tools tools;

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Event Counters

	int EventCounter = 0;

	// --------------------------------------------------------------------------------------------------------------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;
		Long64_t ientry = LoadTree(jentry); if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;

		// --------------------------------------------------------------------------------------------------------------------------------------------------------------

		double weight = EventWeight->at(0);
		Weight = weight;

		double T2Kweight = T2KEventWeight->at(0);
		T2KWeight = T2Kweight;

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		if ( EventPassedSwTrigger != 1) { continue; }

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		// Numu Slices

		if (NumberNuMuPFParticles != 1) { continue; }

		int NNuMuDaughters = PFParticle_NumberNuMuDaughters->at(0);

		if (NNuMuDaughters != 2) { continue; } // Track-PFParticle Ass don't necessarily exist, so use TracksFromCurrentPFParticleStartX->at(0).size()
		int FirstPFParticleDaughter = 0;
		int SecondPFParticleDaughter = 1;
		if (TracksFromCurrentPFParticleStartX->at(0).size() != 2) { continue; }

		// MuonPdg in this case / Pandora = Track-like object
		if (PFParticle_NumberNuMuDaughtersPdgCode->at(0).at(FirstPFParticleDaughter) != MuonPdg || 
			PFParticle_NumberNuMuDaughtersPdgCode->at(0).at(SecondPFParticleDaughter) != MuonPdg) { continue; }
		if (TracksFromCurrentPFParticleStartX->at(0).at(0) == -99.) { continue; }
		if (TracksFromCurrentPFParticleStartX->at(0).at(1) == -99.) { continue; }

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		// Making sure that we have NuScore & FlashScore

		if (PFParticle_NuScore->size() != 1) { continue; }
		if (PFParticle_FlashScore->size() != 1) { continue; }

		NuScore = PFParticle_NuScore->at(0);
		FlashScore = PFParticle_FlashScore->at(0);

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		// Beam Flashes

		if (NumberFlashesBeam != 1) { continue; }
		NBeamFlashes = NumberFlashesBeam;

		BeamFlashes_YCenter.clear();
		BeamFlashes_ZCenter.clear();
		BeamFlashes_TotalPE.clear();

		for (int WhichBeamFlash = 0; WhichBeamFlash < NBeamFlashes; WhichBeamFlash++) {

			BeamFlashes_YCenter.push_back(FlashesBeam_Ycenter->at(WhichBeamFlash));
			BeamFlashes_ZCenter.push_back(FlashesBeam_Zcenter->at(WhichBeamFlash));
			BeamFlashes_TotalPE.push_back(FlashesBeam_TotalPE->at(WhichBeamFlash));

		}

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

// EventWeight to go here


		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		// Tracks

		VectorTrackStart.clear();
		VectorTrackEnd.clear();

		std::vector<int> FirstTrackIndex; FirstTrackIndex.clear();
		std::vector<int> SecondTrackIndex; SecondTrackIndex.clear();
		std::vector<double> TrackPairDistance; TrackPairDistance.clear();
		std::vector<TVector3> TrackPairVertexPosition; TrackPairVertexPosition.clear();

		int Track_MCParticle_MuonCounter = 0, Track_MCParticle_ProtonCounter = 0, Track_MCParticle_PionCounter = 0;
		int fCC1p = 0, fMCParticle_Mode = -1;

		for (int WhichTrack = 0; WhichTrack < NumberTracks; WhichTrack++) {

			if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(FirstPFParticleDaughter) || 
				Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(SecondPFParticleDaughter)) {

				TVector3 TVector3TrackStart(Track_StartX->at(WhichTrack),Track_StartY->at(WhichTrack),Track_StartZ->at(WhichTrack));
				TVector3 TVector3TrackEnd(Track_EndX->at(WhichTrack),Track_EndY->at(WhichTrack),Track_EndZ->at(WhichTrack));

				VectorTrackStart.push_back(TVector3TrackStart);
				VectorTrackEnd.push_back(TVector3TrackEnd);

				if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(FirstPFParticleDaughter) ) { FirstTrackIndex.push_back(WhichTrack); }
				if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(SecondPFParticleDaughter) ) { SecondTrackIndex.push_back(WhichTrack); }

			}
			
		} // end of the loop over the recob::Tracks


		int NCandidateTrackPairs = FirstTrackIndex.size();
		if (NCandidateTrackPairs != 1) { continue; }

		double fTrackPairDistance = (VectorTrackStart.at(0) - VectorTrackStart.at(1)).Mag();
		TrackPairDistance.push_back(fTrackPairDistance);

		TVector3 VertexPositionV3 = (VectorTrackStart.at(0) + VectorTrackStart.at(1))*0.5;
		TrackPairVertexPosition.push_back(VertexPositionV3);

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		// Loop over the candidate track pairs

		CandidateMuP_Distance.clear();
		Vertex_X.clear();
		Vertex_Y.clear();
		Vertex_Z.clear();

		CandidateMu_Mode.clear();
		CandidateMu_P.clear();
		CandidateMu_Phi.clear();
		CandidateMu_CosTheta.clear();
		CandidateMu_Chi2_YPlane.clear();
		CandidateMu_ThreePlaneLogLikelihood.clear();
		CandidateMu_ThreePlaneChi2.clear();
		CandidateMu_StartContainment.clear();
		CandidateMu_EndContainment.clear();
		CandidateMu_MCParticle_Pdg.clear();
		CandidateMu_MCParticle_Purity.clear();

		True_CandidateMu_P.clear();
		True_CandidateMu_Phi.clear();
		True_CandidateMu_CosTheta.clear();
		True_CandidateMu_StartContainment.clear();
		True_CandidateMu_EndContainment.clear();

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		CandidateP_Mode.clear();
		CandidateP_P.clear();
		CandidateP_Phi.clear();
		CandidateP_CosTheta.clear();
		CandidateP_Chi2_YPlane.clear();
		CandidateP_ThreePlaneLogLikelihood.clear();
		CandidateP_ThreePlaneChi2.clear();
		CandidateP_StartContainment.clear();
		CandidateP_EndContainment.clear();
		CandidateP_MCParticle_Pdg.clear();
		CandidateP_MCParticle_Purity.clear();

		True_CandidateP_P.clear();
		True_CandidateP_Phi.clear();
		True_CandidateP_CosTheta.clear();
		True_CandidateP_StartContainment.clear();
		True_CandidateP_EndContainment.clear();

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		for (int WhichTrackPair = 0; WhichTrackPair < NCandidateTrackPairs; WhichTrackPair++) {

			// Track indices

			int FirstCandidateTrackIndex = FirstTrackIndex.at(WhichTrackPair);
			int SecondCandidateTrackIndex = SecondTrackIndex.at(WhichTrackPair);

			// Get the muon & proton candidates

//			int CandidateMuonTrackIndex = Track_Length->at(FirstCandidateTrackIndex) > Track_Length->at(SecondCandidateTrackIndex)? FirstCandidateTrackIndex :  SecondCandidateTrackIndex;
//			int CandidateProtonTrackIndex = Track_Length->at(FirstCandidateTrackIndex) > Track_Length->at(SecondCandidateTrackIndex)? SecondCandidateTrackIndex :  FirstCandidateTrackIndex;

			int CandidateMuonTrackIndex = Track_ParticleId_ProtonScore_ThreePlanePID->at(FirstCandidateTrackIndex) < Track_ParticleId_ProtonScore_ThreePlanePID->at(SecondCandidateTrackIndex)? FirstCandidateTrackIndex :  SecondCandidateTrackIndex;
			int CandidateProtonTrackIndex = Track_ParticleId_ProtonScore_ThreePlanePID->at(FirstCandidateTrackIndex) < Track_ParticleId_ProtonScore_ThreePlanePID->at(SecondCandidateTrackIndex)? SecondCandidateTrackIndex :  FirstCandidateTrackIndex;


			// ------------------------------------------------------------------------------------------------------------------------------------------

			// Candidate muon

			double CandidateMuonTrackTheta = Track_Theta->at(CandidateMuonTrackIndex); // rad
			double CandidateMuonTrackCosTheta = cos(CandidateMuonTrackTheta);
			double CandidateMuonTrackLength = Track_Length->at(CandidateMuonTrackIndex); // cm
			TVector3 CandidateMuonTrackStart(Track_StartX->at(CandidateMuonTrackIndex),Track_StartY->at(CandidateMuonTrackIndex),Track_StartZ->at(CandidateMuonTrackIndex));
			TVector3 CandidateMuonTrackEnd(Track_EndX->at(CandidateMuonTrackIndex),Track_EndY->at(CandidateMuonTrackIndex),Track_EndZ->at(CandidateMuonTrackIndex));
			bool CandidateMuonTrackStartContainment = tools.inFVVector(CandidateMuonTrackStart);
			bool CandidateMuonTrackEndContainment = tools.inFVVector(CandidateMuonTrackStart);

			// Candidate proton

			double CandidateProtonTrackTheta = Track_Theta->at(CandidateProtonTrackIndex); // rad
			double CandidateProtonTrackCosTheta = cos(CandidateProtonTrackTheta);
			double CandidateProtonTrackLength = Track_Length->at(CandidateProtonTrackIndex); // cm
			TVector3 CandidateProtonTrackStart(Track_StartX->at(CandidateProtonTrackIndex),Track_StartY->at(CandidateProtonTrackIndex),Track_StartZ->at(CandidateProtonTrackIndex));
			TVector3 CandidateProtonTrackEnd(Track_EndX->at(CandidateProtonTrackIndex),Track_EndY->at(CandidateProtonTrackIndex),Track_EndZ->at(CandidateProtonTrackIndex));
			bool CandidateProtonTrackStartContainment = tools.inFVVector(CandidateProtonTrackStart);
			bool CandidateProtonTrackEndContainment = tools.inFVVector(CandidateProtonTrackStart);

			// --------------------------------------------------------------------------------------------------------------------------------------

			CandidateMuP_Distance.push_back(TrackPairDistance.at(WhichTrackPair));	
			Vertex_X.push_back(TrackPairVertexPosition.at(WhichTrackPair).X());
			Vertex_Y.push_back(TrackPairVertexPosition.at(WhichTrackPair).Y());
			Vertex_Z.push_back(TrackPairVertexPosition.at(WhichTrackPair).Z());

			// ----------------------------------------------------------------------------------------------------------------------------------------

			// Muon

			double CandidateMuonTrack_Momentum_MCS_GeV = -99.;
			double CandidateMuonTrack_Momentum_MCS_MeV = -99.;
			double CandidateMuonTrack_KE_MeV = -99.;
			double CandidateMuonTrack_KE_GeV = -99.;
			double CandidateMuonTrack_E_GeV = -99.;
			double CalCandidateMu_ThreePlaneChi2 = ThreePlaneChi2(CandidateMuonTrackStart,CandidateMuonTrackEnd,
								Track_ParticleId_ProtonScore_Chi2_UPlane->at(CandidateMuonTrackIndex),
								Track_ParticleId_ProtonScore_Chi2_VPlane->at(CandidateMuonTrackIndex),
								Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateMuonTrackIndex));

			if (CandidateMuonTrackStartContainment == true && CandidateMuonTrackEndContainment == true) {

				CandidateMuonTrack_KE_MeV = sMuonRange2T->Eval(CandidateMuonTrackLength); // MeV
				CandidateMuonTrack_KE_GeV = CandidateMuonTrack_KE_MeV / 1000.; // GeV
				CandidateMuonTrack_Momentum_MCS_MeV = tools.KEToP(MuonPdg,CandidateMuonTrack_KE_MeV); // MeV/c
				CandidateMuonTrack_Momentum_MCS_GeV = CandidateMuonTrack_Momentum_MCS_MeV / 1000.; // GeV/c
				CandidateMuonTrack_E_GeV = CandidateMuonTrack_KE_GeV + MuonMass_GeV; // GeV/c

			} else {

				CandidateMuonTrack_Momentum_MCS_GeV = Track_Momentum_MCS->at(CandidateMuonTrackIndex); // GeV/c
				CandidateMuonTrack_Momentum_MCS_MeV = 1000. * CandidateMuonTrack_Momentum_MCS_GeV; // MeV/c
				CandidateMuonTrack_KE_MeV = tools.PToKE(MuonPdg,CandidateMuonTrack_Momentum_MCS_MeV); // MeV/c
				CandidateMuonTrack_KE_GeV = CandidateMuonTrack_KE_MeV / 1000.; // GeV/c
				CandidateMuonTrack_E_GeV = CandidateMuonTrack_KE_GeV + MuonMass_GeV; // GeV/c

			}

			CandidateMu_P.push_back(CandidateMuonTrack_Momentum_MCS_GeV);
			CandidateMu_Phi.push_back(Track_Phi->at(CandidateMuonTrackIndex) * 180./ TMath::Pi()); // deg
			CandidateMu_CosTheta.push_back(CandidateMuonTrackCosTheta);
			CandidateMu_Chi2_YPlane.push_back(Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateMuonTrackIndex));
			CandidateMu_ThreePlaneLogLikelihood.push_back(Track_ParticleId_ProtonScore_ThreePlanePID->at(CandidateMuonTrackIndex));
			CandidateMu_ThreePlaneChi2.push_back(CalCandidateMu_ThreePlaneChi2);
			CandidateMu_StartContainment.push_back(CandidateMuonTrackStartContainment);
			CandidateMu_EndContainment.push_back(CandidateMuonTrackEndContainment);

			// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

			// Proton

			double CandidateProtonTrack_Momentum_MCS_GeV = -99.;
			double CandidateProtonTrack_Momentum_MCS_MeV = -99.;
			double CandidateProtonTrack_KE_MeV = -99.;
			double CandidateProtonTrack_KE_GeV = -99.;
			double CandidateProtonTrack_E_GeV = -99.;
			double CalCandidateP_ThreePlaneChi2 = ThreePlaneChi2(CandidateProtonTrackStart,CandidateProtonTrackEnd,
								Track_ParticleId_ProtonScore_Chi2_UPlane->at(CandidateProtonTrackIndex),
								Track_ParticleId_ProtonScore_Chi2_VPlane->at(CandidateProtonTrackIndex),
								Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateProtonTrackIndex));

			if (CandidateProtonTrackStartContainment == true && CandidateProtonTrackEndContainment == true) {

				CandidateProtonTrack_KE_MeV = sProtonRange2T->Eval(CandidateProtonTrackLength); // MeV
				CandidateProtonTrack_KE_GeV = CandidateProtonTrack_KE_MeV / 1000.; // GeV
				CandidateProtonTrack_Momentum_MCS_MeV = tools.KEToP(ProtonPdg,CandidateProtonTrack_KE_MeV); // MeV/c
				CandidateProtonTrack_Momentum_MCS_GeV = CandidateProtonTrack_Momentum_MCS_MeV / 1000.; // GeV/c
				CandidateProtonTrack_E_GeV = CandidateProtonTrack_KE_GeV + ProtonMass_GeV; // GeV/c

			} else {

				CandidateProtonTrack_Momentum_MCS_GeV = Track_Momentum_MCS->at(CandidateProtonTrackIndex); // GeV/c
				CandidateProtonTrack_Momentum_MCS_MeV = 1000. * CandidateProtonTrack_Momentum_MCS_GeV; // MeV/c
				CandidateProtonTrack_KE_MeV = tools.PToKE(ProtonPdg,CandidateProtonTrack_Momentum_MCS_MeV); // MeV/c
				CandidateProtonTrack_KE_GeV = CandidateProtonTrack_KE_MeV / 1000.; // GeV/c
				CandidateProtonTrack_E_GeV = CandidateProtonTrack_KE_GeV + ProtonMass_GeV; // GeV/c

			}

			CandidateP_P.push_back(CandidateProtonTrack_Momentum_MCS_GeV);
			CandidateP_Phi.push_back(Track_Phi->at(CandidateProtonTrackIndex) * 180./ TMath::Pi()); // deg
			CandidateP_CosTheta.push_back(CandidateProtonTrackCosTheta);
			CandidateP_Chi2_YPlane.push_back(Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateProtonTrackIndex));
			CandidateP_ThreePlaneLogLikelihood.push_back(Track_ParticleId_ProtonScore_ThreePlanePID->at(CandidateProtonTrackIndex));
			CandidateP_ThreePlaneChi2.push_back(CalCandidateP_ThreePlaneChi2);
			CandidateP_StartContainment.push_back(CandidateProtonTrackStartContainment);
			CandidateP_EndContainment.push_back(CandidateProtonTrackEndContainment);

			// ------------------------------------------------------------------------------------------------------------------------------------------
			// ------------------------------------------------------------------------------------------------------------------------------------------

			if (string(fWhichSample).find("Overlay") != std::string::npos) {

				CandidateMu_MCParticle_Pdg.push_back(Track_MCParticle_PdgCode->at(CandidateMuonTrackIndex));
				CandidateMu_MCParticle_Purity.push_back(Track_MCParticle_Purity->at(CandidateMuonTrackIndex));
				CandidateMu_Mode.push_back(Track_MCParticle_Mode->at(CandidateMuonTrackIndex));

				TVector3 TrueCandidateMuonTrackStart(Track_MCParticle_Vx->at(CandidateMuonTrackIndex), Track_MCParticle_Vy->at(CandidateMuonTrackIndex),
														       Track_MCParticle_Vz->at(CandidateMuonTrackIndex));
				TVector3 TrueCandidateMuonTrackEnd(Track_MCParticle_EndX->at(CandidateMuonTrackIndex), Track_MCParticle_EndY->at(CandidateMuonTrackIndex),
														       Track_MCParticle_EndZ->at(CandidateMuonTrackIndex));
				TVector3 TrueCandidateMuonChange = TrueCandidateMuonTrackEnd - TrueCandidateMuonTrackStart;
				bool TrueCandidateMuonTrackStartContainment = tools.inFVVector(TrueCandidateMuonTrackStart);
				bool TrueCandidateMuonTrackEndContainment = tools.inFVVector(TrueCandidateMuonTrackEnd);

				double TrueCandidateMuonTrackPhi = TrueCandidateMuonChange.Phi(); // rad
				double TrueCandidateMuonTrackPhi_Deg = TrueCandidateMuonTrackPhi * 180./ TMath::Pi(); // deg
				double TrueCandidateMuonTrackTheta = TrueCandidateMuonChange.Theta(); // rad
				double TrueCandidateMuonTrackCosTheta = cos(TrueCandidateMuonTrackTheta);
				double TrueCandidateMuonTrackLength = TrueCandidateMuonChange.Mag(); // cm
				double TrueCandidateMuonTrackMomentum_GeV = Track_MCParticle_P->at(CandidateMuonTrackIndex); // GeV
				double TrueCandidateMuonTrackMomentum_MeV = 1000.* TrueCandidateMuonTrackMomentum_GeV; // MeV
				double TrueCandidateMuonTrack_KE_MeV = tools.PToKE(MuonPdg,TrueCandidateMuonTrackMomentum_MeV); // MeV
				double TrueCandidateMuonTrack_KE_GeV = TrueCandidateMuonTrack_KE_MeV / 1000.; // GeV
				double TrueCandidateMuonTrack_E_GeV = TrueCandidateMuonTrack_KE_GeV + MuonMass_GeV; // GeV

				True_CandidateMu_P.push_back(TrueCandidateMuonTrackMomentum_GeV);
				True_CandidateMu_Phi.push_back(TrueCandidateMuonTrackPhi_Deg); // deg
				True_CandidateMu_CosTheta.push_back(TrueCandidateMuonTrackCosTheta);
				True_CandidateMu_StartContainment.push_back(TrueCandidateMuonTrackStartContainment);
				True_CandidateMu_EndContainment.push_back(TrueCandidateMuonTrackEndContainment);

				// ---------------------------------------------------------------------------------------------------------------------------------------------

				CandidateP_MCParticle_Pdg.push_back(Track_MCParticle_PdgCode->at(CandidateProtonTrackIndex));
				CandidateP_MCParticle_Purity.push_back(Track_MCParticle_Purity->at(CandidateProtonTrackIndex));
				CandidateP_Mode.push_back(Track_MCParticle_Mode->at(CandidateProtonTrackIndex));

				TVector3 TrueCandidateProtonTrackStart(Track_MCParticle_Vx->at(CandidateProtonTrackIndex), Track_MCParticle_Vy->at(CandidateProtonTrackIndex),
														       Track_MCParticle_Vz->at(CandidateProtonTrackIndex));
				TVector3 TrueCandidateProtonTrackEnd(Track_MCParticle_EndX->at(CandidateProtonTrackIndex), Track_MCParticle_EndY->at(CandidateProtonTrackIndex),
														       Track_MCParticle_EndZ->at(CandidateProtonTrackIndex));
				TVector3 TrueCandidateProtonChange = TrueCandidateProtonTrackEnd - TrueCandidateProtonTrackStart;
				bool TrueCandidateProtonTrackStartContainment = tools.inFVVector(TrueCandidateProtonTrackStart);
				bool TrueCandidateProtonTrackEndContainment = tools.inFVVector(TrueCandidateProtonTrackEnd);

				double TrueCandidateProtonTrackPhi = TrueCandidateProtonChange.Phi(); // rad
				double TrueCandidateProtonTrackPhi_Deg = TrueCandidateProtonTrackPhi * 180./ TMath::Pi(); // deg
				double TrueCandidateProtonTrackTheta = TrueCandidateProtonChange.Theta(); // rad
				double TrueCandidateProtonTrackCosTheta = cos(TrueCandidateProtonTrackTheta);
				double TrueCandidateProtonTrackLength = TrueCandidateProtonChange.Mag(); // cm
				double TrueCandidateProtonTrackMomentum_GeV = Track_MCParticle_P->at(CandidateProtonTrackIndex); // GeV
				double TrueCandidateProtonTrackMomentum_MeV = 1000.* TrueCandidateProtonTrackMomentum_GeV; // MeV
				double TrueCandidateProtonTrack_KE_MeV = tools.PToKE(ProtonPdg,TrueCandidateProtonTrackMomentum_MeV); // MeV
				double TrueCandidateProtonTrack_KE_GeV = TrueCandidateProtonTrack_KE_MeV / 1000.; // GeV
				double TrueCandidateProtonTrack_E_GeV = TrueCandidateProtonTrack_KE_GeV + ProtonMass_GeV; // GeV

				True_CandidateP_P.push_back(TrueCandidateProtonTrackMomentum_GeV);
				True_CandidateP_Phi.push_back(TrueCandidateProtonTrackPhi_Deg); // deg
				True_CandidateP_CosTheta.push_back(TrueCandidateProtonTrackCosTheta);
				True_CandidateP_StartContainment.push_back(TrueCandidateProtonTrackStartContainment);
				True_CandidateP_EndContainment.push_back(TrueCandidateProtonTrackEndContainment);


			} // only for overlays

			EventCounter++;

		} // End of the loop over the candidate track pairs

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		// MCParticle Loop

		int TrueMuonCounter = 0, TrueProtonCounter = 0, TrueChargedPionCounter = 0, TrueNeutralPionCounter = 0;
		int NMCParticles = MCParticle_PdgCode->size();

		for (int WhichMCParticle = 0; WhichMCParticle < NMCParticles; WhichMCParticle++) {

			// Demand stable final state particles

			if (MCParticle_StatusCode->at(WhichMCParticle) == 1) {

				TVector3 TVector3TrueStart(MCParticle_Vx->at(WhichMCParticle),MCParticle_Vy->at(WhichMCParticle),MCParticle_Vz->at(WhichMCParticle));
				TVector3 TVector3TrueEnd(MCParticle_EndX->at(WhichMCParticle), MCParticle_EndY->at(WhichMCParticle),MCParticle_EndZ->at(WhichMCParticle));
				bool TrueStartContainment = tools.inFVVector(TVector3TrueStart);

				if (TrueStartContainment == 1) {

					if (MCParticle_PdgCode->at(WhichMCParticle) == MuonPdg && MCParticle_P->at(WhichMCParticle) > ArrayNBinsMuonMomentum[0]) 
						{ TrueMuonCounter++; }

					if (MCParticle_PdgCode->at(WhichMCParticle) == ProtonPdg && MCParticle_P->at(WhichMCParticle) > ArrayNBinsProtonMomentum[0]) 
						{ TrueProtonCounter++; }

					if (fabs(MCParticle_PdgCode->at(WhichMCParticle)) == AbsChargedPionPdg && MCParticle_P->at(WhichMCParticle) > ChargedPionMomentumThres) 
						{ TrueChargedPionCounter++; }

				}

			} // End of the demand stable final state particles and primary interactions

		} // end of the loop over the simb::MCParticles

		// Signal definition: 1 mu (Pmu > 100 MeV / c), 1p (Pp > 200 MeV / c) & pi+/- (Ppi > 70 MeV / c)

		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 0) { fCC1p = 1; }

		if (MCTruth_Mode->size() == 1) { fMCParticle_Mode = MCTruth_Mode->at(0); }

		CC1p = fCC1p;
		MCParticle_Mode = fMCParticle_Mode;

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		tree->Fill();

	} // End of the loop over the number of events

	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// To be printed at the end of the run

	int precision = 2;

	std::cout.precision(precision);
	std::cout << "\n\nTotal of " << EventCounter << " events processed" << std::endl << std::endl;

	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	OutputFile->cd();
	OutputFile->Write();
	OutputFile->Close();
	fSpines->Close();
	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;

} // end of the program

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

double ThreePlaneChi2(TVector3 TrackStart,TVector3 TrackEnd,double Chi2_Plane0,double Chi2_Plane1,double Chi2_Plane2){

	TVector3 TrackDiff = TrackEnd - TrackStart;
	double theta_Plane2 = std::atan2(TrackDiff.Z(),TrackDiff.Y());
	double theta_Plane1 = theta_Plane2 + TMath::Pi();
	double theta_Plane0 = theta_Plane2 - TMath::Pi();

	int w2 = 0; int w1 = 0; int w0 = 0;
	double sin2_pl2 = sin(theta_Plane2) * sin(theta_Plane2);
	double sin2_pl1 = sin(theta_Plane1) * sin(theta_Plane1);
	double sin2_pl0 = sin(theta_Plane0) * sin(theta_Plane0);

	if (sin2_pl2 >= 0.5) w2 = 1;
	if (sin2_pl1 >= 0.5) w1 = 1;
	if (sin2_pl0 >= 0.5) w0 = 1;

	double PID_Chi2P_3pl = -1.;
	int ww0 = w0; int ww1 = w1; int ww2 = w2; // copy from the origin
	if (Chi2_Plane0 < 0) ww0 = 0;
	if (Chi2_Plane1 < 0) ww1 = 0;
	if (Chi2_Plane2 < 0) ww2 = 0;
	if (ww0 + ww1 + ww2 == 0) PID_Chi2P_3pl = -999;
	else PID_Chi2P_3pl = (ww0 * Chi2_Plane0 + ww1 * Chi2_Plane0 + ww2 * Chi2_Plane0) / (ww0 + ww1 + ww2);

	return PID_Chi2P_3pl;

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
