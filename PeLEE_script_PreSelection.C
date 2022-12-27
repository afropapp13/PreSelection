{

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// Full BeamOn Samples

	WhichSampleArray.push_back("BeamOn9_Run1"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run1_neutrinoselection_filt_numu_ALL.root");
	WhichSampleArray.push_back("BeamOn9_Run2"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run2_neutrinoselection_filt_numu_ALL.root");
	WhichSampleArray.push_back("BeamOn9_Run3"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_41/cc0pinp/0617/nslice/run3_neutrinoselection_filt_numu_ALL.root");

//	WhichSampleArray.push_back("BeamOn9_Run4a"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/run4a_neutrinoselection_filt_numu_ALL.root");	
//	WhichSampleArray.push_back("BeamOn9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/run4/bnb_on_run4a_reco2_v08_00_00_57_run4a_reco2.root");
	// Rutgers retreat May 2022
	WhichSampleArray.push_back("BeamOn9_Run4aRutgers"); SamplePath.push_back("/pnfs/uboone/persistent/run4/bnb_on_run4a_reco2_v08_00_00_57_run4a_reco2.root");
	// uB Mini-Retreat Nov 14 2022
	//WhichSampleArray.push_back("BeamOn9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/uboonepro/run4_validation/pelee_ntuples_bnb_beam_on_data_v08_00_00_63_run4a_beam_good_fix.root");
	// Nov 14 2022: excluding low purity runs
	//WhichSampleArray.push_back("BeamOn9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1109/bnb_on_run4a_reco2_v08_00_00_63_POT_DEBUG_run4a_reco2_beam_good.root");
	// Nov 23 2023: w/o low purity runs and after chat with Zarko for the current
	WhichSampleArray.push_back("BeamOn9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1121/quality/bnb_on_run4a_reco2_v08_00_00_63_POT_DEBUG_run4a_reco2_beam_good.root");		

	// ExtBNB

	WhichSampleArray.push_back("ExtBNB9_Run1"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run1/data_extbnb_mcc9.1_v08_00_00_25_reco2_C_all_reco2.root");
	WhichSampleArray.push_back("ExtBNB9_Run2"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run2/data_extbnb_mcc9.1_v08_00_00_25_reco2_D_E_all_reco2.root");
	WhichSampleArray.push_back("ExtBNB9_Run3"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_43/0702/run3/data_extbnb_mcc9.1_v08_00_00_25_reco2_F_G_all_reco2.root");
//	WhichSampleArray.push_back("ExtBNB9_Run4a"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/data_extbnb_mcc9.1_v08_00_00_25_reco2_run4a_all_reco2.root");
//	WhichSampleArray.push_back("ExtBNB9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/run4/bnb_run4a_ext_reco2_v08_00_00_57_run4a_reco2.root");
	// Rutgers retreat May 2022
	WhichSampleArray.push_back("ExtBNB9_Run4aRutgers"); SamplePath.push_back("/pnfs/uboone/persistent/run4/bnb_off_run4a_reco2_v08_00_00_57_run4a_reco2.root");	
	// uB Mini Retreat Nov 14 2022
	//WhichSampleArray.push_back("ExtBNB9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/uboonepro/run4_validation/pelee_ntuple_bnb_run4a_ext_reco2_v08_00_00_63_run4a_reco2_all.root");	
	// Nov 23 2022: w/o low purity runs and after chat with Zarko about current
	WhichSampleArray.push_back("ExtBNB9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1121/quality/bnb_run4a_ext_reco2_v08_00_00_63_run4a_reco2_all.root");	
	
	// MC CV

	WhichSampleArray.push_back("Overlay9_Run1"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run1_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run2"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run2_reco2_D1D2_reco2.root");
	WhichSampleArray.push_back("Overlay9_Run3"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_nu_uboone_overlay_mcc9.1_v08_00_00_26_filter_run3_reco2_G_reco2.root");
	// Rutgers retreat May 2022
	WhichSampleArray.push_back("Overlay9_Run4aRutgers"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_nu_uboone_overlay_pelee_ntuple_run4a.root");
	// uB Mini Retreat Nov 14 2022
	//WhichSampleArray.push_back("Overlay9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/run4/prod_extunbiased_standard_nu_overlay_run4a_reco2_WC_v08_00_00_63_pndr_reco2_reco2.root");	
	// Nov 23 2022: w/o low purity runs and after chat with Zarko about current
	WhichSampleArray.push_back("Overlay9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1121/prod_extunbiased_standard_nu_overlay_run4a_reco2_WC_v08_00_00_63_pndr_reco2_reco2_goodruns_goodbeam.root");
	
	// Dirt

	WhichSampleArray.push_back("OverlayDirt9_Run1"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run1_reco2_reco2.root");
	WhichSampleArray.push_back("OverlayDirt9_Run2"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run2_reco2_reco2.root");
	WhichSampleArray.push_back("OverlayDirt9_Run3"); SamplePath.push_back("/uboone/data/users/apapadop/searchingfornues/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run3_reco2_reco2.root");
	// uB workshop Rutgers May 2022
	WhichSampleArray.push_back("OverlayDirt9_Run4aRutgers"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1121/prod_extunbiased_bnb_dirt_overlay_run4a_reco2_v08_00_00_63_run4a_reco2_goodruns_goodbeam.root");
	// uB Mini Retreat Nov 14 2022
	//WhichSampleArray.push_back("OverlayDirt9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1109/prod_extunbiased_bnb_dirt_overlay_run4a_reco2_v08_00_00_63_run4a_reco2.root");	
	// Nov 23 2022: w/o low purity runs and after chat with Zarko about current
	WhichSampleArray.push_back("OverlayDirt9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/run4/v08_00_00_63/1121/prod_extunbiased_bnb_dirt_overlay_run4a_reco2_v08_00_00_63_run4a_reco2_goodruns_goodbeam.root");		

	// buggy dirt sample

//	WhichSampleArray.push_back("OverlayDirt9_Run1"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run1_reco2_reco2.root");
//	WhichSampleArray.push_back("OverlayDirt9_Run2"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_dirt_overlay_v08_00_00_35_all_run2_reco2_reco2.root");
//	WhichSampleArray.push_back("OverlayDirt9_Run3"); SamplePath.push_back("/pnfs/uboone/persistent/users/davidc/searchingfornues/v08_00_00_43/0928/prodgenie_bnb_dirt_overlay_mcc9.1_v08_00_00_26_run3_reco2_reco2.root");

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
