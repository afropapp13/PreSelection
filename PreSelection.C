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
#include "ubana/myClasses/Box_Tools.h"

using namespace std;
using namespace Constants;

double ThreePlaneChi2(TVector3 TrackStart,TVector3 TrackEnd,double Chi2_Plane0,double Chi2_Plane1,double Chi2_Plane2);

double Sphere(double FracPlane0,double FracPlane1,double FracPlane2);

void PreSelection::Loop() {

	if (fChain == 0) { return; } 
	Long64_t nentries = fChain->GetEntriesFast(); Long64_t nbytes = 0, nb = 0;

	TH1D::SetDefaultSumw2();

	std::vector<TVector3> VectorTrackStart;
	std::vector<TVector3> VectorTrackEnd;

	std::vector<TVector3> VectorMCParticleStart;
	std::vector<TVector3> VectorMCParticleEnd;

	// ---------------------------------------------------------------------------------------------------------------------------------------

	// Txt file to keep track of the event reduction at each stage

	TString TxtName = "/uboone/data/users/apapadop/myEvents/myTxtFiles/"+UBCodeVersion+"/TxtPreSelection_"+fWhichSample+"_"+UBCodeVersion+".txt";
	ofstream myTxtFile;
	myTxtFile.open(TxtName);	

	// ---------------------------------------------------------------------------------------------------------------------------------------

	// Output Files

	TString FileName = "/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_"+fWhichSample+"_"+UBCodeVersion+".root";
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

	int Run;
	int SubRun;
	int Event;

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

	int NC;	
	int CC1p;
	int CC1p1pi;
	int CC2p;
	int CC2p1pi;
	int CC3p;
	int CC3p1pi;
	int CC3p2pi;
	int CC3p3pi;
	int CC4p0pi;
	int CC4p1pi;
	
	int MCParticle_Mode;

	double True_Ev;
	double True_Vx;
	double True_Vy;
	double True_Vz;

	int NumberPi0;
	int NumberNeutrons;
	int NumberProtons;
	int NumberMuons;
	int NumberChargedPions;

	// -------------------------------------------------------------------------------------------------------------------------------------------

	double NuScore;
	double FlashScore; 

	// ------------------------------------------------------------------------------------------------------------------------------------------

	int NBeamFlashes;
	std::vector<double> BeamFlashes_YCenter;
	std::vector<double> BeamFlashes_ZCenter;
	std::vector<double> BeamFlashes_TotalPE;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<double> VertexActivity_50x100;

	std::vector<double> CandidateMuP_Distance;
	std::vector<double> Vertex_X;
	std::vector<double> Vertex_Y;
	std::vector<double> Vertex_Z;

//	std::vector<int> CandidateMu_Mode;
	std::vector<double> CandidateMu_TrackScore;			
	std::vector<double> CandidateMu_P_Range;
	std::vector<double> CandidateMu_P_MCS;	
	std::vector<double> CandidateMu_Phi;
	std::vector<double> CandidateMu_CosTheta;
	std::vector<double> CandidateMu_Chi2_YPlane;
	std::vector<double> CandidateMu_ThreePlaneLogLikelihood;
	std::vector<double> CandidateMu_LLR_PID;
	std::vector<double> CandidateMu_ThreePlaneChi2;
	std::vector<int> CandidateMu_StartContainment;
	std::vector<int> CandidateMu_EndContainment;
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
//	std::vector<double> True_CandidateMu_Px;
//	std::vector<double> True_CandidateMu_Py;
//	std::vector<double> True_CandidateMu_Pz;
	std::vector<double> True_CandidateMu_Phi;
	std::vector<double> True_CandidateMu_CosTheta;
	
	std::vector<double> True_CandidateMu_StartX;
	std::vector<double> True_CandidateMu_StartY;
	std::vector<double> True_CandidateMu_StartZ;
	
	std::vector<double> True_CandidateMu_EndX;
	std::vector<double> True_CandidateMu_EndY;
	std::vector<double> True_CandidateMu_EndZ;				
	
	std::vector<int> True_CandidateMu_StartContainment;
	std::vector<int> True_CandidateMu_EndContainment;

	// ---------------------------------------------------------------------------------------------------------------------------------------

//	std::vector<int> CandidateP_Mode;	
	std::vector<double> CandidateP_TrackScore;
	std::vector<double> CandidateP_P_Range;
	std::vector<double> CandidateP_P_MCS;	
	std::vector<double> CandidateP_Phi;
	std::vector<double> CandidateP_CosTheta;
	std::vector<double> CandidateP_Chi2_YPlane;
	std::vector<double> CandidateP_ThreePlaneLogLikelihood;
	std::vector<double> CandidateP_LLR_PID;
	std::vector<double> CandidateP_ThreePlaneChi2;
	std::vector<int> CandidateP_StartContainment;
	std::vector<int> CandidateP_EndContainment;
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
//	std::vector<double> True_CandidateP_Px;
//	std::vector<double> True_CandidateP_Py;
//	std::vector<double> True_CandidateP_Pz;
	std::vector<double> True_CandidateP_Phi;
	std::vector<double> True_CandidateP_CosTheta;
	
	std::vector<double> True_CandidateP_StartX;
	std::vector<double> True_CandidateP_StartY;
	std::vector<double> True_CandidateP_StartZ;
	
	std::vector<double> True_CandidateP_EndX;
	std::vector<double> True_CandidateP_EndY;
	std::vector<double> True_CandidateP_EndZ;	
	
	std::vector<int> True_CandidateP_StartContainment;
	std::vector<int> True_CandidateP_EndContainment;
	
	// -------------------------------------------------------------------------------------------------------------------------------------------
	
	// STV, Energy Reconstruction & Light Cone Vraiables

	std::vector<double> Reco_kMiss;
	std::vector<double> Reco_EMiss;
	std::vector<double> Reco_PMissMinus;
	std::vector<double> Reco_PMiss;
	std::vector<double> Reco_Pt;
	std::vector<double> Reco_DeltaAlphaT;
	std::vector<double> Reco_DeltaPhiT;
	std::vector<double> Reco_ECal;
	std::vector<double> Reco_EQE;
	std::vector<double> Reco_Q2;
	std::vector<double> Reco_DeltaPhi;
	std::vector<double> Reco_DeltaTheta;		
	
	std::vector<double> True_kMiss;
	std::vector<double> True_EMiss;
	std::vector<double> True_PMissMinus;
	std::vector<double> True_PMiss;	
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

	tree->Branch("Run",&Run);
	tree->Branch("SubRun",&SubRun);
	tree->Branch("Event",&Event);	

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

	tree->Branch("NC",&NC);
	tree->Branch("CC1p",&CC1p);
	tree->Branch("CC1p1pi",&CC1p1pi);
	tree->Branch("CC2p",&CC2p);
	tree->Branch("CC2p1pi",&CC2p1pi);
	tree->Branch("CC3p",&CC3p);
	tree->Branch("CC3p1pi",&CC3p1pi);
	tree->Branch("CC3p2pi",&CC3p2pi);	
	tree->Branch("CC3p3pi",&CC3p3pi);	
	tree->Branch("CC4p0pi",&CC4p0pi);	
	tree->Branch("CC4p1pi",&CC4p1pi);	
	tree->Branch("MCParticle_Mode",&MCParticle_Mode);

	tree->Branch("NumberPi0",&NumberPi0);
	tree->Branch("NumberNeutrons",&NumberNeutrons);
	tree->Branch("NumberProtons",&NumberProtons);
	tree->Branch("NumberMuons",&NumberMuons);
	tree->Branch("NumberChargedPions",&NumberChargedPions);

	tree->Branch("True_Ev",&True_Ev);
	tree->Branch("True_Vx",&True_Vx);
	tree->Branch("True_Vy",&True_Vy);
	tree->Branch("True_Vz",&True_Vz);

	// ------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("NuScore",&NuScore);
	tree->Branch("FlashScore",&FlashScore);

	// ------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("NBeamFlashes",&NBeamFlashes);
	tree->Branch("BeamFlashes_YCenter",&BeamFlashes_YCenter);
	tree->Branch("BeamFlashes_ZCenter",&BeamFlashes_ZCenter);
	tree->Branch("BeamFlashes_TotalPE",&BeamFlashes_TotalPE);

	// --------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("VertexActivity_50x100",&VertexActivity_50x100);
	tree->Branch("CandidateMuP_Distance",&CandidateMuP_Distance);
	tree->Branch("Vertex_X",&Vertex_X);
	tree->Branch("Vertex_Y",&Vertex_Y);
	tree->Branch("Vertex_Z",&Vertex_Z);
		
	// --------------------------------------------------------------------------------------------------------------------------------------------	

	tree->Branch("CandidateMu_TrackScore",&CandidateMu_TrackScore);		
	tree->Branch("CandidateMu_P_Range",&CandidateMu_P_Range);
	tree->Branch("CandidateMu_P_MCS",&CandidateMu_P_MCS);	
	tree->Branch("CandidateMu_Phi",&CandidateMu_Phi);
	tree->Branch("CandidateMu_CosTheta",&CandidateMu_CosTheta);
	tree->Branch("CandidateMu_Chi2_YPlane",&CandidateMu_Chi2_YPlane);
	tree->Branch("CandidateMu_ThreePlaneLogLikelihood",&CandidateMu_ThreePlaneLogLikelihood);
	tree->Branch("CandidateMu_LLR_PID",&CandidateMu_LLR_PID);
	tree->Branch("CandidateMu_ThreePlaneChi2",&CandidateMu_ThreePlaneChi2);
	tree->Branch("CandidateMu_StartContainment",&CandidateMu_StartContainment);
	tree->Branch("CandidateMu_EndContainment",&CandidateMu_EndContainment);
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
//	tree->Branch("True_CandidateMu_Px",&True_CandidateMu_Px);
//	tree->Branch("True_CandidateMu_Py",&True_CandidateMu_Py);
//	tree->Branch("True_CandidateMu_Pz",&True_CandidateMu_Pz);
	tree->Branch("True_CandidateMu_Phi",&True_CandidateMu_Phi);
	tree->Branch("True_CandidateMu_CosTheta",&True_CandidateMu_CosTheta);
	
	tree->Branch("True_CandidateMu_StartX",&True_CandidateMu_StartX);
	tree->Branch("True_CandidateMu_StartY",&True_CandidateMu_StartY);	
	tree->Branch("True_CandidateMu_StartZ",&True_CandidateMu_StartZ);
	
	tree->Branch("True_CandidateMu_EndX",&True_CandidateMu_EndX);
	tree->Branch("True_CandidateMu_EndY",&True_CandidateMu_EndY);	
	tree->Branch("True_CandidateMu_EndZ",&True_CandidateMu_EndZ);	
	
	tree->Branch("True_CandidateMu_StartContainment",&True_CandidateMu_StartContainment);
	tree->Branch("True_CandidateMu_EndContainment",&True_CandidateMu_EndContainment);

	// ------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("CandidateP_TrackScore",&CandidateP_TrackScore);
	tree->Branch("CandidateP_P_Range",&CandidateP_P_Range);
	tree->Branch("CandidateP_P_MCS",&CandidateP_P_MCS);	
	tree->Branch("CandidateP_Phi",&CandidateP_Phi);
	tree->Branch("CandidateP_CosTheta",&CandidateP_CosTheta);
	tree->Branch("CandidateP_Chi2_YPlane",&CandidateP_Chi2_YPlane);
	tree->Branch("CandidateP_ThreePlaneLogLikelihood",&CandidateP_ThreePlaneLogLikelihood);
	tree->Branch("CandidateP_LLR_PID",&CandidateP_LLR_PID);
	tree->Branch("CandidateP_ThreePlaneChi2",&CandidateP_ThreePlaneChi2);
	tree->Branch("CandidateP_StartContainment",&CandidateP_StartContainment);
	tree->Branch("CandidateP_EndContainment",&CandidateP_EndContainment);
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
//	tree->Branch("True_CandidateP_Px",&True_CandidateP_Px);
//	tree->Branch("True_CandidateP_Py",&True_CandidateP_Py);
//	tree->Branch("True_CandidateP_Pz",&True_CandidateP_Pz);
	tree->Branch("True_CandidateP_Phi",&True_CandidateP_Phi);
	tree->Branch("True_CandidateP_CosTheta",&True_CandidateP_CosTheta);
	
	tree->Branch("True_CandidateP_StartX",&True_CandidateP_StartX);
	tree->Branch("True_CandidateP_StartY",&True_CandidateP_StartY);	
	tree->Branch("True_CandidateP_StartZ",&True_CandidateP_StartZ);
	
	tree->Branch("True_CandidateP_EndX",&True_CandidateP_EndX);
	tree->Branch("True_CandidateP_EndY",&True_CandidateP_EndY);	
	tree->Branch("True_CandidateP_EndZ",&True_CandidateP_EndZ);	
	
	tree->Branch("True_CandidateP_StartContainment",&True_CandidateP_StartContainment);
	tree->Branch("True_CandidateP_EndContainment",&True_CandidateP_EndContainment);

	// -----------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("Reco_kMiss",&Reco_kMiss);
	tree->Branch("Reco_PMissMinus",&Reco_PMissMinus);
	tree->Branch("Reco_EMiss",&Reco_EMiss);
	tree->Branch("Reco_PMiss",&Reco_PMiss);	
	tree->Branch("Reco_Pt",&Reco_Pt);
	tree->Branch("Reco_DeltaAlphaT",&Reco_DeltaAlphaT);
	tree->Branch("Reco_DeltaPhiT",&Reco_DeltaPhiT);
	tree->Branch("Reco_ECal",&Reco_ECal);
	tree->Branch("Reco_EQE",&Reco_EQE);
	tree->Branch("Reco_Q2",&Reco_Q2);
	tree->Branch("Reco_DeltaPhi",&Reco_DeltaPhi);
	tree->Branch("Reco_DeltaTheta",&Reco_DeltaTheta);		
	
	tree->Branch("True_kMiss",&True_kMiss);
	tree->Branch("True_PMissMinus",&True_PMissMinus);
	tree->Branch("True_EMiss",&True_EMiss);
	tree->Branch("True_PMiss",&True_PMiss);	
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
	int TotalCounter = 0;
	int SWTriggerCounter = 0;
	int OneNuMuPFParticleCounter = 0;
	int DaughterCounter = 0;
	int TrackLikeDaughterCounter = 0;
	int MatchedTrackPFParticleCounter = 0;
	int NuFlashScoreCounter = 0;
	int FlashCounter = 0;
	int PairCounter = 0;
	int MomentumThresholdCounter = 0;
	int ContainmentCounter = 0;
	int MultipleMCTruth = 0;

	// ----------------------------------------------------------------------------------------------------------------------------------------

	TH1D* NuMuSlicesPlot = new TH1D("NuMuSlicesPlot",";# #nu slices",6,-0.5,5.5);
	TH1D* NDaughtersPlot = new TH1D("NDaughtersPlot",";# daughters",6,-0.5,5.5);
	TH1D* NTrackLikeDaughtersPlot = new TH1D("NTrackLikeDaughtersPlot",";# track-like daughters",6,-0.5,5.5);
	TH1D* NFlashPlot = new TH1D("NFlashPlot",";# flashes",6,-0.5,5.5);
	TH1D* NPairsPlot = new TH1D("NPairsPlot",";# candidate pairs",6,-0.5,5.5);

	TH1D* SamdefEventPlot = new TH1D("SamdefEventPlot",";# samdef events",1,0,1);
	SamdefEventPlot->SetBinContent(1,fChain->GetEntries());

	// ----------------------------------------------------------------------------------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;
		Long64_t ientry = LoadTree(jentry); if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;

		TotalCounter++;

		// -----------------------------------------------------------------------------------------------------------------------------------

		if ( EventPassedSwTrigger != 1) { continue; }
		SWTriggerCounter++;

		// -----------------------------------------------------------------------------------------------------------------------------------

		// Excactly 1 numu slice

		NuMuSlicesPlot->Fill(NumberNuMuPFParticles);
		if (NumberNuMuPFParticles != 1) { continue; }
		OneNuMuPFParticleCounter++;

		int NNuMuDaughters = PFParticle_NumberNuMuDaughters->at(0);

		NDaughtersPlot->Fill(NNuMuDaughters);
		if (NNuMuDaughters != 2) { continue; } // Demand exactly 2 daughter particles
		DaughterCounter++;

		int FirstPFParticleDaughter = 0;
		int SecondPFParticleDaughter = 1;

		NTrackLikeDaughtersPlot->Fill(TracksFromCurrentPFParticleStartX->at(0).size());
		if (TracksFromCurrentPFParticleStartX->at(0).size() != 2) { continue; } // Demand exactly 2 track-like daughter particles
		TrackLikeDaughterCounter++;

		// MuonPdg in this case / Pandora = Track-like object
		
		if (PFParticle_NumberNuMuDaughtersPdgCode->at(0).at(FirstPFParticleDaughter) != MuonPdg || 
			PFParticle_NumberNuMuDaughtersPdgCode->at(0).at(SecondPFParticleDaughter) != MuonPdg) { continue; }
		if (TracksFromCurrentPFParticleStartX->at(0).at(0) == -99.) { continue; }
		if (TracksFromCurrentPFParticleStartX->at(0).at(1) == -99.) { continue; }

		MatchedTrackPFParticleCounter++;

		// ----------------------------------------------------------------------------------------------------------------------------------

		// Making sure that we have NuScore & FlashScore

		if (PFParticle_NuScore->size() != 1) { continue; }
		if (PFParticle_FlashScore->size() != 1) { continue; }
		NuFlashScoreCounter++;

		NuScore = PFParticle_NuScore->at(0);
		FlashScore = PFParticle_FlashScore->at(0);

		Run = RunNumber;
		SubRun = SubRunNumber;
		Event = EventNumber;
		
		// ---------------------------------------------------------------------------------------------------------------------------------

		if (string(fWhichSample).find("Overlay") != std::string::npos) {

			double weight = EventWeight->at(0);
			Weight = weight;

			double T2Kweight = T2KEventWeight->at(0);
			T2KWeight = T2Kweight;

			ROOTinoWeight = ROOTinoEventWeight->at(0);	

			// We need the EventWeight weights only for the nominal samples, not for the detector variations

			if ( 
				fWhichSample == "Overlay9_Run1" || fWhichSample == "Overlay9_Run2" || fWhichSample == "Overlay9_Run3" || 
				fWhichSample == "Overlay9_Run4" || fWhichSample == "Overlay9_Run5" ||
				fWhichSample == "OverlayDirt9_Run1" || fWhichSample == "OverlayDirt9_Run2" || fWhichSample == "OverlayDirt9_Run3" || 
				fWhichSample == "OverlayDirt9_Run4" || fWhichSample == "OverlayDirt9_Run5"				 
			) {	

				// Genie xsection uncertainty weights
				// All_UBGenie_EventWeight has 100 universes
				// Everything else is 2 universes

				std::vector<double> Current_All_UBGenie_EventWeight((*All_UBGenie_EventWeight).begin(),(*All_UBGenie_EventWeight).begin()+100);
				All_UBGenie = Current_All_UBGenie_EventWeight;

				std::vector<double> Current_AxFFCCQEshape_UBGenie_EventWeight((*AxFFCCQEshape_UBGenie_EventWeight).begin(),(*AxFFCCQEshape_UBGenie_EventWeight).begin()+2);
				AxFFCCQEshape_UBGenie = Current_AxFFCCQEshape_UBGenie_EventWeight;

				std::vector<double> Current_DecayAngMEC_UBGenie_EventWeight((*DecayAngMEC_UBGenie_EventWeight).begin(),(*DecayAngMEC_UBGenie_EventWeight).begin()+2);
				DecayAngMEC_UBGenie = Current_DecayAngMEC_UBGenie_EventWeight;

				std::vector<double> Current_NormCCCOH_UBGenie_EventWeight((*NormCCCOH_UBGenie_EventWeight).begin(),(*NormCCCOH_UBGenie_EventWeight).begin()+2);
				NormCCCOH_UBGenie = Current_NormCCCOH_UBGenie_EventWeight;

				std::vector<double> Current_NormNCCOH_UBGenie_EventWeight((*NormNCCOH_UBGenie_EventWeight).begin(),(*NormNCCOH_UBGenie_EventWeight).begin()+2);
				NormNCCOH_UBGenie = *NormNCCOH_UBGenie_EventWeight;

	//		        std::vector<double> Current_RPA_CCQE_Reduced_UBGenie_EventWeight((*RPA_CCQE_Reduced_UBGenie_EventWeight).begin(),(*RPA_CCQE_Reduced_UBGenie_EventWeight).begin()+2);
	//			RPA_CCQE_Reduced_UBGenie = Current_RPA_CCQE_Reduced_UBGenie_EventWeight;

				std::vector<double> Current_RPA_CCQE_UBGenie_EventWeight((*RPA_CCQE_UBGenie_EventWeight).begin(),(*RPA_CCQE_UBGenie_EventWeight).begin()+2);
				RPA_CCQE_UBGenie = Current_RPA_CCQE_UBGenie_EventWeight;

				std::vector<double> Current_ThetaDelta2NRad_UBGenie_EventWeight((*ThetaDelta2NRad_UBGenie_EventWeight).begin(),(*ThetaDelta2NRad_UBGenie_EventWeight).begin()+2);
				ThetaDelta2NRad_UBGenie = Current_ThetaDelta2NRad_UBGenie_EventWeight;

				std::vector<double> Current_Theta_Delta2Npi_UBGenie_EventWeight((*Theta_Delta2Npi_UBGenie_EventWeight).begin(),(*Theta_Delta2Npi_UBGenie_EventWeight).begin()+2);
				Theta_Delta2Npi_UBGenie = Current_Theta_Delta2Npi_UBGenie_EventWeight;

				std::vector<double> Current_VecFFCCQEshape_UBGenie_EventWeight((*VecFFCCQEshape_UBGenie_EventWeight).begin(),(*VecFFCCQEshape_UBGenie_EventWeight).begin()+2);
				VecFFCCQEshape_UBGenie = Current_VecFFCCQEshape_UBGenie_EventWeight;

				std::vector<double> Current_XSecShape_CCMEC_UBGenie_EventWeight((*XSecShape_CCMEC_UBGenie_EventWeight).begin(),(*XSecShape_CCMEC_UBGenie_EventWeight).begin()+2);
				XSecShape_CCMEC_UBGenie = Current_XSecShape_CCMEC_UBGenie_EventWeight;

				// Flux uncertainty weights
				// All of them have 1000 universes
				// Limit them to MultiSimSize

				int MultiSimSize = 100;

				std::vector<double> Current_expskin_FluxUnisim_EventWeight((*expskin_FluxUnisim_EventWeight).begin(),(*expskin_FluxUnisim_EventWeight).begin()+MultiSimSize);
				expskin_FluxUnisim = Current_expskin_FluxUnisim_EventWeight;

				std::vector<double> Current_horncurrent_FluxUnisim_EventWeight((*horncurrent_FluxUnisim_EventWeight).begin(),(*horncurrent_FluxUnisim_EventWeight).begin()+MultiSimSize);
				horncurrent_FluxUnisim = Current_horncurrent_FluxUnisim_EventWeight;

				std::vector<double> Current_kminus_PrimaryHadronNormalization_EventWeight((*kminus_PrimaryHadronNormalization_EventWeight).begin(),\
							(*kminus_PrimaryHadronNormalization_EventWeight).begin()+MultiSimSize);
				kminus_PrimaryHadronNormalization = Current_kminus_PrimaryHadronNormalization_EventWeight;

				std::vector<double> Current_kplus_PrimaryHadronFeynmanScaling_EventWeight((*kplus_PrimaryHadronFeynmanScaling_EventWeight).begin(),\
							(*kplus_PrimaryHadronFeynmanScaling_EventWeight).begin()+MultiSimSize);
				kplus_PrimaryHadronFeynmanScaling = Current_kplus_PrimaryHadronFeynmanScaling_EventWeight;

				std::vector<double> Current_kzero_PrimaryHadronSanfordWang_EventWeight((*kzero_PrimaryHadronSanfordWang_EventWeight).begin(),\
							(*kzero_PrimaryHadronSanfordWang_EventWeight).begin()+MultiSimSize);
				kzero_PrimaryHadronSanfordWang = Current_kzero_PrimaryHadronSanfordWang_EventWeight;

				std::vector<double> Current_nucleoninexsec_FluxUnisim_EventWeight((*nucleoninexsec_FluxUnisim_EventWeight).begin(),\
							(*nucleoninexsec_FluxUnisim_EventWeight).begin()+MultiSimSize);
				nucleoninexsec_FluxUnisim = Current_nucleoninexsec_FluxUnisim_EventWeight;

				std::vector<double> Current_nucleonqexsec_FluxUnisim_EventWeight((*nucleonqexsec_FluxUnisim_EventWeight).begin(),\
							(*nucleonqexsec_FluxUnisim_EventWeight).begin()+MultiSimSize);
				nucleonqexsec_FluxUnisim = Current_nucleoninexsec_FluxUnisim_EventWeight;

				std::vector<double> Current_nucleontotxsec_FluxUnisim_EventWeight((*nucleontotxsec_FluxUnisim_EventWeight).begin(),\
							(*nucleontotxsec_FluxUnisim_EventWeight).begin()+MultiSimSize);
				nucleontotxsec_FluxUnisim = Current_nucleontotxsec_FluxUnisim_EventWeight;

				std::vector<double> Current_piminus_PrimaryHadronSWCentralSplineVariation_EventWeight((*piminus_PrimaryHadronSWCentralSplineVariation_EventWeight).begin(),\
							(*piminus_PrimaryHadronSWCentralSplineVariation_EventWeight).begin()+MultiSimSize);
				piminus_PrimaryHadronSWCentralSplineVariation = Current_piminus_PrimaryHadronSWCentralSplineVariation_EventWeight;

				std::vector<double> Current_pioninexsec_FluxUnisim_EventWeight((*pioninexsec_FluxUnisim_EventWeight).begin(),\
							(*pioninexsec_FluxUnisim_EventWeight).begin()+MultiSimSize);
				pioninexsec_FluxUnisim = Current_pioninexsec_FluxUnisim_EventWeight;

				std::vector<double> Current_pionqexsec_FluxUnisim_EventWeight((*pionqexsec_FluxUnisim_EventWeight).begin(),\
							(*pionqexsec_FluxUnisim_EventWeight).begin()+MultiSimSize);
				pionqexsec_FluxUnisim = Current_pionqexsec_FluxUnisim_EventWeight;

				std::vector<double> Current_piontotxsec_FluxUnisim_EventWeight((*piontotxsec_FluxUnisim_EventWeight).begin(),\
							(*piontotxsec_FluxUnisim_EventWeight).begin()+MultiSimSize);
				piontotxsec_FluxUnisim = Current_pionqexsec_FluxUnisim_EventWeight;

				std::vector<double> Current_piplus_PrimaryHadronSWCentralSplineVariation_EventWeight((*piplus_PrimaryHadronSWCentralSplineVariation_EventWeight).begin(),\
							(*piplus_PrimaryHadronSWCentralSplineVariation_EventWeight).begin()+MultiSimSize);
				piplus_PrimaryHadronSWCentralSplineVariation = Current_pionqexsec_FluxUnisim_EventWeight;

				// G4 uncertainty weights
				// They all have 1000 universes
				// Limit them to 100

				std::vector<double> Current_reinteractions_piminus_Geant4_EventWeight((*reinteractions_piminus_Geant4_EventWeight).begin(),\
							(*reinteractions_piminus_Geant4_EventWeight).begin()+MultiSimSize);
				reinteractions_piminus_Geant4 = Current_reinteractions_piminus_Geant4_EventWeight;

				std::vector<double> Current_reinteractions_piplus_Geant4_EventWeight((*reinteractions_piplus_Geant4_EventWeight).begin(),\
							(*reinteractions_piplus_Geant4_EventWeight).begin()+MultiSimSize);
				reinteractions_piplus_Geant4 = Current_reinteractions_piplus_Geant4_EventWeight;

				std::vector<double> Current_reinteractions_proton_Geant4_EventWeight((*reinteractions_proton_Geant4_EventWeight).begin(),\
							(*reinteractions_proton_Geant4_EventWeight).begin()+MultiSimSize);
				reinteractions_proton_Geant4 = Current_reinteractions_proton_Geant4_EventWeight;

		//		xsr_scc_Fa3_SCC = *xsr_scc_Fa3_SCC_EventWeight;
		//		xsr_scc_Fv3_SCC = *xsr_scc_Fv3_SCC_EventWeight;

			}

		}

		// ----------------------------------------------------------------------------------------------------------------------------------

		// Beam Flashes

		NFlashPlot->Fill(NumberFlashesBeam);
		if (NumberFlashesBeam != 1) { continue; }
		FlashCounter++;

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

		// Hits for vertex activity

		std::vector<double> HitsIntegral; HitsIntegral.clear();
		std::vector<double> HitsPeakTime; HitsPeakTime.clear();
		std::vector<double> HitsWire; HitsWire.clear();
		std::vector<double> HitsPlane; HitsPlane.clear();

		for (int WhichHit = 0; WhichHit < NumberHits; WhichHit++) {

			HitsIntegral.push_back(Hit_Integral->at(WhichHit));
			HitsPeakTime.push_back(Hit_PeakTime->at(WhichHit));
			HitsWire.push_back(Hit_Wire->at(WhichHit));
			HitsPlane.push_back(Hit_WireID_Plane->at(WhichHit));
	
		}

		// --------------------------------------------------------------------------------------------------------------------------------

		// Tracks

		VectorTrackStart.clear();
		VectorTrackEnd.clear();

		std::vector<int> FirstTrackIndex; FirstTrackIndex.clear();
		std::vector<int> SecondTrackIndex; SecondTrackIndex.clear();
		std::vector<double> TrackPairDistance; TrackPairDistance.clear();
		std::vector<TVector3> TrackPairVertexPosition; TrackPairVertexPosition.clear();

		// Hit (Track Associated) quantities

		std::vector<double> TrackAssHits_Integral; TrackAssHits_Integral.clear();
		std::vector<double> TrackAssHits_PeakTime; TrackAssHits_PeakTime.clear();
		std::vector<double> TrackAssHits_Wire; TrackAssHits_Wire.clear();
		std::vector<double> TrackAssHits_Plane; TrackAssHits_Plane.clear();

		// Wires & Ticks

//		std::vector<std::vector<double> > TrackPlaneID; TrackPlaneID.clear();
//		std::vector<std::vector<double> > TrackStartWire; TrackStartWire.clear();
//		std::vector<std::vector<double> > TrackStartTime; TrackStartTime.clear();
//		std::vector<std::vector<double> > TrackEndWire; TrackEndWire.clear();
//		std::vector<std::vector<double> > TrackEndTime; TrackEndTime.clear();

		std::vector<TVector3> VertexPosition; VertexPosition.clear();
		std::vector<TVector3> VertexPlane; VertexPlane.clear();
		std::vector<TVector3> VertexWire; VertexWire.clear();
		std::vector<TVector3> VertexTime; VertexTime.clear();

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

				// Track Associated Hits

				for (int WhichAssHit = 0; WhichAssHit < Track_NumberAssHits->at(WhichTrack); WhichAssHit++) {

					TrackAssHits_Integral.push_back(Track_AssHit_Integral->at(WhichTrack).at(WhichAssHit));
					TrackAssHits_PeakTime.push_back(Track_AssHit_PeakTime->at(WhichTrack).at(WhichAssHit));
					TrackAssHits_Wire.push_back(Track_AssHit_Wire->at(WhichTrack).at(WhichAssHit));
					TrackAssHits_Plane.push_back(Track_AssHit_WireID_Plane->at(WhichTrack).at(WhichAssHit));

				}

				// Wires & Ticks

//				TrackPlaneID.push_back(Track_PlaneID->at(WhichTrack));
//				TrackStartWire.push_back(Track_Start_Wire->at(WhichTrack));
//				TrackEndWire.push_back(Track_End_Wire->at(WhichTrack));
//				TrackStartTime.push_back(Track_Start_Time->at(WhichTrack));
//				TrackEndTime.push_back(Track_End_Time->at(WhichTrack));

				if (Track_StartX->at(WhichTrack) == TracksFromCurrentPFParticleStartX->at(0).at(FirstPFParticleDaughter) ) {

					TVector3 VertexPositionVector(VertexFromCurrentPFParticlePositionX->at(0).at(0),VertexFromCurrentPFParticlePositionY->at(0).at(0),VertexFromCurrentPFParticlePositionZ->at(0).at(0));
					TVector3 VertexPlaneVector(VertexFromCurrentPFParticlePlaneX->at(0).at(0),VertexFromCurrentPFParticlePlaneY->at(0).at(0),VertexFromCurrentPFParticlePlaneZ->at(0).at(0));
					TVector3 VertexWireVector(VertexFromCurrentPFParticleWireX->at(0).at(0),VertexFromCurrentPFParticleWireY->at(0).at(0),VertexFromCurrentPFParticleWireZ->at(0).at(0));
					TVector3 VertexTimeVector(VertexFromCurrentPFParticleTimeX->at(0).at(0),VertexFromCurrentPFParticleTimeY->at(0).at(0),VertexFromCurrentPFParticleTimeZ->at(0).at(0));

					VertexPosition.push_back( VertexPositionVector );
					VertexPlane.push_back( VertexPlaneVector );
					VertexWire.push_back( VertexWireVector );
					VertexTime.push_back( VertexTimeVector );

				} else {


					TVector3 VertexPositionVector(VertexFromCurrentPFParticlePositionX->at(0).at(0),VertexFromCurrentPFParticlePositionY->at(0).at(0),VertexFromCurrentPFParticlePositionZ->at(0).at(1));
					TVector3 VertexPlaneVector(VertexFromCurrentPFParticlePlaneX->at(0).at(0),VertexFromCurrentPFParticlePlaneY->at(0).at(0),VertexFromCurrentPFParticlePlaneZ->at(0).at(1));
					TVector3 VertexWireVector(VertexFromCurrentPFParticleWireX->at(0).at(0),VertexFromCurrentPFParticleWireY->at(0).at(0),VertexFromCurrentPFParticleWireZ->at(0).at(1));
					TVector3 VertexTimeVector(VertexFromCurrentPFParticleTimeX->at(0).at(0),VertexFromCurrentPFParticleTimeY->at(0).at(0),VertexFromCurrentPFParticleTimeZ->at(0).at(1));

					VertexPosition.push_back( VertexPositionVector );
					VertexPlane.push_back( VertexPlaneVector );
					VertexWire.push_back( VertexWireVector );
					VertexTime.push_back( VertexTimeVector );

				}

			}
			
		} // end of the loop over the recob::Tracks

		// -----------------------------------------------------------------------------------------------------------------------------------

		int NCandidateTrackPairs = FirstTrackIndex.size();

		NPairsPlot->Fill(NCandidateTrackPairs);
		if (NCandidateTrackPairs != 1) { continue; }
		PairCounter++;

		double fTrackPairDistance = (VectorTrackStart.at(0) - VectorTrackStart.at(1)).Mag();
		TrackPairDistance.push_back(fTrackPairDistance);

//		if ( VertexPosition.at(0) != VertexPosition.at(1) ) { cout << "Different pandora vertices !!!" << endl; continue;}
//		TVector3 VertexPositionV3 = VertexPosition.at(0);
//		TVector3 VertexPositionV3 = (VectorTrackStart.at(0) + VectorTrackStart.at(1))*0.5;
		TVector3 VertexPositionV3 = VertexPosition.at(0);
		TrackPairVertexPosition.push_back(VertexPositionV3);

		// -----------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------

		// Cosmic rejection paper for vertex activity
		// https://arxiv.org/abs/1812.05679

		// -----------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------

		// Charge deposition in box from track associated hits in a Wires x Ticks = 50 x 100 box

		Box_Tools TrackChargeBox_50x100(TrackAssHits_Integral,TrackAssHits_PeakTime,TrackAssHits_Wire,TrackAssHits_Plane,50,100,VertexWire.at(0),VertexTime.at(0));
		double TrackChargeBox_Plane0_50x100 = TrackChargeBox_50x100.GetChargeDepPlane0();
		double TrackChargeBox_Plane1_50x100 = TrackChargeBox_50x100.GetChargeDepPlane1();
		double TrackChargeBox_Plane2_50x100 = TrackChargeBox_50x100.GetChargeDepPlane2();

		// Charge deposition in box from all hits in a Wires x Ticks = 50 x 100 box

		Box_Tools AllHitsChargeBox_50x100(HitsIntegral,HitsPeakTime,HitsWire,HitsPlane,50,100,VertexWire.at(0),VertexTime.at(0));
		double AllHitsChargeBox_Plane0_50x100 = AllHitsChargeBox_50x100.GetChargeDepPlane0();
		double AllHitsChargeBox_Plane1_50x100 = AllHitsChargeBox_50x100.GetChargeDepPlane1();
		double AllHitsChargeBox_Plane2_50x100 = AllHitsChargeBox_50x100.GetChargeDepPlane2();

		// Fractional charge on each plane & charge deposition in sphere  in a Wires x Ticks = 50 x 100 box

		double FracChargePlane0_50x100 = -99.;
		double FracChargePlane1_50x100 = -99.;
		double FracChargePlane2_50x100 = -99.;

                if (AllHitsChargeBox_Plane0_50x100 > 0 && AllHitsChargeBox_Plane1_50x100 > 0 && AllHitsChargeBox_Plane2_50x100 > 0) {

                        FracChargePlane0_50x100 = TrackChargeBox_Plane0_50x100 / AllHitsChargeBox_Plane0_50x100;
                        FracChargePlane1_50x100 = TrackChargeBox_Plane1_50x100 / AllHitsChargeBox_Plane1_50x100;
                        FracChargePlane2_50x100 = TrackChargeBox_Plane2_50x100 / AllHitsChargeBox_Plane2_50x100;

                }

		double SphereDeposition_50x100 = Sphere(FracChargePlane0_50x100,FracChargePlane1_50x100,FracChargePlane2_50x100);	

		// -----------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------

		// Loop over the candidate track pairs

		VertexActivity_50x100.clear();

		CandidateMuP_Distance.clear();
		Vertex_X.clear();
		Vertex_Y.clear();
		Vertex_Z.clear();

//		CandidateMu_Mode.clear();
		CandidateMu_TrackScore.clear();								
		CandidateMu_P_Range.clear();
		CandidateMu_P_MCS.clear();		
		CandidateMu_Phi.clear();
		CandidateMu_CosTheta.clear();
		CandidateMu_Chi2_YPlane.clear();
		CandidateMu_ThreePlaneLogLikelihood.clear();
		CandidateMu_LLR_PID.clear();
		CandidateMu_ThreePlaneChi2.clear();
		CandidateMu_StartContainment.clear();
		CandidateMu_EndContainment.clear();
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
//		True_CandidateMu_Px.clear();
//		True_CandidateMu_Py.clear();
//		True_CandidateMu_Pz.clear();
		True_CandidateMu_Phi.clear();
		True_CandidateMu_CosTheta.clear();
		
		True_CandidateMu_StartX.clear();
		True_CandidateMu_StartY.clear();
		True_CandidateMu_StartZ.clear();
		
		True_CandidateMu_EndX.clear();
		True_CandidateMu_EndY.clear();
		True_CandidateMu_EndZ.clear();				
		
		True_CandidateMu_StartContainment.clear();
		True_CandidateMu_EndContainment.clear();

		// ---------------------------------------------------------------------------------------------------------------------------------

//		CandidateP_Mode.clear();		
		CandidateP_TrackScore.clear();
		CandidateP_P_Range.clear();
		CandidateP_P_MCS.clear();		
		CandidateP_Phi.clear();
		CandidateP_CosTheta.clear();
		CandidateP_Chi2_YPlane.clear();
		CandidateP_ThreePlaneLogLikelihood.clear();
		CandidateP_LLR_PID.clear();
		CandidateP_ThreePlaneChi2.clear();
		CandidateP_StartContainment.clear();
		CandidateP_EndContainment.clear();
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
//		True_CandidateP_Px.clear();
//		True_CandidateP_Py.clear();
//		True_CandidateP_Pz.clear();
		True_CandidateP_Phi.clear();
		True_CandidateP_CosTheta.clear();
		
		True_CandidateP_StartX.clear();
		True_CandidateP_StartY.clear();
		True_CandidateP_StartZ.clear();
		
		True_CandidateP_EndX.clear();
		True_CandidateP_EndY.clear();
		True_CandidateP_EndZ.clear();		
		
		True_CandidateP_StartContainment.clear();
		True_CandidateP_EndContainment.clear();

		// -----------------------------------------------------------------------------------------------------------------------------

		Reco_kMiss.clear();
		Reco_EMiss.clear();
		Reco_PMissMinus.clear();
		Reco_PMiss.clear();	
		Reco_Pt.clear();
		Reco_DeltaAlphaT.clear();
		Reco_DeltaPhiT.clear();
		Reco_ECal.clear();
		Reco_EQE.clear();
		Reco_Q2.clear();
		Reco_DeltaPhi.clear();
		Reco_DeltaTheta.clear();				
		
		True_kMiss.clear();
		True_EMiss.clear();
		True_PMissMinus.clear();
		True_PMiss.clear();		
		True_Pt.clear();
		True_DeltaAlphaT.clear();
		True_DeltaPhiT.clear();
		True_ECal.clear();
		True_EQE.clear();
		True_Q2.clear();
		True_DeltaPhi.clear();
		True_DeltaTheta.clear();															

		// -----------------------------------------------------------------------------------------------------------------------------

		bool ParticlesBelowThreshold = false;
		bool UncontainedParticles = false;

		int EventCandidatePairs = 0;

		for (int WhichTrackPair = 0; WhichTrackPair < NCandidateTrackPairs; WhichTrackPair++) {

			ParticlesBelowThreshold = false;
			UncontainedParticles = false;

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

			// Track Score

			int MuonInPair = -99, ProtonInPair = -99;

			if (CandidateMuonTrackIndex == FirstCandidateTrackIndex) { MuonInPair = 0; ProtonInPair = 1; }
			else { MuonInPair = 1; ProtonInPair = 0; }

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
			bool CandidateProtonTrackStartContainment = tools.inFVVector(CandidateProtonTrackStart);
			bool CandidateProtonTrackEndContainment = tools.inFVVector(CandidateProtonTrackEnd);			
			
			// ---------------------------------------------------------------------------------------------------------------------		

			VertexActivity_50x100.push_back(SphereDeposition_50x100);	

			CandidateMuP_Distance.push_back(TrackPairDistance.at(WhichTrackPair));	
			Vertex_X.push_back(TrackPairVertexPosition.at(WhichTrackPair).X());
			Vertex_Y.push_back(TrackPairVertexPosition.at(WhichTrackPair).Y());
			Vertex_Z.push_back(TrackPairVertexPosition.at(WhichTrackPair).Z());

			// ---------------------------------------------------------------------------------------------------------------------

			// Muon

			double CandidateMuonTrack_Momentum = -99.;
			double CandidateMuonTrack_Momentum_MCS_MeV = -99.;
			double CandidateMuonTrack_E_GeV = -99.;
			double CalCandidateMu_ThreePlaneChi2 = ThreePlaneChi2(CandidateMuonTrackStart,CandidateMuonTrackEnd,
								Track_ParticleId_ProtonScore_Chi2_UPlane->at(CandidateMuonTrackIndex),
								Track_ParticleId_ProtonScore_Chi2_VPlane->at(CandidateMuonTrackIndex),
								Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateMuonTrackIndex));

			if (CandidateMuonTrackStartContainment == false) { UncontainedParticles = true; } 

			if (CandidateMuonTrackStartContainment == true && CandidateMuonTrackEndContainment == true) {

				CandidateMuonTrack_Momentum = Track_Momentum_Range_Muon->at(CandidateMuonTrackIndex); // GeV/c

			} else {

				CandidateMuonTrack_Momentum = Track_Momentum_MCS->at(CandidateMuonTrackIndex); // GeV/c

			}

			if (CandidateMuonTrack_Momentum < ArrayNBinsMuonMomentum[0]) { ParticlesBelowThreshold = true; } 

			CandidateMuonTrack_E_GeV = TMath::Sqrt( TMath::Power(CandidateMuonTrack_Momentum,2.) + TMath::Power(MuonMass_GeV,2.)); // GeV/c

			CandidateMu_TrackScore.push_back(TracksFromCurrentPFParticleTrackScore->at(0).at(MuonInPair));	
			CandidateMu_P_Range.push_back(Track_Momentum_Range_Muon->at(CandidateMuonTrackIndex));						
			CandidateMu_P_MCS.push_back(Track_Momentum_MCS->at(CandidateMuonTrackIndex));
			CandidateMu_Phi.push_back(Track_Phi->at(CandidateMuonTrackIndex) * 180./ TMath::Pi()); // deg
			CandidateMu_CosTheta.push_back(CandidateMuonTrackCosTheta);
			CandidateMu_Chi2_YPlane.push_back(Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateMuonTrackIndex));
			CandidateMu_ThreePlaneLogLikelihood.push_back(log(Track_ParticleId_ProtonScore_ThreePlanePID->at(CandidateMuonTrackIndex)));
			CandidateMu_LLR_PID.push_back(Track_LLR_PID->at(CandidateMuonTrackIndex));
			CandidateMu_ThreePlaneChi2.push_back(CalCandidateMu_ThreePlaneChi2);
			CandidateMu_StartContainment.push_back(CandidateMuonTrackStartContainment);
			CandidateMu_EndContainment.push_back(CandidateMuonTrackEndContainment);
			CandidateMu_Length.push_back(CandidateMuonTrackLength);
			CandidateMu_StartX.push_back(Track_StartX->at(CandidateMuonTrackIndex));
			CandidateMu_StartY.push_back(Track_StartY->at(CandidateMuonTrackIndex));
			CandidateMu_StartZ.push_back(Track_StartZ->at(CandidateMuonTrackIndex));
			CandidateMu_EndX.push_back(Track_EndX->at(CandidateMuonTrackIndex));
			CandidateMu_EndY.push_back(Track_EndY->at(CandidateMuonTrackIndex));
			CandidateMu_EndZ.push_back(Track_EndZ->at(CandidateMuonTrackIndex));								

			// --------------------------------------------------------------------------------------------------------------------------

			// Proton

			double CandidateProtonTrack_Momentum = -99.;
			double CandidateProtonTrack_E_GeV = -99.;
			double CalCandidateP_ThreePlaneChi2 = ThreePlaneChi2(CandidateProtonTrackStart,CandidateProtonTrackEnd,
								Track_ParticleId_ProtonScore_Chi2_UPlane->at(CandidateProtonTrackIndex),
								Track_ParticleId_ProtonScore_Chi2_VPlane->at(CandidateProtonTrackIndex),
								Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateProtonTrackIndex));

			CandidateProtonTrack_Momentum = Track_Momentum_Range_Proton->at(CandidateProtonTrackIndex); // GeV/c

			if (CandidateProtonTrackStartContainment == false) { UncontainedParticles = true; } 
			if (CandidateProtonTrack_Momentum < ArrayNBinsProtonMomentum[0]) { ParticlesBelowThreshold = true; } 

			CandidateProtonTrack_E_GeV = TMath::Sqrt( TMath::Power(CandidateProtonTrack_Momentum,2.) + TMath::Power(ProtonMass_GeV,2.) ); // GeV/c

			CandidateP_TrackScore.push_back(TracksFromCurrentPFParticleTrackScore->at(0).at(ProtonInPair));
			CandidateP_P_Range.push_back(Track_Momentum_Range_Proton->at(CandidateProtonTrackIndex));
			CandidateP_P_MCS.push_back(Track_Momentum_MCS->at(CandidateProtonTrackIndex));			
			CandidateP_Phi.push_back(Track_Phi->at(CandidateProtonTrackIndex) * 180./ TMath::Pi()); // deg
			CandidateP_CosTheta.push_back(CandidateProtonTrackCosTheta);
			CandidateP_Chi2_YPlane.push_back(Track_ParticleId_ProtonScore_Chi2_YPlane->at(CandidateProtonTrackIndex));
			CandidateP_ThreePlaneLogLikelihood.push_back(log(Track_ParticleId_ProtonScore_ThreePlanePID->at(CandidateProtonTrackIndex)));
			CandidateP_LLR_PID.push_back(Track_LLR_PID->at(CandidateProtonTrackIndex));
			CandidateP_ThreePlaneChi2.push_back(CalCandidateP_ThreePlaneChi2);
			CandidateP_StartContainment.push_back(CandidateProtonTrackStartContainment);
			CandidateP_EndContainment.push_back(CandidateProtonTrackEndContainment);
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
			TVector3CandidateMuon.SetMag(CandidateMuonTrack_Momentum);
			TVector3CandidateMuon.SetTheta(TMath::ACos(CandidateMuonTrackCosTheta));
			TVector3CandidateMuon.SetPhi(Track_Phi->at(CandidateMuonTrackIndex));			

			TVector3 TVector3CandidateProton(-1,-1,-1);
			TVector3CandidateProton.SetMag(CandidateProtonTrack_Momentum);
			TVector3CandidateProton.SetTheta(TMath::ACos(CandidateProtonTrackCosTheta));
			TVector3CandidateProton.SetPhi(Track_Phi->at(CandidateProtonTrackIndex));

			STV_Tools reco_stv_tool(TVector3CandidateMuon,TVector3CandidateProton,CandidateMuonTrack_E_GeV,CandidateProtonTrack_E_GeV);

			Reco_kMiss.push_back(reco_stv_tool.ReturnkMiss());
			Reco_EMiss.push_back(reco_stv_tool.ReturnEMiss());
			Reco_PMissMinus.push_back(reco_stv_tool.ReturnPMissMinus());
			Reco_PMiss.push_back(reco_stv_tool.ReturnPMiss());
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

				double CandidateMuonPx = Track_MCParticle_Px->at(CandidateMuonTrackIndex);
				double CandidateMuonPy = Track_MCParticle_Py->at(CandidateMuonTrackIndex);
				double CandidateMuonPz = Track_MCParticle_Pz->at(CandidateMuonTrackIndex);
				
				double CandidateMuonStartX = Track_MCParticle_Vx->at(CandidateMuonTrackIndex);
				double CandidateMuonStartY = Track_MCParticle_Vy->at(CandidateMuonTrackIndex);
				double CandidateMuonStartZ = Track_MCParticle_Vz->at(CandidateMuonTrackIndex);
				
				double CandidateMuonEndX = Track_MCParticle_EndX->at(CandidateMuonTrackIndex);
				double CandidateMuonEndY = Track_MCParticle_EndY->at(CandidateMuonTrackIndex);
				double CandidateMuonEndZ = Track_MCParticle_EndZ->at(CandidateMuonTrackIndex);						

				TVector3 TrueCandidateMuonTrackStart(CandidateMuonStartX,CandidateMuonStartY,CandidateMuonStartZ);
				TVector3 TrueCandidateMuonTrackEnd(CandidateMuonEndX,CandidateMuonEndY,CandidateMuonEndZ);
//				TVector3 TrueCandidateMuonChange = TrueCandidateMuonTrackEnd - TrueCandidateMuonTrackStart;
				TVector3 TrueCandidateMuonP(CandidateMuonPx,CandidateMuonPy,CandidateMuonPz);

				bool TrueCandidateMuonTrackStartContainment = tools.inFVVector(TrueCandidateMuonTrackStart);
				bool TrueCandidateMuonTrackEndContainment = tools.inFVVector(TrueCandidateMuonTrackEnd);

				double TrueCandidateMuonTrackPhi = TrueCandidateMuonP.Phi(); // rad
				double TrueCandidateMuonTrackPhi_Deg = TrueCandidateMuonTrackPhi * 180./ TMath::Pi(); // deg
				double TrueCandidateMuonTrackTheta = TrueCandidateMuonP.Theta(); // rad
				double TrueCandidateMuonTrackCosTheta = TrueCandidateMuonP.CosTheta();
//				double TrueCandidateMuonTrackLength = TrueCandidateMuonChange.Mag(); // cm

				double TrueCandidateMuonTrackMomentum_GeV = Track_MCParticle_P->at(CandidateMuonTrackIndex); // GeV
//				double TrueCandidateMuonTrackMomentum_MeV = 1000.* TrueCandidateMuonTrackMomentum_GeV; // MeV
//				double TrueCandidateMuonTrack_KE_MeV = tools.PToKE(MuonPdg,TrueCandidateMuonTrackMomentum_MeV); // MeV
//				double TrueCandidateMuonTrack_KE_GeV = TrueCandidateMuonTrack_KE_MeV / 1000.; // GeV
//				double TrueCandidateMuonTrack_E_GeV = TrueCandidateMuonTrack_KE_GeV + MuonMass_GeV; // GeV
				double TrueCandidateMuonTrack_E_GeV = TMath::Sqrt( TMath::Power(TrueCandidateMuonTrackMomentum_GeV,2.) + TMath::Power(MuonMass_GeV,2.) ); // GeV

				True_CandidateMu_P.push_back(TrueCandidateMuonTrackMomentum_GeV);
//				True_CandidateMu_Px.push_back(CandidateMuonPx);
//				True_CandidateMu_Py.push_back(CandidateMuonPy);
//				True_CandidateMu_Pz.push_back(CandidateMuonPz);
				True_CandidateMu_Phi.push_back(TrueCandidateMuonTrackPhi_Deg); // deg
				True_CandidateMu_CosTheta.push_back(TrueCandidateMuonTrackCosTheta);
				
				True_CandidateMu_StartX.push_back(CandidateMuonStartX);
				True_CandidateMu_StartY.push_back(CandidateMuonStartY);
				True_CandidateMu_StartZ.push_back(CandidateMuonStartZ);
				
				True_CandidateMu_EndX.push_back(CandidateMuonEndX);
				True_CandidateMu_EndY.push_back(CandidateMuonEndY);
				True_CandidateMu_EndZ.push_back(CandidateMuonEndZ);				
				
				True_CandidateMu_StartContainment.push_back(TrueCandidateMuonTrackStartContainment);
				True_CandidateMu_EndContainment.push_back(TrueCandidateMuonTrackEndContainment);

				// --------------------------------------------------------------------------------------------------------------------

				CandidateP_MCParticle_Pdg.push_back(Track_MCParticle_PdgCode->at(CandidateProtonTrackIndex));
				CandidateP_MCParticle_Purity.push_back(Track_MCParticle_Purity->at(CandidateProtonTrackIndex));
//				CandidateP_Mode.push_back(Track_MCParticle_Mode->at(CandidateProtonTrackIndex));

				double CandidateProtonPx = Track_MCParticle_Px->at(CandidateProtonTrackIndex);
				double CandidateProtonPy = Track_MCParticle_Py->at(CandidateProtonTrackIndex);
				double CandidateProtonPz = Track_MCParticle_Pz->at(CandidateProtonTrackIndex);
				
				double CandidateProtonStartX = Track_MCParticle_Vx->at(CandidateProtonTrackIndex);
				double CandidateProtonStartY = Track_MCParticle_Vy->at(CandidateProtonTrackIndex);
				double CandidateProtonStartZ = Track_MCParticle_Vz->at(CandidateProtonTrackIndex);
				
				double CandidateProtonEndX = Track_MCParticle_EndX->at(CandidateProtonTrackIndex);
				double CandidateProtonEndY = Track_MCParticle_EndY->at(CandidateProtonTrackIndex);
				double CandidateProtonEndZ = Track_MCParticle_EndZ->at(CandidateProtonTrackIndex);						

				TVector3 TrueCandidateProtonTrackStart(CandidateProtonStartX,CandidateProtonStartY,CandidateProtonStartZ);
				TVector3 TrueCandidateProtonTrackEnd(CandidateProtonEndX,CandidateProtonEndY,CandidateProtonEndZ);
//				TVector3 TrueCandidateProtonChange = TrueCandidateProtonTrackEnd - TrueCandidateProtonTrackStart;
				TVector3 TrueCandidateProtonP(CandidateProtonPx,CandidateProtonPy,CandidateProtonPz);

				bool TrueCandidateProtonTrackStartContainment = tools.inFVVector(TrueCandidateProtonTrackStart);
				bool TrueCandidateProtonTrackEndContainment = tools.inFVVector(TrueCandidateProtonTrackEnd);

				double TrueCandidateProtonTrackPhi = TrueCandidateProtonP.Phi(); // rad
				double TrueCandidateProtonTrackPhi_Deg = TrueCandidateProtonTrackPhi * 180./ TMath::Pi(); // deg
				double TrueCandidateProtonTrackTheta = TrueCandidateProtonP.Theta(); // rad
				double TrueCandidateProtonTrackCosTheta = TrueCandidateProtonP.CosTheta();
//				double TrueCandidateProtonTrackLength = TrueCandidateProtonChange.Mag(); // cm

				double TrueCandidateProtonTrackMomentum_GeV = Track_MCParticle_P->at(CandidateProtonTrackIndex); // GeV
//				double TrueCandidateProtonTrackMomentum_MeV = 1000.* TrueCandidateProtonTrackMomentum_GeV; // MeV
//				double TrueCandidateProtonTrack_KE_MeV = tools.PToKE(ProtonPdg,TrueCandidateProtonTrackMomentum_MeV); // MeV
//				double TrueCandidateProtonTrack_KE_GeV = TrueCandidateProtonTrack_KE_MeV / 1000.; // GeV
//				double TrueCandidateProtonTrack_E_GeV = TrueCandidateProtonTrack_KE_GeV + ProtonMass_GeV; // GeV
				double TrueCandidateProtonTrack_E_GeV = TMath::Sqrt( TMath::Power(TrueCandidateProtonTrackMomentum_GeV,2.) + TMath::Power(ProtonMass_GeV,2.) ); // GeV

				True_CandidateP_P.push_back(TrueCandidateProtonTrackMomentum_GeV);
				True_CandidateP_Phi.push_back(TrueCandidateProtonTrackPhi_Deg); // deg
				True_CandidateP_CosTheta.push_back(TrueCandidateProtonTrackCosTheta);
				
				True_CandidateP_StartX.push_back(CandidateProtonStartX);
				True_CandidateP_StartY.push_back(CandidateProtonStartY);
				True_CandidateP_StartZ.push_back(CandidateProtonStartZ);
				
				True_CandidateP_EndX.push_back(CandidateProtonEndX);
				True_CandidateP_EndY.push_back(CandidateProtonEndY);
				True_CandidateP_EndZ.push_back(CandidateProtonEndZ);				
				
				True_CandidateP_StartContainment.push_back(TrueCandidateProtonTrackStartContainment);
				True_CandidateP_EndContainment.push_back(TrueCandidateProtonTrackEndContainment);
				
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

				True_kMiss.push_back(true_stv_tool.ReturnkMiss());
				True_EMiss.push_back(true_stv_tool.ReturnEMiss());
				True_PMissMinus.push_back(true_stv_tool.ReturnPMissMinus());
				True_PMiss.push_back(true_stv_tool.ReturnPMiss());
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

			EventCandidatePairs++;

		} // End of the loop over the candidate track pairs

		// If the candidate pair includes particles below threshold
		// there is no point in storing the event

		if (ParticlesBelowThreshold) { continue; }

		MomentumThresholdCounter++;

		if (UncontainedParticles) { continue; }

		ContainmentCounter++;

		EventCounter += EventCandidatePairs;

		// ------------------------------------------------------------------------------------------------------------------------------------

		double MCTruth_Data = -99.;

		if (MCTruth_Particle_Nu_E->size() != 1) { MultipleMCTruth++; }

		if (MCTruth_Particle_Nu_E->size() == 1) {

			True_Ev = MCTruth_Particle_Nu_E->at(0);
			True_Vx = MCTruth_Particle_Nu_Vx->at(0);
			True_Vy = MCTruth_Particle_Nu_Vy->at(0);
			True_Vz = MCTruth_Particle_Nu_Vz->at(0);

		} else {

			True_Ev = MCTruth_Data;
			True_Vx = MCTruth_Data;
			True_Vy = MCTruth_Data;
			True_Vz = MCTruth_Data;

		}

		// ------------------------------------------------------------------------------------------------------------------------------------

		// MCParticle Loop
		
		int fCC1p = 0, fCC1p1pi = 0, fCC2p = 0, fCC2p1pi = 0, fCC3p = 0, fCC3p1pi = 0, fCC3p2pi = 0, fCC3p3pi = 0, fCC4p0pi = 0, fCC4p1pi = 0, fMCParticle_Mode = -1, fNC = 0;

		int TrueMuonCounter = 0, TrueProtonCounter = 0, TrueChargedPionCounter = 0, TruePi0Counter = 0, TrueNeutronCounter = 0;
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

				if (MCParticlePdg == NeutralPionPdg) { TruePi0Counter++; }

				if (MCParticlePdg == NeutronPdg) { TrueNeutronCounter++; }

			} // End of the demand stable final state particles and primary interactions

			if (MCTruth_CCNC->at(0) == 1 // NC events				
			) { fNC = 1; }

		} // end of the loop over the simb::MCParticles

		// ------------------------------------------------------------------------------------------------

		// Signal definition: 1 mu (Pmu > 100 MeV / c), 1p (Pp > 200 MeV / c) & 0 pi+/- (Ppi > 70 MeV / c)

		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 0) { fCC1p = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 1) { fCC1p1pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 2 && TrueChargedPionCounter == 0) { fCC2p = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 2 && TrueChargedPionCounter == 1) { fCC2p1pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 0) { fCC3p = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 1) { fCC3p1pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 2) { fCC3p2pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 3) { fCC3p3pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 4 && TrueChargedPionCounter == 0) { fCC4p0pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 4 && TrueChargedPionCounter == 1) { fCC4p1pi = 1; }

		// ------------------------------------------------------------------------------------------------

		// Don't forget to check the true vertex containment for signal CC1p events

		TVector3 TrueNu_Vertex(True_Vx,True_Vy,True_Vz);
		bool TrueNu_Vertex_Containment = tools.inFVVector(TrueNu_Vertex);
		if (TrueNu_Vertex_Containment == 0) { fCC1p = 0; }

		// ------------------------------------------------------------------------------------------------

		if (MCTruth_Mode->size() == 1) { fMCParticle_Mode = MCTruth_Mode->at(0); }

		NC = fNC;
		CC1p = fCC1p;
		CC1p1pi = fCC1p1pi;
		CC2p = fCC2p;
		CC2p1pi = fCC2p1pi;
		CC3p = fCC3p;
		CC3p1pi = fCC3p1pi;
		CC3p2pi = fCC3p2pi;			
		CC3p3pi = fCC3p3pi;
		CC4p0pi = fCC4p0pi;
		CC4p1pi = fCC4p1pi;

		MCParticle_Mode = fMCParticle_Mode;

		NumberPi0 = TruePi0Counter;
		NumberNeutrons = TrueNeutronCounter;
		NumberProtons = TrueProtonCounter;
		NumberMuons = TrueMuonCounter;
		NumberChargedPions = TrueChargedPionCounter;

		// ---------------------------------------------------------------------------------------------------------------------------------

		tree->Fill();

		// ---------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the number of events

	// -----------------------------------------------------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------------------------------------

	// To be printed at the end of the run

	int precision = 2;

	std::cout.precision(precision);
	std::cout << "\n\nGathered a total of " << EventCounter << " preselected events" << std::endl << std::endl;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	// To be saved in the txt file

	myTxtFile << "\n\nStarting with " << TotalCounter << " samdef events (" << int(100.*double(TotalCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << SWTriggerCounter << " events passing SW trigger (" << int(100.*double(SWTriggerCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << OneNuMuPFParticleCounter << " events passing 1 numu PFParticle requirement (" << int(100.*double(OneNuMuPFParticleCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << DaughterCounter << " events passing 2 daughter requirement (" << int(100.*double(DaughterCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << TrackLikeDaughterCounter << " events passing 2 track-like daughter requirement (" << int(100.*double(TrackLikeDaughterCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << MatchedTrackPFParticleCounter << " events passing 2 matched track-like daughter requirement (" << int(100.*double(MatchedTrackPFParticleCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << NuFlashScoreCounter << " events passing nu/flash score requirement (" << int(100.*double(NuFlashScoreCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << FlashCounter << " events passing 1 flash requirement (" << int(100.*double(FlashCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << PairCounter << " events passing 1 candidate pair requirement (" << int(100.*double(PairCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << MomentumThresholdCounter << " events passing momentum requirement (" << int(100.*double(MomentumThresholdCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\n" << ContainmentCounter << " events passing containment requirement (" << int(100.*double(ContainmentCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\nGathered a total of " << EventCounter << " preselected events (" << int(100.*double(EventCounter)/double(TotalCounter)) << " %)" << std::endl << std::endl;

	myTxtFile << "\n\n\n\nMultiple MCTruth events " << MultipleMCTruth << " (" << int(100.*double(MultipleMCTruth)/double(EventCounter)) << " %)" << std::endl << std::endl;


	// ------------------------------------------------------------------------------------------------------------------------------------------

	OutputFile->cd();
	OutputFile->Write();
	OutputFile->Close();
	//fSpines->Close();
	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;
	myTxtFile.close();

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

double Sphere(double FracPlane0,double FracPlane1,double FracPlane2) {

	double SphereDep = TMath::Sqrt( TMath::Power(FracPlane0-1.,2.) + TMath::Power(FracPlane1-1.,2.) + TMath::Power(FracPlane2-1.,2.) );

	return SphereDep;

}

// ----------------------------------------------------------------------------------------------------------------------------------------------------
