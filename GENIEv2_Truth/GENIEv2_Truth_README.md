
###########################################

# POT
root -l
.L pot_tree.C++
pot_tree().Loop()

# Merge truth info into one file 
root -l
.L particle_tree.C++
particle_tree().Loop()

# Isolate true CC1p0pi events (no reconstruction/detector effects)
root -l PeLEE_script_GENIEv2_PreTruthSelection.C
