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
	 
	TString Sample = "/uboone/data/users/apapadop/searchingfornues/data_beamon_v08_00_00_67_pelee_ntuple_run5_v67.root";
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

// then run 
// python /uboone/app/users/zarko/getDataInfo.py --run-subrun-list BeamOn_Run5.txt -v 2