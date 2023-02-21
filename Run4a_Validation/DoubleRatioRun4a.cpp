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

void DoubleRatioRun4a() {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	const int FontStyle = 132;
	const double TextSize = 0.06;	
	
	const TString EventTTreeName = "nuselection/NeutrinoSelectionFilter";
	
	//const TString Cut = "trk_score_v < 0";
	const TString Cut = "nslice == 1 && topological_score > 0.5";
	const TString MCWeight = "weightSpline * ( (weightSpline > 0. && weightSpline < 30. && weightTune > 0. && weightTune < 30.)? weightTune:0.)";		
	//const TString Cut = "";	

	//------------------------------//
	
	std::vector<TString> BeamOnName;  std::vector<TFile*> BeamOnFile;  std::vector<TTree*> BeamOnTTree;  std::vector<double> BeamOnScale;
	std::vector<TString> BeamOffName; std::vector<TFile*> BeamOffFile; std::vector<TTree*> BeamOffTTree; std::vector<double> BeamOffScale;
	std::vector<TString> OverlayName; std::vector<TFile*> OverlayFile; std::vector<TTree*> OverlayTTree; std::vector<double> OverlayScale;
	std::vector<TString> DirtName;    std::vector<TFile*> DirtFile;    std::vector<TTree*> DirtTTree;    std::vector<double> DirtScale;
	
	std::vector<TString> Runs{"Run1","Run2","Run3","Run4a"};
//	std::vector<TString> Runs{"Run4a"};
	const int NRuns = Runs.size();	
	
	std::vector<int> Colors;	
	
	for (int irun = 0; irun < NRuns; irun++) {
	
		if (Runs[irun] == "Run1") {
		
			Colors.push_back(kBlue+2);
		
			BeamOnName.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run1_neutrinoselection_filt_numu_ALL.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run1/data_extbnb_mcc9.1_v08_00_00_25_reco2_C_all_reco2.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.551754065);	
			
			OverlayName.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run1_reco2_reco2.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.123664122);	
			
			DirtName.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run1_reco2_reco2.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.218623482);															
		
		}
	
		if (Runs[irun] == "Run2") {
		
			Colors.push_back(kMagenta-1);		
		
			BeamOnName.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run2_neutrinoselection_filt_numu_ALL.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run2/data_extbnb_mcc9.1_v08_00_00_25_reco2_D_E_all_reco2.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.407111347);	
			
			OverlayName.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run2_reco2_D1D2_reco2.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.256862745);	
			
			DirtName.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run2_reco2_reco2.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.346560847);															
		
		}	
		
		if (Runs[irun] == "Run3") {
		
			Colors.push_back(kGreen+2);		
		
			BeamOnName.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run3_neutrinoselection_filt_numu_ALL.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run3/data_extbnb_mcc9.1_v08_00_00_25_reco2_F_G_all_reco2.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.284369535);
			
			OverlayName.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run3_reco2_G_reco2.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.190298507);	
			
			DirtName.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run3_reco2_reco2.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.349794239);															
		
		}
		
		if (Runs[irun] == "Run4a") {
		
			Colors.push_back(kOrange+7);		
		
			BeamOnName.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1121/quality/bnb_on_run4a_reco2_v08_00_00_63_POT_DEBUG_run4a_reco2_beam_good.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1121/quality/bnb_run4a_ext_reco2_v08_00_00_63_run4a_reco2_all.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.318); // fix	
			
			OverlayName.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1121/prod_extunbiased_standard_nu_overlay_run4a_reco2_WC_v08_00_00_63_pndr_reco2_reco2_goodruns_goodbeam.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.107); // fix	
			
			DirtName.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1121/prod_extunbiased_bnb_dirt_overlay_run4a_reco2_v08_00_00_63_run4a_reco2_goodruns_goodbeam.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.046); // fix															
		
		}				
	
	}

	//------------------------------//

	// Plots to include

	std::vector<TString> PlotNames; std::vector< double> Min; std::vector<double> Max;  std::vector<int> NBins;

	//PlotNames.push_back("selected"); Min.push_back(-0.5); Max.push_back(1.5); NBins.push_back(2);
	PlotNames.push_back("n_tracks"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);	
	PlotNames.push_back("n_showers"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);
	PlotNames.push_back("reco_nu_vtx_sce_x"); Min.push_back(0.); Max.push_back(250); NBins.push_back(50);
	PlotNames.push_back("reco_nu_vtx_sce_y"); Min.push_back(-130); Max.push_back(130); NBins.push_back(50);	
	PlotNames.push_back("reco_nu_vtx_sce_z"); Min.push_back(0.); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_u"); Min.push_back(1); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_v"); Min.push_back(1); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_y"); Min.push_back(1); Max.push_back(1000); NBins.push_back(50);	
	PlotNames.push_back("topological_score"); Min.push_back(0); Max.push_back(1); NBins.push_back(50);				
	PlotNames.push_back("nslice"); Min.push_back(-0.5); Max.push_back(2.5); NBins.push_back(3);
	PlotNames.push_back("nu_flashmatch_score"); Min.push_back(0.); Max.push_back(50.); NBins.push_back(40);
	PlotNames.push_back("trk_score_v"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(40);		
	PlotNames.push_back("pfpdg"); Min.push_back(10.5); Max.push_back(13.5); NBins.push_back(3);
	PlotNames.push_back("trk_llr_pid_score_v"); Min.push_back(0.5); Max.push_back(1.); NBins.push_back(25);
	PlotNames.push_back("pfp_generation_v"); Min.push_back(1.5); Max.push_back(4.5); NBins.push_back(3);

	const int NPlots = PlotNames.size();	

	//------------------------------//
	
	// Loop over the plots to be compared

	for (int iplot = 0; iplot < NPlots; iplot++) {	
	
		TString CanvasName = "Canvas_" + PlotNames[iplot];
		TCanvas* PlotCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
		PlotCanvas->cd();
		PlotCanvas->SetTopMargin(0.12);
		PlotCanvas->SetLeftMargin(0.12);
		PlotCanvas->SetBottomMargin(0.15);
		PlotCanvas->SetGridx();
		PlotCanvas->SetGridy();						
		PlotCanvas->Draw();		

		TLegend* leg = new TLegend(0.03,0.89,0.97,0.99);
		leg->SetBorderSize(0);
		leg->SetNColumns(2);
		leg->SetTextSize(TextSize);	
		leg->SetTextFont(FontStyle);
		leg->SetMargin(0.15);		
	
		// Loop over the runs
	
		for (int irun = 0; irun < NRuns; irun++) {							

			TString BeamOnHistoName = "BeamOn_" +PlotNames[iplot] + "_" + TString(Runs[irun]);
			TH1D* BeamOnHisto = new TH1D(BeamOnHistoName,";" + PlotNames[iplot],NBins[iplot],Min[iplot],Max[iplot]);
			BeamOnTTree[irun]->Draw(PlotNames[iplot] + ">>" + BeamOnHistoName,"("+Cut+")*"+ToString(BeamOnScale[irun]),"goff");
			
			TString BeamOffHistoName = "BeamOff_" +PlotNames[iplot] + "_" + TString(Runs[irun]);
			TH1D* BeamOffHisto = new TH1D(BeamOffHistoName,";" + PlotNames[iplot],NBins[iplot],Min[iplot],Max[iplot]);
			BeamOffTTree[irun]->Draw(PlotNames[iplot] + ">>" + BeamOffHistoName,"("+Cut+")*"+ToString(BeamOffScale[irun]),"goff");
			
			TString OverlayHistoName = "Overlay_" +PlotNames[iplot] + "_" + TString(Runs[irun]);
			TH1D* OverlayHisto = new TH1D(OverlayHistoName,";" + PlotNames[iplot],NBins[iplot],Min[iplot],Max[iplot]);
			OverlayTTree[irun]->Draw(PlotNames[iplot] + ">>" + OverlayHistoName,"("+Cut+")*"+ToString(OverlayScale[irun]) + " * " + MCWeight,"goff");
			
			TString DirtHistoName = "Dirt_" +PlotNames[iplot] + "_" + TString(Runs[irun]);
			TH1D* DirtHisto = new TH1D(DirtHistoName,";" + PlotNames[iplot],NBins[iplot],Min[iplot],Max[iplot]);
			DirtTTree[irun]->Draw(PlotNames[iplot] + ">>" + DirtHistoName,"("+Cut+")*"+ToString(DirtScale[irun]) + " * " + MCWeight,"goff");						

			double DataPOT = PeLEE_ReturnBeamOnRunPOT(Runs[irun]);	

			BeamOnHisto->SetLineWidth(2);
			BeamOnHisto->SetLineColor(Colors[irun]);	
			BeamOnHisto->SetMarkerColor(Colors[irun]);
			BeamOnHisto->SetMarkerStyle(20);
			BeamOnHisto->SetMarkerSize(2.);										

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
//			BeamOnHisto->GetYaxis()->SetTitle("# Events / " + TString( ToString(DataPOT) ) );
			BeamOnHisto->GetYaxis()->SetTitle("Data/(MC+ExtBNB)");
			BeamOnHisto->GetYaxis()->SetTitleSize(TextSize);
			BeamOnHisto->GetYaxis()->SetTitleOffset(1.);
			BeamOnHisto->GetYaxis()->SetTickSize(0);
			BeamOnHisto->GetYaxis()->CenterTitle();	
			BeamOnHisto->GetYaxis()->SetRangeUser(0.01,1.99);
			
			OverlayHisto->Add(DirtHisto);
			OverlayHisto->Add(BeamOffHisto);			

			double BeamOnEvents = BeamOnHisto->Integral();
			BeamOnHisto->Divide(OverlayHisto);
			BeamOnHisto->Draw("e same");
			
			TLegendEntry* legData = leg->AddEntry(BeamOnHisto, Runs[irun] + " " + TString( ToString(DataPOT) ) + " (" + TString( ToString(BeamOnEvents) ) + ")","ep");
			legData->SetTextColor(Colors[irun]);							

		} // End of the loop over the runs
		
		leg->Draw();		
		
		PlotCanvas->SaveAs(PlotPath+"DoubleRatio_Validation_"+PlotNames[iplot]+".pdf");

		//delete PlotCanvas;		
	
	} // End of the loop over the plots	

	//------------------------------//

} // End of the program
