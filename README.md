###########################################

# preselection

root -b run_preselection.cxx

###########################################

# detector variations

root -b run_detvar_preselection.cxx

###########################################

# NuWro fake data

root -b run_fake_data_preselection.cxx

###########################################

./merge_files.sh

###########################################


