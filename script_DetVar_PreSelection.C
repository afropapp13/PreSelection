{

	vector<TString> WhichSampleArray;

	// Detector Systematics // Starting from the same GENIE events

	/*
	// v33
       
	WhichSampleArray.push_back("Overlay9_Run1_CV");
	WhichSampleArray.push_back("Overlay9_Run1_X");
	WhichSampleArray.push_back("Overlay9_Run1_YZ");
	WhichSampleArray.push_back("Overlay9_Run1_LY");
	WhichSampleArray.push_back("Overlay9_Run1_LYRayleigh");
	*/

	//v43

	WhichSampleArray.push_back("Overlay9_Run1_CV");
        WhichSampleArray.push_back("Overlay9_Run1_LYDown");
	WhichSampleArray.push_back("Overlay9_Run1_LYRayleigh");
//	WhichSampleArray.push_back("Overlay9_Run1_LYAttenuation"); // Should't even have been produced, only for Run3

	WhichSampleArray.push_back("Overlay9_Run3_CV");
        WhichSampleArray.push_back("Overlay9_Run3_LYDown");
	WhichSampleArray.push_back("Overlay9_Run3_LYRayleigh");
	WhichSampleArray.push_back("Overlay9_Run3_LYAttenuation");

	WhichSampleArray.push_back("Overlay9_Run3_WireModX");
	WhichSampleArray.push_back("Overlay9_Run3_WireModYZ");
	WhichSampleArray.push_back("Overlay9_Run3_WireModThetaYZ");
	WhichSampleArray.push_back("Overlay9_Run3_WireModThetaXZ");
//	WhichSampleArray.push_back("Overlay9_Run3_dEdx"); // Known issue, don't use it
	WhichSampleArray.push_back("Overlay9_Run3_Recombination2");
	WhichSampleArray.push_back("Overlay9_Run3_SCE");

	// -------------------------------------------------------

	gROOT->ProcessLine(".L ../../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../../myClasses/STV_Tools.cxx+");
	gROOT->ProcessLine(".L ../../myClasses/Box_Tools.cxx+");		

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
