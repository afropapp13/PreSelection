#define myPreFilter_cxx
#include "myPreFilter.h"
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

void myPreFilter::Loop() {

   //----------------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();   

   //----------------------------------------//

	// Output Files

	TString FileName = "/uboone/data/users/apapadop/PeLEETuples/PreTruthSelection_GENIEv2Overlay9_Combined_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

   //----------------------------------------//

   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   //----------------------------------------//

	// TTree

	TTree* tree = new TTree("myPreTruthSelection","myPreTruthSelection");

   //----------------------------------------//

//	int PassedSwTrigger;
	double Weight;
	double T2KWeight;
	double ROOTinoWeight;
	double POTWeight;

	int run;
	int subrun;
	int event;

//	std::vector<unsigned short> genie;
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

	std::vector<double> fluxes;

	std::vector<double> reinteractions;

   //----------------------------------------//

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
	int CC3p3pi;
	int CC4p0pi;
	int CC4p1pi;

	int NumberPi0;
	int NumberNeutrons;		
	int NumberProtons;
	int NumberMuons;
	int NumberChargedPions;

   //----------------------------------------//

	std::vector<int> Muon_MCParticle_Mode;
	std::vector<double> Muon_MCParticle_Mom;
//	std::vector<double> Muon_MCParticle_KE;
	std::vector<double> Muon_MCParticle_Phi;
	std::vector<double> Muon_MCParticle_CosTheta;
//	std::vector<double> Muon_MCParticle_Length;
	std::vector<double> Muon_MCParticle_StartX;
	std::vector<double> Muon_MCParticle_StartY;
	std::vector<double> Muon_MCParticle_StartZ;
	std::vector<int> Muon_MCParticle_StartContainment;
	std::vector<double> Muon_MCParticle_EndX;
	std::vector<double> Muon_MCParticle_EndY;
	std::vector<double> Muon_MCParticle_EndZ;
	std::vector<int> Muon_MCParticle_EndContainment;
	std::vector<int> Muon_MCParticle_Pdg;

   //----------------------------------------//   

	std::vector<int> Proton_MCParticle_Mode;
	std::vector<double> Proton_MCParticle_Mom;
//	std::vector<double> Proton_MCParticle_KE;
	std::vector<double> Proton_MCParticle_Phi;
	std::vector<double> Proton_MCParticle_CosTheta;
	std::vector<double> Proton_MCParticle_Length;
	std::vector<double> Proton_MCParticle_StartX;
	std::vector<double> Proton_MCParticle_StartY;
	std::vector<double> Proton_MCParticle_StartZ;
	std::vector<int> Proton_MCParticle_StartContainment;
	std::vector<double> Proton_MCParticle_EndX;
	std::vector<double> Proton_MCParticle_EndY;
	std::vector<double> Proton_MCParticle_EndZ;
	std::vector<int> Proton_MCParticle_EndContainment;
	std::vector<int> Proton_MCParticle_Pdg;

   //----------------------------------------//   

	// STV, Energy Reconstruction & Light Cone Variables	

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

   //----------------------------------------//
   //----------------------------------------//

	tree->Branch("Weight",&Weight);
	tree->Branch("T2KWeight",&T2KWeight);
	tree->Branch("ROOTinoWeight",&ROOTinoWeight);	
	tree->Branch("POTWeight",&POTWeight);	

	tree->Branch("Run",&run);
	tree->Branch("SubRun",&subrun);
	tree->Branch("Event",&event);	

//	tree->Branch("genie", &genie);
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

	tree->Branch("fluxes", &fluxes);

	tree->Branch("reinteractions", &reinteractions);

   //----------------------------------------//

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
	tree->Branch("CC3p3pi",&CC3p3pi);
	tree->Branch("CC4p0pi",&CC4p0pi);
	tree->Branch("CC4p1pi",&CC4p1pi);

	tree->Branch("NumberPi0",&NumberPi0);
	tree->Branch("NumberNeutrons",&NumberNeutrons);
	tree->Branch("NumberProtons",&NumberProtons);
	tree->Branch("NumberMuons",&NumberMuons);
	tree->Branch("NumberChargedPions",&NumberChargedPions);

   //----------------------------------------//

	tree->Branch("Muon_MCParticle_Mode",&Muon_MCParticle_Mode);
	tree->Branch("Muon_MCParticle_Mom",&Muon_MCParticle_Mom);
//	tree->Branch("Muon_MCParticle_KE",&Muon_MCParticle_KE);
	tree->Branch("Muon_MCParticle_Phi",&Muon_MCParticle_Phi);
	tree->Branch("Muon_MCParticle_CosTheta",&Muon_MCParticle_CosTheta);
//	tree->Branch("Muon_MCParticle_Length",&Muon_MCParticle_Length);
	tree->Branch("Muon_MCParticle_StartX",&Muon_MCParticle_StartX);
	tree->Branch("Muon_MCParticle_StartY",&Muon_MCParticle_StartY);
	tree->Branch("Muon_MCParticle_StartZ",&Muon_MCParticle_StartZ);
	tree->Branch("Muon_MCParticle_StartContainment",&Muon_MCParticle_StartContainment);
	tree->Branch("Muon_MCParticle_EndX",&Muon_MCParticle_EndX);
	tree->Branch("Muon_MCParticle_EndY",&Muon_MCParticle_EndY);
	tree->Branch("Muon_MCParticle_EndZ",&Muon_MCParticle_EndZ);
	tree->Branch("Muon_MCParticle_EndContainment",&Muon_MCParticle_EndContainment);
	tree->Branch("Muon_MCParticle_Pdg",&Muon_MCParticle_Pdg);

   //----------------------------------------//

	tree->Branch("Proton_MCParticle_Mode",&Proton_MCParticle_Mode);
	tree->Branch("Proton_MCParticle_Mom",&Proton_MCParticle_Mom);
//	tree->Branch("Proton_MCParticle_KE",&Proton_MCParticle_KE);
	tree->Branch("Proton_MCParticle_Phi",&Proton_MCParticle_Phi);
	tree->Branch("Proton_MCParticle_CosTheta",&Proton_MCParticle_CosTheta);
	tree->Branch("Proton_MCParticle_Length",&Proton_MCParticle_Length);
	tree->Branch("Proton_MCParticle_StartX",&Proton_MCParticle_StartX);
	tree->Branch("Proton_MCParticle_StartY",&Proton_MCParticle_StartY);
	tree->Branch("Proton_MCParticle_StartZ",&Proton_MCParticle_StartZ);
	tree->Branch("Proton_MCParticle_StartContainment",&Proton_MCParticle_StartContainment);
	tree->Branch("Proton_MCParticle_EndX",&Proton_MCParticle_EndX);
	tree->Branch("Proton_MCParticle_EndY",&Proton_MCParticle_EndY);
	tree->Branch("Proton_MCParticle_EndZ",&Proton_MCParticle_EndZ);
	tree->Branch("Proton_MCParticle_EndContainment",&Proton_MCParticle_EndContainment);
	tree->Branch("Proton_MCParticle_Pdg",&Proton_MCParticle_Pdg);

   //----------------------------------------//            

	tree->Branch("True_A",&True_A);
	tree->Branch("True_kMiss",&True_kMiss);
	tree->Branch("True_EMiss",&True_EMiss);
	tree->Branch("True_PMissMinus",&True_PMissMinus);
	tree->Branch("True_PMiss",&True_PMiss);
	tree->Branch("True_Pt",&True_Pt);
	tree->Branch("True_Ptx",&True_Ptx);
	tree->Branch("True_Pty",&True_Pty);
	tree->Branch("True_PL",&True_PL);
	tree->Branch("True_Pn",&True_Pn);
	tree->Branch("True_PnPerp",&True_PnPerp);
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

   //----------------------------------------//

	Tools tools;

   //----------------------------------------//

	// Counters
	int SelectedEvents = 0; 
	int TotalCounter = 0;
	int CC1pCounter = 0;
	int CC1p1piCounter = 0;
	int CC2pCounter = 0;
	int CC2p1piCounter = 0;
	int CC3pCounter = 0;
	int CC3p1piCounter = 0;
	int CC3p2piCounter = 0;	
	int CC3p3piCounter = 0;	
	int CC4p0piCounter = 0;	
	int CC4p1piCounter = 0;	
	int ContainedEventCounter = 0;
	int MultipleMCTruth = 0;

	TH1D* SamdefEventPlot = new TH1D("SamdefEventPlot",";# samdef events",1,0,1);
	SamdefEventPlot->SetBinContent(1,fChain->GetEntries());	

   //----------------------------------------//

	TString PathToPOTFile = "/uboone/data/users/apapadop/PeLEETuples/PreSelection_GENIEv2Overlay9_Combined_"+UBCodeVersion+"_POT.root";

	TFile* POTFile = TFile::Open(PathToPOTFile,"readonly");
	TH1D* POTCountHist = (TH1D*)(POTFile->Get("POTCountHist"));
	double POTCount = POTCountHist->GetBinContent(1);
	POTFile->Close();

   //----------------------------------------//

   POTWeight = Fulltor860_wcut_Combined / POTCount;

   //----------------------------------------//      

   for (Long64_t jentry=0; jentry<nentries;jentry++) {

      //----------------------------------------//

      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      TotalCounter++;

      //----------------------------------------//

		if (jentry%1000 == 0) std::cout << jentry/1000 << " k " << std::setprecision(3) << double(jentry)/nentries*100. << " %"<< std::endl;      

      //----------------------------------------//

		Weight = 1.;
		T2KWeight = 1.;
		ROOTinoWeight = 1.;      

      //----------------------------------------//

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
		Muon_MCParticle_StartContainment.clear();
		Muon_MCParticle_EndX.clear();
		Muon_MCParticle_EndY.clear();
		Muon_MCParticle_EndZ.clear();
		Muon_MCParticle_EndContainment.clear();
		Muon_MCParticle_Pdg.clear();

      //----------------------------------------//

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
		Proton_MCParticle_StartContainment.clear();
		Proton_MCParticle_EndX.clear();
		Proton_MCParticle_EndY.clear();
		Proton_MCParticle_EndZ.clear();
		Proton_MCParticle_EndContainment.clear();
		Proton_MCParticle_Pdg.clear();

      //----------------------------------------//

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

      //----------------------------------------//

      // Check that we have primary processes
      // and CC events (0)

      if (*Process != "primary") { continue; }
      if (Ccnc != 0) { continue; }      

      //----------------------------------------//

		run = Run;
		subrun = SubRun;
		event = Event;

      //----------------------------------------//

      int NMCParticles = Pdgcode->size();

 		int StableMCParticles = 0;
		int fCC1p = 0;
		int fCC1p1pi = 0;
		int fCC2p = 0;	
		int fCC2p1pi = 0;
		int fCC3p = 0;	
		int fCC3p1pi = 0;
		int fCC3p2pi = 0;			
		int fCC3p3pi = 0;
		int fCC4p0pi = 0;
		int fCC4p1pi = 0;
      int TrueNuMuCounter = 0;
		int TrueMuonCounter = 0, TrueProtonCounter = 0;
      int TrueChargedPionCounter = 0,TruePi0Counter = 0;
      int TrueNeutronCounter = 0, TrueHeavierMesonCounter = 0;
		
		std::vector<int> VectorTrueMuonIndex; VectorTrueMuonIndex.clear();
		std::vector<int> VectorTrueProtonIndex; VectorTrueProtonIndex.clear();		

      //----------------------------------------//

		// Loop over the MCParticles and determine the populations

		for (int WhichMCParticle = 0; WhichMCParticle < NMCParticles; WhichMCParticle++) {

         //----------------------------------------//

			TVector3 MCParticle(Px->at(WhichMCParticle),Py->at(WhichMCParticle),Pz->at(WhichMCParticle));
			double MCParticleMomentum = P->at(WhichMCParticle);
			int MCParticlePdg = Pdgcode->at(WhichMCParticle);

         //----------------------------------------//

         // numu selection
         // initial state particle -> status = 0

         if (
            MCParticlePdg == NuMuPdg && 
            Status->at(WhichMCParticle) == 0
         ) {

            True_Ev = E->at(WhichMCParticle);
            True_Vx = Start_X->at(WhichMCParticle);
            True_Vy = Start_Y->at(WhichMCParticle);
            True_Vz = Start_Z->at(WhichMCParticle);		
            TVector3 TrueNu_Vertex(True_Vx,True_Vy,True_Vz);
		      bool TrueNu_Vertex_Containment = tools.inFVVector(TrueNu_Vertex);
		      if (TrueNu_Vertex_Containment == 1) 
               { TrueNuMuCounter++; }

         }         

         //----------------------------------------//

         // Only stable final-state particles
         // from here on

         if (Status->at(WhichMCParticle) != 1) { continue; }

         //----------------------------------------//

			if ( 
            MCParticlePdg == MuonPdg && 
            MCParticleMomentum >= ArrayNBinsMuonMomentum[0]
            ) { 
               TrueMuonCounter++;  
               VectorTrueMuonIndex.push_back(WhichMCParticle); 
            }

         //----------------------------------------//

			if ( 
            MCParticlePdg == ProtonPdg && 
            MCParticleMomentum >= ArrayNBinsProtonMomentum[0] 
            ) { 
               TrueProtonCounter++; 
               VectorTrueProtonIndex.push_back(WhichMCParticle); 
            }

         //----------------------------------------//

			if ( 
            fabs(MCParticlePdg) == AbsChargedPionPdg && 
            MCParticleMomentum >= ChargedPionMomentumThres 
         ) { TrueChargedPionCounter++; }

         //----------------------------------------//

			if (MCParticlePdg == NeutralPionPdg) 
            { TruePi0Counter++; }

         //----------------------------------------//

			if (MCParticlePdg == NeutronPdg) 
            { TrueNeutronCounter++; }

         //----------------------------------------//

			if ( 
            MCParticlePdg != NeutralPionPdg && 
            fabs(MCParticlePdg) != AbsChargedPionPdg && 
            tools.is_meson_or_antimeson(MCParticlePdg) 
         ) { TrueHeavierMesonCounter++; } 

         //----------------------------------------//                       

      }

      //----------------------------------------//

      // numu CC1p0pi selection

      if (TrueNuMuCounter != 1) { continue; }
      if (TrueMuonCounter != 1) { continue; } 
      if (TrueProtonCounter != 1) { continue; }
      if (TrueChargedPionCounter != 0) { continue; }                  
      if (TruePi0Counter != 0) { continue; }
      if (TrueHeavierMesonCounter != 0) { continue; }      

      //----------------------------------------//                  

      SelectedEvents++;
		fCC1p = 1; 
		CC1pCounter++;

      //----------------------------------------//

		// Muon MCParticle

		double Muon_MCParticlePx = Px->at(VectorTrueMuonIndex.at(0));
		double Muon_MCParticlePy = Py->at(VectorTrueMuonIndex.at(0));
		double Muon_MCParticlePz = Pz->at(VectorTrueMuonIndex.at(0));
			
		double Muon_MCParticleStartX = Start_X->at(VectorTrueMuonIndex.at(0));
		double Muon_MCParticleStartY = Start_Y->at(VectorTrueMuonIndex.at(0));
		double Muon_MCParticleStartZ = Start_Z->at(VectorTrueMuonIndex.at(0));

		double Muon_MCParticleEndX = End_X->at(VectorTrueMuonIndex.at(0));
		double Muon_MCParticleEndY = End_Y->at(VectorTrueMuonIndex.at(0));
		double Muon_MCParticleEndZ = End_Z->at(VectorTrueMuonIndex.at(0));	

		TVector3 Muon_TVector3TrueStart(Muon_MCParticleStartX,Muon_MCParticleStartY,Muon_MCParticleStartZ);
		TVector3 Muon_TVector3TrueEnd(Muon_MCParticleEndX,Muon_MCParticleEndY,Muon_MCParticleEndZ);
		TVector3 Muon_TVector3True(Muon_MCParticlePx,Muon_MCParticlePy,Muon_MCParticlePz);

		bool Muon_TrueStartContainment = tools.inFVVector(Muon_TVector3TrueStart);
		bool Muon_TrueEndContainment = tools.inFVVector(Muon_TVector3TrueEnd);

		double Muon_TrueTheta = Muon_TVector3True.Theta();
		double Muon_TrueTheta_Deg = Muon_TrueTheta * 180./TMath::Pi();
		double Muon_TruePhi = Muon_TVector3True.Phi();
		double Muon_TruePhi_Deg = Muon_TruePhi * 180./TMath::Pi();
		double Muon_TrueCosTheta = Muon_TVector3True.CosTheta();
		double Muon_TrueMomentum_GeV = Muon_TVector3True.Mag(); // GeV
		double Muon_TrueE_GeV = TMath::Sqrt( TMath::Power(Muon_TrueMomentum_GeV,2.) + TMath::Power(MuonMass_GeV,2.) ); // GeV			
			
		Muon_MCParticle_Mode.push_back(Mode);
		Muon_MCParticle_Mom.push_back(Muon_TrueMomentum_GeV);
		Muon_MCParticle_Phi.push_back(Muon_TruePhi_Deg);
		Muon_MCParticle_CosTheta.push_back(Muon_TrueCosTheta);
		Muon_MCParticle_StartX.push_back(Muon_TVector3TrueStart.X());
		Muon_MCParticle_StartY.push_back(Muon_TVector3TrueStart.Y());
		Muon_MCParticle_StartZ.push_back(Muon_TVector3TrueStart.Z());
		Muon_MCParticle_StartContainment.push_back(Muon_TrueStartContainment);
		Muon_MCParticle_EndX.push_back(Muon_TVector3TrueEnd.X());
		Muon_MCParticle_EndY.push_back(Muon_TVector3TrueEnd.Y());
		Muon_MCParticle_EndZ.push_back(Muon_TVector3TrueEnd.Z());
		Muon_MCParticle_EndContainment.push_back(Muon_TrueEndContainment);
		Muon_MCParticle_Pdg.push_back(Pdgcode->at(VectorTrueMuonIndex.at(0)));

      //----------------------------------------//

		// Proton MCParticle

		double Proton_MCParticlePx = Px->at(VectorTrueProtonIndex.at(0));
		double Proton_MCParticlePy = Py->at(VectorTrueProtonIndex.at(0));
		double Proton_MCParticlePz = Pz->at(VectorTrueProtonIndex.at(0));
			
		double Proton_MCParticleStartX = Start_X->at(VectorTrueProtonIndex.at(0));
		double Proton_MCParticleStartY = Start_Y->at(VectorTrueProtonIndex.at(0));
		double Proton_MCParticleStartZ = Start_Z->at(VectorTrueProtonIndex.at(0));

		double Proton_MCParticleEndX = End_X->at(VectorTrueProtonIndex.at(0));
		double Proton_MCParticleEndY = End_Y->at(VectorTrueProtonIndex.at(0));
		double Proton_MCParticleEndZ = End_Z->at(VectorTrueProtonIndex.at(0));		

		TVector3 Proton_TVector3TrueStart(Proton_MCParticleStartX,Proton_MCParticleStartY,Proton_MCParticleStartZ);
		TVector3 Proton_TVector3TrueEnd(Proton_MCParticleEndX,Proton_MCParticleEndY,Proton_MCParticleEndZ);
		TVector3 Proton_TVector3True(Proton_MCParticlePx,Proton_MCParticlePy,Proton_MCParticlePz);

		bool Proton_TrueStartContainment = tools.inFVVector(Proton_TVector3TrueStart);
		bool Proton_TrueEndContainment = tools.inFVVector(Proton_TVector3TrueEnd);

		double Proton_TrueTheta = Proton_TVector3True.Theta();
		double Proton_TrueTheta_Deg = Proton_TrueTheta * 180./TMath::Pi();
		double Proton_TruePhi = Proton_TVector3True.Phi();
		double Proton_TruePhi_Deg = Proton_TruePhi * 180./TMath::Pi();
		double Proton_TrueCosTheta = Proton_TVector3True.CosTheta();
		double Proton_TrueMomentum_GeV = Proton_TVector3True.Mag(); // GeV
		double Proton_TrueE_GeV = TMath::Sqrt( TMath::Power(Proton_TrueMomentum_GeV,2.) + TMath::Power(ProtonMass_GeV,2.) ); // GeV						
			
		Proton_MCParticle_Mode.push_back(Mode);
		Proton_MCParticle_Mom.push_back(Proton_TrueMomentum_GeV);
		Proton_MCParticle_Phi.push_back(Proton_TruePhi_Deg);
		Proton_MCParticle_CosTheta.push_back(Proton_TrueCosTheta);
		Proton_MCParticle_StartX.push_back(Proton_TVector3TrueStart.X());
		Proton_MCParticle_StartY.push_back(Proton_TVector3TrueStart.Y());
		Proton_MCParticle_StartZ.push_back(Proton_TVector3TrueStart.Z());
		Proton_MCParticle_StartContainment.push_back(Proton_TrueStartContainment);
		Proton_MCParticle_EndX.push_back(Proton_TVector3TrueEnd.X());
		Proton_MCParticle_EndY.push_back(Proton_TVector3TrueEnd.Y());
		Proton_MCParticle_EndZ.push_back(Proton_TVector3TrueEnd.Z());
		Proton_MCParticle_EndContainment.push_back(Proton_TrueEndContainment);
		Proton_MCParticle_Pdg.push_back(Pdgcode->at(VectorTrueProtonIndex.at(0)));      

      //----------------------------------------//  

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

		True_A.push_back(stv_tool.ReturnA());
		True_kMiss.push_back(stv_tool.ReturnkMiss());
		True_EMiss.push_back(stv_tool.ReturnEMiss());
		True_PMissMinus.push_back(stv_tool.ReturnPMissMinus());
		True_PMiss.push_back(stv_tool.ReturnPMiss());
		True_Pt.push_back(stv_tool.ReturnPt());
		True_Ptx.push_back(stv_tool.ReturnPtx());
		True_Pty.push_back(stv_tool.ReturnPty());
		True_PL.push_back(stv_tool.ReturnPL());
		True_Pn.push_back(stv_tool.ReturnPn());
		True_PnPerp.push_back(stv_tool.ReturnPnPerp());
		True_PnPar.push_back(stv_tool.ReturnPnPar());				
		True_DeltaAlphaT.push_back(stv_tool.ReturnDeltaAlphaT());
		True_DeltaAlpha3Dq.push_back(stv_tool.ReturnDeltaAlpha3Dq());
		True_DeltaAlpha3DMu.push_back(stv_tool.ReturnDeltaAlpha3DMu());		
		True_DeltaPhiT.push_back(stv_tool.ReturnDeltaPhiT());
		True_DeltaPhi3D.push_back(stv_tool.ReturnDeltaPhi3D());		
		True_ECal.push_back(stv_tool.ReturnECal());
		True_EQE.push_back(stv_tool.ReturnEQE());
		True_Q2.push_back(stv_tool.ReturnQ2()); 

      //----------------------------------------// 

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
			                              
      //----------------------------------------//   

		CC1p = fCC1p;			

		NumberMCParticles = StableMCParticles;	
		NumberPi0 = TruePi0Counter;
		NumberNeutrons = TrueNeutronCounter;
		NumberProtons = TrueProtonCounter;
		NumberMuons = TrueMuonCounter;
		NumberChargedPions = TrueChargedPionCounter; 

      //----------------------------------------//                                               

		// Storing only true CC1p events

		if (CC1p == 0) { continue; }
      tree->Fill();       
      
      //----------------------------------------//

   }

   //----------------------------------------//   

	OutputFile->cd();
	OutputFile->Write();
	OutputFile->Close();
	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;
	std::cout << std::endl << "Selected events = " << SelectedEvents << std::endl << std::endl;

   //----------------------------------------//

} // End of the program