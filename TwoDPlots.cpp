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

	TString RunNumber = "Run1";
//	TString RunNumber = "Run2";
//	TString RunNumber = "Run3";
//	TString RunNumber = "Run4";
//	TString RunNumber = "Run5";

	TFile* OverlayFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+RunNumber+"_"+UBCodeVersion+".root","readonly");
	TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

	TString qualifier = "CC1p && CandidateMu_MCParticle_Pdg == 13 && CandidateP_MCParticle_Pdg == 2212 && CandidateMu_StartContainment == 1 && CandidateP_StartContainment == 1 && CandidateP_EndContainment == 1 && True_CandidateMu_StartContainment == 1 && True_CandidateP_StartContainment == 1 && True_CandidateP_EndContainment == 1";

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Momentum MCS

	TH2D* hMuonMomMCS = new TH2D("hMuonMomMCS",";True Muon Momentum [GeV/c]; MCS Reco Muon Momentum [GeV/c]",400,0,2,400,0,2);

	tree->Draw("CandidateMu_P_MCS:True_CandidateMu_P>>hMuonMomMCS",qualifier+ " && CandidateMu_EndContainment == 0","goff");

	TCanvas* MuonMomentumMCSCanvas = new TCanvas("MuonMomentumMCSCanvas","MuonMomentumMCSCanvas",205,34,1024,768);
	MuonMomentumMCSCanvas->cd();
	hMuonMomMCS->SetTitle("Exiting Candidate Muon Tracks");
	hMuonMomMCS->SetTitleSize(0.08,"t");
	hMuonMomMCS->Draw("coltz");

	MuonMomentumMCSCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonMomentumMCS2DCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Momentum Range

	TH2D* hMuonMomRange = new TH2D("hMuonMomRange",";True Muon Momentum [GeV/c]; Range Reco Muon Momentum [GeV/c]",400,0,2,400,0,2);

	tree->Draw("CandidateMu_P_Range:True_CandidateMu_P>>hMuonMomRange",qualifier+ " && CandidateMu_EndContainment == 1","goff");

	TCanvas* MuonMomentumRangeCanvas = new TCanvas("MuonMomentumRangeCanvas","MuonMomentumRangeCanvas",205,34,1024,768);
	MuonMomentumRangeCanvas->cd();
	hMuonMomRange->SetTitle("Contained Candidate Muon Tracks");
	hMuonMomRange->SetTitleSize(0.08,"t");
	hMuonMomRange->Draw("coltz");

	MuonMomentumRangeCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonMomentum2DRangeCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon CosTheta

	TH2D* hMuonCosTheta = new TH2D("hMuonCosTheta",";True Muon cos(#theta);Reco Muon cos(#theta)",400,-1,1,400,-1,1);

	tree->Draw("CandidateMu_CosTheta:True_CandidateMu_CosTheta>>hMuonCosTheta",qualifier,"goff");

	TCanvas* MuonCosThetaCanvas = new TCanvas("MuonCosThetaCanvas","MuonCosThetaCanvas",205,34,1024,768);
	MuonCosThetaCanvas->cd();
	hMuonCosTheta->Draw("coltz");

	MuonCosThetaCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonCosThetaCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Phi

	TH2D* hMuonPhi = new TH2D("hMuonPhi",";True Muon #phi [deg];Reco Muon #phi [deg]",360,-180,180,360,-180,180);

	tree->Draw("CandidateMu_Phi:True_CandidateMu_Phi>>hMuonPhi",qualifier,"goff");

	TCanvas* MuonPhiCanvas = new TCanvas("MuonPhiCanvas","MuonPhiCanvas",205,34,1024,768);
	MuonPhiCanvas->cd();
	hMuonPhi->Draw("coltz");

	MuonPhiCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonPhiCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton Momentum Range

	TH2D* hProtonMomRange = new TH2D("hProtonMomRange",";True Proton Momentum [GeV/c];Range Reco Proton Momentum [GeV/c]",400,0,2,400,0,2);

	tree->Draw("CandidateP_P_Range:True_CandidateP_P>>hProtonMomRange",qualifier,"goff");

	TCanvas* ProtonMomentumRangeCanvas = new TCanvas("ProtonMomentumRangeCanvas","ProtonMomentumRangeCanvas",205,34,1024,768);
	ProtonMomentumRangeCanvas->cd();
	hProtonMomRange->Draw("coltz");

	ProtonMomentumRangeCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonMomentum2DRangeCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton CosTheta

	TH2D* hProtonCosTheta = new TH2D("hProtonCosTheta",";True Proton cos(#theta);Reco Proton cos(#theta)",400,-1,1,400,-1,1);

	tree->Draw("CandidateP_CosTheta:True_CandidateP_CosTheta>>hProtonCosTheta",qualifier,"goff");

	TCanvas* ProtonCosThetaCanvas = new TCanvas("ProtonCosThetaCanvas","ProtonCosThetaCanvas",205,34,1024,768);
	ProtonCosThetaCanvas->cd();
	hProtonCosTheta->Draw("coltz");

	ProtonCosThetaCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonCosThetaCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton Phi

	TH2D* hProtonPhi = new TH2D("hProtonPhi",";True Proton #phi [deg];Reco Proton #phi [deg]",360,-180,180,360,-180,180);

	tree->Draw("CandidateP_Phi:True_CandidateP_Phi>>hProtonPhi",qualifier,"goff");

	TCanvas* ProtonPhiCanvas = new TCanvas("ProtonPhiCanvas","ProtonPhiCanvas",205,34,1024,768);
	ProtonPhiCanvas->cd();
	hProtonPhi->Draw("coltz");

	ProtonPhiCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonPhiCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Transverse Missing Momentum

	TH2D* hPt = new TH2D("hPt",";True P_{T} [GeV/c];Reco P_{T} [GeV/c]",400,0,1,400,0,1);

	TCanvas* PtCanvas = new TCanvas("PTCanvas","PTCanvas",205,34,1024,768);
	PtCanvas->cd();

	tree->Draw("Reco_Pt:True_Pt>>hPt",qualifier,"goff");
	hPt->Draw("coltz");

	PtCanvas->SaveAs("myPlots/"+UBCodeVersion+"/PtCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Delta AlphaT

	TH2D* hDeltaAlphaT = new TH2D("hDeltaAlphaT",";True #delta#alpha_{T} [deg];Reco #delta#alpha_{T} [deg]",360,0,180,360,0,180);

	tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>hDeltaAlphaT",qualifier,"goff");

	TCanvas* DeltaAlphaTCanvas = new TCanvas("DeltaAlphaTCanvas","DeltaAlphaTCanvas",205,34,1024,768);
	DeltaAlphaTCanvas->cd();
	hDeltaAlphaT->Draw("coltz");

	DeltaAlphaTCanvas->SaveAs("myPlots/"+UBCodeVersion+"/DeltaAlphaTCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Delta PhiT

	TH2D* hDeltaPhiT = new TH2D("hDeltaPhiT",";True #delta#phi_{T} [deg];Reco #delta#phi_{T} [deg]",360,0,180,360,0,180);

	tree->Draw("Reco_DeltaPhiT:True_DeltaPhiT>>hDeltaPhiT",qualifier,"goff");

	TCanvas* DeltaPhiTCanvas = new TCanvas("DeltaPhiTCanvas","DeltaPhiTCanvas",205,34,1024,768);
	DeltaPhiTCanvas->cd();
	hDeltaPhiT->Draw("coltz");

	DeltaPhiTCanvas->SaveAs("myPlots/"+UBCodeVersion+"/DeltaPhiTCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// kMiss

	TH2D* hkMiss = new TH2D("hkMiss",";True k_{Miss} [GeV/c];Reco k_{Miss} [GeV/c]",400,0,1,400,0,1);

	tree->Draw("Reco_kMiss:True_kMiss>>hkMiss",qualifier,"goff");

	TCanvas* kMissCanvas = new TCanvas("kMissCanvas","kMissCanvas",205,34,1024,768);
	kMissCanvas->cd();
	hkMiss->Draw("coltz");

	kMissCanvas->SaveAs("myPlots/"+UBCodeVersion+"/kMissCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// PMissMinus

	TH2D* hPMissMinus = new TH2D("hPMissMinus",";True P^{-}_{Miss} [GeV/c];Reco P^{-}_{Miss} [GeV/c]",450,0,1.5,450,0,1.5);

	tree->Draw("Reco_PMissMinus:True_PMissMinus>>hPMissMinus",qualifier,"goff");

	TCanvas* PMissMinusCanvas = new TCanvas("PMissMinusCanvas","PMissMinusCanvas",205,34,1024,768);
	PMissMinusCanvas->cd();
	hPMissMinus->Draw("coltz");

	PMissMinusCanvas->SaveAs("myPlots/"+UBCodeVersion+"/PMissMinusCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// ECal

	TH2D* hECal = new TH2D("hECal",";True E^{cal} [GeV];Reco E^{cal} [GeV]",400,0,2,400,0,2);

	tree->Draw("Reco_ECal:True_ECal>>hECal",qualifier,"goff");

	TCanvas* ECalCanvas = new TCanvas("ECalCanvas","ECalCanvas",205,34,1024,768);
	ECalCanvas->cd();
	hECal->Draw("coltz");

	ECalCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ECalCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// EQE

	TH2D* hEQE = new TH2D("hEQE",";True E^{QE} [GeV];Reco E^{QE} [GeV]",400,0,2,400,0,2);

	tree->Draw("Reco_EQE:True_EQE>>hEQE",qualifier,"goff");

	TCanvas* EQECanvas = new TCanvas("EQECanvas","EQECanvas",205,34,1024,768);
	EQECanvas->cd();
	hEQE->Draw("coltz");

	EQECanvas->SaveAs("myPlots/"+UBCodeVersion+"/EQECanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// DeltaPhi

	TH2D* hDeltaPhi = new TH2D("hDeltaPhi",";True #Delta#phi_{#mu,p} [deg];Reco #Delta#phi_{#mu,p} [deg]",360,0,360,360,0,360);

	tree->Draw("Reco_DeltaPhi:True_DeltaPhi>>hDeltaPhi",qualifier,"coltz");

	TCanvas* DeltaPhiCanvas = new TCanvas("DeltaPhiCanvas","DeltaPhiCanvas",205,34,1024,768);
	DeltaPhiCanvas->cd();
	hDeltaPhi->Draw("coltz");

	DeltaPhiCanvas->SaveAs("myPlots/"+UBCodeVersion+"/DeltaPhiCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// DeltaTheta

	TH2D* hDeltaTheta = new TH2D("hDeltaTheta",";True #Delta#theta_{#mu,p} [deg];Reco #Delta#theta_{#mu,p} [deg]",360,0,180,360,0,180);

	tree->Draw("Reco_DeltaTheta:True_DeltaTheta>>hDeltaTheta",qualifier,"goff");

	TCanvas* DeltaThetaCanvas = new TCanvas("DeltaThetaCanvas","DeltaThetaCanvas",205,34,1024,768);
	DeltaThetaCanvas->cd();
	hDeltaTheta->Draw("coltz");

	DeltaThetaCanvas->SaveAs("myPlots/"+UBCodeVersion+"/DeltaThetaCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Start X

	TH2D* hMuonStartX = new TH2D("hMuonStartX",";True Muon Start X [cm];Reco Muon Start X [cm]",300,-10,290,300,-10,290);

	tree->Draw("CandidateMu_StartX:True_CandidateMu_StartX>>hMuonStartX",qualifier,"goff");

	TCanvas* MuonStartXCanvas = new TCanvas("MuonStartXCanvas","MuonStartXCanvas",205,34,1024,768);
	MuonStartXCanvas->cd();
	hMuonStartX->Draw("coltz");

	MuonStartXCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonStartXCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Start Y

	TH2D* hMuonStartY = new TH2D("hMuonStartY",";True Muon Start Y [cm];Reco Muon Start Y [cm]",300,-150,150,300,-150,150);

	tree->Draw("CandidateMu_StartY:True_CandidateMu_StartY>>hMuonStartY",qualifier,"goff");

	TCanvas* MuonStartYCanvas = new TCanvas("MuonStartYCanvas","MuonStartYCanvas",205,34,1024,768);
	MuonStartYCanvas->cd();
	hMuonStartY->Draw("coltz");

	MuonStartYCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonStartYCanvas_"+RunNumber+".pdf");\

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Start Z

	TH2D* hMuonStartZ = new TH2D("hMuonStartZ",";True Muon Start Z [cm];Reco Muon Start Z [cm]",1200,-50,1150,1200,-50,1150);

	tree->Draw("CandidateMu_StartZ:True_CandidateMu_StartZ>>hMuonStartZ",qualifier,"goff");

	TCanvas* MuonStartZCanvas = new TCanvas("MuonStartZCanvas","MuonStartZCanvas",205,34,1024,768);
	MuonStartZCanvas->cd();
	hMuonStartZ->Draw("coltz");

	MuonStartZCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonStartZCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton Start X

	TH2D* hProtonStartX = new TH2D("hProtonStartX",";True Proton Start X [cm];Reco Proton Start X [cm]",300,-10,290,300,-10,290);

	tree->Draw("CandidateP_StartX:True_CandidateP_StartX>>hProtonStartX",qualifier,"goff");

	TCanvas* ProtonStartXCanvas = new TCanvas("ProtonStartXCanvas","ProtonStartXCanvas",205,34,1024,768);
	ProtonStartXCanvas->cd();
	hProtonStartX->Draw("coltz");

	ProtonStartXCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonStartXCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton Start Y

	TH2D* hProtonStartY = new TH2D("hProtonStartY",";True Proton Start Y [cm];Reco Proton Start Y [cm]",300,-150,150,300,-150,150);

	tree->Draw("CandidateP_StartY:True_CandidateP_StartY>>hProtonStartY",qualifier,"goff");

	TCanvas* ProtonStartYCanvas = new TCanvas("ProtonStartYCanvas","ProtonStartYCanvas",205,34,1024,768);
	ProtonStartYCanvas->cd();
	hProtonStartY->Draw("coltz");

	ProtonStartYCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonStartYCanvas_"+RunNumber+".pdf");\

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton Start Z

	TH2D* hProtonStartZ = new TH2D("hProtonStartZ",";True Proton Start Z [cm];Reco Proton Start Z [cm]",1200,-50,1150,1200,-50,1150);

	tree->Draw("CandidateP_StartZ:True_CandidateP_StartZ>>hProtonStartZ",qualifier,"goff");

	TCanvas* ProtonStartZCanvas = new TCanvas("ProtonStartZCanvas","ProtonStartZCanvas",205,34,1024,768);
	ProtonStartZCanvas->cd();
	hProtonStartZ->Draw("coltz");

	ProtonStartZCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonStartZCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	//  Muon End X

	TH2D* hMuonEndX = new TH2D("hMuonEndX",";True Muon End X [cm];Reco Muon End X [cm]",300,-10,290,300,-10,290);

	tree->Draw("CandidateMu_EndX:True_CandidateMu_EndX>>hMuonEndX",qualifier+" && CandidateMu_EndContainment == 1","goff");

	TCanvas* MuonEndXCanvas = new TCanvas("MuonEndXCanvas","MuonEndXCanvas",205,34,1024,768);
	MuonEndXCanvas->cd();
	hMuonEndX->SetTitle("Candidate Muon Tracks");
	hMuonEndX->SetTitleSize(0.08,"t");
	hMuonEndX->Draw("coltz");

	MuonEndXCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonEndXCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon End Y

	TH2D* hMuonEndY = new TH2D("hMuonEndY",";True Muon End Y [cm];Reco Muon End Y [cm]",300,-150,150,300,-150,150);

	tree->Draw("CandidateMu_EndY:True_CandidateMu_EndY>>hMuonEndY",qualifier,"goff");

	TCanvas* MuonEndYCanvas = new TCanvas("MuonEndYCanvas","MuonEndYCanvas",205,34,1024,768);
	MuonEndYCanvas->cd();
	hMuonEndY->Draw("coltz");

	MuonEndYCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonEndYCanvas_"+RunNumber+".pdf");\

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon End Z

	TH2D* hMuonEndZ = new TH2D("hMuonEndZ",";True Muon End Z [cm];Reco Muon End Z [cm]",1200,-50,1150,1200,-50,1150);

	tree->Draw("CandidateMu_EndZ:True_CandidateMu_EndZ>>hMuonEndZ",qualifier,"goff");

	TCanvas* MuonEndZCanvas = new TCanvas("MuonEndZCanvas","MuonEndZCanvas",205,34,1024,768);
	MuonEndZCanvas->cd();
	hMuonEndZ->Draw("coltz");

	MuonEndZCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonEndZCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton End X

	TH2D* hProtonEndX = new TH2D("hProtonEndX",";True Proton End X [cm];Reco Proton End X [cm]",300,-10,290,300,-10,290);

	tree->Draw("CandidateP_EndX:True_CandidateP_EndX>>hProtonEndX",qualifier,"goff");

	TCanvas* ProtonEndXCanvas = new TCanvas("ProtonEndXCanvas","ProtonEndXCanvas",205,34,1024,768);
	ProtonEndXCanvas->cd();
	hProtonEndX->Draw("coltz");

	ProtonEndXCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonEndXCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton End Y

	TH2D* hProtonEndY = new TH2D("hProtonEndY",";True Proton End Y [cm];Reco Proton End Y [cm]",300,-150,150,300,-150,150);

	tree->Draw("CandidateP_EndY:True_CandidateP_EndY>>hProtonEndY",qualifier,"goff");

	TCanvas* ProtonEndYCanvas = new TCanvas("ProtonEndYCanvas","ProtonEndYCanvas",205,34,1024,768);
	ProtonEndYCanvas->cd();
	hProtonEndY->Draw("coltz");

	ProtonEndYCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonEndYCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton End Z

	TH2D* hProtonEndZ = new TH2D("hProtonEndZ",";True Proton End Z [cm];Reco Proton End Z [cm]",1200,-50,1150,1200,-50,1150);

	tree->Draw("CandidateP_EndZ:True_CandidateP_EndZ>>hProtonEndZ",qualifier,"goff");

	TCanvas* ProtonEndZCanvas = new TCanvas("ProtonEndZCanvas","ProtonEndZCanvas",205,34,1024,768);
	ProtonEndZCanvas->cd();
	hProtonEndZ->Draw("coltz");

	ProtonEndZCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonEndZCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

} // End of the program 
