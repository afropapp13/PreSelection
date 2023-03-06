
###########################################

# Calibration & Preselection

root -b PeLEE_script_PreSelection.C

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreSelection_BeamOn9_Combined_v08_00_00_52.root /uboone/data/users/apapadop/PeLEETuples/PreSelection_BeamOn9_Run{1,2,3}_v08_00_00_52.root

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreSelection_ExtBNB9_Combined_v08_00_00_52.root /uboone/data/users/apapadop/PeLEETuples/PreSelection_ExtBNB9_Run{1,2,3}_v08_00_00_52.root

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9_Combined_v08_00_00_52.root /uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9_Run{1,2,3}_v08_00_00_52.root

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreSelection_OverlayDirt9_Combined_v08_00_00_52.root /uboone/data/users/apapadop/PeLEETuples/PreSelection_OverlayDirt9_Run{1,2,3}_v08_00_00_52.root

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreTruthSelection_Overlay9_Combined_v08_00_00_52.root /uboone/data/users/apapadop/PeLEETuples/PreTruthSelection_Overlay9_Run{1,2,3}_v08_00_00_52.root

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9_Combined_v08_00_00_52_POT.root /uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9_Run{1,2,3}_v08_00_00_52_POT.root

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreSelection_OverlayDirt9_Combined_v08_00_00_52_POT.root /uboone/data/users/apapadop/PeLEETuples/PreSelection_OverlayDirt9_Run{1,2,3}_v08_00_00_52_POT.root

root -b PeLEE_TwoDPlots.cpp

# DO NOT DELETE !!!
# my own production to perform the LFG/Pmiss/kMiss/PnProxy studies

# root -b PeLEE_script_Dublicate_PreSelection.C

#hadd -f /uboone/data/users/apapadop/PeLEETuples/PreSelection_Dublicate_Overlay9_Combined_v08_00_00_52.root /uboone/data/users/apapadop/PeLEETuples/PreSelection_Dublicate_Overlay9_Run{1,2,3}_v08_00_00_52.root

# root -b PeLEE_LFG_TwoDPlot.cpp

## Perform the fit and store the calibartion coefficients 
#root -b
#.L PeLEE_CreateSplines.cpp
#PeLEE_CreateSplines("Overlay9_Combined",true)

root -b PeLEE_ResoEffStudy.cpp

# locally
./PeLEE_Download2DRecoTruthPlots.sh

root -l PeLEE_script_DetVar_PreSelection.C

# NuWro Fake Data

root -l PeLEE_script_FakeData_PreSelection.C

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9NuWro_Combined_v08_00_00_52.root /uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9NuWro_Run{1,2,3}_v08_00_00_52.root

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreTruthSelection_Overlay9NuWro_Combined_v08_00_00_52.root /uboone/data/users/apapadop/PeLEETuples/PreTruthSelection_Overlay9NuWro_Run{1,2,3}_v08_00_00_52.root

hadd -f /uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9NuWro_Combined_v08_00_00_52_POT.root /uboone/data/users/apapadop/PeLEETuples/PreSelection_Overlay9NuWro_Run{1,2,3}_v08_00_00_52_POT.root


# ------------------------------------------------------- #


# GENIE v2 Fake Data

root -b PeLEE_script_GENIEv2_PreSelection.C

# GENIE v2 Truth Fake Data Studies

cd GENIEv2_Truth

# POT
root -b
.L pot_tree.C++
pot_tree().Loop()

# Merge truth info into one file 
root -b
.L particle_tree.C++
particle_tree().Loop()

# Isolate true CC1p0pi events (no reconstruction/detector effects)
root -b PeLEE_script_GENIEv2_PreTruthSelection.C

