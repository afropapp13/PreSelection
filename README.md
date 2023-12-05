
###########################################

# preselection

export version=v08_00_00_70;

root -b run_preselection.cxx

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_BeamOn9_Combined_${version}.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_BeamOn9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_ExtBNB9_Combined_${version}.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_ExtBNB9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_Overlay9_Combined_${version}.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_OverlayDirt9_Combined_${version}.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_OverlayDirt9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreTruthSelection_Overlay9_Combined_${version}.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_Overlay9_Combined_${version}_POT.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_${version}_POT.root

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_OverlayDirt9_Combined_${version}_POT.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_OverlayDirt9_Run{1,2,3,4b,4c,4d,5}_${version}_POT.root

root -b run_detvar_preselection.cxx

# NuWro fake data preselection

root -b run_fake_data_preselection.cxx

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_Overlay9NuWro_Combined_${version}.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_Overlay9NuWro_Run{1,2,3}_${version}.root

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreTruthSelection_Overlay9NuWro_Combined_${version}.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreTruthSelection_Overlay9NuWro_Run{1,2,3}_${version}.root

hadd -f /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_Overlay9NuWro_Combined_${version}_POT.root /uboone/data/users/apapadop/PeLEETuples_3D_ECal/PreSelection_Overlay9NuWro_Run{1,2,3}_${version}_POT.root

