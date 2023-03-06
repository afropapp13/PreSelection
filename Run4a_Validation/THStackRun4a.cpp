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

void THStackRun4a() {

	//------------------------------//

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();
	gStyle->SetOptStat(0);

	const int FontStyle = 132;
	const double TextSize = 0.06;	
	
	const TString EventTTreeName = "nuselection/NeutrinoSelectionFilter";
	
	//const TString Cut = "trk_score_v < 0";
	//const TString Cut = "nslice == 1";
	const TString Cut = "nslice == 1 && topological_score > 0.5";	
	const TString MCWeight = "weightSpline * ( (weightSpline > 0. && weightSpline < 30. && weightTune > 0. && weightTune < 30.)? weightTune:0.)";	
	//const TString Cut = "";	

	//------------------------------//
	
	std::vector<TString> BeamOnName;  std::vector<TFile*> BeamOnFile;  std::vector<TTree*> BeamOnTTree;  std::vector<double> BeamOnScale;
	std::vector<TString> BeamOffName; std::vector<TFile*> BeamOffFile; std::vector<TTree*> BeamOffTTree; std::vector<double> BeamOffScale;
	std::vector<TString> OverlayName; std::vector<TFile*> OverlayFile; std::vector<TTree*> OverlayTTree; std::vector<double> OverlayScale;
	std::vector<TString> DirtName;    std::vector<TFile*> DirtFile;    std::vector<TTree*> DirtTTree;    std::vector<double> DirtScale;
	
	std::vector<TString> Runs{"Run1","Run2","Run3","Run4a","Run4b"};
//	std::vector<TString> Runs{"Run4a"};
	const int NRuns = Runs.size();	
	
	for (int irun = 0; irun < NRuns; irun++) {
	
		if (Runs[irun] == "Run1") {
		
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

		if (Runs[irun] == "Run4b") {
		
			BeamOnName.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_65/022723/v01/bnb_on_run4b_reco2_v08_00_00_63_run4b_reco2_beam_good.root");
			BeamOnFile.push_back(new TFile(BeamOnName[irun],"readonly"));
			BeamOnTTree.push_back( (TTree*)( BeamOnFile[irun]->Get(EventTTreeName) ) );
			BeamOnScale.push_back(1.);
			
			BeamOffName.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_65/022723/v01/bnb_run4b_ext_reco2_v08_00_00_63_run4b_reco2_all.root");
			BeamOffFile.push_back(new TFile(BeamOffName[irun],"readonly"));
			BeamOffTTree.push_back( (TTree*)( BeamOffFile[irun]->Get(EventTTreeName) ) );
			BeamOffScale.push_back(0.356); 	
			
			OverlayName.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_65/022723/v01/run4b_bnb_nu_overlay_pandora_reco2_run4b_pandora_reco2_reco2.root");
			OverlayFile.push_back(new TFile(OverlayName[irun],"readonly"));
			OverlayTTree.push_back( (TTree*)( OverlayFile[irun]->Get(EventTTreeName) ) );
			OverlayScale.push_back(0.227);
			
			DirtName.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_65/022723/v01/prod_extunbiased_bnb_dirt_overlay_run4b_v08_00_00_63_run4b_reco2.root");
			DirtFile.push_back(new TFile(DirtName[irun],"readonly"));
			DirtTTree.push_back( (TTree*)( DirtFile[irun]->Get(EventTTreeName) ) );
			DirtScale.push_back(0.54); 															
		
		}					
	
	}

	//------------------------------//

	// Plots to include

	std::vector<TString> PlotNames; std::vector< double> Min; std::vector<double> Max;  std::vector<int> NBins;

	PlotNames.push_back("selected"); Min.push_back(-0.5); Max.push_back(1.5); NBins.push_back(2);
	PlotNames.push_back("n_tracks"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);	
	PlotNames.push_back("n_showers"); Min.push_back(-0.5); Max.push_back(5.5); NBins.push_back(6);
	PlotNames.push_back("reco_nu_vtx_sce_x"); Min.push_back(0.); Max.push_back(250.); NBins.push_back(50);
	PlotNames.push_back("reco_nu_vtx_sce_y"); Min.push_back(-110); Max.push_back(110); NBins.push_back(50);	
	PlotNames.push_back("reco_nu_vtx_sce_z"); Min.push_back(0.); Max.push_back(1050); NBins.push_back(50);
	PlotNames.push_back("hits_u"); Min.push_back(0); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_v"); Min.push_back(0); Max.push_back(1000); NBins.push_back(50);
	PlotNames.push_back("hits_y"); Min.push_back(0); Max.push_back(1000); NBins.push_back(50);	
	PlotNames.push_back("topological_score"); Min.push_back(0.5); Max.push_back(1.); NBins.push_back(25);				
	PlotNames.push_back("nslice"); Min.push_back(0.5); Max.push_back(1.5); NBins.push_back(1);
	PlotNames.push_back("nu_flashmatch_score"); Min.push_back(0.); Max.push_back(50.); NBins.push_back(50);
	PlotNames.push_back("trk_score_v"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(50);		
	PlotNames.push_back("pfpdg"); Min.push_back(10.5); Max.push_back(13.5); NBins.push_back(3);
	PlotNames.push_back("trk_llr_pid_score_v"); Min.push_back(0.); Max.push_back(1.); NBins.push_back(100);
	PlotNames.push_back("pfp_generation_v"); Min.push_back(1.5); Max.push_back(4.5); NBins.push_back(3);
	PlotNames.push_back("cos(trk_theta_v)"); Min.push_back(-1.); Max.push_back(1.); NBins.push_back(20);	

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

			TLegend* leg = new TLegend(0.2,0.89,0.9,0.99);
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
