#!/bin/bash

#######################

root -b run_pot.cxx
root -b run_reco_preselection.cxx
root -b run_true_preselection.cxx
./merge_files.sh
