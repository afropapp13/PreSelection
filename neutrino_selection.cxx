#define neutrino_selection_cxx
#include "neutrino_selection.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TString.h>

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#include "../myClasses/Tools.h"
#include "../myClasses/STV_Tools.h"
using namespace std;
using namespace Constants;

// -----------------------------------------------------------------------------

void neutrino_selection::Loop() {

	// -----------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

	// ---------------------------------------------------------------------------------------------------------------------------------------

	// Output Files

	TString FileName = "/uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_"+fLabel+"_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

	// -----------------------------------------------------------------------------

	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	// ----------------------------------------------------------------------------------------------------------------------------------------

	// TTree

	TTree* tree = new TTree("myPreSelection","myPreSelection");

	// ----------------------------------------------------------------------------------------------------------------------------------------

	double Weight;
	double T2KWeight;
	double ROOTinoWeight;
	double POTWeight;

	int Run;
	int SubRun;
	int Event;
	TString run_period;

	std::vector<double> All_UBGenie;
	std::vector<double> AxFFCCQEshape_UBGenie;
	std::vector<double> DecayAngMEC_UBGenie;
	std::vector<double> NormCCCOH_UBGenie;
	std::vector<double> NormNCCOH_UBGenie;
	std::vector<double> RPA_CCQE_UBGenie;
	std::vector<double> ThetaDelta2NRad_UBGenie;
	std::vector<double> Theta_Delta2Npi_UBGenie;
	std::vector<double> VecFFCCQEshape_UBGenie;
	std::vector<double> XSecShape_CCMEC_UBGenie;

	//----------------------------------------//

	std::vector<double> fluxes; // flux variations in single weight

	std::vector<double> reinteractions; // G4 weights in single weight

	int nue;	
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

	double LFG_pn;
	double True_Ev;
	double True_Vx;
	double True_Vy;
	double True_Vz;

	int NumberPi0;
	int NumberNeutrons;
	int NumberProtons;
	int NumberMuons;
	int NumberChargedPions;
	int NumberChargedPionsAnyMom;	

	// -------------------------------------------------------------------------------------------------------------------------------------------

	float NuScore;
	float FlashScore; 
	float fCosmicIPAll3D;
	float fCosmicDirAll3D;
	int fcrtveto;
	float fcrthitpe;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<double> BeamFlashes_TotalPE;
	std::vector<double> BeamFlashes_Time;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<double> CandidateMuP_Distance;
	std::vector<float> Vertex_X;
	std::vector<float> Vertex_Y;
	std::vector<float> Vertex_Z;
	std::vector<double> CandidateMuStartVertexDistance;
	std::vector<double> CandidatePStartVertexDistance;
	std::vector<double> CandidateMuEndVertexDistance;
	std::vector<double> CandidatePEndVertexDistance;

	std::vector<double> CandidateMu_P_Range;
	std::vector<double> CandidateMu_P_MCS;	
	std::vector<double> CandidateMu_Phi;
	std::vector<double> CandidateMu_CosTheta;
	std::vector<double> CandidateMu_Theta;
	std::vector<double> CandidateMu_LLR_PID;
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
	std::vector<double> True_CandidateMu_Phi;
	std::vector<double> True_CandidateMu_Theta;
	std::vector<double> True_CandidateMu_CosTheta;
	
	std::vector<double> True_CandidateMu_StartX;
	std::vector<double> True_CandidateMu_StartY;
	std::vector<double> True_CandidateMu_StartZ;

	std::vector<double> True_CandidateMu_EndX;
	std::vector<double> True_CandidateMu_EndY;
	std::vector<double> True_CandidateMu_EndZ;			
	
	std::vector<int> True_CandidateMu_StartContainment;
	std::vector<int> True_CandidateMu_EndContainment;

	std::vector<double> True_PionMomentum;

	std::vector<double> True_NeutronMomentum;
	std::vector<double> True_NeutronCosTheta;
	std::vector<double> True_NeutronPhi;	
	std::vector<double> True_Neutron_StartX;
	std::vector<double> True_Neutron_StartY;				
	std::vector<double> True_Neutron_StartZ;
	std::vector<bool> True_Neutron_StartContainment;	

	// ---------------------------------------------------------------------------------------------------------------------------------------

	std::vector<double> CandidateP_P_Range;
	std::vector<double> CandidateP_Phi;
	std::vector<double> CandidateP_Theta;
	std::vector<double> CandidateP_CosTheta;
	std::vector<double> CandidateP_LLR_PID;
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
	std::vector<double> True_CandidateP_Phi;
	std::vector<double> True_CandidateP_Theta;
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
	
	// STV, Energy Reconstruction & Light Cone Variables

	std::vector<double> Reco_A;
	std::vector<double> Reco_kMiss;
	std::vector<double> Reco_EMiss;
	std::vector<double> Reco_PMissMinus;
	std::vector<double> Reco_PMiss;
	std::vector<double> Reco_Pt;
	std::vector<double> Reco_Ptx;
	std::vector<double> Reco_Pty;
	std::vector<double> Reco_PL;
	std::vector<double> Reco_Pn;
	std::vector<double> Reco_PnPerp;
	std::vector<double> Reco_PnPerpx;
	std::vector<double> Reco_PnPerpy;		
	std::vector<double> Reco_PnPar;
	std::vector<double> Reco_DeltaAlphaT;
	std::vector<double> Reco_DeltaAlpha3Dq;
	std::vector<double> Reco_DeltaAlpha3DMu;		
	std::vector<double> Reco_DeltaPhiT;
	std::vector<double> Reco_DeltaPhi3D;	
	std::vector<double> Reco_ECal;
	std::vector<double> Reco_EQE;
	std::vector<double> Reco_Q2;
	std::vector<double> Reco_DeltaPhi;
	std::vector<double> Reco_DeltaTheta;

	std::vector<double> True_A;
	std::vector<double> True_kMiss;
	std::vector<double> True_EMiss;
	std::vector<double> True_PMissMinus;
	std::vector<double> True_PMiss;	
	std::vector<double> True_Pt;
	std::vector<double> True_Ptx;
	std::vector<double> True_Pty;
	std::vector<double> True_PL;
	std::vector<double> True_Pn;
	std::vector<double> True_PnPerp;
	std::vector<double> True_PnPerpx;
	std::vector<double> True_PnPerpy;	
	std::vector<double> True_PnPar;		
	std::vector<double> True_DeltaAlphaT;
	std::vector<double> True_DeltaAlpha3Dq;
	std::vector<double> True_DeltaAlpha3DMu;		
	std::vector<double> True_DeltaPhiT;
	std::vector<double> True_DeltaPhi3D;	
	std::vector<double> True_ECal;
	std::vector<double> True_EQE;
	std::vector<double> True_Q2;		
	std::vector<double> True_DeltaPhi;
	std::vector<double> True_DeltaTheta;	

	std::vector<double> StartToStartDistance;
	std::vector<double> EndToEndDistance;	

	// -------------------------------------------------------------------------------------------------------------------------------------------
	// -------------------------------------------------------------------------------------------------------------------------------------------	

	tree->Branch("Weight",&Weight);
	tree->Branch("T2KWeight",&T2KWeight);
	tree->Branch("ROOTinoWeight",&ROOTinoWeight);	
	tree->Branch("POTWeight",&POTWeight);	

	tree->Branch("Run",&Run);
	tree->Branch("SubRun",&SubRun);
	tree->Branch("Event",&Event);	
	tree->Branch("run_period",&run_period);
	
	tree->Branch("All_UBGenie", &All_UBGenie);
	tree->Branch("AxFFCCQEshape_UBGenie", &AxFFCCQEshape_UBGenie);
	tree->Branch("DecayAngMEC_UBGenie", &DecayAngMEC_UBGenie);
	tree->Branch("NormCCCOH_UBGenie", &NormCCCOH_UBGenie);
	tree->Branch("NormNCCOH_UBGenie", &NormNCCOH_UBGenie);
	tree->Branch("RPA_CCQE_UBGenie", &RPA_CCQE_UBGenie);
	tree->Branch("ThetaDelta2NRad_UBGenie", &ThetaDelta2NRad_UBGenie);
	tree->Branch("Theta_Delta2Npi_UBGenie", &Theta_Delta2Npi_UBGenie);
	tree->Branch("VecFFCCQEshape_UBGenie", &VecFFCCQEshape_UBGenie);
	tree->Branch("XSecShape_CCMEC_UBGenie", &XSecShape_CCMEC_UBGenie);

	//----------------------------------------//		

	tree->Branch("fluxes", &fluxes);

	tree->Branch("reinteractions", &reinteractions);

	tree->Branch("nue",&nue);
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
	tree->Branch("NumberChargedPionsAnyMom",&NumberChargedPionsAnyMom);	

	tree->Branch("LFG_pn",&LFG_pn);
	tree->Branch("True_Ev",&True_Ev);
	tree->Branch("True_Vx",&True_Vx);
	tree->Branch("True_Vy",&True_Vy);
	tree->Branch("True_Vz",&True_Vz);

	// ------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("NuScore",&NuScore);
	tree->Branch("FlashScore",&FlashScore);
	tree->Branch("CosmicIPAll3D",&fCosmicIPAll3D);
	tree->Branch("CosmicDirAll3D",&fCosmicDirAll3D);
	tree->Branch("crtveto",&fcrtveto);
	tree->Branch("crthitpe",&fcrthitpe);

	// ------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("BeamFlashes_TotalPE",&BeamFlashes_TotalPE);
	tree->Branch("BeamFlashes_Time",&BeamFlashes_Time);

	// --------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("CandidateMuP_Distance",&CandidateMuP_Distance);
	tree->Branch("Vertex_X",&Vertex_X);
	tree->Branch("Vertex_Y",&Vertex_Y);
	tree->Branch("Vertex_Z",&Vertex_Z);
	tree->Branch("CandidateMuStartVertexDistance",&CandidateMuStartVertexDistance);
	tree->Branch("CandidatePStartVertexDistance",&CandidatePStartVertexDistance);
	tree->Branch("CandidateMuEndVertexDistance",&CandidateMuEndVertexDistance);
	tree->Branch("CandidatePEndVertexDistance",&CandidatePEndVertexDistance);
		
	// --------------------------------------------------------------------------------------------------------------------------------------------	

	tree->Branch("CandidateMu_P_Range",&CandidateMu_P_Range);
	tree->Branch("CandidateMu_P_MCS",&CandidateMu_P_MCS);	
	tree->Branch("CandidateMu_Phi",&CandidateMu_Phi);
	tree->Branch("CandidateMu_Theta",&CandidateMu_Theta);
	tree->Branch("CandidateMu_CosTheta",&CandidateMu_CosTheta);
	tree->Branch("CandidateMu_LLR_PID",&CandidateMu_LLR_PID);
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
	tree->Branch("True_CandidateMu_Phi",&True_CandidateMu_Phi);
	tree->Branch("True_CandidateMu_Theta",&True_CandidateMu_Theta);
	tree->Branch("True_CandidateMu_CosTheta",&True_CandidateMu_CosTheta);
	
	tree->Branch("True_CandidateMu_StartX",&True_CandidateMu_StartX);
	tree->Branch("True_CandidateMu_StartY",&True_CandidateMu_StartY);	
	tree->Branch("True_CandidateMu_StartZ",&True_CandidateMu_StartZ);
	
	tree->Branch("True_CandidateMu_EndX",&True_CandidateMu_EndX);
	tree->Branch("True_CandidateMu_EndY",&True_CandidateMu_EndY);	
	tree->Branch("True_CandidateMu_EndZ",&True_CandidateMu_EndZ);	
	
	tree->Branch("True_CandidateMu_StartContainment",&True_CandidateMu_StartContainment);
	tree->Branch("True_CandidateMu_EndContainment",&True_CandidateMu_EndContainment);

	tree->Branch("True_PionMomentum",&True_PionMomentum);

	tree->Branch("True_NeutronMomentum",&True_NeutronMomentum);
	tree->Branch("True_NeutronCosTheta",&True_NeutronCosTheta);		
	tree->Branch("True_NeutronPhi",&True_NeutronPhi);
	tree->Branch("True_Neutron_StartX",&True_Neutron_StartX);
	tree->Branch("True_Neutron_StartY",&True_Neutron_StartY);	
	tree->Branch("True_Neutron_StartZ",&True_Neutron_StartZ);
	tree->Branch("True_NeutronStart_Containment",&True_Neutron_StartContainment);		

	// ------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("CandidateP_P_Range",&CandidateP_P_Range);
	tree->Branch("CandidateP_Phi",&CandidateP_Phi);
	tree->Branch("CandidateP_Theta",&CandidateP_Theta);
	tree->Branch("CandidateP_CosTheta",&CandidateP_CosTheta);
	tree->Branch("CandidateP_LLR_PID",&CandidateP_LLR_PID);
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
	tree->Branch("True_CandidateP_Phi",&True_CandidateP_Phi);
	tree->Branch("True_CandidateP_Theta",&True_CandidateP_Theta);
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

	tree->Branch("Reco_A",&Reco_A);
	tree->Branch("Reco_kMiss",&Reco_kMiss);
	tree->Branch("Reco_PMissMinus",&Reco_PMissMinus);
	tree->Branch("Reco_EMiss",&Reco_EMiss);
	tree->Branch("Reco_PMiss",&Reco_PMiss);	
	tree->Branch("Reco_Pt",&Reco_Pt);
	tree->Branch("Reco_Ptx",&Reco_Ptx);
	tree->Branch("Reco_Pty",&Reco_Pty);
	tree->Branch("Reco_PL",&Reco_PL);
	tree->Branch("Reco_Pn",&Reco_Pn);
	tree->Branch("Reco_PnPerp",&Reco_PnPerp);
	tree->Branch("Reco_PnPerpx",&Reco_PnPerpx);
	tree->Branch("Reco_PnPerpy",&Reco_PnPerpy);		
	tree->Branch("Reco_PnPar",&Reco_PnPar);		
	tree->Branch("Reco_DeltaAlphaT",&Reco_DeltaAlphaT);
	tree->Branch("Reco_DeltaAlpha3Dq",&Reco_DeltaAlpha3Dq);
	tree->Branch("Reco_DeltaAlpha3DMu",&Reco_DeltaAlpha3DMu);		
	tree->Branch("Reco_DeltaPhiT",&Reco_DeltaPhiT);
	tree->Branch("Reco_DeltaPhi3D",&Reco_DeltaPhi3D);	
	tree->Branch("Reco_ECal",&Reco_ECal);
	tree->Branch("Reco_EQE",&Reco_EQE);
	tree->Branch("Reco_Q2",&Reco_Q2);
	tree->Branch("Reco_DeltaPhi",&Reco_DeltaPhi);
	tree->Branch("Reco_DeltaTheta",&Reco_DeltaTheta);	

	tree->Branch("True_A",&True_A);
	tree->Branch("True_kMiss",&True_kMiss);
	tree->Branch("True_PMissMinus",&True_PMissMinus);
	tree->Branch("True_EMiss",&True_EMiss);
	tree->Branch("True_PMiss",&True_PMiss);	
	tree->Branch("True_Pt",&True_Pt);
	tree->Branch("True_Ptx",&True_Ptx);
	tree->Branch("True_Pty",&True_Pty);
	tree->Branch("True_PL",&True_PL);
	tree->Branch("True_Pn",&True_Pn);
	tree->Branch("True_PnPerp",&True_PnPerp);
	tree->Branch("True_PnPerpx",&True_PnPerpx);
	tree->Branch("True_PnPerpy",&True_PnPerpy);		
	tree->Branch("True_PnPar",&True_PnPar);		
	tree->Branch("True_DeltaAlphaT",&True_DeltaAlphaT);
	tree->Branch("True_DeltaAlpha3Dq",&True_DeltaAlpha3Dq);
	tree->Branch("True_DeltaAlpha3DMu",&True_DeltaAlpha3DMu);
	tree->Branch("True_DeltaPhiT",&True_DeltaPhiT);
	tree->Branch("True_DeltaPhi3D",&True_DeltaPhi3D);	
	tree->Branch("True_ECal",&True_ECal);
	tree->Branch("True_EQE",&True_EQE);
	tree->Branch("True_Q2",&True_Q2);
	tree->Branch("True_DeltaPhi",&True_DeltaPhi);
	tree->Branch("True_DeltaTheta",&True_DeltaTheta);

	tree->Branch("StartToStartDistance",&StartToStartDistance);
	tree->Branch("EndToEndDistance",&EndToEndDistance);						

	// -----------------------------------------------------------------------------------------------------------------------------------------

	Tools tools;

	// -----------------------------------------------------------------------------

	// Counters

	int SelectedEvents = 0;

	// -----------------------------------------------------------------------------------------------------------------------------------------

	// Event Counters

	int EventCounter = 0;
	int TotalCounter = 0;
	int TrackLikeDaughterCounter = 0;
	int MatchedTrackPFParticleCounter = 0;
	int MomentumThresholdCounter = 0;
	int ContainmentCounter = 0;

	// ----------------------------------------------------------------------------------------------------------------------------------------

	TH1D* SamdefEventPlot = new TH1D("SamdefEventPlot",";# samdef events",1,0,1);
	SamdefEventPlot->SetBinContent(1,fChain->GetEntries());

	TH1D* TrackLikeDaughterEventPlot = new TH1D("TrackLikeDaughterEventPlot",";2 track-like daughter events",1,0,1);
	TH1D* MatchedTrackLikeDaughterEventPlot = new TH1D("MatchedTrackLikeDaughterEventPlot",";2 matched track-like daughter events",1,0,1);	
	TH1D* MomentumThresholdEventPlot = new TH1D("MomentumThresholdEventPlot",";Above P threshold events",1,0,1);
	TH1D* ContainmentEventPlot = new TH1D("ContainmentEventPlot",";Contained start point events",1,0,1);

	TH1D* NTrackLikeObjectsPlot = new TH1D("NTrackLikeObjectsPlot",";# track-like objects",10,-0.5,9.5);
	TH1D* NShowerLikeObjectsPlot = new TH1D("NShowerLikeObjectsPlot",";# shower-like objects",10,-0.5,9.5);
	TH1D* TrackHighPIDScorePlot = new TH1D("TrackHighPIDScorePlot",";higher track-like pid score",50,0.,1.);
	TH1D* TrackLowPIDScorePlot = new TH1D("TrackLowPIDScorePlot",";lower track-like pid score",50,0.,1.);	
	TH1D* TrackHighPIDMomentumPlot = new TH1D("TrackHighPIDMomentumPlot",";higher track-like pid momentum",50,0.,1.5);
	TH1D* TrackLowPIDMomentumPlot = new TH1D("TrackLowPIDMomentumPlot",";lower track-like pid momentum",50,0.,1.5);					

	// --------------------------------------------------------------------------------------------------------------------------------

	// POT Counting

	double POTCount = -99.;

	if (string(fLabel).find("Overlay") != std::string::npos) {

		TString PathToPOTFile = "/uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_"+fLabel+"_"+UBCodeVersion+"_POT.root";		

		TFile* POTFile = TFile::Open(PathToPOTFile,"readonly");
		TH1D* POTCountHist = (TH1D*)(POTFile->Get("POTCountHist"));
		POTCount = POTCountHist->GetBinContent(1);
		POTFile->Close();
	
	}

	// ------------------------------------------------------------------------------------------------------------------

	// POT Scaling

	double POTScale = 1.;

	double tor860_wcut = 1;
	double E1DCNT_wcut = 1.;
	double EXT = 1.;

	if (string(fLabel).find("Run1") != std::string::npos) {

		tor860_wcut = Fulltor860_wcut_Run1;
		E1DCNT_wcut = FullE1DCNT_wcut_Run1;
		EXT = FullEXT_Run1;
		run_period = "Run1";	
	}
	
	if (string(fLabel).find("Run2") != std::string::npos) {

		tor860_wcut = Fulltor860_wcut_Run2;
		E1DCNT_wcut = FullE1DCNT_wcut_Run2;
		EXT = FullEXT_Run2;
		run_period = "Run2";	
	
	}
	
	if (string(fLabel).find("Run3") != std::string::npos) {

		tor860_wcut = Fulltor860_wcut_Run3;
		E1DCNT_wcut = FullE1DCNT_wcut_Run3;
		EXT = FullEXT_Run3;
		run_period = "Run3";	

	}
	
	if (string(fLabel).find("Run4a") != std::string::npos) {

		tor860_wcut = Fulltor860_wcut_Run4a;
		E1DCNT_wcut = FullE1DCNT_wcut_Run4a;
		EXT = FullEXT_Run4a;
		run_period = "Run4a";	

	}

	if (string(fLabel).find("Run4b") != std::string::npos) {

		tor860_wcut = Fulltor860_wcut_Run4b;
		E1DCNT_wcut = FullE1DCNT_wcut_Run4b;
		EXT = FullEXT_Run4b;
		run_period = "Run4b";	

	}			

	if (string(fLabel).find("Run4c") != std::string::npos) {

		tor860_wcut = Fulltor860_wcut_Run4c;
		E1DCNT_wcut = FullE1DCNT_wcut_Run4c;
		EXT = FullEXT_Run4c;
		run_period = "Run4c";	

	}			

	if (string(fLabel).find("Run4d") != std::string::npos) {

		tor860_wcut = Fulltor860_wcut_Run4d;
		E1DCNT_wcut = FullE1DCNT_wcut_Run4d;
		EXT = FullEXT_Run4d;
		run_period = "Run4d";	

	}			

	if (string(fLabel).find("Run5") != std::string::npos) {

		tor860_wcut = Fulltor860_wcut_Run5;
		E1DCNT_wcut = FullE1DCNT_wcut_Run5;
		EXT = FullEXT_Run5;
		run_period = "Run5";	

	}	

	if (string(fLabel).find("ExtBNB9") != std::string::npos) { POTScale = E1DCNT_wcut / EXT; }

	if (string(fLabel).find("Overlay") != std::string::npos) { POTScale = tor860_wcut / POTCount; }	

	POTWeight = POTScale;	
	ROOTinoWeight = 1.;

	// -----------------------------------------------------------------------------

	// Only for MC 
	// Need to take care of the bug fix / T2K tune weights & for the systematics weights

	if (string(fLabel).find("Overlay") != std::string::npos) {

		fChain->SetBranchAddress("weightSpline", &weightSpline, &b_weightSpline);
		fChain->SetBranchAddress("weightTune", &weightTune, &b_weightTune);

		// Only the CV samples

		if ( 
			   fLabel == "Overlay9_Run1" 
			|| fLabel == "Overlay9_Run2" 
			|| fLabel == "Overlay9_Run3" 
			|| fLabel == "Overlay9_Run4a" 
			|| fLabel == "Overlay9_Run4b" 
			|| fLabel == "Overlay9_Run4c" 
			|| fLabel == "Overlay9_Run4d" 
			|| fLabel == "Overlay9_Run5"
			|| fLabel == "OverlayDirt9_Run1" 
			|| fLabel == "OverlayDirt9_Run2" 
			|| fLabel == "OverlayDirt9_Run3"  
			|| fLabel == "OverlayDirt9_Run4a" 
			|| fLabel == "OverlayDirt9_Run4b" 
			|| fLabel == "OverlayDirt9_Run4c" 
			|| fLabel == "OverlayDirt9_Run4d" 
			|| fLabel == "OverlayDirt9_Run5"
		) {

			fChain->SetBranchAddress("weights", &weights, &b_weights);

		}

	}

	// -----------------------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		// -----------------------------------------------------------------------------
      
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
      		nb = fChain->GetEntry(jentry);   nbytes += nb;

		TotalCounter++;

		// -----------------------------------------------------------------------------

		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;

		// -----------------------------------------------------------------------------------------------------------------------------------

		// Weights for systematics

		if (string(fLabel).find("Overlay") != std::string::npos) {

			Weight = weightSpline;
			T2KWeight = weightTune;

			if (
				   fLabel == "Overlay9_Run1"
				|| fLabel == "Overlay9_Run2"
				|| fLabel == "Overlay9_Run3"
				|| fLabel == "Overlay9_Run4a"
				|| fLabel == "Overlay9_Run4b"
				|| fLabel == "Overlay9_Run4c"
				|| fLabel == "Overlay9_Run4d"
				|| fLabel == "Overlay9_Run5"
				|| fLabel == "OverlayDirt9_Run1"
				|| fLabel == "OverlayDirt9_Run2"
				|| fLabel == "OverlayDirt9_Run3"
				|| fLabel == "OverlayDirt9_Run4a"
				|| fLabel == "OverlayDirt9_Run4b"
				|| fLabel == "OverlayDirt9_Run4c"
				|| fLabel == "OverlayDirt9_Run4d"
				|| fLabel == "OverlayDirt9_Run5"
			) {


				for ( auto& pair : *weights ) {

					if ( pair.first == "All_UBGenie") {  All_UBGenie = pair.second; }
					else if ( pair.first == "AxFFCCQEshape_UBGenie") {  AxFFCCQEshape_UBGenie = pair.second; }
					else if ( pair.first == "DecayAngMEC_UBGenie") {  DecayAngMEC_UBGenie = pair.second; }
					else if ( pair.first == "NormCCCOH_UBGenie") {  NormCCCOH_UBGenie = pair.second; }
					else if ( pair.first == "NormNCCOH_UBGenie") {  NormNCCOH_UBGenie = pair.second; }
					else if ( pair.first == "RPA_CCQE_UBGenie") {  RPA_CCQE_UBGenie = pair.second; }
					else if ( pair.first == "ThetaDelta2NRad_UBGenie") {  ThetaDelta2NRad_UBGenie = pair.second; }
					else if ( pair.first == "Theta_Delta2Npi_UBGenie") {  Theta_Delta2Npi_UBGenie = pair.second; }
					else if ( pair.first == "VecFFCCQEshape_UBGenie") {  VecFFCCQEshape_UBGenie = pair.second; }
					else if ( pair.first == "XSecShape_CCMEC_UBGenie") {  XSecShape_CCMEC_UBGenie = pair.second; }


					else if ( pair.first == "flux_all") {  fluxes = pair.second; }
					else if ( pair.first == "reint_all") {  reinteractions = pair.second; }
					else if ( pair.first == "RootinoFix_UBGenie") {  ROOTinoWeight = pair.second.at(0); }

					//else {  cout << "pair.first = " << pair.first << " pair.second.size() = " << pair.second.size() << endl; }

				}

			}

		} else {

			// For BeamOn, everything will be 1
			// For BeamOff, the POTScale should be different based on the triggers
			// For MC, we need the POTCount for each one of the samples

			Weight = 1.;
			T2KWeight = 1.;
			ROOTinoWeight = 1.;

		}

		// -----------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------

		// Loop over the candidate track pairs

		CandidateMuP_Distance.clear();
		Vertex_X.clear();
		Vertex_Y.clear();
		Vertex_Z.clear();
		CandidateMuStartVertexDistance.clear();
		CandidatePStartVertexDistance.clear();
		CandidateMuEndVertexDistance.clear();
		CandidatePEndVertexDistance.clear();

		CandidateMu_P_Range.clear();
		CandidateMu_P_MCS.clear();		
		CandidateMu_Phi.clear();
		CandidateMu_Theta.clear();
		CandidateMu_CosTheta.clear();
		CandidateMu_LLR_PID.clear();
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
		True_CandidateMu_Phi.clear();
		True_CandidateMu_Theta.clear();
		True_CandidateMu_CosTheta.clear();
		
		True_CandidateMu_StartX.clear();
		True_CandidateMu_StartY.clear();
		True_CandidateMu_StartZ.clear();
		
		True_CandidateMu_EndX.clear();
		True_CandidateMu_EndY.clear();
		True_CandidateMu_EndZ.clear();				
		
		True_CandidateMu_StartContainment.clear();
		True_CandidateMu_EndContainment.clear();

		True_PionMomentum.clear();

		True_NeutronMomentum.clear();
		True_NeutronCosTheta.clear();
		True_NeutronPhi.clear();
		True_Neutron_StartX.clear();
		True_Neutron_StartY.clear();
		True_Neutron_StartZ.clear();
		True_Neutron_StartContainment.clear();													

		// ---------------------------------------------------------------------------------------------------------------------------------

		CandidateP_P_Range.clear();
		CandidateP_Phi.clear();
		CandidateP_Theta.clear();
		CandidateP_CosTheta.clear();
		CandidateP_LLR_PID.clear();
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
		True_CandidateP_Phi.clear();
		True_CandidateP_Theta.clear();
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

		Reco_A.clear();
		Reco_kMiss.clear();
		Reco_EMiss.clear();
		Reco_PMissMinus.clear();
		Reco_PMiss.clear();	
		Reco_Pt.clear();
		Reco_Ptx.clear();
		Reco_Pty.clear();
		Reco_PL.clear();
		Reco_Pn.clear();
		Reco_PnPerp.clear();
		Reco_PnPerpx.clear();	
		Reco_PnPerpy.clear();			
		Reco_PnPar.clear();				
		Reco_DeltaAlphaT.clear();
		Reco_DeltaAlpha3Dq.clear();
		Reco_DeltaAlpha3DMu.clear();				
		Reco_DeltaPhiT.clear();
		Reco_DeltaPhi3D.clear();		
		Reco_ECal.clear();
		Reco_EQE.clear();
		Reco_Q2.clear();
		Reco_DeltaPhi.clear();
		Reco_DeltaTheta.clear();

		True_A.clear();		
		True_kMiss.clear();
		True_EMiss.clear();
		True_PMissMinus.clear();
		True_PMiss.clear();		
		True_Pt.clear();
		True_Ptx.clear();
		True_Pty.clear();
		True_PL.clear();
		True_Pn.clear();
		True_PnPerp.clear();
		True_PnPerpx.clear();
		True_PnPerpy.clear();				
		True_PnPar.clear();				
		True_DeltaAlphaT.clear();
		True_DeltaAlpha3Dq.clear();
		True_DeltaAlpha3DMu.clear();				
		True_DeltaPhiT.clear();
		True_DeltaPhi3D.clear();		
		True_ECal.clear();
		True_EQE.clear();
		True_Q2.clear();
		True_DeltaPhi.clear();
		True_DeltaTheta.clear();

		StartToStartDistance.clear();
		EndToEndDistance.clear();

		// -----------------------------------------------------------------------------

		// Loop over the PFParticles and keep track of the number of tracks and showers 

		int reco_shower_count = 0;
		int reco_track_count = 0;

		std::vector<int> CandidateIndex;

		for ( int p = 0; p < n_pfps; ++p ) {

			// Only check direct neutrino daughters (generation == 2)

 			unsigned int generation = pfp_generation_v->at( p );
			if ( generation != 2u ) continue;

			float tscore = trk_score_v->at( p );
			if ( tscore <= TRACK_SCORE_CUT ) { ++reco_shower_count; }
			else { ++reco_track_count; CandidateIndex.push_back(p); }
  
		}

		// ---------------------------------------------------------------------------------------------------------------------------------

		NTrackLikeObjectsPlot->Fill(reco_track_count,POTWeight*Weight*T2KWeight*ROOTinoWeight);
		NShowerLikeObjectsPlot->Fill(reco_shower_count,POTWeight*Weight*T2KWeight*ROOTinoWeight);		

		// Requirement for exactly 2 tracks and 0 showers for a CC1p0pi selection 

		if (reco_shower_count != 0) { continue; }
		if (reco_track_count != 2) { continue; }

		// Requirement for exactly one neutrino slice

		if (nslice != 1) { continue; }

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Identify candidate muon & proton
		// Muon = the one with the highest LLR PID Score
		// Proton = the one with the lowest LLR PID Score

		if (CandidateIndex.size() != 2) { continue; }
		float first_pid_score = trk_llr_pid_score_v->at( CandidateIndex.at(0) );
		float second_pid_score = trk_llr_pid_score_v->at( CandidateIndex.at(1) );

		int CandidateMuonIndex = -1.;
		int CandidateProtonIndex = -1.;		

		if (first_pid_score > second_pid_score) { 
			
			CandidateMuonIndex = CandidateIndex.at(0); 
			CandidateProtonIndex = CandidateIndex.at(1); 			
			
		} else { 
			
			CandidateMuonIndex = CandidateIndex.at(1); 
			CandidateProtonIndex = CandidateIndex.at(0); 			
			
		}
		TrackLikeDaughterCounter++;		

		// MuonPdg in this case / Pandora = Track-like object

		if (pfpdg->at(CandidateMuonIndex) != MuonPdg) { continue; }
		if (pfpdg->at(CandidateProtonIndex) != MuonPdg) { continue; }

		MatchedTrackPFParticleCounter++;

		// So at this point we have identified our muon & proton candidates

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Start filling the TTree with events of interest

		Run = run;
		SubRun = sub;
		Event = evt;

		NuScore = topological_score; // double check
		FlashScore = nu_flashmatch_score; // double check
		fCosmicIPAll3D = CosmicIPAll3D;
		fCosmicDirAll3D = CosmicDirAll3D;
		fcrtveto = crtveto;
		fcrthitpe = crthitpe;

		// ----------------------------------------------------------------------------------------------------------------------------------

		// Beam Flashes
		// By definition, only 1 beam flash

		BeamFlashes_TotalPE.clear();
		BeamFlashes_Time.clear();

		BeamFlashes_TotalPE.push_back(flash_pe);
		BeamFlashes_Time.push_back(flash_time);

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Reconstructed Vertex

		TVector3 VertexLocation(reco_nu_vtx_sce_x,reco_nu_vtx_sce_y,reco_nu_vtx_sce_z);

		if (!tools.inFVVector(VertexLocation) ) { continue; }

		Vertex_X.push_back(reco_nu_vtx_sce_x);
		Vertex_Y.push_back(reco_nu_vtx_sce_y);
		Vertex_Z.push_back(reco_nu_vtx_sce_z);

		// ---------------------------------------------------------------------------------------------------------------------

		// Candidate muon variable definition

		double CandidateMuonTrackTheta = trk_theta_v->at(CandidateMuonIndex); // rad
		double CandidateMuonTrackTheta_Deg = CandidateMuonTrackTheta * 180. / TMath::Pi(); // rad
		double CandidateMuonTrackPhi = trk_phi_v->at(CandidateMuonIndex); // rad
		double CandidateMuonTrackPhi_Deg = CandidateMuonTrackPhi * 180. / TMath::Pi(); // rad
		double CandidateMuonTrackCosTheta = cos(CandidateMuonTrackTheta);
		double CandidateMuonTrackLength = trk_len_v->at(CandidateMuonIndex); // cm
			
		double MuonTrackStartX = trk_sce_start_x_v->at(CandidateMuonIndex);
		double MuonTrackStartY = trk_sce_start_y_v->at(CandidateMuonIndex);
		double MuonTrackStartZ = trk_sce_start_z_v->at(CandidateMuonIndex);
			
		double MuonTrackEndX = trk_sce_end_x_v->at(CandidateMuonIndex);
		double MuonTrackEndY = trk_sce_end_y_v->at(CandidateMuonIndex);
		double MuonTrackEndZ = trk_sce_end_z_v->at(CandidateMuonIndex);						
			
		TVector3 CandidateMuonTrackStart(MuonTrackStartX,MuonTrackStartY,MuonTrackStartZ);
		TVector3 CandidateMuonTrackEnd(MuonTrackEndX,MuonTrackEndY,MuonTrackEndZ);
		bool CandidateMuonTrackStartContainment = tools.inFVVector(CandidateMuonTrackStart);
		bool CandidateMuonTrackEndContainment = tools.inFVVector(CandidateMuonTrackEnd);

		double CandidateMuMom = trk_range_muon_mom_v->at(CandidateMuonIndex); // GeV/c
		double CandidateMuE_GeV = TMath::Sqrt( TMath::Power(CandidateMuMom,2.) + TMath::Power(MuonMass_GeV,2.)); // GeV

		// If exiting muon, switch to MCS and recalculate the energy

		if (!CandidateMuonTrackEndContainment) {

			CandidateMuMom = trk_mcs_muon_mom_v->at(CandidateMuonIndex); // GeV/c
			CandidateMuE_GeV = TMath::Sqrt( TMath::Power(CandidateMuMom,2.) + TMath::Power(MuonMass_GeV,2.)); // GeV

		}

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Candidate proton variable definition

		double CandidateProtonTrackTheta = trk_theta_v->at(CandidateProtonIndex); // rad
		double CandidateProtonTrackTheta_Deg = CandidateProtonTrackTheta * 180. / TMath::Pi(); // rad
		double CandidateProtonTrackPhi = trk_phi_v->at(CandidateProtonIndex); // rad
		double CandidateProtonTrackPhi_Deg = CandidateProtonTrackPhi * 180. / TMath::Pi(); // rad
		double CandidateProtonTrackCosTheta = cos(CandidateProtonTrackTheta);
		double CandidateProtonTrackLength = trk_len_v->at(CandidateProtonIndex); // cm
			
		double ProtonTrackStartX = trk_sce_start_x_v->at(CandidateProtonIndex);
		double ProtonTrackStartY = trk_sce_start_y_v->at(CandidateProtonIndex);
		double ProtonTrackStartZ = trk_sce_start_z_v->at(CandidateProtonIndex);
			
		double ProtonTrackEndX = trk_sce_end_x_v->at(CandidateProtonIndex);
		double ProtonTrackEndY = trk_sce_end_y_v->at(CandidateProtonIndex);
		double ProtonTrackEndZ = trk_sce_end_z_v->at(CandidateProtonIndex);						
			
		TVector3 CandidateProtonTrackStart(ProtonTrackStartX,ProtonTrackStartY,ProtonTrackStartZ);
		TVector3 CandidateProtonTrackEnd(ProtonTrackEndX,ProtonTrackEndY,ProtonTrackEndZ);
		bool CandidateProtonTrackStartContainment = tools.inFVVector(CandidateProtonTrackStart);
		bool CandidateProtonTrackEndContainment = tools.inFVVector(CandidateProtonTrackEnd);

		double CandidatePKE_GeV = trk_energy_proton_v->at(CandidateProtonIndex); // GeV // Watch out, kinetic energy not energy
		double CandidatePE_GeV = CandidatePKE_GeV + ProtonMass_GeV; // GeV 
		double CandidatePMom = TMath::Sqrt( TMath::Power(CandidatePE_GeV,2.) - TMath::Power(ProtonMass_GeV,2.)); // GeV/c		 

		// --------------------------------------------------------------------------------------------------------------------
			
		// STV & Energy Reconstruction
			
		TVector3 TVector3CandidateMuon(-1,-1,-1);
		TVector3CandidateMuon.SetMag(CandidateMuMom);
		TVector3CandidateMuon.SetTheta(CandidateMuonTrackTheta); // rad
		TVector3CandidateMuon.SetPhi(CandidateMuonTrackPhi); // rad	

		TVector3 TVector3CandidateProton(-1,-1,-1);
		TVector3CandidateProton.SetMag(CandidatePMom);
		TVector3CandidateProton.SetTheta(CandidateProtonTrackTheta); // rad
		TVector3CandidateProton.SetPhi(CandidateProtonTrackPhi); // rad 

		STV_Tools reco_stv_tool(TVector3CandidateMuon,TVector3CandidateProton,CandidateMuE_GeV,CandidatePE_GeV);

		// ---------------------------------------------------------------------------------------------------------------------------------

		if (T2KWeight > 0 && T2KWeight < 30) {

			TrackHighPIDScorePlot->Fill(trk_llr_pid_score_v->at( CandidateMuonIndex ),POTWeight*Weight*T2KWeight*ROOTinoWeight);
			TrackLowPIDScorePlot->Fill(trk_llr_pid_score_v->at( CandidateProtonIndex ),POTWeight*Weight*T2KWeight*ROOTinoWeight);

			TrackHighPIDMomentumPlot->Fill(CandidateMuMom,POTWeight*Weight*T2KWeight*ROOTinoWeight);
			TrackLowPIDMomentumPlot->Fill(CandidatePMom,POTWeight*Weight*T2KWeight*ROOTinoWeight);

		}		

		// Check min momentum threshold & containment

		if (CandidateMuMom < ArrayNBinsMuonMomentum[0]) { continue; }
		if (CandidatePMom < ArrayNBinsProtonMomentum[0]) { continue; }

		MomentumThresholdCounter++;

		// Fully contained events

		if (!CandidateMuonTrackStartContainment) { continue; }
		if (!CandidateMuonTrackEndContainment) { continue; }
		if (!CandidateProtonTrackStartContainment) { continue; }
		if (!CandidateProtonTrackEndContainment) { continue; }

		ContainmentCounter++;

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

		// Start-To-Start & End-To-End Distance to avoid flipped tracks

		double LocalStartToStartDistance = (CandidateMuonTrackStart - CandidateProtonTrackStart).Mag();
		double LocalEndToEndDistance = (CandidateMuonTrackEnd - CandidateProtonTrackEnd).Mag();

		StartToStartDistance.push_back(LocalStartToStartDistance);
		EndToEndDistance.push_back(LocalEndToEndDistance);

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Fill in the TTree with muon variables

		CandidateMu_P_Range.push_back(trk_range_muon_mom_v->at(CandidateMuonIndex));			
		CandidateMu_P_MCS.push_back(trk_mcs_muon_mom_v->at(CandidateMuonIndex));
		CandidateMu_Phi.push_back(CandidateMuonTrackPhi_Deg); // deg
		CandidateMu_Theta.push_back(CandidateMuonTrackTheta_Deg); // deg
		CandidateMu_CosTheta.push_back(CandidateMuonTrackCosTheta);
		CandidateMu_LLR_PID.push_back(trk_llr_pid_score_v->at(CandidateMuonIndex));
		CandidateMu_StartContainment.push_back(CandidateMuonTrackStartContainment);
		CandidateMu_EndContainment.push_back(CandidateMuonTrackEndContainment);
		CandidateMu_Length.push_back(CandidateMuonTrackLength);
		CandidateMu_StartX.push_back(MuonTrackStartX);
		CandidateMu_StartY.push_back(MuonTrackStartY);
		CandidateMu_StartZ.push_back(MuonTrackStartZ);
		CandidateMu_EndX.push_back(MuonTrackEndX);
		CandidateMu_EndY.push_back(MuonTrackEndY);
		CandidateMu_EndZ.push_back(MuonTrackEndZ);

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Fill in the TTree with proton variables

		CandidateP_P_Range.push_back(CandidatePMom);			
		CandidateP_Phi.push_back(CandidateProtonTrackPhi_Deg); // deg
		CandidateP_Theta.push_back(CandidateProtonTrackTheta_Deg); // deg
		CandidateP_CosTheta.push_back(CandidateProtonTrackCosTheta);
		CandidateP_LLR_PID.push_back(trk_llr_pid_score_v->at(CandidateProtonIndex));
		CandidateP_StartContainment.push_back(CandidateProtonTrackStartContainment);
		CandidateP_EndContainment.push_back(CandidateProtonTrackEndContainment);
		CandidateP_Length.push_back(CandidateProtonTrackLength);
		CandidateP_StartX.push_back(ProtonTrackStartX);
		CandidateP_StartY.push_back(ProtonTrackStartY);
		CandidateP_StartZ.push_back(ProtonTrackStartZ);
		CandidateP_EndX.push_back(ProtonTrackEndX);
		CandidateP_EndY.push_back(ProtonTrackEndY);
		CandidateP_EndZ.push_back(ProtonTrackEndZ);

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Vertex - Track & relative differences

		double CandidateMuStartVertexMag = (VertexLocation - CandidateMuonTrackStart).Mag();
		double CandidatePStartVertexMag = (VertexLocation - CandidateProtonTrackStart).Mag();
		double CandidateMuEndVertexMag = (VertexLocation - CandidateMuonTrackEnd).Mag();
		double CandidatePEndVertexMag = (VertexLocation - CandidateProtonTrackEnd).Mag();

		double CandidateMuPDistance = (CandidateProtonTrackStart - CandidateMuonTrackStart).Mag();

		CandidateMuP_Distance.push_back(CandidateMuPDistance);	

		CandidateMuStartVertexDistance.push_back(CandidateMuStartVertexMag);
		CandidatePStartVertexDistance.push_back(CandidatePStartVertexMag);
		CandidateMuEndVertexDistance.push_back(CandidateMuEndVertexMag);
		CandidatePEndVertexDistance.push_back(CandidatePEndVertexMag);

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Fill in the TTree with STV variables

		Reco_Pt.push_back(reco_stv_tool.ReturnPt());
		Reco_Ptx.push_back(reco_stv_tool.ReturnPtx());
		Reco_Pty.push_back(reco_stv_tool.ReturnPty());
		Reco_PL.push_back(reco_stv_tool.ReturnPL());
		Reco_Pn.push_back(reco_stv_tool.ReturnPn());
		Reco_PnPerp.push_back(reco_stv_tool.ReturnPnPerp());
		Reco_PnPerpx.push_back(reco_stv_tool.ReturnPnPerpx());
		Reco_PnPerpy.push_back(reco_stv_tool.ReturnPnPerpy());				
		Reco_PnPar.push_back(reco_stv_tool.ReturnPnPar());				
		Reco_DeltaAlphaT.push_back(reco_stv_tool.ReturnDeltaAlphaT());
		Reco_DeltaAlpha3Dq.push_back(reco_stv_tool.ReturnDeltaAlpha3Dq());
		Reco_DeltaAlpha3DMu.push_back(reco_stv_tool.ReturnDeltaAlpha3DMu());				
		Reco_DeltaPhiT.push_back(reco_stv_tool.ReturnDeltaPhiT());
		Reco_DeltaPhi3D.push_back(reco_stv_tool.ReturnDeltaPhi3D());		
		Reco_ECal.push_back(reco_stv_tool.ReturnECal());
		Reco_EQE.push_back(reco_stv_tool.ReturnEQE());
		Reco_Q2.push_back(reco_stv_tool.ReturnQ2());
		Reco_A.push_back(reco_stv_tool.ReturnA());
		Reco_EMiss.push_back(reco_stv_tool.ReturnEMiss());
		Reco_kMiss.push_back(reco_stv_tool.ReturnkMiss());
		Reco_PMiss.push_back(reco_stv_tool.ReturnPMiss());
		Reco_PMissMinus.push_back(reco_stv_tool.ReturnPMissMinus());

		// --------------------------------------------------------------------------------------------------------------------
		// --------------------------------------------------------------------------------------------------------------------

		// Backtracking to truth, only for MC

		if (string(fLabel).find("Overlay") != std::string::npos) {

			// ---------------------------------------------------------------------------------------------------------------------------------

			// Backtracked muon candidate

			CandidateMu_MCParticle_Pdg.push_back(backtracked_pdg->at(CandidateMuonIndex));
			CandidateMu_MCParticle_Purity.push_back(backtracked_purity->at(CandidateMuonIndex));

			double CandidateMuonPx = backtracked_px->at(CandidateMuonIndex);
			double CandidateMuonPy = backtracked_py->at(CandidateMuonIndex);
			double CandidateMuonPz = backtracked_pz->at(CandidateMuonIndex);
			TVector3 TrueCandidateMuonP(CandidateMuonPx,CandidateMuonPy,CandidateMuonPz);
				
			double CandidateMuonStartX = backtracked_start_x->at(CandidateMuonIndex);
			double CandidateMuonStartY = backtracked_start_y->at(CandidateMuonIndex);
			double CandidateMuonStartZ = backtracked_start_z->at(CandidateMuonIndex);						
			TVector3 TrueCandidateMuonTrackStart(CandidateMuonStartX,CandidateMuonStartY,CandidateMuonStartZ);
			bool TrueCandidateMuonTrackStartContainment = tools.inFVVector(TrueCandidateMuonTrackStart);

			double TrueCandidateMuonTrackPhi = TrueCandidateMuonP.Phi(); // rad
			double TrueCandidateMuonTrackPhi_Deg = TrueCandidateMuonTrackPhi * 180./ TMath::Pi(); // deg
			double TrueCandidateMuonTrackTheta = TrueCandidateMuonP.Theta(); // rad
			double TrueCandidateMuonTrackTheta_Deg = TrueCandidateMuonTrackTheta * 180./ TMath::Pi(); // deg
			double TrueCandidateMuonTrackCosTheta = TrueCandidateMuonP.CosTheta();

			double TrueCandidateMuonTrackMomentum_GeV = TrueCandidateMuonP.Mag(); // GeV
			double TrueCandidateMuonTrack_E_GeV = TMath::Sqrt( TMath::Power(TrueCandidateMuonTrackMomentum_GeV,2.) + TMath::Power(MuonMass_GeV,2.) ); // GeV

			True_CandidateMu_P.push_back(TrueCandidateMuonTrackMomentum_GeV);
			True_CandidateMu_Phi.push_back(TrueCandidateMuonTrackPhi_Deg); // deg
			True_CandidateMu_Theta.push_back(TrueCandidateMuonTrackTheta_Deg);
			True_CandidateMu_CosTheta.push_back(TrueCandidateMuonTrackCosTheta);
				
			True_CandidateMu_StartX.push_back(CandidateMuonStartX);
			True_CandidateMu_StartY.push_back(CandidateMuonStartY);
			True_CandidateMu_StartZ.push_back(CandidateMuonStartZ);			
			True_CandidateMu_StartContainment.push_back(TrueCandidateMuonTrackStartContainment);

			// ---------------------------------------------------------------------------------------------------------------------------------

			// Backtracked proton candidate

			CandidateP_MCParticle_Pdg.push_back(backtracked_pdg->at(CandidateProtonIndex));
			CandidateP_MCParticle_Purity.push_back(backtracked_purity->at(CandidateProtonIndex));

			double CandidateProtonPx = backtracked_px->at(CandidateProtonIndex);
			double CandidateProtonPy = backtracked_py->at(CandidateProtonIndex);
			double CandidateProtonPz = backtracked_pz->at(CandidateProtonIndex);
			TVector3 TrueCandidateProtonP(CandidateProtonPx,CandidateProtonPy,CandidateProtonPz);
				
			double CandidateProtonStartX = backtracked_start_x->at(CandidateProtonIndex);
			double CandidateProtonStartY = backtracked_start_y->at(CandidateProtonIndex);
			double CandidateProtonStartZ = backtracked_start_z->at(CandidateProtonIndex);						
			TVector3 TrueCandidateProtonTrackStart(CandidateProtonStartX,CandidateProtonStartY,CandidateProtonStartZ);
			bool TrueCandidateProtonTrackStartContainment = tools.inFVVector(TrueCandidateProtonTrackStart);

			double TrueCandidateProtonTrackPhi = TrueCandidateProtonP.Phi(); // rad
			double TrueCandidateProtonTrackPhi_Deg = TrueCandidateProtonTrackPhi * 180./ TMath::Pi(); // deg
			double TrueCandidateProtonTrackTheta = TrueCandidateProtonP.Theta(); // rad
			double TrueCandidateProtonTrackTheta_Deg = TrueCandidateProtonTrackTheta * 180./ TMath::Pi(); // deg
			double TrueCandidateProtonTrackCosTheta = TrueCandidateProtonP.CosTheta();

			double TrueCandidateProtonTrackMomentum_GeV = TrueCandidateProtonP.Mag(); // GeV
			double TrueCandidateProtonTrack_E_GeV = TMath::Sqrt( TMath::Power(TrueCandidateProtonTrackMomentum_GeV,2.) + TMath::Power(ProtonMass_GeV,2.) ); // GeV

			True_CandidateP_P.push_back(TrueCandidateProtonTrackMomentum_GeV);
			True_CandidateP_Phi.push_back(TrueCandidateProtonTrackPhi_Deg); // deg
			True_CandidateP_Theta.push_back(TrueCandidateProtonTrackTheta_Deg);
			True_CandidateP_CosTheta.push_back(TrueCandidateProtonTrackCosTheta);
				
			True_CandidateP_StartX.push_back(CandidateProtonStartX);
			True_CandidateP_StartY.push_back(CandidateProtonStartY);
			True_CandidateP_StartZ.push_back(CandidateProtonStartZ);			
			True_CandidateP_StartContainment.push_back(TrueCandidateProtonTrackStartContainment);

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

			// --------------------------------------------------------------------------------------------------------------------		

			STV_Tools true_stv_tool(True_TVector3CandidateMuon,True_TVector3CandidateProton,TrueCandidateMuonTrack_E_GeV,TrueCandidateProtonTrack_E_GeV);

			True_Pt.push_back(true_stv_tool.ReturnPt());
			True_Ptx.push_back(true_stv_tool.ReturnPtx());
			True_Pty.push_back(true_stv_tool.ReturnPty());
			True_PL.push_back(true_stv_tool.ReturnPL());
			True_Pn.push_back(true_stv_tool.ReturnPn());
			True_PnPerp.push_back(true_stv_tool.ReturnPnPerp());
			True_PnPerpx.push_back(true_stv_tool.ReturnPnPerpx());
			True_PnPerpy.push_back(true_stv_tool.ReturnPnPerpy());						
			True_PnPar.push_back(true_stv_tool.ReturnPnPar());						
			True_DeltaAlphaT.push_back(true_stv_tool.ReturnDeltaAlphaT());
			True_DeltaAlpha3Dq.push_back(true_stv_tool.ReturnDeltaAlpha3Dq());
			True_DeltaAlpha3DMu.push_back(true_stv_tool.ReturnDeltaAlpha3DMu());						
			True_DeltaPhiT.push_back(true_stv_tool.ReturnDeltaPhiT());
			True_DeltaPhi3D.push_back(true_stv_tool.ReturnDeltaPhi3D());			
			True_ECal.push_back(true_stv_tool.ReturnECal());
			True_EQE.push_back(true_stv_tool.ReturnEQE());
			True_Q2.push_back(true_stv_tool.ReturnQ2());	
			True_A.push_back(true_stv_tool.ReturnA());	
			True_EMiss.push_back(true_stv_tool.ReturnEMiss());	
			True_kMiss.push_back(true_stv_tool.ReturnkMiss());	
			True_PMiss.push_back(true_stv_tool.ReturnPMiss());
			True_PMissMinus.push_back(true_stv_tool.ReturnPMissMinus());	
				
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

			// ---------------------------------------------------------------------------------------------------------------------------------


		} else { // BeamOn & ExtBNB

			True_CandidateMu_P.push_back(CosmicPID);
			True_CandidateMu_Phi.push_back(CosmicPID);
			True_CandidateMu_Theta.push_back(CosmicPID);
			True_CandidateMu_CosTheta.push_back(CosmicPID);
				
			True_CandidateMu_StartX.push_back(CosmicPID);
			True_CandidateMu_StartY.push_back(CosmicPID);
			True_CandidateMu_StartZ.push_back(CosmicPID);			
			True_CandidateMu_StartContainment.push_back(CosmicPID);

			True_CandidateMu_EndX.push_back(CosmicPID);
			True_CandidateMu_EndY.push_back(CosmicPID);
			True_CandidateMu_EndZ.push_back(CosmicPID);			
			True_CandidateMu_EndContainment.push_back(CosmicPID);

			True_CandidateP_P.push_back(CosmicPID);
			True_CandidateP_Phi.push_back(CosmicPID);
			True_CandidateP_Theta.push_back(CosmicPID);
			True_CandidateP_CosTheta.push_back(CosmicPID);
				
			True_CandidateP_StartX.push_back(CosmicPID);
			True_CandidateP_StartY.push_back(CosmicPID);
			True_CandidateP_StartZ.push_back(CosmicPID);			
			True_CandidateP_StartContainment.push_back(CosmicPID);

			True_CandidateP_EndX.push_back(CosmicPID);
			True_CandidateP_EndY.push_back(CosmicPID);
			True_CandidateP_EndZ.push_back(CosmicPID);			
			True_CandidateP_EndContainment.push_back(CosmicPID);

			True_Pt.push_back(CosmicPID);
			True_Ptx.push_back(CosmicPID);
			True_Pty.push_back(CosmicPID);
			True_PL.push_back(CosmicPID);
			True_Pn.push_back(CosmicPID);
			True_PnPerp.push_back(CosmicPID);
			True_PnPerpx.push_back(CosmicPID);
			True_PnPerpy.push_back(CosmicPID);						
			True_PnPar.push_back(CosmicPID);						
			True_DeltaAlphaT.push_back(CosmicPID);
			True_DeltaAlpha3Dq.push_back(CosmicPID);
			True_DeltaAlpha3DMu.push_back(CosmicPID);						
			True_DeltaPhiT.push_back(CosmicPID);
			True_DeltaPhi3D.push_back(CosmicPID);			
			True_ECal.push_back(CosmicPID);
			True_EQE.push_back(CosmicPID);
			True_Q2.push_back(CosmicPID);	

			True_A.push_back(CosmicPID);	
			True_EMiss.push_back(CosmicPID);	
			True_kMiss.push_back(CosmicPID);	
			True_PMiss.push_back(CosmicPID);
			True_PMissMinus.push_back(CosmicPID);

			True_DeltaPhi.push_back(CosmicPID);
			True_DeltaTheta.push_back(CosmicPID);

		}

		// ---------------------------------------------------------------------------------------------------------------------------------

		// True neutrino vertex

		if (string(fLabel).find("Overlay") != std::string::npos) {

			True_Ev = nu_e;
			True_Vx = true_nu_vtx_x;
			True_Vy = true_nu_vtx_y;
			True_Vz = true_nu_vtx_z;

		} else {

			True_Ev = CosmicPID;
			True_Vx = CosmicPID;
			True_Vy = CosmicPID;
			True_Vz = CosmicPID;

		}

		// ---------------------------------------------------------------------------------------------------------------------------------

		// Now truth level loop 

		// MCParticle Loop
		
		int fCC1p = 0, fCC1p1pi = 0, fCC2p = 0, fCC2p1pi = 0, fCC3p = 0, fCC3p1pi = 0, fCC3p2pi = 0, fCC3p3pi = 0, fCC4p0pi = 0, fCC4p1pi = 0, fMCParticle_Mode = -1, fNC = 0, fnue = 0;

		int TrueMuonCounter = 0, TrueProtonCounter = 0, TrueChargedPionCounter = 0, TruePi0Counter = 0;
		int TrueNeutronCounter = 0, TrueHeavierMesonCounter = 0, TrueChargedPionCounterAnyMom = 0;
		int NMCParticles = mc_pdg->size();
		
		std::vector<int> VectorTrueMuonIndex; VectorTrueMuonIndex.clear();
		std::vector<int> VectorTrueProtonIndex; VectorTrueProtonIndex.clear();
		std::vector<int> VectorTrueNeutronIndex; VectorTrueNeutronIndex.clear();	

		//----------------------------------------//
		
		TVector3 TrueNu_Vertex(True_Vx,True_Vy,True_Vz);
		bool TrueNu_Vertex_Containment = tools.inFVVector(TrueNu_Vertex);

		//----------------------------------------//			

		for (int WhichMCParticle = 0; WhichMCParticle < NMCParticles; WhichMCParticle++) {

			// MC truth information for the final-state primary particles

			// CC numu events	

			if ( ccnc == 0 && nu_pdg == 14) {

				TVector3 MCParticle(mc_px->at(WhichMCParticle),mc_py->at(WhichMCParticle),mc_pz->at(WhichMCParticle));
				double MCParticleMomentum = MCParticle.Mag();
				double MCParticleCosTheta = MCParticle.CosTheta();
				double MCParticlePhi = MCParticle.Phi()*180./TMath::Pi();				

				int MCParticlePdg = mc_pdg->at(WhichMCParticle);

				if ( MCParticlePdg == MuonPdg && MCParticleMomentum >= ArrayNBinsMuonMomentum[0] ) 
					{ TrueMuonCounter++;  VectorTrueMuonIndex.push_back(WhichMCParticle); }

				if ( MCParticlePdg == ProtonPdg && MCParticleMomentum >= ArrayNBinsProtonMomentum[0] ) 
					{ TrueProtonCounter++; VectorTrueProtonIndex.push_back(WhichMCParticle); }

				if ( fabs(MCParticlePdg) == AbsChargedPionPdg && MCParticleMomentum >= ChargedPionMomentumThres ) 
					{ TrueChargedPionCounter++; }

				if ( fabs(MCParticlePdg) == AbsChargedPionPdg ) 
					{ TrueChargedPionCounterAnyMom++;  True_PionMomentum.push_back(MCParticleMomentum); }					

				if (MCParticlePdg == NeutralPionPdg) { TruePi0Counter++; }

				if (MCParticlePdg == NeutronPdg) { 
					
					TrueNeutronCounter++; 
					True_NeutronMomentum.push_back(MCParticleMomentum);
					True_NeutronCosTheta.push_back(MCParticleCosTheta);
					True_NeutronPhi.push_back(MCParticlePhi);
					True_Neutron_StartX.push_back(True_Vx);
					True_Neutron_StartY.push_back(True_Vy);
					True_Neutron_StartZ.push_back(True_Vz);
					True_Neutron_StartContainment.push_back(TrueNu_Vertex_Containment);																														 				
					
				}

				if ( MCParticlePdg != NeutralPionPdg && fabs(MCParticlePdg) != AbsChargedPionPdg && tools.is_meson_or_antimeson(MCParticlePdg) ) { TrueHeavierMesonCounter++; }				

				// -----------------------------------------------------------------

				// Matching the true endpoint of the CC1p candidate tracks

				if ( mc_vx->at(WhichMCParticle) == True_CandidateMu_StartX.at(0) && mc_vy->at(WhichMCParticle) == True_CandidateMu_StartY.at(0) 
				  && mc_vz->at(WhichMCParticle) == True_CandidateMu_StartZ.at(0) && MCParticlePdg == MuonPdg 
				) { 

					True_CandidateMu_EndX.push_back(mc_endx->at(WhichMCParticle));
					True_CandidateMu_EndY.push_back(mc_endy->at(WhichMCParticle));
					True_CandidateMu_EndZ.push_back(mc_endz->at(WhichMCParticle)); 

				}

				if ( mc_vx->at(WhichMCParticle) == True_CandidateP_StartX.at(0) && mc_vy->at(WhichMCParticle) == True_CandidateP_StartY.at(0) 
				  && mc_vz->at(WhichMCParticle) == True_CandidateP_StartZ.at(0) && MCParticlePdg == ProtonPdg 
				) { 

					True_CandidateP_EndX.push_back(mc_endx->at(WhichMCParticle));
					True_CandidateP_EndY.push_back(mc_endy->at(WhichMCParticle)); 
					True_CandidateP_EndZ.push_back(mc_endz->at(WhichMCParticle));

				}

				// -----------------------------------------------------------------

			} // End of the demand stable final state particles and primary interactions

			// NC events
			if (ccnc == 1) { fNC = 1; }

			// nu_e
			if (nu_pdg == 12) { fnue = 1; }

		} // end of the loop over the simb::MCParticles

		// ------------------------------------------------------------------------------------------------

		// Signal definition: 1 mu (Pmu > 100 MeV / c), 1p (Pp > 250 MeV / c) & 0 pi+/- (Ppi > 70 MeV / c)

		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 0 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC1p = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 1 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC1p1pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 2 && TrueChargedPionCounter == 0 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC2p = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 2 && TrueChargedPionCounter == 1 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC2p1pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 0 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC3p = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 1 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC3p1pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 2 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC3p2pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 3 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC3p3pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 4 && TrueChargedPionCounter == 0 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC4p0pi = 1; }
		if (TrueMuonCounter == 1 && TrueProtonCounter == 4 && TrueChargedPionCounter == 1 && TruePi0Counter == 0 && TrueHeavierMesonCounter == 0) { fCC4p1pi = 1; }

		// ------------------------------------------------------------------------------------------------

		// Don't forget to check the true vertex containment for signal CC1p events

		if (TrueNu_Vertex_Containment == 0) { fCC1p = 0; }

		// ------------------------------------------------------------------------------------------------

		nue = fnue;
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

		MCParticle_Mode = interaction;

		NumberPi0 = TruePi0Counter;
		NumberNeutrons = TrueNeutronCounter;
		NumberProtons = TrueProtonCounter;
		NumberMuons = TrueMuonCounter;
		NumberChargedPions = TrueChargedPionCounter;
		NumberChargedPionsAnyMom = TrueChargedPionCounterAnyMom;		

		// ---------------------------------------------------------------------------------------------------------------------------------

		EventCounter++;

		// ---------------------------------------------------------------------------------------------------------------------------------

		tree->Fill();

		// ---------------------------------------------------------------------------------------------------------------------------------

	}

	// -----------------------------------------------------------------------------

	std::cout << std::endl << EventCounter << " selected events (" << std::setprecision(2) << double(EventCounter)/double(TotalCounter) *100. << "%)" << std::endl << std::endl;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	// To be printed at the end of the run

	int precision = 2;

	std::cout.precision(precision);
	std::cout << "\n\nGathered a total of " << EventCounter << " preselected events" << std::endl << std::endl;

	TrackLikeDaughterEventPlot->SetBinContent(1,TrackLikeDaughterCounter);
	MatchedTrackLikeDaughterEventPlot->SetBinContent(1,MatchedTrackPFParticleCounter);	
	MomentumThresholdEventPlot->SetBinContent(1,MomentumThresholdCounter);
	ContainmentEventPlot->SetBinContent(1,ContainmentCounter);					

	OutputFile->cd();
	TrackLikeDaughterEventPlot->Write();
	MatchedTrackLikeDaughterEventPlot->Write();	
	MomentumThresholdEventPlot->Write();
	ContainmentEventPlot->Write();

	// -----------------------------------------------------------------------------------------------------------------------------------------
	// -----------------------------------------------------------------------------------------------------------------------------------------

	OutputFile->cd();
	OutputFile->Write();
	OutputFile->Close();
	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;

	// -----------------------------------------------------------------------------

} // End of the program
