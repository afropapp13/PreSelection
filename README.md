
###########################################

# Calibration & Preselection

root -l script_PreSelection.C

root -l script_DetVar_PreSelection.C

root -l TwoDPlots.cpp

root -l
.L CreateSplines.cpp
CreateSplines("Overlay9_Run1")

./Download2DRecoTruthPlots.sh
