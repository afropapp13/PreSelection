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

#include "ubana/MyClasses/TrackVertexSorting.h"
#include "ubana/MyClasses/Tools.h"
#include "ubana/MyClasses/SelectionCuts.h"
#include "ubana/MyClasses/Constants.h"

using namespace std;
using namespace Constants;

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

	TString FileName = "./OutputFiles/"+UBCodeVersion+"/PreSelection_"+WhichSample+"_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// TTree

	TTree* tree = new TTree("myPreSelection","myPreSelection");

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//	int PassedSwTrigger;
	double Weight;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int NBeamFlashes;
	std::vector<double> BeamFlashes_YCenter;
	std::vector<double> BeamFlashes_ZCenter;
	std::vector<double> BeamFlashes_TotalPE;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//	int NumberMCParticles;

//	std::vector<int> MCParticle_Mode;
//	std::vector<double> MCParticle_Mom;
////	std::vector<double> MCParticle_KE;
//	std::vector<double> MCParticle_Phi;
//	std::vector<double> MCParticle_CosTheta;
////	std::vector<double> MCParticle_Length;
////	std::vector<double> MCParticle_StartX;
////	std::vector<double> MCParticle_StartY;
////	std::vector<double> MCParticle_StartZ;
////	std::vector<double> MCParticle_EndPointX;
////	std::vector<double> MCParticle_EndPointY;
////	std::vector<double> MCParticle_EndPointZ;
//	std::vector<int> MCParticle_StartContainment;
//	std::vector<int> MCParticle_EndContainment;
//	std::vector<int> MCParticle_Pdg;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<double> CandidateMuP_Distance;
	std::vector<double> Vertex_X;
	std::vector<double> Vertex_Y;
	std::vector<double> Vertex_Z;

	std::vector<int> CandidateMu_Mode;
	std::vector<double> CandidateMu_P;
//	std::vector<double> CandidateMu_KE;
//	std::vector<double> CandidateMu_E;
	std::vector<double> CandidateMu_Phi;
	std::vector<double> CandidateMu_CosTheta;
//	std::vector<double> CandidateMu_Length;
	std::vector<double> CandidateMu_Chi2_YPlane;
	std::vector<double> CandidateMu_ThreePlaneChi2;
//	std::vector<double> CandidateMu_StartX;
//	std::vector<double> CandidateMu_StartY;
//	std::vector<double> CandidateMu_StartZ;
//	std::vector<double> CandidateMu_EndX;
//	std::vector<double> CandidateMu_EndY;
//	std::vector<double> CandidateMu_EndZ;
	std::vector<int> CandidateMu_StartContainment;
	std::vector<int> CandidateMu_EndContainment;
	std::vector<int> CandidateMu_MCParticle_Pdg;
	std::vector<double> CandidateMu_MCParticle_Purity;

	std::vector<double> True_CandidateMu_P;
//	std::vector<double> True_CandidateMu_KE;
//	std::vector<double> True_CandidateMu_E;
	std::vector<double> True_CandidateMu_Phi;
	std::vector<double> True_CandidateMu_CosTheta;
//	std::vector<double> True_CandidateMu_Length;
//	std::vector<double> True_CandidateMu_StartX;
//	std::vector<double> True_CandidateMu_StartY;
//	std::vector<double> True_CandidateMu_StartZ;
//	std::vector<double> True_CandidateMu_EndX;
//	std::vector<double> True_CandidateMu_EndY;
//	std::vector<double> True_CandidateMu_EndZ;
	std::vector<int> True_CandidateMu_StartContainment;
	std::vector<int> True_CandidateMu_EndContainment;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<int> CandidateP_Mode;
	std::vector<double> CandidateP_P;
//	std::vector<double> CandidateP_KE;
//	std::vector<double> CandidateP_E;
	std::vector<double> CandidateP_Phi;
	std::vector<double> CandidateP_CosTheta;
//	std::vector<double> CandidateP_Length;
	std::vector<double> CandidateP_Chi2_YPlane;
	std::vector<double> CandidateP_ThreePlaneChi2;
//	std::vector<double> CandidateP_StartX;
//	std::vector<double> CandidateP_StartY;
//	std::vector<double> CandidateP_StartZ;
//	std::vector<double> CandidateP_EndX;
//	std::vector<double> CandidateP_EndY;
//	std::vector<double> CandidateP_EndZ;
	std::vector<int> CandidateP_StartContainment;
	std::vector<int> CandidateP_EndContainment;
	std::vector<int> CandidateP_MCParticle_Pdg;
	std::vector<double> CandidateP_MCParticle_Purity;

	std::vector<double> True_CandidateP_P;
//	std::vector<double> True_CandidateP_KE;
//	std::vector<double> True_CandidateP_E;
	std::vector<double> True_CandidateP_Phi;
	std::vector<double> True_CandidateP_CosTheta;
//	std::vector<double> True_CandidateP_Length;
//	std::vector<double> True_CandidateP_StartX;
//	std::vector<double> True_CandidateP_StartY;
//	std::vector<double> True_CandidateP_StartZ;
//	std::vector<double> True_CandidateP_EndX;
//	std::vector<double> True_CandidateP_EndY;
//	std::vector<double> True_CandidateP_EndZ;
	std::vector<int> True_CandidateP_StartContainment;
	std::vector<int> True_CandidateP_EndContainment;

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//	tree->Branch("PassedSwTrigger",&PassedSwTrigger);
	tree->Branch("Weight",&Weight);

	tree->Branch("NBeamFlashes",&NBeamFlashes);
	tree->Branch("BeamFlashes_YCenter",&BeamFlashes_YCenter);
	tree->Branch("BeamFlashes_ZCenter",&BeamFlashes_ZCenter);
	tree->Branch("BeamFlashes_TotalPE",&BeamFlashes_TotalPE);

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//	tree->Branch("NumberMCParticles",&NumberMCParticles);
//	tree->Branch("MCParticle_Mode",&MCParticle_Mode);
//	tree->Branch("MCParticle_Mom",&MCParticle_Mom);
////	tree->Branch("MCParticle_KE",&MCParticle_KE);
//	tree->Branch("MCParticle_Phi",&MCParticle_Phi);
//	tree->Branch("MCParticle_CosTheta",&MCParticle_CosTheta);
////	tree->Branch("MCParticle_Length",&MCParticle_Length);
////	tree->Branch("MCParticle_StartX",&MCParticle_StartX);
////	tree->Branch("MCParticle_StartY",&MCParticle_StartY);
////	tree->Branch("MCParticle_StartZ",&MCParticle_StartZ);
////	tree->Branch("MCParticle_EndPointX",&MCParticle_EndPointX);
////	tree->Branch("MCParticle_EndPointY",&MCParticle_EndPointY);
////	tree->Branch("MCParticle_EndPointZ",&MCParticle_EndPointZ);
//	tree->Branch("MCParticle_StartContainment",&MCParticle_StartContainment);
//	tree->Branch("MCParticle_EndContainment",&MCParticle_EndContainment);
//	tree->Branch("MCParticle_Pdg",&MCParticle_Pdg);

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("CandidateMuP_Distance",&CandidateMuP_Distance);
	tree->Branch("Vertex_X",&Vertex_X);
	tree->Branch("Vertex_Y",&Vertex_Y);
	tree->Branch("Vertex_Z",&Vertex_Z);

	tree->Branch("CandidateMu_P",&CandidateMu_P);
//	tree->Branch("CandidateMu_KE",&CandidateMu_KE);
//	tree->Branch("CandidateMu_E",&CandidateMu_E);
	tree->Branch("CandidateMu_Phi",&CandidateMu_Phi);
	tree->Branch("CandidateMu_CosTheta",&CandidateMu_CosTheta);
//	tree->Branch("CandidateMu_Length",&CandidateMu_Length);
	tree->Branch("CandidateMu_Chi2_YPlane",&CandidateMu_Chi2_YPlane);
	tree->Branch("CandidateMu_ThreePlaneChi2",&CandidateMu_ThreePlaneChi2);
//	tree->Branch("CandidateMu_StartX",&CandidateMu_StartX);
//	tree->Branch("CandidateMu_StartY",&CandidateMu_StartY);
//	tree->Branch("CandidateMu_StartZ",&CandidateMu_StartZ);
//	tree->Branch("CandidateMu_EndX",&CandidateMu_EndX);
//	tree->Branch("CandidateMu_EndY",&CandidateMu_EndY);
//	tree->Branch("CandidateMu_EndZ",&CandidateMu_EndZ);
	tree->Branch("CandidateMu_StartContainment",&CandidateMu_StartContainment);
	tree->Branch("CandidateMu_EndContainment",&CandidateMu_EndContainment);
	tree->Branch("CandidateMu_MCParticle_Pdg",&CandidateMu_MCParticle_Pdg);
	tree->Branch("CandidateMu_MCParticle_Purity",&CandidateMu_MCParticle_Purity);

	tree->Branch("True_CandidateMu_P",&True_CandidateMu_P);
//	tree->Branch("True_CandidateMu_KE",&True_CandidateMu_KE);
//	tree->Branch("True_CandidateMu_E",&True_CandidateMu_E);
	tree->Branch("True_CandidateMu_Phi",&True_CandidateMu_Phi);
	tree->Branch("True_CandidateMu_CosTheta",&True_CandidateMu_CosTheta);
//	tree->Branch("True_CandidateMu_Length",&True_CandidateMu_Length);
//	tree->Branch("True_CandidateMu_StartX",&True_CandidateMu_StartX);
//	tree->Branch("True_CandidateMu_StartY",&True_CandidateMu_StartY);
//	tree->Branch("True_CandidateMu_StartZ",&True_CandidateMu_StartZ);
//	tree->Branch("True_CandidateMu_EndX",&True_CandidateMu_EndX);
//	tree->Branch("True_CandidateMu_EndY",&True_CandidateMu_EndY);
//	tree->Branch("True_CandidateMu_EndZ",&True_CandidateMu_EndZ);
	tree->Branch("True_CandidateMu_StartContainment",&True_CandidateMu_StartContainment);
	tree->Branch("True_CandidateMu_EndContainment",&True_CandidateMu_EndContainment);

	// -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("CandidateP_P",&CandidateP_P);
//	tree->Branch("CandidateP_KE",&CandidateP_KE);
//	tree->Branch("CandidateP_E",&CandidateP_E);
	tree->Branch("CandidateP_Phi",&CandidateP_Phi);
	tree->Branch("CandidateP_CosTheta",&CandidateP_CosTheta);
//	tree->Branch("CandidateP_Length",&CandidateP_Length);
	tree->Branch("CandidateP_Chi2_YPlane",&CandidateP_Chi2_YPlane);
	tree->Branch("CandidateP_ThreePlaneChi2",&CandidateP_ThreePlaneChi2);
//	tree->Branch("CandidateP_StartX",&CandidateP_StartX);
//	tree->Branch("CandidateP_StartY",&CandidateP_StartY);
//	tree->Branch("CandidateP_StartZ",&CandidateP_StartZ);
//	tree->Branch("CandidateP_EndX",&CandidateP_EndX);
//	tree->Branch("CandidateP_EndY",&CandidateP_EndY);
//	tree->Branch("CandidateP_EndZ",&CandidateP_EndZ);
	tree->Branch("CandidateP_StartContainment",&CandidateP_StartContainment);
	tree->Branch("CandidateP_EndContainment",&CandidateP_EndContainment);
	tree->Branch("CandidateP_MCParticle_Pdg",&CandidateP_MCParticle_Pdg);
	tree->Branch("CandidateP_MCParticle_Purity",&CandidateP_MCParticle_Purity);

	tree->Branch("True_CandidateP_P",&True_CandidateP_P);
//	tree->Branch("True_CandidateP_KE",&True_CandidateP_KE);
//	tree->Branch("True_CandidateP_E",&True_CandidateP_E);
	tree->Branch("True_CandidateP_Phi",&True_CandidateP_Phi);
	tree->Branch("True_CandidateP_CosTheta",&True_CandidateP_CosTheta);
//	tree->Branch("True_CandidateP_Length",&True_CandidateP_Length);
//	tree->Branch("True_CandidateP_StartX",&True_CandidateP_StartX);
//	tree->Branch("True_CandidateP_StartY",&True_CandidateP_StartY);
//	tree->Branch("True_CandidateP_StartZ",&True_CandidateP_StartZ);
//	tree->Branch("True_CandidateP_EndX",&True_CandidateP_EndX);
//	tree->Branch("True_CandidateP_EndY",&True_CandidateP_EndY);
//	tree->Branch("True_CandidateP_EndZ",&True_CandidateP_EndZ);
	tree->Branch("True_CandidateP_StartContainment",&True_CandidateP_StartContainment);
	tree->Branch("True_CandidateP_EndContainment",&True_CandidateP_EndContainment);

	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	Tools tools;

	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	// Event Counters

	int EventCounter = 0;

	// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {
//	for (Long64_t jentry=0; jentry<1002;jentry++) {
//	for (Long64_t jentry=0; jentry<3002;jentry++) {
//	for (Long64_t jentry=0; jentry<10002;jentry++) {

		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;
		Long64_t ientry = LoadTree(jentry); if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;

		// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//		double weight = 1.;
		double weight = EventWeight->at(0);
		Weight = weight;

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

//		PassedSwTrigger = EventPassedSwTrigger;
		if ( EventPassedSwTrigger != 1) { continue; }

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		// Numu Slices

		if (NumberNuMuPFParticles != 1) { continue; }

		int NNuMuDaughters = PFParticle_NumberNuMuDaughters->at(0);
		if (NNuMuDaughters != 2) { continue; }
		// MuonPdg in this case / Pandora = Track-like object
		if (PFParticle_NumberNuMuDaughtersPdgCode->at(0).at(0) != MuonPdg || PFParticle_NumberNuMuDaughtersPdgCode->at(0).at(0) != MuonPdg) { continue; }
		if (TracksFromCurrentPFParticleStartX->at(0).at(0) == -99. || TracksFromCurrentPFParticleStartX->at(0).at(1) == -99.) { continue; }

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

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		// Tracks

		VectorTrackStart.clear();
		VectorTrackEnd.clear();

		std::vector<int> FirstTrackIndex; FirstTrackIndex.clear();
		std::vector<int> SecondTrackIndex; SecondTrackIndex.clear();
		std::vector<double> TrackPairDistance; TrackPairDistance.clear();
		std::vector<TVector3> TrackPairVertexPosition; TrackPairVertexPosition.clear();

		for (int WhichTrack = 0; WhichTrack < NumberTracks; WhichTrack++) {

//			// Make sure that we have non-zero length tracks by demanding a min length of 0.3 cm (distance between wires)

//			if (Track_Length->at(WhichTrack) > UBSpaceReso) {

//				TVector3 TVector3TrackStart(Track_StartX->at(WhichTrack),Track_StartY->at(WhichTrack),Track_StartZ->at(WhichTrack));
//				TVector3 TVector3TrackEnd(Track_EndX->at(WhichTrack),Track_EndY->at(WhichTrack),Track_EndZ->at(WhichTrack));

//				VectorTrackStart.push_back(TVector3TrackStart);
//				VectorTrackEnd.push_back(TVector3TrackEnd);

//			}

			if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(0) || Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(1)) {

				TVector3 TVector3TrackStart(Track_StartX->at(WhichTrack),Track_StartY->at(WhichTrack),Track_StartZ->at(WhichTrack));
				TVector3 TVector3TrackEnd(Track_EndX->at(WhichTrack),Track_EndY->at(WhichTrack),Track_EndZ->at(WhichTrack));

				VectorTrackStart.push_back(TVector3TrackStart);
				VectorTrackEnd.push_back(TVector3TrackEnd);

				if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(0) ) { FirstTrackIndex.push_back(WhichTrack); }
				if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(1) ) { SecondTrackIndex.push_back(WhichTrack); }

			}
			
		} // end of the loop over the recob::Tracks

		int NCandidateTrackPairs = VectorTrackStart.size() / 2;
		if (NCandidateTrackPairs == 0) { continue; }


double fTrackPairDistance = (VectorTrackStart.at(0) - VectorTrackStart.at(1)).Mag();
TrackPairDistance.push_back(fTrackPairDistance);


TVector3 VertexPositionV3 = (VectorTrackStart.at(0) + VectorTrackStart.at(1))*0.5;
TrackPairVertexPosition.push_back(VertexPositionV3);

		// Get the candidate track pairs

//		TrackVertexSorting recob_trackvertexsorting; 
//		recob_trackvertexsorting.CandidateTrackPairs(VectorTrackStart,VectorTrackEnd);

//		std::vector<int> FirstTrackIndex = recob_trackvertexsorting.ReturnFirstTrackVector();
//		std::vector<int> SecondTrackIndex = recob_trackvertexsorting.ReturnSecondTrackVector();
//		std::vector<double> TrackPairDistance = recob_trackvertexsorting.ReturnTrackPairDistance();
//		std::vector<TVector3> TrackPairVertexPosition = recob_trackvertexsorting.ReturnVertexPosition();

//		int NCandidateTrackPairs = FirstTrackIndex.size();
//		int NCandidateTrackPairs = VectorTrackStart.size();
//std::cout << "NCandidateTrackPairs = " << NCandidateTrackPairs << std::endl;
		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		// Loop over the candidate track pairs

		CandidateMuP_Distance.clear();
		Vertex_X.clear();
		Vertex_Y.clear();
		Vertex_Z.clear();

		CandidateMu_Mode.clear();
		CandidateMu_P.clear();
//		CandidateMu_KE.clear();
//		CandidateMu_E.clear();
		CandidateMu_Phi.clear();
		CandidateMu_CosTheta.clear();
//		CandidateMu_Length.clear();
		CandidateMu_Chi2_YPlane.clear();
		CandidateMu_ThreePlaneChi2.clear();
//		CandidateMu_StartX.clear();
//		CandidateMu_StartY.clear();
//		CandidateMu_StartZ.clear();
//		CandidateMu_EndX.clear();
//		CandidateMu_EndY.clear();
//		CandidateMu_EndZ.clear();
		CandidateMu_StartContainment.clear();
		CandidateMu_EndContainment.clear();
		CandidateMu_MCParticle_Pdg.clear();
		CandidateMu_MCParticle_Purity.clear();

		True_CandidateMu_P.clear();
//		True_CandidateMu_KE.clear();
//		True_CandidateMu_E.clear();
		True_CandidateMu_Phi.clear();
		True_CandidateMu_CosTheta.clear();
//		True_CandidateMu_Length.clear();
//		True_CandidateMu_StartX.clear();
//		True_CandidateMu_StartY.clear();
//		True_CandidateMu_StartZ.clear();
//		True_CandidateMu_EndX.clear();
//		True_CandidateMu_EndY.clear();
//		True_CandidateMu_EndZ.clear();
		True_CandidateMu_StartContainment.clear();
		True_CandidateMu_EndContainment.clear();

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		CandidateP_Mode.clear();
		CandidateP_P.clear();
//		CandidateP_KE.clear();
//		CandidateP_E.clear();
		CandidateP_Phi.clear();
		CandidateP_CosTheta.clear();
//		CandidateP_Length.clear();
		CandidateP_Chi2_YPlane.clear();
		CandidateP_ThreePlaneChi2.clear();
//		CandidateP_StartX.clear();
//		CandidateP_StartY.clear();
//		CandidateP_StartZ.clear();
//		CandidateP_EndX.clear();
//		CandidateP_EndY.clear();
//		CandidateP_EndZ.clear();
		CandidateP_StartContainment.clear();
		CandidateP_EndContainment.clear();
		CandidateP_MCParticle_Pdg.clear();
		CandidateP_MCParticle_Purity.clear();

		True_CandidateP_P.clear();
//		True_CandidateP_KE.clear();
//		True_CandidateP_E.clear();
		True_CandidateP_Phi.clear();
		True_CandidateP_CosTheta.clear();
//		True_CandidateP_Length.clear();
//		True_CandidateP_StartX.clear();
//		True_CandidateP_StartY.clear();
//		True_CandidateP_StartZ.clear();
//		True_CandidateP_EndX.clear();
//		True_CandidateP_EndY.clear();
//		True_CandidateP_EndZ.clear();
		True_CandidateP_StartContainment.clear();
		True_CandidateP_EndContainment.clear();

		// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

		for (int WhichTrackPair = 0; WhichTrackPair < NCandidateTrackPairs; WhichTrackPair++) {

			CandidateMuP_Distance.push_back(TrackPairDistance.at(WhichTrackPair));	
			Vertex_X.push_back(TrackPairVertexPosition.at(WhichTrackPair).X());
			Vertex_Y.push_back(TrackPairVertexPosition.at(WhichTrackPair).Y());
			Vertex_Z.push_back(TrackPairVertexPosition.at(WhichTrackPair).Z());

			// Track indices

			int FirstCandidateTrackIndex = FirstTrackIndex.at(WhichTrackPair);
			int SecondCandidateTrackIndex = SecondTrackIndex.at(WhichTrackPair);
//std::cout << "FirstCandidateTrackIndex = " << FirstCandidateTrackIndex << "  SecondCandidateTrackIndex = " << SecondCandidateTrackIndex << std::endl;
			// Get the muon & proton candidates

			int CandidateMuonTrackIndex = Track_Length->at(FirstCandidateTrackIndex) > Track_Length->at(SecondCandidateTrackIndex)? FirstCandidateTrackIndex :  SecondCandidateTrackIndex;
			int CandidateProtonTrackIndex = Track_Length->at(FirstCandidateTrackIndex) > Track_Length->at(SecondCandidateTrackIndex)? SecondCandidateTrackIndex :  FirstCandidateTrackIndex;
//std::cout << "CandidateMuonTrackIndex = " << CandidateMuonTrackIndex << "  CandidateProtonTrackIndex = " << CandidateProtonTrackIndex << std::endl;
			// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

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

			// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

			// Track-PFParticle Associations

//			if (  !(fabs(CandidateMuonTrackStart.X() - TracksFromCurrentPFParticleStartX->at(0).at(0)) < MaxPFParticleTrackDistance || 
//				fabs(CandidateMuonTrackStart.X() - TracksFromCurrentPFParticleStartX->at(0).at(1)) < MaxPFParticleTrackDistance) ) { continue; }

//			if (  !(fabs(CandidateProtonTrackStart.X() - TracksFromCurrentPFParticleStartX->at(0).at(0)) < MaxPFParticleTrackDistance || 
//				fabs(CandidateProtonTrackStart.X() - TracksFromCurrentPFParticleStartX->at(0).at(1)) < MaxPFParticleTrackDistance) ) { continue; }

			// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

			// Muon

			double CandidateMuonTrack_Momentum_MCS_GeV = -99.;
			double CandidateMuonTrack_Momentum_MCS_MeV = -99.;
			double CandidateMuonTrack_KE_MeV = -99.;
			double CandidateMuonTrack_KE_GeV = -99.;
			double CandidateMuonTrack_E_GeV = -99.;

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
//			CandidateMu_KE.push_back(CandidateMuonTrack_KE_GeV);
//			CandidateMu_E.push_back(CandidateMuonTrack_E_GeV);
			CandidateMu_Phi.push_back(Track_Phi->at(CandidateMuonTrackIndex) * 180./ TMath::Pi()); // deg
			CandidateMu_CosTheta.push_back(CandidateMuonTrackCosTheta);
//			CandidateMu_Length.push_back(Track_Length->at(CandidateMuonTrackIndex)); // cm
			CandidateMu_Chi2_YPlane.push_back(Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateMuonTrackIndex));
			CandidateMu_ThreePlaneChi2.push_back(Track_ParticleId_ProtonScore_ThreePlanePID->at(CandidateMuonTrackIndex));
//			CandidateMu_StartX.push_back(CandidateMuonTrackStart.X());
//			CandidateMu_StartY.push_back(CandidateMuonTrackStart.Y());
//			CandidateMu_StartZ.push_back(CandidateMuonTrackStart.Z());
//			CandidateMu_EndX.push_back(CandidateMuonTrackEnd.X());
//			CandidateMu_EndY.push_back(CandidateMuonTrackEnd.Y());
//			CandidateMu_EndZ.push_back(CandidateMuonTrackEnd.Z());
			CandidateMu_StartContainment.push_back(CandidateMuonTrackStartContainment);
			CandidateMu_EndContainment.push_back(CandidateMuonTrackEndContainment);

			// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

			// Proton

			double CandidateProtonTrack_Momentum_MCS_GeV = -99.;
			double CandidateProtonTrack_Momentum_MCS_MeV = -99.;
			double CandidateProtonTrack_KE_MeV = -99.;
			double CandidateProtonTrack_KE_GeV = -99.;
			double CandidateProtonTrack_E_GeV = -99.;

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
//			CandidateP_KE.push_back(CandidateProtonTrack_KE_GeV);
//			CandidateP_E.push_back(CandidateProtonTrack_E_GeV);
			CandidateP_Phi.push_back(Track_Phi->at(CandidateProtonTrackIndex) * 180./ TMath::Pi()); // deg
			CandidateP_CosTheta.push_back(CandidateProtonTrackCosTheta);
//			CandidateP_Length.push_back(Track_Length->at(CandidateProtonTrackIndex)); // cm
			CandidateP_Chi2_YPlane.push_back(Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateProtonTrackIndex));
			CandidateP_ThreePlaneChi2.push_back(Track_ParticleId_ProtonScore_ThreePlanePID->at(CandidateProtonTrackIndex));
//			CandidateP_StartX.push_back(CandidateProtonTrackStart.X());
//			CandidateP_StartY.push_back(CandidateProtonTrackStart.Y());
//			CandidateP_StartZ.push_back(CandidateProtonTrackStart.Z());
//			CandidateP_EndX.push_back(CandidateProtonTrackEnd.X());
//			CandidateP_EndY.push_back(CandidateProtonTrackEnd.Y());
//			CandidateP_EndZ.push_back(CandidateProtonTrackEnd.Z());
			CandidateP_StartContainment.push_back(CandidateProtonTrackStartContainment);
			CandidateP_EndContainment.push_back(CandidateProtonTrackEndContainment);

			// -----------------------------------------------------------------------------------------------------------------------------------------------------------------
			// -----------------------------------------------------------------------------------------------------------------------------------------------------------------

			if (WhichSample == "Overlay9")	{

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
//				True_CandidateMu_KE.push_back(TrueCandidateMuonTrack_KE_GeV);
//				True_CandidateMu_E.push_back(TrueCandidateMuonTrack_E_GeV);
				True_CandidateMu_Phi.push_back(TrueCandidateMuonTrackPhi_Deg); // deg
				True_CandidateMu_CosTheta.push_back(TrueCandidateMuonTrackCosTheta);
//				True_CandidateMu_Length.push_back(TrueCandidateMuonTrackLength); // cm
//				True_CandidateMu_StartX.push_back(TrueCandidateMuonTrackStart.X());
//				True_CandidateMu_StartY.push_back(TrueCandidateMuonTrackStart.Y());
//				True_CandidateMu_StartZ.push_back(TrueCandidateMuonTrackStart.Z());
//				True_CandidateMu_EndX.push_back(TrueCandidateMuonTrackEnd.X());
//				True_CandidateMu_EndY.push_back(TrueCandidateMuonTrackEnd.Y());
//				True_CandidateMu_EndZ.push_back(TrueCandidateMuonTrackEnd.Z());
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
//				True_CandidateP_KE.push_back(TrueCandidateProtonTrack_KE_GeV);
//				True_CandidateP_E.push_back(TrueCandidateProtonTrack_E_GeV);
				True_CandidateP_Phi.push_back(TrueCandidateProtonTrackPhi_Deg); // deg
				True_CandidateP_CosTheta.push_back(TrueCandidateProtonTrackCosTheta);
//				True_CandidateP_Length.push_back(TrueCandidateProtonTrackLength); // cm
//				True_CandidateP_StartX.push_back(TrueCandidateProtonTrackStart.X());
//				True_CandidateP_StartY.push_back(TrueCandidateProtonTrackStart.Y());
//				True_CandidateP_StartZ.push_back(TrueCandidateProtonTrackStart.Z());
//				True_CandidateP_EndX.push_back(TrueCandidateProtonTrackEnd.X());
//				True_CandidateP_EndY.push_back(TrueCandidateProtonTrackEnd.Y());
//				True_CandidateP_EndZ.push_back(TrueCandidateProtonTrackEnd.Z());
				True_CandidateP_StartContainment.push_back(TrueCandidateProtonTrackStartContainment);
				True_CandidateP_EndContainment.push_back(TrueCandidateProtonTrackEndContainment);


			} // only for overlays

		EventCounter++;

		} // End of the loop over the candidate track pairs

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

//________________________________________________________________________________________________________________________________________________________________________________________________

