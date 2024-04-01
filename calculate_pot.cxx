#include <TH1.h>
#include <TFile.h>
#include <TTree.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "../myClasses/Constants.h"

using namespace std;
using namespace Constants;

void calculate_pot(TString Label, TString Sample) {
	 
	TTree* tree;
	TFile* PeLEEFile = TFile::Open(Sample,"readonly");
	TDirectory * dir = (TDirectory*)PeLEEFile->Get(Sample+":/nuselection");
	dir->GetObject("SubRun",tree);

	float pot;
	float summed_pot = 0.;
	bool has_pot_branch = ( tree->GetBranch("pot") != nullptr );

	if ( has_pot_branch ) {

		tree->SetBranchAddress( "pot", &pot );

		for ( int se = 0; se < tree->GetEntries(); ++se ) {

			tree->GetEntry( se );
			summed_pot += pot;

		}

	}

	std::cout << Label << " Total POT = " << summed_pot << std::endl;

	TH1D* POTCountHist = new TH1D("POTCountHist","",1,0,1);
	POTCountHist->SetBinContent(1,summed_pot);

	// -------------------------------------------------------------------------------

	// Output File

	TString FileName = "/exp/uboone/data/users/apapadop/PeLEETuples_Atmospherics/PreSelection_"+Label+"_"+UBCodeVersion+"_POT.root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	OutputFile->cd();
	POTCountHist->Write();
	OutputFile->Close();

	// ---------------------------------------------------------------------------------------------------------------------------------------	

	cout << endl << Label << " POTCount = " << summed_pot << endl;
	cout << endl << FileName << " has been created" << endl << endl;

} // End of the program
