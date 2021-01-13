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

void TwoDPlots() {

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetTitleSize(0.0,"t");
	gStyle->SetTitleFont(132,"t");

	gStyle->SetTitleOffset(0.9,"xyz");
	gStyle->SetTitleSize(0.05,"xyz");
	gStyle->SetTitleFont(132,"xyz");
	gStyle->SetLabelSize(0.05,"xyz");
	gStyle->SetLabelFont(132,"xyz");
	gStyle->SetNdivisions(5,"xyz");

	gStyle->SetOptStat(0);

	gROOT->ForceStyle();

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<TString> Runs{"Run1"};
//	std::vector<TString> Runs{"Run1","Run3"};
//	std::vector<TString> Runs{"Run1","Run2","Run3","Run4","Run5"};

	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		TFile* OverlayFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

		TString qualifier = "CC1p && CandidateMu_MCParticle_Pdg == 13 && CandidateP_MCParticle_Pdg == 2212 && CandidateMu_StartContainment == 1 && CandidateP_StartContainment == 1 && CandidateP_EndContainment == 1 && True_CandidateMu_StartContainment == 1";

		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Muon Momentum MCS

		TH2D* hMuonMomMCS = new TH2D("hMuonMomMCS",";True Muon Momentum [GeV/c]; MCS Reco Muon Momentum [GeV/c]",400,0,2,400,0,2);

		tree->Draw("CandidateMu_P_MCS:True_CandidateMu_P>>hMuonMomMCS",qualifier+ " && CandidateMu_EndContainment == 0","goff");

		TCanvas* MuonMomentumMCSCanvas = new TCanvas("MuonMomentumMCSCanvas","MuonMomentumMCSCanvas",205,34,1024,768);
		MuonMomentumMCSCanvas->cd();
		hMuonMomMCS->SetTitle("Exiting Candidate Muon Tracks");
		hMuonMomMCS->SetTitleSize(0.08,"t");
		hMuonMomMCS->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonMomentumMCSCanvas->SaveAs(PlotPath+"MuonMomentumMCS2DCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Muon Momentum Range

		TH2D* hMuonMomRange = new TH2D("hMuonMomRange",";True Muon Momentum [GeV/c]; Range Reco Muon Momentum [GeV/c]",400,0,2,400,0,2);

		tree->Draw("CandidateMu_P_Range:True_CandidateMu_P>>hMuonMomRange",qualifier+ " && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonMomentumRangeCanvas = new TCanvas("MuonMomentumRangeCanvas","MuonMomentumRangeCanvas",205,34,1024,768);
		MuonMomentumRangeCanvas->cd();
		hMuonMomRange->SetTitle("Contained Candidate Muon Tracks");
		hMuonMomRange->SetTitleSize(0.08,"t");
		hMuonMomRange->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonMomentumRangeCanvas->SaveAs(PlotPath+"MuonMomentum2DRangeCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Muon CosTheta

		TH2D* hMuonCosTheta = new TH2D("hMuonCosTheta",";True Muon cos(#theta);Reco Muon cos(#theta)",400,-1,1,400,-1,1);

		tree->Draw("CandidateMu_CosTheta:True_CandidateMu_CosTheta>>hMuonCosTheta",qualifier,"goff");

		TCanvas* MuonCosThetaCanvas = new TCanvas("MuonCosThetaCanvas","MuonCosThetaCanvas",205,34,1024,768);
		MuonCosThetaCanvas->cd();
		hMuonCosTheta->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonCosThetaCanvas->SaveAs(PlotPath+"MuonCosThetaCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Muon Phi

		TH2D* hMuonPhi = new TH2D("hMuonPhi",";True Muon #phi [deg];Reco Muon #phi [deg]",360,-180,180,360,-180,180);

		tree->Draw("CandidateMu_Phi:True_CandidateMu_Phi>>hMuonPhi",qualifier,"goff");

		TCanvas* MuonPhiCanvas = new TCanvas("MuonPhiCanvas","MuonPhiCanvas",205,34,1024,768);
		MuonPhiCanvas->cd();
		hMuonPhi->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonPhiCanvas->SaveAs(PlotPath+"MuonPhiCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Proton Momentum Range

		TH2D* hProtonMomRange = new TH2D("hProtonMomRange",";True Proton Momentum [GeV/c];Range Reco Proton Momentum [GeV/c]",400,0,2,400,0,2);

		tree->Draw("CandidateP_P_Range:True_CandidateP_P>>hProtonMomRange",qualifier,"goff");

		TCanvas* ProtonMomentumRangeCanvas = new TCanvas("ProtonMomentumRangeCanvas","ProtonMomentumRangeCanvas",205,34,1024,768);
		ProtonMomentumRangeCanvas->cd();
		hProtonMomRange->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ProtonMomentumRangeCanvas->SaveAs(PlotPath+"ProtonMomentum2DRangeCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Proton CosTheta

		TH2D* hProtonCosTheta = new TH2D("hProtonCosTheta",";True Proton cos(#theta);Reco Proton cos(#theta)",400,-1,1,400,-1,1);

		tree->Draw("CandidateP_CosTheta:True_CandidateP_CosTheta>>hProtonCosTheta",qualifier,"goff");

		TCanvas* ProtonCosThetaCanvas = new TCanvas("ProtonCosThetaCanvas","ProtonCosThetaCanvas",205,34,1024,768);
		ProtonCosThetaCanvas->cd();
		hProtonCosTheta->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ProtonCosThetaCanvas->SaveAs(PlotPath+"ProtonCosThetaCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Proton Phi

		TH2D* hProtonPhi = new TH2D("hProtonPhi",";True Proton #phi [deg];Reco Proton #phi [deg]",360,-180,180,360,-180,180);

		tree->Draw("CandidateP_Phi:True_CandidateP_Phi>>hProtonPhi",qualifier,"goff");

		TCanvas* ProtonPhiCanvas = new TCanvas("ProtonPhiCanvas","ProtonPhiCanvas",205,34,1024,768);
		ProtonPhiCanvas->cd();
		hProtonPhi->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ProtonPhiCanvas->SaveAs(PlotPath+"ProtonPhiCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Transverse Missing Momentum

		TH2D* hPt = new TH2D("hPt",";True P_{T} [GeV/c];Reco P_{T} [GeV/c]",400,0,1,400,0,1);

		TCanvas* PtCanvas = new TCanvas("PTCanvas","PTCanvas",205,34,1024,768);
		PtCanvas->cd();

		tree->Draw("Reco_Pt:True_Pt>>hPt",qualifier,"goff");
		hPt->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		PtCanvas->SaveAs(PlotPath+"PtCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Delta AlphaT

		TH2D* hDeltaAlphaT = new TH2D("hDeltaAlphaT",";True #delta#alpha_{T} [deg];Reco #delta#alpha_{T} [deg]",360,0,180,360,0,180);

		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>hDeltaAlphaT",qualifier,"goff");

		TCanvas* DeltaAlphaTCanvas = new TCanvas("DeltaAlphaTCanvas","DeltaAlphaTCanvas",205,34,1024,768);
		DeltaAlphaTCanvas->cd();
		hDeltaAlphaT->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		DeltaAlphaTCanvas->SaveAs(PlotPath+"DeltaAlphaTCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Delta PhiT

		TH2D* hDeltaPhiT = new TH2D("hDeltaPhiT",";True #delta#phi_{T} [deg];Reco #delta#phi_{T} [deg]",360,0,180,360,0,180);

		tree->Draw("Reco_DeltaPhiT:True_DeltaPhiT>>hDeltaPhiT",qualifier,"goff");

		TCanvas* DeltaPhiTCanvas = new TCanvas("DeltaPhiTCanvas","DeltaPhiTCanvas",205,34,1024,768);
		DeltaPhiTCanvas->cd();
		hDeltaPhiT->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		DeltaPhiTCanvas->SaveAs(PlotPath+"DeltaPhiTCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// kMiss

		TH2D* hkMiss = new TH2D("hkMiss",";True k_{Miss} [GeV/c];Reco k_{Miss} [GeV/c]",400,0,1,400,0,1);

		tree->Draw("Reco_kMiss:True_kMiss>>hkMiss",qualifier,"goff");

		TCanvas* kMissCanvas = new TCanvas("kMissCanvas","kMissCanvas",205,34,1024,768);
		kMissCanvas->cd();
		hkMiss->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		kMissCanvas->SaveAs(PlotPath+"kMissCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// PMiss

		TH2D* hPMiss = new TH2D("hPMiss",";True P_{Miss} [GeV/c];Reco P_{Miss} [GeV/c]",450,0,1.5,450,0,1.5);

		tree->Draw("Reco_PMiss:True_PMiss>>hPMiss",qualifier,"goff");

		TCanvas* PMissCanvas = new TCanvas("PMissCanvas","PMissCanvas",205,34,1024,768);
		PMissCanvas->cd();
		hPMiss->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		PMissCanvas->SaveAs(PlotPath+"PMissCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// PMissMinus

		TH2D* hPMissMinus = new TH2D("hPMissMinus",";True P^{-}_{Miss} [GeV/c];Reco P^{-}_{Miss} [GeV/c]",450,0,1.5,450,0,1.5);

		tree->Draw("Reco_PMissMinus:True_PMissMinus>>hPMissMinus",qualifier,"goff");

		TCanvas* PMissMinusCanvas = new TCanvas("PMissMinusCanvas","PMissMinusCanvas",205,34,1024,768);
		PMissMinusCanvas->cd();
		hPMissMinus->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		PMissMinusCanvas->SaveAs(PlotPath+"PMissMinusCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// ECal

		TH2D* hECal = new TH2D("hECal",";True E^{cal} [GeV];Reco E^{cal} [GeV]",400,0,2,400,0,2);

		tree->Draw("Reco_ECal:True_ECal>>hECal",qualifier,"goff");

		TCanvas* ECalCanvas = new TCanvas("ECalCanvas","ECalCanvas",205,34,1024,768);
		ECalCanvas->cd();
		hECal->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ECalCanvas->SaveAs(PlotPath+"ECalCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// EQE

		TH2D* hEQE = new TH2D("hEQE",";True E^{QE} [GeV];Reco E^{QE} [GeV]",400,0,2,400,0,2);

		tree->Draw("Reco_EQE:True_EQE>>hEQE",qualifier,"goff");

		TCanvas* EQECanvas = new TCanvas("EQECanvas","EQECanvas",205,34,1024,768);
		EQECanvas->cd();
		hEQE->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		EQECanvas->SaveAs(PlotPath+"EQECanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// DeltaPhi

		TH2D* hDeltaPhi = new TH2D("hDeltaPhi",";True #delta#phi_{#mu,p} [deg];Reco #delta#phi_{#mu,p} [deg]",360,0,360,360,0,360);

		tree->Draw("Reco_DeltaPhi:True_DeltaPhi>>hDeltaPhi",qualifier,"coltz");

		TCanvas* DeltaPhiCanvas = new TCanvas("DeltaPhiCanvas","DeltaPhiCanvas",205,34,1024,768);
		DeltaPhiCanvas->cd();
		hDeltaPhi->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		DeltaPhiCanvas->SaveAs(PlotPath+"DeltaPhiCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// DeltaTheta

		TH2D* hDeltaTheta = new TH2D("hDeltaTheta",";True #delta#theta_{#mu,p} [deg];Reco #delta#theta_{#mu,p} [deg]",360,0,180,360,0,180);

		tree->Draw("Reco_DeltaTheta:True_DeltaTheta>>hDeltaTheta",qualifier,"goff");

		TCanvas* DeltaThetaCanvas = new TCanvas("DeltaThetaCanvas","DeltaThetaCanvas",205,34,1024,768);
		DeltaThetaCanvas->cd();
		hDeltaTheta->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		DeltaThetaCanvas->SaveAs(PlotPath+"DeltaThetaCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Muon Start X

		TH2D* hMuonStartX = new TH2D("hMuonStartX",";True Muon Start X [cm];Reco Muon Start X [cm]",300,-10,290,300,-10,290);

		tree->Draw("CandidateMu_StartX:True_CandidateMu_StartX>>hMuonStartX",qualifier,"goff");

		TCanvas* MuonStartXCanvas = new TCanvas("MuonStartXCanvas","MuonStartXCanvas",205,34,1024,768);
		MuonStartXCanvas->cd();
		hMuonStartX->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonStartXCanvas->SaveAs(PlotPath+"MuonStartXCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Muon Start Y

		TH2D* hMuonStartY = new TH2D("hMuonStartY",";True Muon Start Y [cm];Reco Muon Start Y [cm]",300,-150,150,300,-150,150);

		tree->Draw("CandidateMu_StartY:True_CandidateMu_StartY>>hMuonStartY",qualifier,"goff");

		TCanvas* MuonStartYCanvas = new TCanvas("MuonStartYCanvas","MuonStartYCanvas",205,34,1024,768);
		MuonStartYCanvas->cd();
		hMuonStartY->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonStartYCanvas->SaveAs(PlotPath+"MuonStartYCanvas_"+Runs[WhichRun]+".pdf");\

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Muon Start Z

		TH2D* hMuonStartZ = new TH2D("hMuonStartZ",";True Muon Start Z [cm];Reco Muon Start Z [cm]",1200,-50,1150,1200,-50,1150);

		tree->Draw("CandidateMu_StartZ:True_CandidateMu_StartZ>>hMuonStartZ",qualifier,"goff");

		TCanvas* MuonStartZCanvas = new TCanvas("MuonStartZCanvas","MuonStartZCanvas",205,34,1024,768);
		MuonStartZCanvas->cd();
		hMuonStartZ->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonStartZCanvas->SaveAs(PlotPath+"MuonStartZCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Proton Start X

		TH2D* hProtonStartX = new TH2D("hProtonStartX",";True Proton Start X [cm];Reco Proton Start X [cm]",300,-10,290,300,-10,290);

		tree->Draw("CandidateP_StartX:True_CandidateP_StartX>>hProtonStartX",qualifier,"goff");

		TCanvas* ProtonStartXCanvas = new TCanvas("ProtonStartXCanvas","ProtonStartXCanvas",205,34,1024,768);
		ProtonStartXCanvas->cd();
		hProtonStartX->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ProtonStartXCanvas->SaveAs(PlotPath+"ProtonStartXCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Proton Start Y

		TH2D* hProtonStartY = new TH2D("hProtonStartY",";True Proton Start Y [cm];Reco Proton Start Y [cm]",300,-150,150,300,-150,150);

		tree->Draw("CandidateP_StartY:True_CandidateP_StartY>>hProtonStartY",qualifier,"goff");

		TCanvas* ProtonStartYCanvas = new TCanvas("ProtonStartYCanvas","ProtonStartYCanvas",205,34,1024,768);
		ProtonStartYCanvas->cd();
		hProtonStartY->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ProtonStartYCanvas->SaveAs(PlotPath+"ProtonStartYCanvas_"+Runs[WhichRun]+".pdf");\

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Proton Start Z

		TH2D* hProtonStartZ = new TH2D("hProtonStartZ",";True Proton Start Z [cm];Reco Proton Start Z [cm]",1200,-50,1150,1200,-50,1150);

		tree->Draw("CandidateP_StartZ:True_CandidateP_StartZ>>hProtonStartZ",qualifier,"goff");

		TCanvas* ProtonStartZCanvas = new TCanvas("ProtonStartZCanvas","ProtonStartZCanvas",205,34,1024,768);
		ProtonStartZCanvas->cd();
		hProtonStartZ->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ProtonStartZCanvas->SaveAs(PlotPath+"ProtonStartZCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		//  Muon End X

		TH2D* hMuonEndX = new TH2D("hMuonEndX",";True Muon End X [cm];Reco Muon End X [cm]",300,-10,290,300,-10,290);

		tree->Draw("CandidateMu_EndX:True_CandidateMu_EndX>>hMuonEndX",qualifier+" && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonEndXCanvas = new TCanvas("MuonEndXCanvas","MuonEndXCanvas",205,34,1024,768);
		MuonEndXCanvas->cd();
		hMuonEndX->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonEndXCanvas->SaveAs(PlotPath+"MuonEndXCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Muon End Y

		TH2D* hMuonEndY = new TH2D("hMuonEndY",";True Muon End Y [cm];Reco Muon End Y [cm]",300,-150,150,300,-150,150);

		tree->Draw("CandidateMu_EndY:True_CandidateMu_EndY>>hMuonEndY",qualifier,"goff");

		TCanvas* MuonEndYCanvas = new TCanvas("MuonEndYCanvas","MuonEndYCanvas",205,34,1024,768);
		MuonEndYCanvas->cd();
		hMuonEndY->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonEndYCanvas->SaveAs(PlotPath+"MuonEndYCanvas_"+Runs[WhichRun]+".pdf");\

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Muon End Z

		TH2D* hMuonEndZ = new TH2D("hMuonEndZ",";True Muon End Z [cm];Reco Muon End Z [cm]",1200,-50,1150,1200,-50,1150);

		tree->Draw("CandidateMu_EndZ:True_CandidateMu_EndZ>>hMuonEndZ",qualifier,"goff");

		TCanvas* MuonEndZCanvas = new TCanvas("MuonEndZCanvas","MuonEndZCanvas",205,34,1024,768);
		MuonEndZCanvas->cd();
		hMuonEndZ->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		MuonEndZCanvas->SaveAs(PlotPath+"MuonEndZCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Proton End X

		TH2D* hProtonEndX = new TH2D("hProtonEndX",";True Proton End X [cm];Reco Proton End X [cm]",300,-10,290,300,-10,290);

		tree->Draw("CandidateP_EndX:True_CandidateP_EndX>>hProtonEndX",qualifier,"goff");

		TCanvas* ProtonEndXCanvas = new TCanvas("ProtonEndXCanvas","ProtonEndXCanvas",205,34,1024,768);
		ProtonEndXCanvas->cd();
		hProtonEndX->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ProtonEndXCanvas->SaveAs(PlotPath+"ProtonEndXCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Proton End Y

		TH2D* hProtonEndY = new TH2D("hProtonEndY",";True Proton End Y [cm];Reco Proton End Y [cm]",300,-150,150,300,-150,150);

		tree->Draw("CandidateP_EndY:True_CandidateP_EndY>>hProtonEndY",qualifier,"goff");

		TCanvas* ProtonEndYCanvas = new TCanvas("ProtonEndYCanvas","ProtonEndYCanvas",205,34,1024,768);
		ProtonEndYCanvas->cd();
		hProtonEndY->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ProtonEndYCanvas->SaveAs(PlotPath+"ProtonEndYCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Proton End Z

		TH2D* hProtonEndZ = new TH2D("hProtonEndZ",";True Proton End Z [cm];Reco Proton End Z [cm]",1200,-50,1150,1200,-50,1150);

		tree->Draw("CandidateP_EndZ:True_CandidateP_EndZ>>hProtonEndZ",qualifier,"goff");

		TCanvas* ProtonEndZCanvas = new TCanvas("ProtonEndZCanvas","ProtonEndZCanvas",205,34,1024,768);
		ProtonEndZCanvas->cd();
		hProtonEndZ->Draw("coltz");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		ProtonEndZCanvas->SaveAs(PlotPath+"ProtonEndZCanvas_"+Runs[WhichRun]+".pdf");

		// ----------------------------------------------------------------------------------------------------------------------------------------------------------

		// Bonus Plot: 1D μ-p distance 

		TH1D* hMuPDistance = new TH1D("hMuPDistance",";reco #mu-p distance [cm]",23,-0.5,11.5);

		tree->Draw("CandidateMuP_Distance>>hMuPDistance",qualifier,"goff");

		TCanvas* CandidateMuP_DistanceCanvas = new TCanvas("CandidateMuP_DistanceCanvas","CandidateMuP_DistanceCanvas",205,34,1024,768);
		CandidateMuP_DistanceCanvas->SetLeftMargin(0.15);
		CandidateMuP_DistanceCanvas->cd();
		hMuPDistance->SetTitle("MicroBooNE Simulation (CC1p Events)");
		hMuPDistance->GetYaxis()->SetTitle("# Pairs / Bin");
		hMuPDistance->GetYaxis()->SetTitleOffset(1.35);
		hMuPDistance->SetLineColor(kBlue-6);
		hMuPDistance->SetFillColor(kBlue-6);
		hMuPDistance->Draw("hist");

		text->DrawTextNDC(0.47, 0.83, Runs[WhichRun]);

		CandidateMuP_DistanceCanvas->SaveAs(PlotPath+"CandidateMuP_DistanceCanvas_"+Runs[WhichRun]+".pdf");

	} // End of the loop over the runs

} // End of the program 
