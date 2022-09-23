. ../myClasses/Constants.sh

export OutPutDir=/uboone/data/users/$UserID/mySTVAnalysis/myPlots/$SBNDCode/

scp $UserID@$UBgpvm:$OutPutDir/*.pdf ./myPlots/$SBNDCode/
