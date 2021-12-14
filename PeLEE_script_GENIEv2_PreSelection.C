{

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// GENIE v2 // Fake Data Set 5

	WhichSampleArray.push_back("GENIEv2Overlay9_Combined"); SamplePath.push_back("/uboone/data/users/davidc/searchingfornues/v08_00_00_44/0702/prod_uboone_nu2020_fakedata_set5_reco2_v08_00_00_41_reco2.root");

	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L ../../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../../myClasses/STV_Tools.cxx+");	

	gROOT->ProcessLine(".L GENIEv2_NeutrinoSelectionFilter.C+");

	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

			gROOT->ProcessLine("GENIEv2_NeutrinoSelectionFilter(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()");

	}

	//gROOT->ProcessLine(".q");
};
