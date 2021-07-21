{

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// NuWro

	WhichSampleArray.push_back("Overlay9NuWro_Run1"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run1_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run2"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run2_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run3"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_NuWro_reco2_reco2.root");

	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L ../../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../../myClasses/STV_Tools.cxx+");	
	//gROOT->ProcessLine(".L ../../myClasses/Box_Tools.cxx+");	
	//gROOT->ProcessLine(".L ../../myClasses/TruncMean.cxx+");	

	//gROOT->ProcessLine(".L PreSelection.C+");
	//gROOT->ProcessLine(".L PreTruthSelection.C+");
	//gROOT->ProcessLine(".L myPOT.C+");
	//gROOT->ProcessLine(".L CreateSplines.cpp+");

	gROOT->ProcessLine(".L PeLEE_myPOT.C+");
	gROOT->ProcessLine(".L NeutrinoSelectionFilter.C+");
	gROOT->ProcessLine(".L TruthNeutrinoSelectionFilter.C+");

	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

		//if (string(WhichSampleArray[i]).find("Overlay") != std::string::npos)
		//  { gROOT->ProcessLine("myPOT(\""+WhichSampleArray[i]+"\").Loop()"); }

		//if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos) { 

			// Run once to get uncalibrated variables from Larsoft
			// Obtain the calibration splines
			// Then rerun to obtain the correct calibrated variables
			// Use the MC calibration across the whole run

		//	gROOT->ProcessLine("PreSelection(\""+WhichSampleArray[i]+"\").Loop()");
		//	gROOT->ProcessLine("CreateSplines(\""+WhichSampleArray[i]+"\")"); 

		//}

		//gROOT->ProcessLine("PreSelection(\""+WhichSampleArray[i]+"\").Loop()");

		//if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos) 
		//  { gROOT->ProcessLine("PreTruthSelection(\""+WhichSampleArray[i]+"\").Loop()"); } 

			if (string(WhichSampleArray[i]).find("Overlay") != std::string::npos)
			  { gROOT->ProcessLine("PeLEE_myPOT(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\")"); }

			gROOT->ProcessLine("NeutrinoSelectionFilter(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()");

			if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos)
			  { gROOT->ProcessLine("TruthNeutrinoSelectionFilter(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()"); }

	}

	//gROOT->ProcessLine(".q");
};
