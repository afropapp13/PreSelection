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

// -------------------------------------------------------------------------------------------------------------------------------------------------

void PeLEE_TwoDPlots() {

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
	gStyle->SetPadRightMargin(0.13);

	gROOT->ForceStyle();

	TString Recalibrate = "";
//	TString Recalibrate = "_Recalibrate";

	// -------------------------------------------------------------------------------------------------------------------------------------------------

//	std::vector<TString> Runs{"Run1"};
//	std::vector<TString> Runs{"Run1","Run3"};
//	std::vector<TString> Runs{"Run1","Run2","Run3","Run4","Run5"};

	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

//		TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PeLEETuples/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TFile* OverlayFile = TFile::Open("/uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);

		// -----------------------------------------------------------------------------------------------------------------------------------------

//		// Muon Momentum MCS

//		TH2D* hMuonMomMCS = new TH2D("hMuonMomMCS",";True Muon Momentum [GeV/c]; MCS Reco Muon Momentum [GeV/c]",75,0,1.5,75,0,1.5);

//		tree->Draw("CandidateMu_P_MCS" + Recalibrate + ":True_CandidateMu_P>>hMuonMomMCS",qualifier+ " && CandidateMu_EndContainment == 0","goff");

//		TCanvas* MuonMomentumMCSCanvas = new TCanvas("MuonMomentumMCSCanvas_"+Runs[WhichRun],"MuonMomentumMCSCanvas_"+Runs[WhichRun],205,34,1024,768);
//		MuonMomentumMCSCanvas->cd();
//		hMuonMomMCS->SetTitle("Exiting Candidate Muon Tracks");
//		hMuonMomMCS->SetTitleSize(0.08,"t");
//		hMuonMomMCS->Draw("coltz");

//		text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

//		MuonMomentumMCSCanvas->SaveAs(PlotPath+"MuonMomentumMCS2DCanvas_"+Runs[WhichRun]+".pdf");
//		delete MuonMomentumMCSCanvas;

		// ---------------------------------------------------------------------------------------------------------------------------------------

		// Muon Momentum Range

		TH2D* hMuonMomRange = new TH2D("hMuonMomRange",";True Muon Momentum [GeV/c]; Range Reco Muon Momentum [GeV/c]",75,0,1.3,75,0,1.3);

		tree->Draw("CandidateMu_P_Range" + Recalibrate + ":True_CandidateMu_P>>hMuonMomRange",qualifier+ " && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonMomentumRangeCanvas = new TCanvas("MuonMomentumRangeCanvas_"+Runs[WhichRun],"MuonMomentumRangeCanvas_"+Runs[WhichRun],205,34,1024,768);
		MuonMomentumRangeCanvas->cd();
		//hMuonMomRange->SetTitle("Contained Candidate Muon Tracks");
		hMuonMomRange->SetTitleSize(0.08,"t");
		hMuonMomRange->Draw("coltz");

		//text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		MuonMomentumRangeCanvas->SaveAs(PlotPath+"MuonMomentum2DRangeCanvas_"+Runs[WhichRun]+".pdf");
		delete MuonMomentumRangeCanvas;

		// ---------------------------------------------------------------------------------------------------------------------------------------

		// Muon Momentum Range W/O quality cut

		TH2D* hMuonMomRangeNoQC = new TH2D("hMuonMomRangeNoQC",";True Muon Momentum [GeV/c]; Range Reco Muon Momentum [GeV/c]",75,0,1.3,75,0,1.3);

		tree->Draw("CandidateMu_P_Range" + Recalibrate + ":True_CandidateMu_P>>hMuonMomRangeNoQC",qualifierNoMuRangeCut+ " && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonMomentumRangeCanvasNoQC = new TCanvas("MuonMomentumRangeCanvasNoQC_"+Runs[WhichRun],"MuonMomentumRangeCanvasNoQC_"+Runs[WhichRun],205,34,1024,768);
		MuonMomentumRangeCanvasNoQC->cd();
		//hMuonMomRangeNoQC->SetTitle("Contained Candidate Muon Tracks");
		hMuonMomRangeNoQC->SetTitleSize(0.08,"t");
		hMuonMomRangeNoQC->Draw("coltz");

		//text->DrawTextNDC(0.47, 0.92, Runs[WhichRun]);

		MuonMomentumRangeCanvasNoQC->SaveAs(PlotPath+"MuonMomentum2DRangeCanvasNoQC_"+Runs[WhichRun]+".pdf");
		delete MuonMomentumRangeCanvasNoQC;

		// -------------------------------------------------------------------------------------------------------------------------------

		// Muon CosTheta

		TH2D* hMuonCosTheta = new TH2D("hMuonCosTheta",";True cos#theta_{#mu};Reco cos#theta_{#mu}",400,-1,1,400,-1,1);

		tree->Draw("CandidateMu_CosTheta" + Recalibrate + ":True_CandidateMu_CosTheta>>hMuonCosTheta",qualifier,"goff");

		TCanvas* MuonCosThetaCanvas = new TCanvas("MuonCosThetaCanvas_"+Runs[WhichRun],"MuonCosThetaCanvas_"+Runs[WhichRun],205,34,1024,768);
		MuonCosThetaCanvas->cd();
		hMuonCosTheta->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonCosThetaCanvas->SaveAs(PlotPath+"MuonCosThetaCanvas_"+Runs[WhichRun]+".pdf");
		delete MuonCosThetaCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Muon Phi

		TH2D* hMuonPhi = new TH2D("hMuonPhi",";True Muon #phi [deg];Reco Muon #phi [deg]",360,-180,180,360,-180,180);

		tree->Draw("CandidateMu_Phi" + Recalibrate + ":True_CandidateMu_Phi>>hMuonPhi",qualifier,"goff");

		TCanvas* MuonPhiCanvas = new TCanvas("MuonPhiCanvas_"+Runs[WhichRun],"MuonPhiCanvas_"+Runs[WhichRun],205,34,1024,768);
		MuonPhiCanvas->cd();
		hMuonPhi->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonPhiCanvas->SaveAs(PlotPath+"MuonPhiCanvas_"+Runs[WhichRun]+".pdf");
		delete MuonPhiCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Proton Momentum Range vs length

		TH2D* hProtonMomLength = new TH2D("hProtonMomLength",";Reco Proton Momentum [GeV/c];Reco Proton Length [cm]",100,0.3,1.,100,0.,100.);

		tree->Draw("CandidateP_Length:CandidateP_P_Range>>hProtonMomLength",qualifier,"goff");

		TCanvas* ProtonMomentumLengthCanvas = new TCanvas("ProtonMomentumLengthCanvas_"+Runs[WhichRun],"ProtonMomentumCosLengthCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonMomentumLengthCanvas->cd();
		hProtonMomLength->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonMomentumLengthCanvas->SaveAs(PlotPath+"ProtonMomentumLengthCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonMomentumLengthCanvas;			

		// --------------------------------------------------------------------------------------------------------

		// Proton Momentum Range vs length in 0.3-0.5 GeV/c region

		TH2D* ZoomInhProtonMomLength = new TH2D("ZoomInhProtonMomLength",";Reco Proton Momentum [GeV/c];Reco Proton Length [cm]",20,0.3,0.5,15,0.,15.);
		TH2D* CaliZoomInhProtonMomLength = new TH2D("CaliZoomInhProtonMomLength",";Reco Proton Momentum [GeV/c];Reco Proton Length [cm]",20,0.3,0.5,15,0.,15.);		

		tree->Draw("CandidateP_Length:CandidateP_P_Range>>ZoomInhProtonMomLength",qualifier,"goff");
		tree->Draw("CandidateP_Length:(1+0.01*(29.354172*CandidateP_P_Range-14.674918))*CandidateP_P_Range>>CaliZoomInhProtonMomLength",qualifier,"goff");		

		TCanvas* ZoomInProtonMomentumLengthCanvas = new TCanvas("ZoomInProtonMomentumLengthCanvas_"+Runs[WhichRun],"ZoomInProtonMomentumCosLengthCanvas_"+Runs[WhichRun],205,34,1024,768);
		ZoomInProtonMomentumLengthCanvas->cd();
		ZoomInhProtonMomLength->Draw("coltz");
		//CaliZoomInhProtonMomLength->Draw("coltz same");		

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ZoomInProtonMomentumLengthCanvas->SaveAs(PlotPath+"ZoomInProtonMomentumLengthCanvas_"+Runs[WhichRun]+".pdf");
		delete ZoomInProtonMomentumLengthCanvas;			

		// --------------------------------------------------------------------------------------------------------

		// Proton Momentum Range vs cos theta 

		TH2D* hProtonMomCos = new TH2D("hProtonMomCos",";True Proton Momentum [GeV/c];Range Reco Proton cos#theta_{p}",50,0.3,1.,50,-1.,1.);

		tree->Draw("CandidateP_CosTheta:CandidateP_P_Range>>hProtonMomCos","("+qualifier+")*(CandidateP_P_Range - True_CandidateP_P)/True_CandidateP_P * 100 .","goff");

		TCanvas* ProtonMomentumCosCanvas = new TCanvas("ProtonMomentumCosCanvas_"+Runs[WhichRun],"ProtonMomentumCosCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonMomentumCosCanvas->cd();
		hProtonMomCos->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonMomentumCosCanvas->SaveAs(PlotPath+"ProtonMomentumCosCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonMomentumCosCanvas;		

		// --------------------------------------------------------------------------------------------------------

		// Proton Momentum Range

		TH2D* hProtonMomRange = new TH2D("hProtonMomRange",";True Proton Momentum [GeV/c];Range Reco Proton Momentum [GeV/c]",100,0.2,1.1,100,0.2,1.1);

		tree->Draw("CandidateP_P_Range" + Recalibrate + ":True_CandidateP_P>>hProtonMomRange",qualifier,"goff");

		TCanvas* ProtonMomentumRangeCanvas = new TCanvas("ProtonMomentumRangeCanvas_"+Runs[WhichRun],"ProtonMomentumRangeCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonMomentumRangeCanvas->cd();
		hProtonMomRange->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonMomentumRangeCanvas->SaveAs(PlotPath+"ProtonMomentum2DRangeCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonMomentumRangeCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Proton CosTheta

		TH2D* hProtonCosTheta = new TH2D("hProtonCosTheta",";True cos#theta_{p};Reco cos#theta_{p}",400,-1,1,400,-1,1);

		tree->Draw("CandidateP_CosTheta" + Recalibrate + ":True_CandidateP_CosTheta>>hProtonCosTheta",qualifier,"goff");

		TCanvas* ProtonCosThetaCanvas = new TCanvas("ProtonCosThetaCanvas_"+Runs[WhichRun],"ProtonCosThetaCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonCosThetaCanvas->cd();
		hProtonCosTheta->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonCosThetaCanvas->SaveAs(PlotPath+"ProtonCosThetaCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonCosThetaCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Proton Phi

		TH2D* hProtonPhi = new TH2D("hProtonPhi",";True Proton #phi [deg];Reco Proton #phi [deg]",360,-180,180,360,-180,180);

		tree->Draw("CandidateP_Phi" + Recalibrate + ":True_CandidateP_Phi>>hProtonPhi",qualifier,"goff");

		TCanvas* ProtonPhiCanvas = new TCanvas("ProtonPhiCanvas_"+Runs[WhichRun],"ProtonPhiCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonPhiCanvas->cd();
		hProtonPhi->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonPhiCanvas->SaveAs(PlotPath+"ProtonPhiCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonPhiCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Transverse Missing Momentum

		TH2D* hPt = new TH2D("hPt",";True #deltap_{T} [GeV/c];Reco #deltap_{T} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PtCanvas = new TCanvas("PTCanvas_"+Runs[WhichRun],"PTCanvas_"+Runs[WhichRun],205,34,1024,768);
		PtCanvas->cd();

		tree->Draw("Reco_Pt" + Recalibrate + ":True_Pt>>hPt",qualifier,"goff");
		hPt->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PtCanvas->SaveAs(PlotPath+"PtCanvas_"+Runs[WhichRun]+".pdf");
		delete PtCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Transverse Missing Momentum x

		TH2D* hPtx = new TH2D("hPtx",";True #deltap_{T,x} [GeV/c];Reco #deltap_{T,x} [GeV/c]",140,-0.7,0.7,140,-0.7,0.7);

		TCanvas* PtxCanvas = new TCanvas("PTxCanvas_"+Runs[WhichRun],"PTxCanvas_"+Runs[WhichRun],205,34,1024,768);
		PtxCanvas->cd();

		tree->Draw("Reco_Ptx" + Recalibrate + ":True_Ptx>>hPtx",qualifier,"goff");
		hPtx->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PtxCanvas->SaveAs(PlotPath+"PtxCanvas_"+Runs[WhichRun]+".pdf");
		delete PtxCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Transverse Missing Momentum y

		TH2D* hPty = new TH2D("hPty",";True #deltap_{T,y} [GeV/c];Reco #deltap_{T,y} [GeV/c]",100,-0.5,0.5,100,-0.5,0.5);

		TCanvas* PtyCanvas = new TCanvas("PTyCanvas_"+Runs[WhichRun],"PTyCanvas_"+Runs[WhichRun],205,34,1024,768);
		PtyCanvas->cd();

		tree->Draw("Reco_Pty" + Recalibrate + ":True_Pty>>hPty",qualifier,"goff");
		hPty->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PtyCanvas->SaveAs(PlotPath+"PtyCanvas_"+Runs[WhichRun]+".pdf");
		delete PtyCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Longitudinal Missing Momentum

		TH2D* hPL = new TH2D("hPL",";True #deltap_{L} [GeV/c];Reco #deltap_{L} [GeV/c]",100,-0.5,0.5,100,-0.5,0.5);

		TCanvas* PLCanvas = new TCanvas("PLCanvas_"+Runs[WhichRun],"PLCanvas_"+Runs[WhichRun],205,34,1024,768);
		PLCanvas->cd();

		tree->Draw("Reco_PL" + Recalibrate + ":True_PL>>hPL",qualifier,"goff");
		hPL->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PLCanvas->SaveAs(PlotPath+"PLCanvas_"+Runs[WhichRun]+".pdf");
		delete PLCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum

		TH2D* hPn = new TH2D("hPn",";True p_{n,proxy} [GeV/c];Reco p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnCanvas = new TCanvas("PnCanvas_"+Runs[WhichRun],"PnCanvas_"+Runs[WhichRun],205,34,1024,768);
		PnCanvas->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":True_Pn>>hPn",qualifier,"goff");
		hPn->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PnCanvas->SaveAs(PlotPath+"PnCanvas_"+Runs[WhichRun]+".pdf");
		delete PnCanvas;

		// --------------------------------------------------------------------------------------------------------

		// QE Total Missing Momentum

		TH2D* hPnQE = new TH2D("hPnQE",";True p_{n,proxy} [GeV/c];Reco p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnCanvasQE = new TCanvas("QEPnCanvas_"+Runs[WhichRun],"QEPnCanvas_"+Runs[WhichRun],205,34,1024,768);
		PnCanvasQE->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":True_Pn>>hPnQE",qualifier + " && MCParticle_Mode == 0","goff");
		hPnQE->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " QE events");

		PnCanvasQE->SaveAs(PlotPath+"QEPnCanvas_"+Runs[WhichRun]+".pdf");
		delete PnCanvasQE;	

		// --------------------------------------------------------------------------------------------------------

		// MEC Total Missing Momentum

		TH2D* hPnMEC = new TH2D("hPnMEC",";True p_{n,proxy} [GeV/c];Reco p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnCanvasMEC = new TCanvas("MECPnCanvas_"+Runs[WhichRun],"MECPnCanvas_"+Runs[WhichRun],205,34,1024,768);
		PnCanvasMEC->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":True_Pn>>hPnMEC",qualifier + " && MCParticle_Mode == 10","goff");
		hPnMEC->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun]+ " MEC events");

		PnCanvasMEC->SaveAs(PlotPath+"MECPnCanvas_"+Runs[WhichRun]+".pdf");
		delete PnCanvasMEC;			

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum from light cone (L) vs Minerva recipe (M) using reco variables

		TH2D* hPnLM = new TH2D("hPnLM",";Reco k_{Miss} [GeV/c];Reco p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnLMCanvas = new TCanvas("PnLMCanvas_"+Runs[WhichRun],"PnLMCanvas_"+Runs[WhichRun],205,34,1024,768);
		PnLMCanvas->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":Reco_kMiss>>hPnLM",qualifier,"goff");
		hPnLM->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PnLMCanvas->SaveAs(PlotPath+"PnLMCanvas_"+Runs[WhichRun]+".pdf");
		delete PnLMCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum from light cone (L) vs Minerva recipe (M) using reco variables for QE events w/o extra FSI particles

		TH2D* hPnLMQE = new TH2D("hPnLMQE",";Reco k_{Miss} [GeV/c];Reco p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnLMCanvasQE = new TCanvas("PnLMCanvasQE_"+Runs[WhichRun],"PnLMCanvasQE_"+Runs[WhichRun],205,34,1024,768);
		PnLMCanvasQE->cd();

//		tree->Draw("Reco_Pn" + Recalibrate + ":Reco_kMiss>>hPnLMQE",qualifier+ " && NumberNeutrons == 0 && NumberChargedPions == 0 && MCParticle_Mode == 0","goff");
		tree->Draw("Reco_Pn" + Recalibrate + ":Reco_kMiss>>hPnLMQE",qualifier+ "  && MCParticle_Mode == 0","goff");
		hPnLMQE->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " CCQE");

		PnLMCanvasQE->SaveAs(PlotPath+"QEPnLMCanvas_"+Runs[WhichRun]+".pdf");
		delete PnLMCanvasQE;	

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum from light cone (L) vs Minerva recipe (M) using reco variables for MEC events

		TH2D* hPnLMMEC = new TH2D("hPnLMMEC",";Reco k_{Miss} [GeV/c];Reco p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnLMCanvasMEC = new TCanvas("PnLMCanvasMEC_"+Runs[WhichRun],"PnLMCanvasMEC_"+Runs[WhichRun],205,34,1024,768);
		PnLMCanvasMEC->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":Reco_kMiss>>hPnLMMEC",qualifier+ " && MCParticle_Mode == 10","goff");
		hPnLMMEC->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " CCMEC");

		PnLMCanvasMEC->SaveAs(PlotPath+"MECPnLMCanvas_"+Runs[WhichRun]+".pdf");
		delete PnLMCanvasMEC;			

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum from light cone (L) vs Minerva recipe (M) using reco variables for RES events

		TH2D* hPnLMRES = new TH2D("hPnLMRES",";Reco k_{Miss} [GeV/c];Reco p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnLMCanvasRES = new TCanvas("PnLMCanvasRES_"+Runs[WhichRun],"PnLMCanvasRES_"+Runs[WhichRun],205,34,1024,768);
		PnLMCanvasRES->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":Reco_kMiss>>hPnLMRES",qualifier+ " && MCParticle_Mode == 1","goff");
		hPnLMRES->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " CCRES");

		PnLMCanvasRES->SaveAs(PlotPath+"RESPnLMCanvas_"+Runs[WhichRun]+".pdf");
		delete PnLMCanvasRES;		


		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum from light cone (L) vs Minerva recipe (M) using reco variables for DIS events

		TH2D* hPnLMDIS = new TH2D("hPnLMDIS",";Reco k_{Miss} [GeV/c];Reco p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnLMCanvasDIS = new TCanvas("PnLMCanvasDIS_"+Runs[WhichRun],"PnLMCanvasDIS_"+Runs[WhichRun],205,34,1024,768);
		PnLMCanvasDIS->cd();

		tree->Draw("Reco_Pn" + Recalibrate + ":Reco_kMiss>>hPnLMDIS",qualifier+ " && MCParticle_Mode == 2","goff");
		hPnLMDIS->Draw("coltz");

		text->DrawTextNDC(0.37, 0.93, Runs[WhichRun] + " CCDIS");

		PnLMCanvasDIS->SaveAs(PlotPath+"DISPnLMCanvas_"+Runs[WhichRun]+".pdf");
		delete PnLMCanvasDIS;				

		// --------------------------------------------------------------------------------------------------------

		// Total Missing Momentum from light cone (L) vs Minerva recipe (M) using true variables

		TH2D* hPnLMTrue = new TH2D("hPnLMTrue",";True k_{Miss} [GeV/c];True p_{n,proxy} [GeV/c]",80,0,0.8,80,0,0.8);

		TCanvas* PnLMCanvasTrue = new TCanvas("PnLMCanvasTrue_"+Runs[WhichRun],"PnLMCanvasTrue_"+Runs[WhichRun],205,34,1024,768);
		PnLMCanvasTrue->cd();

		tree->Draw("True_Pn" + Recalibrate + ":True_kMiss>>hPnLMTrue",qualifier,"goff");
		hPnLMTrue->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PnLMCanvasTrue->SaveAs(PlotPath+"PnLMCanvasTrue_"+Runs[WhichRun]+".pdf");
		delete PnLMCanvasTrue;

		// --------------------------------------------------------------------------------------------------------

		// Delta AlphaT

		TH2D* hDeltaAlphaT = new TH2D("hDeltaAlphaT",";True #delta#alpha_{T} [deg];Reco #delta#alpha_{T} [deg]",90,0,180,90,0,180);

		tree->Draw("Reco_DeltaAlphaT" + Recalibrate + ":True_DeltaAlphaT>>hDeltaAlphaT",qualifier,"goff");

		TCanvas* DeltaAlphaTCanvas = new TCanvas("DeltaAlphaTCanvas_"+Runs[WhichRun],"DeltaAlphaTCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaAlphaTCanvas->cd();
		hDeltaAlphaT->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		DeltaAlphaTCanvas->SaveAs(PlotPath+"DeltaAlphaTCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaAlphaTCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Delta Alpha3Dq

		TH2D* hDeltaAlpha3Dq = new TH2D("hDeltaAlpha3Dq",";True #delta#alpha_{3D} [deg];Reco #delta#alpha_{3D} [deg]",90,0,180,90,0,180);

		tree->Draw("Reco_DeltaAlpha3Dq" + Recalibrate + ":True_DeltaAlpha3Dq>>hDeltaAlpha3Dq",qualifier,"goff");

		TCanvas* DeltaAlpha3DqCanvas = new TCanvas("DeltaAlpha3DqCanvas_"+Runs[WhichRun],"DeltaAlpha3DqCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaAlpha3DqCanvas->cd();
		hDeltaAlpha3Dq->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		DeltaAlpha3DqCanvas->SaveAs(PlotPath+"DeltaAlpha3DqCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaAlpha3DqCanvas;	

		// --------------------------------------------------------------------------------------------------------

		// Delta Alpha3DMu

		TH2D* hDeltaAlpha3DMu = new TH2D("hDeltaAlpha3DMu",";True #delta#alpha_{3D} [deg];Reco #delta#alpha_{3D} [deg]",90,0,180,90,0,180);

		tree->Draw("Reco_DeltaAlpha3DMu" + Recalibrate + ":True_DeltaAlpha3DMu>>hDeltaAlpha3DMu",qualifier,"goff");

		TCanvas* DeltaAlpha3DMuCanvas = new TCanvas("DeltaAlpha3DMuCanvas_"+Runs[WhichRun],"DeltaAlpha3DMuCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaAlpha3DMuCanvas->cd();
		hDeltaAlpha3DMu->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		DeltaAlpha3DMuCanvas->SaveAs(PlotPath+"DeltaAlpha3DMuCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaAlpha3DMuCanvas;				

		// --------------------------------------------------------------------------------------------------------

		// Delta PhiT

		TH2D* hDeltaPhiT = new TH2D("hDeltaPhiT",";True #delta#phi_{T} [deg];Reco #delta#phi_{T} [deg]",90,0,180,90,0,180);

		tree->Draw("Reco_DeltaPhiT" + Recalibrate + ":True_DeltaPhiT>>hDeltaPhiT",qualifier,"goff");

		TCanvas* DeltaPhiTCanvas = new TCanvas("DeltaPhiTCanvas_"+Runs[WhichRun],"DeltaPhiTCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPhiTCanvas->cd();
		hDeltaPhiT->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		DeltaPhiTCanvas->SaveAs(PlotPath+"DeltaPhiTCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPhiTCanvas;

		// --------------------------------------------------------------------------------------------------------

		// A variable

		TH2D* hA = new TH2D("hA",";True #alpha [c];Reco #alpha [c]",100,0.5,1.5,100,0.5,1.5);

		tree->Draw("Reco_A:True_A>>hA",qualifier,"goff");

		TCanvas* ACanvas = new TCanvas("ACanvas_"+Runs[WhichRun],"ACanvas_"+Runs[WhichRun],205,34,1024,768);
		ACanvas->cd();
		hA->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ACanvas->SaveAs(PlotPath+"ACanvas_"+Runs[WhichRun]+".pdf");
		delete ACanvas;

		// --------------------------------------------------------------------------------------------------------

		// kMiss

		TH2D* hkMiss = new TH2D("hkMiss",";True k_{Miss} [GeV/c];Reco k_{Miss} [GeV/c]",80,0,0.8,80,0,0.8);

		tree->Draw("Reco_kMiss:True_kMiss>>hkMiss",qualifier,"goff");

		TCanvas* kMissCanvas = new TCanvas("kMissCanvas_"+Runs[WhichRun],"kMissCanvas_"+Runs[WhichRun],205,34,1024,768);
		kMissCanvas->cd();
		hkMiss->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		kMissCanvas->SaveAs(PlotPath+"kMissCanvas_"+Runs[WhichRun]+".pdf");
		delete kMissCanvas;

		// --------------------------------------------------------------------------------------------------------

		// PMiss

		TH2D* hPMiss = new TH2D("hPMiss",";True P_{Miss} [GeV/c];Reco P_{Miss} [GeV/c]",100,0,1.,100,0,1.);

		tree->Draw("Reco_PMiss:True_PMiss>>hPMiss",qualifier,"goff");

		TCanvas* PMissCanvas = new TCanvas("PMissCanvas_"+Runs[WhichRun],"PMissCanvas_"+Runs[WhichRun],205,34,1024,768);
		PMissCanvas->cd();
		hPMiss->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PMissCanvas->SaveAs(PlotPath+"PMissCanvas_"+Runs[WhichRun]+".pdf");
		delete PMissCanvas;

		// --------------------------------------------------------------------------------------------------------

		// PMissMinus

		TH2D* hPMissMinus = new TH2D("hPMissMinus",";True P^{-}_{Miss} [GeV/c];Reco P^{-}_{Miss} [GeV/c]",110,0.4,1.5,110,0.4,1.5);

		tree->Draw("Reco_PMissMinus:True_PMissMinus>>hPMissMinus",qualifier,"goff");

		TCanvas* PMissMinusCanvas = new TCanvas("PMissMinusCanvas_"+Runs[WhichRun],"PMissMinusCanvas_"+Runs[WhichRun],205,34,1024,768);
		PMissMinusCanvas->cd();
		hPMissMinus->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		PMissMinusCanvas->SaveAs(PlotPath+"PMissMinusCanvas_"+Runs[WhichRun]+".pdf");
		delete PMissMinusCanvas;

		// --------------------------------------------------------------------------------------------------------

		// ECal

		TH2D* hECal = new TH2D("hECal",";True E^{cal} [GeV];Reco E^{cal} [GeV]",200,0,2,200,0,2);

		tree->Draw("Reco_ECal" + Recalibrate + ":True_ECal>>hECal",qualifier,"goff");

		TCanvas* ECalCanvas = new TCanvas("ECalCanvas_"+Runs[WhichRun],"ECalCanvas_"+Runs[WhichRun],205,34,1024,768);
		ECalCanvas->cd();
		hECal->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ECalCanvas->SaveAs(PlotPath+"ECalCanvas_"+Runs[WhichRun]+".pdf");
		delete ECalCanvas;

		// --------------------------------------------------------------------------------------------------------

		// EQE

		TH2D* hEQE = new TH2D("hEQE",";True E^{QE} [GeV];Reco E^{QE} [GeV]",200,0,2,200,0,2);

		tree->Draw("Reco_EQE" + Recalibrate + ":True_EQE>>hEQE",qualifier,"goff");

		TCanvas* EQECanvas = new TCanvas("EQECanvas_"+Runs[WhichRun],"EQECanvas_"+Runs[WhichRun],205,34,1024,768);
		EQECanvas->cd();
		hEQE->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		EQECanvas->SaveAs(PlotPath+"EQECanvas_"+Runs[WhichRun]+".pdf");
		delete EQECanvas;

		// --------------------------------------------------------------------------------------------------------

		// Q2

		TH2D* hQ2 = new TH2D("hQ2",";True Q^{2} [GeV^{2}/c^{2}];Reco Q^{2} [GeV^{2}/c^{2}]",100,0.,1.,100,0.,1.);

		tree->Draw("Reco_Q2" + Recalibrate + ":True_Q2>>hQ2",qualifier,"goff");

		TCanvas* Q2Canvas = new TCanvas("Q2Canvas_"+Runs[WhichRun],"Q2Canvas_"+Runs[WhichRun],205,34,1024,768);
		Q2Canvas->cd();
		hQ2->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		Q2Canvas->SaveAs(PlotPath+"Q2Canvas_"+Runs[WhichRun]+".pdf");
		delete Q2Canvas;

		// --------------------------------------------------------------------------------------------------------

		// DeltaPhi

		TH2D* hDeltaPhi = new TH2D("hDeltaPhi",";True #delta#phi_{#mu,p} [deg];Reco #delta#phi_{#mu,p} [deg]",360,0,360,360,0,360);

		tree->Draw("Reco_DeltaPhi:True_DeltaPhi>>hDeltaPhi",qualifier,"goff");

		TCanvas* DeltaPhiCanvas = new TCanvas("DeltaPhiCanvas_"+Runs[WhichRun],"DeltaPhiCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPhiCanvas->cd();
		hDeltaPhi->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		DeltaPhiCanvas->SaveAs(PlotPath+"DeltaPhiCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPhiCanvas;

		// --------------------------------------------------------------------------------------------------------

		// DeltaTheta

		TH2D* hDeltaTheta = new TH2D("hDeltaTheta",";True #delta#theta_{#mu,p} [deg];Reco #delta#theta_{#mu,p} [deg]",360,0,180,360,0,180);

		tree->Draw("Reco_DeltaTheta:True_DeltaTheta>>hDeltaTheta",qualifier,"goff");

		TCanvas* DeltaThetaCanvas = new TCanvas("DeltaThetaCanvas_"+Runs[WhichRun],"DeltaThetaCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaThetaCanvas->cd();
		hDeltaTheta->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		DeltaThetaCanvas->SaveAs(PlotPath+"DeltaThetaCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaThetaCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Muon Start X

		TH2D* hMuonStartX = new TH2D("hMuonStartX",";True Muon Start X [cm];Reco Muon Start X [cm]",300,-10,270,300,-10,270);

		tree->Draw("CandidateMu_StartX:True_CandidateMu_StartX>>hMuonStartX",qualifier,"goff");

		TCanvas* MuonStartXCanvas = new TCanvas("MuonStartXCanvas_"+Runs[WhichRun],"MuonStartXCanvas_"+Runs[WhichRun],205,34,1024,768);
		MuonStartXCanvas->cd();
		hMuonStartX->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonStartXCanvas->SaveAs(PlotPath+"MuonStartXCanvas_"+Runs[WhichRun]+".pdf");
		delete MuonStartXCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Muon Start Y

		TH2D* hMuonStartY = new TH2D("hMuonStartY",";True Muon Start Y [cm];Reco Muon Start Y [cm]",300,-130,130,300,-130,130);

		tree->Draw("CandidateMu_StartY:True_CandidateMu_StartY>>hMuonStartY",qualifier,"goff");

		TCanvas* MuonStartYCanvas = new TCanvas("MuonStartYCanvas_"+Runs[WhichRun],"MuonStartYCanvas_"+Runs[WhichRun],205,34,1024,768);
		MuonStartYCanvas->cd();
		hMuonStartY->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonStartYCanvas->SaveAs(PlotPath+"MuonStartYCanvas_"+Runs[WhichRun]+".pdf");
		delete MuonStartYCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Muon Start Z

		TH2D* hMuonStartZ = new TH2D("hMuonStartZ",";True Muon Start Z [cm];Reco Muon Start Z [cm]",550,-20,1100,550,-20,1100);

		tree->Draw("CandidateMu_StartZ:True_CandidateMu_StartZ>>hMuonStartZ",qualifier,"goff");

		TCanvas* MuonStartZCanvas = new TCanvas("MuonStartZCanvas_"+Runs[WhichRun],"MuonStartZCanvas_"+Runs[WhichRun],205,34,1024,768);
		MuonStartZCanvas->cd();
		hMuonStartZ->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonStartZCanvas->SaveAs(PlotPath+"MuonStartZCanvas_"+Runs[WhichRun]+".pdf");
		delete MuonStartZCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Proton Start X

		TH2D* hProtonStartX = new TH2D("hProtonStartX",";True Proton Start X [cm];Reco Proton Start X [cm]",300,-10,270,300,-10,270);

		tree->Draw("CandidateP_StartX:True_CandidateP_StartX>>hProtonStartX",qualifier,"goff");

		TCanvas* ProtonStartXCanvas = new TCanvas("ProtonStartXCanvas_"+Runs[WhichRun],"ProtonStartXCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonStartXCanvas->cd();
		hProtonStartX->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonStartXCanvas->SaveAs(PlotPath+"ProtonStartXCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonStartXCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Proton Start Y

		TH2D* hProtonStartY = new TH2D("hProtonStartY",";True Proton Start Y [cm];Reco Proton Start Y [cm]",300,-130,130,300,-130,130);

		tree->Draw("CandidateP_StartY:True_CandidateP_StartY>>hProtonStartY",qualifier,"goff");

		TCanvas* ProtonStartYCanvas = new TCanvas("ProtonStartYCanvas_"+Runs[WhichRun],"ProtonStartYCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonStartYCanvas->cd();
		hProtonStartY->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonStartYCanvas->SaveAs(PlotPath+"ProtonStartYCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonStartYCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Proton Start Z

		TH2D* hProtonStartZ = new TH2D("hProtonStartZ",";True Proton Start Z [cm];Reco Proton Start Z [cm]",550,-50,1100,5500,-50,1100);

		tree->Draw("CandidateP_StartZ:True_CandidateP_StartZ>>hProtonStartZ",qualifier,"goff");

		TCanvas* ProtonStartZCanvas = new TCanvas("ProtonStartZCanvas_"+Runs[WhichRun],"ProtonStartZCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonStartZCanvas->cd();
		hProtonStartZ->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonStartZCanvas->SaveAs(PlotPath+"ProtonStartZCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonStartZCanvas;

		// --------------------------------------------------------------------------------------------------------

		//  Muon End X

		TH2D* hMuonEndX = new TH2D("hMuonEndX",";True Muon End X [cm];Reco Muon End X [cm]",300,-10,270,300,-10,270);

		tree->Draw("CandidateMu_EndX:True_CandidateMu_EndX>>hMuonEndX",qualifier+" && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonEndXCanvas = new TCanvas("MuonEndXCanvas_"+Runs[WhichRun],"MuonEndXCanvas_"+Runs[WhichRun],205,34,1024,768);
		MuonEndXCanvas->cd();
		hMuonEndX->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonEndXCanvas->SaveAs(PlotPath+"MuonEndXCanvas_"+Runs[WhichRun]+".pdf");
		delete MuonEndXCanvas;

		//--------------------------------------------------------------------------------------------------------

		// Muon End Y

		TH2D* hMuonEndY = new TH2D("hMuonEndY",";True Muon End Y [cm];Reco Muon End Y [cm]",300,-150,150,300,-150,150);

		tree->Draw("CandidateMu_EndY:True_CandidateMu_EndY>>hMuonEndY",qualifier,"goff");

		TCanvas* MuonEndYCanvas = new TCanvas("MuonEndYCanvas_"+Runs[WhichRun],"MuonEndYCanvas_"+Runs[WhichRun],205,34,1024,768);
		MuonEndYCanvas->cd();
		hMuonEndY->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonEndYCanvas->SaveAs(PlotPath+"MuonEndYCanvas_"+Runs[WhichRun]+".pdf");
		delete MuonEndYCanvas;

		//--------------------------------------------------------------------------------------------------------

		// Muon End Z

		TH2D* hMuonEndZ = new TH2D("hMuonEndZ",";True Muon End Z [cm];Reco Muon End Z [cm]",1200,-50,1150,1200,-50,1150);

		tree->Draw("CandidateMu_EndZ:True_CandidateMu_EndZ>>hMuonEndZ",qualifier,"goff");

		TCanvas* MuonEndZCanvas = new TCanvas("MuonEndZCanvas_"+Runs[WhichRun],"MuonEndZCanvas_"+Runs[WhichRun],205,34,1024,768);
		MuonEndZCanvas->cd();
		hMuonEndZ->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonEndZCanvas->SaveAs(PlotPath+"MuonEndZCanvas_"+Runs[WhichRun]+".pdf");
		delete MuonEndZCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Proton End X

		TH2D* hProtonEndX = new TH2D("hProtonEndX",";True Proton End X [cm];Reco Proton End X [cm]",300,-10,290,300,-10,290);

		tree->Draw("CandidateP_EndX:True_CandidateP_EndX[0]>>hProtonEndX",qualifier,"goff");

		TCanvas* ProtonEndXCanvas = new TCanvas("ProtonEndXCanvas_"+Runs[WhichRun],"ProtonEndXCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonEndXCanvas->cd();
		hProtonEndX->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonEndXCanvas->SaveAs(PlotPath+"ProtonEndXCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonEndXCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Proton End Y

		TH2D* hProtonEndY = new TH2D("hProtonEndY",";True Proton End Y [cm];Reco Proton End Y [cm]",300,-150,150,300,-150,150);

		tree->Draw("CandidateP_EndY:True_CandidateP_EndY[0]>>hProtonEndY",qualifier,"goff");

		TCanvas* ProtonEndYCanvas = new TCanvas("ProtonEndYCanvas_"+Runs[WhichRun],"ProtonEndYCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonEndYCanvas->cd();
		hProtonEndY->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonEndYCanvas->SaveAs(PlotPath+"ProtonEndYCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonEndYCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Proton End Z

		TH2D* hProtonEndZ = new TH2D("hProtonEndZ",";True Proton End Z [cm];Reco Proton End Z [cm]",1200,-50,1150,1200,-50,1150);

		tree->Draw("CandidateP_EndZ:True_CandidateP_EndZ[0]>>hProtonEndZ",qualifier,"goff");

		TCanvas* ProtonEndZCanvas = new TCanvas("ProtonEndZCanvas_"+Runs[WhichRun],"ProtonEndZCanvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonEndZCanvas->cd();
		hProtonEndZ->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonEndZCanvas->SaveAs(PlotPath+"ProtonEndZCanvas_"+Runs[WhichRun]+".pdf");
		delete ProtonEndZCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Bonus Plot: 1D μ-p distance 

		TH1D* hMuPDistance = new TH1D("hMuPDistance",";reco pair distance [cm]",23,-0.5,11.5);

		tree->Draw("CandidateMuP_Distance>>hMuPDistance",qualifier,"goff");

		TCanvas* CandidateMuP_DistanceCanvas = new TCanvas("CandidateMuP_DistanceCanvas_"+Runs[WhichRun],"CandidateMuP_DistanceCanvas_"+Runs[WhichRun],205,34,1024,768);
		CandidateMuP_DistanceCanvas->SetLeftMargin(0.15);
		CandidateMuP_DistanceCanvas->cd();
		hMuPDistance->SetTitle("MicroBooNE Simulation (CC1p0#pi Events)");
		hMuPDistance->GetYaxis()->SetTitle("# Pairs / Bin");
		hMuPDistance->GetYaxis()->SetTitleOffset(1.35);
		hMuPDistance->SetLineColor(kBlue-6);
		hMuPDistance->SetFillColor(kBlue-6);
		hMuPDistance->Draw("hist");

		text->DrawTextNDC(0.47, 0.91, Runs[WhichRun]);

		CandidateMuP_DistanceCanvas->SaveAs(PlotPath+"CandidateMuP_DistanceCanvas_"+Runs[WhichRun]+".pdf");
		delete CandidateMuP_DistanceCanvas;

		// --------------------------------------------------------------------------------------------------------

		// Bonus Plot: True charged pion momentum

		TH1D* hPiMom = new TH1D("hPiMom",";True P_{#pi^{#pm}} [GeV/c]",35,0.,0.7);

		tree->Draw("True_PionMomentum>>hPiMom",qualifierData,"goff");

		TCanvas* hPiMomCanvas = new TCanvas("hPiMomCanvas_"+Runs[WhichRun],"hPiMomCanvas_"+Runs[WhichRun],205,34,1024,768);
		hPiMomCanvas->SetLeftMargin(0.15);
		hPiMomCanvas->cd();
		hPiMom->SetTitle("MC Events passing CC1p0#pi selection with N>0 #pi^{#pm}");
		hPiMom->GetYaxis()->SetTitle("POT Normalized Events");
		hPiMom->GetYaxis()->SetTitleOffset(1.35);
		hPiMom->SetLineColor(kBlue-6);
		hPiMom->SetFillColor(kBlue-6);
		hPiMom->Draw("hist");

		text->DrawTextNDC(0.47, 0.91, Runs[WhichRun]);

		hPiMomCanvas->SaveAs(PlotPath+"hPiMomCanvas_"+Runs[WhichRun]+".pdf");
		delete hPiMomCanvas;	

		// --------------------------------------------------------------------------------------------------------

		// Bonus Plot: Zoomed in true charged pion momentum

		TH1D* ZoomInhPiMom = new TH1D("ZoomInhPiMom",";True P_{#pi^{#pm}} [GeV/c]",20,0.,0.1);

		tree->Draw("True_PionMomentum>>ZoomInhPiMom",qualifierData,"goff");

		TCanvas* ZoomInhPiMomCanvas = new TCanvas("ZoomInhPiMomCanvas_"+Runs[WhichRun],"ZoomInhPiMomCanvas_"+Runs[WhichRun],205,34,1024,768);
		ZoomInhPiMomCanvas->SetLeftMargin(0.15);
		ZoomInhPiMomCanvas->cd();
		ZoomInhPiMom->SetTitle("MC Events passing CC1p0#pi selection with N>0 #pi^{#pm}");
		ZoomInhPiMom->GetYaxis()->SetTitle("POT Normalized Events");
		ZoomInhPiMom->GetYaxis()->SetTitleOffset(1.35);
		ZoomInhPiMom->SetLineColor(kBlue-6);
		ZoomInhPiMom->SetFillColor(kBlue-6);
		ZoomInhPiMom->Draw("hist");

		text->DrawTextNDC(0.47, 0.91, Runs[WhichRun]);

		ZoomInhPiMomCanvas->SaveAs(PlotPath+"ZoomInhPiMomCanvas_"+Runs[WhichRun]+".pdf");
		delete ZoomInhPiMomCanvas;			

		// --------------------------------------------------------------------------------------------------------

		// Bonus Plot: Extra Zoomed in true charged pion momentum

		TH1D* ExtraZoomInhPiMom = new TH1D("ExtraZoomInhPiMom",";True P_{#pi^{#pm}} [GeV/c]",14,0.,0.07);

		tree->Draw("True_PionMomentum>>ExtraZoomInhPiMom",qualifierData,"goff");

		TCanvas* ExtraZoomInhPiMomCanvas = new TCanvas("ExtraZoomInhPiMomCanvas_"+Runs[WhichRun],"ExtraZoomInhPiMomCanvas_"+Runs[WhichRun],205,34,1024,768);
		ExtraZoomInhPiMomCanvas->SetLeftMargin(0.15);
		ExtraZoomInhPiMomCanvas->cd();
		ExtraZoomInhPiMom->SetTitle("MC Events passing CC1p0#pi selection with N>0 #pi^{#pm}");
		ExtraZoomInhPiMom->GetYaxis()->SetTitle("POT Normalized Events");
		ExtraZoomInhPiMom->GetYaxis()->SetTitleOffset(1.35);
		ExtraZoomInhPiMom->SetLineColor(kBlue-6);
		ExtraZoomInhPiMom->SetFillColor(kBlue-6);
		ExtraZoomInhPiMom->Draw("hist");

		text->DrawTextNDC(0.47, 0.91, Runs[WhichRun]);

		ExtraZoomInhPiMomCanvas->SaveAs(PlotPath+"ExtraZoomInhPiMomCanvas_"+Runs[WhichRun]+".pdf");
		delete ExtraZoomInhPiMomCanvas;		

		cout << "Fraction of charged pions below 70 MeV/c = " << 100. * ExtraZoomInhPiMom->Integral() / hPiMom->Integral() << " %"<< endl; 	

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Resolutions

		// -----------------------------------------------------------------------------------------------------------------------------------------

//		TLegend* leg = new TLegend(0.15,0.75,0.35,0.85);
//		leg->SetTextFont(FontStyle);
//		leg->SetTextSize(0.05);
//		leg->SetBorderSize(0);

//		// Pmu Range

//		TH1D* hPmuRangeReso = new TH1D("hPmuRangeReso",";(Reco-True) P_{#mu} Range [GeV/c];# Events",100,-0.2,0.2);
//		TH1D* hPmuRangeResoUncali = new TH1D("hPmuRangeResoUncali",";(Reco-True) P_{#mu} Range [GeV/c];# Events",100,-0.2,0.2);

//		tree->Draw("(CandidateMu_P_Range" + Recalibrate + "-True_CandidateMu_P)>>hPmuRangeReso",qualifier + " && CandidateMu_EndContainment == 1","goff");
//		tree->Draw("(CandidateMu_P_Range-True_CandidateMu_P)>>hPmuRangeResoUncali",qualifier + " && CandidateMu_EndContainment == 1","goff");

//		TCanvas* PmuRangeResoCanvas = new TCanvas("PmuRangeResoCanvas_"+Runs[WhichRun],"PmuRangeResoCanvas_"+Runs[WhichRun],205,34,1024,768);
//		PmuRangeResoCanvas->cd();

//		hPmuRangeReso->SetLineColor(kOrange+7);
//		hPmuRangeReso->SetMarkerColor(kOrange+7);
//		hPmuRangeReso->SetMarkerSize(2.);
//		hPmuRangeReso->SetMarkerStyle(20);

//		hPmuRangeResoUncali->SetLineColor(kBlack);
//		hPmuRangeResoUncali->SetMarkerColor(kBlack);
//		hPmuRangeResoUncali->SetMarkerSize(2.);
//		hPmuRangeResoUncali->SetMarkerStyle(20);

//		hPmuRangeResoUncali->Draw("p0 same");
//		hPmuRangeReso->Draw("p0 same");

//		leg->AddEntry(hPmuRangeReso,"Calibrated","p");
//		leg->AddEntry(hPmuRangeResoUncali,"Uncalibrated","p");
//		leg->Draw();

//		TLine* line = new TLine(0,0,0,1.05*hPmuRangeResoUncali->GetMaximum());
//		line->SetLineColor(kBlack);
//		line->SetLineStyle(kDashed);
//		line->Draw();

//		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

//		PmuRangeResoCanvas->SaveAs(PlotPath+"PmuRangeResoCanvas_"+Runs[WhichRun]+".pdf");
//		delete PmuRangeResoCanvas;

//		// -----------------------------------------------------------------------------------------------------------------------------------------

//		// Pp Range

//		TH1D* hPpRangeReso = new TH1D("hPpRangeReso",";(Reco-True) P_{p} Range [GeV/c];# Events",100,-0.2,0.2);
//		TH1D* hPpRangeResoUncali = new TH1D("hPpRangeResoUncali",";(Reco-True) P_{p} Range [GeV/c];# Events",100,-0.2,0.2);

//		tree->Draw("(CandidateP_P_Range" + Recalibrate + "-True_CandidateP_P)>>hPpRangeReso",qualifier,"goff");
//		tree->Draw("(CandidateP_P_Range-True_CandidateP_P)>>hPpRangeResoUncali",qualifier,"goff");

//		TCanvas* PpRangeResoCanvas = new TCanvas("PpRangeResoCanvas_"+Runs[WhichRun],"PpRangeResoCanvas_"+Runs[WhichRun],205,34,1024,768);
//		PpRangeResoCanvas->cd();

//		hPpRangeReso->SetLineColor(kOrange+7);
//		hPpRangeReso->SetMarkerColor(kOrange+7);
//		hPpRangeReso->SetMarkerSize(2.);
//		hPpRangeReso->SetMarkerStyle(20);

//		hPpRangeResoUncali->SetLineColor(kBlack);
//		hPpRangeResoUncali->SetMarkerColor(kBlack);
//		hPpRangeResoUncali->SetMarkerSize(2.);
//		hPpRangeResoUncali->SetMarkerStyle(20);

//		hPpRangeResoUncali->Draw("p0 same");
//		hPpRangeReso->Draw("p0 same");

//		leg->Draw();

//		TLine* linePpRange = new TLine(0,0,0,1.05*hPpRangeResoUncali->GetMaximum());
//		linePpRange->SetLineColor(kBlack);
//		linePpRange->SetLineStyle(kDashed);
//		linePpRange->Draw();

//		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

//		PpRangeResoCanvas->SaveAs(PlotPath+"PpRangeResoCanvas_"+Runs[WhichRun]+".pdf");
//		delete PpRangeResoCanvas;

//		// -----------------------------------------------------------------------------------------------------------------------------------------

//		// Pmu MCS

//		TH1D* hPmuMCSReso = new TH1D("hPmuMCSReso",";(Reco-True) P_{#mu} MCS [GeV/c];# Events",100,-1.,1.);
//		TH1D* hPmuMCSResoUncali = new TH1D("hPmuMCSResoUncali",";(Reco-True) P_{#mu} MCS [GeV/c];# Events",100,-1.,1.);

//		tree->Draw("(CandidateMu_P_MCS" + Recalibrate + "-True_CandidateMu_P)>>hPmuMCSReso",qualifier + " && CandidateMu_EndContainment == 0","goff");
//		tree->Draw("(CandidateMu_P_MCS-True_CandidateMu_P)>>hPmuMCSResoUncali",qualifier + " && CandidateMu_EndContainment == 0","goff");

//		TCanvas* PmuMCSResoCanvas = new TCanvas("PmuMCSResoCanvas_"+Runs[WhichRun],"PmuMCSResoCanvas_"+Runs[WhichRun],205,34,1024,768);
//		PmuMCSResoCanvas->cd();

//		hPmuMCSReso->SetLineColor(kOrange+7);
//		hPmuMCSReso->SetMarkerColor(kOrange+7);
//		hPmuMCSReso->SetMarkerSize(2.);
//		hPmuMCSReso->SetMarkerStyle(20);

//		hPmuMCSResoUncali->SetLineColor(kBlack);
//		hPmuMCSResoUncali->SetMarkerColor(kBlack);
//		hPmuMCSResoUncali->SetMarkerSize(2.);
//		hPmuMCSResoUncali->SetMarkerStyle(20);

//		hPmuMCSResoUncali->Draw("p0 same");
//		hPmuMCSReso->Draw("p0 same");

//		leg->Draw();

//		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

//		TLine* linePmuMCS = new TLine(0,0,0,1.05*hPmuMCSResoUncali->GetMaximum());
//		linePmuMCS->SetLineColor(kBlack);
//		linePmuMCS->SetLineStyle(kDashed);
//		linePmuMCS->Draw();

//		PmuMCSResoCanvas->SaveAs(PlotPath+"PmuMCSResoCanvas_"+Runs[WhichRun]+".pdf");
//		delete PmuMCSResoCanvas;

//		// -----------------------------------------------------------------------------------------------------------------------------------------

//		// Delta AlphaT

//		TH1D* hDeltaAlphaTReso = new TH1D("hDeltaAlphaTReso",";(Reco-True) #delta#alpha_{T} [deg];# Events",100,-180,180);
//		TH1D* hDeltaAlphaTResoUncali = new TH1D("hDeltaAlphaTResoUncali",";(Reco-True) #delta#alpha_{T} [deg];# Events",100,-180,180);

//		tree->Draw("(Reco_DeltaAlphaT" + Recalibrate + "-True_DeltaAlphaT)>>hDeltaAlphaTReso",qualifier,"goff");
//		tree->Draw("(Reco_DeltaAlphaT-True_DeltaAlphaT)>>hDeltaAlphaTResoUncali",qualifier,"goff");

//		TCanvas* DeltaAlphaTResoCanvas = new TCanvas("DeltaAlphaTResoCanvas_"+Runs[WhichRun],"DeltaAlphaTResoCanvas_"+Runs[WhichRun],205,34,1024,768);
//		DeltaAlphaTResoCanvas->cd();

//		hDeltaAlphaTReso->SetLineColor(kOrange+7);
//		hDeltaAlphaTReso->SetMarkerColor(kOrange+7);
//		hDeltaAlphaTReso->SetMarkerSize(2.);
//		hDeltaAlphaTReso->SetMarkerStyle(20);

//		hDeltaAlphaTResoUncali->SetLineColor(kBlack);
//		hDeltaAlphaTResoUncali->SetMarkerColor(kBlack);
//		hDeltaAlphaTResoUncali->SetMarkerSize(2.);
//		hDeltaAlphaTResoUncali->SetMarkerStyle(20);

//		hDeltaAlphaTResoUncali->Draw("p0 same");
//		hDeltaAlphaTReso->Draw("p0 same");

//		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

//		leg->Draw();

//		TLine* lineDeltaAlphaT = new TLine(0,0,0,1.05*hDeltaAlphaTResoUncali->GetMaximum());
//		lineDeltaAlphaT->SetLineColor(kBlack);
//		lineDeltaAlphaT->SetLineStyle(kDashed);
//		lineDeltaAlphaT->Draw();

//		DeltaAlphaTResoCanvas->SaveAs(PlotPath+"DeltaAlphaTResoCanvas_"+Runs[WhichRun]+".pdf");
//		delete DeltaAlphaTResoCanvas;

//		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Delta PT

		TH1D* hDeltaPTReso = new TH1D("hDeltaPTReso",";#deltap_{T} resolution [%];# Events",100,-60,60);
		tree->Draw("(Reco_Pt" + Recalibrate + "-True_Pt)/True_Pt*100.>>hDeltaPTReso",qualifier,"goff");

		TCanvas* DeltaPTResoCanvas = new TCanvas("DeltaPTResoCanvas_"+Runs[WhichRun],"DeltaPTResoCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPTResoCanvas->cd();
		DeltaPTResoCanvas->SetBottomMargin(0.11);		

		hDeltaPTReso->GetXaxis()->CenterTitle();
		hDeltaPTReso->SetLineColor(kOrange+7);
		hDeltaPTReso->SetMarkerColor(kOrange+7);
		hDeltaPTReso->SetMarkerSize(2.);
		hDeltaPTReso->SetMarkerStyle(20);

		hDeltaPTReso->Draw("p0 same");

		TF1* fPT = new TF1("fPT","gaus",-30,30);
		hDeltaPTReso->Fit(fPT,"RQ0");

		double mean = fPT->GetParameter(1);
		double sigma = fPT->GetParameter(2);	

		text->DrawLatexNDC(0.35, 0.93, Runs[WhichRun]+", #sigma = " + TString(std::to_string(sigma)) + " %");			

		DeltaPTResoCanvas->SaveAs(PlotPath+"DeltaPTResoCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPTResoCanvas;

//		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Delta PL

		TH1D* hDeltaPLReso = new TH1D("hDeltaPLReso",";#deltap_{L} resolution [%];# Events",100,-60,60);
		tree->Draw("(Reco_PL" + Recalibrate + "-True_PL)/True_PL*100.>>hDeltaPLReso",qualifier,"goff");

		TCanvas* DeltaPLResoCanvas = new TCanvas("DeltaPLResoCanvas_"+Runs[WhichRun],"DeltaPLResoCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPLResoCanvas->cd();
		DeltaPLResoCanvas->SetBottomMargin(0.11);		

		hDeltaPLReso->GetXaxis()->CenterTitle();
		hDeltaPLReso->SetLineColor(kOrange+7);
		hDeltaPLReso->SetMarkerColor(kOrange+7);
		hDeltaPLReso->SetMarkerSize(2.);
		hDeltaPLReso->SetMarkerStyle(20);

		hDeltaPLReso->Draw("p0 same");

		TF1* fPL = new TF1("fPL","gaus",-30,30);
		hDeltaPLReso->Fit(fPL,"RQ0");

		double meanPL = fPL->GetParameter(1);
		double sigmaPL = fPL->GetParameter(2);	

		text->DrawLatexNDC(0.35, 0.93, Runs[WhichRun]+", #sigma = " + TString(std::to_string(sigmaPL)) + " %");			

		DeltaPLResoCanvas->SaveAs(PlotPath+"DeltaPLResoCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPLResoCanvas;		

//		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Delta PTx

		TH1D* hDeltaPTxReso = new TH1D("hDeltaPTxReso",";#deltap_{T,x} resolution [%];# Events",100,-70,70);
		tree->Draw("(Reco_Ptx" + Recalibrate + "-True_Ptx)/True_Ptx*100.>>hDeltaPTxReso",qualifier,"goff");

		TCanvas* DeltaPTxResoCanvas = new TCanvas("DeltaPTxResoCanvas_"+Runs[WhichRun],"DeltaPTxResoCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPTxResoCanvas->cd();
		DeltaPTxResoCanvas->SetBottomMargin(0.11);		

		hDeltaPTxReso->GetXaxis()->CenterTitle();
		hDeltaPTxReso->SetLineColor(kOrange+7);
		hDeltaPTxReso->SetMarkerColor(kOrange+7);
		hDeltaPTxReso->SetMarkerSize(2.);
		hDeltaPTxReso->SetMarkerStyle(20);

		hDeltaPTxReso->Draw("p0 same");

		TF1* fPTx = new TF1("fPTx","gaus",-30,30);
		hDeltaPTxReso->Fit(fPTx,"RQ0");

		double meanx = fPTx->GetParameter(1);
		double sigmax = fPTx->GetParameter(2);	

		text->DrawLatexNDC(0.35, 0.93, Runs[WhichRun]+", #sigma = " + TString(std::to_string(sigmax)) + " %");			

		DeltaPTxResoCanvas->SaveAs(PlotPath+"DeltaPTxResoCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPTxResoCanvas;	
		
//		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Delta PTy

		TH1D* hDeltaPTyReso = new TH1D("hDeltaPTyReso",";#deltap_{T,y} resolution [%];# Events",100,-70,70);
		tree->Draw("(Reco_Pty" + Recalibrate + "-True_Pty)/True_Pty*100.>>hDeltaPTyReso",qualifier,"goff");

		TCanvas* DeltaPTyResoCanvas = new TCanvas("DeltaPTyResoCanvas_"+Runs[WhichRun],"DeltaPTyResoCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPTyResoCanvas->cd();
		DeltaPTyResoCanvas->SetBottomMargin(0.11);		

		hDeltaPTyReso->GetXaxis()->CenterTitle();
		hDeltaPTyReso->SetLineColor(kOrange+7);
		hDeltaPTyReso->SetMarkerColor(kOrange+7);
		hDeltaPTyReso->SetMarkerSize(2.);
		hDeltaPTyReso->SetMarkerStyle(20);

		hDeltaPTyReso->Draw("p0 same");

		TF1* fPTy = new TF1("fPTy","gaus",-30,30);
		hDeltaPTyReso->Fit(fPTy,"RQ0");

		double meany = fPTy->GetParameter(1);
		double sigmay = fPTy->GetParameter(2);	

		text->DrawLatexNDC(0.35, 0.93, Runs[WhichRun]+", #sigma = " + TString(std::to_string(sigmay)) + " %");			

		DeltaPTyResoCanvas->SaveAs(PlotPath+"DeltaPTyResoCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPTyResoCanvas;

//		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Delta Pn,proxy

		TH1D* hDeltaPnReso = new TH1D("hDeltaPnReso",";P_{n,proxy} resolution [%];# Events",100,-70,70);
		tree->Draw("(Reco_Pn" + Recalibrate + "-True_Pn)/True_Pn*100.>>hDeltaPnReso",qualifier,"goff");

		TCanvas* DeltaPnResoCanvas = new TCanvas("DeltaPnResoCanvas_"+Runs[WhichRun],"DeltaPnResoCanvas_"+Runs[WhichRun],205,34,1024,768);
		DeltaPnResoCanvas->cd();
		DeltaPnResoCanvas->SetBottomMargin(0.11);		

		hDeltaPnReso->GetXaxis()->CenterTitle();
		hDeltaPnReso->SetLineColor(kOrange+7);
		hDeltaPnReso->SetMarkerColor(kOrange+7);
		hDeltaPnReso->SetMarkerSize(2.);
		hDeltaPnReso->SetMarkerStyle(20);

		hDeltaPnReso->Draw("p0 same");

		TF1* fPn = new TF1("fPn","gaus",-30,30);
		hDeltaPnReso->Fit(fPn,"RQ0");

		double meanPn = fPn->GetParameter(1);
		double sigmaPn = fPn->GetParameter(2);	

		text->DrawLatexNDC(0.35, 0.93, Runs[WhichRun]+", #sigma = " + TString(std::to_string(sigmaPn)) + " %");			

		DeltaPnResoCanvas->SaveAs(PlotPath+"DeltaPnResoCanvas_"+Runs[WhichRun]+".pdf");
		delete DeltaPnResoCanvas;		

//		// -----------------------------------------------------------------------------------------------------------------------------------------

		// kMiss

		TH1D* hkMissReso = new TH1D("hkMissReso",";k_{Miss} resolution [%];# Events",100,-60,60);
		tree->Draw("(Reco_kMiss" + Recalibrate + "-True_kMiss)/True_kMiss*100.>>hkMissReso",qualifier,"goff");

		TCanvas* kMissResoCanvas = new TCanvas("kMissResoCanvas_"+Runs[WhichRun],"kMissResoCanvas_"+Runs[WhichRun],205,34,1024,768);
		kMissResoCanvas->cd();
		kMissResoCanvas->SetBottomMargin(0.11);		

		hkMissReso->GetXaxis()->CenterTitle();
		hkMissReso->SetLineColor(kOrange+7);
		hkMissReso->SetMarkerColor(kOrange+7);
		hkMissReso->SetMarkerSize(2.);
		hkMissReso->SetMarkerStyle(20);

		hkMissReso->Draw("p0 same");

		TF1* fkMiss = new TF1("fkMiss","gaus",-30,30);
		hkMissReso->Fit(fkMiss,"RQ0");

		double meankMiss = fkMiss->GetParameter(1);
		double sigmakMiss = fkMiss->GetParameter(2);	

		text->DrawLatexNDC(0.35, 0.93, Runs[WhichRun]+", #sigma = " + TString(std::to_string(sigmakMiss)) + " %");			

		kMissResoCanvas->SaveAs(PlotPath+"kMissResoCanvas_"+Runs[WhichRun]+".pdf");
		delete kMissResoCanvas;

//		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Neutron multiplicity

		TH1D* hNeutronMulti = new TH1D("hNeutronMulti",";# neutrons;# Events",11,-0.5,10.5);
		TH1D* hNeutronMultiQE = new TH1D("hNeutronMultiQE",";# neutrons;# Events",11,-0.5,10.5);
		TH1D* hNeutronMultiMEC = new TH1D("hNeutronMultiMEC",";# neutrons;# Events",11,-0.5,10.5);		

		tree->Draw("NumberNeutrons>>hNeutronMulti",qualifier,"goff");
		tree->Draw("NumberNeutrons>>hNeutronMultiQE",qualifier + " && MCParticle_Mode == 0","goff");
		tree->Draw("NumberNeutrons>>hNeutronMultiMEC",qualifier + " && MCParticle_Mode == 10","goff");				

		TCanvas* NeutronMultiCanvas = new TCanvas("NeutronMultiCanvas_"+Runs[WhichRun],"NeutronMultiCanvas_"+Runs[WhichRun],205,34,1024,768);
		NeutronMultiCanvas->cd();
		NeutronMultiCanvas->SetBottomMargin(0.11);		

		hNeutronMulti->GetXaxis()->CenterTitle();
		hNeutronMulti->SetLineColor(kOrange+7);
		hNeutronMulti->SetMarkerColor(kOrange+7);
		hNeutronMulti->SetMarkerSize(2.);
		hNeutronMulti->SetMarkerStyle(20);
		hNeutronMulti->Draw("p0 text same");	

		hNeutronMultiQE->SetLineColor(kGreen+2);
		hNeutronMultiQE->SetMarkerColor(kGreen+2);
		hNeutronMultiQE->SetMarkerSize(2.);
		hNeutronMultiQE->SetMarkerStyle(20);
		hNeutronMultiQE->Draw("p0 text same");

		hNeutronMultiMEC->SetLineColor(kBlue+1);
		hNeutronMultiMEC->SetMarkerColor(kBlue+1);
		hNeutronMultiMEC->SetMarkerSize(2.);
		hNeutronMultiMEC->SetMarkerStyle(20);
		hNeutronMultiMEC->Draw("p0 text same");				

		text->DrawLatexNDC(0.47, 0.93, Runs[WhichRun]);			

		NeutronMultiCanvas->SaveAs(PlotPath+"NeutronMultiCanvas_"+Runs[WhichRun]+".pdf");
		delete NeutronMultiCanvas;			

//		// -----------------------------------------------------------------------------------------------------------------------------------------

//		// Delta PhiT

//		TH1D* hDeltaPhiTReso = new TH1D("hDeltaPhiTReso",";(Reso-True) #delta#phi_{T} [deg];# Events",100,-30,30);
//		TH1D* hDeltaPhiTResoUncali = new TH1D("hDeltaPhiTResoUncali",";(Reso-True) #delta#phi_{T} [deg];# Events",100,-30,30);

//		tree->Draw("(Reco_DeltaPhiT" + Recalibrate + "-True_DeltaPhiT)>>hDeltaPhiTReso",qualifier,"goff");
//		tree->Draw("(Reco_DeltaPhiT-True_DeltaPhiT)>>hDeltaPhiTResoUncali",qualifier,"goff");

//		TCanvas* DeltaPhiTResoCanvas = new TCanvas("DeltaPhiTResoCanvas_"+Runs[WhichRun],"DeltaPhiTResoCanvas_"+Runs[WhichRun],205,34,1024,768);
//		DeltaPhiTResoCanvas->cd();

//		hDeltaPhiTReso->SetLineColor(kOrange+7);
//		hDeltaPhiTReso->SetMarkerColor(kOrange+7);
//		hDeltaPhiTReso->SetMarkerSize(2.);
//		hDeltaPhiTReso->SetMarkerStyle(20);

//		hDeltaPhiTResoUncali->SetLineColor(kBlack);
//		hDeltaPhiTResoUncali->SetMarkerColor(kBlack);
//		hDeltaPhiTResoUncali->SetMarkerSize(2.);
//		hDeltaPhiTResoUncali->SetMarkerStyle(20);

//		hDeltaPhiTResoUncali->Draw("p0 same");
//		hDeltaPhiTReso->Draw("p0 same");

//		leg->Draw();

//		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

//		TLine* lineDeltaPhiT = new TLine(0,0,0,1.05*hDeltaPhiTResoUncali->GetMaximum());
//		lineDeltaPhiT->SetLineColor(kBlack);
//		lineDeltaPhiT->SetLineStyle(kDashed);
//		lineDeltaPhiT->Draw();

//		DeltaPhiTResoCanvas->SaveAs(PlotPath+"DeltaPhiTResoCanvas_"+Runs[WhichRun]+".pdf");
//		delete DeltaPhiTResoCanvas;

//		// -----------------------------------------------------------------------------------------------------------------------------------------
//		// -----------------------------------------------------------------------------------------------------------------------------------------

//		TLegend* legTrunc = new TLegend(0.15,0.65,0.35,0.85);
//		legTrunc->SetTextSize(0.05);
//		legTrunc->SetTextFont(132);
//		legTrunc->SetBorderSize(0);

//		// 1D Muon Truncated dEdx @ RR = 0

//		TCanvas* MuTruncdEdxCanvas = new TCanvas("MuTruncdEdxCanvas_"+Runs[WhichRun],"MuTruncdEdxCanvas_"+Runs[WhichRun],205,34,1024,768);
//		MuTruncdEdxCanvas->cd();

//		int NBinsMu = 60;
//		double XmindEdxMu = 0, XmaxdEdxMu = 5;

//		TH1D* PlaygroundPlotPlane2Mu = new TH1D("PlaygroundPlotPlane2Mu",";#mu Trunc dEdx @ RR = 0 [MeV/cm]",NBinsMu,XmindEdxMu,XmaxdEdxMu);
//		tree->Draw("CandidateMu_Plane2_LastEDep>>PlaygroundPlotPlane2Mu","("+qualifierNoHitSumCut+")*POTWeight","goff");
//		TH1D* PlaygroundPlotPlane1Mu = new TH1D("PlaygroundPlotPlane1Mu","#mu Trunc dEdx @ RR = 0 [MeV/cm]",NBinsMu,XmindEdxMu,XmaxdEdxMu);
//		tree->Draw("CandidateMu_Plane1_LastEDep>>PlaygroundPlotPlane1Mu","("+qualifierNoHitSumCut+")*POTWeight","goff");
//		TH1D* PlaygroundPlotPlane0Mu = new TH1D("PlaygroundPlotPlane0Mu","#mu Trunc dEdx @ RR = 0 [MeV/cm]",NBinsMu,XmindEdxMu,XmaxdEdxMu);
//		tree->Draw("CandidateMu_Plane0_LastEDep>>PlaygroundPlotPlane0Mu","("+qualifierNoHitSumCut+")*POTWeight","goff");

//		double MaxMu = PlaygroundPlotPlane2Mu->GetMaximum();
//		MaxMu = TMath::Max(MaxMu,PlaygroundPlotPlane0Mu->GetMaximum());
//		MaxMu = TMath::Max(MaxMu,PlaygroundPlotPlane1Mu->GetMaximum());

//		PlaygroundPlotPlane2Mu->SetLineWidth(3);PlaygroundPlotPlane2Mu->SetLineColor(kBlack);
//		PlaygroundPlotPlane2Mu->GetYaxis()->SetTitle("POT Normalized Events");
//		PlaygroundPlotPlane2Mu->GetYaxis()->SetRangeUser(0,1.05*MaxMu);
//		legTrunc->AddEntry(PlaygroundPlotPlane2Mu,"Plane 2","l");
//		PlaygroundPlotPlane2Mu->Draw("same");


//		PlaygroundPlotPlane1Mu->SetLineWidth(3);PlaygroundPlotPlane1Mu->SetLineColor(kBlue);
//		legTrunc->AddEntry(PlaygroundPlotPlane1Mu,"Plane 1","l");
//		PlaygroundPlotPlane1Mu->Draw("same");

//		PlaygroundPlotPlane0Mu->SetLineWidth(3);PlaygroundPlotPlane0Mu->SetLineColor(kOrange+7);
//		legTrunc->AddEntry(PlaygroundPlotPlane0Mu,"Plane 0","l");
//		PlaygroundPlotPlane0Mu->Draw("same");

//		legTrunc->Draw();

//		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

//		MuTruncdEdxCanvas->SaveAs(PlotPath+"MuTruncdEdxCanvas_"+Runs[WhichRun]+".pdf");
//		delete MuTruncdEdxCanvas;

//		// -----------------------------------------------------------------------------------------------------------------------------------------

//		// 1D Proton Truncated dEdx @ RR = 0

//		TCanvas* PTruncdEdxCanvas = new TCanvas("PTruncdEdxCanvas_"+Runs[WhichRun],"PTruncdEdxCanvas_"+Runs[WhichRun],205,34,1024,768);
//		PTruncdEdxCanvas->cd();

//		int NBinsP = 60;
//		double XmindEdxP = 0, XmaxdEdxP = 12;

//		TH1D* PlaygroundPlotPlane2P = new TH1D("PlaygroundPlotPlane2P",";p Trunc dEdx @ RR = 0 [MeV/cm]",NBinsP,XmindEdxP,XmaxdEdxP);
//		tree->Draw("CandidateP_Plane2_LastEDep>>PlaygroundPlotPlane2P","("+qualifierNoHitSumCut+")*POTWeight","goff");
//		TH1D* PlaygroundPlotPlane1P = new TH1D("PlaygroundPlotPlane1P","p Trunc dEdx @ RR = 0 [MeV/cm]",NBinsP,XmindEdxP,XmaxdEdxP);
//		tree->Draw("CandidateP_Plane1_LastEDep>>PlaygroundPlotPlane1P","("+qualifierNoHitSumCut+")*POTWeight","goff");
//		TH1D* PlaygroundPlotPlane0P = new TH1D("PlaygroundPlotPlane0P","p Trunc dEdx @ RR = 0 [MeV/cm]",NBinsP,XmindEdxP,XmaxdEdxP);
//		tree->Draw("CandidateP_Plane0_LastEDep>>PlaygroundPlotPlane0P","("+qualifierNoHitSumCut+")*POTWeight","goff");

//		double MaxP = PlaygroundPlotPlane2P->GetMaximum();
//		MaxP = TMath::Max(MaxP,PlaygroundPlotPlane0P->GetMaximum());
//		MaxP = TMath::Max(MaxP,PlaygroundPlotPlane1P->GetMaximum());

//		PlaygroundPlotPlane2P->SetLineWidth(3);PlaygroundPlotPlane2P->SetLineColor(kBlack);
//		PlaygroundPlotPlane2P->GetYaxis()->SetTitle("POT Normalized Events");
//		PlaygroundPlotPlane2P->GetYaxis()->SetRangeUser(0,1.05*MaxP);
//		PlaygroundPlotPlane2P->Draw("same");

//		PlaygroundPlotPlane1P->SetLineWidth(3);PlaygroundPlotPlane1P->SetLineColor(kBlue);
//		PlaygroundPlotPlane1P->Draw("same");

//		PlaygroundPlotPlane0P->SetLineWidth(3);PlaygroundPlotPlane0P->SetLineColor(kOrange+7);
//		PlaygroundPlotPlane0P->Draw("same");

//		legTrunc->Draw();

//		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

//		PTruncdEdxCanvas->SaveAs(PlotPath+"PTruncdEdxCanvas_"+Runs[WhichRun]+".pdf");
//		delete PTruncdEdxCanvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Calorimetry

		// -----------------------------------------------------------------------------------------------------------------------------------------
/*
		// Exiting Muon Truncated dEdx vs Res Range Plane 0

		TH2D* hMuonTruncdEdxRRPlane0Exit = new TH2D("hMuonTruncdEdxRRPlane0Exit",";Muon Residual Range Plane 0 [cm];Truncated Muon dE/dx Plane 0 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane0_TruncdEdx:CandidateMu_Plane0_ResidualRange>>hMuonTruncdEdxRRPlane0Exit",qualifier + " && CandidateMu_EndContainment == 0","goff");

		TCanvas* MuonTruncdEdxRRPlane0CanvasExit = new TCanvas("MuonTruncdEdxRRPlane0CanvasExit_"+Runs[WhichRun],"MuonTruncdEdxRRPlane0CanvasExit_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane0CanvasExit->cd();
		hMuonTruncdEdxRRPlane0Exit->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane0Exit->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane0CanvasExit->SaveAs(PlotPath+"MuonTruncdEdxRRPlane0CanvasExit_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane0CanvasExit;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Exiting Muon Truncated dEdx vs Res Range Plane 1

		TH2D* hMuonTruncdEdxRRPlane1Exit = new TH2D("hMuonTruncdEdxRRPlane1Exit",";Muon Residual Range Plane 1 [cm];Truncated Muon dE/dx Plane 1 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane1_TruncdEdx:CandidateMu_Plane1_ResidualRange>>hMuonTruncdEdxRRPlane1Exit",qualifier + " && CandidateMu_EndContainment == 0","goff");

		TCanvas* MuonTruncdEdxRRPlane1CanvasExit = new TCanvas("MuonTruncdEdxRRPlane1CanvasExit_"+Runs[WhichRun],"MuonTruncdEdxRRPlane1CanvasExit_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane1CanvasExit->cd();
		hMuonTruncdEdxRRPlane1Exit->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane1Exit->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane1CanvasExit->SaveAs(PlotPath+"MuonTruncdEdxRRPlane1CanvasExit_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane1CanvasExit;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Exiting Muon Truncated dEdx vs Res Range Plane 2

		TH2D* hMuonTruncdEdxRRPlane2Exit = new TH2D("hMuonTruncdEdxRRPlane2Exit",";Muon Residual Range Plane 2 [cm];Truncated Muon dE/dx Plane 2 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane2_TruncdEdx:CandidateMu_Plane2_ResidualRange>>hMuonTruncdEdxRRPlane2Exit",qualifier + " && CandidateMu_EndContainment == 0","goff");

		TCanvas* MuonTruncdEdxRRPlane2CanvasExit = new TCanvas("MuonTruncdEdxRRPlane2CanvasExit_"+Runs[WhichRun],"MuonTruncdEdxRRPlane2CanvasExit_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane2CanvasExit->cd();
		hMuonTruncdEdxRRPlane2Exit->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane2Exit->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane2CanvasExit->SaveAs(PlotPath+"MuonTruncdEdxRRPlane2CanvasExit_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane2CanvasExit;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Exiting Muon Truncated dEdx vs Res Range Plane 0 W/O min hit sum

		TH2D* hMuonTruncdEdxRRPlane0NoMinHitSumExit = new TH2D("hMuonTruncdEdxRRPlane0NoMinHitSumExit",";Muon Residual Range Plane 0 [cm];Truncated Muon dE/dx Plane 0 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane0_TruncdEdx:CandidateMu_Plane0_ResidualRange>>hMuonTruncdEdxRRPlane0NoMinHitSumExit",qualifierNoHitSumCut + " && CandidateMu_EndContainment == 0","goff");

		TCanvas* MuonTruncdEdxRRPlane0CanvasNoMinHitSumExit = new TCanvas("MuonTruncdEdxRRPlane0CanvasNoMinHitSumExit_"+Runs[WhichRun],"MuonTruncdEdxRRPlane0CanvasNoMinHitSumExit_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane0CanvasNoMinHitSumExit->cd();
		hMuonTruncdEdxRRPlane0NoMinHitSumExit->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane0NoMinHitSumExit->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane0CanvasNoMinHitSumExit->SaveAs(PlotPath+"MuonTruncdEdxRRPlane0CanvasNoMinHitSumExit_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane0CanvasNoMinHitSumExit;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Exiting Muon Truncated dEdx vs Res Range Plane 1 W/O min hit sum

		TH2D* hMuonTruncdEdxRRPlane1NoMinHitSumExit = new TH2D("hMuonTruncdEdxRRPlane1NoMinHitSumExit",";Muon Residual Range Plane 1 [cm];Truncated Muon dE/dx Plane 1 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane1_TruncdEdx:CandidateMu_Plane1_ResidualRange>>hMuonTruncdEdxRRPlane1NoMinHitSumExit",qualifierNoHitSumCut + " && CandidateMu_EndContainment == 0","goff");

		TCanvas* MuonTruncdEdxRRPlane1CanvasNoMinHitSumExit = new TCanvas("MuonTruncdEdxRRPlane1CanvasNoMinHitSumExit_"+Runs[WhichRun],"MuonTruncdEdxRRPlane1CanvasNoMinHitSum_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane1CanvasNoMinHitSumExit->cd();
		hMuonTruncdEdxRRPlane1NoMinHitSumExit->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane1NoMinHitSumExit->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane1CanvasNoMinHitSumExit->SaveAs(PlotPath+"MuonTruncdEdxRRPlane1CanvasNoMinHitSumExit_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane1CanvasNoMinHitSumExit;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Exiting Muon Truncated dEdx vs Res Range Plane 2 W/O min hit sum

		TH2D* hMuonTruncdEdxRRPlane2NoMinHitSumExit = new TH2D("hMuonTruncdEdxRRPlane2NoMinHitSumExit",";Muon Residual Range Plane 2 [cm];Truncated Muon dE/dx Plane 2 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane2_TruncdEdx:CandidateMu_Plane2_ResidualRange>>hMuonTruncdEdxRRPlane2NoMinHitSumExit",qualifierNoHitSumCut + " && CandidateMu_EndContainment == 0","goff");

		TCanvas* MuonTruncdEdxRRPlane2CanvasNoMinHitSumExit = new TCanvas("MuonTruncdEdxRRPlane2CanvasNoMinHitSumExit_"+Runs[WhichRun],"MuonTruncdEdxRRPlane2CanvasNoMinHitSumExit_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane2CanvasNoMinHitSumExit->cd();
		hMuonTruncdEdxRRPlane2NoMinHitSumExit->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane2NoMinHitSumExit->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane2CanvasNoMinHitSumExit->SaveAs(PlotPath+"MuonTruncdEdxRRPlane2CanvasNoMinHitSumExit_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane2CanvasNoMinHitSumExit;

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Contained Muon Truncated dEdx vs Res Range Plane 0

		TH2D* hMuonTruncdEdxRRPlane0 = new TH2D("hMuonTruncdEdxRRPlane0",";Muon Residual Range Plane 0 [cm];Truncated Muon dE/dx Plane 0 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane0_TruncdEdx:CandidateMu_Plane0_ResidualRange>>hMuonTruncdEdxRRPlane0",qualifier + " && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonTruncdEdxRRPlane0Canvas = new TCanvas("MuonTruncdEdxRRPlane0Canvas_"+Runs[WhichRun],"MuonTruncdEdxRRPlane0Canvas_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane0Canvas->cd();
		hMuonTruncdEdxRRPlane0->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane0->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane0Canvas->SaveAs(PlotPath+"MuonTruncdEdxRRPlane0Canvas_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane0Canvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Contained Muon Truncated dEdx vs Res Range Plane 1

		TH2D* hMuonTruncdEdxRRPlane1 = new TH2D("hMuonTruncdEdxRRPlane1",";Muon Residual Range Plane 1 [cm];Truncated Muon dE/dx Plane 1 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane1_TruncdEdx:CandidateMu_Plane1_ResidualRange>>hMuonTruncdEdxRRPlane1",qualifier + " && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonTruncdEdxRRPlane1Canvas = new TCanvas("MuonTruncdEdxRRPlane1Canvas_"+Runs[WhichRun],"MuonTruncdEdxRRPlane1Canvas_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane1Canvas->cd();
		hMuonTruncdEdxRRPlane1->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane1->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane1Canvas->SaveAs(PlotPath+"MuonTruncdEdxRRPlane1Canvas_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane1Canvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Contained Muon Truncated dEdx vs Res Range Plane 2

		TH2D* hMuonTruncdEdxRRPlane2 = new TH2D("hMuonTruncdEdxRRPlane2",";Muon Residual Range Plane 2 [cm];Truncated Muon dE/dx Plane 2 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane2_TruncdEdx:CandidateMu_Plane2_ResidualRange>>hMuonTruncdEdxRRPlane2",qualifier + " && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonTruncdEdxRRPlane2Canvas = new TCanvas("MuonTruncdEdxRRPlane2Canvas_"+Runs[WhichRun],"MuonTruncdEdxRRPlane2Canvas_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane2Canvas->cd();
		hMuonTruncdEdxRRPlane2->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane2->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane2Canvas->SaveAs(PlotPath+"MuonTruncdEdxRRPlane2Canvas_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane2Canvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Contained Muon Truncated dEdx vs Res Range Plane 0 W/O min hit sum

		TH2D* hMuonTruncdEdxRRPlane0NoMinHitSum = new TH2D("hMuonTruncdEdxRRPlane0NoMinHitSum",";Muon Residual Range Plane 0 [cm];Truncated Muon dE/dx Plane 0 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane0_TruncdEdx:CandidateMu_Plane0_ResidualRange>>hMuonTruncdEdxRRPlane0NoMinHitSum",qualifierNoHitSumCut + " && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonTruncdEdxRRPlane0CanvasNoMinHitSum = new TCanvas("MuonTruncdEdxRRPlane0CanvasNoMinHitSum_"+Runs[WhichRun],"MuonTruncdEdxRRPlane0CanvasNoMinHitSum_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane0CanvasNoMinHitSum->cd();
		hMuonTruncdEdxRRPlane0NoMinHitSum->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane0NoMinHitSum->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane0CanvasNoMinHitSum->SaveAs(PlotPath+"MuonTruncdEdxRRPlane0CanvasNoMinHitSum_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane0CanvasNoMinHitSum;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Contained Muon Truncated dEdx vs Res Range Plane 1

		TH2D* hMuonTruncdEdxRRPlane1NoMinHitSum = new TH2D("hMuonTruncdEdxRRPlane1NoMinHitSum",";Muon Residual Range Plane 1 [cm];Truncated Muon dE/dx Plane 1 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane1_TruncdEdx:CandidateMu_Plane1_ResidualRange>>hMuonTruncdEdxRRPlane1NoMinHitSum",qualifierNoHitSumCut + " && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonTruncdEdxRRPlane1CanvasNoMinHitSum = new TCanvas("MuonTruncdEdxRRPlane1CanvasNoMinHitSum_"+Runs[WhichRun],"MuonTruncdEdxRRPlane1CanvasNoMinHitSum_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane1CanvasNoMinHitSum->cd();
		hMuonTruncdEdxRRPlane1NoMinHitSum->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane1NoMinHitSum->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane1CanvasNoMinHitSum->SaveAs(PlotPath+"MuonTruncdEdxRRPlane1CanvasNoMinHitSum_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane1CanvasNoMinHitSum;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Contained Muon Truncated dEdx vs Res Range Plane 2

		TH2D* hMuonTruncdEdxRRPlane2NoMinHitSum = new TH2D("hMuonTruncdEdxRRPlane2NoMinHitSum",";Muon Residual Range Plane 2 [cm];Truncated Muon dE/dx Plane 2 [MeV/cm]",50,0,50,50,0,5);

		tree->Draw("CandidateMu_Plane2_TruncdEdx:CandidateMu_Plane2_ResidualRange>>hMuonTruncdEdxRRPlane2NoMinHitSum",qualifierNoHitSumCut + " && CandidateMu_EndContainment == 1","goff");

		TCanvas* MuonTruncdEdxRRPlane2CanvasNoMinHitSum = new TCanvas("MuonTruncdEdxRRPlane2CanvasNoMinHitSum_"+Runs[WhichRun],"MuonTruncdEdxRRPlane2CanvasNoMinHitSum_"+Runs[WhichRun],205,34,1024,768);
		MuonTruncdEdxRRPlane2CanvasNoMinHitSum->cd();
		hMuonTruncdEdxRRPlane2NoMinHitSum->SetTitleSize(0.08,"t");
		hMuonTruncdEdxRRPlane2NoMinHitSum->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		MuonTruncdEdxRRPlane2CanvasNoMinHitSum->SaveAs(PlotPath+"MuonTruncdEdxRRPlane2CanvasNoMinHitSum_"+Runs[WhichRun]+".pdf");
		delete MuonTruncdEdxRRPlane2CanvasNoMinHitSum;

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Proton Truncated dEdx vs Res Range Plane 0

		TH2D* hProtonTruncdEdxRRPlane0 = new TH2D("hProtonTruncdEdxRRPlane0",";Proton Residual Range Plane 0 [cm];Truncated Proton dE/dx Plane 0 [MeV/cm]",50,0,50,50,0,10);

		tree->Draw("CandidateP_Plane0_TruncdEdx:CandidateP_Plane0_ResidualRange>>hProtonTruncdEdxRRPlane0",qualifier,"goff");

		TCanvas* ProtonTruncdEdxRRPlane0Canvas = new TCanvas("ProtonTruncdEdxRRPlane0Canvas_"+Runs[WhichRun],"ProtonTruncdEdxRRPlane0Canvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonTruncdEdxRRPlane0Canvas->cd();
		hProtonTruncdEdxRRPlane0->SetTitleSize(0.08,"t");
		hProtonTruncdEdxRRPlane0->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonTruncdEdxRRPlane0Canvas->SaveAs(PlotPath+"ProtonTruncdEdxRRPlane0Canvas_"+Runs[WhichRun]+".pdf");
		delete ProtonTruncdEdxRRPlane0Canvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Proton Truncated dEdx vs Res Range Plane 1

		TH2D* hProtonTruncdEdxRRPlane1 = new TH2D("hProtonTruncdEdxRRPlane1",";Proton Residual Range Plane 1 [cm];Truncated Proton dE/dx Plane 1 [MeV/cm]",50,0,50,50,0,10);

		tree->Draw("CandidateP_Plane1_TruncdEdx:CandidateP_Plane1_ResidualRange>>hProtonTruncdEdxRRPlane1",qualifier,"goff");

		TCanvas* ProtonTruncdEdxRRPlane1Canvas = new TCanvas("ProtonTruncdEdxRRPlane1Canvas_"+Runs[WhichRun],"ProtonTruncdEdxRRPlane1Canvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonTruncdEdxRRPlane1Canvas->cd();
		hProtonTruncdEdxRRPlane1->SetTitleSize(0.08,"t");
		hProtonTruncdEdxRRPlane1->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonTruncdEdxRRPlane1Canvas->SaveAs(PlotPath+"ProtonTruncdEdxRRPlane1Canvas_"+Runs[WhichRun]+".pdf");
		delete ProtonTruncdEdxRRPlane1Canvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Proton Truncated dEdx vs Res Range Plane 2

		TH2D* hProtonTruncdEdxRRPlane2 = new TH2D("hProtonTruncdEdxRRPlane2",";Proton Residual Range Plane 2 [cm];Truncated Proton dE/dx Plane 2 [MeV/cm]",50,0,50,50,0,10);

		tree->Draw("CandidateP_Plane2_TruncdEdx:CandidateP_Plane2_ResidualRange>>hProtonTruncdEdxRRPlane2",qualifier,"goff");

		TCanvas* ProtonTruncdEdxRRPlane2Canvas = new TCanvas("ProtonTruncdEdxRRPlane2Canvas_"+Runs[WhichRun],"ProtonTruncdEdxRRPlane2Canvas_"+Runs[WhichRun],205,34,1024,768);
		ProtonTruncdEdxRRPlane2Canvas->cd();
		hProtonTruncdEdxRRPlane2->SetTitleSize(0.08,"t");
		hProtonTruncdEdxRRPlane2->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonTruncdEdxRRPlane2Canvas->SaveAs(PlotPath+"ProtonTruncdEdxRRPlane2Canvas_"+Runs[WhichRun]+".pdf");
		delete ProtonTruncdEdxRRPlane2Canvas;

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Proton Truncated dEdx vs Res Range Plane 0 W/O min hit sum

		TH2D* hProtonTruncdEdxRRPlane0NoMinHitSum = new TH2D("hProtonTruncdEdxRRPlane0NoMinHitSum",";Proton Residual Range Plane 0 [cm];Truncated Proton dE/dx Plane 0 [MeV/cm]",50,0,50,50,0,10);

		tree->Draw("CandidateP_Plane0_TruncdEdx:CandidateP_Plane0_ResidualRange>>hProtonTruncdEdxRRPlane0NoMinHitSum",qualifierNoHitSumCut,"goff");

		TCanvas* ProtonTruncdEdxRRPlane0CanvasNoMinHitSum = new TCanvas("ProtonTruncdEdxRRPlane0CanvasNoMinHitSum_"+Runs[WhichRun],"ProtonTruncdEdxRRPlane0CanvasNoMinHitSum_"+Runs[WhichRun],205,34,1024,768);
		ProtonTruncdEdxRRPlane0CanvasNoMinHitSum->cd();
		hProtonTruncdEdxRRPlane0NoMinHitSum->SetTitleSize(0.08,"t");
		hProtonTruncdEdxRRPlane0NoMinHitSum->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonTruncdEdxRRPlane0CanvasNoMinHitSum->SaveAs(PlotPath+"ProtonTruncdEdxRRPlane0CanvasNoMinHitSum_"+Runs[WhichRun]+".pdf");
		delete ProtonTruncdEdxRRPlane0CanvasNoMinHitSum;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Proton Truncated dEdx vs Res Range Plane 1 W/O min hit sum

		TH2D* hProtonTruncdEdxRRPlane1NoMinHitSum = new TH2D("hProtonTruncdEdxRRPlane1NoMinHitSum",";Proton Residual Range Plane 1 [cm];Truncated Proton dE/dx Plane 1 [MeV/cm]",50,0,50,50,0,10);

		tree->Draw("CandidateP_Plane1_TruncdEdx:CandidateP_Plane1_ResidualRange>>hProtonTruncdEdxRRPlane1NoMinHitSum",qualifierNoHitSumCut,"goff");

		TCanvas* ProtonTruncdEdxRRPlane1CanvasNoMinHitSum = new TCanvas("ProtonTruncdEdxRRPlane1CanvasNoMinHitSum_"+Runs[WhichRun],"ProtonTruncdEdxRRPlane1CanvasNoMinHitSum_"+Runs[WhichRun],205,34,1024,768);
		ProtonTruncdEdxRRPlane1CanvasNoMinHitSum->cd();
		hProtonTruncdEdxRRPlane1NoMinHitSum->SetTitleSize(0.08,"t");
		hProtonTruncdEdxRRPlane1NoMinHitSum->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonTruncdEdxRRPlane1CanvasNoMinHitSum->SaveAs(PlotPath+"ProtonTruncdEdxRRPlane1CanvasNoMinHitSum_"+Runs[WhichRun]+".pdf");
		delete ProtonTruncdEdxRRPlane1CanvasNoMinHitSum;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		// Proton Truncated dEdx vs Res Range Plane 2 W/O min hit sum

		TH2D* hProtonTruncdEdxRRPlane2NoMinHitSum = new TH2D("hProtonTruncdEdxRRPlane2NoMinHitSum",";Proton Residual Range Plane 2 [cm];Truncated Proton dE/dx Plane 2 [MeV/cm]",50,0,50,50,0,10);

		tree->Draw("CandidateP_Plane2_TruncdEdx:CandidateP_Plane2_ResidualRange>>hProtonTruncdEdxRRPlane2NoMinHitSum",qualifierNoHitSumCut,"goff");

		TCanvas* ProtonTruncdEdxRRPlane2CanvasNoMinHitSum = new TCanvas("ProtonTruncdEdxRRPlane2CanvasNoMinHitSum_"+Runs[WhichRun],"ProtonTruncdEdxRRPlane2CanvasNoMinHitSum_"+Runs[WhichRun],205,34,1024,768);
		ProtonTruncdEdxRRPlane2CanvasNoMinHitSum->cd();
		hProtonTruncdEdxRRPlane2NoMinHitSum->SetTitleSize(0.08,"t");
		hProtonTruncdEdxRRPlane2NoMinHitSum->Draw("coltz");

		text->DrawTextNDC(0.47, 0.93, Runs[WhichRun]);

		ProtonTruncdEdxRRPlane2CanvasNoMinHitSum->SaveAs(PlotPath+"ProtonTruncdEdxRRPlane2CanvasNoMinHitSum_"+Runs[WhichRun]+".pdf");
		delete ProtonTruncdEdxRRPlane2CanvasNoMinHitSum;
*/

		// -----------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
