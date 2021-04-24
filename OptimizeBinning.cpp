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

#include "../Secondary_Code/myFunctions.cpp"

// -------------------------------------------------------------------------------------------------------------------------------------------------

void GetFitResult(double &mean, double &sigma, float bin_lower_edge, float bin_upper_edge, TTree* tree, bool save_hist, bool &converged, bool draw_fit_results, std::string var, TString qualifier) {
		
	TCut query;
    
	if (var == "Pt") { query = Form(" (" + qualifier + ") && True_Pt > %f && True_Pt < %f ", bin_lower_edge, bin_upper_edge); }
	else if (var == "DeltaAlphaT") { query = Form(" (" + qualifier + ") && True_DeltaAlphaT > %f && True_DeltaAlphaT < %f ", bin_lower_edge, bin_upper_edge); }
	else if (var == "DeltaPhiT") { query = Form(" (" + qualifier + ") && True_DeltaPhiT > %f && True_DeltaPhiT < %f ", bin_lower_edge, bin_upper_edge); }
	else if (var == "MuonMomentum") { query = Form(" (" + qualifier + ") && True_CandidateMu_P > %f && True_CandidateMu_P < %f ", bin_lower_edge, bin_upper_edge); }
	else if (var == "MuonCosTheta") { query = Form(" (" + qualifier + ") && True_CandidateMu_CosTheta > %f && True_CandidateMu_CosTheta < %f ", bin_lower_edge, bin_upper_edge); }
	else if (var == "MuonPhi") { query = Form(" (" + qualifier + ") && True_CandidateMu_Phi > %f && True_CandidateMu_Phi < %f ", bin_lower_edge, bin_upper_edge); }
	else if (var == "ProtonMomentum") { query = Form(" (" + qualifier + ") && True_CandidateP_P > %f && True_CandidateP_P < %f ", bin_lower_edge, bin_upper_edge); }
	else if (var == "ProtonCosTheta") { query = Form(" (" + qualifier + ") && True_CandidateP_CosTheta > %f && True_CandidateP_CosTheta < %f ", bin_lower_edge, bin_upper_edge); }
	else if (var == "ProtonPhi") { query = Form(" (" + qualifier + ") && True_CandidateP_Phi > %f && True_CandidateP_Phi < %f ", bin_lower_edge, bin_upper_edge); }
 	else { return; }

	TString CanvasName = (TString)(Form("c_%f_%f", bin_upper_edge, sigma));
	TCanvas * c = new TCanvas(CanvasName, CanvasName, 500, 500);
	c->SetLeftMargin(0.15);

	// Get the histogram from the pad

	TH1D *htemp;
    
	// Set the binnning

	if (var == "Pt") { htemp = new TH1D("htemp","", 100, ArrayNBinsDeltaPT[0], ArrayNBinsDeltaPT[NBinsDeltaPT]); }
	else if (var == "DeltaAlphaT") { htemp = new TH1D("htemp","", 100, ArrayNBinsDeltaAlphaT[0], ArrayNBinsDeltaAlphaT[NBinsDeltaAlphaT]); }
	else if (var == "DeltaPhiT") { htemp = new TH1D("htemp","", 100, ArrayNBinsDeltaPhiT[0], ArrayNBinsDeltaPhiT[NBinsDeltaPhiT]); }
	else if (var == "MuonMomentum") { htemp = new TH1D("htemp","", 100, ArrayNBinsMuonMomentum[0], ArrayNBinsMuonMomentum[NBinsMuonMomentum]); }
	else if (var == "MuonCosTheta") { htemp = new TH1D("htemp","", 100, ArrayNBinsMuonCosTheta[0], ArrayNBinsMuonCosTheta[NBinsMuonCosTheta]); }
	else if (var == "MuonPhi") { htemp = new TH1D("htemp","", 100, ArrayNBinsMuonPhi[0], ArrayNBinsMuonPhi[NBinsMuonPhi]); }
	else if (var == "ProtonMomentum") { htemp = new TH1D("htemp","", 100, ArrayNBinsProtonMomentum[0], ArrayNBinsProtonMomentum[NBinsProtonMomentum]); }
	else if (var == "ProtonCosTheta") { htemp = new TH1D("htemp","", 100, ArrayNBinsProtonCosTheta[0], ArrayNBinsProtonCosTheta[NBinsProtonCosTheta]); }
	else if (var == "ProtonPhi") { htemp = new TH1D("htemp","", 100, ArrayNBinsProtonPhi[0], ArrayNBinsProtonPhi[NBinsProtonPhi]); }
	else { return; }

	// Draw the Query and put into histogram

	if (var == "Pt") { tree->Draw("Reco_Pt >> htemp", query); }
	else if (var == "DeltaAlphaT") { tree->Draw("Reco_DeltaAlphaT >> htemp", query); }
	else if (var == "DeltaPhiT") { tree->Draw("Reco_DeltaPhiT >> htemp", query); }
	else if (var == "MuonMomentum") { tree->Draw("(CandidateMu_EndContainment)*CandidateMu_P_Range + (!CandidateMu_EndContainment)*CandidateMu_P_MCS >> htemp", query); }
	else if (var == "MuonCosTheta") { tree->Draw("CandidateMu_CosTheta >> htemp", query); }
	else if (var == "MuonPhi") { tree->Draw("CandidateMu_Phi >> htemp", query); }
	else if (var == "ProtonMomentum") { tree->Draw("CandidateP_P_Range >> htemp", query); }
	else if (var == "ProtonCosTheta") { tree->Draw("CandidateP_CosTheta >> htemp", query); }
	else if (var == "ProtonPhi") { tree->Draw("CandidateP_Phi >> htemp", query); }

	// Fit it with a Gaussian

	htemp->Fit("gaus","Q"); // "Q" supresses the printouts of the fit
    
	// Get the fit result

	TF1 *fit_gaus = htemp->GetFunction("gaus");
    
	// Draw the histogram

	if (save_hist) {

		htemp->SetLineWidth(2);
		htemp->SetLineColor(kBlack);

	}

	htemp->GetYaxis()->SetTitleOffset(1.2);
	htemp->Draw("hist");
	if (converged) { fit_gaus->Draw("same"); }

	mean  = fit_gaus->GetParameter(1);
	sigma = fit_gaus->GetParameter(2);

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	// Tolerance levels

	if (var == "Pt") {

		if ( (sigma*2 >= bin_upper_edge - bin_lower_edge - 0.01 && sigma*2 <= bin_upper_edge - bin_lower_edge + 0.01) && htemp->Integral() > 200) {

			//std::cout << "Fit has converged!: " << 2*sigma/(bin_upper_edge - bin_lower_edge) << std::endl;
			converged = true;

		}

	}

	else if (var == "DeltAlphaT") {

		if ( (sigma*2 >= bin_upper_edge - bin_lower_edge - 1 && sigma*2 <= bin_upper_edge - bin_lower_edge + 1) && htemp->Integral() > 330) {

			//std::cout << "Fit has converged!: " << 2*sigma/(bin_upper_edge - bin_lower_edge) << std::endl;
			converged = true;

		}

	}	

	else if (var == "DeltaPhiT") {
//cout << "bin_upper_edge - bin_lower_edge = " << bin_upper_edge - bin_lower_edge << "  2*sigma = " << 2*sigma << endl;
		if ( (sigma*2 >= bin_upper_edge - bin_lower_edge - 5 && sigma*2 <= bin_upper_edge - bin_lower_edge + 5) && htemp->Integral() > 250) {

			//std::cout << "Fit has converged!: " << 2*sigma/(bin_upper_edge - bin_lower_edge) << std::endl;
			converged = true;

		}

	}	

	else if (var == "MuonMomentum") {

		if ( (sigma*2 >= bin_upper_edge - bin_lower_edge - 0.15 && sigma*2 <= bin_upper_edge - bin_lower_edge + 0.15) && htemp->Integral() > 330) {

			//std::cout << "Fit has converged!: " << 2*sigma/(bin_upper_edge - bin_lower_edge) << std::endl;
			converged = true;

		}

	}	

	else if (var == "MuonCosTheta") {

		if ( (sigma*2 >= bin_upper_edge - bin_lower_edge - 0.1 && sigma*2 <= bin_upper_edge - bin_lower_edge + 0.1) && htemp->Integral() > 330) {

			//std::cout << "Fit has converged!: " << 2*sigma/(bin_upper_edge - bin_lower_edge) << std::endl;
			converged = true;

		}

	}	

	else if (var == "MuonPhi") {

		if ( (sigma*2 >= bin_upper_edge - bin_lower_edge - 0.01 && sigma*2 <= bin_upper_edge - bin_lower_edge + 0.01) && htemp->Integral() > 330) {

			//std::cout << "Fit has converged!: " << 2*sigma/(bin_upper_edge - bin_lower_edge) << std::endl;
			converged = true;

		}

	}	

	else if (var == "ProtonMomentum") {

		if ( (sigma*2 >= bin_upper_edge - bin_lower_edge - 0.05 && sigma*2 <= bin_upper_edge - bin_lower_edge + 0.05) && htemp->Integral() > 330) {

			//std::cout << "Fit has converged!: " << 2*sigma/(bin_upper_edge - bin_lower_edge) << std::endl;
			converged = true;

		}

	}	

	else if (var == "ProtonCosTheta") {

		if ( (sigma*2 >= bin_upper_edge - bin_lower_edge - 0.15 && sigma*2 <= bin_upper_edge - bin_lower_edge + 0.15) && htemp->Integral() > 230) {

			//std::cout << "Fit has converged!: " << 2*sigma/(bin_upper_edge - bin_lower_edge) << std::endl;
			converged = true;

		}

	}	

	else if (var == "ProtonPhi") {

		if ( (sigma*2 >= bin_upper_edge - bin_lower_edge - 0.01 && sigma*2 <= bin_upper_edge - bin_lower_edge + 0.01) && htemp->Integral() > 330) {

			//std::cout << "Fit has converged!: " << 2*sigma/(bin_upper_edge - bin_lower_edge) << std::endl;
			converged = true;

		}

	}	

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	TLatex* range;
	TLatex* fit_params;

	if (save_hist) {
        
		if (var == "Pt") { range = new TLatex(0.88,0.85, Form("Reco #deltap_{T} %0.2f - %0.2f GeV/c",bin_lower_edge, bin_upper_edge )); }
		else if (var == "DeltaAlphaT") { range = new TLatex(0.88,0.85, Form("Reco #delta#alpha_{T} %0.2f - %0.2f deg",bin_lower_edge, bin_upper_edge )); }
		else if (var == "DeltaPhiT") { range = new TLatex(0.88,0.85, Form("Reco #delta#phi_{T} %0.2f - %0.2f deg",bin_lower_edge, bin_upper_edge )); }
		else if (var == "MuonMomentum") { range = new TLatex(0.88,0.85, Form("Reco P_{#mu} %0.2f - %0.2f GeV/c",bin_lower_edge, bin_upper_edge )); }
		else if (var == "MuonCosTheta") { range = new TLatex(0.88,0.85, Form("Reco cos#theta_{#mu} %0.2f - %0.2f",bin_lower_edge, bin_upper_edge )); }
		else if (var == "MuonPhi") { range = new TLatex(0.88,0.85, Form("Reco #phi_{#mu} %0.2f - %0.2f",bin_lower_edge, bin_upper_edge )); }
		else if (var == "ProtonMomentum") { range = new TLatex(0.88,0.85, Form("Reco P_{p} %0.2f - %0.2f GeV/c",bin_lower_edge, bin_upper_edge )); }
		else if (var == "ProtonCosTheta") { range = new TLatex(0.88,0.85, Form("Reco cos#theta_{p} %0.2f - %0.2f",bin_lower_edge, bin_upper_edge )); }
		else if (var == "ProtonPhi") { range = new TLatex(0.88,0.85, Form("Reco #phi_{p} %0.2f - %0.2f",bin_lower_edge, bin_upper_edge )); }
		
		range->SetTextColor(kGray+2);
		range->SetNDC();
		range->SetTextSize(0.038);
		range->SetTextAlign(32);
		range->Draw();

		if (var == "Pt") { fit_params = new TLatex(0.88,0.92, Form("Fit Mean: %0.2f GeV/c, Fit Sigma: %0.2f GeV/c",mean, sigma )); }
		else if (var == "DeltaAlphaT") { fit_params = new TLatex(0.88,0.92, Form("Fit Mean: %0.2f deg, Fit Sigma: %0.2f deg",mean, sigma )); }
		else if (var == "DeltaPhiT") { fit_params = new TLatex(0.88,0.92, Form("Fit Mean: %0.2f deg, Fit Sigma: %0.2f deg",mean, sigma )); }
		else if (var == "MuonMomentum") { fit_params = new TLatex(0.88,0.92, Form("Fit Mean: %0.2f GeV/c, Fit Sigma: %0.2f GeV/c",mean, sigma )); }
		else if (var == "MuonCosTheta") { fit_params = new TLatex(0.88,0.92, Form("Fit Mean: %0.2f, Fit Sigma: %0.2f",mean, sigma )); }
		else if (var == "MuonPhi") { fit_params = new TLatex(0.88,0.92, Form("Fit Mean: %0.2f deg, Fit Sigma: %0.2f deg",mean, sigma )); }
		else if (var == "ProtonMomentum") { fit_params = new TLatex(0.88,0.92, Form("Fit Mean: %0.2f GeV/c, Fit Sigma: %0.2f GeV/c",mean, sigma )); }
		else if (var == "ProtonCosTheta") { fit_params = new TLatex(0.88,0.92, Form("Fit Mean: %0.2f, Fit Sigma: %0.2f",mean, sigma )); }
		else if (var == "ProtonPhi") { fit_params = new TLatex(0.88,0.92, Form("Fit Mean: %0.2f deg, Fit Sigma: %0.2f deg",mean, sigma )); }

		fit_params->SetTextColor(kGray+2);
		fit_params->SetNDC();
		fit_params->SetTextSize(0.038);
		fit_params->SetTextAlign(32);
		if (draw_fit_results) fit_params->Draw();
        
		if (var == "Pt") { htemp->SetTitle(";#deltap_{T} [GeV/c]; Entries"); }
		else if (var == "DeltaAlphaT") { htemp->SetTitle(";#delta#alpha_{T} [GeV/c]; Entries"); }
		else if (var == "DeltaPhiT") { htemp->SetTitle(";#delta#phi_{T} [GeV/c]; Entries"); }
		else if (var == "MuonMomentum") { htemp->SetTitle(";P_{#mu} [GeV/c]; Entries"); }
		else if (var == "MuonCosTheta") { htemp->SetTitle(";cos#theta_{#mu}; Entries"); }
		else if (var == "MuonPhi") { htemp->SetTitle(";#phi_{#mu}; Entries"); }
		else if (var == "ProtonMomentum") { htemp->SetTitle(";P_{p} [GeV/c]; Entries"); }
		else if (var == "ProtonCosTheta") { htemp->SetTitle(";cos#theta_{p}; Entries"); }
		else if (var == "ProtonPhi") { htemp->SetTitle(";#phi_{p}; Entries"); }

		htemp->GetXaxis()->CenterTitle();
		htemp->GetYaxis()->CenterTitle();        
		htemp->SetStats(kFALSE);
		c->SetTopMargin(0.11);

		std::string VarString = std::string(TString(var).ReplaceAll(".","_"));
		std::string LowEdge = std::string(ToStringFloat(bin_lower_edge).ReplaceAll(".","_"));
		std::string UpperEdge = std::string(ToStringFloat(bin_upper_edge).ReplaceAll(".","_"));				
        
		if (var == "Pt") { c->Print(Form(PlotPath+"%s_bins_%sGeV_c_to_%sGeV_c.pdf",VarString.c_str(), LowEdge.c_str(), UpperEdge.c_str() )); }
		else if (var == "DeltaAlphaT") { c->Print(Form(PlotPath+"%s_bins_%sdeg_to_%sdeg.pdf",VarString.c_str(), LowEdge.c_str(), UpperEdge.c_str() )); }
		else if (var == "DeltaPhiT") { c->Print(Form(PlotPath+"%s_bins_%sdeg_to_%sdeg.pdf",VarString.c_str(), LowEdge.c_str(), UpperEdge.c_str() )); }
		else if (var == "MuonMomentum") { c->Print(Form(PlotPath+"%s_bins_%sGeV_c_to_%sGeV_c.pdf",VarString.c_str(), LowEdge.c_str(), UpperEdge.c_str() )); }	
		else if (var == "MuonCosTheta") { c->Print(Form(PlotPath+"%s_bins_%s_to_%s.pdf",VarString.c_str(), LowEdge.c_str(), UpperEdge.c_str() )); }
		else if (var == "MuonPhi") { c->Print(Form(PlotPath+"%s_bins_%sdeg_to_%sdeg.pdf",VarString.c_str(), LowEdge.c_str(), UpperEdge.c_str() )); }						
		else if (var == "ProtonMomentum") { c->Print(Form(PlotPath+"%s_bins_%sGeV_c_to_%sGeV_c.pdf",VarString.c_str(), LowEdge.c_str(), UpperEdge.c_str() )); }	
		else if (var == "ProtonCosTheta") { c->Print(Form(PlotPath+"%s_bins_%s_to_%s.pdf",VarString.c_str(), LowEdge.c_str(), UpperEdge.c_str() )); }
		else if (var == "ProtonPhi") { c->Print(Form(PlotPath+"%s_bins_%sdeg_to_%sdeg.pdf",VarString.c_str(), LowEdge.c_str(), UpperEdge.c_str() )); }

	} // End of the case where we save the hist

	//std::cout << "Integral: " <<htemp->Integral() << std::endl;

	delete htemp;
	delete c;

}

// -------------------------------------------------------------------------------------------------------------------------------------------------

void OptimizeBinning() {

	// -------------------------------------------------------------------------------------------------------------------------------------------------

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

	// -------------------------------------------------------------------------------------------------------------------------------------------------

	std::vector<TString> Runs{"Run1"};
//	std::vector<TString> Runs{"Run1","Run3"};
//	std::vector<TString> Runs{"Run1","Run2","Run3","Run4","Run5"};

	const int NRuns = Runs.size();

	for (int WhichRun = 0; WhichRun < NRuns; WhichRun++) {

		// -----------------------------------------------------------------------------------------------------------------------------------------

		TFile* OverlayFile = TFile::Open("/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_Overlay9_"+Runs[WhichRun]+"_"+UBCodeVersion+".root","readonly");
		TTree* tree = (TTree*)(OverlayFile->Get("myPreSelection"));

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

		TString qualifier = CC1p +" && "+ Containment +" && " + ProtonMom + " && " + DeltaPT + " && " + DeltaPhiT + " && " + MuonMom;

		TLatex *text = new TLatex();
		text->SetTextFont(FontStyle);
		text->SetTextSize(0.05);

		// --------------------------------------------------------------------------------------------------------

	    	// The variable to optimise

//	    	std::string var = std::string("Pt");
//	    	std::string var = std::string("DeltaAlphaT");
	    	std::string var = std::string("DeltaPhiT");
//	    	std::string var = std::string("MuonMomentum");
//	    	std::string var = std::string("MuonCosTheta");
//	    	std::string var = std::string("MuonPhi");
//	    	std::string var = std::string("ProtonMomentum");
//	    	std::string var = std::string("ProtonCosTheta");
//	    	std::string var = std::string("ProtonPhi");

	    	int nbins = 10; // Default // 1st bin is for initialization
//	    	int nbins = 2; // Alternative

//			if (var == "ProtonCosTheta") { nbins = 13; }

	    	// Load in the tfile and tree
	    	double mean{0.0}, sigma{0.0};
	    	bool converged = false;

	    	// Were do we want to start the fit iteration from?

		float lower_bin = 0.0;

		// The last bin to go up to?

		float upper_bin = 1.0;

		// What increment size to increase the bins by

		float increment_size = 0.01;

		// Loop over the bins

		for (float bin = 0; bin < nbins; bin++ ) {

			std::cout << "\n\033[0;34mTrying to optimise bin # " << bin << " / " << nbins << " for "+ var + "\033[0m\n"<< std::endl;
			converged = false;

			// Slide upper bin value till we get 2xthe STD of the fit

			for (float i = lower_bin + increment_size; i <= upper_bin; i += increment_size) {

				// ------------------------------------------------------------------------------------------------

				// The 1st iteration usually fails, but we need to initialize the process

				if (bin == 0 && var == "Pt") {

					bool fake = true;
					GetFitResult(mean, sigma, ArrayNBinsDeltaPT[0], ArrayNBinsDeltaPT[NBinsDeltaPT], tree, true, fake, true, var, qualifier);
					lower_bin = ArrayNBinsDeltaPT[0];
					upper_bin = ArrayNBinsDeltaPT[NBinsDeltaPT];
					increment_size = 0.01;					
					break;

				}

				if (bin == 0 && var == "DeltaAlphaT") {

					bool fake = true;
					GetFitResult(mean, sigma, ArrayNBinsDeltaAlphaT[0], ArrayNBinsDeltaAlphaT[NBinsDeltaAlphaT], tree, true, fake, true, var, qualifier);
					lower_bin = ArrayNBinsDeltaAlphaT[0];
					upper_bin = ArrayNBinsDeltaAlphaT[NBinsDeltaAlphaT];
					increment_size = 1;
					break;

				}

				if (bin == 0 && var == "DeltaPhiT") {

					bool fake = true;
					GetFitResult(mean, sigma, ArrayNBinsDeltaPhiT[0], ArrayNBinsDeltaPhiT[0] + 10, tree, true, fake, true, var, qualifier);
					lower_bin = ArrayNBinsDeltaPhiT[0];
					upper_bin = ArrayNBinsDeltaPhiT[NBinsDeltaPhiT];
					increment_size = 15.;
					break;

				}

				if (bin == 0 && var == "MuonMomentum") {

					bool fake = true;
					GetFitResult(mean, sigma, ArrayNBinsMuonMomentum[0], ArrayNBinsMuonMomentum[NBinsMuonMomentum], tree, true, fake, true, var, qualifier);					
					lower_bin = ArrayNBinsMuonMomentum[0];
					upper_bin = ArrayNBinsMuonMomentum[NBinsMuonMomentum];
					increment_size = 0.1;
					break;

				}

				if (bin == 0 && var == "MuonCosTheta") {

					bool fake = true;
					GetFitResult(mean, sigma, ArrayNBinsMuonCosTheta[0], ArrayNBinsMuonCosTheta[0] + 0.01, tree, true, fake, true, var, qualifier);
					lower_bin = ArrayNBinsMuonCosTheta[0];
					upper_bin = ArrayNBinsMuonCosTheta[NBinsMuonCosTheta];
					increment_size = 0.01;
					break;

				}

				if (bin == 0 && var == "MuonPhi") {

					bool fake = true;
					GetFitResult(mean, sigma, -180, 10, tree, true, fake, true, var, qualifier);
					lower_bin = ArrayNBinsMuonPhi[0];
					upper_bin = ArrayNBinsMuonPhi[NBinsMuonPhi];
					increment_size = 0.01;
					break;

				}

				if (bin == 0 && var == "ProtonMomentum") {

					bool fake = true;
					GetFitResult(mean, sigma, ArrayNBinsProtonMomentum[0], ArrayNBinsProtonMomentum[NBinsProtonMomentum], tree, true, fake, true, var, qualifier);
					lower_bin = ArrayNBinsProtonMomentum[0];
					upper_bin = ArrayNBinsProtonMomentum[NBinsProtonMomentum];
					increment_size = 0.1;
					break;

				}

				if (bin == 0 && var == "ProtonCosTheta") {

					bool fake = true;
					GetFitResult(mean, sigma, ArrayNBinsProtonCosTheta[0],ArrayNBinsProtonCosTheta[0] + 0.1, tree, true, fake, true, var, qualifier);
					lower_bin = ArrayNBinsProtonCosTheta[0];
					upper_bin = ArrayNBinsProtonCosTheta[NBinsProtonCosTheta];
					increment_size = 0.2;
					break;

				}

				if (bin == 0 && var == "ProtonPhi") {

					bool fake = true;
					GetFitResult(mean, sigma, ArrayNBinsProtonPhi[0], ArrayNBinsProtonPhi[0] + 10, tree, true, fake, true, var, qualifier);
					lower_bin = ArrayNBinsProtonPhi[0];
					upper_bin = ArrayNBinsProtonPhi[NBinsMuonPhi];
					increment_size = 1.;
					break;

				}

				// ------------------------------------------------------------------------------------------------

				// call function which draws the tree to a canvas, fits the tree and returns the fit parameter
				// If the fit has 2xSTD = the reco bin size then we have successfully optimised the bin

				GetFitResult(mean, sigma, lower_bin, i, tree, false, converged, false, var, qualifier);

				// If it converged, do it again and print the canvas then break

				if (converged) {
				
					GetFitResult(mean, sigma, lower_bin, i, tree, true, converged, true, var, qualifier);
					//std::cout << "\n\033[0;34mMean: " << mean << "  Sigma: " << sigma<< "\033[0m"<< std::endl;
					std::cout << "\033[0;34mLower bound: " << lower_bin << " Upper bound: " << i << "\033[0m\n" << std::endl;
					
					// Reset the lower bin value

					lower_bin = i;
					break;

				}

				// Since the fit doesnt want to converge for elec_E for the last bin, lets just draw it anyway
		
				if (bin == nbins-1) {

					bool fake = true;
					GetFitResult(mean, sigma, lower_bin, upper_bin, tree, true, fake, true, var, qualifier);
					break;

				}

			} // End of the loop between lower / upper bins

		} // End of the loop over the bins

		// --------------------------------------------------------------------------------------------------------

	} // End of the loop over the runs

} // End of the program 
