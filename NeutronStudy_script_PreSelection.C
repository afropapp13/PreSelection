{

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// Full BeamOn Samples

//	WhichSampleArray.push_back("BeamOn9_Run1"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run1_neutrinoselection_filt_numu_ALL.root");

	// ExtBNB

//	WhichSampleArray.push_back("ExtBNB9_Run1"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run1/data_extbnb_mcc9.1_v08_00_00_25_reco2_C_all_reco2.root");

	// MC CV

	WhichSampleArray.push_back("NeutronStudy_Overlay9_Run1"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/neutronstudy_overlay_run1.root");

	// Dirt

//	WhichSampleArray.push_back("OverlayDirt9_Run1"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run1_reco2_reco2.root");

	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L ../../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../../myClasses/STV_Tools.cxx+");	
	//gROOT->ProcessLine(".L ../../myClasses/Box_Tools.cxx+");	
	//gROOT->ProcessLine(".L ../../myClasses/TruncMean.cxx+");	


	gROOT->ProcessLine(".L PeLEE_myPOT.C+");
	gROOT->ProcessLine(".L NeutrinoSelectionFilter.C+");
	gROOT->ProcessLine(".L TruthNeutrinoSelectionFilter.C+");

	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

			if (string(WhichSampleArray[i]).find("Overlay") != std::string::npos)
			  { gROOT->ProcessLine("PeLEE_myPOT(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\")"); }

			gROOT->ProcessLine("NeutrinoSelectionFilter(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()");

			if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos)
			  { gROOT->ProcessLine("TruthNeutrinoSelectionFilter(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()"); }

	}

	//gROOT->ProcessLine(".q");
};
