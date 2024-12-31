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

#include "../../../myClasses/Constants.h"

using namespace Constants;

void BeamOnComparisons() {

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
	
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/bnb_beam_on_peleeTuple_uboone_v08_00_00_70_run1_C1.root"); 
	BeamOnLabels.push_back("Run 1");
	BeamOnColors.push_back(kBlue+2);	
	BeamOnPOT.push_back(Fulltor860_wcut_Run1);
	
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1_opentrigger/run1_bnb_opentrigger_pandora_real_ntuple_3v_A_ana_goodruns.root"); 
	BeamOnLabels.push_back("Run 1A open trigger");
	BeamOnColors.push_back(kMagenta);	
	BeamOnPOT.push_back(Fulltor860_wcut_Run1A_open_trigger);
	
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1_opentrigger/run1_bnb_opentrigger_pandora_real_ntuple_3v_B_ana_goodruns.root"); 
	BeamOnLabels.push_back("Run 1B open trigger");
	BeamOnColors.push_back(kPink+2);	
	BeamOnPOT.push_back(Fulltor860_wcut_Run1B_open_trigger);
	
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/combined/bnb_beam_on_peleeTuple_uboone_v08_00_00_70_run2.root"); 
	BeamOnLabels.push_back("Run 2");
	BeamOnColors.push_back(kAzure-4);	
	BeamOnPOT.push_back(Fulltor860_wcut_Run2);

	BeamOnNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3/run3_bnb_beam_on_crtremerging_pandora_reco2_run3_ana.root"); 
	BeamOnLabels.push_back("Run 3");
	BeamOnColors.push_back(kGreen+2);	
	BeamOnPOT.push_back(Fulltor860_wcut_Run3);	
	
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/Run4a_bnb_beamOn_PeLee_ntuples_run4a_ana.root");	
	BeamOnLabels.push_back("Run 4a");	
	BeamOnColors.push_back(kViolet);
	BeamOnPOT.push_back(Fulltor860_wcut_Run4a);	
		
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/run4b_bnb_beamon_crtremerging_pandora_reco2_run4b_ana.root");	
	BeamOnLabels.push_back("Run 4b");	
	BeamOnColors.push_back(kOrange+7);
	BeamOnPOT.push_back(Fulltor860_wcut_Run4b);
		
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/run4c_bnb_beamon_crtremerging_pandora_reco2_run4c_ana.root");	
	BeamOnLabels.push_back("Run 4c");	
	BeamOnColors.push_back(kMagenta-7);
	BeamOnPOT.push_back(Fulltor860_wcut_Run4c);
	
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4d/Run4d_bnb_beamOn_PeLee_ntuples_run4d_ana_ana.root");	
	BeamOnLabels.push_back("Run 4d");	
	BeamOnColors.push_back(kCyan-3);
	BeamOnPOT.push_back(Fulltor860_wcut_Run4d);
	
	BeamOnNames.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/run5_bnb_beamon_PeLEE_ntuples_run5_ana.root");	
	BeamOnLabels.push_back("Run 5");	
	BeamOnColors.push_back(kRed+1);
	BeamOnPOT.push_back(Fulltor860_wcut_Run5);					

	//------------------------------//		

	const int NSamples = BeamOnNames.size();

	std::vector<TFile*> BeamOnFiles; BeamOnFiles.resize(NSamples);

	//------------------------------//

	// TTree names & pointers

	TString EventTTreeName = "nuselection/NeutrinoSelectionFilter";
	std::vector<TTree*> EventTTree; EventTTree.resize(NSamples);

	//------------------------------//

	// Cut

	//TString Cut = "trk_score_v < 0";
	TString Cut = "nslice == 1";
	//TString Cut = "";
	//TString Cut = "nslice == 1 && topological_score > 0.5 && n_tracks_contained > 0";
	//TString Cut = "nslice == 1 && topological_score > 0.5";			

	//------------------------------//

	// Plots to include

	std::vector<TString> PlotNames; std::vector< double> Min; std::vector<double> Max;  std::vector<int> NBins;

	//PlotNames.push_back("selected"); Min.push_back(-0.5); Max.push_back(1.5); NBins.push_back(2);
	PlotNames.push_back("n_tracks"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);	
	PlotNames.push_back("n_showers"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);
	PlotNames.push_back("reco_nu_vtx_sce_x"); Min.push_back(10.); Max.push_back(246.); NBins.push_back(25);
	PlotNames.push_back("reco_nu_vtx_sce_y"); Min.push_back(-105.); Max.push_back(105.); NBins.push_back(25);	
	PlotNames.push_back("reco_nu_vtx_sce_z"); Min.push_back(10.); Max.push_back(1026.); NBins.push_back(25);
	PlotNames.push_back("hits_u"); Min.push_back(1); Max.push_back(1000); NBins.push_back(25);
	PlotNames.push_back("hits_v"); Min.push_back(1); Max.push_back(1000); NBins.push_back(25);
	PlotNames.push_back("hits_y"); Min.push_back(1); Max.push_back(1000); NBins.push_back(25);	
	PlotNames.push_back("topological_score"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(50);				
	PlotNames.push_back("nslice"); Min.push_back(0.5); Max.push_back(1.5); NBins.push_back(1);
	PlotNames.push_back("nu_flashmatch_score"); Min.push_back(0.); Max.push_back(50.); NBins.push_back(25);
	PlotNames.push_back("trk_score_v"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(50);		
	PlotNames.push_back("pfpdg"); Min.push_back(10.5); Max.push_back(13.5); NBins.push_back(3);
	PlotNames.push_back("trk_llr_pid_score_v"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(50);
	PlotNames.push_back("pfp_generation_v"); Min.push_back(1.5); Max.push_back(4.5); NBins.push_back(3);
	PlotNames.push_back("cos(trk_theta_v)"); Min.push_back(-1.); Max.push_back(1.); NBins.push_back(20);
	//PlotNames.push_back("cos(trk_theta)"); Min.push_back(-1.); Max.push_back(1.); NBins.push_back(20);
	PlotNames.push_back("trk_len_v"); Min.push_back(0.); Max.push_back(100.); NBins.push_back(20);
	PlotNames.push_back("crtveto"); Min.push_back(-0.5); Max.push_back(1.5); NBins.push_back(2);
	PlotNames.push_back("crthitpe"); Min.push_back(40); Max.push_back(570); NBins.push_back(100);					

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
		PlotCanvas->SetTopMargin(0.14);
		PlotCanvas->SetLeftMargin(0.15);
		PlotCanvas->SetBottomMargin(0.15);		
		PlotCanvas->Draw();	

		/*
		TString CanvasNameAreaNorm = "AreaNormCanvas_" + PlotNames[iPlot];
		TCanvas* PlotCanvasAreaNorm = new TCanvas(CanvasNameAreaNorm,CanvasNameAreaNorm,205,34,1024,768);
		PlotCanvasAreaNorm->cd();
		PlotCanvasAreaNorm->SetTopMargin(0.12);
		PlotCanvasAreaNorm->SetLeftMargin(0.15);
		PlotCanvasAreaNorm->SetBottomMargin(0.15);		
		PlotCanvasAreaNorm->Draw();		
*/

		TLegend* leg = new TLegend(0.01,0.87,0.99,0.98);
		leg->SetBorderSize(0);
		leg->SetNColumns(3);
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
			EventTTree[iSample]->Draw(PlotNames[iPlot] + ">>" + HistosName[iSample],Cut,"goff");

			Histos[iSample]->SetLineWidth(2);
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
			Histos[iSample]->GetYaxis()->SetTickSize(0.02);
			Histos[iSample]->GetYaxis()->CenterTitle();	

			/*
			TH1D* CloneAreaNorm = (TH1D*)(Histos[0]->Clone());
			*/

			//----------------------------------------//

			double SF = BeamOnPOT[0] / BeamOnPOT[iSample];
//			double SF = 1. / Histos[iSample]->GetEntries();
			double NEvents = Histos[iSample]->GetEntries();
			Histos[iSample]->Scale(SF);

			double imax = TMath::Max(Histos[iSample]->GetMaximum(),Histos[0]->GetMaximum());			
			Histos[iSample]->GetYaxis()->SetRangeUser(0.,1.05*imax);
			Histos[0]->GetYaxis()->SetRangeUser(0.,1.05*imax);			

			PlotCanvas->cd();
			Histos[iSample]->SetMarkerColor(BeamOnColors.at(iSample));
			Histos[iSample]->SetMarkerStyle(20);
			Histos[iSample]->SetMarkerSize(2.);				
			Histos[iSample]->Draw("e same");
			Histos[0]->Draw("e same");	

			//----------------------------------------//

			/*TH1D* Clone = (TH1D*)(Histos[iSample]->Clone());
			double SFAreaNorm = CloneAreaNorm->Integral() / Clone->Integral();
			Clone->Scale(SFAreaNorm);

			double imaxAreaNorm = TMath::Max(Clone->GetMaximum(),CloneAreaNorm->GetMaximum());
			Clone->GetYaxis()->SetRangeUser(0.,1.1*imaxAreaNorm);
			CloneAreaNorm->GetYaxis()->SetRangeUser(0.,1.1*imaxAreaNorm);

			PlotCanvasAreaNorm->cd();
			Clone->Draw("e hist same");	
			CloneAreaNorm->Draw("e hist same");*/	

			//----------------------------------------//						

//			TLegendEntry* legEntry = leg->AddEntry(Histos[iSample],BeamOnLabels[iSample] + ", " +TString( ToString(BeamOnPOT[iSample]) ) + " (" + TString( ToString(NEvents) ) + ")","l");
			TLegendEntry* legEntry = leg->AddEntry(Histos[iSample],BeamOnLabels[iSample] + ", " +TString( ToString(BeamOnPOT[iSample]) ),"ep");
			legEntry->SetTextColor( BeamOnColors.at(iSample) );		

			//----------------------------------------//					

		} // End of the loop over the samples grabing the plots	

		PlotCanvas->cd();
		leg->Draw();
		
		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);
		text->DrawTextNDC(0.18, 0.82, "BeamOn");		

		/*PlotCanvasAreaNorm->cd();*
		leg->Draw();	
		text->DrawTextNDC(0.16, 0.85, "BeamOn");*/			

		TString CanvasNameTString = "/exp/"+PlotPath+"Run4a_Validation_"+PlotNames[iPlot]+".pdf";
		CanvasNameTString.ReplaceAll("(","_").ReplaceAll(")","_");

		/*
		TString CanvasNameTStringNorm = PlotPath+"Run4a_Validation_"+PlotNames[iPlot]+"_AreaNorm.pdf";
		CanvasNameTStringNorm.ReplaceAll("(","_").ReplaceAll(")","_");		
		*/

		PlotCanvas->SaveAs(CanvasNameTString);
		/*PlotCanvasAreaNorm->SaveAs(CanvasNameTStringNorm);*/	

		//delete PlotCanvas;
		//delete PlotCanvasAreaNorm;		

	} // End of the loop over the plots

	//------------------------------//

} // End of the program
