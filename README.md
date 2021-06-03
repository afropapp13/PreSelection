
###########################################

# We need to obtain the momentum calibrations first
# Run only over the MCs

root -l 
.L PreSelection.C
PreSelection("Overlay9_Run1");PreSelection("Overlay9_Run3")

root -l CreateSplines.cpp

###########################################

# Now run the actual Preselection

root -l script_PreSelection.C

root -l script_DetVar_PreSelection.C

root -l TwoDPlots.cpp

./Download2DRecoTruthPlots.sh
