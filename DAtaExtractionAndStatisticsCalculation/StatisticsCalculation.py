import ExtraccionDeDatosSergio as Extraction
from ExtraccionDeDatosSergio import PositiveSlopeDef as PositiveSlopeDef
from ExtraccionDeDatosSergio import TimeAboveLiquidsDef as TimeAboveLiquidsDef
from ExtraccionDeDatosSergio import PeakTemperatureDef as PeakTemperatureeDef


DocMessage = open("OutPuts.txt")
message = DocMessage.read()
conclutions = message[0:]
cont = 0
cont1 = 0
while cont < len(conclutions):
    if conclutions[cont] == "0":
        break
    elif conclutions[cont] == "1":
        cont1 += 1
    cont += 1
if cont1 == 3:
    print("Lets continue")
else:
    print("Impossible to calculate. Try to generate the data again.")


SolderPaste1 = "Indium 8.9E Lead free"
SolderPaste2 = "Indium 5.8LS Lead free"
SolderPaste3 = "Senju M40-LS720V-Hf"
SolderPaste4 = "Alpha OM 338 PT"
SolderPaste5 = "Indium SMQ98H (Sn63Pb37)"

MinRS = 0  # MinimumRiseSlope
MaxRS = 0 # MaximumRiseSlope
MinTAL = 0 # MinimumTimeAboveLiquids
MaxTAL = 0 # MaximumTimeAboveLiquids
MinPT = 0 # MinimumPeakTemperature
MaxPT = 0 # MaximumPeakTemperature
TALObj = 0 # TimeAboveLiquidsObjective
PTObj = 0 # PeakTemperatureObjective
UPCLRS = 0 # UpperPreControlLimitRiseSlope
LPCLRS = 0 # LowerPreControlLimitRiseSlope
UPCLTAL = 0 #UpperPrecontrolLimitTimeAboveLiquids
LPCLTAL = 0 #LowerPreControlLimitTimeAboveLiquids
UPCLPT = 0 # UpperPreControlLimitPeakTemperature
LPCLPT = 0 # LowerPreControlLimitPeakTemperature

UserElection = input("Please provide the solder paste you are using: ")

while True:
    if UserElection == SolderPaste1 or UserElection == SolderPaste2:
        MinRS = 0.5
        MaxRS = 2.5
        MinTAL = 30.00
        MaxTAL = 100.00
        MinPT = 230.00
        MaxPT = 262.00
        TALObj = 65.00
        PTObj = 245.00
        UPCLRS = (((MaxRS - MinRS)/4)*3) + MinRS
        LPCLRS = ((MaxRS - MinRS)/4) + MinRS
        UPCLTAL = (((MaxTAL - MinTAL)/4)*3) + MinTAL
        LPCLTAL = ((MaxTAL - MinTAL)/4) + MinTAL
        UPCLPT = (((MaxPT - MinPT)/4)*3) + MinPT
        LPCLPT = ((MaxPT - MinPT)/4) + MinPT
        break
    elif UserElection == SolderPaste3:
        MinRS = 0.8
        MaxRS = 1.5
        MinTAL = 30.00
        MaxTAL = 90.00
        MinPT = 232.00
        MaxPT = 255.00
        TALObj = 60.00
        PTObj = 245.00
        UPCLRS = (((MaxRS - MinRS)/4)*3) + MinRS
        LPCLRS = ((MaxRS - MinRS)/4) + MinRS
        UPCLTAL = (((MaxTAL - MinTAL)/4)*3) + MinTAL
        LPCLTAL = ((MaxTAL - MinTAL)/4) + MinTAL
        UPCLPT = (((MaxPT - MinPT)/4)*3) + MinPT
        LPCLPT = ((MaxPT - MinPT)/4) + MinPT
        break
    elif UserElection == SolderPaste4:
        MinRS = 0.8
        MaxRS = 1.5
        MinTAL = 30.00
        MaxTAL = 90.00
        MinPT = 230.00
        MaxPT = 250.00
        TALObj = 65.00
        PTObj = 240.00
        UPCLRS = (((MaxRS - MinRS)/4)*3) + MinRS
        LPCLRS = ((MaxRS - MinRS)/4) + MinRS
        UPCLTAL = (((MaxTAL - MinTAL)/4)*3) + MinTAL
        LPCLTAL = ((MaxTAL - MinTAL)/4) + MinTAL
        UPCLPT = (((MaxPT - MinPT)/4)*3) + MinPT
        LPCLPT = ((MaxPT - MinPT)/4) + MinPT
        break
    elif UserElection == SolderPaste5:
        MinRS = 0.5
        MaxRS = 2.00
        MinTAL = 30.00
        MaxTAL = 90.00
        MinPT = 204.00
        MaxPT = 224.00
        TALObj = 65.00
        PTObj = 215.00
        UPCLRS = (((MaxRS - MinRS)/4)*3) + MinRS
        LPCLRS = ((MaxRS - MinRS)/4) + MinRS
        UPCLTAL = (((MaxTAL - MinTAL)/4)*3) + MinTAL
        LPCLTAL = ((MaxTAL - MinTAL)/4) + MinTAL
        UPCLPT = (((MaxPT - MinPT)/4)*3) + MinPT
        LPCLPT = ((MaxPT - MinPT)/4) + MinPT
        break
