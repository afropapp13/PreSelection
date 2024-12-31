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

void THStacked() {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	const int FontStyle = 132;
	const double TextSize = 0.06;	
	
	const TString EventTTreeName = "nuselection/NeutrinoSelectionFilter";
	
	//const TString Cut = "trk_score_v < 0";
	//const TString Cut = "nslice == 1";
	const TString Cut = "nslice == 1";	
	const TString MCWeight = "weightSpline * ( (weightSpline > 0. && weightSpline < 30. && weightTune > 0. && weightTune < 30.)? weightTune:0.)";	
	//const TString Cut = "";	

	//------------------------------//
	
	std::vector<TString> BeamOnName;  std::vector<TFile*> BeamOnFile;  std::vector<TTree*> BeamOnTTree;  std::vector<double> BeamOnScale;
	std::vector<TString> BeamOffName; std::vector<TFile*> BeamOffFile; std::vector<TTree*> BeamOffTTree; std::vector<double> BeamOffScale;
	std::vector<TString> OverlayName; std::vector<TFile*> OverlayFile; std::vector<TTree*> OverlayTTree; std::vector<double> OverlayScale;
	std::vector<TString> DirtName;    std::vector<TFile*> DirtFile;    std::vector<TTree*> DirtTTree;    std::vector<double> DirtScale;
	
	std::vector<TString> Runs{"Run1","Run2","Run3","Run4a","Run4b","Run4c","Run4d","Run5"};
	//std::vector<TString> Runs{"Run4a"};
	const int NRuns = Runs.size();	
	
	for (int irun = 0; irun < NRuns; irun++) {
	
		if (Runs[irun] == "Run1") {
		
			BeamOnName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/bnb_beam_on_peleeTuple_uboone_v08_00_00_70_run1_C1.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/combined/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run1.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.57);	
			
			OverlayName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run1_nu.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.13);	
			
			DirtName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run1_dirt.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.528);		
		
		}
	
		if (Runs[irun] == "Run2") {
		
			BeamOnName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/combined/bnb_beam_on_peleeTuple_uboone_v08_00_00_70_run2.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/combined/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run2.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.4);	
			
			OverlayName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run2_nu.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.257);	
			
			DirtName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run2a_dirt.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.477);															
		
		}	
		
		if (Runs[irun] == "Run3") {
		
			BeamOnName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3/bnb_beam_on_peleeTuple_uboone_v08_00_00_70_run3.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run3.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.296);
			
			OverlayName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run3_nu.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.195);	
			
			DirtName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run3_dirt.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.785);	
		
		}
		
		if (Runs[irun] == "Run4a") {
		
			BeamOnName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/Run4a_bnb_beamOn_PeLee_ntuples_run4a_ana.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/Run4a_bnb_beamOff_PeLee_ntuples_run4a_ana.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.349);
			
			OverlayName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/run4a_bnb_nu_overlay_unified_pandora_reco2_run4a_ana.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.223); 	
			
			DirtName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/Run4a_BNB_dirt_overlay_Pandora_Unified_Reco2_fixed_run4a_ana.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.501);
		
		}			

		if (Runs[irun] == "Run4b") {
		
			BeamOnName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/Run4b_bnb_beamOn_PeLee_ntuples_run4b_ana.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/Run4b_bnb_beamOff_PeLee_ntuples_run4b_ana.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.38);
			
			OverlayName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/run4b_bnb_nu_overlay_unified_pandora_reco2_run4b_ana.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.194);
			
			DirtName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/Run4b_BNB_dirt_overlay_Pandora_Reco2_reco2_ana.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.487);		
		
		}	

		if (Runs[irun] == "Run4c") {
		
			BeamOnName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/Run4c_bnb_beamOn_PeLee_ntuples_run4c_ana_ana.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/Run4c_bnb_beamOff_PeLee_ntuples_run4c_ana_ana.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.405); 	
			
			OverlayName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run4c_nu.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.196);
			
			DirtName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run4c_dirt.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.512);	
		
		}	

		if (Runs[irun] == "Run4d") {
		
			BeamOnName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4d/Run4d_bnb_beamOn_PeLee_ntuples_run4d_ana_ana.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4d/Run4d_bnb_beamOff_PeLee_ntuples_run4d_ana_ana.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.151);
			
			OverlayName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run4d_nu.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.0578);
			
			DirtName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4d/Run4d_BNB_dirt_overlay_Pandora_Unified_Reco2_reco2_ana.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.249);
		
		}	


		if (Runs[irun] == "Run5") {		
		
			BeamOnName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/run5_bnb_beamon_PeLEE_ntuples_run5_ana.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/Run5_bnb_beamOff_PeLee_ntuples_run5_ana_ana.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.323);
			
			OverlayName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/run5_bnb_nu_overlay_ntuple_v08_00_00_67_run5_ana.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.178);
			
			DirtName.push_back("root://fndca1.fnal.gov:1094//pnfs/uboone/persistent/users/jdetje/pelee_v08_00_00_70/overlay_peleeTuple_uboone_v08_00_00_70_run5_dirt.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.434);
		
		}						
	
	}

	//------------------------------//

	// Plots to include

	std::vector<TString> PlotNames; std::vector< double> Min; std::vector<double> Max;  std::vector<int> NBins;

	//PlotNames.push_back("selected"); Min.push_back(-0.5); Max.push_back(1.5); NBins.push_back(2);
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
	PlotNames.push_back("nu_flashmatch_score"); Min.push_back(0.); Max.push_back(50.); NBins.push_back(50);
	PlotNames.push_back("trk_score_v"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(50);		
	PlotNames.push_back("pfpdg"); Min.push_back(10.5); Max.push_back(13.5); NBins.push_back(3);
	PlotNames.push_back("trk_llr_pid_score_v"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(100);
	PlotNames.push_back("pfp_generation_v"); Min.push_back(1.5); Max.push_back(4.5); NBins.push_back(3);
	PlotNames.push_back("cos(trk_theta_v)"); Min.push_back(-1.); Max.push_back(1.); NBins.push_back(20);
	PlotNames.push_back("crtveto"); Min.push_back(-0.5); Max.push_back(1.5); NBins.push_back(2);	
	PlotNames.push_back("crthitpe"); Min.push_back(40); Max.push_back(570); NBins.push_back(100);		

	const int NPlots = PlotNames.size();	

	//------------------------------//
	
	// Loop over the runs
	
	for (int irun = 0; irun < NRuns; irun++) {

		// Loop over the plots to be compared

		for (int iplot = 0; iplot < NPlots; iplot++) {

			THStack* stack = new THStack(PlotNames[iplot],"");

			TString CanvasName = "Canvas_" + Runs[irun] + "_" + PlotNames[iplot];
			TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
			PlotCanvas->cd();
			PlotCanvas->SetTopMargin(0.12);
			PlotCanvas->SetLeftMargin(0.15);
			PlotCanvas->SetBottomMargin(0.15);		
			PlotCanvas->Draw();		

			TLegend* leg = new TLegend(0.3,0.89,0.9,0.99);
			leg->SetBorderSize(0);
			leg->SetNColumns(2);
			leg->SetTextSize(TextSize);	
			leg->SetTextFont(FontStyle);
			leg->SetMargin(0.15);	
			
			TString HistoNameTString = PlotNames[iplot];
			HistoNameTString.ReplaceAll("(","_").ReplaceAll(")","_");										

			TString BeamOnHistoName = "BeamOn_" + HistoNameTString + "_" + TString(Runs[irun]);
			TH1D* BeamOnHisto = new TH1D(BeamOnHistoName,";" + PlotNames[iplot],NBins[iplot],Min[iplot],Max[iplot]);
			BeamOnTTree[irun]->Draw(PlotNames[iplot] + ">>" + BeamOnHistoName,"("+Cut+")*"+ToString(BeamOnScale[irun]),"goff");
			
			TString BeamOffHistoName = "BeamOff_" + HistoNameTString + "_" + TString(Runs[irun]);
			TH1D* BeamOffHisto = new TH1D(BeamOffHistoName,";" + PlotNames[iplot],NBins[iplot],Min[iplot],Max[iplot]);
			BeamOffTTree[irun]->Draw(PlotNames[iplot] + ">>" + BeamOffHistoName,"("+Cut+")*"+ToString(BeamOffScale[irun]),"goff");
			
			TString OverlayHistoName = "Overlay_" + HistoNameTString + "_" + TString(Runs[irun]);
			TH1D* OverlayHisto = new TH1D(OverlayHistoName,";" + PlotNames[iplot],NBins[iplot],Min[iplot],Max[iplot]);
			OverlayTTree[irun]->Draw(PlotNames[iplot] + ">>" + OverlayHistoName,"("+Cut+")*"+ToString(OverlayScale[irun]) + " * " + MCWeight,"goff");
			
			TString DirtHistoName = "Dirt_" + HistoNameTString + "_" + TString(Runs[irun]);
			TH1D* DirtHisto = new TH1D(DirtHistoName,";" + PlotNames[iplot],NBins[iplot],Min[iplot],Max[iplot]);
			DirtTTree[irun]->Draw(PlotNames[iplot] + ">>" + DirtHistoName,"("+Cut+")*"+ToString(DirtScale[irun]),"goff");						

			BeamOnHisto->SetLineWidth(2);
			BeamOnHisto->SetLineColor(kBlack);	
			BeamOnHisto->SetMarkerColor(kBlack);
			BeamOnHisto->SetMarkerStyle(20);
			BeamOnHisto->SetMarkerSize(2.);										

			double DataPOT = PeLEE_ReturnBeamOnRunPOT(Runs[irun]);	

			BeamOnHisto->GetXaxis()->SetTitleFont(FontStyle);
			BeamOnHisto->GetXaxis()->SetLabelFont(FontStyle);
			BeamOnHisto->GetXaxis()->SetNdivisions(8);
			BeamOnHisto->GetXaxis()->SetLabelSize(TextSize);
			BeamOnHisto->GetXaxis()->SetTitleSize(TextSize);	
			BeamOnHisto->GetXaxis()->SetTitleOffset(1.1);					
			BeamOnHisto->GetXaxis()->CenterTitle();						

			BeamOnHisto->GetYaxis()->SetTitleFont(FontStyle);
			BeamOnHisto->GetYaxis()->SetLabelFont(FontStyle);
			BeamOnHisto->GetYaxis()->SetNdivisions(6);
			BeamOnHisto->GetYaxis()->SetLabelSize(TextSize);
			BeamOnHisto->GetYaxis()->SetTitle("# Events / " + TString( ToString(DataPOT) ) );
			BeamOnHisto->GetYaxis()->SetTitleSize(TextSize);
			BeamOnHisto->GetYaxis()->SetTitleOffset(1.3);
			BeamOnHisto->GetYaxis()->SetTickSize(0);
			BeamOnHisto->GetYaxis()->CenterTitle();	
			BeamOnHisto->GetYaxis()->SetRangeUser(0.,1.25*BeamOnHisto->GetMaximum());

			BeamOnHisto->Draw("e same");
			double BeamOnEvents = BeamOnHisto->Integral();

			//TLegendEntry* legData = leg->AddEntry(BeamOnHisto, "BeamOn (" + TString( ToString(BeamOnEvents) ) + ")","ep");
			TLegendEntry* legData = leg->AddEntry(BeamOnHisto, "BeamOn","ep");			
			legData->SetTextColor(kBlack);				

			//----------------------------------------//			

			OverlayHisto->SetLineColor(OverlayColor);
			OverlayHisto->SetFillColor(OverlayColor);
			OverlayHisto->SetLineWidth(1);
			stack->Add(OverlayHisto,"hist");
			stack->Draw("same");

			double OverlayEvents = OverlayHisto->Integral();
//			TLegendEntry* legOverlay = leg->AddEntry(OverlayHisto, "MC (" + TString( ToString(OverlayEvents) ) + ")","f");
			TLegendEntry* legOverlay = leg->AddEntry(OverlayHisto, "MC","f");
			legOverlay->SetTextColor(OverlayColor);			

			//----------------------------------------//			

			DirtHisto->SetLineColor(kOrange-3);
			DirtHisto->SetFillColor(kOrange-3);
			DirtHisto->SetLineWidth(1);
			stack->Add(DirtHisto,"hist");
			stack->Draw("same");	

			double DirtEvents = DirtHisto->Integral();
//			TLegendEntry* legDirt = leg->AddEntry(DirtHisto, "Dirt (" + TString( ToString(DirtEvents) ) + ")","f");
			TLegendEntry* legDirt = leg->AddEntry(DirtHisto, "Dirt","f");
			legDirt->SetTextColor(kOrange-3);			
			
			//----------------------------------------//			

			BeamOffHisto->SetLineColor(kGray+1);
			BeamOffHisto->SetFillColor(kGray+1);
			BeamOffHisto->SetFillStyle(3004);
			BeamOffHisto->SetLineWidth(1);
			stack->Add(BeamOffHisto,"hist");
			stack->Draw("same");	

			double BeamOffEvents = BeamOffHisto->Integral();
//			TLegendEntry* legBeamOff = leg->AddEntry(BeamOffHisto, "BeamOff (" + TString( ToString(BeamOffEvents) ) + ")","f");
			TLegendEntry* legBeamOff = leg->AddEntry(BeamOffHisto, "BeamOff","f");
			legBeamOff->SetTextColor(kGray+1);

			//----------------------------------------//					

			BeamOnHisto->Draw("e same");

			leg->Draw();	

			TLatex *text = new TLatex();
			text->SetTextFont(FontStyle);
			text->SetTextSize(TextSize);
			text->DrawTextNDC(0.75, 0.83, Runs[irun]);			

			PlotCanvas->SaveAs(PlotPath+"THStack" + Runs[irun] + "_Validation_"+ HistoNameTString +".pdf");

			//delete PlotCanvas;

		} // End of the loop over the plots

	} // End of the loop over the runs

	//------------------------------//

} // End of the program
