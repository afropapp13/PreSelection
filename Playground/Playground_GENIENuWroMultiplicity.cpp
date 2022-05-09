#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLegendEntry.h>
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

void Playground_GENIENuWroMultiplicity() {

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

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<TString> Runs{"Combined"};
	const int NRuns = Runs.size();

	TString Cuts = Containment + " && " + ProtonMom + " && " + DeltaPhiT + " && " + MuonMom + " && " + QualityCut + " && " + MinMuonVertexDist\
		+ " && " + MinProtonVertexDist + " && " + AvoidFlippedTracks;	

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* GENIEFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* GENIEtree = (TTree*)(GENIEFile->Get("myPreSelection"));

		TFile* NuWroFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9NuWro_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* NuWrotree = (TTree*)(NuWroFile->Get("myPreSelection"));		

		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);	

		TLegend* leg = new TLegend(0.63,0.6,0.85,0.8);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.05);
		leg->SetTextFont(132);
		leg->SetNColumns(1);
		leg->SetMargin(0.1);
		
		TCanvas* ProtonMultiCanvas = new TCanvas("ProtonMultiCanvas_"+Runs[WhichRun],"ProtonMultiCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonMultiCanvas->cd();
		ProtonMultiCanvas->SetBottomMargin(0.11);
		ProtonMultiCanvas->SetLeftMargin(0.15);	

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Proton multiplicity

		TH1D* GENIEProton = new TH1D("GENIEProton",";# Protons;# Events",11,-0.5,10.5);	
		GENIEtree->Draw("NumberProtons>>GENIEProton","("+Cuts+")*POTWeight * Weight * T2KWeight * ROOTinoWeight","goff");	

		TH1D* NuWroProton = new TH1D("NuWroProton",";# Protons;# Events",11,-0.5,10.5);	
		NuWrotree->Draw("NumberProtons>>NuWroProton","("+Cuts+")*POTWeight","goff");								

		GENIEProton->GetXaxis()->CenterTitle();
		GENIEProton->GetYaxis()->SetTitleOffset(1.4);

		GENIEProton->SetLineColor(kOrange+7);
		GENIEProton->SetMarkerColor(kOrange+7);
		GENIEProton->SetMarkerSize(2.);
		GENIEProton->SetMarkerStyle(20);
		GENIEProton->Draw("p0 same");	

		NuWroProton->SetLineColor(OverlayColor);
		NuWroProton->SetMarkerColor(OverlayColor);
		NuWroProton->SetMarkerSize(2.);
		NuWroProton->SetMarkerStyle(20);
		NuWroProton->Draw("p0 same");	

		TLegendEntry* lGENIE = leg->AddEntry(GENIEProton,"GENIE","p");
		lGENIE->SetTextColor(kOrange+7);	

		TLegendEntry* lNuWro = leg->AddEntry(NuWroProton,"NuWro","p");
		lNuWro->SetTextColor(OverlayColor);		

		leg->Draw();				

		//text->DrawLatexNDC(0.47, 0.93, Runs[WhichRun]);			

		//ProtonMultiCanvas->SaveAs(PlotPath+"ProtonMultiCanvas_"+Runs[WhichRun]+".pdf");
		//delete ProtonMultiCanvas;		

		// -----------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
