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

void InvestigateBinMigrations() {

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	gStyle->SetTitleSize(0.0,"t");
	gStyle->SetTitleFont(132,"t");

	gStyle->SetTitleOffset(0.9,"x");
	gStyle->SetTitleOffset(1.,"y");
	gStyle->SetTitleSize(0.05,"xyz");
	gStyle->SetTitleFont(132,"xyz");
	gStyle->SetLabelSize(0.05,"xyz");
	gStyle->SetLabelFont(132,"xyz");
	gStyle->SetNdivisions(12,"xyz");

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

		// ---------------------------------------------------------------------------------------------------------------------------------------

		TCanvas* OverlayCanvas = new TCanvas("OverlayCanvas"+Runs[WhichRun],"OverlayCanvas"+Runs[WhichRun],205,34,1024,768);

		TLegend* leg = new TLegend(0.6,0.65,0.8,0.85);
		leg->SetTextSize(0.05);
		leg->SetTextFont(132);
		leg->SetBorderSize(0);

		// ---------------------------------------------------------------------------------------------------------------------------------

//		TString AxisLabel = ";#delta#alpha_{T} [deg];#delta#alpha_{T} resolution [%];"; double Xmin = 0.; double Xmax = 180.;
//		int NBins = 20;
//		TString Reso = "(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100."; TString XVar = "Reco_DeltaAlphaT";

//		TString AxisLabel = ";P_{p} [GeV/c];P_{p} resolution [%];"; double Xmin = ArrayNBinsProtonMomentum[0]; double Xmax = ArrayNBinsProtonMomentum[NBinsProtonMomentum];
//		int NBins = 20;
//		TString Reso = "(CandidateP_P_Range-True_CandidateP_P)/True_CandidateP_P*100."; TString XVar = "CandidateP_P_Range";

		// Effective Efficiencies

//		TString XVar = "Reco_DeltaAlphaT"; TString TrueXVar = "True_DeltaAlphaT"; TString AxisLabel = ";#delta#alpha_{T} [deg];# Events;"; double Xmin = 0.; double Xmax = 180.;
//		TString XVar = "Reco_Pt"; TString TrueXVar = "True_Pt"; TString AxisLabel = ";#deltap_{T} [deg];# Events;"; double Xmin = 0.; double Xmax = 1.;

		// Standard efficiency in true bin

//		TString XVar = "True_Pt"; TString TrueXVar = "True_Pt"; TString AxisLabel = ";#deltap_{T} [GeV/c];Efficiency;"; double Xmin = 0.; double Xmax = 1.;
//		TString XVar = "True_DeltaAlphaT"; TString TrueXVar = "True_DeltaAlphaT"; TString AxisLabel = ";#delta#alpha_{T} [deg];Efficiency;"; double Xmin = 0.; double Xmax = 180.;
//		TString XVar = "True_DeltaPhiT"; TString TrueXVar = "True_DeltaPhiT"; TString AxisLabel = ";#delta#phi_{T} [deg];Efficiency;"; double Xmin = 0.; double Xmax = 180.;

//		TString XVar = "True_CandidateMu_CosTheta"; TString TrueXVar = "Muon_MCParticle_CosTheta"; TString AxisLabel = ";cos#theta_{#mu};Efficiency;"; double Xmin = -1.; double Xmax = 1.;
//		TString XVar = "True_CandidateP_CosTheta"; TString TrueXVar = "Proton_MCParticle_CosTheta"; TString AxisLabel = ";cos#theta_{p};Efficiency;"; double Xmin = -1.; double Xmax = 1.;
//		TString XVar = "True_CandidateMu_Phi"; TString TrueXVar = "Muon_MCParticle_Phi"; TString AxisLabel = ";#phi_{#mu} [deg];Efficiency;"; double Xmin = -180.; double Xmax = 180.;
//		TString XVar = "True_CandidateP_Phi"; TString TrueXVar = "Proton_MCParticle_Phi"; TString AxisLabel = ";#phi_{p} [deg];Efficiency;"; double Xmin = -180.; double Xmax = 180.;
//		TString XVar = "True_CandidateMu_P"; TString TrueXVar = "Muon_MCParticle_Mom"; TString AxisLabel = ";P_{#mu} [GeV/c];Efficiency;"; double Xmin = 0.1; double Xmax = 1.5;
//		TString XVar = "True_CandidateP_P"; TString TrueXVar = "Proton_MCParticle_Mom"; TString AxisLabel = ";P_{p} [GeV/c];Efficiency;"; double Xmin = 0.25; double Xmax = 1.2;

//		TString CutOn = "CandidateMu_CosTheta"; TString CutOnLabel = "cos#theta_{#mu}";	TString TruthCutOn = "Muon_MCParticle_CosTheta";	
//		double Step = 0.2; double XminCut = -1.; double XmaxCut = -0.2; int NBinsCut = (XmaxCut - XminCut) / Step;
//		double Step = 0.2; double XminCut = -0.2; double XmaxCut = 0.4; int NBinsCut = (XmaxCut - XminCut) / Step;
//		double Step = 0.1; double XminCut = 0.4; double XmaxCut = 0.8; int NBinsCut = (XmaxCut - XminCut) / Step;
//		double Step = 0.05; double XminCut = 0.8; double XmaxCut = 1.01; int NBinsCut = (XmaxCut - XminCut) / Step;

//		TString CutOn = "Muon_MCParticle_CosTheta"; TString CutOnLabel = "cos#theta_{#mu}"; TString XVar = "True_DeltaAlphaT";	
//		double Step = 0.05; double XminCut = 0.8; double XmaxCut = 1.01; int NBinsCut = (XmaxCut - XminCut) / Step;	
//		qualifier = "";

//		TString CutOn = "CandidateMu_Phi"; TString CutOnLabel = "#phi_{#mu}"; TString TruthCutOn = "Muon_MCParticle_Phi";
//		double Step = 20;
//		double XminCut = -180.; double XmaxCut = -120.; int NBinsCut = (XmaxCut - XminCut) / Step;
//		double XminCut = -120.; double XmaxCut = -60.; int NBinsCut = (XmaxCut - XminCut) / Step;
//		double XminCut = -60.; double XmaxCut = 0.; int NBinsCut = (XmaxCut - XminCut) / Step;
//		double XminCut = 0.; double XmaxCut = 60.; int NBinsCut = (XmaxCut - XminCut) / Step;
//		double XminCut = 60.; double XmaxCut = 120.; int NBinsCut = (XmaxCut - XminCut) / Step;
//		double XminCut = 120.; double XmaxCut = 180.; int NBinsCut = (XmaxCut - XminCut) / Step;

//		TString AxisLabel = ";P_{p} [GeV/c];P_{p} resolution [%];"; int NBins = 40; double Xmin = ArrayNBinsProtonMomentum[0]; double Xmax = ArrayNBinsProtonMomentum[NBinsProtonMomentum];
//		TString Reso = "(CandidateP_P_Range-True_CandidateP_P)/True_CandidateP_P*100."; TString XVar = "CandidateP_P_Range";

//		TString AxisLabel = ";#delta#phi_{T} [deg];#delta#phi_{T} resolution [%];"; double Xmin = 0.; double Xmax = 180.;
//		int NBins = 36;
//		//int NBins = 1;
//		TString Reso = "(Reco_DeltaPhiT-True_DeltaAlphaT)/True_DeltaPhiT*100."; TString XVar = "Reco_DeltaPhiT";

//		TString AxisLabel = ";cos#theta_{p} [GeV/c];cos#theta_{p} resolution [%];"; int NBins = 40; double Xmin = ArrayNBinsProtonCosTheta[0]; double Xmax = ArrayNBinsProtonCosTheta[NBinsProtonCosTheta];
//		TString Reso = "(CandidateP_CosTheta-True_CandidateP_CosTheta)/True_CandidateP_CosTheta*100."; TString XVar = "CandidateP_CosTheta";

//		TString AxisLabel = ";cos#theta_{#mu} [GeV/c];cos#theta_{#mu} resolution [%];"; int NBins = 40; double Xmin = ArrayNBinsMuonCosTheta[0]; double Xmax = ArrayNBinsMuonCosTheta[NBinsMuonCosTheta];
//		TString Reso = "(CandidateMu_CosTheta-True_CandidateMu_CosTheta)/True_CandidateMu_CosTheta*100."; TString XVar = "CandidateMu_CosTheta";

//		TString AxisLabel = ";P_{#mu} [GeV/c];P_{#mu} resolution [%];"; int NBins = 40; double Xmin = ArrayNBinsMuonMomentum[0]; double Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum];
//		TString Reso = "(CandidateMu_P_Range-True_CandidateMu_P)/True_CandidateMu_P*100."; TString XVar = "CandidateMu_P_Range";

//		TString AxisLabel = ";P_{#mu} [GeV/c];P_{#mu} resolution [%];"; int NBins = 40; double Xmin = ArrayNBinsMuonMomentum[0]; double Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum];
//		TString Reso = "(CandidateMu_P_MCS-True_CandidateMu_P)/True_CandidateMu_P*100."; TString XVar = "CandidateMu_P_MCS";

//		TString AxisLabel = ";P_{#mu} [GeV/c];P_{#mu} resolution [%];"; int NBins = 40; double Xmin = ArrayNBinsMuonMomentum[0]; double Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum];
//		TString Reso = "(CandidateMu_P_MCS-True_CandidateMu_P)/True_CandidateMu_P*100."; TString XVar = "CandidateMu_P_MCS";

//		TString AxisLabel = ";Vertex Y [cm];#delta#alpha_{T} resolution [%];"; double Xmin = -120; double Xmax = 120.;
//		int NBins = 100;
//		//int NBins = 1;
//		TString Reso = "(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100."; TString XVar = "Vertex_Y";

		// ---------------------------------------------------------------------------------------------------------------------------------

//		TProfile* PlaygroundPlotsAll = new TProfile("PlaygroundPlotAll",AxisLabel,NBins,Xmin,Xmax);
//		TProfile* PlaygroundPlots[NBinsCut];

//		TH1D* PlaygroundPlotsAll = new TH1D("PlaygroundPlotAll",AxisLabel,NBins,Xmin,Xmax);
//		TH1D* PlaygroundTruthPlotsAll = new TH1D("PlaygroundTruthPlotAll",AxisLabel,NBins,Xmin,Xmax);

//		TH1D* PlaygroundPlots[NBinsCut];
//		TH1D* PlaygroundTruthPlots[NBinsCut];

//		tree->Draw(Reso+":"+XVar+">>PlaygroundPlotAll",qualifier,"goff");
//		tree->Draw(XVar+":"+Reso+">>PlaygroundPlotAll",qualifier,"goff");
//		tree->Draw(Reso+":"+XVar+">>PlaygroundPlotAll",qualifier,"prof");
//		tree->Draw(XVar+">>PlaygroundPlotAll",qualifier,"goff");
//		treeTruth->Draw(TrueXVar+">>PlaygroundTruthPlotAll","","goff");

//		PlaygroundPlotsAll->SetLineWidth(3);
//		PlaygroundPlotsAll->SetLineColor(kBlack);
//		PlaygroundPlotsAll->Divide(PlaygroundTruthPlotsAll);
//		PlaygroundPlotsAll->GetYaxis()->SetRangeUser(0.,1.05*PlaygroundPlotsAll->GetMaximum());
//		PlaygroundPlotsAll->Draw("hist same");
//		leg->AddEntry(PlaygroundPlotsAll,"All","l");


//		int ColorCounter = 2;

//		for (int i = 0; i < NBinsCut; i++) {

////			PlaygroundPlots[i] = new TProfile("PlaygroundPlot_"+TString(std::to_string(i)),AxisLabel,NBins,Xmin,Xmax);
//			PlaygroundPlots[i] = new TH1D("PlaygroundPlot_"+TString(std::to_string(i)),AxisLabel,NBins,Xmin,Xmax);
//			PlaygroundTruthPlots[i] = new TH1D("PlaygroundTruthPlot_"+TString(std::to_string(i)),AxisLabel,NBins,Xmin,Xmax);

//			TString LowThres = TString(std::to_string(XminCut + i * Step ) );
//			TString LowCut  = CutOn + " > " + LowThres ;
//			TString TruthLowCut  = TruthCutOn + " > " + LowThres ;

//			TString HighThres = TString(std::to_string(XminCut + (i+1) * Step ));
//			TString HighCut  = CutOn + " < " + HighThres ;
//			TString TruthHighCut  = TruthCutOn + " < " + HighThres ;

////			tree->Draw(Reso+":"+XVar+">>PlaygroundPlot_"+TString(std::to_string(i)),qualifier + " && " + LowCut + " && " + HighCut,"goff");
//			tree->Draw(XVar+">>PlaygroundPlot_"+TString(std::to_string(i)),qualifier + " && " + LowCut + " && " + HighCut,"goff");
////			treeTruth->Draw(TrueXVar+">>PlaygroundTruthPlot_"+TString(std::to_string(i)),TruthLowCut + " && " + TruthHighCut,"goff");

//			if (ColorCounter == 10) { ColorCounter++; }
//			PlaygroundPlots[i]->SetLineColor(ColorCounter);
//			PlaygroundPlots[i]->SetLineWidth(3);
////			PlaygroundPlots[i]->Divide(PlaygroundTruthPlots[i]);
//			PlaygroundPlots[i]->Draw("hist same");

//			leg->AddEntry(PlaygroundPlots[i],LowThres + " < " + CutOnLabel + " < " + HighThres,"l");

//			ColorCounter++;

//		}

//		leg->Draw();

		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

//		TString AxisLabel = ";P_{p} [GeV/c];P_{p} resolution [%];"; double Xmin = ArrayNBinsProtonMomentum[0]; double Xmax = ArrayNBinsProtonMomentum[NBinsProtonMomentum];
//		TString Reso = "(CandidateP_P_Range-True_CandidateP_P)/True_CandidateP_P*100."; TString XVar = "CandidateP_P_Range"; int NBins = 20;

//		TString AxisLabel = ";cos#theta_{p};cos#theta_{p} resolution [%];"; double Xmin = ArrayNBinsProtonCosTheta[0]; double Xmax = ArrayNBinsProtonCosTheta[NBinsProtonCosTheta];
//		TString Reso = "(CandidateP_CosTheta-True_CandidateP_CosTheta)/True_CandidateP_CosTheta*100."; TString XVar = "CandidateP_CosTheta"; int NBins = 12;

//		TString AxisLabel = ";#phi_{p};#phi_{p} resolution [%];"; double Xmin = ArrayNBinsProtonPhi[0]; double Xmax = ArrayNBinsProtonPhi[NBinsProtonPhi];
//		TString Reso = "(CandidateP_Phi-True_CandidateP_Phi)/True_CandidateP_Phi*100."; TString XVar = "CandidateP_Phi"; int NBins = 20;

//		TString AxisLabel = ";P_{#mu} [GeV/c];P_{#mu} resolution [%];"; double Xmin = ArrayNBinsMuonMomentum[0]; double Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum];
//		TString Reso = "((CandidateMu_EndContainment*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS)-True_CandidateMu_CosTheta)/True_CandidateMu_CosTheta*100."; 
//		TString XVar = "CandidateMu_EndContainment*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS"; int NBins = 20;

//		TString AxisLabel = ";cos#theta_{#mu};cos#theta_{#mu} resolution [%];"; double Xmin = ArrayNBinsMuonCosTheta[0]; double Xmax = ArrayNBinsMuonCosTheta[NBinsMuonCosTheta];
//		TString Reso = "(CandidateMu_CosTheta-True_CandidateMu_CosTheta)/True_CandidateMu_CosTheta*100."; TString XVar = "CandidateMu_CosTheta"; int NBins = 20;

//		TString AxisLabel = ";#phi_{#mu};#phi_{#mu} resolution [%];"; double Xmin = ArrayNBinsMuonPhi[0]; double Xmax = ArrayNBinsMuonPhi[NBinsMuonPhi];
//		TString Reso = "(CandidateMu_Phi-True_CandidateMu_Phi)/True_CandidateMu_Phi*100."; TString XVar = "CandidateMu_Phi"; int NBins = 20;

//		TString AxisLabel = ";#delta#alpha_{T};#delta#alpha_{T} resolution [%];"; double Xmin = ArrayNBinsDeltaAlphaT[0]; double Xmax = ArrayNBinsDeltaAlphaT[NBinsDeltaAlphaT];
//		TString Reso = "(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100."; TString XVar = "Reco_DeltaAlphaT"; int NBins = 12;

//		TString AxisLabel = ";#delta#phi_{T};#delta#phi_{T} resolution [%];"; double Xmin = ArrayNBinsDeltaPhiT[0]; double Xmax = ArrayNBinsDeltaPhiT[NBinsDeltaPhiT];
//		TString Reso = "(Reco_DeltaPhiT-True_DeltaPhiT)/True_DeltaPhiT*100."; TString XVar = "Reco_DeltaPhiT"; int NBins = 20;

//		TString AxisLabel = ";#deltap_{T};#deltap_{T} resolution [%];"; double Xmin = ArrayNBinsDeltaPT[0]; double Xmax = ArrayNBinsDeltaPT[NBinsDeltaPT];
//		TString Reso = "(Reco_Pt-True_Pt)/True_Pt*100."; TString XVar = "Reco_Pt"; int NBins = 20;

//		TProfile* p = new TProfile("p",AxisLabel,NBins,Xmin,Xmax);
//		tree->Draw(Reso+":"+XVar+">>p",qualifier,"prof");

		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

		int NBins = 60;
//		TString Reso = "TMath::Abs(Reco_DeltaAlphaT-True_DeltaAlphaT)/True_DeltaAlphaT*100.";
		TString Reso = "TMath::Abs(Reco_DeltaAlphaT-True_DeltaAlphaT)";

//		TString xvar = "CandidateMu_P_MCS * TMath::Sqrt( 1- TMath::Power(CandidateMu_CosTheta,2.) )"; TString AxisLabel = ";p_{#mu,T} [GeV/c];"; double Xmin = 0.; double Xmax = 1.;
//		TString xvar = "CandidateMu_P_Range * TMath::Sqrt( 1- TMath::Power(CandidateMu_CosTheta,2.) )"; TString AxisLabel = ";p_{#mu,T} [GeV/c];"; double Xmin = 0.; double Xmax = 1.;
		TString xvar = "CandidateP_P_Range * TMath::Sqrt( 1- TMath::Power(CandidateP_CosTheta,2.) )"; TString AxisLabel = ";p_{p,T} [GeV/c];"; double Xmin = 0.; double Xmax = 1.;
//		TString xvar = "Reco_Pt"; TString AxisLabel = ";#delta p_{T} [GeV/c];"; double Xmin = ArrayNBinsDeltaPT[0]; double Xmax = ArrayNBinsDeltaPT[NBinsDeltaPT];
//		TString xvar = "CandidateMu_CosTheta"; TString AxisLabel = ";cos#theta_{#mu};"; double Xmin = ArrayNBinsMuonCosTheta[0]; double Xmax = ArrayNBinsMuonCosTheta[NBinsMuonCosTheta];
//		TString xvar = "CandidateMu_Phi"; TString AxisLabel = ";#phi_{#mu};"; double Xmin = ArrayNBinsMuonPhi[0]; double Xmax = ArrayNBinsMuonPhi[NBinsMuonPhi];
//		TString xvar = "CandidateMu_P_Range"; TString AxisLabel = ";P_{#mu};"; double Xmin = ArrayNBinsMuonMomentum[0]; double Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum];
//		TString xvar = "CandidateMu_P_MCS"; TString AxisLabel = ";P_{#mu};"; double Xmin = ArrayNBinsMuonMomentum[0]; double Xmax = ArrayNBinsMuonMomentum[NBinsMuonMomentum];
//		TString xvar = "CandidateP_CosTheta"; TString AxisLabel = ";cos#theta_{p};"; double Xmin = ArrayNBinsProtonCosTheta[0]; double Xmax = ArrayNBinsProtonCosTheta[NBinsProtonCosTheta];
//		TString xvar = "CandidateP_P_Range"; TString AxisLabel = ";P_{p};"; double Xmin = ArrayNBinsProtonMomentum[0]; double Xmax = ArrayNBinsProtonMomentum[NBinsProtonMomentum];
//		TString xvar = "CandidateP_Phi"; TString AxisLabel = ";#phi_{p};"; double Xmin = ArrayNBinsProtonPhi[0]; double Xmax = ArrayNBinsProtonPhi[NBinsProtonPhi];
//		TString xvar = "Reco_DeltaPhi"; TString AxisLabel = ";#delta#phi_{#mu,p};"; double Xmin = MinDeltaPhi; double Xmax = MaxDeltaPhi;
//		TString xvar = "Reco_DeltaTheta"; TString AxisLabel = ";#delta#theta_{#mu,p};"; double Xmin = MinDeltaTheta; double Xmax = MaxDeltaTheta;
//		TString xvar = "Vertex_X"; TString AxisLabel = ";Vertex X [cm];"; double Xmin = MinVertexX; double Xmax = MaxVertexX;
//		TString xvar = "Vertex_Y"; TString AxisLabel = ";Vertex Y [cm];"; double Xmin = MinVertexY; double Xmax = MaxVertexY;
//		TString xvar = "Vertex_Z"; TString AxisLabel = ";Vertex Z [cm];"; double Xmin = MinVertexZ; double Xmax = MaxVertexZ;
//		TString xvar = "CandidateP_P_Range * TMath::Sin( TMath::ACos(CandidateP_CosTheta) )"; TString AxisLabel = ";P_{p,T};"; double Xmin = ArrayNBinsProtonMomentum[0]; double Xmax = ArrayNBinsProtonMomentum[NBinsProtonMomentum];
//		TString xvar = "TMath::ATan((CandidateMu_EndX - CandidateMu_StartX) / (CandidateMu_EndZ - CandidateMu_StartZ))*180./TMath::Pi()"; TString AxisLabel = ";#theta_{XZ};"; double Xmin = -90; double Xmax = 90;
//		TString xvar = "TMath::ATan( CandidateMu_P_Range * TMath::Sqrt(1-TMath::Power(CandidateMu_CosTheta,2.)) * TMath::Sin(CandidateMu_Phi * TMath::Pi() / 180.) / (CandidateMu_P_Range * CandidateMu_CosTheta) ) * 180 / TMath::Pi()"; TString AxisLabel = ";#theta_{XZ,mom};"; double Xmin = -90; double Xmax = 90;
//		TString xvar = "TMath::ATan((CandidateMu_EndY - CandidateMu_StartY) / (CandidateMu_EndZ - CandidateMu_StartZ))*180./TMath::Pi()"; TString AxisLabel = ";#theta_{YZ};"; double Xmin = -90; double Xmax = 90;

//		TString Qualifier = qualifier;
//		TString Qualifier = qualifier + " && TMath::Abs(CandidateMu_Phi-90) < 10";
		TString Qualifier = qualifierNoHitSumCut + " && Reco_DeltaAlphaT < 30";
//		TString Qualifier = qualifierNoHitSumCut + " && CandidateMu_EndContainment == 1" + " && Reco_DeltaAlphaT < 30";		

		
		TH1D* PlaygroundPlotGood = new TH1D("PlaygroundPlotGood",AxisLabel,NBins,Xmin,Xmax);
		tree->Draw(xvar+">>PlaygroundPlotGood","("+Qualifier+ " && " + Reso + " < 25)*POTWeight","goff");
		PlaygroundPlotGood->SetLineWidth(3);
		PlaygroundPlotGood->SetLineColor(kBlack);
		PlaygroundPlotGood->GetYaxis()->SetTitle("POT Normalized Events");
		PlaygroundPlotGood->GetYaxis()->SetRangeUser(0,1.05*PlaygroundPlotGood->GetMaximum());
		leg->AddEntry(PlaygroundPlotGood,"#Delta#delta#alpha_{T} < 25 deg","l");
		PlaygroundPlotGood->Draw("same");

		TH1D* PlaygroundPlotBad = new TH1D("PlaygroundPlotBad",AxisLabel,NBins,Xmin,Xmax);
		tree->Draw(xvar+">>PlaygroundPlotBad","("+Qualifier+ " && " + Reso + " > 25)*POTWeight","goff");
		PlaygroundPlotBad->SetLineWidth(3);
		PlaygroundPlotBad->SetLineColor(kRed);
		//PlaygroundPlotBad->Scale(1.45);
		leg->AddEntry(PlaygroundPlotBad,"#Delta#delta#alpha_{T} > 25 deg","l");
		PlaygroundPlotBad->Draw("same");
		

		/*
//		double XmindEdx = 0, XmaxdEdx = 5; TString Particle = "Mu";
		double XmindEdx = 0, XmaxdEdx = 12; TString Particle = "P";

		TH1D* PlaygroundPlotPlane2 = new TH1D("PlaygroundPlotPlane2",";"+Particle+" Trunc dEdx @ RR = 0 [MeV/cm]",NBins,XmindEdx,XmaxdEdx);
		tree->Draw("Candidate"+Particle+"_Plane2_TruncdEdx[0][0][0]>>PlaygroundPlotPlane2","("+Qualifier+")*POTWeight","goff");
		PlaygroundPlotPlane2->SetLineWidth(3);PlaygroundPlotPlane2->SetLineColor(kBlack);
		PlaygroundPlotPlane2->GetYaxis()->SetTitle("POT Normalized Events");
		PlaygroundPlotPlane2->GetYaxis()->SetRangeUser(0,1.05*PlaygroundPlotPlane2->GetMaximum());
		leg->AddEntry(PlaygroundPlotPlane2,"Plane 2","l");
		PlaygroundPlotPlane2->Draw("same");

		TH1D* PlaygroundPlotPlane1 = new TH1D("PlaygroundPlotPlane1","Trunc dEdx @ RR = 0 [MeV/cm]",NBins,XmindEdx,XmaxdEdx);
		tree->Draw("Candidate"+Particle+"_Plane1_TruncdEdx[0][0][0]>>PlaygroundPlotPlane1","("+Qualifier+")*POTWeight","goff");
		PlaygroundPlotPlane1->SetLineWidth(3);PlaygroundPlotPlane1->SetLineColor(kBlue);
		leg->AddEntry(PlaygroundPlotPlane1,"Plane 1","l");
		PlaygroundPlotPlane1->Draw("same");

		TH1D* PlaygroundPlotPlane0 = new TH1D("PlaygroundPlotPlane0","Trunc dEdx @ RR = 0 [MeV/cm]",NBins,XmindEdx,XmaxdEdx);
		tree->Draw("Candidate"+Particle+"_Plane0_TruncdEdx[0][0][0]>>PlaygroundPlotPlane0","("+Qualifier+")*POTWeight","goff");
		PlaygroundPlotPlane0->SetLineWidth(3);PlaygroundPlotPlane0->SetLineColor(kOrange+7);
		leg->AddEntry(PlaygroundPlotPlane0,"Plane 0","l");
		PlaygroundPlotPlane0->Draw("same");
		*/

		leg->Draw();

		// ---------------------------------------------------------------------------------------------------------------------------------------




		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
