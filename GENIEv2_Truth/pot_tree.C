#define pot_tree_cxx
#include "pot_tree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "ubana/myClasses/Constants.h"

using namespace std;
using namespace Constants;

void pot_tree::Loop() {

   //----------------------------------------//

   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   //----------------------------------------//

	float summed_pot = 0.;   

   //----------------------------------------//

   // Loop over the events

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
   
      //----------------------------------------//
      
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      summed_pot += totpot;

      //----------------------------------------//

   } // End of the loop over the events

   //----------------------------------------//   

	std::cout << "GENIEv2Overlay9_Combined Total POT = " << summed_pot << std::endl;

	TH1D* POTCountHist = new TH1D("POTCountHist","",1,0,1);
	POTCountHist->SetBinContent(1,summed_pot);

   //----------------------------------------//

	// Output File

	TString FileName = "/pnfs/uboone/persistent/users/apapadop/mySamples/"+UBCodeVersion+"/PeLEETuples/PreSelection_GENIEv2Overlay9_Combined_"+UBCodeVersion+"_POT.root";
	TFile* OutputFile = new TFile(FileName,"recreate");
	OutputFile->cd();
	POTCountHist->Write();
	OutputFile->Close();

   //----------------------------------------//	

	cout << endl << "GENIEv2Overlay9_Combined POTCount = " << summed_pot << endl;
	cout << endl << FileName << " has been created" << endl << endl;

   //----------------------------------------//

} // End of the program