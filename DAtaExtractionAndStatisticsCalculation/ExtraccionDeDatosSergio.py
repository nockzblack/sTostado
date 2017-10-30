import PyPDF2


print("Insert the document you want to extract the data of")
print("Please specify the format of the document, example Document.pdf")


Document = input("Name of the document: ")
OutPut = open("OutPuts.txt", "w")
pdfNewFile = open(Document,'rb')
pdfReader = PyPDF2.PdfFileReader(pdfNewFile)
pageObj2 = pdfReader.getPage(1)
pageObj = pdfReader.getPage(0)
text = pageObj.extractText()
text2 = pageObj2.extractText() # Extraction of the data text page 2
numToWork = text2.find("#") # The numeral is found to know where are the data.
toWork = text2[numToWork:]  #Variable called toWork is a string


index_PositiveSlope = toWork.index("PositiveSlope") # We are founding words
index_PositiveSlopeTime = toWork.index("PositiveSlope Time")
index_TimeAboveLiquids = toWork.index("Time AboveLiquidus")
index_PeakTemperature = toWork.index("PeakTemperature")
index_Variable = 0
index_Lower = text.index("Lower") # Index to find the Oven Temperature Data.


if "Time AbovePeak" in toWork: # It mght be this string on the text or not
    index_Variable = toWork.index("Time AbovePeak")
else:
    index_Variable = toWork.index("Delta T")


PositiveSlopeDef = []
def ValuesPositiveSlope():
    PositiveSlopeData = ""
    PositiveSlope = toWork[index_PositiveSlope:index_PositiveSlopeTime]
    for i in PositiveSlope:
        if i in "0123456789.":
            PositiveSlopeData += i
        elif i in "*":
            warning = OutPut.write("0")
            return warning
    begin = 0
    cont = 0
    while cont < len(PositiveSlopeData):
        point = PositiveSlopeData.index(".")
        end = point + 3
        firstPart = PositiveSlopeData[begin:point]
        secondPart = PositiveSlopeData[point:end]
        term = firstPart + secondPart
        PositiveSlopeDef.append(term)
        y = begin
        PositiveSlopeData = PositiveSlopeData[end:]
        cont += 1
    PositiveSlopeDef.append(PositiveSlopeData)
    for i in PositiveSlopeDef:
        if i == '':
            PositiveSlopeDef.remove(i)
    OutPut.write("1")
    return PositiveSlopeDef


TimeAboveLiquidsDef = []
def ValuesTimeAboveLiquids():
    TimeAboveLiquidsData = ""
    TimeAboveLiquids = toWork[index_TimeAboveLiquids:index_PeakTemperature]
    while ")" in TimeAboveLiquids: # Still working on lines between 70 and 72
        x = TimeAboveLiquids.index(")")
        TimeAboveLiquids = TimeAboveLiquids[x+1:]
    for i in TimeAboveLiquids:
        if i in "0123456789.":
            TimeAboveLiquidsData += i
        elif i in "*":
            warning = OutPut.write("0")
            return warning
    begin = 0
    cont = 0
    while cont < len(TimeAboveLiquidsData):
        point = TimeAboveLiquidsData.index(".")
        end = point + 3
        firstPart = TimeAboveLiquidsData[begin:point]
        secondPart = TimeAboveLiquidsData[point:end]
        term = firstPart + secondPart
        TimeAboveLiquidsDef.append(term)
        y = begin
        TimeAboveLiquidsData = TimeAboveLiquidsData[end:]
        cont += 1
    TimeAboveLiquidsDef.append(TimeAboveLiquidsData)
    for i in TimeAboveLiquidsDef:
        if i == '':
            TimeAboveLiquidsDef.remove(i)
    OutPut.write("1")
    return TimeAboveLiquidsDef


PeakTemperatureDef = []
def ValuesPeakTemperature():
    PeakTemperatureData = ""
    PeakTemperature = toWork[index_PeakTemperature:index_Variable]
    for i in PeakTemperature:
        if i in "0123456789.":
            PeakTemperatureData += i
        elif i in "*":
            warning = OutPut.write("0")
            return warning
    begin = 0
    cont = 0
    while cont < len(PeakTemperatureData):
        point = PeakTemperatureData.index(".")
        end = point + 2
        firstPart = PeakTemperatureData[begin:point]
        secondPart = PeakTemperatureData[point:end]
        term = firstPart + secondPart
        PeakTemperatureDef.append(term)
        y = begin
        PeakTemperatureData = PeakTemperatureData[end:]
        cont += 1
    PeakTemperatureDef.append(PeakTemperatureData)
    for i in PeakTemperatureDef:
        if i == '':
            PeakTemperatureDef.remove(i)
    OutPut.write("1")
    return PeakTemperatureDef

TemperatureDataDef = []
TemperatureDataDef2 = []
def OvenTemperatureData():
    GeneralData = text[index_Lower:]
    TemperatureData = GeneralData.split(" ")
    TemperatureData2 = []
    if "Zona" in GeneralData: # Language of the document modify the format
        cont = 0
        while cont < len(TemperatureData):
            try:
                TemperatureData[cont] = float(TemperatureData[cont])
                TemperatureData2.append(TemperatureData[cont])
            except ValueError:
                TemperatureData.remove(TemperatureData[cont])
            cont += 1
        cont1 = 1
        for i in TemperatureData2:
            if cont1 % 3 == 0:
                TemperatureDataDef.append(i)
            cont1 += 1
        for i in range(2):
            TemperatureDataDef.remove(TemperatureDataDef[10])
        return TemperatureDataDef
    else:
        TemperatureData = TemperatureData[2]
        TemperatureData = TemperatureData[TemperatureData.index("H"):]
        cont = 0
        cont1 = 0
        while cont < len(TemperatureData):
            if TemperatureData[cont] == ".":
                cont1 += 1
            elif cont1 == 2:
                TemperatureData = TemperatureData[cont:]
                TemperatureData = TemperatureData[1:]
                begin = 0
                point = TemperatureData.index(".")
                end = point + 2
                firstPart = TemperatureData[begin:point]
                secondPart = TemperatureData[point:end]
                term = firstPart + secondPart
                TemperatureDataDef2.append(term)
                TemperatureData = TemperatureData[end:]
                cont = 0
                cont1 = 0
            cont += 1
        return TemperatureDataDef2


print(ValuesPositiveSlope())
print(ValuesTimeAboveLiquids())
print(ValuesPeakTemperature())
print(OvenTemperatureData())



OutPut.close()
pdfNewFile.close()
