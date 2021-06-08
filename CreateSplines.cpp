#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TString.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLine.h>
#include <TLatex.h>
#include <TF1.h>
#include <TGraphErrors.h>

#include <iostream>
#include <vector>
#include <iomanip>      // std::setprecision

#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/Constants.h"

using namespace std;
using namespace Constants;

void ReturnGraph(TFile* OutputFile, TTree* tree, TString qualifier, TString XVar, bool StorePlots) {

	// --------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);

	// --------------------------------------------------------------------------------------------------

	TString Run = "";

	if (string(OutputFile->GetName()).find("Run1") != std::string::npos) { Run = "Run1"; }
	if (string(OutputFile->GetName()).find("Run2") != std::string::npos) { Run = "Run2"; }
	if (string(OutputFile->GetName()).find("Run3") != std::string::npos) { Run = "Run3"; }
	if (string(OutputFile->GetName()).find("Run4") != std::string::npos) { Run = "Run4"; }
	if (string(OutputFile->GetName()).find("Run5") != std::string::npos) { Run = "Run5"; }

	// --------------------------------------------------------------------------------------------------

	double XminReso = -30.; double XmaxReso = 30.; int NBins = 40;

	TString AxisLabel = ""; TString Reso = ""; int NBinsReso = 10;
	double Xmin = -999.; double Xmax = -999.; TString XVarLabel = "";

	// --------------------------------------------------------------------------------------------------

	if (XVar == "CandidateP_P_Range") { 

		AxisLabel = ";P_{p} Range resolution [%];# Events;"; Reso = "(CandidateP_P_Range-True_CandidateP_P)/True_CandidateP_P*100.";
		Xmin = ArrayNBinsProtonMomentum[0]; Xmax = ArrayNBinsProtonMomentum[NBinsProtonMomentum]; XVarLabel = "P_{p} Range [GeV/c]";

	}

	if (XVar == "CandidateMu_P_Range") { 

		NBinsReso = 7;
		AxisLabel = ";P_{#mu} Range resolution [%];# Events;"; Reso = "(CandidateMu_P_Range-True_CandidateMu_P)/True_CandidateMu_P*100.";
		Xmin = ArrayNBinsMuonMomentum[0]; Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum]; XVarLabel = "P_{#mu} Range [GeV/c]";

	}

	if (XVar == "CandidateMu_P_MCS") { 

		XminReso = -70.; XmaxReso = 70.;
		AxisLabel = ";P_{#mu} MCS resolution [%];# Events;"; Reso = "(CandidateMu_P_MCS-True_CandidateMu_P)/True_CandidateMu_P*100.";
		Xmin = MuMinSumHitsValue; Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum]; XVarLabel = "P_{#mu} MCS [GeV/c]";

	}

	if (XVar == "Reco_DeltaAlphaT") { 

		XminReso = -100.; XmaxReso = 100.;
		NBinsReso = 7;
		AxisLabel = ";#delta#alpha_{T} resolution [%];# Events;"; Reso = "(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.";
		Xmin = ArrayNBinsDeltaAlphaT[0]; Xmax = ArrayNBinsDeltaAlphaT[NBinsDeltaAlphaT]; XVarLabel = "#delta#alpha_{T} [deg]";

	}

	if (XVar == "Reco_DeltaPhiT") { 

		XminReso = -70.; XmaxReso = 70.;
		NBinsReso = 7;
		AxisLabel = ";#delta#phi_{T} resolution [%];# Events;"; Reso = "(Reco_DeltaPhiT-True_DeltaPhiT)/True_DeltaPhiT*100.";
		Xmin = ArrayNBinsDeltaPhiT[0]; Xmax = ArrayNBinsDeltaPhiT[NBinsDeltaPhiT]; XVarLabel = "#delta#phi_{T} [deg]";

	}

	if (XVar == "Reco_Pt") { 

		XminReso = -60.; XmaxReso = 60.;
		NBinsReso = 6;
		AxisLabel = ";#delta p_{T} resolution [%];# Events;"; Reso = "(Reco_Pt-True_Pt)/True_Pt*100.";
		Xmin = ArrayNBinsDeltaPT[0]; Xmax = ArrayNBinsDeltaPT[NBinsDeltaPT]; XVarLabel = "#delta p_{T} [GeV/c]";

	}

	// --------------------------------------------------------------------------------------------------

	double Step = (Xmax -Xmin) / NBinsReso;

	double BinArray[NBinsReso]; memset( BinArray, 0, NBinsReso * sizeof(double) );
	double BinArrayError[NBinsReso]; memset( BinArrayError, 0, NBinsReso * sizeof(double) );
	double MeanArray[NBinsReso]; memset( MeanArray, 0, NBinsReso * sizeof(double) );
	double CaliMeanArray[NBinsReso]; memset( CaliMeanArray, 0, NBinsReso * sizeof(double) );
	double SigmaArray[NBinsReso]; memset( SigmaArray, 0, NBinsReso * sizeof(double) );
	double MeanErrorArray[NBinsReso]; memset( MeanErrorArray, 0, NBinsReso * sizeof(double) );
	double SigmaErrorArray[NBinsReso]; memset( SigmaErrorArray, 0, NBinsReso * sizeof(double) );

	TH1D* PlaygroundPlots[NBinsReso];

	if (XVar == "CandidateMu_P_Range") { qualifier = qualifier + " && CandidateMu_EndContainment == 1"; }
	if (XVar == "CandidateMu_P_MCS") { qualifier = qualifier + " && CandidateMu_EndContainment == 0"; }

	for (int i = 0; i < NBinsReso; i++) {

		TString PlotName = XVar+"_PlaygroundPlot_"+TString(std::to_string(i));
		PlaygroundPlots[i] = new TH1D(PlotName,AxisLabel,NBins,XminReso,XmaxReso);

		TString LowThres = TString(std::to_string(Xmin + i * Step ) );
		TString LowCut  = XVar + " > " + LowThres ;
		TString HighThres = TString(std::to_string(Xmin + (i+1) * Step ));
		TString HighCut  = XVar + " < " + HighThres ;

		tree->Draw(Reso+">>"+PlotName,qualifier + " && " + LowCut + " && " + HighCut,"goff");

		TF1* f = new TF1("f","gaus",-20,20);
		PlaygroundPlots[i]->Fit(f,"RQ0");

		double mean = f->GetParameter(1);
		double sigma = f->GetParameter(2);
		double meanError = f->GetParError(1);
		double sigmaError = f->GetParError(2);

		if (StorePlots) {

			TString CanvasName = TString(std::to_string(i+1))+"_"+XVar+"_OverlayCanvas"+Run;
			TCanvas* OverlayCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);

			TLegend* leg = new TLegend(0.15,0.91,0.4,0.98);
			leg->SetTextSize(0.04);
			leg->SetTextFont(132);
			leg->SetBorderSize(0);

			PlaygroundPlots[i]->SetLineColor(kBlue);
			PlaygroundPlots[i]->SetMarkerColor(kBlue);
			PlaygroundPlots[i]->SetMarkerStyle(20);
			PlaygroundPlots[i]->SetMarkerSize(2.);
			PlaygroundPlots[i]->SetLineWidth(3);
			PlaygroundPlots[i]->Draw("p0 same");

			leg->AddEntry(PlaygroundPlots[i],LowThres + " < " + XVarLabel + " < " + HighThres + ", #mu = " + TString(std::to_string(mean)) + ", #sigma = " + TString(std::to_string(sigma)),"p");

			leg->Draw();

			OverlayCanvas->SaveAs(PlotPath+XVar+"_Between_" + TString(std::to_string(i)) + "_" + TString(std::to_string(i+1)) + "_" + Run+".pdf");
			delete OverlayCanvas;

		}

		BinArray[i] = Xmin + (i+0.5) * Step;
		BinArrayError[i] = 0.5 * Step;
		MeanArray[i] = mean;
		SigmaArray[i] = sigma;
		MeanErrorArray[i] = meanError;
		SigmaErrorArray[i] = sigmaError;

	}

	TGraphErrors* graphMean = new TGraphErrors(NBinsReso,BinArray,MeanArray,BinArrayError,MeanErrorArray);
	graphMean->GetXaxis()->SetTitle(XVarLabel);
	graphMean->GetYaxis()->SetTitle("Mean Value [%]");
	graphMean->SetTitle("");
	OutputFile->cd();
	graphMean->Write("Mean_"+XVar);

	if (StorePlots) {

		TString MeanCanvasName = XVar+"_MeanOverlayCanvas"+Run;
		TCanvas* MeanOverlayCanvas = new TCanvas(MeanCanvasName,MeanCanvasName,205,34,1024,768);

		MeanOverlayCanvas->cd();
		graphMean->SetLineColor(kBlack);
		graphMean->SetMarkerColor(kBlack);
		graphMean->SetMarkerStyle(20);
		graphMean->SetMarkerSize(2.);
		graphMean->SetLineWidth(3);
		graphMean->Draw("ap0");

		MeanOverlayCanvas->SaveAs(PlotPath+"Mean_"+XVar+Run+".pdf");
		delete MeanOverlayCanvas;

	}

	TGraphErrors* graphSigma = new TGraphErrors(NBinsReso,BinArray,SigmaArray,BinArrayError,SigmaErrorArray);
	graphSigma->GetXaxis()->SetTitle(XVarLabel);
	graphSigma->GetYaxis()->SetTitle("#sigma Value [%]");
	graphSigma->SetTitle("");
	OutputFile->cd();
	graphSigma->Write("Sigma_"+XVar);

	if (StorePlots) {

		TString SigmaCanvasName = XVar+"_SigmaOverlayCanvas"+Run;
		TCanvas* SigmaOverlayCanvas = new TCanvas(SigmaCanvasName,SigmaCanvasName,205,34,1024,768);

		SigmaOverlayCanvas->cd();
		graphSigma->SetLineColor(kBlack);
		graphSigma->SetMarkerColor(kBlack);
		graphSigma->SetMarkerStyle(20);
		graphSigma->SetMarkerSize(2.);
		graphSigma->SetLineWidth(3);
		graphSigma->Draw("ap0");

		SigmaOverlayCanvas->SaveAs(PlotPath+"Sigma_"+XVar+Run+".pdf");
		delete SigmaOverlayCanvas;

	}

}


void CreateSplines(TString Sample, bool StorePlots = false) {

	// -----------------------------------------------------------------------------------------------------------------------------------------

	TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_"+Sample+"_"+UBCodeVersion+".root","readonly");
	TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

	// ---------------------------------------------------------------------------------------------------------------------------------------

	TString FileName = "/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/Splines_"+Sample+"_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

	// ---------------------------------------------------------------------------------------------------------------------------------------

	ReturnGraph(OutputFile,tree,qualifier,"CandidateP_P_Range",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"CandidateMu_P_Range",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"CandidateMu_P_MCS",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"Reco_DeltaAlphaT",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"Reco_Pt",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"Reco_DeltaPhiT",StorePlots);

	// ---------------------------------------------------------------------------------------------------------------------------------------

	OutputFile->Close();

	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;

	// ---------------------------------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------------------------------------

} // End of the program 
