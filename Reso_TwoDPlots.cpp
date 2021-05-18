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

#include "ubana/myClasses/Tools.h"
#include "ubana/myClasses/Constants.h"

using namespace std;
using namespace Constants;

void Reso_TwoDPlots() {

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

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<TString> Runs{"Run1"};
//	std::vector<TString> Runs{"Run1","Run3"};
//	std::vector<TString> Runs{"Run1","Run2","Run3","Run4","Run5"};

	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

		TFile* DataFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_BeamOn9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* treeData = (TTree*)(OverlayFile->Get("myPreSelection"));

		TString CC1p = "CC1p && CandidateMu_MCParticle_Pdg == 13 && CandidateP_MCParticle_Pdg == 2212 && NumberPi0 == 0"; 

		TString Containment = "CandidateMu_StartContainment == 1 && CandidateP_StartContainment == 1 && CandidateP_EndContainment == 1 && True_CandidateMu_StartContainment == 1";

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

		TString qualifier = CC1p +" && "+ Containment +" && " + ProtonMom + " && " + DeltaPT + " && " + DeltaPhiT + " && " + MuonMom + " && " + LLP + " && " + NuScore;

		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------
/*
		// DeltaAlphaTReso Vs ThetaMu

		TH2D* DeltaAlphaTResoVsThetaMu = new TH2D("DeltaAlphaTResoVsThetaMu",";#theta_{#mu} [deg];#delta#alpha_{T} resolution [%]",180,0,180,200,-100.,100.);

		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:TMath::ACos(CandidateMu_CosTheta)*180./TMath::Pi()>>DeltaAlphaTResoVsThetaMu",qualifier,"goff");

		TCanvas* DeltaAlphaTResoVsThetaMuCanvas = new TCanvas("DeltaAlphaTResoVsThetaMuCanvas_"+Runs[WhichRun],"DeltaAlphaTResoVsThetaMuCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaAlphaTResoVsThetaMu->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaAlphaTResoVsThetaMuCanvas->SaveAs(PlotPath+"DeltaAlphaTResoVsThetaMu2DCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaAlphaTResoVsThetaMuCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// DeltaAlphaTReso Vs ThetaP

		TH2D* DeltaAlphaTResoVsThetaP = new TH2D("DeltaAlphaTResoVsThetaP",";#theta_{p} [deg];#delta#alpha_{T} resolution [%]",180,0,180,200,-100.,100.);

		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:TMath::ACos(CandidateP_CosTheta)*180./TMath::Pi()>>DeltaAlphaTResoVsThetaP",qualifier,"goff");

		TCanvas* DeltaAlphaTResoVsThetaPCanvas = new TCanvas("DeltaAlphaTResoVsThetaPCanvas_"+Runs[WhichRun],"DeltaAlphaTResoVsThetaPCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaAlphaTResoVsThetaP->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaAlphaTResoVsThetaPCanvas->SaveAs(PlotPath+"DeltaAlphaTResoVsThetaP2DCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaAlphaTResoVsThetaPCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// DeltaAlphaTReso Vs DeltaTheta

		TH2D* DeltaAlphaTResoVsDeltaTheta = new TH2D("DeltaAlphaTResoVsDeltaTheta",";#delta#theta_{#mu,p} [deg];#delta#alpha_{T} resolution [%]",180,0,180,200,-100.,100.);

		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:Reco_DeltaTheta>>DeltaAlphaTResoVsDeltaTheta",qualifier,"goff");

		TCanvas* DeltaAlphaTResoVsDeltaThetaCanvas = new TCanvas("DeltaAlphaTResoVsDeltaThetaCanvas_"+Runs[WhichRun],"DeltaAlphaTResoVsDeltaThetaCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaAlphaTResoVsDeltaTheta->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaAlphaTResoVsDeltaThetaCanvas->SaveAs(PlotPath+"DeltaAlphaTResoVsDeltaTheta2DCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaAlphaTResoVsDeltaThetaCanvas;


		// 1D Projection in PhiT Slices
	
		TH1D* DeltaAlphaTReso_LowDeltaTheta = new TH1D("DeltaAlphaTReso_LowDeltaTheta",";#delta#alpha_{T} resolution [%]",100,-100.,100.);
		TH1D* DeltaAlphaTReso_MedDeltaTheta = new TH1D("DeltaAlphaTReso_MedDeltaTheta",";#delta#alpha_{T} resolution [%]",100,-100.,100.);
		TH1D* DeltaAlphaTReso_HighDeltaTheta = new TH1D("DeltaAlphaTReso_HighDeltaTheta",";#delta#alpha_{T} resolution [%]",100,-100.,100.);

		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>DeltaAlphaTReso_LowDeltaTheta",qualifier + " && TMath::Abs(Reco_DeltaTheta - 90) < 30","goff");
		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>DeltaAlphaTReso_MedDeltaTheta",qualifier + " && TMath::Abs(Reco_DeltaTheta - 90) > 30 && TMath::Abs(Reco_DeltaTheta - 90) < 60","goff");	
		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>DeltaAlphaTReso_HighDeltaTheta",qualifier + " && TMath::Abs(Reco_DeltaTheta - 90) > 60","goff");

		TCanvas* DeltaAlphaTReso_DeltaThetaSlices_Canvas = new TCanvas("DeltaAlphaTReso_DeltaThetaSlices_Canvas_"+Runs[WhichRun],"DeltaAlphaTReso_DeltaThetaSlices_Canvas_"+Runs[WhichRun],205,34,1024,768);

		DeltaAlphaTReso_LowDeltaTheta->GetXaxis()->CenterTitle();
		DeltaAlphaTReso_LowDeltaTheta->GetYaxis()->CenterTitle();
		DeltaAlphaTReso_LowDeltaTheta->GetYaxis()->SetTitle("Arbitrary Units");

		DeltaAlphaTReso_LowDeltaTheta->SetLineColor(kBlue+2);
		DeltaAlphaTReso_LowDeltaTheta->SetMarkerColor(kBlue+2);
		DeltaAlphaTReso_LowDeltaTheta->SetMarkerSize(2.);
		DeltaAlphaTReso_LowDeltaTheta->SetMarkerStyle(20);
		DeltaAlphaTReso_LowDeltaTheta->Scale(1./DeltaAlphaTReso_LowDeltaTheta->GetMaximum());
		DeltaAlphaTReso_LowDeltaTheta->Draw("p0 hist same");

		DeltaAlphaTReso_MedDeltaTheta->SetLineColor(kGreen+1);
		DeltaAlphaTReso_MedDeltaTheta->SetMarkerColor(kGreen+1);
		DeltaAlphaTReso_MedDeltaTheta->SetMarkerSize(2.);
		DeltaAlphaTReso_MedDeltaTheta->SetMarkerStyle(20);
		DeltaAlphaTReso_MedDeltaTheta->Scale(1./DeltaAlphaTReso_MedDeltaTheta->GetMaximum());
		DeltaAlphaTReso_MedDeltaTheta->Draw("p0 hist same");

		DeltaAlphaTReso_HighDeltaTheta->SetLineColor(kOrange+7);
		DeltaAlphaTReso_HighDeltaTheta->SetMarkerColor(kOrange+7);
		DeltaAlphaTReso_HighDeltaTheta->SetMarkerSize(2.);
		DeltaAlphaTReso_HighDeltaTheta->SetMarkerStyle(20);
		DeltaAlphaTReso_HighDeltaTheta->Scale(1./DeltaAlphaTReso_HighDeltaTheta->GetMaximum());
		DeltaAlphaTReso_HighDeltaTheta->Draw("p0 hist same");


		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		TLegend* leg_DeltaAlphaTReso_DeltaThetaSlices = new TLegend(0.55,0.65,0.85,0.85);
		leg_DeltaAlphaTReso_DeltaThetaSlices->SetBorderSize(0);
		leg_DeltaAlphaTReso_DeltaThetaSlices->SetTextFont(132);
		leg_DeltaAlphaTReso_DeltaThetaSlices->SetTextSize(0.05);

		leg_DeltaAlphaTReso_DeltaThetaSlices->AddEntry(DeltaAlphaTReso_LowDeltaTheta,"|#delta#theta_{#mu,p} - 90| < 30 deg","p");
		leg_DeltaAlphaTReso_DeltaThetaSlices->AddEntry(DeltaAlphaTReso_MedDeltaTheta,"30 < |#delta#theta_{#mu,p} - 90| < 60 deg","p");
		leg_DeltaAlphaTReso_DeltaThetaSlices->AddEntry(DeltaAlphaTReso_HighDeltaTheta,"|#delta#theta_{#mu,p} - 90| > 60 deg","p");
		leg_DeltaAlphaTReso_DeltaThetaSlices->Draw();

		DeltaAlphaTReso_DeltaThetaSlices_Canvas->SaveAs(PlotPath+"DeltaAlphaTReso_DeltaThetaSlices_Canvas_"+Runs[WhichRun]+".pdf");
		//delete DeltaAlphaTReso_DeltaThetaSlices_Canvas;

		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

		// DeltaPhiTReso Vs ThetaMu

		TH2D* DeltaPhiTResoVsThetaMu = new TH2D("DeltaPhiTResoVsThetaMu",";#theta_{#mu} [deg];#delta#phi_{T} resolution [%]",180,0,180,200,-100.,100.);

		tree->Draw("(Reco_DeltaPhiT-True_DeltaPhiT)/True_DeltaPhiT*100.:TMath::ACos(CandidateMu_CosTheta)*180./TMath::Pi()>>DeltaPhiTResoVsThetaMu",qualifier,"goff");

		TCanvas* DeltaPhiTResoVsThetaMuCanvas = new TCanvas("DeltaPhiTResoVsThetaMuCanvas_"+Runs[WhichRun],"DeltaPhiTResoVsThetaMuCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPhiTResoVsThetaMu->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaPhiTResoVsThetaMuCanvas->SaveAs(PlotPath+"DeltaPhiTResoVsThetaMu2DCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPhiTResoVsThetaMuCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// DeltaPhiTReso Vs ThetaP

		TH2D* DeltaPhiTResoVsThetaP = new TH2D("DeltaPhiTResoVsThetaP",";#theta_{p} [deg];#delta#phi_{T} resolution [%]",180,0,180,200,-100.,100.);

		tree->Draw("(Reco_DeltaPhiT-True_DeltaPhiT)/True_DeltaPhiT*100.:TMath::ACos(CandidateP_CosTheta)*180./TMath::Pi()>>DeltaPhiTResoVsThetaP",qualifier,"goff");

		TCanvas* DeltaPhiTResoVsThetaPCanvas = new TCanvas("DeltaPhiTResoVsThetaPCanvas_"+Runs[WhichRun],"DeltaPhiTResoVsThetaPCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPhiTResoVsThetaP->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaPhiTResoVsThetaPCanvas->SaveAs(PlotPath+"DeltaPhiTResoVsThetaP2DCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPhiTResoVsThetaPCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// DeltaPhiTReso Vs DeltaTheta

		TH2D* DeltaPhiTResoVsDeltaTheta = new TH2D("DeltaPhiTResoVsDeltaTheta",";#delta#theta_{#mu,p} [deg];#delta#phi_{T} resolution [%]",180,0,180,200,-100.,100.);

		tree->Draw("(Reco_DeltaPhiT-True_DeltaPhiT)/True_DeltaPhiT*100.:Reco_DeltaTheta>>DeltaPhiTResoVsDeltaTheta",qualifier,"goff");

		TCanvas* DeltaPhiTResoVsDeltaThetaCanvas = new TCanvas("DeltaPhiTResoVsDeltaThetaCanvas_"+Runs[WhichRun],"DeltaPhiTResoVsDeltaThetaCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPhiTResoVsDeltaTheta->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaPhiTResoVsDeltaThetaCanvas->SaveAs(PlotPath+"DeltaPhiTResoVsDeltaTheta2DCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPhiTResoVsDeltaThetaCanvas;

		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

		// DeltaPTReso Vs ThetaMu

		TH2D* DeltaPTResoVsThetaMu = new TH2D("DeltaPTResoVsThetaMu",";#theta_{#mu} [deg];#deltap_{T} resolution [%]",180,0,180,200,-100.,100.);

		tree->Draw("(Reco_Pt-True_Pt)/True_Pt*100.:TMath::ACos(CandidateMu_CosTheta)*180./TMath::Pi()>>DeltaPTResoVsThetaMu",qualifier,"goff");

		TCanvas* DeltaPTResoVsThetaMuCanvas = new TCanvas("DeltaPTResoVsThetaMuCanvas_"+Runs[WhichRun],"DeltaPTResoVsThetaMuCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPTResoVsThetaMu->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaPTResoVsThetaMuCanvas->SaveAs(PlotPath+"DeltaPTResoVsThetaMu2DCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPTResoVsThetaMuCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// DeltaPTReso Vs ThetaP

		TH2D* DeltaPTResoVsThetaP = new TH2D("DeltaPTResoVsThetaP",";#theta_{p} [deg];#deltap_{T} resolution [%]",180,0,180,200,-100.,100.);

		tree->Draw("(Reco_Pt-True_Pt)/True_Pt*100.:TMath::ACos(CandidateP_CosTheta)*180./TMath::Pi()>>DeltaPTResoVsThetaP",qualifier,"goff");

		TCanvas* DeltaPTResoVsThetaPCanvas = new TCanvas("DeltaPTResoVsThetaPCanvas_"+Runs[WhichRun],"DeltaPTResoVsThetaPCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPTResoVsThetaP->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaPTResoVsThetaPCanvas->SaveAs(PlotPath+"DeltaPTResoVsThetaP2DCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPTResoVsThetaPCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// DeltaPTReso Vs DeltaTheta

		TH2D* DeltaPTResoVsDeltaTheta = new TH2D("DeltaPTResoVsDeltaTheta",";#delta#theta_{#mu,p} [deg];#delta p_{T} resolution [%]",180,0,180,200,-100.,100.);

		tree->Draw("(Reco_Pt-True_Pt)/True_Pt*100.:Reco_DeltaTheta>>DeltaPTResoVsDeltaTheta",qualifier,"goff");

		TCanvas* DeltaPTResoVsDeltaThetaCanvas = new TCanvas("DeltaPTResoVsDeltaThetaCanvas_"+Runs[WhichRun],"DeltaPTResoVsDeltaThetaCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPTResoVsDeltaTheta->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaPTResoVsDeltaThetaCanvas->SaveAs(PlotPath+"DeltaPTResoVsDeltaTheta2DCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPTResoVsDeltaThetaCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------

		// DeltaAlphaTReso Vs DeltaPT

		TH2D* DeltaAlphaTResoVsDeltaPT = new TH2D("DeltaAlphaTResoVsDeltaPT",";#deltap_{T} [GeV/c];#delta#alpha_{T} resolution [%]",100,0.,1.,200,-100.,100.);

		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:Reco_Pt>>DeltaAlphaTResoVsDeltaPT",qualifier,"goff");

		TCanvas* DeltaAlphaTResoVsDeltaPTCanvas = new TCanvas("DeltaAlphaTResoVsDeltaPTCanvas_"+Runs[WhichRun],"DeltaAlphaTResoVsDeltaPTCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaAlphaTResoVsDeltaPT->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaAlphaTResoVsDeltaPTCanvas->SaveAs(PlotPath+"DeltaAlphaTResoVsDeltaPT2DCanvas_"+Runs[WhichRun]+".pdf");
		//delete DeltaAlphaTResoVsDeltaPTCanvas;

		// 1D Projection in PT Slices
	
		TH1D* DeltaAlphaTReso_LowDeltaPT = new TH1D("DeltaAlphaTReso_LowDeltaPT",";#delta#alpha_{T} resolution [%]",100,-100.,100.);
		TH1D* DeltaAlphaTReso_MedDeltaPT = new TH1D("DeltaAlphaTReso_MedDeltaPT",";#delta#alpha_{T} resolution [%]",100,-100.,100.);
		TH1D* DeltaAlphaTReso_HighDeltaPT = new TH1D("DeltaAlphaTReso_HighDeltaPT",";#delta#alpha_{T} resolution [%]",100,-100.,100.);

		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>DeltaAlphaTReso_LowDeltaPT",qualifier + " && Reco_Pt < 0.3","goff");
		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>DeltaAlphaTReso_MedDeltaPT",qualifier + " && Reco_Pt > 0.3 && Reco_Pt < 0.6","goff");	
		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>DeltaAlphaTReso_HighDeltaPT",qualifier + " && Reco_Pt > 0.6","goff");

		TCanvas* DeltaAlphaTReso_PTSlices_Canvas = new TCanvas("DeltaAlphaTReso_DeltaPTSlices_Canvas_"+Runs[WhichRun],"DeltaAlphaTReso_Slices_Canvas_"+Runs[WhichRun],205,34,1024,768);

		DeltaAlphaTReso_LowDeltaPT->GetXaxis()->CenterTitle();
		DeltaAlphaTReso_LowDeltaPT->GetYaxis()->CenterTitle();
		DeltaAlphaTReso_LowDeltaPT->GetYaxis()->SetTitle("Arbitrary Units");

		DeltaAlphaTReso_LowDeltaPT->SetLineColor(kBlue+2);
		DeltaAlphaTReso_LowDeltaPT->SetMarkerColor(kBlue+2);
		DeltaAlphaTReso_LowDeltaPT->SetMarkerSize(2.);
		DeltaAlphaTReso_LowDeltaPT->SetMarkerStyle(20);
		DeltaAlphaTReso_LowDeltaPT->Scale(1./DeltaAlphaTReso_LowDeltaPT->GetMaximum());
		DeltaAlphaTReso_LowDeltaPT->Draw("p0 hist same");

		DeltaAlphaTReso_MedDeltaPT->SetLineColor(kGreen+1);
		DeltaAlphaTReso_MedDeltaPT->SetMarkerColor(kGreen+1);
		DeltaAlphaTReso_MedDeltaPT->SetMarkerSize(2.);
		DeltaAlphaTReso_MedDeltaPT->SetMarkerStyle(20);
		DeltaAlphaTReso_MedDeltaPT->Scale(1./DeltaAlphaTReso_MedDeltaPT->GetMaximum());
		DeltaAlphaTReso_MedDeltaPT->Draw("p0 hist same");

		DeltaAlphaTReso_HighDeltaPT->SetLineColor(kOrange+7);
		DeltaAlphaTReso_HighDeltaPT->SetMarkerColor(kOrange+7);
		DeltaAlphaTReso_HighDeltaPT->SetMarkerSize(2.);
		DeltaAlphaTReso_HighDeltaPT->SetMarkerStyle(20);
		DeltaAlphaTReso_HighDeltaPT->Scale(1./DeltaAlphaTReso_HighDeltaPT->GetMaximum());
		DeltaAlphaTReso_HighDeltaPT->Draw("p0 hist same");


		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		TLegend* leg_DeltaAlphaTReso_PTSlices = new TLegend(0.55,0.65,0.85,0.85);
		leg_DeltaAlphaTReso_PTSlices->SetBorderSize(0);
		leg_DeltaAlphaTReso_PTSlices->SetTextFont(132);
		leg_DeltaAlphaTReso_PTSlices->SetTextSize(0.05);

		leg_DeltaAlphaTReso_PTSlices->AddEntry(DeltaAlphaTReso_LowDeltaPT,"#deltap_{T} < 0.3 GeV/c","p");
		leg_DeltaAlphaTReso_PTSlices->AddEntry(DeltaAlphaTReso_MedDeltaPT,"0.3 < #deltap_{T} < 0.6 GeV/c","p");
		leg_DeltaAlphaTReso_PTSlices->AddEntry(DeltaAlphaTReso_HighDeltaPT,"#deltap_{T} > 0.6 GeV/c","p");
		leg_DeltaAlphaTReso_PTSlices->Draw();

		DeltaAlphaTReso_PTSlices_Canvas->SaveAs(PlotPath+"DeltaAlphaTReso_DeltaPTSlices_Canvas_"+Runs[WhichRun]+".pdf");
		//delete DeltaAlphaTReso_PTSlices_Canvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------
*/
		// DeltaAlphaTReso Vs DeltaPhiT
/*
		TH2D* DeltaAlphaTResoVsDeltaPhiT = new TH2D("DeltaAlphaTResoVsDeltaPhiT",";#delta#phi_{T} [GeV/c];#delta#alpha_{T} resolution [%]",180,0.,180.,200,-100.,100.);

//		qualifier = qualifier + " && CandidateMu_EndContainment == 1 && TMath::Abs(CandidateMu_P_Range - CandidateMu_P_MCS)/CandidateMu_P_Range  < 0.25";
		qualifier = qualifier + " && CandidateMu_EndContainment == 0 && TMath::Abs(CandidateMu_StartZ - CandidateMu_EndZ)  > 50";

		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:Reco_DeltaPhiT>>DeltaAlphaTResoVsDeltaPhiT",qualifier,"goff");

		TCanvas* DeltaAlphaTResoVsDeltaPhiTCanvas = new TCanvas("DeltaAlphaTResoVsDeltaPhiTCanvas_"+Runs[WhichRun],"DeltaAlphaTResoVsDeltaPhiTCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaAlphaTResoVsDeltaPhiT->Draw("coltz");

		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		DeltaAlphaTResoVsDeltaPhiTCanvas->SaveAs(PlotPath+"DeltaAlphaTResoVsDeltaPhiT2DCanvas_"+Runs[WhichRun]+".pdf");
		//delete DeltaAlphaTResoVsDeltaPTCanvas;

		// 1D Projection in PhiT Slices
	
		TH1D* DeltaAlphaTReso_LowDeltaPhiT = new TH1D("DeltaAlphaTReso_LowDeltaPhiT",";#delta#alpha_{T} resolution [%]",100,-100.,100.);
		TH1D* DeltaAlphaTReso_MedDeltaPhiT = new TH1D("DeltaAlphaTReso_MedDeltaPhiT",";#delta#alpha_{T} resolution [%]",100,-100.,100.);
		TH1D* DeltaAlphaTReso_HighDeltaPhiT = new TH1D("DeltaAlphaTReso_HighDeltaPhiT",";#delta#alpha_{T} resolution [%]",100,-100.,100.);

		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>DeltaAlphaTReso_LowDeltaPhiT",qualifier + " && Reco_DeltaPhiT < 30","goff");
		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>DeltaAlphaTReso_MedDeltaPhiT",qualifier + " && Reco_DeltaPhiT > 30 && Reco_DeltaPhiT < 60","goff");	
		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>DeltaAlphaTReso_HighDeltaPhiT",qualifier + " && Reco_DeltaPhiT > 60","goff");

		TCanvas* DeltaAlphaTReso_PhiTSlices_Canvas = new TCanvas("DeltaAlphaTReso_DeltaPhiTSlices_Canvas_"+Runs[WhichRun],"DeltaAlphaTReso_Slices_Canvas_"+Runs[WhichRun],205,34,1024,768);

		DeltaAlphaTReso_LowDeltaPhiT->GetXaxis()->CenterTitle();
		DeltaAlphaTReso_LowDeltaPhiT->GetYaxis()->CenterTitle();
		DeltaAlphaTReso_LowDeltaPhiT->GetYaxis()->SetTitle("Arbitrary Units");

		DeltaAlphaTReso_LowDeltaPhiT->SetLineColor(kBlue+2);
		DeltaAlphaTReso_LowDeltaPhiT->SetMarkerColor(kBlue+2);
		DeltaAlphaTReso_LowDeltaPhiT->SetMarkerSize(2.);
		DeltaAlphaTReso_LowDeltaPhiT->SetMarkerStyle(20);
		DeltaAlphaTReso_LowDeltaPhiT->Scale(1./DeltaAlphaTReso_LowDeltaPhiT->GetMaximum());
		DeltaAlphaTReso_LowDeltaPhiT->Draw("p0 hist same");

		DeltaAlphaTReso_MedDeltaPhiT->SetLineColor(kGreen+1);
		DeltaAlphaTReso_MedDeltaPhiT->SetMarkerColor(kGreen+1);
		DeltaAlphaTReso_MedDeltaPhiT->SetMarkerSize(2.);
		DeltaAlphaTReso_MedDeltaPhiT->SetMarkerStyle(20);
		DeltaAlphaTReso_MedDeltaPhiT->Scale(1./DeltaAlphaTReso_MedDeltaPhiT->GetMaximum());
		DeltaAlphaTReso_MedDeltaPhiT->Draw("p0 hist same");

		DeltaAlphaTReso_HighDeltaPhiT->SetLineColor(kOrange+7);
		DeltaAlphaTReso_HighDeltaPhiT->SetMarkerColor(kOrange+7);
		DeltaAlphaTReso_HighDeltaPhiT->SetMarkerSize(2.);
		DeltaAlphaTReso_HighDeltaPhiT->SetMarkerStyle(20);
		DeltaAlphaTReso_HighDeltaPhiT->Scale(1./DeltaAlphaTReso_HighDeltaPhiT->GetMaximum());
		DeltaAlphaTReso_HighDeltaPhiT->Draw("p0 hist same");


		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		TLegend* leg_DeltaAlphaTReso_PhiTSlices = new TLegend(0.55,0.65,0.85,0.85);
		leg_DeltaAlphaTReso_PhiTSlices->SetBorderSize(0);
		leg_DeltaAlphaTReso_PhiTSlices->SetTextFont(132);
		leg_DeltaAlphaTReso_PhiTSlices->SetTextSize(0.05);

		leg_DeltaAlphaTReso_PhiTSlices->AddEntry(DeltaAlphaTReso_LowDeltaPhiT,"#delta#phi_{T} < 30 deg","p");
		leg_DeltaAlphaTReso_PhiTSlices->AddEntry(DeltaAlphaTReso_MedDeltaPhiT,"30 < #delta#phi_{T} < 60 deg","p");
		leg_DeltaAlphaTReso_PhiTSlices->AddEntry(DeltaAlphaTReso_HighDeltaPhiT,"#delta#phi_{T} > 60 deg","p");
		leg_DeltaAlphaTReso_PhiTSlices->Draw();

		DeltaAlphaTReso_PhiTSlices_Canvas->SaveAs(PlotPath+"DeltaAlphaTReso_DeltaPhiTSlices_Canvas_"+Runs[WhichRun]+".pdf");
		//delete DeltaAlphaTReso_PhiTSlices_Canvas;
*/

		// ---------------------------------------------------------------------------------------------------------------------------------------

		// Playground

		// 1D Plots for PhiT < 30 deg events
	
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#theta_{#mu} [deg]",180,0.,180.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#phi_{#mu} [deg]",180,-180.,180.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";Muon containment",2,-0.5,1.5);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";P_{#mu} [GeV/c]",50,0.1,1.7);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#theta_{p} [deg]",180,0.,180.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#phi_{p} [deg]",180,-180.,180.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";P_{p} [GeV/c]",50,0.25,1.2);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#delta#theta_{#mu,p} [deg]",180,0.,180.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#delta#phi_{#mu,p} [deg]",180,0.,360.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";Muon Length [cm]",200,0.,400.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";Proton Length [cm]",200,0.,100.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";Proton Length [cm];#delta#alpha_{T} resolution [%]",200,0.,100.,200,-100.,100.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True cos#theta_{#mu};Reco cos#theta_{#mu}",100,-1,1.,100,-1.,1.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True cos#theta_{p};Reco cos#theta_{p}",100,-1,1.,100,-1.,1.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True #phi_{#mu};Reco #phi_{#mu}",90,-180,180.,90,-180.,180.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True #phi_{p};Reco #phi_{p}",90,-180,180.,90,-180.,180.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True #theta_{#mu};Reco #theta_{#mu}",90,0,180.,90,0.,180.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True #theta_{p};Reco #theta_{p}",90,0,180.,90,0.,180.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";#delta p_{T} [GeV/c];#delta#phi_{T} [deg]",100,0,1.,90,0.,180.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True P_{#mu,#perp};Reco P_{#mu,#perp}",100,0.,1.,100,0.,1.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True P_{p,#perp};Reco P_{p,#perp}",100,0.,1.,100,0.,1.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True #delta#alpha_{T};Reco #delta#alpha_{T}",90,0.,180.,90,0.,180.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True #delta p_{T};Reco #delta p_{T}",100,0.,1.,100,0.,1.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True P_{#mu,X};Reco P_{#mu,X}",100,0.,1.,100,0.,1.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True #delta p_{T} [GeV/c];Reco #delta p_{T} [deg]",100,0,1.,100,0,1.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";Muon Start Z - Vertex Z [cm];#delta#alpha_{T} resolution [%]",50,0.,5.,200,-100.,100.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";Proton Start Z - Vertex Z [cm];#delta#alpha_{T} resolution [%]",50,0.,5.,200,-100.,100.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";#mu-p distance [cm];#delta#alpha_{T} resolution [%]",50,0.,5.,200,-100.,100.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True G4 Muon Length [cm];Reco Muon Length [cm]",80,0.,400.,80,0.,400.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True G4 Proton Length [cm];Reco Proton Length [cm]",100,0.,100.,100,0.,100.);

//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#Delta#theta [deg];",180,0.,180.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#Delta#theta [deg];",180,0.,180.);
		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#delta#alpha_{T} resolution[%];",200,-100.,100.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#theta_{#mu} [deg];",180,0.,180.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";#phi_{#mu} [deg];",360,-180.,180.);

//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";cos#theta#mu;#delta#alpha_{T} resolution [%]",100,-1,1.,200,-100.,100.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";cos#thetap;#delta#alpha_{T} resolution [%]",100,-1,1.,200,-100.,100.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";Muon Start Point - Vertex Distance [cm];#delta#alpha_{T} resolution [%]",50,0.,5.,200,-100.,100.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";Proton Start Point - Vertex Distance [cm];#delta#alpha_{T} resolution [%]",100,0.,10.,200,-100.,100.);

//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True P_{#mu};Reco P_{#mu}",100,0.1,1.7,100,0.1,1.7);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";True #delta#alpha_{T} [deg];Reco #delta#alpha_{T} [deg]",90,0,180.,90,0,180.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";P_{#mu} Range Resolution[%]",100,-100.,100.);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";Event",10,2290,2300);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";SubRun",1000,0,1000);

//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";Vertex X [cm]",200,0.,250);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";Vertex Y [cm]",200,-125,125);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";Vertex Z [cm]",500,0,1000);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";Bug Fix Weight",70,0.95,1.5);

//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";manual #theta_{#mu};pandora #theta_{#mu}",180,0.,180,180,0.,180);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";pandora #theta_{#mu}",180,0.,180);
//		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",";manual #theta_{#mu}",180,0.,180);

//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";Muon Start - Vertex Distance [cm];Muon End - Vertex Distance [cm]",100,0.,200.,100,0.,200.);
//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";Proton Start - Vertex Distance [cm];Proton End - Vertex Distance [cm]",100,0.,200.,100,0.,200.);

//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";Muon Z Start [cm];Muon Z End [cm]",100,0.,1000,100,0.,1000);

//		TH2D* PlaygroundPlot = new TH2D("PlaygroundPlot",";Muon X Start [cm];Muon Y Start [cm]",100,0,250,100,-120,120);

//		tree->Draw("TMath::ACos(CandidateMu_CosTheta)*180./TMath::Pi()>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("CandidateMu_Phi>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("(CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("TMath::ACos(CandidateP_CosTheta)*180./TMath::Pi()>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("CandidateP_Phi>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("CandidateP_P_Range>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("Reco_DeltaTheta>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("Reco_DeltaPhi>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("CandidateMu_Length>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("CandidateP_Length>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:TMath::Abs(CandidateP_StartZ-Vertex_Z)>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("CandidateMu_CosTheta:True_CandidateMu_CosTheta>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("CandidateP_CosTheta:True_CandidateP_CosTheta>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("CandidateMu_Phi:True_CandidateMu_Phi>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("CandidateP_Phi:True_CandidateP_Phi>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("TMath::ACos(CandidateMu_CosTheta)*180./TMath::Pi():TMath::ACos(True_CandidateMu_CosTheta)*180./TMath::Pi()>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("TMath::ACos(CandidateP_CosTheta)*180./TMath::Pi():TMath::ACos(True_CandidateP_CosTheta)*180./TMath::Pi()>>PlaygroundPlot",qualifier + " && Reco_DeltaPhiT < 30","goff");
//		tree->Draw("Reco_DeltaPhiT:Reco_Pt>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("( (CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS ) * sin(TMath::ACos(CandidateMu_CosTheta)):True_CandidateMu_P * sin(TMath::ACos(True_CandidateMu_CosTheta))>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("CandidateMu_P_Range * sin(TMath::ACos(CandidateMu_CosTheta)):True_CandidateMu_P * sin(TMath::ACos(True_CandidateMu_CosTheta))>>PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 1","goff");
//		tree->Draw("CandidateP_P_Range * sin(TMath::ACos(CandidateP_CosTheta)):True_CandidateP_P * sin(TMath::ACos(True_CandidateP_CosTheta))>>PlaygroundPlot",qualifier,"goff");

//TMath::Sqrt( TMath::Power(CandidateMu_EndX - CandidateMu_StartX,2.) + TMath::Power(CandidateMu_EndY - CandidateMu_StartY,2.) ) )

//		tree->Draw("CandidateMu_Theta*180./TMath::Pi():TMath::ATan( TMath::Power(CandidateMu_EndX - CandidateMu_StartX,2.) + TMath::Power(CandidateMu_EndY - CandidateMu_StartY,2.) / (CandidateMu_EndZ - CandidateMu_StartZ)  ) * 180./TMath::Pi() >> PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 0 && TMath::Abs(Reco_DeltaAlphaT-True_DeltaAlphaT) > 150","goff");

		//tree->Draw("CandidateMu_Theta*180./TMath::Pi() >> PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 0 && TMath::Abs(Reco_DeltaAlphaT-True_DeltaAlphaT) > 150","goff");

//		tree->Draw("TMath::ATan( TMath::Power(CandidateMu_EndX - CandidateMu_StartX,2.) + TMath::Power(CandidateMu_EndY - CandidateMu_StartY,2.) / (CandidateMu_EndZ - CandidateMu_StartZ)  ) * 180./TMath::Pi() >> PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 0 && TMath::Abs(Reco_DeltaAlphaT-True_DeltaAlphaT) > 150","goff");

//		tree->Draw("CandidateMu_EndZ:CandidateMu_StartZ >> PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 0 && TMath::Abs(Reco_DeltaAlphaT-True_DeltaAlphaT) > 150 && CandidateMu_EndZ > CandidateMu_StartZ + 200  ","goff");

//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 1","goff");
//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 1 && TMath::Abs(CandidateMu_P_Range - CandidateMu_P_MCS) / CandidateMu_P_Range < 0.25","goff");
//		tree->Draw("Reco_Pt:True_Pt>>PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 1","goff");
//		tree->Draw("Reco_Pt:True_Pt>>PlaygroundPlot",qualifier +" && ((CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) > True_CandidateMu_P -0.1 && ((CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) < True_CandidateMu_P +0.1","goff");
//		tree->Draw("Reco_DeltaTheta>>PlaygroundPlot",qualifier+" && ( ((CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) < True_CandidateMu_P -0.1 || ((CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) > True_CandidateMu_P +0.1)","goff");

//		tree->Draw("(CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS:True_CandidateMu_P>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("(CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS:True_CandidateMu_P>>PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 1","goff");
//		tree->Draw("(CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS:True_CandidateMu_P>>PlaygroundPlot",qualifier +" && ((CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) > True_CandidateMu_P -0.1 && ((CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) < True_CandidateMu_P +0.1","goff");

//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier +" && CandidateMu_EndContainment == 1","goff");
//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier +" && ((CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) > True_CandidateMu_P -0.1 && ((CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) < True_CandidateMu_P +0.1","goff");

//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier +" && TMath::Abs(CandidateMu_P_Range - True_CandidateMu_P ) / True_CandidateMu_P < 0.15  && CandidateMu_EndContainment == 1","goff");

//		tree->Draw("CandidateMu_P_Range:True_CandidateMu_P>>PlaygroundPlot",qualifier + " && TMath::Abs(CandidateMu_P_Range - True_CandidateMu_P ) / True_CandidateMu_P < 0.15  && CandidateMu_EndContainment == 1","goff");

//		tree->Draw("CandidateMu_P_Range:True_CandidateMu_P>>PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 1 && TMath::Abs(Reco_DeltaTheta - 90) < 55","goff");

//		tree->Draw("CandidateMu_P_MCS:True_CandidateMu_P>>PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 0","goff");

//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier +" && CandidateMu_EndContainment == 0","goff");

//&& CandidateMu_EndZ > CandidateMu_StartZ + 100
//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier +" && CandidateMu_EndContainment == 0 && TMath::Abs(CandidateMu_EndZ - CandidateMu_StartZ) > 50","goff");

//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier,"goff");

//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier +" && ( CandidateMu_EndContainment == 0 || (CandidateMu_EndContainment == 1 && TMath::Abs(CandidateMu_P_Range - CandidateMu_P_MCS ) < 0.1) )","goff");

//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier +" && (CandidateMu_EndContainment == 1 )","goff");

//		tree->Draw("(CandidateMu_P_MCS-True_CandidateMu_P)/True_CandidateMu_P*100.>>PlaygroundPlot",qualifier +" && (CandidateMu_EndContainment == 1 )","goff");
//		tree->Draw("Event>>PlaygroundPlot",qualifier +"  && TMath::Abs(CandidateMu_P_Range - True_CandidateMu_P ) / True_CandidateMu_P > 0.15  && CandidateMu_EndContainment == 1 && Run == 7054 && SubRun == 2020","goff");

//		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:CandidateMuP_Distance>>PlaygroundPlot",qualifier,"goff");

//		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:CandidateMu_StartZ - Vertex_Z>>PlaygroundPlot",qualifier,"goff");

//		tree->Draw("CandidateMu_Length.:True_CandidateMu_Length>>PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 1","goff");

//		tree->Draw("CandidateP_Length.:True_CandidateP_Length>>PlaygroundPlot",qualifier,"goff");

//		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:CandidateMu_CosTheta>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:CandidateP_CosTheta>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:CandidateMuVertexDistance>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.:CandidatePVertexDistance>>PlaygroundPlot",qualifier,"goff");

//		tree->Draw("CandidateMuEndVertexDistance.:CandidateMuStartVertexDistance>>PlaygroundPlot",qualifier,"goff");
//		tree->Draw("CandidatePEndVertexDistance.:CandidatePStartVertexDistance>>PlaygroundPlot",qualifier,"goff");

//		tree->Draw("T2KWeight>>PlaygroundPlot",qualifier,"goff");

//		tree->Draw("CandidateMu_StartY:CandidateMu_StartX>>PlaygroundPlot",qualifier,"goff");

//		tree->Draw("CandidateMu_P_Range:True_CandidateMu_P>>PlaygroundPlot",qualifier + " && TMath::Abs(CandidateMu_P_Range - CandidateMu_P_MCS ) / CandidateMu_P_Range < 0.25  && CandidateMu_EndContainment == 1","goff");
//		tree->Draw("CandidateMu_P_MCS:True_CandidateMu_P>>PlaygroundPlot",qualifier + " && CandidateMu_EndContainment == 0 && ( (CandidateMu_StartZ < 650 && CandidateMu_EndZ < 650) || (CandidateMu_StartZ > 750 && CandidateMu_EndZ > 750)  ) ","goff");

//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier +" && CandidateMu_EndContainment == 1 && TMath::Abs(CandidateMu_P_Range - CandidateMu_P_MCS ) / CandidateMu_P_Range < 0.25","goff");

//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>PlaygroundPlot",qualifier +" && CandidateMu_EndContainment == 0 && (Vertex_Z < 675 || Vertex_Z < 775) ","goff");

//		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>PlaygroundPlot",qualifier +" && CandidateMu_EndContainment == 1 && TMath::Abs(CandidateMu_P_Range - CandidateMu_P_MCS ) / CandidateMu_P_Range < 0.25","goff");

		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>PlaygroundPlot",qualifier +" && CandidateMu_EndContainment == 0 && CandidateMu_Length>100","goff");

//		tree->Draw("Vertex_Z>>PlaygroundPlot",qualifier +" && CandidateMu_EndContainment == 0 && TMath::Abs(Reco_DeltaAlphaT-True_DeltaAlphaT) > 140","goff");

//		tree->Draw("CandidateMu_Phi>>PlaygroundPlot",qualifier + " && (Vertex_Z < 650 || Vertex_Z > 750) ","goff");

		cout << "Events = " << PlaygroundPlot->Integral() << endl;

//		PlaygroundPlot->Draw("coltz");
		PlaygroundPlot->Draw();

		// ---------------------------------------------------------------------------------------------------------------------------------------

//		TCanvas* OverlayCanvas = new TCanvas("OverlayCanvas"+Runs[WhichRun],"OverlayCanvas"+Runs[WhichRun],205,34,1024,768);

//		int NPlots = 10;
//		TH1D* PlaygroundPlots[NPlots];

//		TLegend* leg = new TLegend(0.2,0.3,0.4,0.5);

//		for (int i = 0; i < 20; i++) {

//			PlaygroundPlots[i] = new TH1D("PlaygroundPlot_"+TString(std::to_string(i)),";#delta#alpha_{T} resolution[%];",200,-100.,100.);
//			TString MinLength = TString(std::to_string(10*i));
//			tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.>>PlaygroundPlot_"+TString(std::to_string(i)),qualifier +" && CandidateMu_EndContainment == 0 && CandidateMu_Length>"+MinLength,"goff");

//			PlaygroundPlots[i]->SetLineColor(i+1);
//			PlaygroundPlots[i]->SetLineWidth(3);
//			PlaygroundPlots[i]->Scale(1./PlaygroundPlots[i]->GetMaximum());
//			PlaygroundPlots[i]->Draw("hist same");

//			leg->AddEntry(PlaygroundPlots[i],MinLength+" cm","l");

//		}

//		leg->SetTextSize(0.05);
//		leg->Draw();

		// ---------------------------------------------------------------------------------------------------------------------------------------
/*
		// 1D Phi_p Projection in P_P Slices
	
		TH1D* PhiPReso_LowMomP = new TH1D("PhiPReso_LowMomP",";#phi_{p} resolution [%]",100,-100.,100.);
		TH1D* PhiPReso_MedMomP = new TH1D("PhiPReso_MedMomP",";#phi_{p} resolution [%]",100,-100.,100.);
		TH1D* PhiPReso_HighMomP = new TH1D("PhiPReso_HighMomP",";#phi_{p} resolution [%]",100,-100.,100.);

		tree->Draw("(CandidateP_Phi-True_CandidateP_Phi)/True_CandidateP_Phi*100.>>PhiPReso_LowMomP",qualifier + " && CandidateP_P_Range < 0.4","goff");
		tree->Draw("(CandidateP_Phi-True_CandidateP_Phi)/True_CandidateP_Phi*100.>>PhiPReso_MedMomP",qualifier + " && CandidateP_P_Range > 0.4 && CandidateP_P_Range < 0.8","goff");	
		tree->Draw("(CandidateP_Phi-True_CandidateP_Phi)/True_CandidateP_Phi*100.>>PhiPReso_HighMomP",qualifier + " && CandidateP_P_Range > 0.8","goff");

		TCanvas* PhiPReso_PhiTSlices_Canvas = new TCanvas("PhiPReso_MomPSlices_Canvas_"+Runs[WhichRun],"PhiPReso_Slices_Canvas_"+Runs[WhichRun],205,34,1024,768);

		PhiPReso_LowMomP->GetXaxis()->CenterTitle();
		PhiPReso_LowMomP->GetYaxis()->CenterTitle();
		PhiPReso_LowMomP->GetYaxis()->SetTitle("Arbitrary Units");

		PhiPReso_LowMomP->SetLineColor(kBlue+2);
		PhiPReso_LowMomP->SetMarkerColor(kBlue+2);
		PhiPReso_LowMomP->SetMarkerSize(2.);
		PhiPReso_LowMomP->SetMarkerStyle(20);
		PhiPReso_LowMomP->Scale(1./PhiPReso_LowMomP->GetMaximum());
		PhiPReso_LowMomP->Draw("p0 hist same");

		PhiPReso_MedMomP->SetLineColor(kGreen+1);
		PhiPReso_MedMomP->SetMarkerColor(kGreen+1);
		PhiPReso_MedMomP->SetMarkerSize(2.);
		PhiPReso_MedMomP->SetMarkerStyle(20);
		PhiPReso_MedMomP->Scale(1./PhiPReso_MedMomP->GetMaximum());
		PhiPReso_MedMomP->Draw("p0 hist same");

		PhiPReso_HighMomP->SetLineColor(kOrange+7);
		PhiPReso_HighMomP->SetMarkerColor(kOrange+7);
		PhiPReso_HighMomP->SetMarkerSize(2.);
		PhiPReso_HighMomP->SetMarkerStyle(20);
		PhiPReso_HighMomP->Scale(1./PhiPReso_HighMomP->GetMaximum());
		PhiPReso_HighMomP->Draw("p0 hist same");


		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		TLegend* leg_PhiPReso_PhiTSlices = new TLegend(0.55,0.65,0.85,0.85);
		leg_PhiPReso_PhiTSlices->SetBorderSize(0);
		leg_PhiPReso_PhiTSlices->SetTextFont(132);
		leg_PhiPReso_PhiTSlices->SetTextSize(0.05);

		leg_PhiPReso_PhiTSlices->AddEntry(PhiPReso_LowMomP,"P_{p} < 0.4 [GeV/c]","p");
		leg_PhiPReso_PhiTSlices->AddEntry(PhiPReso_MedMomP,"0.4 < P_{p} < 0.8 [GeV/c]","p");
		leg_PhiPReso_PhiTSlices->AddEntry(PhiPReso_HighMomP,"P_{p} > 0.8 [GeV/c]","p");
		leg_PhiPReso_PhiTSlices->Draw();

		//PhiPReso_PhiTSlices_Canvas->SaveAs(PlotPath+"PhiPReso_MomPSlices_Canvas_"+Runs[WhichRun]+".pdf");
		//delete PhiPReso_PhiTSlices_Canvas;
*/

		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
