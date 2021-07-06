{

	vector<TString> WhichSampleArray;

    	WhichSampleArray.push_back("Overlay9_Run1"); // Nominal CV, needs to go first to obtain the relevant calibration
	WhichSampleArray.push_back("BeamOn9_Run1");
	WhichSampleArray.push_back("ExtBNB9_Run1");
	WhichSampleArray.push_back("OverlayDirt9_Run1");

//	WhichSampleArray.push_back("BeamOn9_Run2");
//	WhichSampleArray.push_back("ExtBNB9_Run2");
//	WhichSampleArray.push_back("OverlayDirt9_Run2");
//	WhichSampleArray.push_back("Overlay9_Run2"); // Nominal CV
        
	WhichSampleArray.push_back("Overlay9_Run3"); // Nominal CV, needs to go first to obtain the relevant calibration    
	WhichSampleArray.push_back("BeamOn9_Run3");
	WhichSampleArray.push_back("ExtBNB9_Run3");
	WhichSampleArray.push_back("OverlayDirt9_Run3");   
	
	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L ../../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../../myClasses/STV_Tools.cxx+");	
	gROOT->ProcessLine(".L ../../myClasses/Box_Tools.cxx+");	
	gROOT->ProcessLine(".L ../../myClasses/TruncMean.cxx+");	

	gROOT->ProcessLine(".L PreSelection.C+");
	gROOT->ProcessLine(".L PreTruthSelection.C+");
	gROOT->ProcessLine(".L myPOT.C+");
	gROOT->ProcessLine(".L CreateSplines.cpp+");

	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

		if (string(WhichSampleArray[i]).find("Overlay") != std::string::npos)
		  { gROOT->ProcessLine("myPOT(\""+WhichSampleArray[i]+"\").Loop()"); }

		if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos) { 

			// Run once to get uncalibrated variables from Larsoft
			// Obtain the calibration splines
			// Then rerun to obtain the correct calibrated variables
			// Use the MC calibration across the whole run

			gROOT->ProcessLine("PreSelection(\""+WhichSampleArray[i]+"\").Loop()");
			gROOT->ProcessLine("CreateSplines(\""+WhichSampleArray[i]+"\")"); 

		}

		gROOT->ProcessLine("PreSelection(\""+WhichSampleArray[i]+"\").Loop()");

		if (string(WhichSampleArray[i]).find("Overlay9") != std::string::npos) 
		  { gROOT->ProcessLine("PreTruthSelection(\""+WhichSampleArray[i]+"\").Loop()"); } 

	}

	//gROOT->ProcessLine(".q");
};
