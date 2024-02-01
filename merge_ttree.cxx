#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>
#include <TChain.h>
#include <TGaxis.h>
#include <TROOT.h>
#include <TString.h>

using namespace std;

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

void merge_ttree() {

        TString pathIn = "/pnfs/uboone/scratch/users/apapadop/nuwro_run4/neutrinoselection_filt_*.root";
        TString pathOut = "/uboone/data/users/apapadop/searchingfornues/";

	// -----------------------------------------------------------------

	TString FullOutFile = pathOut+"high_stat_prodgenie_bnb_nu_nuwro_overlay_run4_pelee.root";
	TFile* f = TFile::Open(FullOutFile,"recreate");
	f->cd();
	f->mkdir("nuselection")->cd();

	// -----------------------------------------------------------------

	TChain ch("nuselection/NeutrinoSelectionFilter");
	cout << "About to start looping!" << endl;
	//for (int i = 0;i<2500;i++) { if (i%100 == 0) { cout << "Event " << i << endl; } ch.Add(pathIn); }
	ch.Add(pathIn);
	cout << "chain events = " << ch.GetEntries() << endl << endl;
	cout << "Done looping, about to start merging!" << endl;
	ch.CloneTree(-1,"fast");
	cout << "Done merging NeutrinoSelectionFilter!" << endl;

	// -----------------------------------------------------------------

        TChain chPOT("nuselection/SubRun");
	//for (int i = 0;i<2500;i++) { if (i%100 == 0) { cout << "Event " << i << endl; } chPOT.Add(pathIn); }
	chPOT.Add(pathIn);
	cout << "POT chain events = " << chPOT.GetEntries() << endl << endl;
	chPOT.CloneTree(-1,"fast");
	f->Write();
	cout << "Done merging SubRun!" << endl;

	// -----------------------------------------------------------------

        std::cout << "path in = " << pathIn << std::endl;
        std::cout << "file out = " << FullOutFile << std::endl;

}

