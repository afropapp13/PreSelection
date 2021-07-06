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

// ---------------------------------------------------------------

void PrettyPlot(TH1D* h, int Color) {

	h->SetLineWidth(2);
	h->SetLineColor(Color);
//	h->Scale(1./h->GetMaximum());
	h->Draw("hist same");	

}

// ---------------------------------------------------------------

void Playground() {

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

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

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TLegend* leg = new TLegend(0.15,0.7,0.35,0.85);
		leg->SetTextFont(FontStyle);
		leg->SetTextSize(0.05);
		leg->SetBorderSize(0);

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------
/*
//		TString Xvar = "CandidateMu_CosTheta"; double Xmin = -1.; double Xmax = 1.;
//		TString Xvar = "CandidateP_CosTheta"; double Xmin = -1.; double Xmax = 1.;
//		TString Xvar = "CandidateMu_Phi"; double Xmin = -180.; double Xmax = 180.;
//		TString Xvar = "CandidateP_Phi"; double Xmin = -180.; double Xmax = 180.;
//		TString Xvar = "CandidateMu_P_Range"; double Xmin = 0.1; double Xmax = 1.4;
//		TString Xvar = "(!CandidateMu_EndContainment)*CandidateMu_P_MCS"; double Xmin = 0.1; double Xmax = 1.4;
//		TString Xvar = "( CandidateMu_EndContainment*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS"; double Xmin = 0.1; double Xmax = 1.4;
//		TString Xvar = "CandidateP_P_Range"; double Xmin = 0.25; double Xmax = 1.1;
//		TString Xvar = "Vertex_X"; double Xmin = 0.; double Xmax = 260.;
//		TString Xvar = "Vertex_Y"; double Xmin = -120.; double Xmax = 120.;
//		TString Xvar = "Vertex_Z"; double Xmin = -10.; double Xmax = 1050.;
//		TString Xvar = "Reco_DeltaTheta"; double Xmin = 0.; double Xmax = 180.;
//		TString Xvar = "CandidateMuP_Distance"; double Xmin = 0.; double Xmax = 6.;
//		TString Xvar = "CandidateMuStartVertexDistance"; double Xmin = 0.; double Xmax = 1.5;
//		TString Xvar = "CandidatePStartVertexDistance"; double Xmin = 0.; double Xmax = 5.;
//		TString Xvar = "Reco_Pt"; double Xmin = 0.; double Xmax = 1.;
//		TString Xvar = "BeamFlashes_TotalPE"; double Xmin = 0.; double Xmax = 1000.;
//		TString Xvar = "NuScore"; double Xmin = 0.; double Xmax = 1.;
//		TString Xvar = "CandidateMu_Length"; double Xmin = 0.; double Xmax = 400.;
//		TString Xvar = "CandidateP_Length"; double Xmin = 0.; double Xmax = 100.;
		TString Xvar = "CandidateMu_MinDistance"; double Xmin = 0.; double Xmax = 50.;

//		TString Xvar = "Reco_DeltaPhi"; double Xmin = 0.; double Xmax = 360.;

//		TString Xvar = "TMath::Sqrt( TMath::Power(CandidateMu_StartX-True_CandidateMu_StartX,2.) + TMath::Power(CandidateMu_StartY-True_CandidateMu_StartY,2.) + TMath::Power(CandidateMu_StartZ-True_CandidateMu_StartZ,2.) )"; double Xmin = 0.; double Xmax = 20.;

//		TString Xvar = "TMath::Sqrt( TMath::Power(CandidateP_StartX-True_CandidateP_StartX,2.) + TMath::Power(CandidateP_StartY-True_CandidateP_StartY,2.) + TMath::Power(CandidateP_StartZ-True_CandidateP_StartZ,2.) )"; double Xmin = 0.; double Xmax = 20.;

//		TString MuPX = "( CandidateMu_EndContainment*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) * TMath::Sqrt(1. - TMath::Power(CandidateMu_CosTheta,2.) * TMath::Cos(CandidateMu_Phi * TMath::Pi() / 180. ) )";
//		TString PPX = " CandidateP_P_Range * TMath::Sqrt(1. - TMath::Power(CandidateP_CosTheta,2.) * TMath::Cos(CandidateP_Phi * TMath::Pi() / 180. ) )";

//		TString MuPY = "( CandidateMu_EndContainment*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) * TMath::Sqrt(1. - TMath::Power(CandidateMu_CosTheta,2.) * TMath::Sin(CandidateMu_Phi * TMath::Pi() / 180. ) )";
//		TString PPY = " CandidateP_P_Range * TMath::Sqrt(1. - TMath::Power(CandidateP_CosTheta,2.) * TMath::Sin(CandidateP_Phi * TMath::Pi() / 180. ) )";

//		TString MuPZ = "( CandidateMu_EndContainment*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS) * CandidateMu_CosTheta";
//		TString PPZ = " CandidateP_P_Range * CandidateP_CosTheta";

//		TString Xvar = "TMath::ATan( ( " + MuPX + " - " + PPX + ") / (" + MuPZ + " - " + PPZ + ") ) * 180. / TMath::Pi()"; double Xmin = -90.; double Xmax = 90.; // XZ
//		TString Xvar = "TMath::ATan( ( " + MuPY + " - " + PPY + ") / (" + MuPZ + " - " + PPZ + ") ) * 180. / TMath::Pi()"; double Xmin = -90.; double Xmax = 90.; // YZ
//		TString Xvar = "TMath::ATan( ( " + MuPX + " - " + PPX + ") / (" + MuPY + " - " + PPY + ") ) * 180. / TMath::Pi()"; double Xmin = -90.; double Xmax = 90.; // XY


		TString Labels = ";"+Xvar+";POT Normalized Events";
		int NBins = 50; 

		TString Qualifier = qualifier + " && CandidateMu_EndContainment == 1";
//		TString Qualifier = qualifier + " && TMath::Abs(Reco_DeltaPhi - 180) < 30";
//		TString Qualifier = qualifier;

		TString extra = " TMath::Abs(Reco_DeltaAlphaT - True_DeltaAlphaT) ";

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlot","(" +Qualifier+")*POTWeight","goff");
		PrettyPlot(PlaygroundPlot,kBlack);
		leg->AddEntry(PlaygroundPlot,"All");

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotFlipped = new TH1D("PlaygroundPlotFlipped",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotFlipped","(" +Qualifier+" && " + extra + " > 100 )*POTWeight","goff");
		PrettyPlot(PlaygroundPlotFlipped,kRed);
		leg->AddEntry(PlaygroundPlotFlipped,"Flipped");

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotUnFlipped = new TH1D("PlaygroundPlotUnFlipped",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotUnFlipped","(" +Qualifier+" && " + extra + "  < 100)*POTWeight","goff");
		PrettyPlot(PlaygroundPlotUnFlipped,kBlue);
		leg->AddEntry(PlaygroundPlotUnFlipped,"Not Flipped");

*/
		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------
/*
		TString thres = " < 50";
//		TString thres = " > 130";
//		TString thres = " > 50 && Reco_DeltaAlphaT_Recalibrate < 90";
//		TString thres = " > 90 && Reco_DeltaAlphaT_Recalibrate < 130";

		TString Labels = ";#delta#alpha_{T} Reco - True [deg];POT Normalized Events";
		int NBins = 45;
		double Xmin = -180.;
		double Xmax = 180.; 
//		TString Xvar = "Reco_DeltaAlphaT-True_DeltaAlphaT";
		TString Xvar = "Reco_DeltaAlphaT_Recalibrate-True_DeltaAlphaT";

		TString Qualifier = qualifier + " && Reco_DeltaAlphaT_Recalibrate " + thres;
//		TString Qualifier = qualifier;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlot","(" +Qualifier+")*POTWeight","goff");
		cout << "Events = " << PlaygroundPlot->Integral() << endl;
		PrettyPlot(PlaygroundPlot,kBlack);
		PlaygroundPlot->SetTitle(Xvar);
		leg->AddEntry(PlaygroundPlot,"All reco #delta#alpha_{T}"+thres);

		// ---------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotForwMu = new TH1D("PlaygroundPlotForwMu",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotForwMu","("+Qualifier + " && CandidateMu_EndContainment == 1)*POTWeight","goff");
		PrettyPlot(PlaygroundPlotForwMu,kRed);
		leg->AddEntry(PlaygroundPlotForwMu,"contained");

		// ---------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotForwP = new TH1D("PlaygroundPlotForwP",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotForwP","("+Qualifier + " && CandidateMu_EndContainment == 0 )*POTWeight","goff");
		PrettyPlot(PlaygroundPlotForwP,kBlue);
		leg->AddEntry(PlaygroundPlotForwP,"exiting");

		leg->Draw();
*/
		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------
/*
//		TString thres = " < 50";
		TString thres = " > 130";

		TString Labels = ";#delta#alpha_{T} Reco - True [deg];Peak Normalized To 1";
//		TString Labels = ";#delta#alpha_{T} Reco - True [deg];POT Normalized Events";
		int NBins = 45;
		double Xmin = -180.;
		double Xmax = 180.; 
		TString Xvar = "Reco_DeltaAlphaT-True_DeltaAlphaT";

		TString Qualifier = qualifier + " && Reco_DeltaAlphaT" + thres;
//		TString Qualifier = qualifier;

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlot","(" +Qualifier+")*POTWeight","goff");
		cout << "Events = " << PlaygroundPlot->Integral() << endl;
		PrettyPlot(PlaygroundPlot,kBlack);
		leg->AddEntry(PlaygroundPlot,"All reco #delta#alpha_{T}"+thres);

		// ---------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotForwMu = new TH1D("PlaygroundPlotForwMu",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotForwMu","("+Qualifier + " && Reco_Pt > 0.07)*POTWeight","goff");
		PrettyPlot(PlaygroundPlotForwMu,kRed);
		leg->AddEntry(PlaygroundPlotForwMu,"P_{T} > 70 MeV/c");

		// ---------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotForwP = new TH1D("PlaygroundPlotForwP",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotForwP","("+Qualifier + " && Reco_Pt > 0.1)*POTWeight","goff");
		PrettyPlot(PlaygroundPlotForwP,kBlue);
		leg->AddEntry(PlaygroundPlotForwP,"P_{T} > 100 MeV/c");

		// ---------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotThree = new TH1D("PlaygroundPlotThree",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotThree","("+Qualifier + " && Reco_Pt > 0.15)*POTWeight","goff");
		PrettyPlot(PlaygroundPlotThree,kMagenta);
		leg->AddEntry(PlaygroundPlotThree,"P_{T} > 150 MeV/c");

		// ---------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotFour = new TH1D("PlaygroundPlotFour",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotFour","("+Qualifier + " && Reco_Pt > 0.2)*POTWeight","goff");
		PrettyPlot(PlaygroundPlotFour,kGreen+1);
		leg->AddEntry(PlaygroundPlotFour,"P_{T} > 200 MeV/c");

		// ---------------------------------------------------------------------------------------------------------------------------------------

		leg->Draw();
*/
		// -----------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------
/*
		TCanvas* PTCanvas = new TCanvas("PTCanvas_"+Runs[WhichRun],"PTCanvas_"+Runs[WhichRun],205,34,1024,768);

		TString thres = " 100";

//		TString Labels = ";P_{T} [GeV/c];POT Normalized Events";
		TString Labels = ";P_{T} [GeV/c];Peak Normalized to 1";
		int NBins = 50;
		double Xmin = 0.;
		double Xmax = 1.; 
		TString Xvar = "Reco_Pt";

//		TString Qualifier = qualifier + " && Reco_DeltaAlphaT" + thres;
		TString Qualifier = qualifier + " && Reco_Pt > 0.12";

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlot","(" +Qualifier+")*POTWeight","goff");
		cout << "Events = " << PlaygroundPlot->Integral() << endl;
		PrettyPlot(PlaygroundPlot,kBlack);
		leg->AddEntry(PlaygroundPlot,"All reco #delta#alpha_{T}");

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotFlipped = new TH1D("PlaygroundPlotFlipped",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotFlipped","(" +Qualifier+" && TMath::Abs(Reco_DeltaAlphaT - True_DeltaAlphaT) > " + thres + ")*POTWeight","goff");
		PrettyPlot(PlaygroundPlotFlipped,kRed);
		leg->AddEntry(PlaygroundPlotFlipped,"Flipped #delta#alpha_{T}");

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlotUnFlipped = new TH1D("PlaygroundPlotUnFlipped",Labels,NBins,Xmin,Xmax);
		tree->Draw(Xvar+">>PlaygroundPlotUnFlipped","(" +Qualifier+" && TMath::Abs(Reco_DeltaAlphaT - True_DeltaAlphaT) < " + thres + ")*POTWeight","goff");
		PrettyPlot(PlaygroundPlotUnFlipped,kBlue);
		leg->AddEntry(PlaygroundPlotUnFlipped,"Unflipped #delta#alpha_{T}");

		// ---------------------------------------------------------------------------------------------------------------------------------------

		leg->Draw();
*/
		// -----------------------------------------------------------------------------------------------------------------------------------------
		// -----------------------------------------------------------------------------------------------------------------------------------------
/*
//		TString Qualifier = qualifier;
		TString Qualifier = qualifier + " && CandidateMu_EndContainment == 1";

		TCanvas* DeltaAlphaTCanvas = new TCanvas("DeltaAlphaTCanvas_"+Runs[WhichRun],"DeltaAlphaTCanvas_"+Runs[WhichRun],205,34,1024,768);

		TH2D* hDeltaAlphaT = new TH2D("hDeltaAlphaT",";True #delta#alpha_{T} [deg];Reco #delta#alpha_{T} [deg]",90,0,180,90,0,180);
//		tree->Draw("Reco_DeltaAlphaT:True_DeltaAlphaT>>hDeltaAlphaT",Qualifier,"goff");
		tree->Draw("Reco_DeltaAlphaT_Recalibrate:True_DeltaAlphaT>>hDeltaAlphaT",Qualifier,"goff");
		hDeltaAlphaT->Draw("coltz");
*/
		// -----------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------
/*
		TCanvas* MCSCanvas = new TCanvas("MCSCanvas_"+Runs[WhichRun],"MCSCanvas_"+Runs[WhichRun],205,34,1024,768);

		TH2D* hMCS = new TH2D("hMCS",";Reco P_{#mu} [GeV/c];Reco P_{#mu,MCS} Recalibrated [GeV/c]",50,0.1,1.4,50,0.1,1.4);
		tree->Draw("CandidateMu_P_MCS_Recalibrate:CandidateMu_P_MCS>>hMCS",Qualifier+ " && CandidateMu_EndContainment == 0","goff");
		hMCS->Draw("coltz");
*/

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

		TH1D* PlaygroundPlot = new TH1D("PlaygroundPlot","nue",2,0,2);
		tree->Draw("nue>>PlaygroundPlot",qualifier);

	} // End of the loop over the runs

} // End of the program 
