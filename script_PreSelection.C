{
gROOT->ProcessLine(".L ../../MyClasses/TrackVertexSorting.cxx+");
gROOT->ProcessLine(".L ../../MyClasses/Tools.cxx+");
gROOT->ProcessLine(".L PreSelection.C+");
gROOT->ProcessLine("PreSelection().Loop()");
gROOT->ProcessLine(".q");
};
