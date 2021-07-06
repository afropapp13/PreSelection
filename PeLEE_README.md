
###########################################

# Calibration & Preselection

root -l PeLEE_script_PreSelection.C

hadd -f /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreSelection_BeamOn9_Combined_v08_00_00_52.root /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreSelection_BeamOn9_Run{1,2,3}_v08_00_00_52.root

hadd -f /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreSelection_ExtBNB9_Combined_v08_00_00_52.root /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreSelection_ExtBNB9_Run{1,2,3}_v08_00_00_52.root

hadd -f /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreSelection_Overlay9_Combined_v08_00_00_52.root /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreSelection_Overlay9_Run{1,2,3}_v08_00_00_52.root

hadd -f /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreSelection_OverlayDirt9_Combined_v08_00_00_52.root /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreSelection_OverlayDirt9_Run{1,2,3}_v08_00_00_52.root

hadd -f /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreTruthSelection_Overlay9_Combined_v08_00_00_52.root /pnfs/uboone/persistent/users/apapadop/mySamples/v08_00_00_52/PeLEETuples/PreTruthSelection_Overlay9_Run{1,2,3}_v08_00_00_52.root

root -l script_DetVar_PreSelection.C

root -l PeLEE_TwoDPlots.cpp

root -l
.L PeLEE_CreateSplines.cpp
PeLEE_CreateSplines("Overlay9_Combined")

# locally
./PeLEE_Download2DRecoTruthPlots.sh
