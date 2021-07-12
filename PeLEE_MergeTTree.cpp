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

void PeLEE_MergeTTree(TString number,TString OutName) {

        TString pathIn = "/pnfs/uboone/scratch/users/apapadop/v08_00_00_54/"+OutName+"/July04/"+OutName+"/v00/"+number;
        TString pathScratch = "/pnfs/uboone/scratch/users/apapadop/";
        TString pathOut = "/uboone/data/users/apapadop/searchingfornues/";

	// -----------------------------------------------------------------

	TString FullOutFile = pathOut+"high_stat_prodgenie_bnb_nu_overlay_DetVar_"+OutName+"_reco2_reco2.root";
	TFile* f = TFile::Open(FullOutFile,"recreate");
	f->cd();
	f->mkdir("nuselection")->cd();

	// -----------------------------------------------------------------

//        TChain ch("nuselection/NeutrinoSelectionFilter");
//	for (int i = 0;i<2500;i++) { ch.Add(Form(pathIn+"_%s/neutrinoselection_filt_*.root",std::to_string(i).c_str())); }
//        ch.Merge(f,1000);

	// -----------------------------------------------------------------

////	f->cd();
////	f->cd("nuselection");
//        TChain chPOT("nuselection/SubRun");
//	for (int i = 0;i<2500;i++) { chPOT.Add(Form(pathIn+"_%s/neutrinoselection_filt_*.root",std::to_string(i).c_str())); }
//	f->cd("nuselection");
//        chPOT.Merge(f,1000);

	// -----------------------------------------------------------------

        TChain ch("nuselection/NeutrinoSelectionFilter");
	cout << "About to start looping!" << endl;
	for (int i = 0;i<2500;i++) { if (i%100 == 0) { cout << "Event " << i << endl; } ch.Add(Form(pathIn+"_%s/neutrinoselection_filt_*.root",std::to_string(i).c_str())); }
	cout << "chain events = " << ch.GetEntries() << endl << endl;
	cout << "Done looping, about to start merging!" << endl;
//	ch.Merge(pathScratch+"NeutrinoSelectionFilter_high_stat_prodgenie_bnb_nu_overlay_DetVar_"+OutName+"_reco2_reco2.root");
//        ch.Merge(f,1000);
	ch.CloneTree(-1,"fast");
//	f->Write();
	cout << "Done merging NeutrinoSelectionFilter!" << endl;

	// -----------------------------------------------------------------

        TChain chPOT("nuselection/SubRun");
	for (int i = 0;i<2500;i++) { if (i%100 == 0) { cout << "Event " << i << endl; } chPOT.Add(Form(pathIn+"_%s/neutrinoselection_filt_*.root",std::to_string(i).c_str())); }
	cout << "POT chain events = " << chPOT.GetEntries() << endl << endl;
//	f->cd("nuselection");
//        chPOT.Merge(f,1000);
	chPOT.CloneTree(-1,"fast");
	f->Write();
	cout << "Done merging SubRun!" << endl;

	// -----------------------------------------------------------------

        std::cout << "path in = " << pathIn << std::endl;
//        std::cout << "path scratch = " << pathScratch << std::endl;
        std::cout << "path out = " << pathOut << std::endl;

}

