{

	vector<TString> WhichSampleArray;
	WhichSampleArray.push_back("Run1Data9");
	WhichSampleArray.push_back("ExtBNB9");
	WhichSampleArray.push_back("OverlayDirt9");

	WhichSampleArray.push_back("Overlay9"); // CV

	// Detector Systematics

	WhichSampleArray.push_back("Overlay9_SCE");
	WhichSampleArray.push_back("Overlay9_DLdown");

	gROOT->ProcessLine(".L ../../MyClasses/TrackVertexSorting.cxx+");
	gROOT->ProcessLine(".L ../../MyClasses/Tools.cxx+");

	gROOT->ProcessLine(".L PreSelection.C+");
	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

		gROOT->ProcessLine("PreSelection(\""+WhichSampleArray[i]+"\").Loop()");

	}

	gROOT->ProcessLine(".q");
};
