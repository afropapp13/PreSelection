. ../myClasses/Constants.sh

export OutPutDir=/uboone/data/users/$UserID/mySTVAnalysis/myPlots/$UBCode/

scp $UserID@uboonegpvm05.fnal.gov:$OutPutDir/*.pdf ./myPlots/$UBCode/
