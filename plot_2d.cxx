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

#include "../myClasses/Tools.h"
#include "../myClasses/Constants.h"

using namespace std;
using namespace Constants;

// -------------------------------------------------------------------------------------------------------------------------------------------------

void plot_2d() {

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetPalette(kRainBow); 
	gStyle->SetNumberContours(999); 

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

	std::vector<TString> Runs{"Combined"};

	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* OverlayFile = TFile::Open("/exp/uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// ECal

		TH2D* hECal = new TH2D("hECal",";True E^{cal} [GeV];Reco E^{cal} [GeV]",200,0.2,1.6,200,0.2,1.6);

		tree->Draw("Reco_ECal:True_ECal>>hECal",qualifier,"goff");

		TCanvas* ECalCanvas = new TCanvas("ECalCanvas_"+Runs[WhichRun],"ECalCanvas_"+Runs[WhichRun],205,34,1024,768);
		ECalCanvas->cd();
		hECal->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ECalCanvas->SaveAs(PlotPath+"ECalCanvas_"+Runs[WhichRun]+".pdf");
		delete ECalCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
