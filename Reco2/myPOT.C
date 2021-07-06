#define myPOT_cxx
#include "myPOT.h"
#include <TH1.h>
#include <TFile.h>

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

void myPOT::Loop() {
	 
	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();
	Long64_t nbytes = 0, nb = 0;

	double POTCount = 0.;

	for (Long64_t jentry=0; jentry<nentries;jentry++) {

			Long64_t ientry = LoadTree(jentry); if (ientry < 0) break;
			nb = fChain->GetEntry(jentry);	 nbytes += nb;

			POTCount += POT;

	} // End of the loop over the events

	std::cout << fWhichSample << " Total POT = " <<	POTCount << std::endl;

	TH1D* POTCountHist = new TH1D("POTCountHist","",1,0,1);
	POTCountHist->SetBinContent(1,POTCount);

	// -------------------------------------------------------------------------------

	// Output File

	TString FileName = "/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PreSelection_"+fWhichSample+"_"+UBCodeVersion+"_POT.root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	OutputFile->cd();
	POTCountHist->Write();
	OutputFile->Close();

	// ---------------------------------------------------------------------------------------------------------------------------------------

	// Txt file to keep track of the POT

	TString TxtName = "/uboone/data/users/apapadop/myEvents/myTxtFiles/"+UBCodeVersion+"/TxtPOT_"+fWhichSample+"_"+UBCodeVersion+".txt";
	ofstream myTxtFile;
	myTxtFile.open(TxtName);	

	myTxtFile << "POTCount = " << POTCount << std::endl;

} // End of the program
