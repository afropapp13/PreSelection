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

#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/STV_Tools.h"

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

	// -------------------------------------------------------------------------------------------------------------------------------------

	// Momentum from range

	TFile *fSpines = TFile::Open("Proton_Muon_Range_dEdx_LAr_TSplines.root","READ");
	TSpline3* sMuonRange2T = (TSpline3*)fSpines->Get("sMuonRange2T");
	TSpline3* sProtonRange2T = (TSpline3*)fSpines->Get("sProtonRange2T");

	// ---------------------------------------------------------------------------------------------------------------------------------------

	// Output Files

	TString FileName = "/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_"+fWhichSample+"_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

	// ----------------------------------------------------------------------------------------------------------------------------------------

	// TTree

	TTree* tree = new TTree("myPreSelection","myPreSelection");

	// -----------------------------------------------------------------------------------------------------------------------------------------

//	int PassedSwTrigger;
	double Weight;
	double T2KWeight;
	double ROOTinoWeight;

	std::vector<double> All_UBGenie;
	std::vector<double> AxFFCCQEshape_UBGenie;
	std::vector<double> DecayAngMEC_UBGenie;
	std::vector<double> NormCCCOH_UBGenie;
	std::vector<double> NormNCCOH_UBGenie;
//	std::vector<double> RPA_CCQE_Reduced_UBGenie;
	std::vector<double> RPA_CCQE_UBGenie;
	std::vector<double> ThetaDelta2NRad_UBGenie;
	std::vector<double> Theta_Delta2Npi_UBGenie;
	std::vector<double> VecFFCCQEshape_UBGenie;
	std::vector<double> XSecShape_CCMEC_UBGenie;
	std::vector<double> expskin_FluxUnisim;
	std::vector<double> horncurrent_FluxUnisim;
	std::vector<double> kminus_PrimaryHadronNormalization;
	std::vector<double> kplus_PrimaryHadronFeynmanScaling;
	std::vector<double> kzero_PrimaryHadronSanfordWang;
	std::vector<double> nucleoninexsec_FluxUnisim;
	std::vector<double> nucleonqexsec_FluxUnisim;
	std::vector<double> nucleontotxsec_FluxUnisim;
	std::vector<double> piminus_PrimaryHadronSWCentralSplineVariation;
	std::vector<double> pioninexsec_FluxUnisim;
	std::vector<double> pionqexsec_FluxUnisim;
	std::vector<double> piontotxsec_FluxUnisim;
	std::vector<double> piplus_PrimaryHadronSWCentralSplineVariation;
	std::vector<double> reinteractions_piminus_Geant4;
	std::vector<double> reinteractions_piplus_Geant4;
	std::vector<double> reinteractions_proton_Geant4;
//	std::vector<double> xsr_scc_Fa3_SCC;
//	std::vector<double> xsr_scc_Fv3_SCC;
	
	int CC1p;
	int CC1p1pi;
	int CC2p;
	int CC2p1pi;
	int CC3p;
	int CC3p1pi;
	int CC3p2pi;
	int MCParticle_Mode;

	// -------------------------------------------------------------------------------------------------------------------------------------------

	double NuScore;
	double FlashScore; 

	// ------------------------------------------------------------------------------------------------------------------------------------------

	int NBeamFlashes;
	std::vector<double> BeamFlashes_YCenter;
	std::vector<double> BeamFlashes_ZCenter;
	std::vector<double> BeamFlashes_TotalPE;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<double> CandidateMuP_Distance;
	std::vector<double> Vertex_X;
	std::vector<double> Vertex_Y;
	std::vector<double> Vertex_Z;

//	std::vector<int> CandidateMu_Mode;			
	std::vector<double> CandidateMu_P_Range;
	std::vector<double> CandidateMu_P_MCS;	
	std::vector<double> CandidateMu_Phi;
	std::vector<double> CandidateMu_CosTheta;
	std::vector<double> CandidateMu_Chi2_YPlane;
	std::vector<double> CandidateMu_ThreePlaneLogLikelihood;
	std::vector<double> CandidateMu_ThreePlaneChi2;
//	std::vector<int> CandidateMu_StartContainment;
//	std::vector<int> CandidateMu_EndContainment;
	std::vector<double> CandidateMu_Length;
	std::vector<int> CandidateMu_MCParticle_Pdg;
	std::vector<double> CandidateMu_MCParticle_Purity;
	std::vector<double> CandidateMu_StartX;
	std::vector<double> CandidateMu_StartY;
	std::vector<double> CandidateMu_StartZ;
	std::vector<double> CandidateMu_EndX;
	std::vector<double> CandidateMu_EndY;
	std::vector<double> CandidateMu_EndZ;				

	std::vector<double> True_CandidateMu_P;
	std::vector<double> True_CandidateMu_Phi;
	std::vector<double> True_CandidateMu_CosTheta;
//	std::vector<int> True_CandidateMu_StartContainment;
//	std::vector<int> True_CandidateMu_EndContainment;

	// ---------------------------------------------------------------------------------------------------------------------------------------

//	std::vector<int> CandidateP_Mode;	
	std::vector<double> CandidateP_P_Range;
	std::vector<double> CandidateP_P_MCS;	
	std::vector<double> CandidateP_Phi;
	std::vector<double> CandidateP_CosTheta;
	std::vector<double> CandidateP_Chi2_YPlane;
	std::vector<double> CandidateP_ThreePlaneLogLikelihood;
	std::vector<double> CandidateP_ThreePlaneChi2;
//	std::vector<int> CandidateP_StartContainment;
//	std::vector<int> CandidateP_EndContainment;
	std::vector<double> CandidateP_Length;	
	std::vector<int> CandidateP_MCParticle_Pdg;
	std::vector<double> CandidateP_MCParticle_Purity;
	std::vector<double> CandidateP_StartX;
	std::vector<double> CandidateP_StartY;
	std::vector<double> CandidateP_StartZ;
	std::vector<double> CandidateP_EndX;
	std::vector<double> CandidateP_EndY;
	std::vector<double> CandidateP_EndZ;	

	std::vector<double> True_CandidateP_P;
	std::vector<double> True_CandidateP_Phi;
	std::vector<double> True_CandidateP_CosTheta;
//	std::vector<int> True_CandidateP_StartContainment;
//	std::vector<int> True_CandidateP_EndContainment;
	
	// -------------------------------------------------------------------------------------------------------------------------------------------
	
	// STV & Energy Reconstruction
	
	std::vector<double> Reco_Pt;
	std::vector<double> Reco_DeltaAlphaT;
	std::vector<double> Reco_DeltaPhiT;
	std::vector<double> Reco_ECal;
	std::vector<double> Reco_EQE;
	std::vector<double> Reco_Q2;
	std::vector<double> Reco_DeltaPhi;
	std::vector<double> Reco_DeltaTheta;		
	
	std::vector<double> True_Pt;
	std::vector<double> True_DeltaAlphaT;
	std::vector<double> True_DeltaPhiT;
	std::vector<double> True_ECal;
	std::vector<double> True_EQE;
	std::vector<double> True_Q2;		
	std::vector<double> True_DeltaPhi;
	std::vector<double> True_DeltaTheta;							

	// -------------------------------------------------------------------------------------------------------------------------------------------
	// -------------------------------------------------------------------------------------------------------------------------------------------	

	tree->Branch("Weight",&Weight);
	tree->Branch("T2KWeight",&T2KWeight);
	tree->Branch("ROOTinoWeight",&ROOTinoWeight);	

	tree->Branch("All_UBGenie", &All_UBGenie);
	tree->Branch("AxFFCCQEshape_UBGenie", &AxFFCCQEshape_UBGenie);
	tree->Branch("DecayAngMEC_UBGenie", &DecayAngMEC_UBGenie);
	tree->Branch("NormCCCOH_UBGenie", &NormCCCOH_UBGenie);
	tree->Branch("NormNCCOH_UBGenie", &NormNCCOH_UBGenie);
//	tree->Branch("RPA_CCQE_Reduced_UBGenie", &RPA_CCQE_Reduced_UBGenie);
	tree->Branch("RPA_CCQE_UBGenie", &RPA_CCQE_UBGenie);
	tree->Branch("ThetaDelta2NRad_UBGenie", &ThetaDelta2NRad_UBGenie);
	tree->Branch("Theta_Delta2Npi_UBGenie", &Theta_Delta2Npi_UBGenie);
	tree->Branch("VecFFCCQEshape_UBGenie", &VecFFCCQEshape_UBGenie);
	tree->Branch("XSecShape_CCMEC_UBGenie", &XSecShape_CCMEC_UBGenie);
	tree->Branch("expskin_FluxUnisim", &expskin_FluxUnisim);
	tree->Branch("horncurrent_FluxUnisim", &horncurrent_FluxUnisim);
	tree->Branch("kminus_PrimaryHadronNormalization", &kminus_PrimaryHadronNormalization);
	tree->Branch("kplus_PrimaryHadronFeynmanScaling", &kplus_PrimaryHadronFeynmanScaling);
	tree->Branch("kzero_PrimaryHadronSanfordWang", &kzero_PrimaryHadronSanfordWang);
	tree->Branch("nucleoninexsec_FluxUnisim", &nucleoninexsec_FluxUnisim);
	tree->Branch("nucleonqexsec_FluxUnisim", &nucleonqexsec_FluxUnisim);
	tree->Branch("nucleontotxsec_FluxUnisim", &nucleontotxsec_FluxUnisim);
	tree->Branch("piminus_PrimaryHadronSWCentralSplineVariation", &piminus_PrimaryHadronSWCentralSplineVariation);
	tree->Branch("pioninexsec_FluxUnisim", &pioninexsec_FluxUnisim);
	tree->Branch("pionqexsec_FluxUnisim", &pionqexsec_FluxUnisim);
	tree->Branch("piontotxsec_FluxUnisim", &piontotxsec_FluxUnisim);
	tree->Branch("piplus_PrimaryHadronSWCentralSplineVariation", &piplus_PrimaryHadronSWCentralSplineVariation);
	tree->Branch("reinteractions_piminus_Geant4", &reinteractions_piminus_Geant4);
	tree->Branch("reinteractions_piplus_Geant4", &reinteractions_piplus_Geant4);
	tree->Branch("reinteractions_proton_Geant4", &reinteractions_proton_Geant4);
//	tree->Branch("xsr_scc_Fa3_SCC", &xsr_scc_Fa3_SCC);
//	tree->Branch("xsr_scc_Fv3_SCC", &xsr_scc_Fv3_SCC);


	tree->Branch("CC1p",&CC1p);
	tree->Branch("CC1p1pi",&CC1p1pi);
	tree->Branch("CC2p",&CC2p);
	tree->Branch("CC2p1pi",&CC2p1pi);
	tree->Branch("CC3p",&CC3p);
	tree->Branch("CC3p1pi",&CC3p1pi);
	tree->Branch("CC3p2pi",&CC3p2pi);	
	tree->Branch("MCParticle_Mode",&MCParticle_Mode);

	// ------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("NuScore",&NuScore);
	tree->Branch("FlashScore",&FlashScore);

	// ------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("NBeamFlashes",&NBeamFlashes);
	tree->Branch("BeamFlashes_YCenter",&BeamFlashes_YCenter);
	tree->Branch("BeamFlashes_ZCenter",&BeamFlashes_ZCenter);
	tree->Branch("BeamFlashes_TotalPE",&BeamFlashes_TotalPE);

	// --------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("CandidateMuP_Distance",&CandidateMuP_Distance);
	tree->Branch("Vertex_X",&Vertex_X);
	tree->Branch("Vertex_Y",&Vertex_Y);
	tree->Branch("Vertex_Z",&Vertex_Z);
		
	tree->Branch("CandidateMu_P_Range",&CandidateMu_P_Range);
	tree->Branch("CandidateMu_P_MCS",&CandidateMu_P_MCS);	
	tree->Branch("CandidateMu_Phi",&CandidateMu_Phi);
	tree->Branch("CandidateMu_CosTheta",&CandidateMu_CosTheta);
	tree->Branch("CandidateMu_Chi2_YPlane",&CandidateMu_Chi2_YPlane);
	tree->Branch("CandidateMu_ThreePlaneLogLikelihood",&CandidateMu_ThreePlaneLogLikelihood);
	tree->Branch("CandidateMu_ThreePlaneChi2",&CandidateMu_ThreePlaneChi2);
//	tree->Branch("CandidateMu_StartContainment",&CandidateMu_StartContainment);
//	tree->Branch("CandidateMu_EndContainment",&CandidateMu_EndContainment);
	tree->Branch("CandidateMu_Length",&CandidateMu_Length);	
	tree->Branch("CandidateMu_MCParticle_Pdg",&CandidateMu_MCParticle_Pdg);
	tree->Branch("CandidateMu_MCParticle_Purity",&CandidateMu_MCParticle_Purity);
	tree->Branch("CandidateMu_StartX",&CandidateMu_StartX);
	tree->Branch("CandidateMu_StartY",&CandidateMu_StartY);
	tree->Branch("CandidateMu_StartZ",&CandidateMu_StartZ);
	tree->Branch("CandidateMu_EndX",&CandidateMu_EndX);
	tree->Branch("CandidateMu_EndY",&CandidateMu_EndY);
	tree->Branch("CandidateMu_EndZ",&CandidateMu_EndZ);				

	tree->Branch("True_CandidateMu_P",&True_CandidateMu_P);
	tree->Branch("True_CandidateMu_Phi",&True_CandidateMu_Phi);
	tree->Branch("True_CandidateMu_CosTheta",&True_CandidateMu_CosTheta);
//	tree->Branch("True_CandidateMu_StartContainment",&True_CandidateMu_StartContainment);
//	tree->Branch("True_CandidateMu_EndContainment",&True_CandidateMu_EndContainment);

	// ------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("CandidateP_P_Range",&CandidateP_P_Range);
	tree->Branch("CandidateP_P_MCS",&CandidateP_P_MCS);	
	tree->Branch("CandidateP_Phi",&CandidateP_Phi);
	tree->Branch("CandidateP_CosTheta",&CandidateP_CosTheta);
	tree->Branch("CandidateP_Chi2_YPlane",&CandidateP_Chi2_YPlane);
	tree->Branch("CandidateP_ThreePlaneLogLikelihood",&CandidateP_ThreePlaneLogLikelihood);
	tree->Branch("CandidateP_ThreePlaneChi2",&CandidateP_ThreePlaneChi2);
//	tree->Branch("CandidateP_StartContainment",&CandidateP_StartContainment);
//	tree->Branch("CandidateP_EndContainment",&CandidateP_EndContainment);
	tree->Branch("CandidateP_Length",&CandidateP_Length);	
	tree->Branch("CandidateP_MCParticle_Pdg",&CandidateP_MCParticle_Pdg);
	tree->Branch("CandidateP_MCParticle_Purity",&CandidateP_MCParticle_Purity);
	tree->Branch("CandidateP_StartX",&CandidateP_StartX);
	tree->Branch("CandidateP_StartY",&CandidateP_StartY);
	tree->Branch("CandidateP_StartZ",&CandidateP_StartZ);
	tree->Branch("CandidateP_EndX",&CandidateP_EndX);
	tree->Branch("CandidateP_EndY",&CandidateP_EndY);
	tree->Branch("CandidateP_EndZ",&CandidateP_EndZ);	

	tree->Branch("True_CandidateP_P",&True_CandidateP_P);
	tree->Branch("True_CandidateP_Phi",&True_CandidateP_Phi);
	tree->Branch("True_CandidateP_CosTheta",&True_CandidateP_CosTheta);
//	tree->Branch("True_CandidateP_StartContainment",&True_CandidateP_StartContainment);
//	tree->Branch("True_CandidateP_EndContainment",&True_CandidateP_EndContainment);

	// -----------------------------------------------------------------------------------------------------------------------------------------
	
	tree->Branch("Reco_Pt",&Reco_Pt);
	tree->Branch("Reco_DeltaAlphaT",&Reco_DeltaAlphaT);
	tree->Branch("Reco_DeltaPhiT",&Reco_DeltaPhiT);
	tree->Branch("Reco_ECal",&Reco_ECal);
	tree->Branch("Reco_EQE",&Reco_EQE);
	tree->Branch("Reco_Q2",&Reco_Q2);
	tree->Branch("Reco_DeltaPhi",&Reco_DeltaPhi);
	tree->Branch("Reco_DeltaTheta",&Reco_DeltaTheta);		
	
	tree->Branch("True_Pt",&True_Pt);
	tree->Branch("True_DeltaAlphaT",&True_DeltaAlphaT);
	tree->Branch("True_DeltaPhiT",&True_DeltaPhiT);
	tree->Branch("True_ECal",&True_ECal);
	tree->Branch("True_EQE",&True_EQE);
	tree->Branch("True_Q2",&True_Q2);
	tree->Branch("True_DeltaPhi",&True_DeltaPhi);
	tree->Branch("True_DeltaTheta",&True_DeltaTheta);						

	// -----------------------------------------------------------------------------------------------------------------------------------------

	Tools tools;

	// -----------------------------------------------------------------------------------------------------------------------------------------

	// Event Counters

	int EventCounter = 0;

	// ----------------------------------------------------------------------------------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;
		Long64_t ientry = LoadTree(jentry); if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;

		// -----------------------------------------------------------------------------------------------------------------------------------

		if ( EventPassedSwTrigger != 1) { continue; }

		// -----------------------------------------------------------------------------------------------------------------------------------

		// Numu Slices

		if (NumberNuMuPFParticles != 1) { continue; }

		int NNuMuDaughters = PFParticle_NumberNuMuDaughters->at(0);

		if (NNuMuDaughters != 2) { continue; } // Demand exactly 2 daughter particles
		int FirstPFParticleDaughter = 0;
		int SecondPFParticleDaughter = 1;
		if (TracksFromCurrentPFParticleStartX->at(0).size() != 2) { continue; } // Demand exactly 2 track-like daughter particles

		// MuonPdg in this case / Pandora = Track-like object
		
		if (PFParticle_NumberNuMuDaughtersPdgCode->at(0).at(FirstPFParticleDaughter) != MuonPdg || 
			PFParticle_NumberNuMuDaughtersPdgCode->at(0).at(SecondPFParticleDaughter) != MuonPdg) { continue; }
		if (TracksFromCurrentPFParticleStartX->at(0).at(0) == -99.) { continue; }
		if (TracksFromCurrentPFParticleStartX->at(0).at(1) == -99.) { continue; }

		// ----------------------------------------------------------------------------------------------------------------------------------

		// Making sure that we have NuScore & FlashScore

		if (PFParticle_NuScore->size() != 1) { continue; }
		if (PFParticle_FlashScore->size() != 1) { continue; }

		NuScore = PFParticle_NuScore->at(0);
		FlashScore = PFParticle_FlashScore->at(0);
		
		// ---------------------------------------------------------------------------------------------------------------------------------

		double weight = EventWeight->at(0);
		Weight = weight;

		double T2Kweight = T2KEventWeight->at(0);
		T2KWeight = T2Kweight;
		
		ROOTinoWeight = ROOTinoEventWeight->at(0);		

		All_UBGenie = *All_UBGenie_EventWeight;
		AxFFCCQEshape_UBGenie = *AxFFCCQEshape_UBGenie_EventWeight;
		DecayAngMEC_UBGenie = *DecayAngMEC_UBGenie_EventWeight;
		NormCCCOH_UBGenie = *NormCCCOH_UBGenie_EventWeight;
		NormNCCOH_UBGenie = *NormNCCOH_UBGenie_EventWeight;
//		RPA_CCQE_Reduced_UBGenie = *RPA_CCQE_Reduced_UBGenie_EventWeight;
		RPA_CCQE_UBGenie = *RPA_CCQE_UBGenie_EventWeight;
		ThetaDelta2NRad_UBGenie = *ThetaDelta2NRad_UBGenie_EventWeight;
		Theta_Delta2Npi_UBGenie = *Theta_Delta2Npi_UBGenie_EventWeight;
		VecFFCCQEshape_UBGenie = *VecFFCCQEshape_UBGenie_EventWeight;
		XSecShape_CCMEC_UBGenie = *XSecShape_CCMEC_UBGenie_EventWeight;
		expskin_FluxUnisim = *expskin_FluxUnisim_EventWeight;
		horncurrent_FluxUnisim = *horncurrent_FluxUnisim_EventWeight;
		kminus_PrimaryHadronNormalization = *kminus_PrimaryHadronNormalization_EventWeight;
		kplus_PrimaryHadronFeynmanScaling = *kplus_PrimaryHadronFeynmanScaling_EventWeight;
		kzero_PrimaryHadronSanfordWang = *kzero_PrimaryHadronSanfordWang_EventWeight;
		nucleoninexsec_FluxUnisim = *nucleoninexsec_FluxUnisim_EventWeight;
		nucleonqexsec_FluxUnisim = *nucleonqexsec_FluxUnisim_EventWeight;
		nucleontotxsec_FluxUnisim = *nucleontotxsec_FluxUnisim_EventWeight;
		piminus_PrimaryHadronSWCentralSplineVariation = *piminus_PrimaryHadronSWCentralSplineVariation_EventWeight;
		pioninexsec_FluxUnisim = *pioninexsec_FluxUnisim_EventWeight;
		pionqexsec_FluxUnisim = *pionqexsec_FluxUnisim_EventWeight;
		piontotxsec_FluxUnisim = *piontotxsec_FluxUnisim_EventWeight;
		piplus_PrimaryHadronSWCentralSplineVariation = *piplus_PrimaryHadronSWCentralSplineVariation_EventWeight;
		reinteractions_piminus_Geant4 = *reinteractions_piminus_Geant4_EventWeight;
		reinteractions_piplus_Geant4 = *reinteractions_piplus_Geant4_EventWeight;
		reinteractions_proton_Geant4 = *reinteractions_proton_Geant4_EventWeight;
//		xsr_scc_Fa3_SCC = *xsr_scc_Fa3_SCC_EventWeight;
//		xsr_scc_Fv3_SCC = *xsr_scc_Fv3_SCC_EventWeight;

		// ----------------------------------------------------------------------------------------------------------------------------------

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

		// --------------------------------------------------------------------------------------------------------------------------------

		// Tracks

		VectorTrackStart.clear();
		VectorTrackEnd.clear();

		std::vector<int> FirstTrackIndex; FirstTrackIndex.clear();
		std::vector<int> SecondTrackIndex; SecondTrackIndex.clear();
		std::vector<double> TrackPairDistance; TrackPairDistance.clear();
		std::vector<TVector3> TrackPairVertexPosition; TrackPairVertexPosition.clear();

		for (int WhichTrack = 0; WhichTrack < NumberTracks; WhichTrack++) {

			if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(FirstPFParticleDaughter) || 
				Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(SecondPFParticleDaughter)) {

				TVector3 TVector3TrackStart(Track_StartX->at(WhichTrack),Track_StartY->at(WhichTrack),Track_StartZ->at(WhichTrack));
				TVector3 TVector3TrackEnd(Track_EndX->at(WhichTrack),Track_EndY->at(WhichTrack),Track_EndZ->at(WhichTrack));

				VectorTrackStart.push_back(TVector3TrackStart);
				VectorTrackEnd.push_back(TVector3TrackEnd);

				if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(FirstPFParticleDaughter) )
					{ FirstTrackIndex.push_back(WhichTrack); }
				if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(SecondPFParticleDaughter) )
					{ SecondTrackIndex.push_back(WhichTrack); }

			}
			
		} // end of the loop over the recob::Tracks


		int NCandidateTrackPairs = FirstTrackIndex.size();
		if (NCandidateTrackPairs != 1) { continue; }

		double fTrackPairDistance = (VectorTrackStart.at(0) - VectorTrackStart.at(1)).Mag();
		TrackPairDistance.push_back(fTrackPairDistance);

		TVector3 VertexPositionV3 = (VectorTrackStart.at(0) + VectorTrackStart.at(1))*0.5;
		TrackPairVertexPosition.push_back(VertexPositionV3);

		// -----------------------------------------------------------------------------------------------------------------------------------

		// Loop over the candidate track pairs

		CandidateMuP_Distance.clear();
		Vertex_X.clear();
		Vertex_Y.clear();
		Vertex_Z.clear();

//		CandidateMu_Mode.clear();								
		CandidateMu_P_Range.clear();
		CandidateMu_P_MCS.clear();		
		CandidateMu_Phi.clear();
		CandidateMu_CosTheta.clear();
		CandidateMu_Chi2_YPlane.clear();
		CandidateMu_ThreePlaneLogLikelihood.clear();
		CandidateMu_ThreePlaneChi2.clear();
//		CandidateMu_StartContainment.clear();
//		CandidateMu_EndContainment.clear();
		CandidateMu_Length.clear();		
		CandidateMu_MCParticle_Pdg.clear();
		CandidateMu_MCParticle_Purity.clear();
		CandidateMu_StartX.clear();
		CandidateMu_StartY.clear();
		CandidateMu_StartZ.clear();
		CandidateMu_EndX.clear();
		CandidateMu_EndY.clear();
		CandidateMu_EndZ.clear();										

		True_CandidateMu_P.clear();
		True_CandidateMu_Phi.clear();
		True_CandidateMu_CosTheta.clear();
//		True_CandidateMu_StartContainment.clear();
//		True_CandidateMu_EndContainment.clear();

		// ---------------------------------------------------------------------------------------------------------------------------------

//		CandidateP_Mode.clear();		
		CandidateP_P_Range.clear();
		CandidateP_P_MCS.clear();		
		CandidateP_Phi.clear();
		CandidateP_CosTheta.clear();
		CandidateP_Chi2_YPlane.clear();
		CandidateP_ThreePlaneLogLikelihood.clear();
		CandidateP_ThreePlaneChi2.clear();
//		CandidateP_StartContainment.clear();
//		CandidateP_EndContainment.clear();
		CandidateP_Length.clear();		
		CandidateP_MCParticle_Pdg.clear();
		CandidateP_MCParticle_Purity.clear();
		CandidateP_StartX.clear();
		CandidateP_StartY.clear();
		CandidateP_StartZ.clear();
		CandidateP_EndX.clear();
		CandidateP_EndY.clear();
		CandidateP_EndZ.clear();		

		True_CandidateP_P.clear();
		True_CandidateP_Phi.clear();
		True_CandidateP_CosTheta.clear();
//		True_CandidateP_StartContainment.clear();
//		True_CandidateP_EndContainment.clear();

		// -----------------------------------------------------------------------------------------------------------------------------
		
		Reco_Pt.clear();
		Reco_DeltaAlphaT.clear();
		Reco_DeltaPhiT.clear();
		Reco_ECal.clear();
		Reco_EQE.clear();
		Reco_Q2.clear();
		Reco_DeltaPhi.clear();
		Reco_DeltaTheta.clear();				
		
		True_Pt.clear();
		True_DeltaAlphaT.clear();
		True_DeltaPhiT.clear();
		True_ECal.clear();
		True_EQE.clear();
		True_Q2.clear();
		True_DeltaPhi.clear();
		True_DeltaTheta.clear();															

		// -----------------------------------------------------------------------------------------------------------------------------

		for (int WhichTrackPair = 0; WhichTrackPair < NCandidateTrackPairs; WhichTrackPair++) {

			// Track indices

			int FirstCandidateTrackIndex = FirstTrackIndex.at(WhichTrackPair);
			int SecondCandidateTrackIndex = SecondTrackIndex.at(WhichTrackPair);

			// Get the muon & proton candidates

//			double FirstTrackLength = Track_Length->at(FirstCandidateTrackIndex);
//			double SecondTrackLength = Track_Length->at(SecondCandidateTrackIndex);			
//			int CandidateMuonTrackIndex = FirstTrackLength > SecondTrackLength? FirstCandidateTrackIndex :  SecondCandidateTrackIndex;
//			int CandidateProtonTrackIndex = FirstTrackLength > SecondTrackLength? SecondCandidateTrackIndex :  FirstCandidateTrackIndex;

			double FirstTrackThreePlanePID = Track_ParticleId_ProtonScore_ThreePlanePID->at(FirstCandidateTrackIndex);
			double SecondTrackThreePlanePID = Track_ParticleId_ProtonScore_ThreePlanePID->at(SecondCandidateTrackIndex);
			int CandidateMuonTrackIndex = FirstTrackThreePlanePID<SecondTrackThreePlanePID?FirstCandidateTrackIndex:SecondCandidateTrackIndex;
			int CandidateProtonTrackIndex = FirstTrackThreePlanePID<SecondTrackThreePlanePID?SecondCandidateTrackIndex:FirstCandidateTrackIndex;

			// ---------------------------------------------------------------------------------------------------------------------

			// Candidate muon

			double CandidateMuonTrackTheta = Track_Theta->at(CandidateMuonTrackIndex); // rad
			double CandidateMuonTrackCosTheta = cos(CandidateMuonTrackTheta);
			double CandidateMuonTrackLength = Track_Length->at(CandidateMuonTrackIndex); // cm
			
			double MuonTrackStartX = Track_StartX->at(CandidateMuonTrackIndex);
			double MuonTrackStartY = Track_StartY->at(CandidateMuonTrackIndex);
			double MuonTrackStartZ = Track_StartZ->at(CandidateMuonTrackIndex);
			
			double MuonTrackEndX = Track_EndX->at(CandidateMuonTrackIndex);
			double MuonTrackEndY = Track_EndY->at(CandidateMuonTrackIndex);
			double MuonTrackEndZ = Track_EndZ->at(CandidateMuonTrackIndex);						
			
			TVector3 CandidateMuonTrackStart(MuonTrackStartX,MuonTrackStartY,MuonTrackStartZ);
			TVector3 CandidateMuonTrackEnd(MuonTrackEndX,MuonTrackEndY,MuonTrackEndZ);
			bool CandidateMuonTrackStartContainment = tools.inFVVector(CandidateMuonTrackStart);
			bool CandidateMuonTrackEndContainment = tools.inFVVector(CandidateMuonTrackEnd);

			// Candidate proton

			double CandidateProtonTrackTheta = Track_Theta->at(CandidateProtonTrackIndex); // rad
			double CandidateProtonTrackCosTheta = cos(CandidateProtonTrackTheta);
			double CandidateProtonTrackLength = Track_Length->at(CandidateProtonTrackIndex); // cm
			
			double ProtonTrackStartX = Track_StartX->at(CandidateProtonTrackIndex);
			double ProtonTrackStartY = Track_StartY->at(CandidateProtonTrackIndex);
			double ProtonTrackStartZ = Track_StartZ->at(CandidateProtonTrackIndex);
			
			double ProtonTrackEndX = Track_EndX->at(CandidateProtonTrackIndex);
			double ProtonTrackEndY = Track_EndY->at(CandidateProtonTrackIndex);
			double ProtonTrackEndZ = Track_EndZ->at(CandidateProtonTrackIndex);			
			
			TVector3 CandidateProtonTrackStart(ProtonTrackStartX,ProtonTrackStartY,ProtonTrackStartZ);
			TVector3 CandidateProtonTrackEnd(ProtonTrackEndX,ProtonTrackEndY,ProtonTrackEndZ);
//			bool CandidateProtonTrackStartContainment = tools.inFVVector(CandidateProtonTrackStart);
//			bool CandidateProtonTrackEndContainment = tools.inFVVector(CandidateProtonTrackEnd);			
			
			// ---------------------------------------------------------------------------------------------------------------------		

			CandidateMuP_Distance.push_back(TrackPairDistance.at(WhichTrackPair));	
			Vertex_X.push_back(TrackPairVertexPosition.at(WhichTrackPair).X());
			Vertex_Y.push_back(TrackPairVertexPosition.at(WhichTrackPair).Y());
			Vertex_Z.push_back(TrackPairVertexPosition.at(WhichTrackPair).Z());

			// ---------------------------------------------------------------------------------------------------------------------

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
//				CandidateMuonTrack_Momentum_MCS_GeV = CandidateMuonTrack_Momentum_MCS_MeV / 1000.; // GeV/c
				CandidateMuonTrack_Momentum_MCS_GeV = Track_Momentum_Range_Muon->at(CandidateMuonTrackIndex); // GeV/c
				CandidateMuonTrack_E_GeV = CandidateMuonTrack_KE_GeV + MuonMass_GeV; // GeV/c

			} else {

				CandidateMuonTrack_Momentum_MCS_GeV = Track_Momentum_MCS->at(CandidateMuonTrackIndex); // GeV/c
				CandidateMuonTrack_Momentum_MCS_MeV = 1000. * CandidateMuonTrack_Momentum_MCS_GeV; // MeV/c
				CandidateMuonTrack_KE_MeV = tools.PToKE(MuonPdg,CandidateMuonTrack_Momentum_MCS_MeV); // MeV/c
				CandidateMuonTrack_KE_GeV = CandidateMuonTrack_KE_MeV / 1000.; // GeV/c
				CandidateMuonTrack_E_GeV = CandidateMuonTrack_KE_GeV + MuonMass_GeV; // GeV/c

			}
									
			CandidateMu_P_MCS.push_back(Track_Momentum_MCS->at(CandidateMuonTrackIndex));
//			CandidateMu_P_Range.push_back(tools.KEToP(0.001*MuonPdg,sMuonRange2T->Eval(CandidateMuonTrackLength)));			
			CandidateMu_P_Range.push_back(Track_Momentum_Range_Muon->at(CandidateMuonTrackIndex));			
			CandidateMu_Phi.push_back(Track_Phi->at(CandidateMuonTrackIndex) * 180./ TMath::Pi()); // deg
			CandidateMu_CosTheta.push_back(CandidateMuonTrackCosTheta);
			CandidateMu_Chi2_YPlane.push_back(Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateMuonTrackIndex));
			CandidateMu_ThreePlaneLogLikelihood.push_back(Track_ParticleId_ProtonScore_ThreePlanePID->at(CandidateMuonTrackIndex));
			CandidateMu_ThreePlaneChi2.push_back(CalCandidateMu_ThreePlaneChi2);
//			CandidateMu_StartContainment.push_back(CandidateMuonTrackStartContainment);
//			CandidateMu_EndContainment.push_back(CandidateMuonTrackEndContainment);
			CandidateMu_Length.push_back(CandidateMuonTrackLength);
			CandidateMu_StartX.push_back(Track_StartX->at(CandidateMuonTrackIndex));
			CandidateMu_StartY.push_back(Track_StartY->at(CandidateMuonTrackIndex));
			CandidateMu_StartZ.push_back(Track_StartZ->at(CandidateMuonTrackIndex));
			CandidateMu_EndX.push_back(Track_EndX->at(CandidateMuonTrackIndex));
			CandidateMu_EndY.push_back(Track_EndY->at(CandidateMuonTrackIndex));
			CandidateMu_EndZ.push_back(Track_EndZ->at(CandidateMuonTrackIndex));								

			// --------------------------------------------------------------------------------------------------------------------------

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

/*			if (CandidateProtonTrackStartContainment == true && CandidateProtonTrackEndContainment == true) {*/

				CandidateProtonTrack_KE_MeV = sProtonRange2T->Eval(CandidateProtonTrackLength); // MeV
				CandidateProtonTrack_KE_GeV = CandidateProtonTrack_KE_MeV / 1000.; // GeV
				CandidateProtonTrack_Momentum_MCS_MeV = tools.KEToP(ProtonPdg,CandidateProtonTrack_KE_MeV); // MeV/c
				CandidateProtonTrack_Momentum_MCS_GeV = CandidateProtonTrack_Momentum_MCS_MeV / 1000.; // GeV/c
//				CandidateProtonTrack_Momentum_MCS_GeV = Track_Momentum->at(CandidateProtonTrackIndex); // GeV/c
				CandidateProtonTrack_E_GeV = CandidateProtonTrack_KE_GeV + ProtonMass_GeV; // GeV/c
/*
			} else {

				CandidateProtonTrack_Momentum_MCS_GeV = Track_Momentum_MCS->at(CandidateProtonTrackIndex); // GeV/c
				CandidateProtonTrack_Momentum_MCS_MeV = 1000. * CandidateProtonTrack_Momentum_MCS_GeV; // MeV/c
				CandidateProtonTrack_KE_MeV = tools.PToKE(ProtonPdg,CandidateProtonTrack_Momentum_MCS_MeV); // MeV/c
				CandidateProtonTrack_KE_GeV = CandidateProtonTrack_KE_MeV / 1000.; // GeV/c
				CandidateProtonTrack_E_GeV = CandidateProtonTrack_KE_GeV + ProtonMass_GeV; // GeV/c

			}
*/

			CandidateP_P_Range.push_back(Track_Momentum_Range_Proton->at(CandidateProtonTrackIndex));
			CandidateP_P_MCS.push_back(Track_Momentum_MCS->at(CandidateProtonTrackIndex));			
			CandidateP_Phi.push_back(Track_Phi->at(CandidateProtonTrackIndex) * 180./ TMath::Pi()); // deg
			CandidateP_CosTheta.push_back(CandidateProtonTrackCosTheta);
			CandidateP_Chi2_YPlane.push_back(Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateProtonTrackIndex));
			CandidateP_ThreePlaneLogLikelihood.push_back(Track_ParticleId_ProtonScore_ThreePlanePID->at(CandidateProtonTrackIndex));
			CandidateP_ThreePlaneChi2.push_back(CalCandidateP_ThreePlaneChi2);
//			CandidateP_StartContainment.push_back(CandidateProtonTrackStartContainment);
//			CandidateP_EndContainment.push_back(CandidateProtonTrackEndContainment);
			CandidateP_Length.push_back(CandidateProtonTrackLength);
			CandidateP_StartX.push_back(Track_StartX->at(CandidateProtonTrackIndex));
			CandidateP_StartY.push_back(Track_StartY->at(CandidateProtonTrackIndex));
			CandidateP_StartZ.push_back(Track_StartZ->at(CandidateProtonTrackIndex));
			CandidateP_EndX.push_back(Track_EndX->at(CandidateProtonTrackIndex));
			CandidateP_EndY.push_back(Track_EndY->at(CandidateProtonTrackIndex));
			CandidateP_EndZ.push_back(Track_EndZ->at(CandidateProtonTrackIndex));						

			// --------------------------------------------------------------------------------------------------------------------
			
			// STV & Energy Reconstruction
			
			TVector3 TVector3CandidateMuon(-1,-1,-1);
			TVector3CandidateMuon.SetMag(CandidateMuonTrack_Momentum_MCS_GeV);
			TVector3CandidateMuon.SetTheta(TMath::ACos(CandidateMuonTrackCosTheta));
			TVector3CandidateMuon.SetPhi(Track_Phi->at(CandidateMuonTrackIndex));			

			TVector3 TVector3CandidateProton(-1,-1,-1);
			TVector3CandidateProton.SetMag(CandidateProtonTrack_Momentum_MCS_GeV);
			TVector3CandidateProton.SetTheta(TMath::ACos(CandidateProtonTrackCosTheta));
			TVector3CandidateProton.SetPhi(Track_Phi->at(CandidateProtonTrackIndex));

			STV_Tools reco_stv_tool(TVector3CandidateMuon,TVector3CandidateProton,CandidateMuonTrack_E_GeV,CandidateProtonTrack_E_GeV);

			Reco_Pt.push_back(reco_stv_tool.ReturnPt());
			Reco_DeltaAlphaT.push_back(reco_stv_tool.ReturnDeltaAlphaT());
			Reco_DeltaPhiT.push_back(reco_stv_tool.ReturnDeltaPhiT());
			Reco_ECal.push_back(reco_stv_tool.ReturnECal());
			Reco_EQE.push_back(reco_stv_tool.ReturnEQE());
			Reco_Q2.push_back(reco_stv_tool.ReturnQ2());	
			
			// --------------------------------------------------------------------------------------------------------------------

			// Relative Angles
			
			double DeltaPhi_Rad = TVector3CandidateMuon.DeltaPhi(TVector3CandidateProton);
			double DeltaPhi_Deg = DeltaPhi_Rad * 180. / TMath::Pi();
			if (DeltaPhi_Deg >= 360.) { DeltaPhi_Deg -= 360.; }
			if (DeltaPhi_Deg < 0.) { DeltaPhi_Deg += 360.; }
			Reco_DeltaPhi.push_back(DeltaPhi_Deg);
			
			double DeltaTheta_Rad = TVector3CandidateMuon.Angle(TVector3CandidateProton);
			double DeltaTheta_Deg = DeltaTheta_Rad * 180. / TMath::Pi();
			if (DeltaTheta_Deg >= 360.) { DeltaTheta_Deg -= 360.; }
			if (DeltaTheta_Deg < 0.) { DeltaTheta_Deg += 360.; }
			Reco_DeltaTheta.push_back(DeltaTheta_Deg);									
			
			// --------------------------------------------------------------------------------------------------------------------
			// --------------------------------------------------------------------------------------------------------------------

			// Backtracking to truth, only for overlays

			if (string(fWhichSample).find("Overlay") != std::string::npos) {

				CandidateMu_MCParticle_Pdg.push_back(Track_MCParticle_PdgCode->at(CandidateMuonTrackIndex));
				CandidateMu_MCParticle_Purity.push_back(Track_MCParticle_Purity->at(CandidateMuonTrackIndex));
//				CandidateMu_Mode.push_back(Track_MCParticle_Mode->at(CandidateMuonTrackIndex));
				
				double CandidateMuonStartX = Track_MCParticle_Vx->at(CandidateMuonTrackIndex);
				double CandidateMuonStartY = Track_MCParticle_Vy->at(CandidateMuonTrackIndex);
				double CandidateMuonStartZ = Track_MCParticle_Vz->at(CandidateMuonTrackIndex);
				
				double CandidateMuonEndX = Track_MCParticle_EndX->at(CandidateMuonTrackIndex);
				double CandidateMuonEndY = Track_MCParticle_EndY->at(CandidateMuonTrackIndex);
				double CandidateMuonEndZ = Track_MCParticle_EndZ->at(CandidateMuonTrackIndex);						

				TVector3 TrueCandidateMuonTrackStart(CandidateMuonStartX,CandidateMuonStartY,CandidateMuonStartZ);
				TVector3 TrueCandidateMuonTrackEnd(CandidateMuonEndX,CandidateMuonEndY,CandidateMuonEndZ);
				TVector3 TrueCandidateMuonChange = TrueCandidateMuonTrackEnd - TrueCandidateMuonTrackStart;
//				bool TrueCandidateMuonTrackStartContainment = tools.inFVVector(TrueCandidateMuonTrackStart);
//				bool TrueCandidateMuonTrackEndContainment = tools.inFVVector(TrueCandidateMuonTrackEnd);

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
//				True_CandidateMu_StartContainment.push_back(TrueCandidateMuonTrackStartContainment);
//				True_CandidateMu_EndContainment.push_back(TrueCandidateMuonTrackEndContainment);

				// --------------------------------------------------------------------------------------------------------------------

				CandidateP_MCParticle_Pdg.push_back(Track_MCParticle_PdgCode->at(CandidateProtonTrackIndex));
				CandidateP_MCParticle_Purity.push_back(Track_MCParticle_Purity->at(CandidateProtonTrackIndex));
//				CandidateP_Mode.push_back(Track_MCParticle_Mode->at(CandidateProtonTrackIndex));
				
				double CandidateProtonStartX = Track_MCParticle_Vx->at(CandidateProtonTrackIndex);
				double CandidateProtonStartY = Track_MCParticle_Vy->at(CandidateProtonTrackIndex);
				double CandidateProtonStartZ = Track_MCParticle_Vz->at(CandidateProtonTrackIndex);
				
				double CandidateProtonEndX = Track_MCParticle_EndX->at(CandidateProtonTrackIndex);
				double CandidateProtonEndY = Track_MCParticle_EndY->at(CandidateProtonTrackIndex);
				double CandidateProtonEndZ = Track_MCParticle_EndZ->at(CandidateProtonTrackIndex);						

				TVector3 TrueCandidateProtonTrackStart(CandidateProtonStartX,CandidateProtonStartY,CandidateProtonStartZ);
				TVector3 TrueCandidateProtonTrackEnd(CandidateProtonEndX,CandidateProtonEndY,CandidateProtonEndZ);
				TVector3 TrueCandidateProtonChange = TrueCandidateProtonTrackEnd - TrueCandidateProtonTrackStart;
//				bool TrueCandidateProtonTrackStartContainment = tools.inFVVector(TrueCandidateProtonTrackStart);
//				bool TrueCandidateProtonTrackEndContainment = tools.inFVVector(TrueCandidateProtonTrackEnd);

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
//				True_CandidateP_StartContainment.push_back(TrueCandidateProtonTrackStartContainment);
//				True_CandidateP_EndContainment.push_back(TrueCandidateProtonTrackEndContainment);
				
				// --------------------------------------------------------------------------------------------------------------------
				
				// STV & Energy Reconstruction
				
				TVector3 True_TVector3CandidateMuon(-1,-1,-1);
				True_TVector3CandidateMuon.SetMag(TrueCandidateMuonTrackMomentum_GeV);
				True_TVector3CandidateMuon.SetTheta(TrueCandidateMuonTrackTheta);
				True_TVector3CandidateMuon.SetPhi(TrueCandidateMuonTrackPhi);

				TVector3 True_TVector3CandidateProton(-1,-1,-1);
				True_TVector3CandidateProton.SetMag(TrueCandidateProtonTrackMomentum_GeV);
				True_TVector3CandidateProton.SetTheta(TrueCandidateProtonTrackTheta);
				True_TVector3CandidateProton.SetPhi(TrueCandidateProtonTrackPhi);			


				STV_Tools true_stv_tool(True_TVector3CandidateMuon,True_TVector3CandidateProton,
							 TrueCandidateMuonTrack_E_GeV,TrueCandidateProtonTrack_E_GeV);

				True_Pt.push_back(true_stv_tool.ReturnPt());
				True_DeltaAlphaT.push_back(true_stv_tool.ReturnDeltaAlphaT());
				True_DeltaPhiT.push_back(true_stv_tool.ReturnDeltaPhiT());
				True_ECal.push_back(true_stv_tool.ReturnECal());
				True_EQE.push_back(true_stv_tool.ReturnEQE());
				True_Q2.push_back(true_stv_tool.ReturnQ2());	
				
				// --------------------------------------------------------------------------------------------------------------------

				// Relative Angles
				
				double True_DeltaPhi_Rad = True_TVector3CandidateMuon.DeltaPhi(True_TVector3CandidateProton);
				double True_DeltaPhi_Deg = True_DeltaPhi_Rad * 180. / TMath::Pi();
				if (True_DeltaPhi_Deg >= 360.) { True_DeltaPhi_Deg -= 360.; }
				if (True_DeltaPhi_Deg < 0.) { True_DeltaPhi_Deg += 360.; }
				True_DeltaPhi.push_back(True_DeltaPhi_Deg);
				
				double True_DeltaTheta_Rad = True_TVector3CandidateMuon.Angle(True_TVector3CandidateProton);
				double True_DeltaTheta_Deg = True_DeltaTheta_Rad * 180. / TMath::Pi();
				if (True_DeltaTheta_Deg >= 360.) { True_DeltaTheta_Deg -= 360.; }
				if (True_DeltaTheta_Deg < 0.) { True_DeltaTheta_Deg += 360.; }
				True_DeltaTheta.push_back(True_DeltaTheta_Deg);						

			} // End of the backtracking to truth, only for overlays

			EventCounter++;

		} // End of the loop over the candidate track pairs

		// ------------------------------------------------------------------------------------------------------------------------------------

		// MCParticle Loop
		
		int fCC1p = 0, fCC1p1pi = 0, fCC2p = 0, fCC2p1pi = 0, fCC3p = 0, fCC3p1pi = 0, fCC3p2pi = 0, fMCParticle_Mode = -1;

		int TrueMuonCounter = 0, TrueProtonCounter = 0, TrueChargedPionCounter = 0;
		int NMCParticles = MCParticle_PdgCode->size();
		
		std::vector<int> VectorTrueMuonIndex; VectorTrueMuonIndex.clear();
		std::vector<int> VectorTrueProtonIndex; VectorTrueProtonIndex.clear();		

		for (int WhichMCParticle = 0; WhichMCParticle < NMCParticles; WhichMCParticle++) {

			// Demand stable final state particles and primary interactions

			if (
				MCParticle_StatusCode->at(WhichMCParticle) == 1 
				&& MCParticle_Process->at(WhichMCParticle) == "primary"				
				&& MCTruth_CCNC->at(0) == 0 // CC events				
			) {

				double MCParticleMomentum = MCParticle_P->at(WhichMCParticle);
				int MCParticlePdg = MCParticle_PdgCode->at(WhichMCParticle);

				if ( MCParticlePdg == MuonPdg && MCParticleMomentum >= ArrayNBinsMuonMomentum[0] ) 
					{ TrueMuonCounter++;  VectorTrueMuonIndex.push_back(WhichMCParticle); }

				if ( MCParticlePdg == ProtonPdg && MCParticleMomentum >= ArrayNBinsProtonMomentum[0] ) 
					{ TrueProtonCounter++; VectorTrueProtonIndex.push_back(WhichMCParticle); }

				if ( fabs(MCParticlePdg) == AbsChargedPionPdg && MCParticleMomentum >= ChargedPionMomentumThres ) 
					{ TrueChargedPionCounter++; }

			} // End of the demand stable final state particles and primary interactions

		} // end of the loop over the simb::MCParticles

		// Signal definition: 1 mu (Pmu > 100 MeV / c), 1p (Pp > 200 MeV / c) & 0 pi+/- (Ppi > 70 MeV / c)

		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 0) { fCC1p = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 1) { fCC1p1pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 2 && TrueChargedPionCounter == 0) { fCC2p = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 2 && TrueChargedPionCounter == 1) { fCC2p1pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 0) { fCC3p = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 1) { fCC3p1pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 2) { fCC3p2pi = 1; }

		if (MCTruth_Mode->size() == 1) { fMCParticle_Mode = MCTruth_Mode->at(0); }

		CC1p = fCC1p;
		CC1p1pi = fCC1p1pi;
		CC2p = fCC2p;
		CC2p1pi = fCC2p1pi;
		CC3p = fCC3p;
		CC3p1pi = fCC3p1pi;
		CC3p2pi = fCC3p2pi;			

		MCParticle_Mode = fMCParticle_Mode;

		// ---------------------------------------------------------------------------------------------------------------------------------

		tree->Fill();

	} // End of the loop over the number of events

	// -----------------------------------------------------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------------------------------------

	// To be printed at the end of the run

	int precision = 2;

	std::cout.precision(precision);
	std::cout << "\n\nGathered a total of " << EventCounter << " preselected events" << std::endl << std::endl;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	OutputFile->cd();
	OutputFile->Write();
	OutputFile->Close();
	fSpines->Close();
	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;

} // end of the program

// ----------------------------------------------------------------------------------------------------------------------------------------------------

double ThreePlaneChi2(TVector3 TrackStart,TVector3 TrackEnd,double Chi2_Plane0,double Chi2_Plane1,double Chi2_Plane2) {

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

// ----------------------------------------------------------------------------------------------------------------------------------------------------
