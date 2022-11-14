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

#include "../../Secondary_Code/myFunctions.cpp"

#include "ubana/myClasses/Constants.h"

using namespace Constants;

void QuickRun4aComparisons() {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	const int FontStyle = 132;
	const double TextSize = 0.06;			

	//------------------------------//

	// Which BeamOn samples do we want to overlay?
	// Push them back in the array

	std::vector<TString> BeamOnNames; std::vector<TString> BeamOnLabels; 
	std::vector<int> BeamOnColors; std::vector<double> BeamOnPOT;
	/*
	BeamOnNames.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run1_neutrinoselection_filt_numu_ALL.root"); 
	BeamOnLabels.push_back("Run 1");
	BeamOnColors.push_back(kBlue+2);	
	BeamOnPOT.push_back(Fulltor860_wcut_Run1);
	*/
	//	BeamOnNames.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run1/numupresel/data_bnb_mcc9.1_v08_00_00_25_reco2_C1_beam_good_reco2_5e19.root"); 
	BeamOnNames.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run1/data_bnb_mcc9.1_v08_00_00_25_reco2_C1_beam_good_reco2_5e19.root"); 
	BeamOnLabels.push_back("Run 1");
	//	BeamOnColors.push_back(kRed+1);	
	BeamOnColors.push_back(kBlue+2);	
	BeamOnPOT.push_back(5e19);
	/*
	BeamOnNames.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run3_neutrinoselection_filt_numu_ALL.root"); 
	BeamOnLabels.push_back("Run 3");
	BeamOnColors.push_back(kGreen+2);	
	BeamOnPOT.push_back(Fulltor860_wcut_Run3);	
	*/
	//	BeamOnNames.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run3/numupresel/data_bnb_mcc9.1_v08_00_00_25_reco2_G1_beam_good_reco2_1e19.root"); 
	BeamOnNames.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run3/data_bnb_mcc9.1_v08_00_00_25_reco2_G1_beam_good_reco2_1e19.root"); 
	BeamOnLabels.push_back("Run 3");
	//	BeamOnColors.push_back(kMagenta);	
	BeamOnColors.push_back(kGreen+2);	
	BeamOnPOT.push_back(1e19);	

	// Rutgers
	//BeamOnNames.push_back("/pnfs/uboone/persistent/run4/bnb_on_run4a_reco2_v08_00_00_57_run4a_reco2.root");
	// Oct 2022
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/uboonepro/run4_validation/pelee_ntuples_bnb_beam_on_data_v08_00_00_63_run4a_beam_good.root");	
	BeamOnLabels.push_back("Run 4a");	
	BeamOnColors.push_back(kOrange+7);
	BeamOnPOT.push_back(Fulltor860_wcut_Run4a);	

	//------------------------------//		

	const int NSamples = BeamOnNames.size();

	std::vector<TFile*> BeamOnFiles; BeamOnFiles.resize(NSamples);

	//------------------------------//

	// TTree names & pointers

	TString EventTTreeName = "nuselection/NeutrinoSelectionFilter";
	std::vector<TTree*> EventTTree; EventTTree.resize(NSamples);

	//------------------------------//

	// Cut

	TString Cut = "nslice == 1";
	//TString Cut = "";

	//------------------------------//

	// Plots to include

	std::vector<TString> PlotNames; std::vector< double> Min; std::vector<double> Max;  std::vector<int> NBins;

	PlotNames.push_back("selected"); Min.push_back(-0.5); Max.push_back(1.5); NBins.push_back(2);
	PlotNames.push_back("n_tracks"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);	
	PlotNames.push_back("n_showers"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);
	PlotNames.push_back("reco_nu_vtx_sce_x"); Min.push_back(-20); Max.push_back(270); NBins.push_back(50);
	PlotNames.push_back("reco_nu_vtx_sce_y"); Min.push_back(-150); Max.push_back(150); NBins.push_back(50);	
	PlotNames.push_back("reco_nu_vtx_sce_z"); Min.push_back(-100); Max.push_back(1100); NBins.push_back(50);
	PlotNames.push_back("hits_u"); Min.push_back(0); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_v"); Min.push_back(0); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_y"); Min.push_back(0); Max.push_back(1000); NBins.push_back(50);	
	PlotNames.push_back("topological_score"); Min.push_back(0); Max.push_back(1); NBins.push_back(50);				
	PlotNames.push_back("nslice"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);

	const int NPlots = PlotNames.size();

	//------------------------------//	

	// Loop over the samples to open the files and the TTree

	for (int iSample = 0; iSample < NSamples; iSample++) {

		BeamOnFiles[iSample] = new TFile(BeamOnNames[iSample],"readonly");
		EventTTree[iSample] = (TTree*)( BeamOnFiles[iSample]->Get(EventTTreeName) );

	} // End of the loop over the samples

	//------------------------------//

	// Loop over the plots to be compared

	for (int iPlot = 0; iPlot < NPlots; iPlot++) {

		TString CanvasName = "Canvas_" + PlotNames[iPlot];
		TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
		PlotCanvas->cd();
		PlotCanvas->SetTopMargin(0.12);
		PlotCanvas->SetLeftMargin(0.15);
		PlotCanvas->SetBottomMargin(0.15);		
		PlotCanvas->Draw();	

		TString CanvasNameAreaNorm = "AreaNormCanvas_" + PlotNames[iPlot];
		TCanvas* PlotCanvasAreaNorm = new TCanvas(CanvasNameAreaNorm,CanvasNameAreaNorm,205,34,1024,768);
		PlotCanvasAreaNorm->cd();
		PlotCanvasAreaNorm->SetTopMargin(0.12);
		PlotCanvasAreaNorm->SetLeftMargin(0.15);
		PlotCanvasAreaNorm->SetBottomMargin(0.15);		
		PlotCanvasAreaNorm->Draw();		

		TLegend* leg = new TLegend(0.2,0.91,0.9,0.98);
		leg->SetBorderSize(0);
		leg->SetNColumns(2);
		leg->SetTextSize(TextSize-0.01);	
		leg->SetTextFont(FontStyle);						

		// Loop over the samples to open the files and to get the corresponding plot

		std::vector<TH1D*> Histos; Histos.resize(NSamples);
		std::vector<TString> HistosName; HistosName.resize(NSamples);		

		for (int iSample = 0; iSample < NSamples; iSample++) {	

			HistosName[iSample] = PlotNames[iPlot] + "_" + TString( ToString(iSample) );
			Histos[iSample] = new TH1D(HistosName[iSample],";" + PlotNames[iPlot],NBins[iPlot],Min[iPlot],Max[iPlot]);
			EventTTree[iSample]->Draw(PlotNames[iPlot] + ">>" + HistosName[iSample],Cut,"goff");

			Histos[iSample]->SetLineWidth(4);
			Histos[iSample]->SetLineColor( BeamOnColors.at(iSample) );	

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
			Histos[iSample]->GetYaxis()->SetTitle("# Events / " + TString( ToString(BeamOnPOT[0]) ) );
			Histos[iSample]->GetYaxis()->SetTitleSize(TextSize);
			Histos[iSample]->GetYaxis()->SetTitleOffset(1.3);
			Histos[iSample]->GetYaxis()->SetTickSize(0);
			Histos[iSample]->GetYaxis()->CenterTitle();	

			TH1D* CloneAreaNorm = (TH1D*)(Histos[0]->Clone());

			//----------------------------------------//

			double SF = BeamOnPOT[0] / BeamOnPOT[iSample];
//			double SF = 1. / Histos[iSample]->GetEntries();
			Histos[iSample]->Scale(SF);

			double imax = TMath::Max(Histos[iSample]->GetMaximum(),Histos[0]->GetMaximum());			
			Histos[iSample]->GetYaxis()->SetRangeUser(0.,1.1*imax);
			Histos[0]->GetYaxis()->SetRangeUser(0.,1.1*imax);			

			PlotCanvas->cd();
			Histos[iSample]->Draw("hist same");
			Histos[0]->Draw("hist same");	

			//----------------------------------------//

			TH1D* Clone = (TH1D*)(Histos[iSample]->Clone());
			double SFAreaNorm = CloneAreaNorm->Integral() / Clone->Integral();
			Clone->Scale(SFAreaNorm);	

			double imaxAreaNorm = TMath::Max(Clone->GetMaximum(),CloneAreaNorm->GetMaximum());
			Clone->GetYaxis()->SetRangeUser(0.,1.1*imaxAreaNorm);
			CloneAreaNorm->GetYaxis()->SetRangeUser(0.,1.1*imaxAreaNorm);

			PlotCanvasAreaNorm->cd();
			Clone->Draw("hist same");	
			CloneAreaNorm->Draw("hist same");		

			//----------------------------------------//						

			TLegendEntry* legEntry = leg->AddEntry(Histos[iSample],BeamOnLabels[iSample] + ", " +TString( ToString(BeamOnPOT[iSample]) ),"l");
			legEntry->SetTextColor( BeamOnColors.at(iSample) );		

			//----------------------------------------//					

		} // End of the loop over the samples grabing the plots	

		PlotCanvas->cd();
		leg->Draw();

		PlotCanvasAreaNorm->cd();
		leg->Draw();		

		PlotCanvas->SaveAs(PlotPath+"Run4a_Validation_"+PlotNames[iPlot]+".pdf");
		PlotCanvasAreaNorm->SaveAs(PlotPath+"Run4a_Validation_"+PlotNames[iPlot]+"_AreaNorm.pdf");	

		//delete PlotCanvas;
		delete PlotCanvasAreaNorm;		

	} // End of the loop over the plots

	//------------------------------//

} // End of the program
