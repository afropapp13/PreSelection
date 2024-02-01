{

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// NuWro

	WhichSampleArray.push_back("Overlay9NuWro_Run1"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run1_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run2"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run2_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run3"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run4a"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_nuwro_overlay_run4a_pelee.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run4"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_nuwro_overlay_run4_pelee.root");

	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L ../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../myClasses/STV_Tools.cxx+");	

	gROOT->ProcessLine(".L calculate_pot.cxx+");
	gROOT->ProcessLine(".L neutrino_selection.cxx+");
	gROOT->ProcessLine(".L true_neutrino_selection.cxx+");

	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

			if (string(WhichSampleArray[i]).find("Overlay") != std::string::npos)
			  { gROOT->ProcessLine("calculate_pot(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\")"); }

			gROOT->ProcessLine("neutrino_selection(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()");

			if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos)
			  { gROOT->ProcessLine("true_neutrino_selection(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()"); }

	}

	//gROOT->ProcessLine(".q");
};
