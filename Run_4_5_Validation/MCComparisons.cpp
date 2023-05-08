#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TGaxis.h>
#include <TROOT.h>
#include <TString.h>

using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <map>

#include "../../Secondary_Code/myFunctions.cpp"

#include "ubana/myClasses/Constants.h"

using namespace Constants;

void MCComparisons() {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	const int FontStyle = 132;
	const double TextSize = 0.06;			

	//------------------------------//

	std::vector<TString> MCNames; std::vector<TString> MCLabels; 
	std::vector<int> MCColors; std::vector<double> MCPOT;
	
	MCNames.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run1_reco2_reco2.root"); 
	MCLabels.push_back("Run 1");
	MCColors.push_back(kBlue+2);	
	MCPOT.push_back(1.31E+21);	
	
	MCNames.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run2_reco2_D1D2_reco2.root"); 
	MCLabels.push_back("Run 2");
	MCColors.push_back(kAzure-4);	
	MCPOT.push_back(1.02E+21);
	
	MCNames.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run3_reco2_G_reco2.root"); 
	MCLabels.push_back("Run 3");
	MCColors.push_back(kGreen+2);	
	MCPOT.push_back(1.34E+21);	

/*
	MCNames.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_65/022723/v01/run4b_bnb_nu_overlay_pandora_reco2_run4b_pandora_reco2_reco2.root");	
	MCLabels.push_back("Run 4b");	
	MCColors.push_back(kOrange+7);
	MCPOT.push_back(6.1428283e+20);
*/

	MCNames.push_back("/uboone/data/users/apapadop/searchingfornues/mc_overlay_v08_00_00_67_pelee_ntuple_run5_v67.root");	
	MCLabels.push_back("Run 5");	
	MCColors.push_back(kRed+1);
	MCPOT.push_back(1.02168e+21);						

	//------------------------------//		

	const int NSamples = MCNames.size();

	std::vector<TFile*> MCFiles; MCFiles.resize(NSamples);

	//------------------------------//

	// TTree names & pointers

	TString EventTTreeName = "nuselection/NeutrinoSelectionFilter";
	std::vector<TTree*> EventTTree; EventTTree.resize(NSamples);

	//------------------------------//

	// Cut

	//TString Cut = "trk_score_v < 0";
	TString Cut = "nslice == 1";
	//TString Cut = " (0<1) ";
	//TString Cut = "nslice == 1 && topological_score > 0.5 && n_tracks_contained > 0";
	//TString Cut = "nslice == 1 && topological_score > 0.5";			

	//------------------------------//

	// Plots to include

	std::vector<TString> PlotNames; std::vector< double> Min; std::vector<double> Max;  std::vector<int> NBins;

	PlotNames.push_back("weightSpline"); Min.push_back(0.8); Max.push_back(1.5); NBins.push_back(60);
	PlotNames.push_back("weightTune"); Min.push_back(0.); Max.push_back(3.); NBins.push_back(60);
	PlotNames.push_back("nu_e"); Min.push_back(0.); Max.push_back(3.); NBins.push_back(60);
	PlotNames.push_back("cos(theta)"); Min.push_back(-1.); Max.push_back(1.); NBins.push_back(30);		
	//PlotNames.push_back("selected"); Min.push_back(-0.5); Max.push_back(1.5); NBins.push_back(2);
	PlotNames.push_back("n_tracks"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);	
	PlotNames.push_back("n_showers"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);
	PlotNames.push_back("reco_nu_vtx_sce_x"); Min.push_back(0.); Max.push_back(250); NBins.push_back(50);
	PlotNames.push_back("reco_nu_vtx_sce_y"); Min.push_back(-110); Max.push_back(110); NBins.push_back(50);	
	PlotNames.push_back("reco_nu_vtx_sce_z"); Min.push_back(0.); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_u"); Min.push_back(1); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_v"); Min.push_back(1); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_y"); Min.push_back(1); Max.push_back(1000); NBins.push_back(50);	
	PlotNames.push_back("topological_score"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(50);				
	PlotNames.push_back("nslice"); Min.push_back(0.5); Max.push_back(1.5); NBins.push_back(1);
	PlotNames.push_back("nu_flashmatch_score"); Min.push_back(0.); Max.push_back(50.); NBins.push_back(40);
	PlotNames.push_back("trk_score_v"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(40);		
	PlotNames.push_back("pfpdg"); Min.push_back(10.5); Max.push_back(13.5); NBins.push_back(3);
	PlotNames.push_back("trk_llr_pid_score_v"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(50);
	PlotNames.push_back("pfp_generation_v"); Min.push_back(1.5); Max.push_back(4.5); NBins.push_back(3);
	PlotNames.push_back("cos(trk_theta_v)"); Min.push_back(-1.); Max.push_back(1.); NBins.push_back(20);
	//PlotNames.push_back("cos(trk_theta)"); Min.push_back(-1.); Max.push_back(1.); NBins.push_back(20);				

	const int NPlots = PlotNames.size();

	//------------------------------//	

	std::map<TString,TString> InteMode =
	{
		{ "" , Cut},
		{ "QE" , Cut + " && interaction == 0"},
		{ "MEC", Cut + " && interaction == 10" },
		{ "RES", Cut + " && interaction == 1" },
		{ "DIS", Cut + " && interaction == 2" }				

	};

	std::vector<TString> InteractionLabels = {"","QE","MEC","RES","DIS"};	

	const TString MCWeight = "weightSpline * ( (weightSpline > 0. && weightSpline < 30. && weightTune > 0. && weightTune < 30.)? weightTune:0.)";	
//	const TString MCWeight = "weightSpline";

	//------------------------------//		

	// Loop over the samples to open the files and the TTree

	for (int iSample = 0; iSample < NSamples; iSample++) {

		MCFiles[iSample] = new TFile(MCNames[iSample],"readonly");
		EventTTree[iSample] = (TTree*)( MCFiles[iSample]->Get(EventTTreeName) );

	} // End of the loop over the samples

	//------------------------------//

	// Loop over the interaction modes

	for (int imode = 0; imode < (int)(InteractionLabels.size()); imode++) {	

		// Loop over the plots to be compared

		for (int iPlot = 0; iPlot < NPlots; iPlot++) {

			TString StringPlotName = PlotNames[iPlot];
			StringPlotName.ReplaceAll("(","_").ReplaceAll(")","_");

			TString CanvasName = "Canvas_" + PlotNames[iPlot] + "_" + InteractionLabels[imode];
			TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
			PlotCanvas->cd();
			PlotCanvas->SetTopMargin(0.14);
			PlotCanvas->SetLeftMargin(0.15);
			PlotCanvas->SetBottomMargin(0.15);		
			PlotCanvas->Draw();	

			TLegend* leg = new TLegend(0.3,0.88,0.95,0.99);
			leg->SetBorderSize(0);
			leg->SetNColumns(2);
			leg->SetTextSize(TextSize-0.01);	
			leg->SetTextFont(FontStyle);
			leg->SetMargin(0.1);								

			// Loop over the samples to open the files and to get the corresponding plot

			std::vector<TH1D*> Histos; Histos.resize(NSamples);
			std::vector<TString> HistosName; HistosName.resize(NSamples);		

			for (int iSample = 0; iSample < NSamples; iSample++) {	

				TString HistoNameTString = PlotNames[iPlot]+ "_" + InteractionLabels[imode];
				HistoNameTString.ReplaceAll("(","_").ReplaceAll(")","_");

				HistosName[iSample] = HistoNameTString + "_" + TString( ToString(iSample) );

				Histos[iSample] = new TH1D(HistosName[iSample],";" + PlotNames[iPlot],NBins[iPlot],Min[iPlot],Max[iPlot]);
				EventTTree[iSample]->Draw(PlotNames[iPlot] + ">>" + HistosName[iSample], "(" + InteMode[ InteractionLabels[imode] ] + ") * " + MCWeight,"goff");

				Histos[iSample]->SetLineWidth(2);
				Histos[iSample]->SetLineColor( MCColors.at(iSample) );	

				Histos[iSample]->GetXaxis()->SetTitleFont(FontStyle);
				Histos[iSample]->GetXaxis()->SetLabelFont(FontStyle);
				Histos[iSample]->GetXaxis()->SetNdivisions(8);
				Histos[iSample]->GetXaxis()->SetLabelSize(TextSize);
				Histos[iSample]->GetXaxis()->SetTitleSize(TextSize);	
				Histos[iSample]->GetXaxis()->SetTitleOffset(1.1);					
				Histos[iSample]->GetXaxis()->CenterTitle();						

				Histos[iSample]->GetYaxis()->SetTitleFont(FontStyle);
				Histos[iSample]->GetYaxis()->SetLabelFont(FontStyle);
				Histos[iSample]->GetYaxis()->SetNdivisions(6);
				Histos[iSample]->GetYaxis()->SetLabelSize(TextSize);
				Histos[iSample]->GetYaxis()->SetTitle("# Events / " + TString( ToString(MCPOT[0]) ) );
				Histos[iSample]->GetYaxis()->SetTitleSize(TextSize);
				Histos[iSample]->GetYaxis()->SetTitleOffset(1.3);
				Histos[iSample]->GetYaxis()->SetTickSize(0.02);
				Histos[iSample]->GetYaxis()->CenterTitle();	

				//----------------------------------------//

				double SF = MCPOT[0] / MCPOT[iSample];
				double NEvents = Histos[iSample]->GetEntries();
				Histos[iSample]->Scale(SF);

				double imax = TMath::Max(Histos[iSample]->GetMaximum(),Histos[0]->GetMaximum());			
				Histos[iSample]->GetYaxis()->SetRangeUser(0.,1.1*imax);
				Histos[0]->GetYaxis()->SetRangeUser(0.,1.1*imax);			

				PlotCanvas->cd();
				Histos[iSample]->SetMarkerColor(MCColors.at(iSample));
				Histos[iSample]->SetMarkerStyle(20);
				Histos[iSample]->SetMarkerSize(2.);				
				Histos[iSample]->Draw("hist same");
				Histos[0]->Draw("hist same");	

				TLegendEntry* legEntry = leg->AddEntry(Histos[iSample],MCLabels[iSample] + ", " +TString( ToString(MCPOT[iSample]) ),"l");
				legEntry->SetTextColor( MCColors.at(iSample) );		

				//----------------------------------------//					

			} // End of the loop over the samples grabing the plots	

			PlotCanvas->cd();
			leg->Draw();
			
			TLatex *text = new TLatex();
			text->SetTextFont(FontStyle);
			text->SetTextSize(0.05);
			text->DrawTextNDC(0.16, 0.82, "MC");				

			TString CanvasNameTString = PlotPath+"MCComparison_"+PlotNames[iPlot]+"_" + InteractionLabels[imode] + ".pdf";
			CanvasNameTString.ReplaceAll("(","_").ReplaceAll(")","_");

			PlotCanvas->SaveAs(CanvasNameTString);

			//delete PlotCanvas;

		} // End of the loop over the plots

	} // End of the loop over the interaction modes	

	//------------------------------//

} // End of the program
