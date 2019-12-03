{

	vector<TString> WhichTruthSampleArray;

	WhichTruthSampleArray.push_back("Overlay9"); // CV

	// Detector Systematics

	WhichTruthSampleArray.push_back("Overlay9_SCE");
	WhichTruthSampleArray.push_back("Overlay9_DLdown");

	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L ../../MyClasses/TrackVertexSorting.cxx+");
	gROOT->ProcessLine(".L ../../MyClasses/Tools.cxx+");

	gROOT->ProcessLine(".L PreTruthSelection.C+");

	for (int i =0;i < (int)(WhichTruthSampleArray.size()); i++) {

		gROOT->ProcessLine("PreTruthSelection(\""+WhichTruthSampleArray[i]+"\").Loop()");

	}

	//gROOT->ProcessLine(".q");
};
