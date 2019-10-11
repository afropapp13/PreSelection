{
gROOT->ProcessLine(".L ../../MyClasses/TrackVertexSorting.cxx+");
gROOT->ProcessLine(".L ../../MyClasses/Tools.cxx+");
gROOT->ProcessLine(".L PreTruthSelection.C+");
gROOT->ProcessLine("PreTruthSelection().Loop()");
gROOT->ProcessLine(".q");
};
