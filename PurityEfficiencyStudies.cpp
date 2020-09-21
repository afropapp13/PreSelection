#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLine.h>
#include <TLatex.h>

#include <iostream>
#include <vector>

#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/Constants.h"

using namespace std;
using namespace Constants;

void PurityEfficiencyStudies() {

	gStyle->SetOptStat(0);

	TString RunNumber = "Run1";
//	TString RunNumber = "Run2";
//	TString RunNumber = "Run3";
//	TString RunNumber = "Run4";
//	TString RunNumber = "Run5";

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------	

	TFile* file = new TFile("myPlots/"+UBCodeVersion+"/PurityEfficiencyStudies.root","recreate");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------	

	// POT

	double POTScale = 1.;

	double tor860_wcut = 1;
	double E1DCNT_wcut = 1.;
	double EXT = 1.;

	if (RunNumber == "Run1") {

		tor860_wcut = tor860_wcut_Run1;
		E1DCNT_wcut = E1DCNT_wcut_Run1;
		EXT = EXT_Run1;

	}
	
//	if (RunNumber == "Run2") {

//		tor860_wcut = tor860_wcut_Run2;
//		E1DCNT_wcut = E1DCNT_wcut_Run2;
//		EXT = EXT_Run2;

//	}
	
	if (RunNumber == "Run3") {

		tor860_wcut = tor860_wcut_Run3;
		E1DCNT_wcut = E1DCNT_wcut_Run3;
		EXT = EXT_Run3;

	}
	
//	if (RunNumber == "Run4") {

//		tor860_wcut = tor860_wcut_Run4;
//		E1DCNT_wcut = E1DCNT_wcut_Run4;
//		EXT = EXT_Run4;

//	}

//	if (RunNumber == "Run5") {

//		tor860_wcut = tor860_wcut_Run5;
//		E1DCNT_wcut = E1DCNT_wcut_Run5;
//		EXT = EXT_Run5;

//	}

	TString PathToPOTFile = "/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+RunNumber+"_"+UBCodeVersion+"_POT.root";

	TFile* POTFile = TFile::Open(PathToPOTFile,"readonly");
	TH1D* POTCountHist = (TH1D*)(POTFile->Get("POTCountHist"));
	double POTCount = POTCountHist->GetBinContent(1);
	POTFile->Close();

	TString DirtPathToPOTFile = "/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_OverlayDirt9_"+RunNumber+"_"+UBCodeVersion+"_POT.root";

	TFile* DirtPOTFile = TFile::Open(DirtPathToPOTFile,"readonly");
	TH1D* DirtPOTCountHist = (TH1D*)(DirtPOTFile->Get("POTCountHist"));
	double DirtPOTCount = DirtPOTCountHist->GetBinContent(1);
	DirtPOTFile->Close();

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------	

	TFile* BeamOnRecoFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_BeamOn9_"+RunNumber+"_"+UBCodeVersion+".root","readonly");
	TTree* BeamOnRecoTree = (TTree*)(BeamOnRecoFile->Get("myPreSelection"));

	TFile* ExtBNBRecoFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_ExtBNB9_"+RunNumber+"_"+UBCodeVersion+".root","readonly");
	TTree* ExtBNBRecoTree = (TTree*)(ExtBNBRecoFile->Get("myPreSelection"));

	TFile* DirtRecoFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_OverlayDirt9_"+RunNumber+"_"+UBCodeVersion+".root","readonly");
	TTree* DirtRecoTree = (TTree*)(DirtRecoFile->Get("myPreSelection"));

	TFile* OverlayRecoFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+RunNumber+"_"+UBCodeVersion+".root","readonly");
	TTree* RecoTree = (TTree*)(OverlayRecoFile->Get("myPreSelection"));

	TString RecoCC1pQualifier = "CC1p && CandidateMu_MCParticle_Pdg == 13 && CandidateP_MCParticle_Pdg == 2212 && CandidateMu_StartContainment == 1 && CandidateP_StartContainment == 1 && CandidateP_EndContainment == 1 && True_CandidateMu_StartContainment == 1 && True_CandidateP_StartContainment == 1 && True_CandidateP_EndContainment == 1 && @CandidateMu_P_MCS->size() == 1 && NuScore > 0.04 && Weight > 0 && Weight < 10 && T2KWeight > 0 && T2KWeight < 10 && CandidateP_P_Range > 0.2 && ( (CandidateMu_EndContainment == 1 && CandidateMu_P_Range > 0.1) || (CandidateMu_EndContainment == 0 && CandidateMu_P_MCS > 0.1) ) && CandidateP_P_Range < 1.2 && ( (CandidateMu_EndContainment == 1 && CandidateMu_P_Range < 1.7) || (CandidateMu_EndContainment == 0 && CandidateMu_P_MCS < 1.7) ) && Reco_Pt < 1 && Reco_DeltaPhiT < 135";

	TString RecoQualifier = "CandidateMu_StartContainment == 1 && CandidateP_StartContainment == 1 && CandidateP_EndContainment == 1 && CandidateP_P_Range > 0.2 && ( (CandidateMu_EndContainment == 1 && CandidateMu_P_Range > 0.1) || (CandidateMu_EndContainment == 0 && CandidateMu_P_MCS > 0.1) )  && @CandidateMu_P_MCS->size() == 1 && NuScore > 0.04 && Weight > 0 && Weight < 10 && T2KWeight > 0 && T2KWeight < 10  && CandidateP_P_Range < 1.2 && ( (CandidateMu_EndContainment == 1 && CandidateMu_P_Range < 1.7) || (CandidateMu_EndContainment == 0 && CandidateMu_P_MCS < 1.7) ) && Reco_Pt < 1  && Reco_DeltaPhiT < 135";

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------	

	TFile* OverlayTruthFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreTruthSelection_Overlay9_"+RunNumber+"_"+UBCodeVersion+".root","readonly");
	TTree* TruthTree = (TTree*)(OverlayTruthFile->Get("myPreTruthSelection"));

	TString TruthQualifier = "Muon_MCParticle_StartContainment == 1 && Proton_MCParticle_StartContainment == 1 && Proton_MCParticle_EndContainment == 1  && True_DeltaPhiT < 135  && Weight > 0 && Weight < 10 && T2KWeight > 0 && T2KWeight < 10 && True_Pt < 1 && True_DeltaPhiT < 135";

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Cos Theta bins
	
	int NBinsMuCosTheta = 20;

	double MinMuCosTheta = -1., MaxMuCosTheta = 1.;

	// Nu Score bins // NuScore

//	int NBinsNuScore = 20;
	int NBinsNuScore = 6;

	double MinNuScore = 0., MaxNuScore = 1.;

	double NuScoreStep = (MaxNuScore - MinNuScore) / NBinsNuScore;

	// Proton Chi2 LogLikelihood  bins // CandidateMu_ThreePlaneLogLikelihood

//	int NBinsLL = 20;
	int NBinsLL = 6;

	double MinLL = -5., MaxLL = 5.;

	double LLStep = (MaxLL - MinLL) / NBinsLL;

	TH2D* EfficiencyPlot = new TH2D("EfficiencyPlot",";#nu Score Threshold; #chi^{2} Proton LogLikelihood Threshold",NBinsNuScore,MinNuScore,MaxNuScore,NBinsLL,MinLL,MaxLL);
	TH2D* PurityPlot = new TH2D("PurityPlot",";#nu Score Threshold; #chi^{2} Proton LogLikelihood Threshold",NBinsNuScore,MinNuScore,MaxNuScore,NBinsLL,MinLL,MaxLL);
	TH2D* PurityEfficiencyStudyPlot = new TH2D("PurityEfficiencyStudyPlot",";#nu Score Threshold; #chi^{2} Proton LogLikelihood Threshold",NBinsNuScore,MinNuScore,MaxNuScore,NBinsLL,MinLL,MaxLL);

	TH1D* hTruth = new TH1D("hTruth","hTruth",NBinsMuCosTheta,MinMuCosTheta,MaxMuCosTheta);
	TruthTree->Draw("Muon_MCParticle_CosTheta>>hTruth",TruthQualifier);

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Loop over NuScore

	for (int NuScoreThres = 0; NuScoreThres < NBinsNuScore; NuScoreThres++) {

		double CurrentNuScore = MinNuScore + NuScoreThres * NuScoreStep;

		cout << "Current NuScore Thres = " << CurrentNuScore << endl;

		for (int LLThres = 0; LLThres < NBinsLL; LLThres++) {

			double CurrentLLThres = MinLL + LLThres * LLStep;

			// Dirt Events

			TH1D* hDirt = new TH1D("hDirt_"+TString(std::to_string(CurrentNuScore))+"_"+TString(std::to_string(CurrentLLThres)),"",NBinsMuCosTheta,MinMuCosTheta,MaxMuCosTheta);
			DirtRecoTree->Draw("CandidateMu_CosTheta>>hDirt_"+TString(std::to_string(CurrentNuScore))+"_"+TString(std::to_string(CurrentLLThres)),RecoQualifier+" && NuScore > "+TString(std::to_string(CurrentNuScore))  +" && CandidateP_ThreePlaneLogLikelihood > "+TString(std::to_string(CurrentLLThres)) );

			// ExtBNB Events

			TH1D* hExtBNB = new TH1D("hExtBNB_"+TString(std::to_string(CurrentNuScore))+"_"+TString(std::to_string(CurrentLLThres)),"",NBinsMuCosTheta,MinMuCosTheta,MaxMuCosTheta);
			ExtBNBRecoTree->Draw("CandidateMu_CosTheta>>hExtBNB_"+TString(std::to_string(CurrentNuScore))+"_"+TString(std::to_string(CurrentLLThres)),RecoQualifier+" && NuScore > "+TString(std::to_string(CurrentNuScore))  +" && CandidateP_ThreePlaneLogLikelihood > "+TString(std::to_string(CurrentLLThres)) );

			// CC1p Reco Overlay Events

			TH1D* hRecoCC1p = new TH1D("hRecoCC1p_"+TString(std::to_string(CurrentNuScore))+"_"+TString(std::to_string(CurrentLLThres)),"",NBinsMuCosTheta,MinMuCosTheta,MaxMuCosTheta);
			RecoTree->Draw("CandidateMu_CosTheta>>hRecoCC1p_"+TString(std::to_string(CurrentNuScore))+"_"+TString(std::to_string(CurrentLLThres)),RecoCC1pQualifier+" && NuScore > "+TString(std::to_string(CurrentNuScore)) +" && CandidateP_ThreePlaneLogLikelihood > "+TString(std::to_string(CurrentLLThres)) );

			// All Reco Overlay Events

			TH1D* hReco = new TH1D("hReco_"+TString(std::to_string(CurrentNuScore))+"_"+TString(std::to_string(CurrentLLThres)),"",NBinsMuCosTheta,MinMuCosTheta,MaxMuCosTheta);
			RecoTree->Draw("CandidateMu_CosTheta>>hReco_"+TString(std::to_string(CurrentNuScore))+"_"+TString(std::to_string(CurrentLLThres)),RecoQualifier+" && NuScore > "+TString(std::to_string(CurrentNuScore))  +" && CandidateP_ThreePlaneLogLikelihood > "+TString(std::to_string(CurrentLLThres)) );

			double NRecoCC1p = (tor860_wcut/POTCount) * hRecoCC1p->GetEntries(); 
			double NReco = (tor860_wcut/POTCount) * hReco->GetEntries(); 
			double NExtBNB = (E1DCNT_wcut/EXT) * hExtBNB->GetEntries(); 
			double NDirt = (tor860_wcut/DirtPOTCount) * hDirt->GetEntries(); 

			double purity = NRecoCC1p / ( NReco + NExtBNB + NDirt) ;
			double efficiency = hRecoCC1p->GetEntries() / hTruth->GetEntries();
			double product = purity * efficiency; 

			EfficiencyPlot->SetBinContent(NuScoreThres+1,LLThres+1,efficiency);
			PurityPlot->SetBinContent(NuScoreThres+1,LLThres+1,purity);
			PurityEfficiencyStudyPlot->SetBinContent(NuScoreThres+1,LLThres+1,product);

		} // End of the loop over the 

	} // End of the loop over nu score steps

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	double max = PurityEfficiencyStudyPlot->GetMaximum();
cout << "max = " << max << endl;
	double XBin = PurityEfficiencyStudyPlot->GetXaxis()->FindBin(max);
cout << "XBin = " << XBin << endl;
	double YBin = PurityEfficiencyStudyPlot->GetYaxis()->FindBin(max);
cout << "YBin = " << YBin << endl;
cout << "FindBin = " << PurityEfficiencyStudyPlot->FindBin(max) << endl;

	double OptimizedNuScoreThres = PurityEfficiencyStudyPlot->GetXaxis()->GetBinLowEdge(XBin);
	double OptimizedLLThres = PurityEfficiencyStudyPlot->GetYaxis()->GetBinLowEdge(YBin);

	// BeamOn Events

	TH1D* hBeamOn = new TH1D("hBeamOn","hBeamOn",NBinsMuCosTheta,MinMuCosTheta,MaxMuCosTheta);
	BeamOnRecoTree->Draw("CandidateMu_CosTheta>>hBeamOn",RecoQualifier+" && NuScore > "+TString(std::to_string(OptimizedNuScoreThres))  +" && CandidateP_ThreePlaneLogLikelihood > "+TString(std::to_string(OptimizedLLThres)) );

	cout << "After optimizing cuts and maximizing purity*efficiency, the max is obtained at v Score (XBin) = " << OptimizedNuScoreThres << " (" << XBin << ")";
	cout << " and at LL (YBin) = " << OptimizedLLThres << " (" << YBin << ")" << endl;
	cout << "That corresponds to " << hBeamOn->GetEntries() << " beam on events" << endl;

	TH1D* hBeamOnDefault = new TH1D("hBeamOnDefault","hBeamOnDefault",NBinsMuCosTheta,MinMuCosTheta,MaxMuCosTheta);
	BeamOnRecoTree->Draw("CandidateMu_CosTheta>>hBeamOnDefault",RecoQualifier+" && NuScore > 0.6 && CandidateP_ThreePlaneLogLikelihood > -1" );

	cout << "The current selection with v Score > 0.6 and at LL > -1 corresponds to " << hBeamOnDefault->GetEntries() << " beam on events" << endl;	

	TCanvas* PurityEfficiencyStudyCanvas = new TCanvas("PurityEfficiencyStudyCanvas","PurityEfficiencyStudyCanvas",205,34,1024,768);
	PurityEfficiencyStudyPlot->Draw("text coltz");

	TCanvas* PurityCanvas = new TCanvas("PurityCanvas","PurityCanvas",205,34,1024,768);
	PurityPlot->Draw("text coltz");

	TCanvas* EfficiencyCanvas = new TCanvas("EfficiencyCanvas","EfficiencyCanvas",205,34,1024,768);
	EfficiencyPlot->Draw("text coltz");

	file->cd();
	PurityEfficiencyStudyPlot->Write();
	PurityPlot->Write();
	EfficiencyPlot->Write();
	file->Close();

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

} // End of the program 
