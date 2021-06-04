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

void ReturnGraph(TFile* OutputFile, TTree* tree, TString qualifier, TString XVar) {

	double XminReso = -30.; double XmaxReso = 30.; int NBins = 40;

	TString AxisLabel = ""; TString Reso = ""; const int NBinsReso = 10;
	double Xmin = -999.; double Xmax = -999.; TString XVarLabel = "";

	// --------------------------------------------------------------------------------------------------

	if (XVar == "CandidateP_P_Range") { 

		AxisLabel = ";P_{p} resolution [%];# Events;"; Reso = "(CandidateP_P_Range-True_CandidateP_P)/True_CandidateP_P*100.";
		Xmin = ArrayNBinsProtonMomentum[0]; Xmax = ArrayNBinsProtonMomentum[NBinsProtonMomentum]; XVarLabel = "P_{p} Range [GeV/c]";

	}

	if (XVar == "CandidateMu_P_Range") { 

		AxisLabel = ";P_{#mu} resolution [%];# Events;"; Reso = "(CandidateMu_P_Range-True_CandidateMu_P)/True_CandidateMu_P*100.";
		Xmin = ArrayNBinsMuonMomentum[0]; Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum]; XVarLabel = "P_{#mu} Range [GeV/c]";

	}

	if (XVar == "CandidateMu_P_MCS") { 

		AxisLabel = ";P_{#mu} resolution [%];# Events;"; Reso = "(CandidateMu_P_MCS-True_CandidateMu_P)/True_CandidateMu_P*100.";
		Xmin = 0.25; Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum]; XVarLabel = "P_{#mu} MCS [GeV/c]";

	}

	// --------------------------------------------------------------------------------------------------

	double Step = (Xmax -Xmin) / NBinsReso;

	double BinArray[NBinsReso] = {0};
	double BinArrayError[NBinsReso] = {0};
	double MeanArray[NBinsReso] = {0};
	double SigmaArray[NBinsReso] = {0};
	double MeanErrorArray[NBinsReso] = {0};
	double SigmaErrorArray[NBinsReso] = {0};

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
	OutputFile->cd();
	graphMean->Write("Mean_"+XVar);

	TGraphErrors* graphSigma = new TGraphErrors(NBinsReso,BinArray,SigmaArray,BinArrayError,SigmaErrorArray);
	graphSigma->GetXaxis()->SetTitle(XVarLabel);
	graphSigma->GetYaxis()->SetTitle("Sigma Value [%]");
	OutputFile->cd();
	graphSigma->Write("Sigma_"+XVar);


}


void CreateSplines(TString Sample) {

	// -------------------------------------------------------------------------------------------------------------------------------------------------

//	std::vector<TString> Runs{"Run1"};
//	std::vector<TString> Runs{"Run1","Run3"};

//	const int NRuns = Runs.size();

//	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_"+Sample+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

//		TFile* OverlayTruthFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreTruthSelection_"+Sample+"_"+UBCodeVersion+".root","readonly");
//		TTree* treeTruth = (TTree*)(OverlayTruthFile->Get("myPreTruthSelection"));

//		TFile* DataFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_BeamOn9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
//		TTree* treeData = (TTree*)(DataFile->Get("myPreSelection"));

		TString CC1p = "CC1p && CandidateMu_MCParticle_Pdg == 13 && CandidateP_MCParticle_Pdg == 2212 && NumberPi0 == 0"; 

		TString Containment = "CandidateMu_StartContainment == 1 && CandidateP_StartContainment == 1 && CandidateP_EndContainment == 1 && True_CandidateMu_StartContainment == 1";

		// Use uncalibrated quantities to obtain calibration

		TString ProtonMom = "CandidateP_P_Range > " + TString(std::to_string(ArrayNBinsProtonMomentum[0])) + " && CandidateP_P_Range < "\
		+ TString(std::to_string(ArrayNBinsProtonMomentum[NBinsProtonMomentum])) + " && True_CandidateP_P > "+ TString(std::to_string(ArrayNBinsProtonMomentum[0]))\
		+ " && True_CandidateP_P < "+ TString(std::to_string(ArrayNBinsProtonMomentum[NBinsProtonMomentum]));

		TString DeltaPT = "Reco_Pt > " + TString(std::to_string(ArrayNBinsDeltaPT[0])) + " && Reco_Pt < " + TString(std::to_string(ArrayNBinsDeltaPT[NBinsDeltaPT]))\
		+ " && True_Pt > " + TString(std::to_string(ArrayNBinsDeltaPT[0])) + " && True_Pt < " + TString(std::to_string(ArrayNBinsDeltaPT[NBinsDeltaPT]));
 
		TString DeltaPhiT = "Reco_DeltaPhiT > " + TString(std::to_string(ArrayNBinsDeltaPhiT[0])) + " && Reco_DeltaPhiT < " + TString(std::to_string(ArrayNBinsDeltaPhiT[NBinsDeltaPhiT]))\
		+ " && True_DeltaPhiT > " + TString(std::to_string(ArrayNBinsDeltaPhiT[0])) + " && True_DeltaPhiT < " + TString(std::to_string(ArrayNBinsDeltaPhiT[NBinsDeltaPhiT])); 

		TString MuonMom = "True_CandidateMu_P > "+ TString(std::to_string(ArrayNBinsMuonMomentum[0])) + " && True_CandidateMu_P < "\
		+ TString(std::to_string(ArrayNBinsMuonMomentum[NBinsMuonMomentum]))\
		+ " && ( ( CandidateMu_EndContainment == 1 && CandidateMu_P_Range > "\
		+ TString(std::to_string(ArrayNBinsMuonMomentum[0])) + " && CandidateMu_P_Range < "\
		+ TString(std::to_string(ArrayNBinsMuonMomentum[NBinsMuonMomentum])) +" ) || ( CandidateMu_EndContainment == 0 && CandidateMu_P_MCS > "\
		+ TString(std::to_string(ArrayNBinsMuonMomentum[0])) + " && CandidateMu_P_MCS < "\
		+ TString(std::to_string(ArrayNBinsMuonMomentum[NBinsMuonMomentum])) +" ) )" ;

		TString LLP = " CandidateP_ThreePlaneLogLikelihood > " + TString(std::to_string(ProtonThreePlaneChi2LogLikelihoodCut));

		TString NuScore = " NuScore > " + TString(std::to_string(MinimumNuScore)); 

		TString QualityCut = " ( (CandidateMu_EndContainment == 1 && TMath::Abs(CandidateMu_P_Range-CandidateMu_P_MCS)/CandidateMu_P_Range<0.25 ) || CandidateMu_EndContainment == 0)";

		TString MinHitsMu = "  (CandidateMu_Plane0_TruncdEdx[0][0] + CandidateMu_Plane1_TruncdEdx[0][0] + CandidateMu_Plane2_TruncdEdx[0][0] > 0.5)";

		TString MinHitsP = " (CandidateP_Plane0_TruncdEdx[0][0] + CandidateP_Plane1_TruncdEdx[0][0] + CandidateP_Plane2_TruncdEdx[0][0] > 1.5)";

		TString qualifier = CC1p +" && "+ Containment +" && " + ProtonMom + " && " + DeltaPT + " && " + DeltaPhiT + " && " + MuonMom + " && " + QualityCut + " && " + MinHitsMu + " && " + MinHitsP;

		// ---------------------------------------------------------------------------------------------------------------------------------------

		// What about NuWro ?

		TString FileName = "/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/Splines_"+Sample+"_"+UBCodeVersion+".root";
		TFile* OutputFile = new TFile(FileName,"recreate");
		std::cout << std::endl << "File " << FileName << " to be created"<< std::endl << std::endl;

		// ---------------------------------------------------------------------------------------------------------------------------------------

		ReturnGraph(OutputFile,tree,qualifier,"CandidateP_P_Range");
		ReturnGraph(OutputFile,tree,qualifier,"CandidateMu_P_Range");
		ReturnGraph(OutputFile,tree,qualifier,"CandidateMu_P_MCS");

		// ---------------------------------------------------------------------------------------------------------------------------------------

		OutputFile->Close();

		std::cout << std::endl << "File " << FileName << " has been created"<< std::endl << std::endl;

		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

	//} // End of the loop over the runs

} // End of the program 
