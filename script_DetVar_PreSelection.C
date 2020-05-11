{

	vector<TString> WhichSampleArray;

	// Detector Systematics // Starting from the same GENIE events
       
	WhichSampleArray.push_back("Overlay9_CV_Run1");
	WhichSampleArray.push_back("Overlay9_X_Run1");
	WhichSampleArray.push_back("Overlay9_YZ_Run1");
	WhichSampleArray.push_back("Overlay9_LY_Run1");
	WhichSampleArray.push_back("Overlay9_LYRayleigh_Run1");
	
	// -------------------------------------------------------

	gROOT->ProcessLine(".L ../../MyClasses/Tools.cxx+");

	gROOT->ProcessLine(".L PreSelection.C+");
	gROOT->ProcessLine(".L PreTruthSelection.C+");
	gROOT->ProcessLine(".L myPOT.C+");

	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

		gROOT->ProcessLine("PreSelection(\""+WhichSampleArray[i]+"\").Loop()");

		if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos) 
		  { gROOT->ProcessLine("PreTruthSelection(\""+WhichSampleArray[i]+"\").Loop()"); } 

                if (string(WhichSampleArray[i]).find("Overlay") != std::string::npos)
                  { gROOT->ProcessLine("myPOT(\""+WhichSampleArray[i]+"\").Loop()"); }

	}

	//gROOT->ProcessLine(".q");
};
