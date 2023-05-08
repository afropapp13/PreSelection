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

void DirtComparisons() {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	const int FontStyle = 132;
	const double TextSize = 0.06;			

	//------------------------------//

	std::vector<TString> DirtNames; std::vector<TString> DirtLabels; 
	std::vector<int> DirtColors; std::vector<double> DirtTriggers;
	
	DirtNames.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run1_reco2_reco2.root"); 
	DirtLabels.push_back("Run 1");
	DirtColors.push_back(kBlue+2);	
	DirtTriggers.push_back(7.41E+20);	
	
	DirtNames.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run2_reco2_reco2.root"); 
	DirtLabels.push_back("Run 2");
	DirtColors.push_back(kAzure-4);	
	DirtTriggers.push_back(7.56E+20);
	
	DirtNames.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run3_reco2_reco2.root"); 
	DirtLabels.push_back("Run 3");
	DirtColors.push_back(kGreen+2);	
	DirtTriggers.push_back(7.29E+20);	

/*
	DirtNames.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_65/022723/v01/prod_extunbiased_bnb_dirt_overlay_run4b_v08_00_00_63_run4b_reco2.root");	
	DirtLabels.push_back("Run 4b");	
	DirtColors.push_back(kOrange+7);
	DirtTriggers.push_back(2.5824087e+20);
*/	

	DirtNames.push_back("/uboone/data/users/apapadop/searchingfornues/mc_dirt_v08_00_00_67_pelee_ntuple_run5_v67.root");	
	DirtLabels.push_back("Run 5");	
	DirtColors.push_back(kRed+1);
	DirtTriggers.push_back(3.67173e+20);						

	//------------------------------//		

	const int NSamples = DirtNames.size();

	std::vector<TFile*> DirtFiles; DirtFiles.resize(NSamples);

	//------------------------------//

	// TTree names & pointers

	TString EventTTreeName = "nuselection/NeutrinoSelectionFilter";
	std::vector<TTree*> EventTTree; EventTTree.resize(NSamples);

	//------------------------------//

	// Cut

	//TString Cut = "trk_score_v < 0";
	//TString Cut = "nslice == 1";
	//TString Cut = " (0<1) ";
	//TString Cut = "nslice == 1 && topological_score > 0.5 && n_tracks_contained > 0";
	TString Cut = "nslice == 1 && topological_score > 0.5";			

	//------------------------------//

	// Plots to include

	std::vector<TString> PlotNames; std::vector< double> Min; std::vector<double> Max;  std::vector<int> NBins;

	PlotNames.push_back("n_tracks"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);	
	PlotNames.push_back("n_showers"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);
	PlotNames.push_back("reco_nu_vtx_sce_x"); Min.push_back(0.); Max.push_back(250); NBins.push_back(50);
	PlotNames.push_back("reco_nu_vtx_sce_y"); Min.push_back(-110); Max.push_back(110); NBins.push_back(50);	
	PlotNames.push_back("reco_nu_vtx_sce_z"); Min.push_back(0.); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_u"); Min.push_back(1); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_v"); Min.push_back(1); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_y"); Min.push_back(1); Max.push_back(1000); NBins.push_back(50);	
	PlotNames.push_back("topological_score"); Min.push_back(0.5); Max.push_back(1); NBins.push_back(25);				
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

	// Loop over the samples to open the files and the TTree

	for (int iSample = 0; iSample < NSamples; iSample++) {

		DirtFiles[iSample] = new TFile(DirtNames[iSample],"readonly");
		EventTTree[iSample] = (TTree*)( DirtFiles[iSample]->Get(EventTTreeName) );

	} // End of the loop over the samples

	//------------------------------//

	// Loop over the plots to be compared

	for (int iPlot = 0; iPlot < NPlots; iPlot++) {

		TString StringPlotName = PlotNames[iPlot];
		StringPlotName.ReplaceAll("(","_").ReplaceAll(")","_");

		TString CanvasName = "Canvas_" + PlotNames[iPlot];
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

			TString HistoNameTString = PlotNames[iPlot];
			HistoNameTString.ReplaceAll("(","_").ReplaceAll(")","_");

			HistosName[iSample] = HistoNameTString + "_" + TString( ToString(iSample) );

			Histos[iSample] = new TH1D(HistosName[iSample],";" + PlotNames[iPlot],NBins[iPlot],Min[iPlot],Max[iPlot]);
			EventTTree[iSample]->Draw(PlotNames[iPlot] + ">>" + HistosName[iSample], Cut ,"goff");

			Histos[iSample]->SetLineWidth(2);
			Histos[iSample]->SetLineColor( DirtColors.at(iSample) );	

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
			Histos[iSample]->GetYaxis()->SetTitle("# Events / " + TString( ToString(DirtTriggers[0]) ) );
			Histos[iSample]->GetYaxis()->SetTitleSize(TextSize);
			Histos[iSample]->GetYaxis()->SetTitleOffset(1.3);
			Histos[iSample]->GetYaxis()->SetTickSize(0.02);
			Histos[iSample]->GetYaxis()->CenterTitle();	

			//----------------------------------------//

			double SF = DirtTriggers[0] / DirtTriggers[iSample];
			double NEvents = Histos[iSample]->GetEntries();
			Histos[iSample]->Scale(SF);

			double imax = TMath::Max(Histos[iSample]->GetMaximum(),Histos[0]->GetMaximum());			
			Histos[iSample]->GetYaxis()->SetRangeUser(0.,1.1*imax);
			Histos[0]->GetYaxis()->SetRangeUser(0.,1.1*imax);			

			PlotCanvas->cd();
			Histos[iSample]->SetMarkerColor(DirtColors.at(iSample));
			Histos[iSample]->SetMarkerStyle(20);
			Histos[iSample]->SetMarkerSize(2.);				
			Histos[iSample]->Draw("hist same");
			Histos[0]->Draw("hist same");	

			TLegendEntry* legEntry = leg->AddEntry(Histos[iSample],DirtLabels[iSample] + ", " +TString( ToString(DirtTriggers[iSample]) ),"l");
			legEntry->SetTextColor( DirtColors.at(iSample) );		

			//----------------------------------------//					

		} // End of the loop over the samples grabing the plots	

		PlotCanvas->cd();
		leg->Draw();
			
		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);
		text->DrawTextNDC(0.16, 0.82, "Dirt");				

		TString CanvasNameTString = PlotPath+"DirtComparison_"+PlotNames[iPlot]+".pdf";
		CanvasNameTString.ReplaceAll("(","_").ReplaceAll(")","_");

		PlotCanvas->SaveAs(CanvasNameTString);

		//delete PlotCanvas;

	} // End of the loop over the plots	

	//------------------------------//

} // End of the program
