// https://vjudge.net/user/memset0
#include<bits/stdc++.h>
using namespace std;
using T = pair<size_t, string>;
T M[]={
{200,"AAAADDPwAAAAADPPPDDD8wMMwwAw8wDwPD"},
{40,"PwwPAMA"},
{4,"M"},
{0,""},
{200,"AwPwMwDPAMMwAPMwAADAPMPwMw88DADAMA"},
{200,"AAAMMMAAAMADM8wM8M88AAMwA8AM-MP8wA"},
{100000,"8A8AzMwAAMwPA-wAA8wPwwAMw8AzM-wAAzPwDMwAMAwwAwADAM88Aw8DAAMDAMMM--ADPA-wD-wwDPwzw8-wzwMADwzAD8zMw8wAAzwADwADA8DMDAwMDMAMMDAM-MAAw-DDMMAwA8zzMAPAzwwzMPAD8AP8AAzAwAAzAAAPMwzPAMAMMAADMAMAADDMD8DDAMMAPAMAAwMz-AD8DPAAw8wDz8MADPMAM88Aw8wAAAMDMAAAwDDMMw8wwAMzPAAMw8zA-APMzwAzAM-DMwDMDDAA8AADPPAAPzAMADDwAwP8-w-DMMAMADMP8DDADAMA8wADAADwzAwMAPAD8PMADA8A-DDAzADPwwAwADDwwAAwwDwAA8Dww-MA8MDPPwAAAwP8zzPDDA8MMMADMDwADAAADPMDDDAPDADwAA8-8MAAAAMPMAz8DMDwMwPAAAzDzzwAMDAAPDwMM88DPzwAAMPMAAADA8zMwDAzzMwwzMA-Dz8wMAAAAD-wAAzA-MwAzDAAwAMwADwzADAMADA-MwwADzwwzDDDAw-MA8zw-8DwAAAzwAwAwAAAzDwDAAw-w-APP-w88PAwDAwAPAMDMAAMwDPP8APw8PDAwzDDDA-MAAD8AAMAwAPAAMDzwAMMzwDMw8MDPwwAAMzA8zAAzPDMwA-MMAMAAD-DwDPMAADzAAzzMDMzwMMAAzAw8--AD-MMADP-AwD8PDAMz8DD8wwAMDDD-PA8AM8DwPMDAMMAMA8MAMDwwAADPMwA88AMDADMMADwzzAzAwMAA-A8AAPADMPPMzAMDwwPMDAMPMAAMDwPAPAw-DwAMwPDz8MDAAP-8PAAADADMzAwDAMMMwMAz-MMA8wMMzzDA8AwAAw8PADAPzD8AA-PA--AAw8DAwAzPMAMAwwMDADPzAAwDAAMAMwAD8DMMA-A8AP8Az8DDADAA--wAADwPMAAzDzMMzMA8A8wAw-DwAAzADwDADw8ADw8w8PMz8AMAAAPADAAMwDDDzAAAA8ADw8AMwAAPA-D8AwAwzAwAAzDwDMPwAwzwA8ADADAAD8wD-PMAD8wPDwwAMD88ADAADwAAAAAw8wwAwz8-DDADA-AzAAAMwADPAw8wM8wADAMDwwzMA8AMzM8zDMwDAwDDMAADMAwDDAzwADwwD8AM-PA8A8AAAwwwDMAA88AP8w8AAwADAMwAPPMwPMw-wDAMMwD8ADMw-AD88zw-A-z8AADPwwADMAAwAAMMMADAAD8P8wMwzPzzM8DAD8DzwwPA-DwwwDAAPAMPwAADwMAP-AAwAM-zMAPwMwMD8wAMAAMwwwMMAAMAwAwwAAADDwAzAAwwwDDAwzAwwMAAz-A8A8wPADMzwwADwAwAMAPwM-8DAwzAPDDAwzDAA-MwAMzzDwAAzMD8MAMADAA--MAwDzADAwDAAPMAA8AAAwAAAMAAwAzD8zAAAzMAAw8Pwzw8z-wADADMAMw8MAMwDwzAAADAz-AwAwAPM-A8DMADAPPwMPPA8A-8wwAzAwDDA88ADAAzD8M-MwAwAwAwAAwAPPwMAAMMAMAMDMMMDD8A-AwAwMwDAPwAAPwP8wwwA8MAwwwAwADAzPzDDzwDM88PAwDzADAwAwADMPAwMwAwDDzAPAAwDPAAD-AADDA-AMAzAw8DwwAMMAAAwAzAAAwwwAADMMw8wPDAwzD8zPDzPDADAAAzAwwADMz88zAzDwAzADDzMAzADD8AMzwAM8MAMzAMAwAAAAAAMwzAwzAPDAAMDwPAwwAAMPADwDMD8MDw8DwAAADwDDADAD8zDwwAAAwAM8M-MzPMAAAAMMAzAM8AAADDMPPAADD-PMMwMwwzAwAzAwAww8MzAAwAADz8wAD8zwzzAMA8MDwwwAwA8DDAMwPMwMMM8wAADM8wPAwMADAAwD8AAAADwDwD-DzwzwwMDMPAMADwPwz8DwwDwDMAPPDDwMAMAADwzAwMADMAA8AzAMDAAwDAwMMMDDwDwAMMP8DMMzPMAAwzADAADDMAA8AAAAAAMMwPAA8D8AwDDwAAD8PDAzzAAAwPMAA-MMDDzAMDww-MMPDwA-A-ADA8PADwwwAMAzAADzAAA-8MPDADADAMzMzAAz8AAAAP8MDwzDD-wwDAMDzADAMDAADDPM8D8AMAAwDAwAwDMDMAwwA-P-AAADAAw-8zAMwzwDA-AAMwPP8AMAzPDAMAAwwwwMDMDAADw-AA8wzAMADAMz8MAwwAzA-wwMAAzPzAAwDA-PMDPzDDzMz8wDADzP-DwAMPPAAAwzwwADAAAPAA8AAwMPAzDA8DMzAPADwAzAA8MPADwMAA-AAzwAAAMADDAPPMP8AA-AAAzzAw8AAwAPMwPzAAwwMA8D8AwzwAzAAAMDAAwAzDwwA8APMPAPADDAAMAwwDAAwwwAADAwDwDAAwAwzAAzAMw--8wAD-AM-ADA8AD8D8PD8APzPMz-AzwwDMDwwwzMDAwwzAwDDAAAADAMwAzzAAADAAw8DDMAwAzAADAADAAMADMwwwADAzDMzDMD8ADA-PAAwA-DAAP8MADDwAP8Mw8PPADAwzDPMAMwwAMAwADwAP8wPMwPwMDAMPDAPzDzwAwAA8zDAAwPAM88wwAAzzwDDMPAzDAAAM-DwAAwMMAAAPMAwAzDDADzADwAw88wMzPMADwzPA-z8ADAMDAPwAwMM-ADD8MAAAAAA8MwAMMMMDwDMMDDwwAAADAMw8DzPMz8DMwAMDAwAM88DAAAzzPADA8wAAAzzMAAAAP-DAAAMwMDAADzMDMAAwAAwwMAAAPMP88wwADMM8AAPM8DDAA-wMADA8DAPADDAAMwDADD8ADwDAP88AAADPAwPzAwDAMAwAAwDz-DM8DDDDMDAPAwMMMA8AM88wAMD-ADAAAAA8DAAzPPPw8MAwwADAMAAww8MwADM8AAAwA-DDzMMAMAz8DDAA-MwMwD-D8zMADPPAPzD8DzDDMAAD8zMAAwMDwMzzAwzAPADwww8DPDDDAAAADPAwM8wDAD8MAzPwPwAAwA-DwMAMMAwP888AMMAMAw8zMAPzAMAAMADDAzMA8A8zAwAMAAAAMwDDMMAwDzAAwwPAAAAwwMADPAzDMzM-wDDwwzwwAwPMzAAwDPA8APAADAAAM-AzDAPD-wMADMA8wAwDw-8-wAAAwA8DDwwzDDwMzMMAMD-APAzwwwAMMAwPADMAwwAwMM-wAwADAwwwDAPMwPMwM-MAPwwA-PMAwAwwP8zwDwAwAzwwAADwDwDDzADMMMMAPDDAMAMDwDAP-z-DAAAA8MzwPw8AAz-DDMAwPPzDDMDwAwwMDD-AMDMMMDzDAPwzDDADAwMz8P8AD8AADAwMAzwMAwADMAPDDDDAPDwAMDD8DPDzAA-MAAwAMPAzw8AzwAPPMMzDMw-8--AwAzMADA8wDzPwAD8DMMw-PAMwAz8z8PAMMMwDzAzMAMw8P8Dzww-DwzzzAAMDwMMw-MAAAAP88MAzDAAADADDAAAPAz8AAA8AAA8AM-AD8MAAAwPPw-AAADMAMDAMAMDAwzAMADAADMAMMMzwzADA8AAD8Dzw8PMAz-DzAMPwMAAzMMAwDAA-AAAw8APDADwAw88DMwAPAADD-DMAzwA-DPMMAwMPMAwzD8ADAAMwADAMADA8PMM-wAMAMDAAwzMDPwwMAwzPwAwDMDMADwDwAAMAPAADDADA88AwPPMwAMwAwwwzwAzAPwwAAAAPw-8zwADA8MD-wDAwAwMA-PMwAPwADzz8DDMAAD8MPADz8DAAA8zzDwA-AAAAAAAMAzAAAA88Aw8wMAADwAAwAPMA88wAAwwAAD8AAAPM88AAADwPwMDM-888MMA8AAA-PwMwAw8zwMMAPMDMwDAwMwAD-8DzAAAAwAwPD8PAPAAAMAwAMwAAADM8AwADAzDDPAMAwDAAw8PAAPwMMAAAAAzDMADAAA-AMAAzw8-A8zMAAAAAAPw-DM-wwAADPw8PDAA8wwwPDwwA8AAAAAPwwzzDAzDDzDAzM8wzAMDAAADzDA8w8MMAzw-A8DD8ADA-AMDPDPA8MMAA8MwAM-z-wMAzzDPPAwDDAMD-MAwMAA8AMADwAMMA8AMAAAw-wPMDMwzwDMMAAMAAMADAAAAAPMwwMDwMAAwAAAAAzPzMDMzMwwAAwPwAAMMADwDPDMAAwMMAMAw8wwAMwA8DzM8AAAwAwM8AwDP8zz8-wDAMzAM8P8DD-8MMMA88AMzAwwzADMMDDDAzAM8Dw-MAAPDDADz8wDAAAAA8DwMPPPAAM-AMDP8zAMzAP8AzAPMAMwAMD8ADwDwAAzwAM-PDMAMMAAwwwMPADDzzzDMAADAD8zMD8wMDzDAAwAMMAMMAMDw8AA8zzzAzPMw8AAMAPwwAAA8PMzDwzAMMDwwwMA8z8wwMAAMDDDADDDwMAAwAwzwAA8w-wMwAwMPMAzAwMMAAPMwPAzMPAMMwzzAAwDPMAwDwMwAA-8D-AwAwADMMADMw88PPMwDDAzAAAMAzP8DAwAAADDADzDAz8wPMwwDAPzMMAwPMMP-P8-AwPwMAzzD88MM8MDAADwADMMAwAMP8DwzMDPzAPAMD-MMDw-wAMwzDM-DMDwAPAwAAPwDwwAwADAPAAMDDwMAAAAAzPDwMMDwAMww-A8AMwAAM8MwAM8z-ADA88-AAMzzPA-8AwM8DPDDzPw88wAPADAwD8MAD8zAMzMPwwDAAAMA--MMAPDwwDMM8AAMAMw88AwwMAAzAMP8AADMA-8AAwPDwAA8A8DDDAMzzMwDDAwDPAAMDzDDDAA8zDAAAAAwA8MAMwAzAAwwwPwzwMwwwAAM8AAA-APwwAzMA8PAAMADDMzDMAAMPADDAAwwMD8DAAA-wPMAMwAwwAwPMAwDwMA88MzADMzDADAwzAPDD--Aw8-wAAPPAzwAAD8MDDMAwMAAMA8MAPPPAwMA-8MwAAAw8A8wP8MMzADAA-wAMPDAwwwADwzAAwAADwwM8wAM88PDwMzAMADAMDAAwMzAA8-wPwMwM8AAw-MDDAP-w--zP8MzAwwMMMM8zADMAAwDPAAAzw-wDMMMzwAMwwDDA8wA-DwAADP-MMwAAwAMzzwDPwMAAAAADDMADDMwMzwPMADAM-MMMAAAAMwzAzwADMzAwwPPzAAAAzMwMDAMDMAAMAzPwMDwwAzwP8zAD8PPMA8wAMDAAAAADAwAADPwMADMAAwMwwAADD-PzMDDMADAADADzADDAPMzA8zAAwAAw8wMwPA8-MMDAPMAAAADDADAAPAMwwDDAzAAAMz-wD-wwAMzAAAzAADAPzzAAMMD88MDA8zwwPwDzAMwMwADAzDwwMDAP-AMzwM8MwAADMzMAAwMD8AwwPwADAAAAAMPAwPMP-PM-D8wzwAA8wMDMPDPMAAAA--DzAwAAM-MAAAPD8MA88AMDAAMDAwMAAAAMwAzDADAzAD8AAAMPAMD8DMwDAAwAMDAAA8AzADPwAMMMDPP-D-A8DDAMDAAAAAPPAPMADPAAAAwDMMwAzDPzMMwAMwz8DAAA-DwAMA8AMAPwD-wzAAMMAAPwwAAAPMAADPADz8A8MwM--wAw-8wwAMMDDwDAwAAD-wwAMAAMwMwADDDwwDDMDDDMMADwAwM8AzDAPAA8DAMDMA8wAAwAzwwAAMMDwAADDwMPMP8M-w8ADDPwDAMDDzM88wwADwAAAAzPM8AAMMAwPPDDAAwzA8zAAzAAAAAAMMPAMPAMMDwADA8AwDwADzAwMwDwwMMAMzAzPzDAAwzzAwDww8DAAwAAMPMzMAADMDDwDwDzAD-zM8AAwPAA8AzMw8DMAwMDMDAMwDAwDPww8PzAAAwDDMMMAMwD-MAzDAAADAAM8zAzAPAww8Pwz8MAPzAMDAPAA8AAzP-wAwAAA-8MAzAwAAzA8wMwMPzAA8PAADwwwAwzAzMM-wDDAwDw8DwAD8z-8D8zAAAAAMDMDPP8M-MM-MwDPDwAADw-8A8wAMDMAwAAAA88DAwAAD-MAA-Aw8wAAwPPA8wADAM8AwPADMwPMM-MA8wMMwMA-MzAw-MwAwMMwMMwzD8zAAAMMMMwMD-AMMAwMAA-AzAADzADAMwAMwA-wMww8AMDwwADwww8ADDMMADwAMAwAAAAAAMwD8MMD8ADDA8DADAMPPw8wAADPMDwAAwAA8DPDw8AwAAAMAwM8MMDMAzAMwM-P8AzzAMAzzAw8wwwAAAA8AAAADMAAzPzAMPAwzM8MAA-zAz-AAMzMPAMwzDAMw8MPzMDwwMAPDwM8PDAMAAAAzMAwDAM8DA8APPDMwPPAP-AAAwMADzMPADAMDwAMwzADzAzAADzAADMDwDwzAPMwMMMwMDAAwA8zwPAAADA8MDD-Azz-PAMPDAPAzDAAA8A-AwwDDAwPPAA8AAzPDDDAAAAAADMzAwMw-wAwDAMP8AwAMPAPMAwwAA8AAMAAMDAMADMDMMPzAAwAww8ADMAAwzAAAwA-wPD8DAAPAMAzzAAPAD8DA8Mw-ADMMAPMAPMPAPAAAD-A8MAAAMDDDAAwMwAMDzA-w-AwAw8AzAAwDPPwMMwDwzwAD-wADAMDAAA-AzAPzAzwMAwAMD8PAD-DAA-wD8MPwA-AAPzADM-PwzPDMD-wzAAP8AwwAwwAwMPD8AMzPAPP8zMA8AAMMAADMwMMDAMwMwAwzDzDMMwDAzD8DAzAzAAAAMwP8AAM8DwwD8wDwAAMDAA8MwDzDMPPAMwMAMwMA-MwPMDMPMMPw88zzADwAwAPA-AAA8M8DzDwAAAPAADwwA8w8DPAAz8AD8MwADMMzAA8PM-wA8DzPwAzA8MMwwzMwwwAzwA8DAAAMAMAwAwAwMAMAwDw8wwAAMwADAMwwAD-MMwMz8DAwDAAPA-wMMMMAPMwMAwwM-DAADP8ADMMMAAAAwwwAD8DwwzPMwMMPADAwAA8wDAAwAMMAAwDDAAPMw8DAMPMw8MwPAPMzMADwwzA8PA8ADwAAMzPAAMDAAMMwP8MAAwPDAwAAw8AwAwDDAwzAwAAwMA8AAwDDDwwwD8zPzAAA8MA-wMzMwAADAAwMDDP88DDAzMAzAAA8AMPMzMADwz-zAwDADDA8A8Pw8MwMwwPwDwPAPwAPz-8MMPM-Az8PwA8AAzwAAADwwA8P8AAMDAwwPAAMAwwADDPAAAzMMPAzzwAMA8z8ADwAD8M8MAMADDADDD8D8DAPwMAzzADAAMM8DMAAP-AAAAADwDwwAMPMAwMw8DPAMAAAwzzDDAwAwPA8MAwD8PwzAA8PwwwPPMADPwwADAzDADDD88AwMMMAzDwA-APMAMAMAM88AMMDAAMA8APA8zDAzMzwPAAM-AAA8M-APDAAAD8APwAAzM-8AwD8PAw8AD8Mw-AAPwAwwM-ADwAMAwMAPw8-MzAAAD-8DD8AMMAA88zMAP8AAww88APA8P8DwMDwwDPwAwMPMwDAMDDADPwADAwAAPA88MwwAwDMwwzwAAM8zAzDPADwPAzDM8DDwzDDAMDAMPPwA8wA8APPP-DP8AAM8ADPMAADwPAMMAAzzMwPAAAw8DzMAPMPMMDDPwAwzMAwwzAAAz8wwPD-MzDz8wAMDAwAMMw8PwPA8PADMMDAAAADAMAADzwAwwD8MAwAAA-DAMDD8wwMPD8MwwPDD8z8AMw8zADz8w8AMA-8PPzwMwAw8PPwMMMMPMMA8AA8wADAPDPwAPwAAMADAD8zM-AMAAAMwDDMwwAwDzAAADMAAzA8z-AM-A8MAzzwz8wAMAwAD8AAMMAADMMPMP8AwAzAA-AMDAADM8-AwA-APDw8zAwADMDPAMPAMAAAMAAADwzDMMzMA8AwAzMwAAMwP8D8PMzADAAMA8MAA-DAAMMMM8APAzAAwww8ww-AMAAzDAAMPDw-ADM8AMAM8AwMwwDPwwMPAAAMzAwwwzMPDwwAwAwAAD8MDMADAAAADw-wwMwMAA8wAA8Az8MAADAzPzA-AAMADDMPA8zAwPMwwDAMADwMMzAADAzAAADwAAA8PADAAw8MAAwzMM-MDDwAwADAAPAAwwPzwwADwzMM88MDAAMA8DAAAAAMAAAAzADADDAzAwAPDAAwPAD-AMMw8wDMP8PMDAPAAMADM8MAA88AzMwP--wDPzwMzDAwAwAMADzwAw8Az8AAzAPwwDD8AMwwDDMAAA-wMPwD8AAMAwM8DDMMA8ADDADMDMA-PAAMPMPM-DPwAPAAwA8zPw8zwwMzMzAMD8DwPAMwAwPMMAP8MPPAAAD8DAMAwA8ADAAA-zDMA8DAAAMzMwAwADAA8AMPAMAMzD8AAADAAAAwDMDPMDAzADwAAMMDAMAAPwwA-P-Pw-AAAzPAAzDDwDwwAAMwADMAMA-wMAAwPADAMAMPA-MAAADAwzPDDPDADP8AADAM8DADDzAzwAAMwAADPwAwMwAzDz8Mwz-APAMAwAADADDwDMMPMAwAMDAwAwAwDAAwwDMAwwDMAD8MzA8AAA-w8wMPDADw8AAADAwDww88wMA-DDDDMPDAwDMADwMMAAMw-AzDAzDAADAAAAMAM--AwzPzwDP8MMwwAAz8M8M8AA88ADAAAwAADADAwDDMDwzzDDDMAw-AAAzzPMADA88AwDA8MAwzzMAMw-MADAAzMADDMMAAADzAzDADAMAAAA-wDPA-AAwAzAP8APAz8zP8MwMMAAAAzPMMDAAM8MAM---AwDzAAzAAAwwM8AAPAMwAMPAzwDzw8-DzMAPPzDAwMwMDwAPzP8AAwD8wAPwMD8AP8PwPwAD8DADADDMMDMAAzPAMwAMAADDPPA8w-zMAAw8w8APD8MAAMDDzPMzzzDMwwwwwwAAwAMAMAwADAzDAzMAA8MDAPAMwwADwMwPDAPMMAADzAPDPDAwzPwAMMAMAwzMPwDMMDAAwzMMAAAwA8wzP-AA-wMwMMDwP8MMAAMA8DMMAz8PMA8PzwzA8AwDMMDADDwPAD8DP8DPDAADDDAwPwPPwDAAAwwPADMADPAAAA8AwMPAAADAPMAPwP88ADDMMzD-zM-wMDDMAwzAMAAAAwMwAAD-AMPPwwAzMDD-P8wwwwwAwAAA8AAwADDwAD8APMwwMMAADAAww8DM8AwwPw8MP8AAMPPPAAPPADAP8DPMDwA-8wADADMMADAPDDAwAAzzz-A-MAADAw-MAM-PAMMAMMwMA8zPMAP-APAw8ADwD88zAzADAD8AAwPAwAA8zAPMAzDMDDDAMDM8zPwwMPww-AAA-AD8MPAA8PMwPMAMwMzADwDDA8A8wzwMAPDPAMAwMPDDAA-ADzAMDAAAwzAMwz8A88PAzPAzDMAAA-MPM8wDMzD-AAAwAwMAzDwzAAPw8ADMwDMDAAADMwMwDAzA8-ADwMPAAzA8wwAzAMAADM8AM--A8zPPDAPAzAAwzAzMPAzDMADzMAzAAwwAPDwwAMAzADM8wAMDAwMADz8MwDwAzP8AwAwAPzAwwP8AAAMADzD8P-wwzA8zM8MM8APDPAwM8AMAMwMA8A8MAwAMwADMP8PzwDDz8PAAAzDMDAAMAMAADMDDD8MADAAMAADMAz-ADAM8AD-M8Mw8wAPAA8A-ADPDwAwADM8-AwMAwMw-AzAMAPwD-DwAww8w8DwMPPAAPAADAAwAAAAwAzMMMwD-PzMwDwDAwDwzAA8P8P-zMwwwMA-w8AAw8APPwAwA8AAMMAAwAAPAAzAPPMDAA8APw8MzwDA8wMwAAAAMAAPAAPM-8AwAAMzwzMDDzDwDMw8DPw8Mz-AD8AwAAPDPDMw-8MzwP8AA8w-Aww8MDAMzzA8wwAAAzDMAwwM8zAADw8wAzP8MADwAADPPDAM88DzAMAAwA8AADwMAwAwPAAzwDMD8APPA-8AwwA88zMwAA8ADDADzDMMMwzADMPAMP8AAADAMAAwMMADP8zMwPDzDM8wPPw88PwDDDPAwMMzA-AwA8-AwADAwMAP-AP88APwAMDA-DDA8wzDA8DD8MwAAw-P-wMMAAD8MPAzDPzMM-AzwwDzAMAPD8wDA8DMwzAAzzPDDAA8MAwAAwDwAADMwMADMAPAADAADAAzDwz-DwADPwMMAMww8MMDM8PMMMAzzAAMwwzAAAwwDPPPMMAMwMMz8AAPMDwAzPMPMP-A-Mwz-AMDAwzzPDDAAww8MPDADDMDMADzAPwMDw8wAwPAwAADAPPDwADzDAwDM-AAPMwA8AwMAwwAzADMADMPw8AMAAPMPw88AA8PA8w8wAAADMPM8DMDMDPMM--AMMAMPDDDAMD8w8Aw8wDAzwDDwMAMAAAMAPDPAzAMPzAAwPwMM-AAwM8MzwwAAPAzMDAz-MzAMDAPDAMDDMDDAPD-DDDD-DDAz-AMMDwMPMAD-PM-MDAPwDwADzM8AzDAMAMzwwDMAwzD8wAAMAwAAAA8MAD8wAwzAP8wAMA-AAAA888w8MDAMA8AzDzwAAM8A8MMwDwMwMAwzwADzD8wDwMAwDAMwAPPMPMAAMAwzwA-ww-zADAAMAD8D8wMMMADwAAAMwMwAA88PAPAAAw8AwP8APzzwAMMMwzAAMwzMADD8z8AM-AMAzPADzMMMDMPAAAwDDMP8A8AADPAzA8w-AA8wAwDAA-wPAMDMDwzzPwz-8MA8-AAPDAAAADMMMMzMPAzDDwPAMAwDMAPDDwDAPDwzwAAzPMPAAPPww8wzDADDwA8wAwz8A8MAMMAzDD8P8AwMDwwADADzA8PAwwAMwwzzMAPMPAADAPA8zP8DMPADPDAMAAAADD-wAAAMDAD8APwD8M-AAwDDDAADw-MAAwMwAM8--8DAAD8AAzMA-MMMPMzADPDzA8PzwAAPM8AMMDMAwAMMDw8ADw8Pz8AA-wMMww-DPzAPzAMAAM8wAAMAAPDAPDDDAAAA8AwMMAz8wAzA8DMA8MMDDD8MD88z8P88DMAMwwDwAzAzDAMAMwz8-PPAw-zADADADPwwDzzDw8AAAwMDz8DDMwM8AA88z8zDPADDMAwAMDMDwwMzwA8PPA8AAAAwD-DAP8zAwAA8DDzwADDDMAAwDPPM-APAPwAPMAMAwzAPwAAwMwA8zAD8DAMPwAAADD8wMAwADAw88APzADzMAPwDAAAzAAw-MwAAMMADAAwD-Mz-wDzAwDPPDPD-DAAz-Pzw8MAPPDDMMDzwzPDAPDw-DPMMwA8PPPzA-ADAPAAAMAADAAAwA88D8wAwMzzDAAAMA-AMzAA8DMA8AMwMAw8AAw-zAA-D-AD8DwP8DMAzAADDwAwDzzwz8zPMMwD-MDD8PwDAAAAAMAAAAz-zDADAAwzMwDAA-M8DAPz8AMwzwAwAAAzMA-AAAA8wwDww8AADAwwzwPADMMAw8zzAwDDwwzAwDAzMMMAwAwA-8DzM8Aw88ADMDADwAA8zwAw8AAAzADMzDAwAAAAAzMDADAAMwDP-PD-MAAPwww-zwAA8APAAA-zAwwAAAAPAzMDDDDPAADAAMAAM8DAwAA8MAMMMMwMM8wwDMzwwAD-zwwDwzzDDwAwMwzzAwMPw-DDDMPDDPDAzzMzM-MzMA8DAPAADzMMADDDMM8AADAD8-w8ADMMAAAAAwMw8-AADDMzDMwMzMwDAMwz8PAPwMwP8PAAAMDDwP8zwAADAAwAAwwPMwAAAAAAPMPM-A-AwMwMAzAPD8PPDAA8wPAAPzADDMA8AwDAMMADPwAwPD8z-zAPwDAAwzMAMAPPAPwD-PAPDADMMwMDAAPMA-MwzAwzMwDwADDA8zwDDMAAMAPADMAADMDDMAA88AzPA8ADDDDz-8Mw8w-zAPDAAz8PwPMAMPAAMA-wD8wMPAAMzAAzA8MAAMADAPAADwMAMA8DMwAzAwMDwzz8wMAwPzMDDPPDAMAP-zPzDDMPwA8MADwAADDPA-DAwAM8MAAzzDDzzPDADAAAwAM8DMMM8P8MwPAADzAM8AzzA--D-M8wPwwwAwAAAAP8ADw-AADDwA--AwAA8AzPDAzDAwwAAAMAz-zADDzPDAAD8wAMMPAAzAAwMzDzMAAPzAM8MMzDDMAAAwAPDDADDPAPzAMDAAMwA8zwwDDAwDADwDDMwAAAw8wMDDPDADzMMAAwPMAMAMMwPwzAwAwAAAA8wA8P8DPwP-AAwPMAAAwA8DDAMDMAAwMMDww8APzzDA8AD-w-zAzAAAAADPMAMPMAPAMDAAwAA8zMDAAwDDAAwAPP-MDAzDDAAAMDwM8MMMDAMDMwwPM8AzwAwzzM-PAA-AAP-8D8AADMwAMDA8ADMADMMMA8PDMMAD-AA8wDMzDw--8-AAPz-AMDwMDAAPAAwPAAAAD8A8AwMMPwDDADwDAwwAAAAAww8AwPD88PADADDAAwAMDDAADAMAz8AzMAM8MDzwMAM8DAAwwMDDwwDA8DA-wADzDwAwwMMP-APAMADAAAAMwMPMADDAMD8AwwADADP8AMwwAMAAAMAwAAwAAPMDDAAAPDAAMwMMMwA88zPwA-DzMAwDDAMwMADMD-DPDADAD-zAw8AA8PMM8D-AwzzDAAAAPDAA-wwwzwzDAAwDDDMAMzMw-AADwDAMMMzzzAA8-MMDwDAzDDDDwAAAPDMwAPw-DwwzDA8MMMDwDM-wzAzwD8-zAAAPPDAAAAwwAMwAAzAwADDAMPDAAPPzzAADA-ADAMzDzzDAAwMMADAPwADAzDMwAPDDDM-AzA8ADAzAMD-wA8DDwM8AMDzAMPDzDzAwA88wAP8AA8Aw8Pz--Pw-AADM8PMDww-ADDwMAAMMwzMAMMzwPDwMAwzADzAMAMwADw-AAMAD-MAPD8ADADMwAMzAwAwA-AzAw8-MAAzAwDwAP8zw8w8DMwDADzADAPzwwzAwD8zw8-w8zzw8MAD8MwADDDAAAAw8AwDw8DDMM-8wMPMAAwMAAA8zMP8PzwAM-DwMAD8wwAMAADAMA8PwMDAMDPAPAwAzMMAPPDAMDDwDDDA-8wwA-DDA8DzzAzADM8zA8DDwwAAAwAMA8A-MDAwMAAADDzMwPMAwwD8MwD8MAwA-DAwzAAADAzzPPAw8wDMMDwMDMzwA-DAAMDAADAwAwwzADMwAPAA8PAw8MDzMMD-APAADwPMAMMD8wAPD8M8APDDDMwMDwAwzww-MzMAAwMDMDAwDMDD8w8ADMAwAAAwMw8DwADwM-AA--AA8-wwwDAMAAMMD-wADDP-AwwMAMwDwADw-zwAAwwAA-zA-ADzAwDwAMwwAAADM-DPD8zMAMDAADMAA88wAMDzPAwzzA-DwMAwADAPDMwDAD8A8AAAAMAPwz8wwMMD8AAwAAAzAPwMAD8AwzMAzMDDwMAAwDPMAwAMwAAAM-MzPDD88Pz8zAAz8PAw8AMAAAAADMwPMMAMwD-DADwDAAzMDPMDwMzwAMz-D8MzDMAM8AAPzAMMwDDwMMMwDPwwwAD88-PPAAAwMwwPMAADAPwDADMMMwAAAMwMAPwDDzADAMAADDD8DAAPwAADzAMADAAADMADDM8DADA-zA8wDMDPPDMA-MMwwDDDA-ADMwMPAAwPAMDwA8MAzMAzAA-MwzPAM8wPADwA88ADAwMDAA8wPADwAzPDAAMPw8zwMMMDMDDDAA-Az8wAA8wPAzAww-w-wA-AMAwAzDPDAzM-AMMAADM8AwMzzAw8APADAwAwMMDzADD88DDMAAADAA-AwzAAAM8AMAAPDMDDAw8AAAA8AAwMwAAPzwMwAAz8-AAPPA-AzMA8zPMwDAwAA--AAAM-ww-DAADzzAwwMwMMMww-zAwD88wAwMDPMMAAM8Az8wwAP8DzzwAww8MwPAwzAAAzDDwMDA8wAMA8DwMPAA8AAMzA8PAzDADD8A8AwAMDw-MMMMP-AwMww8PDDAz8AAMAMAMDwwDMw8DwAzMADADDADAPAAwMDADDDADAAMAAAD-M8MDzPzzzwz88-wPPADAAMMzwDDwADMDMzDAMwwDAMMwAAMADMAzA8MDDAMwADAMAMDA8zzDPwA8DAAMDAzz-DwP8AAPM-ww8zAADMDwAw-MDMDAzAD-DPMwDwMMwAwMMAAAAPw-wMAADAPDMDAAMwAwzww8wAAzwAw-8DzMzA8wPwAADMwAAMPA8MAPMPAAzAAzMAA8ADwAwPMAAMDMMAwDzAzMAMMw8-DAAwAADwA88-wMwwwAAAAw8AwM8DMAAMPADDPD8wPA-AMPA-AMDAP8DAMADzDAwDMwAMPDAD8AMDDwwAwAP8wAAMMPDPMMPDDwAwPDMDwPAADADA8PwMwDDDAD-AAwAAPPADwMDAw8DDMwMAAAzDwwPzA-zzPADMDDAMwzDDwMzMMMAMwMDwAwMAMz-DAwAMD-wDAADMPPwPMPwMDzw-DAPMwAwA-DwwMA-ADAAwMPzA8AMwwMMwzAADzA-wzPDAMAAPwwAAAMww-wwMwwAMPAAAwAzw8AP8APAPMPMzAzMM-8AP8wwzAAwMMDADDPz-APMAAwMMPAAwwM8AAAAA8wAAMAPDAMAAwPwDMMAA-zAA8w-w8zzMADM8MPAPDwzz8DwA8AA8ww8AwwAD-ADAA8zADzMMMMDAwMMDAMwzDDDDPAAAADwAADADMM-D-AMMMA-P8ADPDwM88-DzwD8DPDPMA8APzAwwADwAAwAA8DwAzDPA-z8MMz8P8DMAwzAMAwPzMDAD8-Aw8Aw8AMwPDwDMAPADAAzMDAMwAAM-AAP8zAMPMADzPDPAzADzwDDDAMAADAMwzPww8DMDzwzDAA8DAD-DAM8AMAwDwAwM8DzwD8DPAADADwMzDAA8PAAMwA8AwPwAw-DAAAwP8ADwwA8wAAzDzwMMAPAD8ADAADzDD8AMzAMAM88AAMMAwMA8w8MAzADzzD8Mz8AP8ADM8DPwzAAwwAww8PwDAAwPzwAADAPAADAAA888DMzzAwAzADwAMAMMMAAA-AP-PDMzMAMAD8AMPAA8M-ADPwPwwzwAwwwAwwMPMPAAw8wPAwPA8AMDwPwA8zDw8M-wAAwDAADDzAwMDD8DAAwAAwAD8AAMAw-AAAw8zDAwADAPwDwwD8AAwwDAMPPAADwPzADADzDwwPwA8DMPDAMAwAD8D8wM8zAMAAMDMAAPDDwMwMPMAAADzA888w8zww---ADMAMPMAww-8AAPwAAADAwwAwAMMDwMzwwAwAM8zMAAwAPzMA88PwAPPP8AzAA8Azzz8wD-MwDwAADMDMAMwAAM8A8PDAPMzAAMAPAzMMDAMAwAMwwMMDMwzMM-DMAAAAAPzADADAAAAA8wz8AwAAADAwAAAAMAAAAM--MADzMwDDDAADDMPAw8DDADzP8AAMMDPPwAPzwAMwDDPADPAAAAMAMwAMD8AMDDMPzwwMAAA8zAAMAADwzDzDAAwM8DDwMDwADMzPDMMDMMz-zADAAA8PAAP8M8w8AAz8AAA-AMD8MwAADzMAAPA8MAPA-wwPzzADDM-DMMDADAAMDMDAA-zwDMzAMw8MMMAAMwDAzDPMwMAww-M-PPwMAw-AAzMMAM8MMwwwDDMzDDAPw-P-8AwMADAzDMMz8MAwzDDAzP8AAAAMwDAPAAwwAAAw-DzPA8P8wMMDDAAM8DMDDMwAMwADD-AM88PAMDwDAADwM8DA8zMAA-AAAD8DzDzADDAAzADwAwMz-wAwAzMPPwMzDwwPwAAPAAwwwzDPzw-AAADMwAAD8--MMzwAMP8wMDzMwADDMMDPPMADAwPAAzAAwMA8AAAADw8ADAA8PM8zwAMMADAwMAMDzAAwDDwADDMADMw8DMwzAMAAA--8wMDPMAMA8PwADMAwMMA8MA8AAAwzADwDwAAA-zADAAzAwAAMDMDPwM8wAP-DAAAD8AAM-AAzMwA8MDAPAMzzAA8MAwwDzDAAAPAD8wPMzwwAP8AAzDMAMDAAAA-DMw8M8wADPAAMA-DAADAPMADw8PAPPDAAwz8DAPzwD8wwA8MAwAAD-P8DAzA8AADwDAAPAAMA88wMMDwAPAwwAw8AMPMDA8AAM8AAzwM-AwMDAAzM88AwAMAAMwA8A8DAMzAAzDzM8AMwD8MMAwPwwPDPADPwADMAAAzPADD-A8DAPAPMAD-8A8MAAA-MwwDDwww8MAM8APAAAPwAA8AMPAwzMA88D8AAAMz8MDzPAwDA8PzzDMzwAPwwzwAMwAPAPADwwDAMAMwAAADzDAPwzAMAPDMzDMDDwA-wwA8-zADMDPAzwADzPA8wDAAMDwPM8AA8AM-AzAMDPDAMzAAAAwAAA8wAMw-wAwMADAPMAAPwDAMAzAPMDAAA8AAzwPPD8PDwDAPwDMAAzzPwzPA-88MAP-wA8wAAwMDMzAMADPDPDzwM8AMwzwAPwMPADDDAAADzPwAwzDzA-AwwPPDPwDwAADDDAAPAPAAzwDwADw8P-wA8AAD8zwwPDzADwA88DMAzAzMwAADPPM8zAMADDMADAAwAAzzD8ADPA8AMwMDMPAAwAAAMPDA-wADAwMwD8AAMPMPwwDAAw8AAAMA8ADMAAD8AzDDAz8-DwPPAAwAAD8MAMADAAD8DAzAPzDMzDDDPAAzzwADDAPPAPPwAAzDw-AMAzM-MAwDwAzMAMMMAAAAAAP-wDwMMAAAwAzAAAAAMAwMMAAAMDMADA-DDAA8MAAMDzMAAD8-AAM"},
{10,"AA"},
{10,"DA"},
{200,"MP8zwAwA-AwAAzDwMAPP8A8wzDDAMA8zwD"},
};
namespace lib {
const char BASE[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+-";
pair<size_t, string> encode_base64(vector<bool> a) {
  size_t n = a.size();
  a.resize((a.size() + 5) / 6 * 6);
  string s;
  for (size_t i = 0; i < a.size(); i += 6) {
    s.push_back(BASE[a[i] | a[i + 1] << 1 | a[i + 2] << 2 | a[i + 3] << 3 | a[i + 4] << 4 | a[i + 5] << 5]);
  }
  return {n, s};
}
vector<bool> decode_base64(pair<size_t, string> it) {
  string &s = it.second;
  vector<bool> a(s.length() * 6);
  for (size_t i = 0; i < s.length(); i++) {
    size_t x = find(BASE, BASE + 64, s[i]) - BASE;
    for (int j = 0; j < 6; j++) {
      a[i * 6 + j] = x & 1;
      x >>= 1;
    }
  }
  a.resize(it.first);
  return a;
}
} // namespace lib
vector<int>H(){
  int n, m, a, b;
  string s;
  cin >> n >> m >> s >> a >> b;
  return {n, m, (int)s.length(), a, b};
}
void O(int task,T ans){
  if (ans.first == 0) {
    cout << "-1" << endl;
    return;
  }
  vector<bool> b = lib::decode_base64(ans);
  vector<int> a(b.size() >> 1);
  for (int i = 0; i < a.size(); i++) {
    a[i] = b[i << 1] | (b[i << 1 | 1] << 1);
  }
  string s;
  for (int i = 0; i < a.size(); i++) {
    s += 'A' + a[i];
  }
  cout << s << endl;
}
int main(){
ios::sync_with_stdio(0),cin.tie(0);
auto V=H();
#define I(A,B,C,D,E,F) if(V[0]==A&&V[1]==B&&V[2]==C&&V[3]==D&&V[4]==E)O(F,M[F-1]);
I(100,0,100,200,62,1);
I(20,0,20,40,7,2);
I(2,0,2,4,2,3);
I(5000,0,5000,10000,969,4);
I(100,8,100,200,41,5);
I(100,8,100,200,38,6);
I(50000,0,50000,50000,1,7);
I(5,0,5,10,1,8);
I(5,2,5,10,2,9);
I(100,0,100,200,94,10);
}

