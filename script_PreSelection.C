{

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// BeamOn Samples

	//WhichSampleArray.push_back("BeamOn9_Run1"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run1_neutrinoselection_filt_numu_ALL.root");

	// ExtBNB

	//WhichSampleArray.push_back("ExtBNB9_Run1"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run1/data_extbnb_mcc9.1_v08_00_00_25_reco2_C_all_reco2.root");

	// MC CV

	WhichSampleArray.push_back("MC"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run1_reco2_reco2.root");

	// Dirt

	//WhichSampleArray.push_back("OverlayDirt9_Run1"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run1_reco2_reco2.root");

	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L NeutrinoSelectionFilter.C++");

	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

//		gROOT->ProcessLine("NeutrinoSelectionFilter(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()");
		gROOT->ProcessLine("NeutrinoSelectionFilter().Loop()");

	}

	//gROOT->ProcessLine(".q");
};
