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
#include "ubana/myClasses/STV_Tools.h"

using namespace std;
using namespace Constants;

void PreTruthSelection::Loop() {

	if (fChain == 0) { return; } 
	Long64_t nentries = fChain->GetEntriesFast(); Long64_t nbytes = 0, nb = 0;

	TH1D::SetDefaultSumw2();

	// ---------------------------------------------------------------------------------------------------------------------------------------

	// Txt file to keep track of the event reduction at each stage

	TString TxtName = "/uboone/data/users/apapadop/myEvents/myTxtFiles/"+UBCodeVersion+"/TxtPreTruthSelection_"+fWhichSample+"_"+UBCodeVersion+".txt";
	ofstream myTxtFile;
	myTxtFile.open(TxtName);

	// --------------------------------------------------------------------------------------------------------------------------------------------------

	// Output Files

	TString FileName = "/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreTruthSelection_"+fWhichSample+"_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

	// ----------------------------------------------------------------------------------------------------------------------------------------

	// TTree

	TTree* tree = new TTree("myPreTruthSelection","myPreTruthSelection");

	// ------------------------------------------------------------------------------------------------------------------------------------------

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

	// ------------------------------------------------------------------------------------------------------------------------------------------

	double True_Ev;
	double True_Vx;
	double True_Vy;
	double True_Vz;

	int NumberMCParticles;
	int CC1p;
	int CC1p1pi;
	int CC2p;
	int CC2p1pi;
	int CC3p;
	int CC3p1pi;
	int CC3p2pi;

	int NumberPi0;
	int NumberNeutrons;		
	
	// ------------------------------------------------------------------------------------------------------------------------------------------	

	std::vector<int> Muon_MCParticle_Mode;
	std::vector<double> Muon_MCParticle_Mom;
//	std::vector<double> Muon_MCParticle_KE;
	std::vector<double> Muon_MCParticle_Phi;
	std::vector<double> Muon_MCParticle_CosTheta;
//	std::vector<double> Muon_MCParticle_Length;
	std::vector<double> Muon_MCParticle_StartX;
	std::vector<double> Muon_MCParticle_StartY;
	std::vector<double> Muon_MCParticle_StartZ;
	std::vector<double> Muon_MCParticle_EndX;
	std::vector<double> Muon_MCParticle_EndY;
	std::vector<double> Muon_MCParticle_EndZ;
	std::vector<int> Muon_MCParticle_StartContainment;
	std::vector<int> Muon_MCParticle_EndContainment;
	std::vector<int> Muon_MCParticle_Pdg;
	
	// ------------------------------------------------------------------------------------------------------------------------------------------	

	std::vector<int> Proton_MCParticle_Mode;
	std::vector<double> Proton_MCParticle_Mom;
//	std::vector<double> Proton_MCParticle_KE;
	std::vector<double> Proton_MCParticle_Phi;
	std::vector<double> Proton_MCParticle_CosTheta;
	std::vector<double> Proton_MCParticle_Length;
	std::vector<double> Proton_MCParticle_StartX;
	std::vector<double> Proton_MCParticle_StartY;
	std::vector<double> Proton_MCParticle_StartZ;
	std::vector<double> Proton_MCParticle_EndX;
	std::vector<double> Proton_MCParticle_EndY;
	std::vector<double> Proton_MCParticle_EndZ;
	std::vector<int> Proton_MCParticle_StartContainment;
	std::vector<int> Proton_MCParticle_EndContainment;
	std::vector<int> Proton_MCParticle_Pdg;
	
	// -------------------------------------------------------------------------------------------------------------------------------------------
	
	// STV, Energy Reconstruction & Light Cone Variables	

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

	// ------------------------------------------------------------------------------------------------------------------------------------------	
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

	// -------------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("True_Ev",&True_Ev);
	tree->Branch("True_Vx",&True_Vx);
	tree->Branch("True_Vy",&True_Vy);
	tree->Branch("True_Vz",&True_Vz);

	tree->Branch("NumberMCParticles",&NumberMCParticles);
	tree->Branch("CC1p",&CC1p);
	tree->Branch("CC1p1pi",&CC1p1pi);
	tree->Branch("CC2p",&CC2p);
	tree->Branch("CC2p1pi",&CC2p1pi);
	tree->Branch("CC3p",&CC3p);
	tree->Branch("CC3p1pi",&CC3p1pi);
	tree->Branch("CC3p2pi",&CC3p2pi);

	tree->Branch("NumberPi0",&NumberPi0);
	tree->Branch("NumberNeutrons",&NumberNeutrons);
	
	// -------------------------------------------------------------------------------------------------------------------------------------------
		
	tree->Branch("Muon_MCParticle_Mode",&Muon_MCParticle_Mode);
	tree->Branch("Muon_MCParticle_Mom",&Muon_MCParticle_Mom);
//	tree->Branch("Muon_MCParticle_KE",&Muon_MCParticle_KE);
	tree->Branch("Muon_MCParticle_Phi",&Muon_MCParticle_Phi);
	tree->Branch("Muon_MCParticle_CosTheta",&Muon_MCParticle_CosTheta);
//	tree->Branch("Muon_MCParticle_Length",&Muon_MCParticle_Length);
	tree->Branch("Muon_MCParticle_StartX",&Muon_MCParticle_StartX);
	tree->Branch("Muon_MCParticle_StartY",&Muon_MCParticle_StartY);
	tree->Branch("Muon_MCParticle_StartZ",&Muon_MCParticle_StartZ);
	tree->Branch("Muon_MCParticle_EndX",&Muon_MCParticle_EndX);
	tree->Branch("Muon_MCParticle_EndY",&Muon_MCParticle_EndY);
	tree->Branch("Muon_MCParticle_EndZ",&Muon_MCParticle_EndZ);
	tree->Branch("Muon_MCParticle_StartContainment",&Muon_MCParticle_StartContainment);
	tree->Branch("Muon_MCParticle_EndContainment",&Muon_MCParticle_EndContainment);
	tree->Branch("Muon_MCParticle_Pdg",&Muon_MCParticle_Pdg);
	
	// -------------------------------------------------------------------------------------------------------------------------------------------
		
	tree->Branch("Proton_MCParticle_Mode",&Proton_MCParticle_Mode);
	tree->Branch("Proton_MCParticle_Mom",&Proton_MCParticle_Mom);
//	tree->Branch("Proton_MCParticle_KE",&Proton_MCParticle_KE);
	tree->Branch("Proton_MCParticle_Phi",&Proton_MCParticle_Phi);
	tree->Branch("Proton_MCParticle_CosTheta",&Proton_MCParticle_CosTheta);
	tree->Branch("Proton_MCParticle_Length",&Proton_MCParticle_Length);
	tree->Branch("Proton_MCParticle_StartX",&Proton_MCParticle_StartX);
	tree->Branch("Proton_MCParticle_StartY",&Proton_MCParticle_StartY);
	tree->Branch("Proton_MCParticle_StartZ",&Proton_MCParticle_StartZ);
	tree->Branch("Proton_MCParticle_EndX",&Proton_MCParticle_EndX);
	tree->Branch("Proton_MCParticle_EndY",&Proton_MCParticle_EndY);
	tree->Branch("Proton_MCParticle_EndZ",&Proton_MCParticle_EndZ);
	tree->Branch("Proton_MCParticle_StartContainment",&Proton_MCParticle_StartContainment);
	tree->Branch("Proton_MCParticle_EndContainment",&Proton_MCParticle_EndContainment);
	tree->Branch("Proton_MCParticle_Pdg",&Proton_MCParticle_Pdg);
	
	// -----------------------------------------------------------------------------------------------------------------------------------------

	tree->Branch("True_kMiss",&True_kMiss);
	tree->Branch("True_EMiss",&True_EMiss);
	tree->Branch("True_PMissMinus",&True_PMissMinus);
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

	// ------------------------------------------------------------------------------------------------------------------------------------------

	// Event Counters

	int CC1pCounter = 0;
	int CC1p1piCounter = 0;
	int CC2pCounter = 0;
	int CC2p1piCounter = 0;
	int CC3pCounter = 0;
	int CC3p1piCounter = 0;
	int CC3p2piCounter = 0;	
	int ContainedEventCounter = 0;

	// ------------------------------------------------------------------------------------------------------------------------------------------

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;
		Long64_t ientry = LoadTree(jentry); if (ientry < 0) break; nb = fChain->GetEntry(jentry); nbytes += nb;

		// ---------------------------------------------------------------------------------------------------------------------------------

		if (string(fWhichSample).find("Overlay") != std::string::npos) {

	//		double weight = 1.;
			double weight = EventWeight->at(0); // spline bug fix from v3.0.4 to v3.0.6
			Weight = weight;

			double T2Kweight = T2KEventWeight->at(0); // MicroBooNE tune based on T2K 
			T2KWeight = T2Kweight;
			
			ROOTinoWeight = ROOTinoEventWeight->at(0);	

			// We need the EventWeight weights only for the nominal samples, not for the detector variations

			if ( 
				fWhichSample == "Overlay9_Run1" || fWhichSample == "Overlay9_Run2" || fWhichSample == "Overlay9_Run3" || 
				fWhichSample == "Overlay9_Run4" || fWhichSample == "Overlay9_Run5" ||
				fWhichSample == "OverlayDirt9_Run1" || fWhichSample == "OverlayDirt9_Run2" || fWhichSample == "OverlayDirt9_Run3" || 
				fWhichSample == "OverlayDirt9_Run4" || fWhichSample == "OverlayDirt9_Run5"				 
			) {

				// Most of the multisims have a size of a 1000
				// That is more than sufficient, we can do it with 100 universes

				// Genie xsection uncertainty weights
				// All_UBGenie_EventWeight has 100 universes
				// Everything else is 2 universes

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

				int MultiSimSize = 100;

				// Flux uncertainty weights
				// All of them have 1000 universes
				// Limit them to MultiSimSize

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

		// ------------------------------------------------------------------------------------------------------------------------------

		// Muon MCParticles

		Muon_MCParticle_Mode.clear();
		Muon_MCParticle_Mom.clear();
//		Muon_MCParticle_KE.clear();
		Muon_MCParticle_Phi.clear();
		Muon_MCParticle_CosTheta.clear();
//		Muon_MCParticle_Length.clear();
		Muon_MCParticle_StartX.clear();
		Muon_MCParticle_StartY.clear();
		Muon_MCParticle_StartZ.clear();
		Muon_MCParticle_EndX.clear();
		Muon_MCParticle_EndY.clear();
		Muon_MCParticle_EndZ.clear();
		Muon_MCParticle_StartContainment.clear();
		Muon_MCParticle_EndContainment.clear();
		Muon_MCParticle_Pdg.clear();
		
		// ------------------------------------------------------------------------------------------------------------------------------

		// Proton MCParticles

		Proton_MCParticle_Mode.clear();
		Proton_MCParticle_Mom.clear();
//		Proton_MCParticle_KE.clear();
		Proton_MCParticle_Phi.clear();
		Proton_MCParticle_CosTheta.clear();
		Proton_MCParticle_Length.clear();
		Proton_MCParticle_StartX.clear();
		Proton_MCParticle_StartY.clear();
		Proton_MCParticle_StartZ.clear();
		Proton_MCParticle_EndX.clear();
		Proton_MCParticle_EndY.clear();
		Proton_MCParticle_EndZ.clear();
		Proton_MCParticle_StartContainment.clear();
		Proton_MCParticle_EndContainment.clear();
		Proton_MCParticle_Pdg.clear();
		
		// -----------------------------------------------------------------------------------------------------------------------------

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

		// ----------------------------------------------------------------------------------------------------------------------------	

		True_Ev = MCTruth_Particle_Nu_E->at(0);
		True_Vx = MCTruth_Particle_Nu_Vx->at(0);
		True_Vy = MCTruth_Particle_Nu_Vy->at(0);
		True_Vz = MCTruth_Particle_Nu_Vz->at(0);

		TVector3 TrueNu_Vertex(True_Vx,True_Vy,True_Vz);
		bool TrueNu_Vertex_Containment = tools.inFVVector(TrueNu_Vertex);
		if (TrueNu_Vertex_Containment == 0) { continue; }
		ContainedEventCounter++;
		
		// ----------------------------------------------------------------------------------------------------------------------------	

		int NMCParticles = MCParticle_Vx->size();
		
		// ------------------------------------------------------------------------------------------------------------------------------		

		int StableMCParticles = 0;
		int fCC1p = 0;
		int fCC1p1pi = 0;
		int fCC2p = 0;	
		int fCC2p1pi = 0;
		int fCC3p = 0;	
		int fCC3p1pi = 0;
		int fCC3p2pi = 0;			
		int TrueMuonCounter = 0, TrueProtonCounter = 0, TrueChargedPionCounter = 0, TruePi0Counter = 0, TrueNeutronCounter = 0;
		
		std::vector<int> VectorTrueMuonIndex; VectorTrueMuonIndex.clear();
		std::vector<int> VectorTrueProtonIndex; VectorTrueProtonIndex.clear();		

		// Loop over the MCParticles and determine the populations

		for (int WhichMCParticle = 0; WhichMCParticle < NMCParticles; WhichMCParticle++) {

			// Demand stable final state particles

			if (
				MCParticle_StatusCode->at(WhichMCParticle) == 1
				&& MCParticle_Process->at(WhichMCParticle) == "primary"				
				&& MCTruth_CCNC->at(0) == 0 // CC events
			) {
				
				double MCParticleMomentum = MCParticle_P->at(WhichMCParticle);
				int MCParticlePdg = MCParticle_PdgCode->at(WhichMCParticle);

				if (MCParticlePdg == MuonPdg && MCParticleMomentum > ArrayNBinsMuonMomentum[0])
					{ TrueMuonCounter++; VectorTrueMuonIndex.push_back(WhichMCParticle); }

				if (MCParticlePdg == ProtonPdg && MCParticleMomentum > ArrayNBinsProtonMomentum[0]) 
					{ TrueProtonCounter++; VectorTrueProtonIndex.push_back(WhichMCParticle); }

				if (fabs(MCParticlePdg) == AbsChargedPionPdg && MCParticleMomentum > ChargedPionMomentumThres) 
					{ TrueChargedPionCounter++; }

				if (MCParticlePdg == NeutralPionPdg) { TruePi0Counter++; }

				if (MCParticlePdg == NeutronPdg) { TrueNeutronCounter++; }

				StableMCParticles++;

			} // End of the demand stable final state particles

		} // end of the loop over the MCParticles

		// --------------------------------------------------------------------------------------------------------------------------		

		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 1) {
			fCC1p1pi = 1; 
			CC1p1piCounter++;
		}
		
		// --------------------------------------------------------------------------------------------------------------------------
		
		if (TrueMuonCounter == 1 && TrueProtonCounter == 2 && TrueChargedPionCounter == 0) {
			fCC2p = 1; 
			CC2pCounter++;
		}

		// --------------------------------------------------------------------------------------------------------------------------
		
		if (TrueMuonCounter == 1 && TrueProtonCounter == 2 && TrueChargedPionCounter == 1) {
			fCC2p1pi = 1; 
			CC2p1piCounter++;
		}

		// --------------------------------------------------------------------------------------------------------------------------
		
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 0) {
			fCC3p = 1; 
			CC3pCounter++;
		}

		// --------------------------------------------------------------------------------------------------------------------------
		
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 1) {
			fCC3p1pi = 1; 
			CC3p1piCounter++;
		}

		// --------------------------------------------------------------------------------------------------------------------------
		
		if (TrueMuonCounter == 1 && TrueProtonCounter == 3 && TrueChargedPionCounter == 2) {
			fCC3p2pi = 1; 
			CC3p2piCounter++;
		}
		
		// ------------------------------------------------------------------------------------------------------------------------		

		if (TrueMuonCounter == 1 && TrueProtonCounter == 1 && TrueChargedPionCounter == 0) {
			
		 
			fCC1p = 1; 
			CC1pCounter++; 
			
			// --------------------------------------------------------------------------------------------------------------------------
			
			// Muon MCParticle

			double Muon_MCParticlePx = MCParticle_Px->at(VectorTrueMuonIndex.at(0));
			double Muon_MCParticlePy = MCParticle_Py->at(VectorTrueMuonIndex.at(0));
			double Muon_MCParticlePz = MCParticle_Pz->at(VectorTrueMuonIndex.at(0));
			
			double Muon_MCParticleStartX = MCParticle_Vx->at(VectorTrueMuonIndex.at(0));
			double Muon_MCParticleStartY = MCParticle_Vy->at(VectorTrueMuonIndex.at(0));
			double Muon_MCParticleStartZ = MCParticle_Vz->at(VectorTrueMuonIndex.at(0));
			
			double Muon_MCParticleEndX = MCParticle_EndX->at(VectorTrueMuonIndex.at(0));
			double Muon_MCParticleEndY = MCParticle_EndY->at(VectorTrueMuonIndex.at(0));
			double Muon_MCParticleEndZ = MCParticle_EndZ->at(VectorTrueMuonIndex.at(0));		

			TVector3 Muon_TVector3TrueStart(Muon_MCParticleStartX,Muon_MCParticleStartY,Muon_MCParticleStartZ);
			TVector3 Muon_TVector3TrueEnd(Muon_MCParticleEndX,Muon_MCParticleEndY,Muon_MCParticleEndZ);
//			TVector3 Muon_TVector3TrueChange = Muon_TVector3TrueEnd - Muon_TVector3TrueStart;
			TVector3 Muon_TVector3True(Muon_MCParticlePx,Muon_MCParticlePy,Muon_MCParticlePz);

			bool Muon_TrueStartContainment = tools.inFVVector(Muon_TVector3TrueStart);
			bool Muon_TrueEndContainment = tools.inFVVector(Muon_TVector3TrueEnd);

//			double Muon_TrueLength = Muon_TVector3True.Mag();
			double Muon_TrueTheta = Muon_TVector3True.Theta();
			double Muon_TrueTheta_Deg = Muon_TrueTheta * 180./TMath::Pi();
			double Muon_TruePhi = Muon_TVector3True.Phi();
			double Muon_TruePhi_Deg = Muon_TruePhi * 180./TMath::Pi();
			double Muon_TrueCosTheta = Muon_TVector3True.CosTheta();
			double Muon_TrueMomentum_GeV = MCParticle_P->at(VectorTrueMuonIndex.at(0)); // GeV
//			double Muon_TrueMomentum_MeV = 1000. * Muon_TrueMomentum_GeV; // MeV
//			double Muon_TrueKE_MeV = tools.PToKE(MCParticle_PdgCode->at(VectorTrueMuonIndex.at(0)),Muon_TrueMomentum_MeV); // MeV
//			double Muon_TrueKE_GeV = Muon_TrueKE_MeV / 1000.; // GeV
//			double Muon_TrueE_GeV = Muon_TrueKE_GeV + MuonMass_GeV; // GeV			
			double Muon_TrueE_GeV = TMath::Sqrt( TMath::Power(Muon_TrueMomentum_GeV,2.) + TMath::Power(MuonMass_GeV,2.) ); // GeV			
			
			Muon_MCParticle_Mode.push_back(MCTruth_Mode->at(0));
			Muon_MCParticle_Mom.push_back(Muon_TrueMomentum_GeV);
//			Muon_MCParticle_KE.push_back(Muon_TrueKE_GeV);
			Muon_MCParticle_Phi.push_back(Muon_TruePhi_Deg);
			Muon_MCParticle_CosTheta.push_back(Muon_TrueCosTheta);
//			Muon_MCParticle_Length.push_back(Muon_TrueLength);
			Muon_MCParticle_StartX.push_back(Muon_TVector3TrueStart.X());
			Muon_MCParticle_StartY.push_back(Muon_TVector3TrueStart.Y());
			Muon_MCParticle_StartZ.push_back(Muon_TVector3TrueStart.Z());
			Muon_MCParticle_EndX.push_back(Muon_TVector3TrueEnd.X());
			Muon_MCParticle_EndY.push_back(Muon_TVector3TrueEnd.Y());
			Muon_MCParticle_EndZ.push_back(Muon_TVector3TrueEnd.Z());
			Muon_MCParticle_StartContainment.push_back(Muon_TrueStartContainment);
			Muon_MCParticle_EndContainment.push_back(Muon_TrueEndContainment);
			Muon_MCParticle_Pdg.push_back(MCParticle_PdgCode->at(VectorTrueMuonIndex.at(0)));
			
			// --------------------------------------------------------------------------------------------------------------------------
			
			// Proton MCParticle

			double Proton_MCParticlePx = MCParticle_Px->at(VectorTrueProtonIndex.at(0));
			double Proton_MCParticlePy = MCParticle_Py->at(VectorTrueProtonIndex.at(0));
			double Proton_MCParticlePz = MCParticle_Pz->at(VectorTrueProtonIndex.at(0));
			
			double Proton_MCParticleStartX = MCParticle_Vx->at(VectorTrueProtonIndex.at(0));
			double Proton_MCParticleStartY = MCParticle_Vy->at(VectorTrueProtonIndex.at(0));
			double Proton_MCParticleStartZ = MCParticle_Vz->at(VectorTrueProtonIndex.at(0));
			
			double Proton_MCParticleEndX = MCParticle_EndX->at(VectorTrueProtonIndex.at(0));
			double Proton_MCParticleEndY = MCParticle_EndY->at(VectorTrueProtonIndex.at(0));
			double Proton_MCParticleEndZ = MCParticle_EndZ->at(VectorTrueProtonIndex.at(0));		

			TVector3 Proton_TVector3TrueStart(Proton_MCParticleStartX,Proton_MCParticleStartY,Proton_MCParticleStartZ);
			TVector3 Proton_TVector3TrueEnd(Proton_MCParticleEndX,Proton_MCParticleEndY,Proton_MCParticleEndZ);
//			TVector3 Proton_TVector3TrueChange = Proton_TVector3TrueEnd - Proton_TVector3TrueStart;
			TVector3 Proton_TVector3True(Proton_MCParticlePx,Proton_MCParticlePy,Proton_MCParticlePz);

			bool Proton_TrueStartContainment = tools.inFVVector(Proton_TVector3TrueStart);
			bool Proton_TrueEndContainment = tools.inFVVector(Proton_TVector3TrueEnd);

//			double Proton_TrueLength = Proton_TVector3TrueChange.Mag();
			double Proton_TrueTheta = Proton_TVector3True.Theta();
			double Proton_TrueTheta_Deg = Proton_TrueTheta * 180./TMath::Pi();
			double Proton_TruePhi = Proton_TVector3True.Phi();
			double Proton_TruePhi_Deg = Proton_TruePhi * 180./TMath::Pi();
			double Proton_TrueCosTheta = Proton_TVector3True.CosTheta();
			double Proton_TrueMomentum_GeV = MCParticle_P->at(VectorTrueProtonIndex.at(0)); // GeV
//			double Proton_TrueMomentum_MeV = 1000. * Proton_TrueMomentum_GeV; // MeV
//			double Proton_TrueKE_MeV = tools.PToKE(MCParticle_PdgCode->at(VectorTrueProtonIndex.at(0)),Proton_TrueMomentum_MeV); // MeV
//			double Proton_TrueKE_GeV = Proton_TrueKE_MeV / 1000.; // GeV
//			double Proton_TrueE_GeV = Proton_TrueKE_GeV + ProtonMass_GeV; // GeV						
			double Proton_TrueE_GeV = TMath::Sqrt( TMath::Power(Proton_TrueMomentum_GeV,2.) + TMath::Power(ProtonMass_GeV,2.) ); // GeV						
			
			Proton_MCParticle_Mode.push_back(MCTruth_Mode->at(0));
			Proton_MCParticle_Mom.push_back(Proton_TrueMomentum_GeV);
//			Proton_MCParticle_KE.push_back(Proton_TrueKE_GeV);
			Proton_MCParticle_Phi.push_back(Proton_TruePhi_Deg);
			Proton_MCParticle_CosTheta.push_back(Proton_TrueCosTheta);
//			Proton_MCParticle_Length.push_back(Proton_TrueLength);
			Proton_MCParticle_StartX.push_back(Proton_TVector3TrueStart.X());
			Proton_MCParticle_StartY.push_back(Proton_TVector3TrueStart.Y());
			Proton_MCParticle_StartZ.push_back(Proton_TVector3TrueStart.Z());
			Proton_MCParticle_EndX.push_back(Proton_TVector3TrueEnd.X());
			Proton_MCParticle_EndY.push_back(Proton_TVector3TrueEnd.Y());
			Proton_MCParticle_EndZ.push_back(Proton_TVector3TrueEnd.Z());
			Proton_MCParticle_StartContainment.push_back(Proton_TrueStartContainment);
			Proton_MCParticle_EndContainment.push_back(Proton_TrueEndContainment);
			Proton_MCParticle_Pdg.push_back(MCParticle_PdgCode->at(VectorTrueProtonIndex.at(0)));
			
			// --------------------------------------------------------------------------------------------------------------------
			
			// STV & Energy Reconstruction
			
			TVector3 True_TVector3CandidateMuon(-1,-1,-1);
			True_TVector3CandidateMuon.SetMag(Muon_TrueMomentum_GeV);
			True_TVector3CandidateMuon.SetTheta(Muon_TrueTheta);
			True_TVector3CandidateMuon.SetPhi(Muon_TruePhi);

			TVector3 True_TVector3CandidateProton(-1,-1,-1);
			True_TVector3CandidateProton.SetMag(Proton_TrueMomentum_GeV);
			True_TVector3CandidateProton.SetTheta(Proton_TrueTheta);
			True_TVector3CandidateProton.SetPhi(Proton_TruePhi);

			STV_Tools stv_tool(True_TVector3CandidateMuon,True_TVector3CandidateProton,Muon_TrueE_GeV,Proton_TrueE_GeV);

			True_kMiss.push_back(stv_tool.ReturnkMiss());
			True_EMiss.push_back(stv_tool.ReturnEMiss());
			True_PMissMinus.push_back(stv_tool.ReturnPMissMinus());
			True_PMiss.push_back(stv_tool.ReturnPMiss());
			True_Pt.push_back(stv_tool.ReturnPt());
			True_DeltaAlphaT.push_back(stv_tool.ReturnDeltaAlphaT());
			True_DeltaPhiT.push_back(stv_tool.ReturnDeltaPhiT());
			True_ECal.push_back(stv_tool.ReturnECal());
			True_EQE.push_back(stv_tool.ReturnEQE());
			True_Q2.push_back(stv_tool.ReturnQ2());
			
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
			
		} else {
		
			double NotCC1pSignal = -999.;
			int IntNotCC1pSignal = -999;			
		
			Muon_MCParticle_Mode.push_back(IntNotCC1pSignal);
			Muon_MCParticle_Mom.push_back(NotCC1pSignal);
//			Muon_MCParticle_KE.push_back(NotCC1pSignal);
			Muon_MCParticle_Phi.push_back(NotCC1pSignal);
			Muon_MCParticle_CosTheta.push_back(NotCC1pSignal);
//			Muon_MCParticle_Length.push_back(NotCC1pSignal);
			Muon_MCParticle_StartX.push_back(NotCC1pSignal);
			Muon_MCParticle_StartY.push_back(NotCC1pSignal);
			Muon_MCParticle_StartZ.push_back(NotCC1pSignal);
			Muon_MCParticle_EndX.push_back(NotCC1pSignal);
			Muon_MCParticle_EndY.push_back(NotCC1pSignal);
			Muon_MCParticle_EndZ.push_back(NotCC1pSignal);
			Muon_MCParticle_StartContainment.push_back(IntNotCC1pSignal);
			Muon_MCParticle_EndContainment.push_back(IntNotCC1pSignal);
			Muon_MCParticle_Pdg.push_back(IntNotCC1pSignal);
			
			Proton_MCParticle_Mode.push_back(IntNotCC1pSignal);
			Proton_MCParticle_Mom.push_back(NotCC1pSignal);
//			Proton_MCParticle_KE.push_back(NotCC1pSignal);
			Proton_MCParticle_Phi.push_back(NotCC1pSignal);
			Proton_MCParticle_CosTheta.push_back(NotCC1pSignal);
			Proton_MCParticle_Length.push_back(NotCC1pSignal);
			Proton_MCParticle_StartX.push_back(NotCC1pSignal);
			Proton_MCParticle_StartY.push_back(NotCC1pSignal);
			Proton_MCParticle_StartZ.push_back(NotCC1pSignal);
			Proton_MCParticle_EndX.push_back(NotCC1pSignal);
			Proton_MCParticle_EndY.push_back(NotCC1pSignal);
			Proton_MCParticle_EndZ.push_back(NotCC1pSignal);
			Proton_MCParticle_StartContainment.push_back(IntNotCC1pSignal);
			Proton_MCParticle_EndContainment.push_back(IntNotCC1pSignal);
			Proton_MCParticle_Pdg.push_back(IntNotCC1pSignal);

			True_kMiss.push_back(NotCC1pSignal);
			True_EMiss.push_back(NotCC1pSignal);
			True_PMissMinus.push_back(NotCC1pSignal);
			True_PMiss.push_back(NotCC1pSignal);			
			True_Pt.push_back(NotCC1pSignal);
			True_DeltaAlphaT.push_back(NotCC1pSignal);
			True_DeltaPhiT.push_back(NotCC1pSignal);
			True_ECal.push_back(NotCC1pSignal);
			True_EQE.push_back(NotCC1pSignal);
			True_Q2.push_back(NotCC1pSignal);
			
			True_DeltaPhi.push_back(NotCC1pSignal);
			True_DeltaTheta.push_back(NotCC1pSignal);		
			
		}
		
		// --------------------------------------------------------------------------------------------------------------------------		
		
		CC1p = fCC1p;
		CC1p1pi = fCC1p1pi;
		CC2p = fCC2p;	
		CC2p1pi = fCC2p1pi;
		CC3p = fCC3p;
		CC3p1pi = fCC3p1pi;
		CC3p2pi = fCC3p2pi;			

		NumberMCParticles = StableMCParticles;	
		NumberPi0 = TruePi0Counter;
		NumberNeutrons = TrueNeutronCounter;
		
		// --------------------------------------------------------------------------------------------------------------------------		

		// True vertex containment has been established in previous continue statement
		// Now we have to establish that we satisfy the CC1p signal definition
		if (CC1p == 0 /*|| Muon_MCParticle_StartContainment.at(0) == 0*/ ) { continue; }
		tree->Fill();

	} // End of the loop over the number of events

	// -------------------------------------------------------------------------------------------------------------------------------------------
	// --------------------------------------------------------------------------------------------------------------------------------------------

	// To be printed at the end of the run

	int precision = 2;

	std::cout.precision(precision);
	std::cout << "\n\nTotal of " << nentries << " samdef events processed (" << int(100.*double(nentries)/double(nentries)) << " %)" << std::endl << std::endl;
	std::cout << "\n\nTotal of " << ContainedEventCounter << " contained events processed (" << int(100.*double(ContainedEventCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	std::cout << "\n\nTotal of " << CC1pCounter << " CC1p events processed (" << int(100.*double(CC1pCounter)/double(nentries)) << " %)" << std::endl << std::endl;	
	std::cout << "\n\nTotal of " << CC1p1piCounter << " CC1p1pi events processed (" << int(100.*double(CC1p1piCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	std::cout << "\n\nTotal of " << CC2pCounter << " CC2p events processed (" << int(100.*double(CC2pCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	std::cout << "\n\nTotal of " << CC2p1piCounter << " CC2p1pi events processed (" << int(100.*double(CC2p1piCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	std::cout << "\n\nTotal of " << CC3pCounter << " CC3p events processed (" << int(100.*double(CC3pCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	std::cout << "\n\nTotal of " << CC3p1piCounter << " CC3p1pi events processed (" << int(100.*double(CC3p1piCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	std::cout << "\n\nTotal of " << CC3p2piCounter << " CC3p2pi events processed (" << int(100.*double(CC3p2piCounter)/double(nentries)) << " %)" << std::endl << std::endl;

	// --------------------------------------------------------------------------------------------------------------------------------------------

	myTxtFile << "\n\nTotal of " << nentries << " events processed (" << int(100.*double(nentries)/double(nentries)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\nTotal of " << ContainedEventCounter << " contained events processed (" << int(100.*double(ContainedEventCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\nTotal of " << CC1pCounter << " CC1p events processed (" << int(100.*double(CC1pCounter)/double(nentries)) << " %)" << std::endl << std::endl;	
	myTxtFile << "\n\nTotal of " << CC1p1piCounter << " CC1p1pi events processed (" << int(100.*double(CC1p1piCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\nTotal of " << CC2pCounter << " CC2p events processed (" << int(100.*double(CC2pCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\nTotal of " << CC2p1piCounter << " CC2p1pi events processed (" << int(100.*double(CC2p1piCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\nTotal of " << CC3pCounter << " CC3p events processed (" << int(100.*double(CC3pCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\nTotal of " << CC3p1piCounter << " CC3p1pi events processed (" << int(100.*double(CC3p1piCounter)/double(nentries)) << " %)" << std::endl << std::endl;
	myTxtFile << "\n\nTotal of " << CC3p2piCounter << " CC3p2pi events processed (" << int(100.*double(CC3p2piCounter)/double(nentries)) << " %)" << std::endl << std::endl;

	// --------------------------------------------------------------------------------------------------------------------------------------------

	OutputFile->cd();
	OutputFile->Write();
	OutputFile->Close();
	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;
	myTxtFile.close();

} // end of the program

// --------------------------------------------------------------------------------------------------------------------------------------------
