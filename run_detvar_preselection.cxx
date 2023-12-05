{

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// Run3

	WhichSampleArray.push_back("Overlay9_Run3_CV"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_CV_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3_CVextra"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_CVextra_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3_LYDown"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_LYDown_reco2_reco2.root");	
	WhichSampleArray.push_back("Overlay9_Run3_LYAttenuation"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_LYAttenuation_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3_LYRayleigh"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_LYRayleigh_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3_X"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_X_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3_YZ"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_YZ_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3_ThetaYZ"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_ThetaXZ_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3_ThetaXZ"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_ThetaYZ_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3_SCE"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_SCE_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3_Recombination2"); SamplePath.push_back("/uboone/data/users/cthorpe/PELEE_2023_Samples/run3/detvar/numupresel/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_Recombination_reco2_reco2.root");


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
