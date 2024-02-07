#!/bin/bash

#######################

export version=v08_00_00_70;
export path_in=/uboone/data/users/apapadop/PeLEETuples_Atmospherics/;

# CV files

hadd -f ${path_in}/PreSelection_BeamOn9_Combined_${version}.root ${path_in}/PreSelection_BeamOn9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f ${path_in}/PreSelection_ExtBNB9_Combined_${version}.root ${path_in}/PreSelection_ExtBNB9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f ${path_in}/PreSelection_Overlay9_Combined_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f ${path_in}/PreSelection_OverlayDirt9_Combined_${version}.root ${path_in}/PreSelection_OverlayDirt9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_${version}.root

hadd -f ${path_in}/PreSelection_Overlay9_Combined_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_${version}_POT.root

hadd -f ${path_in}/PreSelection_OverlayDirt9_Combined_${version}_POT.root ${path_in}/PreSelection_OverlayDirt9_Run{1,2,3,4b,4c,4d,5}_${version}_POT.root

######################

# Detector variations

# CV
hadd -f ${path_in}/PreSelection_Overlay9_Combined_CV_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_CV_${version}.root
hadd -f ${path_in}/PreSelection_Overlay9_Combined_CV_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_CV_${version}_POT.root
hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_CV_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_CV_${version}.root

# CV extra
hadd -f ${path_in}/PreSelection_Overlay9_Combined_CVExtra_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_CV_${version}.root
hadd -f ${path_in}/PreSelection_Overlay9_Combined_CVExtra_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_CV_${version}_POT.root
hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_CVExtra_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_CVExtra_${version}.root

# LYDown
hadd -f ${path_in}/PreSelection_Overlay9_Combined_LYDown_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_LYDown_${version}.root
hadd -f ${path_in}/PreSelection_Overlay9_Combined_LYDown_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_LYDown_${version}_POT.root
hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_LYDown_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_LYDown_${version}.root

# LYRayleigh
hadd -f ${path_in}/PreSelection_Overlay9_Combined_LYRayleigh_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_LYRayleigh_${version}.root
hadd -f ${path_in}/PreSelection_Overlay9_Combined_LYRayleigh_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_LYRayleigh_${version}_POT.root
hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_LYRayleigh_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_LYRayleigh_${version}.root

# LYAttenuation
hadd -f ${path_in}/PreSelection_Overlay9_Combined_LYAttenuation_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_LYAttenuation_${version}.root
hadd -f ${path_in}/PreSelection_Overlay9_Combined_LYAttenuation_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_LYAttenuation_${version}_POT.root
hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_LYAttenuation_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_LYAttenuation_${version}.root

# SCE
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_SCE_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_SCE_${version}.root
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_SCE_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_SCE_${version}_POT.root
#hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_SCE_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_SCE_${version}.root

# Recombinations2
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_Recombination2_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_Recombination2_${version}.root
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_Recombination2_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_Recombination2_${version}_POT.root
#hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_Recombination2_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_Recombination2_${version}.root

# X
hadd -f ${path_in}/PreSelection_Overlay9_Combined_X_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_X_${version}.root
hadd -f ${path_in}/PreSelection_Overlay9_Combined_X_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_X_${version}_POT.root
hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_X_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_X_${version}.root

# YZ
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_YZ_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_YZ_${version}.root
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_YZ_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_YZ_${version}_POT.root
#hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_YZ_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_YZ_${version}.root

## ThetaXZ
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_ThetaXZ_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_ThetaXZ_${version}.root
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_ThetaXZ_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_ThetaXZ_${version}_POT.root
#hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_ThetaXZ_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_ThetaXZ_${version}.root

# ThetaYZ
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_ThetaYZ_${version}.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_ThetaYZ_${version}.root
#hadd -f ${path_in}/PreSelection_Overlay9_Combined_ThetaYZ_${version}_POT.root ${path_in}/PreSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_ThetaYZ_${version}_POT.root
#hadd -f ${path_in}/PreTruthSelection_Overlay9_Combined_ThetaYZ_${version}.root ${path_in}/PreTruthSelection_Overlay9_Run{1,2,3,4b,4c,4d,5}_ThetaYZ_${version}.root

######################

# NuWro files

hadd -f ${path_in}/PreSelection_Overlay9NuWro_Combined_${version}.root ${path_in}/PreSelection_Overlay9NuWro_Run{1,2,3,4b,4c,4d}_${version}.root
hadd -f ${path_in}/PreTruthSelection_Overlay9NuWro_Combined_${version}.root ${path_in}/PreTruthSelection_Overlay9NuWro_Run{1,2,3,4b,4c,4d}_${version}.root
hadd -f ${path_in}/PreSelection_Overlay9NuWro_Combined_${version}_POT.root ${path_in}/PreSelection_Overlay9NuWro_Run{1,2,3,4b,4c,4d}_${version}_POT.root

######################


