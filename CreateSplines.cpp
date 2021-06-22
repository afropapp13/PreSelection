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
#include <TGaxis.h>

#include <iostream>
#include <vector>
#include <iomanip>      // std::setprecision

#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/Constants.h"

using namespace std;
using namespace Constants;

//double round(double var,double n) {

//	std::cout << std::setprecision(2);
//	double value = (int)(var * TMath::Power(10.,n) + .5);
//	return (double)value / TMath::Power(10.,n);

//}

TString to_string_with_precision(double a_value, const int n = 3)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return TString(out.str());
}

void ReturnGraph(TFile* OutputFile, TTree* tree, TString qualifier, TString XVar, bool StorePlots) {

	// --------------------------------------------------------------------------------------------------

	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(4);

	// --------------------------------------------------------------------------------------------------

	TString Run = "";

	if (string(OutputFile->GetName()).find("Run1") != std::string::npos) { Run = "Run1"; }
	if (string(OutputFile->GetName()).find("Run2") != std::string::npos) { Run = "Run2"; }
	if (string(OutputFile->GetName()).find("Run3") != std::string::npos) { Run = "Run3"; }
	if (string(OutputFile->GetName()).find("Run4") != std::string::npos) { Run = "Run4"; }
	if (string(OutputFile->GetName()).find("Run5") != std::string::npos) { Run = "Run5"; }

	// --------------------------------------------------------------------------------------------------

	double XminReso = -30.; double XmaxReso = 30.; int NBins = 40;

	TString AxisLabel = ""; 
	int NBinsReso = 10;
	double Xmin = -999.; double Xmax = -999.; 
	TString Reso = ""; TString XVarLabel = ""; TString RecaliReso = ""; TString Units = "[%]";
	double FitMin = -20., FitMax = 20.;

	TString ResoAxisLabel = "";	
	TString ResoRatio = "";	
	double ResoFitMin = -10., ResoFitMax = 10.;
	double ResoRangeMin = -20., ResoRangeMax = 20.;

	// --------------------------------------------------------------------------------------------------

	if (XVar == "CandidateP_P_Range") { 

		FitMin = -0.1; FitMax = 0.1;
		XminReso = -0.4; XmaxReso = 0.4;
		NBinsReso = 8;
		ResoAxisLabel = ";P_{p} Range resolution [%];# Events;"; 
		ResoRatio = "(CandidateP_P_Range-True_CandidateP_P)/True_CandidateP_P*100.";
		// RecaliReso = "(CandidateP_P_Range_Recalibrate-True_CandidateP_P)/True_CandidateP_P*100.";
		AxisLabel = ";P_{p} Range Difference [GeV/c];# Events;"; 
		Reso = "(CandidateP_P_Range-True_CandidateP_P)";
		RecaliReso = "(CandidateP_P_Range_Recalibrate-True_CandidateP_P)";		
		Xmin = ArrayNBinsProtonMomentum[0]; Xmax = ArrayNBinsProtonMomentum[NBinsProtonMomentum]; 
		XVarLabel = "P_{p} Range [GeV/c]";
		Units = "[GeV/c]";

	}

	if (XVar == "CandidateP_Phi") { 

		FitMin = -8; FitMax = 8;
		XminReso = -15; XmaxReso = 15;
		NBinsReso = 8;
		// AxisLabel = ";#phi_{p} resolution [%];# Events;"; 
		// Reso = "(CandidateP_Phi-True_CandidateP_Phi)/True_CandidateP_Phi*100.";
		// RecaliReso = "(CandidateP_Phi_Recalibrate-True_CandidateP_Phi)/True_CandidateP_Phi*100.";
		AxisLabel = ";#phi_{p} Difference [deg];# Events;"; 
		Reso = "(CandidateP_Phi-True_CandidateP_Phi)";
		RecaliReso = "(CandidateP_Phi_Recalibrate-True_CandidateP_Phi)";		
		Xmin = ArrayNBinsProtonPhi[0]; Xmax = ArrayNBinsProtonPhi[NBinsProtonPhi]; 
		XVarLabel = "#phi_{p} [deg]";
		Units = "[deg]";		

	}

	if (XVar == "CandidateP_Theta") { 

		FitMin = -8; FitMax = 8;
		XminReso = -15; XmaxReso = 15;
		NBinsReso = 5;
		// AxisLabel = ";#theta_{p} resolution [%];# Events;"; 
		// Reso = "(CandidateP_Theta-True_CandidateP_Theta)/True_CandidateP_Theta*100.";
		// RecaliReso = "(CandidateP_Theta_Recalibrate-True_CandidateP_Theta)/True_CandidateP_Theta*100.";
		AxisLabel = ";#theta_{p} Difference [deg];# Events;"; 
		Reso = "(CandidateP_Theta-True_CandidateP_Theta)";
		RecaliReso = "(CandidateP_Theta_Recalibrate-True_CandidateP_Theta)";		
		Xmin = 0.; Xmax = 180.; XVarLabel = "#theta_{p} [deg]";
		Units = "[deg]";

	}

	if (XVar == "CandidateP_CosTheta") { 

		FitMin = -0.1; FitMax = 0.1;
		XminReso = -0.15; XmaxReso = 0.15;
		NBinsReso = 7;
		// AxisLabel = ";cos#theta_{p} resolution [%];# Events;"; 
		// Reso = "(CandidateP_CosTheta-True_CandidateP_CosTheta)/True_CandidateP_CosTheta*100.";
		// RecaliReso = "(CandidateP_CosTheta_Recalibrate-True_CandidateP_CosTheta)/True_CandidateP_CosTheta*100.";
		AxisLabel = ";cos#theta_{p} Difference;# Events;"; 
		Reso = "(CandidateP_CosTheta-True_CandidateP_CosTheta)";
		RecaliReso = "(CandidateP_CosTheta_Recalibrate-True_CandidateP_CosTheta)";	
		Xmin = ArrayNBinsProtonCosTheta[0]; Xmax = ArrayNBinsProtonCosTheta[NBinsProtonCosTheta]; 
		XVarLabel = "cos#theta_{p}";
		Units = "";

	}

	if (XVar == "CandidateMu_P_Range") { 

		FitMin = -0.1; FitMax = 0.1;
		XminReso = -0.4; XmaxReso = 0.4;
		NBinsReso = 6;
		ResoAxisLabel = ";P_{#mu} Range resolution [%];# Events;"; 
		ResoRatio = "(CandidateMu_P_Range-True_CandidateMu_P)/True_CandidateMu_P*100.";
		// RecaliReso = "(CandidateMu_P_Range_Recalibrate-True_CandidateMu_P)/True_CandidateMu_P*100.";
		AxisLabel = ";P_{#mu} Range Difference [GeV/c];# Events;"; 
		Reso = "(CandidateMu_P_Range-True_CandidateMu_P)";
		RecaliReso = "(CandidateMu_P_Range_Recalibrate-True_CandidateMu_P)";		
		Xmin = ArrayNBinsMuonMomentum[0]; Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum]; 
		XVarLabel = "P_{#mu} Range [GeV/c]";
		Units = "[GeV/c]";		

	}

	if (XVar == "CandidateMu_P_MCS") { 

		ResoFitMin = -40.; ResoFitMax = 40.;
		ResoRangeMin = -80.; ResoRangeMax = 80.;
		FitMin = -0.25; FitMax = 0.25;
		XminReso = -0.5; XmaxReso = 0.5;
		NBinsReso = 9;
		ResoAxisLabel = ";P_{#mu} MCS resolution [%];# Events;"; 
		ResoRatio = "(CandidateMu_P_MCS-True_CandidateMu_P)/True_CandidateMu_P*100.";
		// RecaliReso = "(CandidateMu_P_MCS_Recalibrate-True_CandidateMu_P)/True_CandidateMu_P*100.";
		AxisLabel = ";P_{#mu} MCS Difference [GeV/c];# Events;"; 
		Reso = "(CandidateMu_P_MCS-True_CandidateMu_P)";
		RecaliReso = "(CandidateMu_P_MCS_Recalibrate-True_CandidateMu_P)";		
		Xmin = 0.3; Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum]; 
		XVarLabel = "P_{#mu} MCS [GeV/c]";
		Units = "[GeV/c]";		

	}

	if (XVar == "CandidateMu_Phi") { 

		FitMin = -8; FitMax = 8;
		XminReso = -15; XmaxReso = 15;
		NBinsReso = 8;
		// AxisLabel = ";#phi_{#mu} resolution [%];# Events;"; 
		// Reso = "(CandidateMu_Phi-True_CandidateMu_Phi)/True_CandidateMu_Phi*100.";
		// RecaliReso = "(CandidateMu_Phi_Recalibrate-True_CandidateMu_Phi)/True_CandidateMu_Phi*100.";
		AxisLabel = ";#phi_{#mu} Difference [deg];# Events;"; 
		Reso = "(CandidateMu_Phi-True_CandidateMu_Phi)";
		RecaliReso = "(CandidateMu_Phi_Recalibrate-True_CandidateMu_Phi)";		
		Xmin = ArrayNBinsMuonPhi[0]; Xmax = ArrayNBinsMuonPhi[NBinsMuonPhi]; 
		XVarLabel = "#phi_{#mu} [deg]";
		Units = "[deg]";		

	}

	if (XVar == "CandidateMu_Theta") { 

		FitMin = -8; FitMax = 8;
		XminReso = -15; XmaxReso = 15;
		NBinsReso = 6;
		// AxisLabel = ";#theta_{#mu} resolution [%];# Events;"; 
		// Reso = "(CandidateMu_Theta-True_CandidateMu_Theta)/True_CandidateMu_Theta*100.";
		// RecaliReso = "(CandidateMu_Theta_Recalibrate-True_CandidateMu_Theta)/True_CandidateMu_Theta*100.";
		AxisLabel = ";#theta_{#mu} Difference [deg];# Events;"; 
		Reso = "(CandidateMu_Theta-True_CandidateMu_Theta)";
		RecaliReso = "(CandidateMu_Theta_Recalibrate-True_CandidateMu_Theta)";		
		Xmin = 0.; Xmax = 180.; XVarLabel = "#theta_{#mu} [deg]";
		Units = "[deg]";		

	}

	if (XVar == "CandidateMu_CosTheta") { 

		FitMin = -0.1; FitMax = 0.1;
		XminReso = -0.15; XmaxReso = 0.15;
		NBinsReso = 8;
		// AxisLabel = ";cos#theta_{#mu} resolution [%];# Events;"; 
		// Reso = "(CandidateMu_CosTheta-True_CandidateMu_CosTheta)/True_CandidateMu_CosTheta*100.";
		// RecaliReso = "(CandidateMu_CosTheta_Recalibrate-True_CandidateMu_CosTheta)/True_CandidateMu_CosTheta*100.";
		AxisLabel = ";cos#theta_{#mu} Difference;# Events;"; 
		Reso = "(CandidateMu_CosTheta-True_CandidateMu_CosTheta)";
		RecaliReso = "(CandidateMu_CosTheta_Recalibrate-True_CandidateMu_CosTheta)";		
		Xmin = ArrayNBinsMuonCosTheta[0]; Xmax = ArrayNBinsMuonCosTheta[NBinsMuonCosTheta]; 
		XVarLabel = "cos#theta_{#mu}";
		Units = "";		

	}

	if (XVar == "Reco_DeltaAlphaT") { 

		FitMin = -40; FitMax = 40;
		XminReso = -180; XmaxReso = 180;
		NBinsReso = 7;
		// AxisLabel = ";#delta#alpha_{T} resolution [%];# Events;"; 
		// Reso = "(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.";
		// RecaliReso = "(Reco_DeltaAlphaT_Recalibrate-True_DeltaAlphaT)/True_DeltaAlphaT*100.";
		AxisLabel = ";#delta#alpha_{T} Difference [deg];# Events;"; 
		Reso = "(Reco_DeltaAlphaT-True_DeltaAlphaT)";
		RecaliReso = "(Reco_DeltaAlphaT_Recalibrate-True_DeltaAlphaT)";
		Xmin = ArrayNBinsDeltaAlphaT[0]; Xmax = ArrayNBinsDeltaAlphaT[NBinsDeltaAlphaT]; 
		XVarLabel = "#delta#alpha_{T} [deg]";
		Units = "[deg]";		

	}

	if (XVar == "Reco_DeltaPhiT") { 

		FitMin = -15; FitMax = 15;
		XminReso = -30; XmaxReso = 30;
		NBinsReso = 7;
		// AxisLabel = ";#delta#phi_{T} resolution [%];# Events;"; 
		// Reso = "(Reco_DeltaPhiT-True_DeltaPhiT)/True_DeltaPhiT*100.";
		// RecaliReso = "(Reco_DeltaPhiT_Recalibrate-True_DeltaPhiT)/True_DeltaPhiT*100.";
		AxisLabel = ";#delta#phi_{T} Difference [deg];# Events;"; 
		Reso = "(Reco_DeltaPhiT-True_DeltaPhiT)";
		RecaliReso = "(Reco_DeltaPhiT_Recalibrate-True_DeltaPhiT)";		
		Xmin = ArrayNBinsDeltaPhiT[0]; Xmax = ArrayNBinsDeltaPhiT[NBinsDeltaPhiT]; 
		XVarLabel = "#delta#phi_{T} [deg]";
		Units = "[deg]";		

	}

	if (XVar == "Reco_Pt") { 

		FitMin = -0.15; FitMax = 0.15;
		XminReso = -0.3; XmaxReso = 0.3;
		NBinsReso = 6;
		// AxisLabel = ";#delta p_{T} resolution [%];# Events;"; 
		// Reso = "(Reco_Pt-True_Pt)/True_Pt*100.";
		// RecaliReso = "(Reco_Pt_Recalibrate-True_Pt)/True_Pt*100.";
		AxisLabel = ";#delta p_{T} Difference [GeV/c];# Events;"; 
		Reso = "(Reco_Pt-True_Pt)";
		RecaliReso = "(Reco_Pt_Recalibrate-True_Pt)";		
		Xmin = ArrayNBinsDeltaPT[0]; Xmax = ArrayNBinsDeltaPT[NBinsDeltaPT]; 
		XVarLabel = "#delta p_{T} [GeV/c]";
		Units = "[GeV/c]";		

	}

	// --------------------------------------------------------------------------------------------------

	double Step = (Xmax -Xmin) / NBinsReso;

	double BinArray[NBinsReso]; memset( BinArray, 0, NBinsReso * sizeof(double) );
	double BinArrayError[NBinsReso]; memset( BinArrayError, 0, NBinsReso * sizeof(double) );

	double MeanArray[NBinsReso]; memset( MeanArray, 0, NBinsReso * sizeof(double) );
	double SigmaArray[NBinsReso]; memset( SigmaArray, 0, NBinsReso * sizeof(double) );
	double MeanErrorArray[NBinsReso]; memset( MeanErrorArray, 0, NBinsReso * sizeof(double) );
	double SigmaErrorArray[NBinsReso]; memset( SigmaErrorArray, 0, NBinsReso * sizeof(double) );

	double ResoMeanArray[NBinsReso]; memset( ResoMeanArray, 0, NBinsReso * sizeof(double) );
	double ResoSigmaArray[NBinsReso]; memset( ResoSigmaArray, 0, NBinsReso * sizeof(double) );
	double ResoMeanErrorArray[NBinsReso]; memset( ResoMeanErrorArray, 0, NBinsReso * sizeof(double) );
	double ResoSigmaErrorArray[NBinsReso]; memset( ResoSigmaErrorArray, 0, NBinsReso * sizeof(double) );

	double RecaliMeanArray[NBinsReso]; memset( RecaliMeanArray, 0, NBinsReso * sizeof(double) );
	double RecaliSigmaArray[NBinsReso]; memset( RecaliSigmaArray, 0, NBinsReso * sizeof(double) );
	double RecaliMeanErrorArray[NBinsReso]; memset( RecaliMeanErrorArray, 0, NBinsReso * sizeof(double) );
	double RecaliSigmaErrorArray[NBinsReso]; memset( RecaliSigmaErrorArray, 0, NBinsReso * sizeof(double) );

//	double ResoRecaliMeanArray[NBinsReso]; memset( ResoRecaliMeanArray, 0, NBinsReso * sizeof(double) );
//	double ResoRecaliSigmaArray[NBinsReso]; memset( ResoRecaliSigmaArray, 0, NBinsReso * sizeof(double) );
//	double ResoRecaliMeanErrorArray[NBinsReso]; memset( ResoRecaliMeanErrorArray, 0, NBinsReso * sizeof(double) );
//	double ResoRecaliSigmaErrorArray[NBinsReso]; memset( ResoRecaliSigmaErrorArray, 0, NBinsReso * sizeof(double) );

	// --------------------------------------------------------------------------------------------------

	TH1D* PlaygroundPlots[NBinsReso];
	TH1D* RecaliPlaygroundPlots[NBinsReso];

	TH1D* ResoPlaygroundPlots[NBinsReso];
//	TH1D* ResoRecaliPlaygroundPlots[NBinsReso];

	if (XVar == "CandidateMu_P_Range") { qualifier = qualifier + " && CandidateMu_EndContainment == 1"; }
	if (XVar == "CandidateMu_P_MCS") { qualifier = qualifier + " && CandidateMu_EndContainment == 0"; }

	for (int i = 0; i < NBinsReso; i++) {

		TString PlotName = XVar+"_PlaygroundPlot_"+to_string_with_precision(i);
		PlaygroundPlots[i] = new TH1D(PlotName,AxisLabel,NBins,XminReso,XmaxReso);
		TString RecaliPlotName = XVar+"_RecaliPlaygroundPlot_"+to_string_with_precision(i);
		RecaliPlaygroundPlots[i] = new TH1D(RecaliPlotName,AxisLabel,NBins,XminReso,XmaxReso);

		TString ResoPlotName = XVar+"_ResoPlaygroundPlot_"+to_string_with_precision(i);
		ResoPlaygroundPlots[i] = new TH1D(ResoPlotName,ResoAxisLabel,NBins,ResoRangeMin,ResoRangeMax);
//		TString ResoRecaliPlotName = XVar+"_ResoRecaliPlaygroundPlot_"+to_string_with_precision(i);
//		ResoRecaliPlaygroundPlots[i] = new TH1D(ResoRecaliPlotName,ResoAxisLabel,NBins,ResoRangeMin,ResoRangeMax);

		TString LowThres = to_string_with_precision(Xmin + i * Step);
		TString LowCut  = XVar + " > " + LowThres ;
		TString HighThres = to_string_with_precision(Xmin + (i+1) * Step);
		TString HighCut  = XVar + " < " + HighThres ;

		tree->Draw(Reso+">>"+PlotName,qualifier + " && " + LowCut + " && " + HighCut,"goff");
		tree->Draw(RecaliReso+">>"+RecaliPlotName,qualifier + " && " + LowCut + " && " + HighCut,"goff");


		if (ResoAxisLabel != "") {

			tree->Draw(ResoRatio+">>"+ResoPlotName,qualifier + " && " + LowCut + " && " + HighCut,"goff");
	//		tree->Draw(RecaliResoRatio+">>"+ResoRecaliPlotName,qualifier + " && " + LowCut + " && " + HighCut,"goff");

		}

		// -----------------------------------------------------------------------------------------------------------

		// Fitting to a gaussian

		TF1* f = new TF1("f","gaus",FitMin,FitMax);
		PlaygroundPlots[i]->Fit(f,"RQ0");

		double mean = f->GetParameter(1);
		double sigma = f->GetParameter(2);
		double meanError = f->GetParError(1);
		double sigmaError = f->GetParError(2);

		double meanReso = -99.;
		double sigmaReso = -99.;
		double meanErrorReso = -99.;
		double sigmaErrorReso = -99.;
		TF1* fReso = new TF1("fReso","gaus",ResoFitMin,ResoFitMax);
		if (ResoAxisLabel != "") {
	
			ResoPlaygroundPlots[i]->Fit(fReso,"RQ0");

			meanReso = fReso->GetParameter(1);
			sigmaReso = fReso->GetParameter(2);
			meanErrorReso = fReso->GetParError(1);
			sigmaErrorReso = fReso->GetParError(2);

		}

		// if (TMath::Abs(mean) > 50) {

		// 	mean = PlaygroundPlots[i]->GetMean();
		// 	meanError = PlaygroundPlots[i]->GetMeanError();
		// 	sigma = PlaygroundPlots[i]->GetRMS();
		// 	sigmaError = PlaygroundPlots[i]->GetRMSError();

		// }

		TF1* fCali = new TF1("fCali","gaus",FitMin,FitMax);
		RecaliPlaygroundPlots[i]->Fit(fCali,"RQ0");

		double meanCali = fCali->GetParameter(1);
		double sigmaCali = fCali->GetParameter(2);
		double meanErrorCali = fCali->GetParError(1);
		double sigmaErrorCali = fCali->GetParError(2);

//		if (TMath::Abs(meanCali) > 50) {

//			meanCali = RecaliPlaygroundPlots[i]->GetMean();
//			meanErrorCali = RecaliPlaygroundPlots[i]->GetMeanError();
//			sigmaCali = RecaliPlaygroundPlots[i]->GetRMS();
//			sigmaErrorCali = RecaliPlaygroundPlots[i]->GetRMSError();

//		}

		// -----------------------------------------------------------------------------------------------------------

		if (StorePlots) {

			TString CanvasName = to_string_with_precision(i+1)+"_"+XVar+"_OverlayCanvas"+Run;
			TCanvas* OverlayCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
			OverlayCanvas->SetLeftMargin(0.1);

			TLegend* leg = new TLegend(0.3,0.91,0.4,0.98);
			leg->SetTextSize(0.04);
			leg->SetTextFont(132);
			leg->SetBorderSize(0);

			TLegend* legCali = new TLegend(0.55,0.82,0.7,0.89);
			legCali->SetTextSize(0.04);
			legCali->SetTextFont(132);
			legCali->SetBorderSize(0);

			PlaygroundPlots[i]->SetLineColor(kBlack);
			PlaygroundPlots[i]->SetMarkerColor(kBlack);
			PlaygroundPlots[i]->SetMarkerStyle(20);
			PlaygroundPlots[i]->SetMarkerSize(2.);
			PlaygroundPlots[i]->SetLineWidth(3);
			PlaygroundPlots[i]->GetYaxis()->SetTitleOffset(1.1);
			PlaygroundPlots[i]->Draw("p0 same");

			RecaliPlaygroundPlots[i]->SetLineColor(kOrange+7);
			RecaliPlaygroundPlots[i]->SetMarkerColor(kOrange+7);
			RecaliPlaygroundPlots[i]->SetMarkerStyle(20);
			RecaliPlaygroundPlots[i]->SetMarkerSize(2.);
			RecaliPlaygroundPlots[i]->SetLineWidth(3);
			RecaliPlaygroundPlots[i]->Draw("p0 same");

//			leg->AddEntry(PlaygroundPlots[i],LowThres + " < " + XVarLabel + " < " + HighThres + ", #mu = " + to_string_with_precision(mean) + ", #sigma = " + to_string_with_precision(sigma),"");
			leg->AddEntry(PlaygroundPlots[i],LowThres + " < " + XVarLabel + " < " + HighThres,"");
			leg->Draw();

			legCali->AddEntry(RecaliPlaygroundPlots[i],"Calibrated, #mu = " + to_string_with_precision(meanCali),"p");
			legCali->AddEntry(PlaygroundPlots[i],"Uncalibrated, #mu = " + to_string_with_precision(mean),"p");
			legCali->Draw();

			TLine* line = new TLine(0,0,0,1.05*PlaygroundPlots[i]->GetMaximum());
			line->SetLineColor(kBlack);
			line->SetLineStyle(kDashed);
			line->Draw();

			OverlayCanvas->SaveAs(PlotPath+XVar+"_Between_" + TString(std::to_string(i)) + "_" + TString(std::to_string(i+1)) + "_" + Run+".pdf");
			delete OverlayCanvas;

		}

		BinArray[i] = Xmin + (i+0.5) * Step;
		BinArrayError[i] = 0.5 * Step;

		MeanArray[i] = mean;
		SigmaArray[i] = sigma;
		MeanErrorArray[i] = meanError;
		SigmaErrorArray[i] = sigmaError;

		RecaliMeanArray[i] = meanCali;
		RecaliSigmaArray[i] = sigmaCali;
		RecaliMeanErrorArray[i] = meanErrorCali;
		RecaliSigmaErrorArray[i] = sigmaErrorCali;

		ResoMeanArray[i] = meanReso;
		ResoSigmaArray[i] = sigmaReso;
		ResoMeanErrorArray[i] = meanErrorReso;
		ResoSigmaErrorArray[i] = sigmaErrorReso;

//		ResoRecaliMeanArray[i] = meanCaliReso;
//		ResoRecaliSigmaArray[i] = sigmaCaliReso;
//		ResoRecaliMeanErrorArray[i] = meanErrorCaliReso;
//		ResoRecaliSigmaErrorArray[i] = sigmaErrorCaliReso;

	} // End of the loop over the slices

	// -------------------------------------------------------------------------------------------------------------

	TGraphErrors* graphMean = new TGraphErrors(NBinsReso,BinArray,MeanArray,BinArrayError,MeanErrorArray);
	graphMean->GetXaxis()->SetTitle("Reco " + XVarLabel);
	graphMean->GetYaxis()->SetTitle("Mean Value " + Units);
	graphMean->SetTitle("");
	OutputFile->cd();
	graphMean->Write("Mean_"+XVar);

	TGraphErrors* RecaligraphMean = new TGraphErrors(NBinsReso,BinArray,RecaliMeanArray,BinArrayError,RecaliMeanErrorArray);
	RecaligraphMean->GetXaxis()->SetTitle("Reco " + XVarLabel);
	RecaligraphMean->GetYaxis()->SetTitle("Mean Value " + Units);
	RecaligraphMean->SetTitle("");
	OutputFile->cd();
	RecaligraphMean->Write("RecaliMean_"+XVar);

	TGraphErrors* graphSigma = new TGraphErrors(NBinsReso,BinArray,SigmaArray,BinArrayError,SigmaErrorArray);
	graphSigma->GetXaxis()->SetTitle("Reco " + XVarLabel);
	graphSigma->GetYaxis()->SetTitle("#sigma Value " + Units);
	graphSigma->SetTitle("");
	OutputFile->cd();
	graphSigma->Write("Sigma_"+XVar);

//	TGraphErrors* RecaligraphSigma = new TGraphErrors(NBinsReso,BinArray,RecaliSigmaArray,BinArrayError,RecaliSigmaErrorArray);
//	RecaligraphSigma->GetXaxis()->SetTitle("Reco " + XVarLabel);
//	RecaligraphSigma->GetYaxis()->SetTitle("#sigma Value " + Units);
//	RecaligraphSigma->SetTitle("");
//	OutputFile->cd();
//	RecaligraphSigma->Write("RecaliSigma_"+XVar);

	if (StorePlots) {

		// ----------------------------------------------------------------------------------------

		// Using the differences

		TString MeanCanvasName = XVar+"_MeanOverlayCanvas"+Run;
		TCanvas* MeanOverlayCanvas = new TCanvas(MeanCanvasName,MeanCanvasName,205,34,1024,768);
		MeanOverlayCanvas->SetLeftMargin(0.15);

		MeanOverlayCanvas->cd();
		graphMean->SetLineColor(kBlack);
		graphMean->SetMarkerColor(kBlack);
		graphMean->SetMarkerStyle(20);
		graphMean->SetMarkerSize(2.);
		graphMean->SetLineWidth(3);
		graphMean->GetYaxis()->SetTitleOffset(1.35);

		double Min = 1.3*TMath::Min( TMath::MinElement(NBinsReso,graphMean->GetY()), TMath::MinElement(NBinsReso,RecaligraphMean->GetY()));
		double Max = 1.3*TMath::Max( TMath::MaxElement(NBinsReso,graphMean->GetY()), TMath::MaxElement(NBinsReso,RecaligraphMean->GetY()));
		graphMean->GetYaxis()->SetRangeUser(Min,Max);

		graphMean->Draw("ap0");

		RecaligraphMean->SetLineColor(kOrange+7);
		RecaligraphMean->SetMarkerColor(kOrange+7);
		RecaligraphMean->SetMarkerStyle(20);
		RecaligraphMean->SetMarkerSize(2.);
		RecaligraphMean->SetLineWidth(3);
		RecaligraphMean->Draw("p0 same");

		TLegend* legCali = new TLegend(0.6,0.91,0.75,0.99);
		legCali->SetTextSize(0.04);
		legCali->SetTextFont(132);
		legCali->SetBorderSize(0);

		legCali->AddEntry(RecaligraphMean,"Calibrated","p");
		legCali->AddEntry(graphMean,"Uncalibrated","p");
		legCali->Draw();

		MeanOverlayCanvas->SaveAs(PlotPath+"Mean_"+XVar+Run+".pdf");
		delete MeanOverlayCanvas;

		// ----------------------------------------------------------------------------------------

		TString SigmaCanvasName = XVar+"_SigmaOverlayCanvas"+Run;
		TCanvas* SigmaOverlayCanvas = new TCanvas(SigmaCanvasName,SigmaCanvasName,205,34,1024,768);

		SigmaOverlayCanvas->cd();
		graphSigma->SetLineColor(kBlack);
		graphSigma->SetMarkerColor(kBlack);
		graphSigma->SetMarkerStyle(20);
		graphSigma->SetMarkerSize(2.);
		graphSigma->SetLineWidth(3);
		graphSigma->SetMinimum(0);		
		graphSigma->Draw("ap0");

//		RecaligraphSigma->SetLineColor(kOrange+7);
//		RecaligraphSigma->SetMarkerColor(kOrange+7);
//		RecaligraphSigma->SetMarkerStyle(20);
//		RecaligraphSigma->SetMarkerSize(2.);
//		RecaligraphSigma->SetLineWidth(3);
//		RecaligraphSigma->Draw("p0 same");

		SigmaOverlayCanvas->SaveAs(PlotPath+"Sigma_"+XVar+Run+".pdf");
		delete SigmaOverlayCanvas;

		// ----------------------------------------------------------------------------------------

		// Using the resolutions only for the momenta

		if (ResoAxisLabel != "") {

			TString ResoMeanCanvasName = XVar+"_ResoMeanOverlayCanvas"+Run;
			TCanvas* ResoMeanOverlayCanvas = new TCanvas(ResoMeanCanvasName,ResoMeanCanvasName,205,34,1024,768);

			TGraphErrors* graphMeanReso = new TGraphErrors(NBinsReso,BinArray,ResoMeanArray,BinArrayError,ResoMeanErrorArray);
			graphMeanReso->GetXaxis()->SetTitle("Reco " + XVarLabel);
			graphMeanReso->GetYaxis()->SetTitle("Mean Value [%]");
			graphMeanReso->SetTitle("");
			graphMeanReso->SetLineColor(kBlack);
			graphMeanReso->SetMarkerColor(kBlack);
			graphMeanReso->SetMarkerStyle(20);
			graphMeanReso->SetMarkerSize(2.);
			graphMeanReso->SetLineWidth(3);

			graphMeanReso->Draw("ap0");

			ResoMeanOverlayCanvas->SaveAs(PlotPath+"ResoMean_"+XVar+Run+".pdf");
			delete ResoMeanOverlayCanvas;

		}

	}

}


void CreateSplines(TString Sample, bool StorePlots = false) {

	// -----------------------------------------------------------------------------------------------------------------------------------------

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetTitleSize(0.0,"t");
	gStyle->SetTitleFont(132,"t");

	gStyle->SetTitleOffset(0.9,"xyz");
	gStyle->SetTitleSize(0.05,"xyz");
	gStyle->SetTitleFont(132,"xyz");
	gStyle->SetLabelSize(0.05,"xyz");
	gStyle->SetLabelFont(132,"xyz");
	gStyle->SetNdivisions(8,"xyz");

	gStyle->SetOptStat(0);

	gROOT->ForceStyle();

	TH1::SetDefaultSumw2(kTRUE);

	// -----------------------------------------------------------------------------------------------------------------------------------------

	TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_"+Sample+"_"+UBCodeVersion+".root","readonly");
	TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

	// ---------------------------------------------------------------------------------------------------------------------------------------

	TString FileName = "/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/Splines_"+Sample+"_"+UBCodeVersion+".root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

	// ---------------------------------------------------------------------------------------------------------------------------------------

	ReturnGraph(OutputFile,tree,qualifier,"CandidateP_P_Range",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"CandidateP_Phi",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"CandidateP_Theta",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"CandidateP_CosTheta",StorePlots);

	ReturnGraph(OutputFile,tree,qualifier,"CandidateMu_P_Range",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"CandidateMu_P_MCS",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"CandidateMu_Phi",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"CandidateMu_Theta",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"CandidateMu_CosTheta",StorePlots);

	ReturnGraph(OutputFile,tree,qualifier,"Reco_Pt",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"Reco_DeltaPhiT",StorePlots);
	ReturnGraph(OutputFile,tree,qualifier,"Reco_DeltaAlphaT",StorePlots);

	// ---------------------------------------------------------------------------------------------------------------------------------------

	OutputFile->Close();
	delete tree;
	OverlayFile->Close();

	std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;

	// ---------------------------------------------------------------------------------------------------------------------------------------
	// ---------------------------------------------------------------------------------------------------------------------------------------

} // End of the program 
