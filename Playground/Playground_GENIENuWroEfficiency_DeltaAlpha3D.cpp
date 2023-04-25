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
#include <cmath>

#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/Constants.h"

using namespace std;
using namespace Constants;

// -------------------------------------------------------------------------------------------------------------------------------------------------

void Playground_GENIENuWroEfficiency_DeltaAlpha3D() {

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

	TString Cuts = CC1p +" && "+ Containment + " && " + ProtonMom + " && " + DeltaPhiT + " && " + MuonMom + " && " + QualityCut + " && " + MinMuonVertexDist\
		+ " && " + MinProtonVertexDist + " && True_CandidateMu_P > 0.1 && True_CandidateMu_P < 1.2 && True_CandidateP_P > 0.3 && True_CandidateP_P < 1. && CandidateP_LLR_PID < 0.05"
		+ " && " + AvoidFlippedTracks + " && Reco_Pn > 0.3 && sqrt(Reco_Q2) > 0.5";	

	TString LocalTrueCC1p = "CC1p && NumberPi0 == 0 && Muon_MCParticle_Mom > 0.1 && Muon_MCParticle_Mom < 1.2 && Proton_MCParticle_Mom > 0.3 && Proton_MCParticle_Mom < 1. && "
		+ TrueCC1p + " && True_Pn > 0.3  && sqrt(True_Q2) > 0.5";	

//	TString truevar = "True_DeltaAlpha3Dq"; TString varlabel = "#alpha_{3D,q} [deg]";
	TString truevar = "True_DeltaAlpha3DMu"; TString varlabel = "#alpha_{3D,#mu} [deg]";

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* GENIEFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* GENIEtree = (TTree*)(GENIEFile->Get("myPreSelection"));

		TFile* TruthGENIEFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreTruthSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* TruthGENIEtree = (TTree*)(TruthGENIEFile->Get("myPreTruthSelection"));		

		TFile* NuWroFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9NuWro_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* NuWrotree = (TTree*)(NuWroFile->Get("myPreSelection"));

		TFile* TruthNuWroFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreTruthSelection_Overlay9NuWro_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* TruthNuWrotree = (TTree*)(TruthNuWroFile->Get("myPreTruthSelection"));				

		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);	

		TLegend* leg = new TLegend(0.15,0.91,0.85,0.99);
		leg->SetBorderSize(0);
		leg->SetTextSize(0.05);
		leg->SetTextFont(132);
		leg->SetNColumns(2);
		leg->SetMargin(0.1);
		
		TCanvas* EffCanvas = new TCanvas("EffCanvas_"+Runs[WhichRun],"EffCanvas_"+Runs[WhichRun],205,34,1024,768);
		EffCanvas->cd();
		EffCanvas->SetBottomMargin(0.11);
		EffCanvas->SetLeftMargin(0.15);	

		//----------------------------------------//

		TH1D* GENIEReco = new TH1D("GENIEReco",";" + varlabel + ";Efficiency",NBinsDeltaAlpha3Dq,ArrayNBinsDeltaAlpha3Dq);	
		GENIEtree->Draw(truevar+">>GENIEReco","("+Cuts+")*POTWeight * Weight * ROOTinoWeight","goff");	//T2KWeight

		TH1D* GENIETrue = new TH1D("GENIETrue",";" + varlabel + ";Efficiency",NBinsDeltaAlpha3Dq,ArrayNBinsDeltaAlpha3Dq);	
		TruthGENIEtree->Draw(truevar+">>GENIETrue","("+LocalTrueCC1p+")*POTWeight * Weight * ROOTinoWeight","goff");	//T2KWeight
		
		GENIEReco->Divide(GENIETrue);	

		//----------------------------------------//		

		TH1D* NuWroReco = new TH1D("NuWroReco",";" + varlabel + ";Efficiency",NBinsDeltaAlpha3Dq,ArrayNBinsDeltaAlpha3Dq);	
		NuWrotree->Draw(truevar+">>NuWroReco","("+Cuts+")*POTWeight","goff");		

		TH1D* NuWroTrue = new TH1D("NuWroTrue",";" + varlabel + ";Efficiency",NBinsDeltaAlpha3Dq,ArrayNBinsDeltaAlpha3Dq);	
		TruthNuWrotree->Draw(truevar+">>NuWroTrue","("+LocalTrueCC1p+")*POTWeight","goff");	

		NuWroReco->Divide(NuWroTrue);

		//----------------------------------------//									

		GENIEReco->SetLineColor(OverlayColor);
		GENIEReco->SetMarkerColor(OverlayColor);
		GENIEReco->SetMarkerSize(2.);
		GENIEReco->SetMarkerStyle(20);
		GENIEReco->SetTitle("");		

		GENIEReco->GetXaxis()->CenterTitle();

		GENIEReco->GetYaxis()->SetTitleOffset(1.4);
		GENIEReco->GetYaxis()->SetRangeUser(0.,0.18);

		GENIEReco->Draw("p0 same");	

		NuWroReco->SetLineColor(kOrange+7);
		NuWroReco->SetMarkerColor(kOrange+7);
		NuWroReco->SetMarkerSize(2.);
		NuWroReco->SetMarkerStyle(20);

		//NuWroReco->Draw("p0 same");	

		TLegendEntry* lGENIE = leg->AddEntry(GENIEReco,"GENIE","p");
		lGENIE->SetTextColor(OverlayColor);	

		//TLegendEntry* lNuWro = leg->AddEntry(NuWroReco,"NuWro","p");
		//lNuWro->SetTextColor(kOrange+7);		

		leg->Draw();				

		//text->DrawLatexNDC(0.47, 0.93, Cuts);			

		//EffCanvas->SaveAs(PlotPath+"EffCanvas_"+Runs[WhichRun]+".pdf");
		//delete EffCanvas;		

		// -----------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
