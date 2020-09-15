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

	gStyle->SetOptStat(0);

	TString RunNumber = "Run1";
//	TString RunNumber = "Run2";
//	TString RunNumber = "Run3";
//	TString RunNumber = "Run4";
//	TString RunNumber = "Run5";

	TFile* OverlayFile = TFile::Open("/uboone/data/users/apapadop/myEvents/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+RunNumber+"_"+UBCodeVersion+".root","readonly");
	TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

	TString qualifier = "CC1p && CandidateMu_MCParticle_Pdg == 13 && CandidateP_MCParticle_Pdg == 2212";

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Momentum MCS

	TCanvas* MuonMomentumMCSCanvas = new TCanvas("MuonMomentumMCSCanvas","MuonMomentumMCSCanvas",205,34,1024,768);
	MuonMomentumMCSCanvas->cd();

	tree->Draw("CandidateMu_P_MCS:True_CandidateMu_P>>hMuonMomMCS(400,0,2,400,0,2)",qualifier,"coltz");

	MuonMomentumMCSCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonMomentumMCS2DCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Momentum Range

	TCanvas* MuonMomentumRangeCanvas = new TCanvas("MuonMomentumRangeCanvas","MuonMomentumRangeCanvas",205,34,1024,768);
	MuonMomentumRangeCanvas->cd();

	tree->Draw("CandidateMu_P_Range:True_CandidateMu_P>>hMuonMomRange(400,0,2,400,0,2)",qualifier,"coltz");

	MuonMomentumRangeCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonMomentum2DRangeCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon CosTheta

	TCanvas* MuonCosThetaCanvas = new TCanvas("MuonCosThetaCanvas","MuonCosThetaCanvas",205,34,1024,768);
	MuonCosThetaCanvas->cd();

	tree->Draw("CandidateMu_CosTheta:True_CandidateMu_CosTheta>>hMuonCosTheta(400,-1,1,400,-1,1)",qualifier,"coltz");

	MuonCosThetaCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonCosThetaCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Muon Phi

	TCanvas* MuonPhiCanvas = new TCanvas("MuonPhiCanvas","MuonPhiCanvas",205,34,1024,768);
	MuonPhiCanvas->cd();

	tree->Draw("CandidateMu_Phi:True_CandidateMu_Phi>>hMuonPhi(360,-180,180,360,-180,180)",qualifier,"coltz");

	MuonPhiCanvas->SaveAs("myPlots/"+UBCodeVersion+"/MuonPhiCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton Momentum Range

	TCanvas* ProtonMomentumRangeCanvas = new TCanvas("ProtonMomentumRangeCanvas","ProtonMomentumRangeCanvas",205,34,1024,768);
	ProtonMomentumRangeCanvas->cd();

	tree->Draw("CandidateP_P_Range:True_CandidateP_P>>hProtonMomRange(400,0,2,400,0,2)",qualifier,"coltz");

	ProtonMomentumRangeCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonMomentum2DRangeCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton CosTheta

	TCanvas* ProtonCosThetaCanvas = new TCanvas("ProtonCosThetaCanvas","ProtonCosThetaCanvas",205,34,1024,768);
	ProtonCosThetaCanvas->cd();

	tree->Draw("CandidateP_CosTheta:True_CandidateP_CosTheta>>hProtonCosTheta(400,-1,1,400,-1,1)",qualifier,"coltz");

	ProtonCosThetaCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonCosThetaCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Proton Phi

	TCanvas* ProtonPhiCanvas = new TCanvas("ProtonPhiCanvas","ProtonPhiCanvas",205,34,1024,768);
	ProtonPhiCanvas->cd();

	tree->Draw("CandidateP_Phi:True_CandidateP_Phi>>hProtonPhi(360,-180,180,360,-180,180)",qualifier,"coltz");

	ProtonPhiCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ProtonPhiCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Transverse Missing Momentum

	TCanvas* PtCanvas = new TCanvas("PTCanvas","PTCanvas",205,34,1024,768);
	PtCanvas->cd();

	tree->Draw("Reco_Pt:True_Pt>>hPt(400,0,1,400,0,1)",qualifier,"coltz");

	PtCanvas->SaveAs("myPlots/"+UBCodeVersion+"/PtCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Delta AlphaT

	TCanvas* DeltaAlphaTCanvas = new TCanvas("DeltaAlphaTCanvas","DeltaAlphaTCanvas",205,34,1024,768);
	DeltaAlphaTCanvas->cd();

	tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>hDeltaAlphaT(360,0,180,360,0,180)",qualifier,"coltz");

	DeltaAlphaTCanvas->SaveAs("myPlots/"+UBCodeVersion+"/DeltaAlphaTCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// Delta PhiT

	TCanvas* DeltaPhiTCanvas = new TCanvas("DeltaPhiTCanvas","DeltaPhiTCanvas",205,34,1024,768);
	DeltaPhiTCanvas->cd();

	tree->Draw("Reco_DeltaPhiT:True_DeltaPhiT>>hDeltaPhiT(360,0,180,360,0,180)",qualifier,"coltz");

	DeltaPhiTCanvas->SaveAs("myPlots/"+UBCodeVersion+"/DeltaPhiTCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// kMiss

	TCanvas* kMissCanvas = new TCanvas("kMissCanvas","kMissCanvas",205,34,1024,768);
	kMissCanvas->cd();

	tree->Draw("Reco_kMiss:True_kMiss>>hkMissT(400,0,1,400,0,1)",qualifier,"coltz");

	kMissCanvas->SaveAs("myPlots/"+UBCodeVersion+"/kMissCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// PMissMinus

	TCanvas* PMissMinusCanvas = new TCanvas("PMissMinusCanvas","PMissMinusCanvas",205,34,1024,768);
	PMissMinusCanvas->cd();

	tree->Draw("Reco_PMissMinus:True_PMissMinus>>hPMissMinus(300,0,1.5,300,0,1.5)",qualifier,"coltz");

	PMissMinusCanvas->SaveAs("myPlots/"+UBCodeVersion+"/PMissMinusCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// ECal

	TCanvas* ECalCanvas = new TCanvas("ECalCanvas","ECalCanvas",205,34,1024,768);
	ECalCanvas->cd();

	tree->Draw("Reco_ECal:True_ECal>>hECal(400,0,2,400,0,2)",qualifier,"coltz");

	ECalCanvas->SaveAs("myPlots/"+UBCodeVersion+"/ECalCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// EQE

	TCanvas* EQECanvas = new TCanvas("EQECanvas","EQECanvas",205,34,1024,768);
	EQECanvas->cd();

	tree->Draw("Reco_EQE:True_EQE>>hEQE(400,0,2,400,0,2)",qualifier,"coltz");

	EQECanvas->SaveAs("myPlots/"+UBCodeVersion+"/EQECanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// DeltaPhi

	TCanvas* DeltaPhiCanvas = new TCanvas("DeltaPhiCanvas","DeltaPhiCanvas",205,34,1024,768);
	DeltaPhiCanvas->cd();

	tree->Draw("Reco_DeltaPhi:True_DeltaPhi>>hDeltaPhi(360,0,360,360,0,360)",qualifier,"coltz");

	DeltaPhiCanvas->SaveAs("myPlots/"+UBCodeVersion+"/DeltaPhiCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------

	// DeltaTheta

	TCanvas* DeltaThetaCanvas = new TCanvas("DeltaThetaCanvas","DeltaThetaCanvas",205,34,1024,768);
	DeltaThetaCanvas->cd();

	tree->Draw("Reco_DeltaTheta:True_DeltaTheta>>hDeltaTheta(180,0,180,180,0,180)",qualifier,"coltz");

	DeltaThetaCanvas->SaveAs("myPlots/"+UBCodeVersion+"/DeltaThetaCanvas_"+RunNumber+".pdf");

	// ----------------------------------------------------------------------------------------------------------------------------------------------------------



} // End of the program 
