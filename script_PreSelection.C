{

	vector<TString> WhichSampleArray;

	WhichSampleArray.push_back("BeamOn9_Run1");
	WhichSampleArray.push_back("ExtBNB9_Run1");
	WhichSampleArray.push_back("OverlayDirt9_Run1");
        WhichSampleArray.push_back("Overlay9_Run1"); // Nominal CV

        WhichSampleArray.push_back("Overlay9NuWro_Run1"); // Fake Data

//	WhichSampleArray.push_back("BeamOn9_Run2");
//	WhichSampleArray.push_back("ExtBNB9_Run2");
//	WhichSampleArray.push_back("OverlayDirt9_Run2");
//	WhichSampleArray.push_back("Overlay9_Run2"); // Nominal CV
        
	WhichSampleArray.push_back("BeamOn9_Run3");
	WhichSampleArray.push_back("ExtBNB9_Run3");
	WhichSampleArray.push_back("OverlayDirt9_Run3");
	WhichSampleArray.push_back("Overlay9_Run3"); // Nominal CV       
	
	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L ../../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../../myClasses/STV_Tools.cxx+");	
	gROOT->ProcessLine(".L ../../myClasses/Box_Tools.cxx+");	
	gROOT->ProcessLine(".L ../../myClasses/TruncMean.cxx+");	

	gROOT->ProcessLine(".L PreSelection.C+");
	gROOT->ProcessLine(".L PreTruthSelection.C+");
	gROOT->ProcessLine(".L myPOT.C+");

	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

		if (string(WhichSampleArray[i]).find("Overlay") != std::string::npos)
		  { gROOT->ProcessLine("myPOT(\""+WhichSampleArray[i]+"\").Loop()"); }

		gROOT->ProcessLine("PreSelection(\""+WhichSampleArray[i]+"\").Loop()");

		if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos) 
		  { gROOT->ProcessLine("PreTruthSelection(\""+WhichSampleArray[i]+"\").Loop()"); } 

	}

	//gROOT->ProcessLine(".q");
};
