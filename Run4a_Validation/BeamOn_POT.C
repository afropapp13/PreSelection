#include <TFile.h>
#include <TTree.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

void BeamOn_POT() {
	 
	TString Sample = "/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_65/031923/v00/bnb_on_run5_reco2_v08_00_00_66_run5_reco2_beam_good.root";
	TString Label = "BeamOn_Run5";

	ofstream fpot;
	fpot.open (Label + ".txt");

	int run;
	int subRun;

	TTree* tree;
	TFile* PeLEEFile = TFile::Open(Sample,"readonly");
	TDirectory * dir = (TDirectory*)PeLEEFile->Get(Sample+":/nuselection");
    dir->GetObject("SubRun",tree);

	tree->SetBranchAddress( "run", &run );
	tree->SetBranchAddress( "subRun", &subRun );	

	for ( int se = 0; se < tree->GetEntries(); ++se ) {

		tree->GetEntry( se );
		//cout << run << "\t" << subRun << endl;
		fpot << run << " " << subRun << endl;

	}

	fpot.close();

} // End of the program
