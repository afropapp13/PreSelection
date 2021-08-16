#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLine.h>
#include <TLatex.h>
#include <TPaletteAxis.h>

#include <iostream>
#include <vector>

#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/Constants.h"

using namespace std;
using namespace Constants;

// -------------------------------------------------------------------------------------------------------------------------------------------------

void PlotResidual(TTree* t, TString Reco, TString True, int NBins, double min, double max) {

	TH1D* hTrue = new TH1D("hTrue_"+Reco,";"+True,NBins,min,max);
	TH1D* hReco = new TH1D("hReco_"+Reco,";"+True,NBins,min,max);

	t->Draw(Reco+">>hReco_"+Reco,qualifier,"goff");
	t->Draw(True+">>hTrue_"+Reco,qualifier,"goff");

	TH1D* RecoClone = (TH1D*)(hReco->Clone());
	RecoClone->Add(hTrue,-1.);
	RecoClone->Divide(hTrue);
	RecoClone->Scale(100.); // %

	RecoClone->GetYaxis()->SetTitle("(Reco-True)/True [%]"); // %
	RecoClone->SetTitle("Using selected CC1p0#pi events"); // %

	TCanvas* Canvas = new TCanvas("Canvas_"+Reco,"Canvas_"+Reco,205,34,1024,768);

	RecoClone->Draw();

}

// -------------------------------------------------------------------------------------------------------------------------------------------------

void PeLEE_BinMigration() {

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetTitleSize(0.0,"t");
	gStyle->SetTitleFont(132,"t");

	gStyle->SetTitleOffset(0.9,"xyz");
	gStyle->SetTitleSize(0.05,"xyz");
	gStyle->SetTitleFont(132,"xyz");
	gStyle->SetLabelSize(0.05,"xyz");
	gStyle->SetLabelFont(132,"xyz");
	gStyle->SetNdivisions(8,"xyz");

	gStyle->SetOptStat(0);
	gStyle->SetPadRightMargin(0.13);

	gROOT->ForceStyle();

	TString Recalibrate = "";
//	TString Recalibrate = "_Recalibrate";

	TH1::SetDefaultSumw2(kTRUE);

	// -------------------------------------------------------------------------------------------------------------------------------------------------

//	std::vector<TString> Runs{"Run1"};
//	std::vector<TString> Runs{"Run1","Run3"};
//	std::vector<TString> Runs{"Run1","Run2","Run3","Run4","Run5"};
	std::vector<TString> Runs{"Combined"};

	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PeLEETuples/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

		// ---------------------------------------------------------------------------------------------------------------------------------------

		PlotResidual(tree,"CandidateMu_P_Range","True_CandidateMu_P",12,0.,1.2);
		PlotResidual(tree,"CandidateMu_CosTheta","True_CandidateMu_CosTheta",12,0.,1.2);

		PlotResidual(tree,"CandidateP_P_Range","True_CandidateP_P",12,0.,1.2);
		PlotResidual(tree,"CandidateP_CosTheta","True_CandidateP_CosTheta",12,0.,1.2);

		PlotResidual(tree,"Reco_Pt","True_Pt",12,0.,0.8);

		PlotResidual(tree,"Reco_DeltaAlphaT","True_DeltaAlphaT",12,0.,180);

		PlotResidual(tree,"Reco_DeltaPhiT","True_DeltaPhiT",12,0.,180);


		// -----------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
