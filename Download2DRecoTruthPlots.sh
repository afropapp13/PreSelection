
export UserID=apapadop

export UBCode=v08_00_00_43

export OutPutDir=/uboone/app/users/apapadop/uboonecode_v08_00_00_43/srcs/ubana/ubana/AnalysisCode/myPreSelection/myPlots/$UBCode

scp $UserID@uboonegpvm05.fnal.gov:$OutPutDir/*.pdf ./myPlots/$UBCode/

# End of the loop over the run numbers
