{

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// dublicate MC, hacked PeLEE module to gran true p_n from Local FG

	WhichSampleArray.push_back("Dublicate_Overlay9_Run1"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run1_Overlay_reco2_reco2.root");
	WhichSampleArray.push_back("Dublicate_Overlay9_Run2"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run2_Overlay_reco2_reco2.root");
	WhichSampleArray.push_back("Dublicate_Overlay9_Run3"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_Overlay_reco2_reco2.root");
	
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

			if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos && !(string(WhichSampleArray[i]).find("Dublicate") != std::string::npos))
			  { gROOT->ProcessLine("TruthNeutrinoSelectionFilter(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()"); }

	}

	//gROOT->ProcessLine(".q");
};
