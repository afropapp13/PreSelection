#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLine.h>
#include <TLatex.h>

#include <iostream>
#include <vector>
#include <iomanip>      // std::setprecision

#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/Constants.h"

using namespace std;
using namespace Constants;

void ResoStudy() {

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetTitleSize(0.0,"t");
	gStyle->SetTitleFont(132,"t");

	gStyle->SetTitleOffset(0.9,"x");
	gStyle->SetTitleOffset(1.,"y");
	gStyle->SetTitleSize(0.05,"xyz");
	gStyle->SetTitleFont(132,"xyz");
	gStyle->SetLabelSize(0.05,"xyz");
	gStyle->SetLabelFont(132,"xyz");
	gStyle->SetNdivisions(10,"xyz");

	gStyle->SetOptStat(0);

	gROOT->ForceStyle();

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<TString> Runs{"Run1"};
//	std::vector<TString> Runs{"Run1","Run3"};
//	std::vector<TString> Runs{"Run1","Run2","Run3","Run4","Run5"};

	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

		TFile* OverlayTruthFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreTruthSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* treeTruth = (TTree*)(OverlayTruthFile->Get("myPreTruthSelection"));

		TFile* DataFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_BeamOn9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* treeData = (TTree*)(OverlayFile->Get("myPreSelection"));

		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);

		// ---------------------------------------------------------------------------------------------------------------------------------

//		double XminReso = -100.; double XmaxReso = 100.; int NBins = 20;
		double XminReso = -30.; double XmaxReso = 30.; int NBins = 40;

//		TString AxisLabel = ";#delta#alpha_{T} resolution [%];# Events;";
//		TString Reso = "(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.";

//		TString AxisLabel = ";P_{p} resolution [%];# Events;"; TString Reso = "(CandidateP_P_Range-True_CandidateP_P)/True_CandidateP_P*100."; const int NBinsReso = 10;
//		TString AxisLabel = ";P_{#mu} resolution [%];# Events;"; TString Reso = "(CandidateMu_P_Range-True_CandidateMu_P)/True_CandidateMu_P*100."; const int NBinsReso = 10;
//		TString AxisLabel = ";P_{#mu} resolution [%];# Events;"; TString Reso = "(CandidateMu_P_MCS-True_CandidateMu_P)/True_CandidateMu_P*100."; const int NBinsReso = 8;
		TString AxisLabel = ";P_{#mu} resolution [%];# Events;"; TString Reso = "(CandidateMu_P_MCS-True_CandidateMu_P)/True_CandidateMu_P*100."; const int NBinsReso = 1;

//		double Xmin = ArrayNBinsProtonMomentum[0]; double Xmax = ArrayNBinsProtonMomentum[NBinsProtonMomentum]; TString XVar = "CandidateP_P_Range"; TString XVarLabel = "P_{p}";
//		double Xmin = ArrayNBinsProtonCosTheta[0]; double Xmax = ArrayNBinsProtonCosTheta[NBinsProtonCosTheta]; TString XVar = "CandidateP_CosTheta"; TString XVarLabel = "cos#theta_{p}";
//		double Xmin = ArrayNBinsProtonPhi[0]; double Xmax = ArrayNBinsProtonPhi[NBinsProtonPhi]; TString XVar = "CandidateP_Phi"; TString XVarLabel = "#phi_{p}";
//		double Xmin = ArrayNBinsMuonCosTheta[0]; double Xmax = ArrayNBinsMuonCosTheta[NBinsMuonCosTheta]; TString XVar = "CandidateMu_CosTheta"; TString XVarLabel = "cos#theta_{#mu}";
//		double Xmin = ArrayNBinsMuonMomentum[0]; double Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum]; TString XVar = "CandidateMu_P_Range"; TString XVarLabel = "P_{#mu}";
//		double Xmin = ArrayNBinsMuonMomentum[0]; double Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum]; TString XVar = "CandidateMu_P_MCS"; TString XVarLabel = "P_{#mu}";
//		double Xmin = 0.25; double Xmax = 1.45; TString XVar = "CandidateMu_P_MCS"; TString XVarLabel = "P_{#mu}";
		double Xmin = 1.45; double Xmax = 1.7; TString XVar = "CandidateMu_P_MCS"; TString XVarLabel = "P_{#mu}";
//		double Xmin = ArrayNBinsMuonPhi[0]; double Xmax = ArrayNBinsMuonPhi[NBinsMuonPhi]; TString XVar = "CandidateMu_Phi"; TString XVarLabel = "#phi_{#mu}";

		double Step = (Xmax -Xmin) / NBinsReso;

		double BinArray[NBinsReso] = {0};
		double MeanArray[NBinsReso] = {0};
		double SigmaArray[NBinsReso] = {0};

		// ---------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlots[NBinsReso];

		if (XVar == "CandidateMu_P_Range") { qualifier = qualifier + " && CandidateMu_EndContainment == 1"; }
		if (XVar == "CandidateMu_P_MCS") { qualifier = qualifier + " && CandidateMu_EndContainment == 0 && CandidateMu_Length > 50"; }

		for (int i = 0; i < NBinsReso; i++) {

			TLegend* leg = new TLegend(0.15,0.91,0.4,0.98);
			leg->SetTextSize(0.04);
			leg->SetTextFont(132);
			leg->SetBorderSize(0);

			TString CanvasName = TString(std::to_string(i+1))+"_"+XVar+"_OverlayCanvas"+Runs[WhichRun];
			TCanvas* OverlayCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);

			TString PlotName = XVar+"_PlaygroundPlot_"+TString(std::to_string(i));
			PlaygroundPlots[i] = new TH1D(PlotName,AxisLabel,NBins,XminReso,XmaxReso);

			TString LowThres = TString(std::to_string(Xmin + i * Step ) );
			TString LowCut  = XVar + " > " + LowThres ;

			TString HighThres = TString(std::to_string(Xmin + (i+1) * Step ));
			TString HighCut  = XVar + " < " + HighThres ;

			tree->Draw(Reso+">>"+PlotName,qualifier + " && " + LowCut + " && " + HighCut,"goff");

			PlaygroundPlots[i]->SetLineColor(kBlue);
			PlaygroundPlots[i]->SetMarkerColor(kBlue);
			PlaygroundPlots[i]->SetMarkerStyle(20);
			PlaygroundPlots[i]->SetMarkerSize(2.);
			PlaygroundPlots[i]->SetLineWidth(3);
			PlaygroundPlots[i]->Draw("p0 same");

			double NEvents = PlaygroundPlots[i]->Integral();
			cout << i+1 << " slice events = " << NEvents << endl;

			TF1* f = new TF1("f","gaus",-20,20);
			PlaygroundPlots[i]->Fit(f,"RQ0");

			double mean = f->GetParameter(1);
			double sigma = f->GetParameter(2);

			leg->AddEntry(PlaygroundPlots[i],LowThres + " < " + XVarLabel + " < " + HighThres + ", #mu = " + TString(std::to_string(mean)) + ", #sigma = " + TString(std::to_string(sigma)),"p");

			BinArray[i] = Xmin + (i+0.5) * Step;
			MeanArray[i] = mean;
			SigmaArray[i] = sigma;

			leg->Draw();

		}

		// ---------------------------------------------------------------------------------------------------------------------------------------

		TString MeanCanvasName = XVar+"_Mean_OverlayCanvas"+Runs[WhichRun];
		TCanvas* MeanOverlayCanvas = new TCanvas(MeanCanvasName,MeanCanvasName,205,34,1024,768);
		TGraph* graphMean = new TGraph(NBinsReso,BinArray,MeanArray);

		graphMean->GetXaxis()->SetTitle(XVarLabel);
		graphMean->GetYaxis()->SetTitle("Mean Value [%]");
		graphMean->SetTitle("");

		graphMean->SetMarkerSize(2.);
		graphMean->SetMarkerStyle(20);
		graphMean->SetLineWidth(3);
		graphMean->SetMarkerColor(kBlack);
		graphMean->SetLineColor(kBlack);
		graphMean->Draw("ap0 same");

		// ---------------------------------------------------------------------------------------------------------------------------------------

		TString SigmaCanvasName = XVar+"_Sigma_OverlayCanvas"+Runs[WhichRun];
		TCanvas* SigmaOverlayCanvas = new TCanvas(SigmaCanvasName,SigmaCanvasName,205,34,1024,768);
		TGraph* graphSigma = new TGraph(NBinsReso,BinArray,SigmaArray);

		graphSigma->GetXaxis()->SetTitle(XVarLabel);
		graphSigma->GetYaxis()->SetTitle("#sigma Value [%]");
		graphSigma->SetMinimum(0);
		graphSigma->SetTitle("");

		graphSigma->SetMarkerSize(2.);
		graphSigma->SetMarkerStyle(20);
		graphSigma->SetLineWidth(3);
		graphSigma->SetMarkerColor(kBlack);
		graphSigma->SetLineColor(kBlack);
		graphSigma->Draw("ap0 same");

		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
