#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLine.h>
#include <TLatex.h>
#include <TPaletteAxis.h>

#include <iostream>
#include <vector>

#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/Constants.h"

using namespace std;
using namespace Constants;

//----------------------------------------//

void RecoProjectSlice(TTree* tData,TTree* tGENIE,TTree* tNuWro,TString XVar,int Xbins,double Xmin, double Xmax,TString YVar,TString Ymin, TString Ymax) {

	TH1D* hData = new TH1D("h"+XVar+"Data"+YVar+"_"+Ymin+"_"+Ymax,";"+XVar+";POT Norm Events",Xbins,Xmin,Xmax);
	hData->SetLineColor(kBlack);
	hData->SetLineWidth(2);

	TH1D* hGENIE = new TH1D("h"+XVar+"GENIE"+YVar+"_"+Ymin+"_"+Ymax,";"+XVar+";POT Norm Events",Xbins,Xmin,Xmax);
	hGENIE->SetLineColor(kGreen+2);
	hGENIE->SetLineWidth(2);

	TH1D* hNuWro = new TH1D("h"+XVar+"NuWro"+YVar+"_"+Ymin+"_"+Ymax,";"+XVar+";POT Norm Events",Xbins,Xmin,Xmax);	
	hNuWro->SetLineColor(kOrange+7);
	hNuWro->SetLineWidth(2);

	tData->Draw(XVar+">>h"+XVar+"Data"+YVar+"_"+Ymin+"_"+Ymax,"("+qualifierData + " && " + YVar + ">" + Ymin + " && " + YVar + "<" + Ymax +")","goff");
	tGENIE->Draw(XVar+">>h"+XVar+"GENIE"+YVar+"_"+Ymin+"_"+Ymax,"("+qualifierData + " && " + YVar + ">" + Ymin + " && " + YVar + "<" + Ymax +")* POTWeight * Weight * T2KWeight * ROOTinoWeight","goff");
	tNuWro->Draw(XVar+">>h"+XVar+"NuWro"+YVar+"_"+Ymin+"_"+Ymax,"("+qualifierData + " && " + YVar + ">" + Ymin + " && " + YVar + "<" + Ymax +")* POTWeight","goff");	

	TString CanvasName = "cSlice"+XVar+YVar+"_"+Ymin+"_"+Ymax;
	TCanvas* c = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
	c->SetRightMargin(0.1);
	c->SetLeftMargin(0.15);	
	c->cd();

	hData->GetYaxis()->SetRangeUser(0.,1.15* TMath::Max(hGENIE->GetMaximum(), hData->GetMaximum()) );
	hData->GetYaxis()->SetTitleOffset(1.15);
	hData->Draw("same e");	

	hGENIE->Draw("same e");

	hNuWro->Draw("same e");	

	TLegend* leg = new TLegend(0.15,0.91,0.45,0.98);
	leg->SetBorderSize(0);
	leg->SetTextFont(FontStyle);
	leg->SetNColumns(2);
	leg->SetMargin(0.13);

	leg->AddEntry(hData,"Data","lep");
	leg->AddEntry(hGENIE,"GENIE","lep");
	leg->AddEntry(hNuWro,"NuWro","lep");		

	leg->Draw();

	TLegend* legTex = new TLegend(0.46,0.91,0.66,0.98);
	legTex->SetBorderSize(0);
	legTex->SetTextFont(FontStyle);
	legTex->SetTextSize(0.04);	
	legTex->SetNColumns(2);
	legTex->SetMargin(0.13);

	legTex->AddEntry(hGENIE,Ymin + " < " + YVar + " < " + Ymax,"");		
	legTex->Draw();	

}

//----------------------------------------//

void ProjectSlice(TTree* tGENIE,TTree* tNuWro,TString XVar,int Xbins,double Xmin, double Xmax,TString YVar,TString Ymin, TString Ymax) {

	TH1D* hGENIE = new TH1D("h"+XVar+"GENIE"+YVar+"_"+Ymin+"_"+Ymax,";"+XVar+";POT Norm Events",Xbins,Xmin,Xmax);
	hGENIE->SetLineColor(kBlack);
	hGENIE->SetLineWidth(2);

	TH1D* hNuWro = new TH1D("h"+XVar+"NuWro"+YVar+"_"+Ymin+"_"+Ymax,";"+XVar+";POT Norm Events",Xbins,Xmin,Xmax);	
	hNuWro->SetLineColor(kOrange+7);
	hNuWro->SetLineWidth(2);

	tGENIE->Draw(XVar+">>h"+XVar+"GENIE"+YVar+"_"+Ymin+"_"+Ymax,"("+qualifier + " && " + YVar + ">" + Ymin + " && " + YVar + "<" + Ymax +")* POTWeight * Weight * T2KWeight * ROOTinoWeight","goff");
	tNuWro->Draw(XVar+">>h"+XVar+"NuWro"+YVar+"_"+Ymin+"_"+Ymax,"("+qualifier + " && " + YVar + ">" + Ymin + " && " + YVar + "<" + Ymax +")* POTWeight","goff");	

	TString CanvasName = "cSlice"+XVar+YVar+"_"+Ymin+"_"+Ymax;
	TCanvas* c = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
	c->SetRightMargin(0.1);
	c->SetLeftMargin(0.15);	
	c->cd();

	hGENIE->GetYaxis()->SetRangeUser(0.,1.15* TMath::Max(hGENIE->GetMaximum(), hNuWro->GetMaximum()) );
	hGENIE->GetYaxis()->SetTitleOffset(1.15);
	hGENIE->Draw("same");

	hNuWro->Draw("same");	

	TLegend* leg = new TLegend(0.15,0.91,0.45,0.98);
	leg->SetBorderSize(0);
	leg->SetTextFont(FontStyle);
	leg->SetNColumns(2);
	leg->SetMargin(0.13);

	leg->AddEntry(hGENIE,"GENIE","l");
	leg->AddEntry(hNuWro,"NuWro","l");		

	leg->Draw();

	TLegend* legTex = new TLegend(0.46,0.91,0.66,0.98);
	legTex->SetBorderSize(0);
	legTex->SetTextFont(FontStyle);
	legTex->SetTextSize(0.04);	
	legTex->SetNColumns(2);
	legTex->SetMargin(0.13);

	legTex->AddEntry(hGENIE,Ymin + " < " + YVar + " < " + Ymax,"");		
	legTex->Draw();	

}

//----------------------------------------//

void TruthProjectSlice(TTree* tGENIE,TTree* tNuWro,TString XVar,int Xbins,double Xmin, double Xmax,TString YVar,TString Ymin, TString Ymax) {

	TH1D* hGENIE = new TH1D("h"+XVar+"GENIE"+YVar+"_"+Ymin+"_"+Ymax,";"+XVar+";POT Norm Events",Xbins,Xmin,Xmax);
	hGENIE->SetLineColor(kBlack);
	hGENIE->SetLineWidth(2);

	TH1D* hNuWro = new TH1D("h"+XVar+"NuWro"+YVar+"_"+Ymin+"_"+Ymax,";"+XVar+";POT Norm Events",Xbins,Xmin,Xmax);	
	hNuWro->SetLineColor(kOrange+7);
	hNuWro->SetLineWidth(2);

//	tGENIE->Draw(XVar+">>h"+XVar+"GENIE"+YVar+"_"+Ymin+"_"+Ymax,"("+TrueCC1p + " && " + YVar + ">" + Ymin + " && " + YVar + "<" + Ymax +")* POTWeight * Weight * T2KWeight * ROOTinoWeight","goff");
//	tNuWro->Draw(XVar+">>h"+XVar+"NuWro"+YVar+"_"+Ymin+"_"+Ymax,"("+TrueCC1p + " && " + YVar + ">" + Ymin + " && " + YVar + "<" + Ymax +")* POTWeight","goff");	
	
	tGENIE->Draw(XVar+">>h"+XVar+"GENIE"+YVar+"_"+Ymin+"_"+Ymax,"("+TrueCC1p + " && " + YVar + ">" + Ymin + " && " + YVar + "<" + Ymax +" && T2KWeight > 0 && T2KWeight < 30)* POTWeight * Weight * ROOTinoWeight","goff");
	tNuWro->Draw(XVar+">>h"+XVar+"NuWro"+YVar+"_"+Ymin+"_"+Ymax,"("+TrueCC1p + " && " + YVar + ">" + Ymin + " && " + YVar + "<" + Ymax +")* POTWeight","goff");	

	TString CanvasName = "cSlice"+XVar+YVar+"_"+Ymin+"_"+Ymax;
	TCanvas* c = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
	c->SetRightMargin(0.1);
	c->SetLeftMargin(0.15);	
	c->cd();

	hGENIE->GetYaxis()->SetRangeUser(0.,1.15* TMath::Max(hGENIE->GetMaximum(), hNuWro->GetMaximum()) );
	hGENIE->GetYaxis()->SetTitleOffset(1.15);
	hGENIE->Draw("same");

	hNuWro->Draw("same");	

	TLegend* leg = new TLegend(0.15,0.91,0.45,0.98);
	leg->SetBorderSize(0);
	leg->SetTextFont(FontStyle);
	leg->SetNColumns(2);
	leg->SetMargin(0.13);

	leg->AddEntry(hGENIE,"GENIE","l");
	leg->AddEntry(hNuWro,"NuWro","l");		

	leg->Draw();

	TLegend* legTex = new TLegend(0.46,0.91,0.66,0.98);
	legTex->SetBorderSize(0);
	legTex->SetTextFont(FontStyle);
	legTex->SetTextSize(0.04);	
	legTex->SetNColumns(2);
	legTex->SetMargin(0.13);

	legTex->AddEntry(hGENIE,Ymin + " < " + YVar + " < " + Ymax,"");		
	legTex->Draw();	

}

//----------------------------------------//

void Plot2D(TString Label,TTree* t,TString XVar,int Xbins,double Xmin, double Xmax,TString YVar,int Ybins,double Ymin, double Ymax, TString weight) {

	TH2D* h = new TH2D("h"+XVar+YVar+Label,";"+XVar+";"+YVar,Xbins,Xmin,Xmax,Ybins,Ymin,Ymax);

	t->Draw(YVar+":"+XVar+">>h"+XVar+YVar+Label,"("+qualifier+")*" + weight,"goff");

	TCanvas* c = new TCanvas("c"+Label+XVar+YVar,"c"+Label+XVar+YVar,205,34,1024,768);
	c->SetRightMargin(0.15);
	c->cd();
	h->SetTitle(Label);
	h->GetZaxis()->SetTitle("POT Norm Events");	
	h->Draw("coltz");	

}

//----------------------------------------//

void Playground_GENIENuWro_2D() {

	//----------------------------------------//

	const Int_t NCont = 999;	
	gStyle->SetPalette(55); 
	gStyle->SetNumberContours(NCont); 	

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

	//----------------------------------------//

	std::vector<TString> Runs{"Combined"};
	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		//----------------------------------------//

		TFile* DataFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreSelection_BeamOn9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* DataTree = (TTree*)(DataFile->Get("myPreSelection"));

		TFile* GENIEFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* GENIETree = (TTree*)(GENIEFile->Get("myPreSelection"));

		TFile* TruthGENIEFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreTruthSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* TruthGENIETree = (TTree*)(TruthGENIEFile->Get("myPreTruthSelection"));		

		TFile* NuWroFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9NuWro_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* NuWroTree = (TTree*)(NuWroFile->Get("myPreSelection"));

		TFile* TruthNuWroFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreTruthSelection_Overlay9NuWro_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* TruthNuWroTree = (TTree*)(TruthNuWroFile->Get("myPreTruthSelection"));		

		//----------------------------------------//

//		Plot2D("GENIE",GENIETree,"True_CandidateMu_CosTheta",20,-1.,1.,"True_DeltaAlphaT",20,0.,180.,"POTWeight * Weight * T2KWeight * ROOTinoWeight");
//		Plot2D("NuWro",NuWroTree,"True_CandidateMu_CosTheta",20,-1.,1.,"True_DeltaAlphaT",20,0.,180.,"POTWeight");

//		Plot2D("GENIE",GENIETree,"True_CandidateP_CosTheta",20,-1.,1.,"True_DeltaAlphaT",20,0.,180.,"POTWeight * Weight * T2KWeight * ROOTinoWeight");
//		Plot2D("NuWro",NuWroTree,"True_CandidateP_CosTheta",20,-1.,1.,"True_DeltaAlphaT",20,0.,180.,"POTWeight");

//		Plot2D("GENIE",GENIETree,"True_CandidateMu_P",20,0.1,1.2,"True_DeltaAlphaT",20,0.,180.,"POTWeight * Weight * T2KWeight * ROOTinoWeight");
//		Plot2D("NuWro",NuWroTree,"True_CandidateMu_P",20,0.1,1.2,"True_DeltaAlphaT",20,0.,180.,"POTWeight");

//		Plot2D("GENIE",GENIETree,"True_CandidateP_P",20,0.3,1.,"True_DeltaAlphaT",20,0.,180.,"POTWeight * Weight * T2KWeight * ROOTinoWeight");
//		Plot2D("NuWro",NuWroTree,"True_CandidateP_P",20,0.3,1.,"True_DeltaAlphaT",20,0.,180.,"POTWeight");

		//----------------------------------------//

//		ProjectSlice(GENIETree,NuWroTree,"True_DeltaAlphaT",20,0.,180.,"True_CandidateMu_CosTheta","-1.","0.7");
//		ProjectSlice(GENIETree,NuWroTree,"True_DeltaAlphaT",20,0.,180.,"True_CandidateMu_CosTheta","0.7","1.");	

//		ProjectSlice(GENIETree,NuWroTree,"True_DeltaAlphaT",20,0.,180.,"True_CandidateP_CosTheta","-1.","0.7");
//		ProjectSlice(GENIETree,NuWroTree,"True_DeltaAlphaT",20,0.,180.,"True_CandidateP_CosTheta","0.7","1.");

//		ProjectSlice(GENIETree,NuWroTree,"True_DeltaAlphaT",20,0.,180.,"True_CandidateMu_P","0.1","0.6");
//		ProjectSlice(GENIETree,NuWroTree,"True_DeltaAlphaT",20,0.,180.,"True_CandidateMu_P","0.6","1.2");	

//		ProjectSlice(GENIETree,NuWroTree,"True_DeltaAlphaT",20,0.,180.,"True_CandidateP_P","0.3","0.55");
//		ProjectSlice(GENIETree,NuWroTree,"True_DeltaAlphaT",20,0.,180.,"True_CandidateP_P","0.55","1.");									

//		RecoProjectSlice(DataTree,GENIETree,NuWroTree,"Reco_DeltaAlphaT",20,0.,180.,"CandidateP_P_Range","0.3","0.55");
//		RecoProjectSlice(DataTree,GENIETree,NuWroTree,"Reco_DeltaAlphaT",20,0.,180.,"CandidateP_P_Range","0.55","1.");

		TruthProjectSlice(TruthGENIETree,TruthNuWroTree,"True_DeltaAlphaT",20,0.,180.,"Proton_MCParticle_Mom","0.3","0.55");
		TruthProjectSlice(TruthGENIETree,TruthNuWroTree,"True_DeltaAlphaT",20,0.,180.,"Proton_MCParticle_Mom","0.55","1.");

		//----------------------------------------//

	} // End of the loop over the runs

} // End of the program 
