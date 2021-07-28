{

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// Full BeamOn Samples

	WhichSampleArray.push_back("BeamOn9_Run1"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run1_neutrinoselection_filt_numu_ALL.root");
	WhichSampleArray.push_back("BeamOn9_Run2"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run2_neutrinoselection_filt_numu_ALL.root");
	WhichSampleArray.push_back("BeamOn9_Run3"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run3_neutrinoselection_filt_numu_ALL.root");

	// ExtBNB

	WhichSampleArray.push_back("ExtBNB9_Run1"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run1/data_extbnb_mcc9.1_v08_00_00_25_reco2_C_all_reco2.root");
	WhichSampleArray.push_back("ExtBNB9_Run2"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run2/data_extbnb_mcc9.1_v08_00_00_25_reco2_D_E_all_reco2.root");
	WhichSampleArray.push_back("ExtBNB9_Run3"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run3/data_extbnb_mcc9.1_v08_00_00_25_reco2_F_G_all_reco2.root");


	// MC CV

	WhichSampleArray.push_back("Overlay9_Run1"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run1_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run2"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run2_reco2_D1D2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run3_reco2_G_reco2.root");

	// Dirt

	WhichSampleArray.push_back("OverlayDirt9_Run1"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run1_reco2_reco2.root");
	WhichSampleArray.push_back("OverlayDirt9_Run2"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run2_reco2_reco2.root");
	WhichSampleArray.push_back("OverlayDirt9_Run3"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run3_reco2_reco2.root");

	// buggy

//	WhichSampleArray.push_back("OverlayDirt9_Run1"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run1_reco2_reco2.root");
//	WhichSampleArray.push_back("OverlayDirt9_Run2"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_dirt_overlay_v08_00_00_35_all_run2_reco2_reco2.root");
//	WhichSampleArray.push_back("OverlayDirt9_Run3"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run3_reco2_reco2.root");
	
	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L ../../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../../myClasses/STV_Tools.cxx+");	
	//gROOT->ProcessLine(".L ../../myClasses/Box_Tools.cxx+");	
	//gROOT->ProcessLine(".L ../../myClasses/TruncMean.cxx+");	

	//gROOT->ProcessLine(".L PreSelection.C+");
	//gROOT->ProcessLine(".L PreTruthSelection.C+");
	//gROOT->ProcessLine(".L myPOT.C+");
	//gROOT->ProcessLine(".L CreateSplines.cpp+");

	gROOT->ProcessLine(".L PeLEE_myCCQEPOT.C+");
	gROOT->ProcessLine(".L CCQENeutrinoSelectionFilter.C+");
	gROOT->ProcessLine(".L TruthCCQENeutrinoSelectionFilter.C+");

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
			  { gROOT->ProcessLine("PeLEE_myCCQEPOT(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\")"); }

			gROOT->ProcessLine("CCQENeutrinoSelectionFilter(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()");

			if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos)
			  { gROOT->ProcessLine("TruthCCQENeutrinoSelectionFilter(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()"); }

	}

	//gROOT->ProcessLine(".q");
};
