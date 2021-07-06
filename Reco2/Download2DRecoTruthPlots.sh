. ../myClasses/Constants.sh

export OutPutDir=/uboone/data/users/$UserID/mySTVAnalysis/myPlots/$UBCode/

scp $UserID@$UBgpvm:$OutPutDir/*.pdf ./myPlots/$UBCode/
