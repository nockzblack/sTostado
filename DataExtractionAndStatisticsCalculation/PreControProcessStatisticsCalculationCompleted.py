import PyPDF2
import os
import sys

#DestinyPath = "/Users/sergio/Documents/Prueba/Prueba2/Prueba3/Prueba4/Prueba5"
DestinyPath = sys.argv[1]
Document = sys.argv[2]
#Document = "arris2.pdf"
UserSolderPasteElection = sys.argv[3]
#UserSolderPasteElection = "Alpha OM 338 PT"

OriginPath = os.getcwd()
os.chdir(DestinyPath)
OutPut = open("OutPuts1.txt", "w")
pdfNewFile = open(Document, 'rb')
pdfReader = PyPDF2.PdfFileReader(pdfNewFile, strict=False)
pageObj2 = pdfReader.getPage(1)
pageObj = pdfReader.getPage(0)
text = pageObj.extractText()
text2 = pageObj2.extractText()
numToWork = text2.find("#")
toWork = text2[numToWork:]

index_PositiveSlope = toWork.index("PositiveSlope")
index_PositiveSlopeTime = toWork.index("PositiveSlope Time")
index_TimeAboveLiquids = toWork.index("Time AboveLiquidus")
index_PeakTemperature = toWork.index("PeakTemperature")
index_Variable = 0
index_Lower = text.index("Lower")

if "Time AbovePeak" in toWork:
    index_Variable = toWork.index("Time AbovePeak")
else:
    index_Variable = toWork.index("Delta T")


def ValuesPositiveSlope():
    PositiveSlopeData = ""
    PositiveSlope = toWork[index_PositiveSlope:index_PositiveSlopeTime]
    for i in PositiveSlope:
        if i in "0123456789.":
            PositiveSlopeData += i
        elif i in "*":
            warning = OutPut.write("0")
            return warning
    while len(PositiveSlopeData) > 0:
        point = PositiveSlopeData.index(".")
        end = point + 3
        firstPart = PositiveSlopeData[0:point]
        secondPart = PositiveSlopeData[point:end]
        term = firstPart + secondPart
        if float(term) > 100:
            term = float(term) / 60
        else:
            term = term
        print(term)
        PositiveSlopeData = PositiveSlopeData[end:]
    true = OutPut.write("1")
    return true


def ValuesTimeAboveLiquids():
    TimeAboveLiquidsData = ""
    TimeAboveLiquids = toWork[index_TimeAboveLiquids:index_PeakTemperature]
    while ")" in TimeAboveLiquids:  # Still working on lines between 70 and 72
        x = TimeAboveLiquids.index(")")
        TimeAboveLiquids = TimeAboveLiquids[x + 1:]
    for i in TimeAboveLiquids:
        if i in "0123456789.":
            TimeAboveLiquidsData += i
        elif i in "*":
            warning = OutPut.write("0")
            return warning
    while len(TimeAboveLiquidsData) > 0:
        point = TimeAboveLiquidsData.index(".")
        end = point + 3
        firstPart = TimeAboveLiquidsData[0:point]
        secondPart = TimeAboveLiquidsData[point:end]
        term = firstPart + secondPart
        print(term)
        TimeAboveLiquidsData = TimeAboveLiquidsData[end:]
    true = OutPut.write("1")
    return true


def ValuesPeakTemperature():
    PeakTemperatureData = ""
    PeakTemperature = toWork[index_PeakTemperature:index_Variable]
    for i in PeakTemperature:
        if i in "0123456789.":
            PeakTemperatureData += i
        elif i in "*":
            warning = OutPut.write("0")
            return warning
    while len(PeakTemperatureData) > 0:
        point = PeakTemperatureData.index(".")
        end = point + 2
        firstPart = PeakTemperatureData[0:point]
        secondPart = PeakTemperatureData[point:end]
        term = firstPart + secondPart
        print(term)
        PeakTemperatureData = PeakTemperatureData[end:]
    true = OutPut.write("1")
    return true


def OvenTemperatureData():
    GeneralData = text[index_Lower:]
    TemperatureData = GeneralData.split(" ")
    GeneralData2 = ""
    if "Zona" in GeneralData:  # Language of the document modify the format
        for i in GeneralData:
            if i == " ":
                GeneralData2 += ""
            else:
                GeneralData2 += i
        index_p = GeneralData.index(":")
        GeneralData2 = GeneralData2[index_p:]
        GeneralData2 = GeneralData2.split(".")
        for i in range(10):
            for j in range(2):
                GeneralData2.remove(GeneralData2[0])
            print(int(GeneralData2[0]))
            GeneralData2.remove(GeneralData2[0])
        return True
    else:
        TemperatureData = TemperatureData[2]
        TemperatureData = TemperatureData[TemperatureData.index("H"):]
        TemperatureData = TemperatureData.split(".")
        for i in range(10):
            for j in range(2):
                TemperatureData.remove(TemperatureData[0])
            print(int(TemperatureData[0]))
            TemperatureData.remove(TemperatureData[0])
        return True


print("A")
ValuesPositiveSlope()
print("B")
ValuesTimeAboveLiquids()
print("C")
ValuesPeakTemperature()
print("D")
OvenTemperatureData()

OutPut.close()
pdfNewFile.close()

DocMessage = open("OutPuts1.txt", 'r')
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
DocMessage.close()

if cont1 == 3:
    SolderPaste1 = "Indium 8.9E Lead free"
    SolderPaste2 = "Indium 5.8LS Lead free"
    SolderPaste3 = "Senju M40-LS720V-HF"
    SolderPaste4 = "Alpha OM 338 PT"
    SolderPaste5 = "Indium SMQ98H (Sn63Pb37)"
    Warning1 = ""
    MinRS = 0  # MinimumRiseSlope
    MaxRS = 0  # MaximumRiseSlope
    MinTAL = 0  # MinimumTimeAboveLiquids
    MaxTAL = 0  # MaximumTimeAboveLiquids
    MinPT = 0  # MinimumPeakTemperature
    MaxPT = 0  # MaximumPeakTemperature
    TALObj = 0  # TimeAboveLiquidsObjective
    PTObj = 0  # PeakTemperatureObjective
    UPCLRS = 0  # UpperPreControlLimitRiseSlope
    LPCLRS = 0  # LowerPreControlLimitRiseSlope
    UPCLTAL = 0  # UpperPrecontrolLimitTimeAboveLiquids
    LPCLTAL = 0  # LowerPreControlLimitTimeAboveLiquids
    UPCLPT = 0  # UpperPreControlLimitPeakTemperature
    LPCLPT = 0  # LowerPreControlLimitPeakTemperature
    while True:
        if UserSolderPasteElection == SolderPaste1 or UserSolderPasteElection == SolderPaste2:
            MinRS = 0.5
            MaxRS = 2.5
            MinTAL = 30.00
            MaxTAL = 100.00
            MinPT = 230.00
            MaxPT = 262.00
            TALObj = 65.00
            PTObj = 245.00
            UPCLRS = (((MaxRS - MinRS) / 4) * 3) + MinRS
            LPCLRS = ((MaxRS - MinRS) / 4) + MinRS
            UPCLTAL = (((MaxTAL - MinTAL) / 4) * 3) + MinTAL
            LPCLTAL = ((MaxTAL - MinTAL) / 4) + MinTAL
            UPCLPT = (((MaxPT - MinPT) / 4) * 3) + MinPT
            LPCLPT = ((MaxPT - MinPT) / 4) + MinPT
            print("E")
            print(UPCLRS)
            print(LPCLRS)
            print(UPCLTAL)
            print(LPCLTAL)
            print(UPCLPT)
            print(LPCLPT)
            break
        elif UserSolderPasteElection == SolderPaste3:
            MinRS = 0.8
            MaxRS = 1.5
            MinTAL = 30.00
            MaxTAL = 90.00
            MinPT = 232.00
            MaxPT = 255.00
            TALObj = 60.00
            PTObj = 245.00
            UPCLRS = (((MaxRS - MinRS) / 4) * 3) + MinRS
            LPCLRS = ((MaxRS - MinRS) / 4) + MinRS
            UPCLTAL = (((MaxTAL - MinTAL) / 4) * 3) + MinTAL
            LPCLTAL = ((MaxTAL - MinTAL) / 4) + MinTAL
            UPCLPT = (((MaxPT - MinPT) / 4) * 3) + MinPT
            LPCLPT = ((MaxPT - MinPT) / 4) + MinPT
            print("E")
            print(UPCLRS)
            print(LPCLRS)
            print(UPCLTAL)
            print(LPCLTAL)
            print(UPCLPT)
            print(LPCLPT)
            break
        elif UserSolderPasteElection == SolderPaste4:
            MinRS = 0.5
            MaxRS = 3.0
            MinTAL = 45.00
            MaxTAL = 90.00
            MinPT = 230.00
            MaxPT = 250.00
            TALObj = 65.00
            PTObj = 240.00
            UPCLRS = (((MaxRS - MinRS) / 4) * 3) + MinRS
            LPCLRS = ((MaxRS - MinRS) / 4) + MinRS
            UPCLTAL = (((MaxTAL - MinTAL) / 4) * 3) + MinTAL
            LPCLTAL = ((MaxTAL - MinTAL) / 4) + MinTAL
            UPCLPT = (((MaxPT - MinPT) / 4) * 3) + MinPT
            LPCLPT = ((MaxPT - MinPT) / 4) + MinPT
            print("E")
            print(UPCLRS)
            print(LPCLRS)
            print(UPCLTAL)
            print(LPCLTAL)
            print(UPCLPT)
            print(LPCLPT)
            break
        elif UserSolderPasteElection == SolderPaste5:
            MinRS = 0.5
            MaxRS = 2.00
            MinTAL = 30.00
            MaxTAL = 90.00
            MinPT = 204.00
            MaxPT = 224.00
            TALObj = 65.00
            PTObj = 215.00
            UPCLRS = (((MaxRS - MinRS) / 4) * 3) + MinRS
            LPCLRS = ((MaxRS - MinRS) / 4) + MinRS
            UPCLTAL = (((MaxTAL - MinTAL) / 4) * 3) + MinTAL
            LPCLTAL = ((MaxTAL - MinTAL) / 4) + MinTAL
            UPCLPT = (((MaxPT - MinPT) / 4) * 3) + MinPT
            LPCLPT = ((MaxPT - MinPT) / 4) + MinPT
            print("E")
            print(UPCLRS)
            print(LPCLRS)
            print(UPCLTAL)
            print(LPCLTAL)
            print(UPCLPT)
            print(LPCLPT)
            break
else:
    Warning1 = "Impossible to calculate. Try to generate the data again. There was an error with a thermocouple."
    print(Warning1)
    sys.exit()
sys.exit()
