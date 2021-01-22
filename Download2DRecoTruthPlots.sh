. ../myClasses/Constants.sh

export OutPutDir=/uboone/data/users/$UserID/mySTVAnalysis/myPlots/$UBCode/

scp $UserID@$UBgpvm.fnal.gov:$OutPutDir/*.pdf ./myPlots/$UBCode/
