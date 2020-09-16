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

	TFile* OverlayRecoFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+RunNumber+"_"+UBCodeVersion+".root","readonly");
	TTree* RecoTree = (TTree*)(OverlayRecoFile->Get("myPreSelection"));

	TString RecoCC1pQualifier = "CC1p && CandidateMu_MCParticle_Pdg == 13 && CandidateP_MCParticle_Pdg == 2212 && CandidateMu_StartContainment == 1 && CandidateP_StartContainment == 1 && CandidateP_EndContainment == 1 && True_CandidateMu_StartContainment == 1 && True_CandidateP_StartContainment == 1 && True_CandidateP_EndContainment == 1";
	TString RecoQualifier = "CandidateMu_StartContainment == 1 && CandidateP_StartContainment == 1 && CandidateP_EndContainment == 1";

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------	

	TFile* OverlayTruthFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreTruthSelection_Overlay9_"+RunNumber+"_"+UBCodeVersion+".root","readonly");
	TTree* TruthTree = (TTree*)(OverlayTruthFile->Get("myPreTruthSelection"));

	TString TruthQualifier = "Muon_MCParticle_StartContainment == 1 && Proton_MCParticle_StartContainment == 1 && Proton_MCParticle_EndContainment == 1";

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Cos Theta bins
	
	int NBinsMuCosTheta = 20;

	double MinMuCosTheta = -1., MaxMuCosTheta = 1.;

	// Nu Score bins // NuScore

	int NBinsNuScore = 20;

	double MinNuScore = 0., MaxNuScore = 1.;

	double NuScoreStep = (MaxNuScore - MinNuScore) / NBinsNuScore;

	// Proton Chi2 LogLikelihood  bins // CandidateMu_ThreePlaneLogLikelihood

	int NBinsLL = 20;

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

		for (int LLThres = 0; LLThres < NBinsLL; LLThres++) {

			double CurrentLLThres = MinLL + LLThres * LLStep;

			// CC1p Reco Events

			TH1D* hRecoCC1p = new TH1D("hRecoCC1p","hRecoCC1p",NBinsMuCosTheta,MinMuCosTheta,MaxMuCosTheta);
			RecoTree->Draw("CandidateMu_CosTheta>>hRecoCC1p",RecoCC1pQualifier+" && NuScore > "+TString(std::to_string(CurrentNuScore)) +" && CandidateP_ThreePlaneLogLikelihood > "+TString(std::to_string(CurrentLLThres)) );

			// All Reco Events

			TH1D* hReco = new TH1D("hReco","hReco",NBinsMuCosTheta,MinMuCosTheta,MaxMuCosTheta);
			RecoTree->Draw("CandidateMu_CosTheta>>hReco",RecoQualifier+" && NuScore > "+TString(std::to_string(CurrentNuScore))  +" && CandidateP_ThreePlaneLogLikelihood > "+TString(std::to_string(CurrentLLThres)) );

			double purity = hRecoCC1p->GetEntries() / hReco->GetEntries();
			double efficiency = hRecoCC1p->GetEntries() / hTruth->GetEntries();
			double product = purity * efficiency; 

			EfficiencyPlot->SetBinContent(NuScoreThres+1,LLThres+1,efficiency);
			PurityPlot->SetBinContent(NuScoreThres+1,LLThres+1,purity);
			PurityEfficiencyStudyPlot->SetBinContent(NuScoreThres+1,LLThres+1,product);

		} // End of the loop over the 

	} // End of the loop over nu score steps

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	TCanvas* PurityEfficiencyStudyCanvas = new TCanvas("PurityEfficiencyStudyCanvas","PurityEfficiencyStudyCanvas",205,34,1024,768);
	PurityEfficiencyStudyPlot->Draw("text coltz");

	double max = PurityEfficiencyStudyPlot->GetMaximum();

	TCanvas* PurityCanvas = new TCanvas("PurityCanvas","PurityCanvas",205,34,1024,768);
	PurityPlot->Draw("text coltz");

	TCanvas* EfficiencyCanvas = new TCanvas("EfficiencyCanvas","EfficiencyCanvas",205,34,1024,768);
	EfficiencyPlot->Draw("text coltz");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

} // End of the program 
