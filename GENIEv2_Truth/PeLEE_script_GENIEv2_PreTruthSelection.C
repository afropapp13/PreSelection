{

	// ----------------------------------------------------------------------------------

	gROOT->ProcessLine(".L ../../../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../../../myClasses/STV_Tools.cxx+");	

	gROOT->ProcessLine(".L myPreFilter.C++");
	gROOT->ProcessLine("myPreFilter().Loop()");

	//gROOT->ProcessLine(".q");
};
