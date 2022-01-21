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

void PrettyPlot(TH1D* h, int Color) {

	int font = 132;
	double size = 0.05;

	h->GetXaxis()->CenterTitle();
	h->GetXaxis()->SetTitleFont(font);
	h->GetXaxis()->SetTitleSize(size);	
	h->GetXaxis()->SetLabelFont(font);
	h->GetXaxis()->SetLabelSize(size);
	
	h->GetYaxis()->CenterTitle();
	h->GetYaxis()->SetTitleFont(font);
	h->GetYaxis()->SetTitleSize(size);	
	h->GetYaxis()->SetLabelFont(font);
	h->GetYaxis()->SetLabelSize(size);

	h->SetLineColor(Color);
	h->SetMarkerColor(Color);
	h->SetMarkerSize(2.);
	h->SetMarkerStyle(20);

	h->Scale(1./h->GetMaximum());

}

// -------------------------------------------------------------------------------------------------------------------------------------------------

void PeLEE_LFG_TwoDPlot() {

	// -----------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();	

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

	std::vector<TString> Runs{"Combined"};
	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

//		TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PeLEETuples/PreSelection_Dublicate_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TFile* OverlayFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreSelection_Dublicate_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
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

		// Total Missing Momentum for QE events

		TH2D* hPnQE = new TH2D("hPnQE",";LFG p_{n} [GeV/c];True p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnCanvasQE = new TCanvas("QELFGPnCanvas_"+Runs[WhichRun],"QELFGPnCanvas_"+Runs[WhichRun],205,34,1024,768);
		PnCanvasQE->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":LFG_pn>>hPnQE",qualifier + " && MCParticle_Mode == 0","goff");
		hPnQE->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " QE Events");

		PnCanvasQE->SaveAs(PlotPath+"QELFG_PnCanvas_"+Runs[WhichRun]+".pdf");
		delete PnCanvasQE;

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum for MEC events

		TH2D* hPnMEC = new TH2D("hPnMEC",";LFG p_{n} [GeV/c];True p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnCanvasMEC = new TCanvas("MECLFGPnCanvas_"+Runs[WhichRun],"MECLFGPnCanvas_"+Runs[WhichRun],205,34,1024,768);
		PnCanvasMEC->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":LFG_pn>>hPnMEC",qualifier + " && MCParticle_Mode == 10","goff");
		hPnMEC->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " MEC Events");

		PnCanvasMEC->SaveAs(PlotPath+"MECLFG_PnCanvas_"+Runs[WhichRun]+".pdf");
		delete PnCanvasMEC;

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum for RES events

		TH2D* hPnRES = new TH2D("hPnRES",";LFG p_{n} [GeV/c];True p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnCanvasRES = new TCanvas("RESLFGPnCanvas_"+Runs[WhichRun],"RESLFGPnCanvas_"+Runs[WhichRun],205,34,1024,768);
		PnCanvasRES->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":LFG_pn>>hPnRES",qualifier + " && MCParticle_Mode == 1","goff");
		hPnRES->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " RES Events");

		PnCanvasRES->SaveAs(PlotPath+"RESLFG_PnCanvas_"+Runs[WhichRun]+".pdf");
		delete PnCanvasRES;

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum for DIS events

		TH2D* hPnDIS = new TH2D("hPnDIS",";LFG p_{n} [GeV/c];True p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnCanvasDIS = new TCanvas("DISLFGPnCanvas_"+Runs[WhichRun],"DISLFGPnCanvas_"+Runs[WhichRun],205,34,1024,768);
		PnCanvasDIS->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":LFG_pn>>hPnDIS",qualifier + " && MCParticle_Mode == 2","goff");
		hPnDIS->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " DIS Events");

		PnCanvasDIS->SaveAs(PlotPath+"DISLFG_PnCanvas_"+Runs[WhichRun]+".pdf");
		delete PnCanvasDIS;

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

		// --------------------------------------------------------------------------------------------------------

		// kMiss for QE Events

		TH2D* hkMissQE = new TH2D("hkMissQE",";LFG p_{n} [GeV/c];True k_{Miss} [GeV/c]",80,0,0.8,80,0,0.8);

		tree->Draw("Reco_kMiss:LFG_pn>>hkMissQE",qualifier + " && MCParticle_Mode == 0","goff");

		TCanvas* kMissCanvasQE = new TCanvas("QELFGkMissCanvas_"+Runs[WhichRun],"QELFGkMissCanvas_"+Runs[WhichRun],205,34,1024,768);
		kMissCanvasQE->cd();
		hkMissQE->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " QE Events");

		kMissCanvasQE->SaveAs(PlotPath+"QELFG_kMissCanvas_"+Runs[WhichRun]+".pdf");
		delete kMissCanvasQE;

		// --------------------------------------------------------------------------------------------------------

		// kMiss for MEC Events

		TH2D* hkMissMEC = new TH2D("hkMissMEC",";LFG p_{n} [GeV/c];True k_{Miss} [GeV/c]",80,0,0.8,80,0,0.8);

		tree->Draw("Reco_kMiss:LFG_pn>>hkMissMEC",qualifier + " && MCParticle_Mode == 10","goff");

		TCanvas* kMissCanvasMEC = new TCanvas("MECLFGkMissCanvas_"+Runs[WhichRun],"MECLFGkMissCanvas_"+Runs[WhichRun],205,34,1024,768);
		kMissCanvasMEC->cd();
		hkMissMEC->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " MEC Events");

		kMissCanvasMEC->SaveAs(PlotPath+"MECLFG_kMissCanvas_"+Runs[WhichRun]+".pdf");
		delete kMissCanvasMEC;

		// --------------------------------------------------------------------------------------------------------

		// kMiss for RES Events

		TH2D* hkMissRES = new TH2D("hkMissRES",";LFG p_{n} [GeV/c];True k_{Miss} [GeV/c]",80,0,0.8,80,0,0.8);

		tree->Draw("Reco_kMiss:LFG_pn>>hkMissRES",qualifier + " && MCParticle_Mode == 1","goff");

		TCanvas* kMissCanvasRES = new TCanvas("RESLFGkMissCanvas_"+Runs[WhichRun],"RESLFGkMissCanvas_"+Runs[WhichRun],205,34,1024,768);
		kMissCanvasRES->cd();
		hkMissRES->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " RES Events");

		kMissCanvasRES->SaveAs(PlotPath+"RESLFG_kMissCanvas_"+Runs[WhichRun]+".pdf");
		delete kMissCanvasRES;

		// --------------------------------------------------------------------------------------------------------

		// kMiss for DIS Events

		TH2D* hkMissDIS = new TH2D("hkMissDIS",";LFG p_{n} [GeV/c];True k_{Miss} [GeV/c]",80,0,0.8,80,0,0.8);

		tree->Draw("Reco_kMiss:LFG_pn>>hkMissDIS",qualifier + " && MCParticle_Mode == 2","goff");

		TCanvas* kMissCanvasDIS = new TCanvas("DISLFGkMissCanvas_"+Runs[WhichRun],"DISLFGkMissCanvas_"+Runs[WhichRun],205,34,1024,768);
		kMissCanvasDIS->cd();
		hkMissDIS->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " DIS Events");

		kMissCanvasDIS->SaveAs(PlotPath+"DISLFG_kMissCanvas_"+Runs[WhichRun]+".pdf");
		delete kMissCanvasDIS;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		for (int i = 0; i < NRanges; i++) {

			TString Qualifier = qualifier + " && " + TString(std::to_string(range[i])) + " < LFG_pn && LFG_pn < " + TString(std::to_string(range[i+1]));

			TString CanvasName = "LFG_Pn_Slice"+TString(std::to_string(i));
			TCanvas* can = new TCanvas(CanvasName,CanvasName,205,34,1024,768);

			TH1D* LFG = new TH1D("LFG_"+TString(std::to_string(range[i])),";p_{n} [GeV/c]",NBins,LowEdge,HighEdge);
			tree->Draw("LFG_pn>>LFG_"+TString(std::to_string(range[i])),Qualifier ,"goff");
			PrettyPlot(LFG,kBlue+2);
			//LFG->SetTitle(TString(std::to_string(range[i])) + " < p_{n} < ");
			LFG->Draw("p hist same");

			TH1D* kMiss = new TH1D("kMiss_"+TString(std::to_string(range[i])),";p_{n} [GeV/c]",NBins,LowEdge,HighEdge);
			tree->Draw("True_kMiss>>kMiss_"+TString(std::to_string(range[i])),Qualifier ,"goff");
			PrettyPlot(kMiss,kOrange+7);
			kMiss->Draw("p0 hist same");	

			TH1D* Pn = new TH1D("Pn_"+TString(std::to_string(range[i])),";p_{n} [GeV/c]",NBins,LowEdge,HighEdge);
			tree->Draw("True_Pn>>Pn_"+TString(std::to_string(range[i])),Qualifier ,"goff");
			PrettyPlot(Pn,kGreen+2);
			Pn->Draw("p0 hist same");					

			TLegend* leg = new TLegend(0.7,0.7,0.87,0.9);
			leg->AddEntry(LFG,"LFG","p");
			leg->AddEntry(kMiss,"k_{Miss}","p");
			leg->AddEntry(Pn,"P_{n,proxy}","p");

			leg->SetTextFont(FontStyle);
			leg->SetTextSize(0.05);			
			leg->Draw();

			can->SaveAs(PlotPath+CanvasName+".pdf");
			delete can;

		}

		// -----------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
