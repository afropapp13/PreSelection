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

// -------------------------------------------------------------------------------------------------------------------------------------------------

void TwoEfficiencyFunction(TString Run, TString XVar, TString YVar , TTree* t, TTree* tTrue, int XBins, double Xmin, double Xmax, int YBins, double Ymin, double Ymax) {

	// ----------------------------------------------------------------------------------------

	gStyle->SetMarkerSize(1.5);
	gStyle->SetPaintTextFormat("4.2f");	

	// ----------------------------------------------------------------------------------------

	static std::map<TString,TString> VarLabel =
	{
		{ "True_CandidateP_P",  "P_{p} [GeV/c]" },
		{ "True_CandidateMu_P",  "P_{#mu} [GeV/c]" },
		{ "True_CandidateP_CosTheta",  "cos#theta_{p}" },
		{ "True_CandidateMu_CosTheta",  "cos#theta_{#mu}" },
		{ "True_CandidateP_Phi",  "#phi_{p} [deg]" },
		{ "True_CandidateMu_Phi",  "#phi_{#mu} [deg]" },
		{ "True_Pt",  "#deltap_{T} [GeV/c]" },
		{ "True_DeltaAlphaT",  "#delta#alpha_{T} [GeV/c]" },
		{ "True_DeltaPhiT",  "#delta#phi_{T} [GeV/c]" },
	};

	static std::map<TString,TString> RecoToTruth =
	{
		{ "True_CandidateP_P",  "Proton_MCParticle_Mom" },
		{ "True_CandidateMu_P",  "Muon_MCParticle_Mom" },
		{ "True_CandidateP_CosTheta", "Proton_MCParticle_CosTheta" },
		{ "True_CandidateMu_CosTheta",  "Muon_MCParticle_CosTheta" },
		{ "True_CandidateP_Phi",  "Proton_MCParticle_Phi" },
		{ "True_CandidateMu_Phi",  "Muon_MCParticle_Phi" },
		{ "True_Pt",  "True_Pt" },
		{ "True_DeltaAlphaT",  "True_DeltaAlphaT" },
		{ "True_DeltaPhiT",  "True_DeltaPhiT" },
	};

	TString XLabel = VarLabel[XVar], YLabel = VarLabel[YVar];
	TString TrueXVar = RecoToTruth[XVar], TrueYVar = RecoToTruth[YVar];

	// ----------------------------------------------------------------------------------------

	TString WithQCQual = qualifier + " && NuScore > " + TString(std::to_string(MinimumNuScore)) + " && CandidateP_ThreePlaneLogLikelihood > "\
			 +  TString(std::to_string(ProtonThreePlaneChi2LogLikelihoodCut));

	TString WithoutQCQual = qualifierNoExitMuQC + " && NuScore > " + TString(std::to_string(MinimumNuScore)) + " && CandidateP_ThreePlaneLogLikelihood > "\
			 +  TString(std::to_string(ProtonThreePlaneChi2LogLikelihoodCut));

	// ----------------------------------------------------------------------------------------

	// Truth level

	TH2D* truth = new TH2D("True_" + YVar + "_" + XVar,";" + XLabel + ";" + YLabel,XBins,Xmin,Xmax,YBins,Ymin,Ymax);
	tTrue->Draw(TrueYVar + ":" + TrueXVar + " >>" + "True_" + YVar + "_" + XVar,"("+TrueQualifier + ")*POTWeight","goff");

	// ----------------------------------------------------------------------------------------

	// Selection with quality cut on exiting muons // Reco level

	TString WithExitQCCanvasName = XVar+YVar+"WithExitQCCanvas_"+Run;
	TCanvas* WithExitQCCanvas = new TCanvas(WithExitQCCanvasName,WithExitQCCanvasName,205,34,1024,768);
	WithExitQCCanvas->SetBottomMargin(0.12);
	WithExitQCCanvas->SetRightMargin(0.12);

	TH2D* recoWith = new TH2D("Reco_" + YVar + "_" + XVar,";" + XLabel + ";" + YLabel,XBins,Xmin,Xmax,YBins,Ymin,Ymax);
	t->Draw(YVar + ":" + XVar + " >>" + "Reco_" + YVar + "_" + XVar,"("+WithQCQual + ")*POTWeight","goff");

	recoWith->Divide(truth);

	recoWith->SetMarkerColor(kWhite);				
	recoWith->SetMarkerSize(1.5);

	recoWith->GetZaxis()->SetRangeUser(0.,0.35);
	recoWith->Draw("coltz text");

	TLatex *textEff = new TLatex();
	textEff->SetTextFont(FontStyle);
	textEff->SetTextSize(TextSize);
	textEff->DrawTextNDC(0.1, 0.91, Run + " (With)");

	WithExitQCCanvas->SaveAs(PlotPath+"WithExitQCCanvas_"+XVar+"_"+YVar+"_"+Run+".pdf");
	delete WithExitQCCanvas;

	// --------------------------------------------------------------------------------------

	// Selection without quality cut on exiting muons // Reco level

	TString WithoutExitQCCanvasName = XVar+YVar+"WithoutExitQCCanvas_"+Run;
	TCanvas* WithoutExitQCCanvas = new TCanvas(WithoutExitQCCanvasName,WithoutExitQCCanvasName,205,34,1024,768);
	WithoutExitQCCanvas->SetBottomMargin(0.12);
	WithoutExitQCCanvas->SetRightMargin(0.12);

	TH2D* recoWithout = new TH2D("Reco_WO_" + YVar + "_" + XVar,";" + XLabel + ";" + YLabel,XBins,Xmin,Xmax,YBins,Ymin,Ymax);
	t->Draw(YVar + ":" + XVar + " >>" + "Reco_WO_" + YVar + "_" + XVar,"("+WithoutQCQual + ")*POTWeight","goff");

	recoWithout->Divide(truth);

	recoWithout->SetMarkerColor(kWhite);				
	recoWithout->SetMarkerSize(1.5);

	recoWithout->GetZaxis()->SetRangeUser(0.,0.35);
	recoWithout->Draw("coltz text");

	textEff->DrawTextNDC(0.1, 0.91, Run + " (Without)");

	WithoutExitQCCanvas->SaveAs(PlotPath+"WithoutExitQCCanvas_"+XVar+"_"+YVar+"_"+Run+".pdf");
	delete WithoutExitQCCanvas;

	// --------------------------------------------------------------------------------------

	// Now the ratio

	TString RatioCanvasName = XVar+YVar+"RatioCanvas_"+Run;
	TCanvas* RatioCanvas = new TCanvas(RatioCanvasName,RatioCanvasName,205,34,1024,768);
	RatioCanvas->SetBottomMargin(0.12);
	RatioCanvas->SetRightMargin(0.12);

	TH2D* recoWithoutClone = (TH2D*)(recoWithout->Clone());
	recoWithoutClone->Add(recoWith,-1);
	recoWithoutClone->Divide(recoWithout);

	recoWithoutClone->GetZaxis()->SetRangeUser(0.,1.);
	recoWithoutClone->Draw("coltz text");

	textEff->DrawTextNDC(0.1, 0.91, Run + " (Fractional Change)");

	RatioCanvas->SaveAs(PlotPath+"ExitMuQCRatioCanvas_"+XVar+"_"+YVar+"_"+Run+".pdf");
	delete RatioCanvas;

}

// -------------------------------------------------------------------------------------------------------------------------------------------------

void EfficiencyFunction(TString Run, TString Var, TTree* t, TString TrueVar, TTree* tTrue, int NBins, double Xmin, double Xmax) {

	TString XLabel = "blah";
	if (Var == "True_CandidateP_P") { XLabel = "P_{p} [GeV/c]"; }
	if (Var == "True_CandidateMu_P") { XLabel = "P_{#mu} [GeV/c]"; }
	if (Var == "True_CandidateP_CosTheta") { XLabel = "cos#theta_{p}"; }
	if (Var == "True_CandidateMu_CosTheta") { XLabel = "cos#theta_{#mu}"; }
	if (Var == "True_CandidateP_Phi") { XLabel = "#phi_{p} [deg]"; }
	if (Var == "True_CandidateMu_Phi") { XLabel = "#phi_{#mu} [deg]"; }
	if (Var == "True_Pt") { XLabel = "#deltap_{T} [GeV/c]"; }
	if (Var == "True_DeltaAlphaT") { XLabel = "#delta#alpha_{T} [deg]"; }
	if (Var == "True_DeltaPhiT") { XLabel = "#delta#phi_{T} [deg]"; }

	TString EffCanvasName = Var+"EffCanvas_"+Run;
	TCanvas* EffCanvas = new TCanvas(EffCanvasName,EffCanvasName,205,34,1024,768);
	EffCanvas->SetBottomMargin(0.12);

	TH1D* reco = new TH1D(Var,";" + XLabel + "; Efficiency [%]",NBins,Xmin,Xmax);
	t->Draw(Var + " >>" + Var,"("+qualifier + ")*POTWeight","goff");

	TH1D* truth = new TH1D("True"+TrueVar,";" + XLabel + "; Efficiency [%]",NBins,Xmin,Xmax);
	tTrue->Draw(TrueVar + " >>True" + TrueVar,"("+TrueQualifier + ")*POTWeight","goff");

	reco->SetMarkerSize(2.);
	reco->SetMarkerStyle(20);
	reco->SetMarkerColor(kBlack);
	reco->SetLineColor(kBlack);

	reco->Divide(truth);
	reco->Scale(100.);
	reco->GetYaxis()->SetRangeUser(0,1.1*reco->GetMaximum());

	reco->Draw("e1");

	TLatex *textEff = new TLatex();
	textEff->SetTextFont(FontStyle);
	textEff->SetTextSize(TextSize);
	textEff->DrawTextNDC(0.1, 0.91, Run);

	EffCanvas->SaveAs(PlotPath+"FineBinEff_"+Var+"_"+Run+".pdf");
	delete 	EffCanvas;

}

// -------------------------------------------------------------------------------------------------------------------------------------------------

void PrettyPlot(TH1D* h, int Color) {

	h->Scale(1./h->GetMaximum());
	h->SetMarkerSize(2.);
	h->SetMarkerStyle(20);
	h->SetMarkerColor(Color);
	h->SetLineColor(Color);

	h->GetYaxis()->CenterTitle();
	h->GetYaxis()->SetTitle("Peak Normalized To 1");

	h->GetXaxis()->CenterTitle();
	h->GetXaxis()->SetTitleOffset(1.1);

}

// -------------------------------------------------------------------------------------------------------------------------------------------------

void ProtonPrintCanvas(TString Run, TString Var, TTree* t, TString Slice) {

	// ---------------------------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();

	// ---------------------------------------------------------------------------------------------

	TLatex *text = new TLatex();
	text->SetTextFont(132);
	text->SetTextSize(0.05);

	TLegend* leg = new TLegend(0.02,0.91,0.98,0.99);
	leg->SetTextSize(0.04);
	leg->SetTextFont(132);
	leg->SetBorderSize(0);
	leg->SetNColumns(4);

	// ---------------------------------------------------------------------------------------------

	TString Label = "labelblah", Cut = "cutblah";

	if (Slice == "AllPT") { Label = "All"; Cut = Var + " > " + TString(std::to_string(ArrayNBinsDeltaPT[0])) + " && " + Var + " < " + TString(std::to_string(ArrayNBinsDeltaPT[NBinsDeltaPT])); }
	if (Slice == "LowPT") { Label = "0 < #deltap_{T} < 0.3 [GeV/c]"; Cut = Var + " > 0 && " + Var + " < 0.3"; }
	if (Slice == "MidPT") { Label = "0.3 < #deltap_{T} < 0.6 [GeV/c]"; Cut = Var + " > 0.3 && " + Var + " < 0.6"; }
	if (Slice == "HighPT") { Label = "0.6 < #deltap_{T} < 0.95 [GeV/c]"; Cut = Var + " > 0.6 && " + Var + " < " + TString(std::to_string(ArrayNBinsDeltaPT[NBinsDeltaPT])); }

	if (Slice == "AllDeltaAlphaT") { Label = "All"; Cut = Var + " > " + TString(std::to_string(ArrayNBinsDeltaAlphaT[0])) + " && " + Var + " < " + TString(std::to_string(ArrayNBinsDeltaAlphaT[NBinsDeltaAlphaT])); }
	if (Slice == "LowDeltaAlphaT") { Label = "0 < #delta#alpha_{T} < 30 [deg]"; Cut = Var + " > 0 && " + Var + " < 50"; }
	if (Slice == "MidDeltaAlphaT") { Label = "30 < #delta#alpha_{T} < 130 [deg]"; Cut = Var + " > 50 && " + Var + " < 130"; }
	if (Slice == "HighDeltaAlphaT") { Label = "130 < #delta#alpha_{T} < 180 [deg]"; Cut = Var + " > 130 && " + Var + " < 180"; }

	if (Slice == "AllDeltaPhiT") { Label = "All"; Cut = Var + " > " + TString(std::to_string(ArrayNBinsDeltaPhiT[0])) + " && " + Var + " < " + TString(std::to_string(ArrayNBinsDeltaPhiT[NBinsDeltaPhiT])); }
	if (Slice == "LowDeltaPhiT") { Label = "0 < #delta#phi_{T} < 30 [deg]"; Cut = Var + " > 0 && " + Var + " < 30"; }
	if (Slice == "MidDeltaPhiT") { Label = "30 < #delta#phi_{T} < 60 [deg]"; Cut = Var + " > 30 && " + Var + " < 60"; }
	if (Slice == "HighDeltaPhiT") { Label = "60 < #delta#phi_{T} < 180 [deg]"; Cut = Var + " > 60 && " + Var + " < 180"; }

	// ---------------------------------------------------------------------------------------------

	int NBins = -99; double Xmin = -99., Xmax = -99.; TString XLabel = "blah"; TString TrueVar = "true blah";

	if (string(Var).find("Pt") != std::string::npos) 
		{ NBins = 30; Xmin = -0.85; Xmax = 0.85; XLabel = "#delta p_{T} [GeV/c]"; TrueVar = "True_Pt"; }
	if (string(Var).find("DeltaAlphaT") != std::string::npos) 
		{ NBins = 30; Xmin = -180; Xmax = 180.; XLabel = "#delta#alpha_{T} [deg]"; TrueVar = "True_DeltaAlphaT"; }
	if (string(Var).find("DeltaPhiT") != std::string::npos) 
		{ NBins = 30; Xmin = -30; Xmax = 30.; XLabel = "#delta#phi_{T} [deg]"; TrueVar = "True_DeltaPhiT"; }

	// ---------------------------------------------------------------------------------------------

	const int LengthSlices = 3;
	TString LengthArray[LengthSlices+1] = {"0.","10.","40.","1000."};

	// ---------------------------------------------------------------------------------------------

	TString Qualifier = qualifierNoExitMuQC + " && NuScore > " + TString(std::to_string(MinimumNuScore)) + " && CandidateP_ThreePlaneLogLikelihood > "\
			 +  TString(std::to_string(ProtonThreePlaneChi2LogLikelihoodCut));

	// ---------------------------------------------------------------------------------------------

	TString Weight = "POTWeight * Weight * T2KWeight * ROOTinoWeight";

	// ---------------------------------------------------------------------------------------------

	TString CanvasName = Slice+Var+"DiffCanvas_"+Run;
	TCanvas* DiffCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
	DiffCanvas->SetBottomMargin(0.12);

	TH1D* ExitShort = new TH1D(Slice + Var+"ExitShortP",";(Reco - True) " + XLabel+";",NBins,Xmin,Xmax);
	TString ExitShortString = "CandidateP_Length>"+LengthArray[0]+" && CandidateP_Length < "+LengthArray[1];
	t->Draw(Var + " - " + TrueVar + " >>" + Slice + Var + "ExitShortP","("+Qualifier+" && " + ExitShortString +" && " + Cut + ")*"+Weight,"goff");
	double ExitShortEvents = ExitShort->Integral();
	PrettyPlot(ExitShort,kBlue+1);
	ExitShort->Draw("p0 hist same");

	TH1D* ExitMedium = new TH1D(Slice + Var + "ExitMediumP",";(Reco - True) " + XLabel,NBins,Xmin,Xmax);
	TString ExitMedString = "CandidateP_Length>"+LengthArray[1]+" && CandidateP_Length < "+LengthArray[2];
	t->Draw(Var + " - " + TrueVar + " >>" + Slice + Var + "ExitMediumP","("+Qualifier+"&& " + ExitMedString +" && " + Cut + ")*"+Weight,"goff");
	double ExitMediumEvents = ExitMedium->Integral();
	PrettyPlot(ExitMedium,kGreen+1);
	ExitMedium->Draw("p0 hist same");

	TH1D* ExitLong = new TH1D(Slice + Var + "ExitLongP",";(Reco - True) " + XLabel,NBins,Xmin,Xmax);
	TString ExitLongString = "CandidateP_Length>"+LengthArray[2]+" && CandidateP_Length < "+LengthArray[3];
	t->Draw(Var + " - " + TrueVar + " >>" + Slice + Var + "ExitLongP","("+Qualifier+"&& " + ExitLongString + " && " + Cut + ")*"+Weight,"goff");
	double ExitLongEvents = ExitLong->Integral();
	PrettyPlot(ExitLong,kOrange+7);
	ExitLong->Draw("p0 hist same");

	leg->AddEntry(ExitShort,"Exit Short [" + TString(std::to_string(int(ExitShortEvents))) + "]","p");
	leg->AddEntry(ExitMedium,"Exit Medium [" + TString(std::to_string(int(ExitMediumEvents))) + "]","p");
	leg->AddEntry(ExitLong,"Exit Long [" + TString(std::to_string(int(ExitLongEvents))) + "]","p");

	leg->Draw();

	text->DrawLatexNDC(0.15,0.8,Label);

	// ---------------------------------------------------------------------------------------------

	DiffCanvas->SaveAs(PlotPath+Slice+"_"+Var+"ProtonLengthContainmentStudyCanvas_"+Run+".pdf");
	delete DiffCanvas;

	// ---------------------------------------------------------------------------------------------

}

// -------------------------------------------------------------------------------------------------------------------------------------------------

void MuonPrintCanvas(TString Run, TString Var, TTree* t, TString Slice) {

	// ---------------------------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();

	// ---------------------------------------------------------------------------------------------

	TLatex *text = new TLatex();
	text->SetTextFont(132);
	text->SetTextSize(0.05);

	TLegend* leg = new TLegend(0.02,0.91,0.98,0.99);
	leg->SetTextSize(0.04);
	leg->SetTextFont(132);
	leg->SetBorderSize(0);
	leg->SetNColumns(4);

	// ---------------------------------------------------------------------------------------------

	TString Label = "labelblah", Cut = "cutblah";

	if (Slice == "AllPT") { Label = "All"; Cut = Var + " > " + TString(std::to_string(ArrayNBinsDeltaPT[0])) + " && " + Var + " < " + TString(std::to_string(ArrayNBinsDeltaPT[NBinsDeltaPT])); }
	if (Slice == "LowPT") { Label = "0 < #deltap_{T} < 0.3 [GeV/c]"; Cut = Var + " > 0 && " + Var + " < 0.3"; }
	if (Slice == "MidPT") { Label = "0.3 < #deltap_{T} < 0.6 [GeV/c]"; Cut = Var + " > 0.3 && " + Var + " < 0.6"; }
	if (Slice == "HighPT") { Label = "0.6 < #deltap_{T} < 0.95 [GeV/c]"; Cut = Var + " > 0.6 && " + Var + " < " + TString(std::to_string(ArrayNBinsDeltaPT[NBinsDeltaPT])); }

	if (Slice == "AllDeltaAlphaT") { Label = "All"; Cut = Var + " > " + TString(std::to_string(ArrayNBinsDeltaAlphaT[0])) + " && " + Var + " < " + TString(std::to_string(ArrayNBinsDeltaAlphaT[NBinsDeltaAlphaT])); }
	if (Slice == "LowDeltaAlphaT") { Label = "0 < #delta#alpha_{T} < 30 [deg]"; Cut = Var + " > 0 && " + Var + " < 50"; }
	if (Slice == "MidDeltaAlphaT") { Label = "30 < #delta#alpha_{T} < 130 [deg]"; Cut = Var + " > 50 && " + Var + " < 130"; }
	if (Slice == "HighDeltaAlphaT") { Label = "130 < #delta#alpha_{T} < 180 [deg]"; Cut = Var + " > 130 && " + Var + " < 180"; }

	if (Slice == "AllDeltaPhiT") { Label = "All"; Cut = Var + " > " + TString(std::to_string(ArrayNBinsDeltaPhiT[0])) + " && " + Var + " < " + TString(std::to_string(ArrayNBinsDeltaPhiT[NBinsDeltaPhiT])); }
	if (Slice == "LowDeltaPhiT") { Label = "0 < #delta#phi_{T} < 30 [deg]"; Cut = Var + " > 0 && " + Var + " < 30"; }
	if (Slice == "MidDeltaPhiT") { Label = "30 < #delta#phi_{T} < 60 [deg]"; Cut = Var + " > 30 && " + Var + " < 60"; }
	if (Slice == "HighDeltaPhiT") { Label = "60 < #delta#phi_{T} < 180 [deg]"; Cut = Var + " > 60 && " + Var + " < 180"; }

	// ---------------------------------------------------------------------------------------------

	int NBins = -99; double Xmin = -99., Xmax = -99.; TString XLabel = "blah"; TString TrueVar = "true blah";

	if (string(Var).find("Pt") != std::string::npos) 
		{ NBins = 30; Xmin = -0.85; Xmax = 0.85; XLabel = "#delta p_{T} [GeV/c]"; TrueVar = "True_Pt"; }
	if (string(Var).find("DeltaAlphaT") != std::string::npos) 
		{ NBins = 30; Xmin = -180; Xmax = 180.; XLabel = "#delta#alpha_{T} [deg]"; TrueVar = "True_DeltaAlphaT"; }
	if (string(Var).find("DeltaPhiT") != std::string::npos) 
		{ NBins = 30; Xmin = -30; Xmax = 30.; XLabel = "#delta#phi_{T} [deg]"; TrueVar = "True_DeltaPhiT"; }

	// ---------------------------------------------------------------------------------------------

	const int LengthSlices = 3;
	TString LengthArray[LengthSlices+1] = {"0.","100.","200.","1000."};

	// ---------------------------------------------------------------------------------------------

	TString Qualifier = qualifierNoExitMuQC + " && NuScore > " + TString(std::to_string(MinimumNuScore)) + " && CandidateP_ThreePlaneLogLikelihood > "\
			 +  TString(std::to_string(ProtonThreePlaneChi2LogLikelihoodCut));

	// ---------------------------------------------------------------------------------------------

	TString Weight = "POTWeight * Weight * T2KWeight * ROOTinoWeight";

	// ---------------------------------------------------------------------------------------------

	TString CanvasName = Slice+Var+"DiffCanvas_"+Run;
	TCanvas* DiffCanvas = new TCanvas(CanvasName,CanvasName,205,34,1024,768);
	DiffCanvas->SetBottomMargin(0.12);

	TH1D* Contained = new TH1D(Slice + Var + "ContainedMu",";(Reco - True) " + XLabel+";",NBins,Xmin,Xmax);
	t->Draw(Var + " - " + TrueVar + " >>" + Slice + Var + "ContainedMu","("+Qualifier+" && CandidateMu_EndContainment == 1 && " + Cut + ")*"+Weight,"goff");
	double ContainedEvents = Contained->Integral();
	PrettyPlot(Contained,kBlack);
	Contained->Draw("p0 hist");

	TH1D* ExitShort = new TH1D(Slice + Var+"ExitShortMu",";(Reco - True) " + XLabel+";",NBins,Xmin,Xmax);
	TString ExitShortString = "CandidateMu_Length>"+LengthArray[0]+" && CandidateMu_Length < "+LengthArray[1];
	t->Draw(Var + " - " + TrueVar + " >>" + Slice + Var + "ExitShortMu","("+Qualifier+" && CandidateMu_EndContainment == 0 && " + ExitShortString +" && " + Cut + ")*"+Weight,"goff");
	double ExitShortEvents = ExitShort->Integral();
	PrettyPlot(ExitShort,kBlue+1);
	ExitShort->Draw("p0 hist same");

	TH1D* ExitMedium = new TH1D(Slice + Var + "ExitMediumMu",";(Reco - True) " + XLabel,NBins,Xmin,Xmax);
	TString ExitMedString = "CandidateMu_Length>"+LengthArray[1]+" && CandidateMu_Length < "+LengthArray[2];
	t->Draw(Var + " - " + TrueVar + " >>" + Slice + Var + "ExitMediumMu","("+Qualifier+"&& CandidateMu_EndContainment == 0 && " + ExitMedString +" && " + Cut + ")*"+Weight,"goff");
	double ExitMediumEvents = ExitMedium->Integral();
	PrettyPlot(ExitMedium,kGreen+1);
	ExitMedium->Draw("p0 hist same");

	TH1D* ExitLong = new TH1D(Slice + Var + "ExitLongMu",";(Reco - True) " + XLabel,NBins,Xmin,Xmax);
	TString ExitLongString = "CandidateMu_Length>"+LengthArray[2]+" && CandidateMu_Length < "+LengthArray[3];
	t->Draw(Var + " - " + TrueVar + " >>" + Slice + Var + "ExitLongMu","("+Qualifier+"&& CandidateMu_EndContainment == 0 && " + ExitLongString + " && " + Cut + ")*"+Weight,"goff");
	double ExitLongEvents = ExitLong->Integral();
	PrettyPlot(ExitLong,kOrange+7);
	ExitLong->Draw("p0 hist same");

	leg->AddEntry(Contained,"Contained [" + TString(std::to_string(int(ContainedEvents))) + "]","p");
	leg->AddEntry(ExitShort,"Exit Short [" + TString(std::to_string(int(ExitShortEvents))) + "]","p");
	leg->AddEntry(ExitMedium,"Exit Medium [" + TString(std::to_string(int(ExitMediumEvents))) + "]","p");
	leg->AddEntry(ExitLong,"Exit Long [" + TString(std::to_string(int(ExitLongEvents))) + "]","p");

	leg->Draw();

	text->DrawLatexNDC(0.15,0.8,Label);

	// ---------------------------------------------------------------------------------------------

	DiffCanvas->SaveAs(PlotPath+Slice+"_"+Var+"MuonLengthContainmentStudyCanvas_"+Run+".pdf");
	delete DiffCanvas;

	// ---------------------------------------------------------------------------------------------

}

// -------------------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------------

void ResoEffStudy() {

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	TH1D::SetDefaultSumw2();
	TH2D::SetDefaultSumw2();

	gStyle->SetTitleSize(0.0,"t");
	gStyle->SetTitleFont(132,"t");

	gStyle->SetTitleOffset(0.9,"x");
	gStyle->SetTitleOffset(1.,"y");
	gStyle->SetTitleSize(0.05,"xyz");
	gStyle->SetTitleFont(132,"xyz");
	gStyle->SetLabelSize(0.05,"xyz");
	gStyle->SetLabelFont(132,"xyz");
	gStyle->SetNdivisions(10,"xyz");

	gStyle->SetOptStat(0);

	gROOT->ForceStyle();

	// -------------------------------------------------------------------------------------------------------------------------------------------------

//	std::vector<TString> Runs{"Run1"};
	std::vector<TString> Runs{"Run1","Run3"};
//	std::vector<TString> Runs{"Run1","Run2","Run3","Run4","Run5"};

	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

		TFile* OverlayTruthFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/" + UBCodeVersion + "/PreTruthSelection_Overlay9_"\
					  + Runs[WhichRun] + "_"+UBCodeVersion+".root","readonly");
		TTree* treeTruth = (TTree*)(OverlayTruthFile->Get("myPreTruthSelection"));

//		TFile* DataFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_BeamOn9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
//		TTree* treeData = (TTree*)(OverlayFile->Get("myPreSelection"));

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------------------------------------------------------

		// Reco - True diffs in muon length slices

		MuonPrintCanvas(Runs[WhichRun],"Reco_Pt_Recalibrate",tree,"AllPT");
		MuonPrintCanvas(Runs[WhichRun],"Reco_Pt_Recalibrate",tree,"LowPT");
		MuonPrintCanvas(Runs[WhichRun],"Reco_Pt_Recalibrate",tree,"MidPT");
		MuonPrintCanvas(Runs[WhichRun],"Reco_Pt_Recalibrate",tree,"HighPT");

		MuonPrintCanvas(Runs[WhichRun],"Reco_DeltaAlphaT_Recalibrate",tree,"AllDeltaAlphaT");
		MuonPrintCanvas(Runs[WhichRun],"Reco_DeltaAlphaT_Recalibrate",tree,"LowDeltaAlphaT");
		MuonPrintCanvas(Runs[WhichRun],"Reco_DeltaAlphaT_Recalibrate",tree,"MidDeltaAlphaT");
		MuonPrintCanvas(Runs[WhichRun],"Reco_DeltaAlphaT_Recalibrate",tree,"HighDeltaAlphaT");

		MuonPrintCanvas(Runs[WhichRun],"Reco_DeltaPhiT_Recalibrate",tree,"AllDeltaPhiT");
		MuonPrintCanvas(Runs[WhichRun],"Reco_DeltaPhiT_Recalibrate",tree,"LowDeltaPhiT");
		MuonPrintCanvas(Runs[WhichRun],"Reco_DeltaPhiT_Recalibrate",tree,"MidDeltaPhiT");
		MuonPrintCanvas(Runs[WhichRun],"Reco_DeltaPhiT_Recalibrate",tree,"HighDeltaPhiT");

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------------------------------------------------------

		// Reco - True diffs in proton length slices

		ProtonPrintCanvas(Runs[WhichRun],"Reco_Pt_Recalibrate",tree,"AllPT");
		ProtonPrintCanvas(Runs[WhichRun],"Reco_Pt_Recalibrate",tree,"LowPT");
		ProtonPrintCanvas(Runs[WhichRun],"Reco_Pt_Recalibrate",tree,"MidPT");
		ProtonPrintCanvas(Runs[WhichRun],"Reco_Pt_Recalibrate",tree,"HighPT");

		ProtonPrintCanvas(Runs[WhichRun],"Reco_DeltaAlphaT_Recalibrate",tree,"AllDeltaAlphaT");
		ProtonPrintCanvas(Runs[WhichRun],"Reco_DeltaAlphaT_Recalibrate",tree,"LowDeltaAlphaT");
		ProtonPrintCanvas(Runs[WhichRun],"Reco_DeltaAlphaT_Recalibrate",tree,"MidDeltaAlphaT");
		ProtonPrintCanvas(Runs[WhichRun],"Reco_DeltaAlphaT_Recalibrate",tree,"HighDeltaAlphaT");

		ProtonPrintCanvas(Runs[WhichRun],"Reco_DeltaPhiT_Recalibrate",tree,"AllDeltaPhiT");
		ProtonPrintCanvas(Runs[WhichRun],"Reco_DeltaPhiT_Recalibrate",tree,"LowDeltaPhiT");
		ProtonPrintCanvas(Runs[WhichRun],"Reco_DeltaPhiT_Recalibrate",tree,"MidDeltaPhiT");
		ProtonPrintCanvas(Runs[WhichRun],"Reco_DeltaPhiT_Recalibrate",tree,"HighDeltaPhiT");

		// -----------------------------------------------------------------------------------------------------------------------------------------
		// ----------------------------------------------------------------------------------------------------------------------------------------

		// 1D CC1p0pi efficiencies in much finer binning than the actual one used in the analysis

		EfficiencyFunction(Runs[WhichRun],"True_CandidateP_P",tree,"Proton_MCParticle_Mom",treeTruth,20,0.25,1.1);
		EfficiencyFunction(Runs[WhichRun],"True_CandidateMu_P",tree,"Muon_MCParticle_Mom",treeTruth,20,0.1,1.4);

		EfficiencyFunction(Runs[WhichRun],"True_CandidateP_CosTheta",tree,"Proton_MCParticle_CosTheta",treeTruth,20,-1.,1.);
		EfficiencyFunction(Runs[WhichRun],"True_CandidateMu_CosTheta",tree,"Muon_MCParticle_CosTheta",treeTruth,20,-1.,1.);

		EfficiencyFunction(Runs[WhichRun],"True_CandidateP_Phi",tree,"Proton_MCParticle_Phi",treeTruth,20,-180.,180.);
		EfficiencyFunction(Runs[WhichRun],"True_CandidateMu_Phi",tree,"Muon_MCParticle_Phi",treeTruth,20,-180.,180.);

		EfficiencyFunction(Runs[WhichRun],"True_Pt",tree,"True_Pt",treeTruth,20,0.,0.95);
		EfficiencyFunction(Runs[WhichRun],"True_DeltaAlphaT",tree,"True_DeltaAlphaT",treeTruth,20,0.,180.);
		EfficiencyFunction(Runs[WhichRun],"True_DeltaPhiT",tree,"True_DeltaPhiT",treeTruth,20,0.,180.);

		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

		// 2D CC1p0pi efficiencies for muon / proton
		// cos theta vs P
		// P vs phi
		// cos theta vs phi

		TwoEfficiencyFunction(Runs[WhichRun],"True_CandidateMu_P","True_CandidateMu_CosTheta", tree, treeTruth,15,0.1,1.4,15,-1.,1.);
		TwoEfficiencyFunction(Runs[WhichRun],"True_CandidateMu_P","True_CandidateMu_Phi", tree, treeTruth,15,0.1,1.4,15,-180.,180.);
		TwoEfficiencyFunction(Runs[WhichRun],"True_CandidateMu_CosTheta","True_CandidateMu_Phi", tree, treeTruth,15,-1.,1.,15,-180.,180.);

		TwoEfficiencyFunction(Runs[WhichRun],"True_CandidateP_P","True_CandidateP_CosTheta", tree, treeTruth,15,0.25,1.1,15,-1.,1.);
		TwoEfficiencyFunction(Runs[WhichRun],"True_CandidateP_P","True_CandidateP_Phi", tree, treeTruth,15,0.25,1.1,15,-180.,180.);
		TwoEfficiencyFunction(Runs[WhichRun],"True_CandidateP_CosTheta","True_CandidateP_Phi", tree, treeTruth,15,-1.,1.,15,-180.,180.);

		// ---------------------------------------------------------------------------------------------------------------------------------------
		// ---------------------------------------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
