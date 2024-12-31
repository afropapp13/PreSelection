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

void ExtBNBComparisons() {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	const int FontStyle = 132;
	const double TextSize = 0.06;			

	//------------------------------//

	std::vector<TString> ExtBNBNames; std::vector<TString> ExtBNBLabels; 
	std::vector<int> ExtBNBColors; std::vector<double> ExtBNBTriggers;
	
	ExtBNBNames.push_back("/pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/combined/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run1.root"); 
	ExtBNBLabels.push_back("Run 1");
	ExtBNBColors.push_back(kBlue+2);	
	ExtBNBTriggers.push_back(65744587);	
	
	ExtBNBNames.push_back("/pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/combined/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run2.root"); 
	ExtBNBLabels.push_back("Run 2");
	ExtBNBColors.push_back(kAzure-4);	
	ExtBNBTriggers.push_back(153905891);
	
	ExtBNBNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run3.root"); 
	ExtBNBLabels.push_back("Run 3");
	ExtBNBColors.push_back(kGreen+2);	
	ExtBNBTriggers.push_back(207167629);	

	ExtBNBNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/Run4a_bnb_beamOff_PeLee_ntuples_run4a_ana.root");	
	ExtBNBLabels.push_back("Run 4a");	
	ExtBNBColors.push_back(kViolet);
	ExtBNBTriggers.push_back(27596585);

	ExtBNBNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/Run4b_bnb_beamOff_PeLee_ntuples_run4b_ana.root");	
	ExtBNBLabels.push_back("Run 4b");	
	ExtBNBColors.push_back(kOrange+7);
	ExtBNBTriggers.push_back(91167643);

	ExtBNBNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/Run4c_bnb_beamOff_PeLee_ntuples_run4c_ana_ana.root");	
	ExtBNBLabels.push_back("Run 4c");	
	ExtBNBColors.push_back(kMagenta-7);
	ExtBNBTriggers.push_back(50978641);

	ExtBNBNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4d/Run4d_bnb_beamOff_PeLee_ntuples_run4d_ana_ana.root");	
	ExtBNBLabels.push_back("Run 4d");	
	ExtBNBColors.push_back(kCyan-3);
	ExtBNBTriggers.push_back(75637751);


	ExtBNBNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/Run5_bnb_beamOff_PeLee_ntuples_run5_ana_ana.root");	
	ExtBNBLabels.push_back("Run 5");	
	ExtBNBColors.push_back(kRed+1);
	ExtBNBTriggers.push_back(115079907);						

	//------------------------------//		

	const int NSamples = ExtBNBNames.size();

	std::vector<TFile*> ExtBNBFiles; ExtBNBFiles.resize(NSamples);

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

	PlotNames.push_back("n_tracks"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);	
	PlotNames.push_back("n_showers"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);
	PlotNames.push_back("reco_nu_vtx_sce_x"); Min.push_back(10.); Max.push_back(246.); NBins.push_back(25);
	PlotNames.push_back("reco_nu_vtx_sce_y"); Min.push_back(-105.); Max.push_back(105.); NBins.push_back(25);	
	PlotNames.push_back("reco_nu_vtx_sce_z"); Min.push_back(10.); Max.push_back(1026.); NBins.push_back(25);
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
	PlotNames.push_back("crtveto"); Min.push_back(-0.5); Max.push_back(1.5); NBins.push_back(2);
	PlotNames.push_back("crthitpe"); Min.push_back(40); Max.push_back(570); NBins.push_back(100);					

	const int NPlots = PlotNames.size();

	//------------------------------//		

	// Loop over the samples to open the files and the TTree

	for (int iSample = 0; iSample < NSamples; iSample++) {

		ExtBNBFiles[iSample] = new TFile(ExtBNBNames[iSample],"readonly");
		EventTTree[iSample] = (TTree*)( ExtBNBFiles[iSample]->Get(EventTTreeName) );

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

		TLegend* leg = new TLegend(0.3,0.87,0.95,0.98);
		leg->SetBorderSize(0);
		leg->SetNColumns(2);
		leg->SetTextSize(TextSize-0.02);	
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
			Histos[iSample]->SetLineColor( ExtBNBColors.at(iSample) );	

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
			Histos[iSample]->GetYaxis()->SetTitle("# Events / " + TString( ToString(ExtBNBTriggers[0]) ) );
			Histos[iSample]->GetYaxis()->SetTitleSize(TextSize);
			Histos[iSample]->GetYaxis()->SetTitleOffset(1.3);
			Histos[iSample]->GetYaxis()->SetTickSize(0.02);
			Histos[iSample]->GetYaxis()->CenterTitle();	

			//----------------------------------------//

			double SF = ExtBNBTriggers[0] / ExtBNBTriggers[iSample];
			double NEvents = Histos[iSample]->GetEntries();
			Histos[iSample]->Scale(SF);

			double imax = TMath::Max(Histos[iSample]->GetMaximum(),Histos[0]->GetMaximum());			
			Histos[iSample]->GetYaxis()->SetRangeUser(0.,1.08*imax);
			Histos[0]->GetYaxis()->SetRangeUser(0.,1.08*imax);			

			PlotCanvas->cd();
			Histos[iSample]->SetMarkerColor(ExtBNBColors.at(iSample));
			Histos[iSample]->SetMarkerStyle(20);
			Histos[iSample]->SetMarkerSize(2.);				
			Histos[iSample]->Draw("e same");
			Histos[0]->Draw("e same");	

			TLegendEntry* legEntry = leg->AddEntry(Histos[iSample],ExtBNBLabels[iSample] + ", " +TString( ToString(ExtBNBTriggers[iSample]) ),"ep");
			legEntry->SetTextColor( ExtBNBColors.at(iSample) );		

			//----------------------------------------//					

		} // End of the loop over the samples grabing the plots	

		PlotCanvas->cd();
		leg->Draw();
			
		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);
		text->DrawTextNDC(0.16, 0.82, "ExtBNB");				

		TString CanvasNameTString = PlotPath+"ExtBNBComparison_"+PlotNames[iPlot]+".pdf";
		CanvasNameTString.ReplaceAll("(","_").ReplaceAll(")","_");

		PlotCanvas->SaveAs(CanvasNameTString);

		//delete PlotCanvas;

	} // End of the loop over the plots	

	//------------------------------//

} // End of the program
