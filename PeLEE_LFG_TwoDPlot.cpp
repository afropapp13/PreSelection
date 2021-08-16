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

void PeLEE_LFG_TwoDPlot() {

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

	// -------------------------------------------------------------------------------------------------------------------------------------------------

//	std::vector<TString> Runs{"Run1"};
//	std::vector<TString> Runs{"Run1","Run3"};
//	std::vector<TString> Runs{"Run1","Run2","Run3","Run4","Run5"};

	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PeLEETuples/PreSelection_Dublicate_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum

		TH2D* hPn = new TH2D("hPn",";LFG p_{n} [GeV/c];True p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnCanvas = new TCanvas("LFGPnCanvas_"+Runs[WhichRun],"LFGPnCanvas_"+Runs[WhichRun],205,34,1024,768);
		PnCanvas->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":LFG_pn>>hPn",qualifier,"goff");
		hPn->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PnCanvas->SaveAs(PlotPath+"LFG_PnCanvas_"+Runs[WhichRun]+".pdf");
		delete PnCanvas;

		// --------------------------------------------------------------------------------------------------------

		// kMiss

		TH2D* hkMiss = new TH2D("hkMiss",";LFG p_{n} [GeV/c];True k_{Miss} [GeV/c]",80,0,0.8,80,0,0.8);

		tree->Draw("Reco_kMiss:LFG_pn>>hkMiss",qualifier,"goff");

		TCanvas* kMissCanvas = new TCanvas("LFGkMissCanvas_"+Runs[WhichRun],"LFGkMissCanvas_"+Runs[WhichRun],205,34,1024,768);
		kMissCanvas->cd();
		hkMiss->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		kMissCanvas->SaveAs(PlotPath+"LFG_kMissCanvas_"+Runs[WhichRun]+".pdf");
		delete kMissCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
