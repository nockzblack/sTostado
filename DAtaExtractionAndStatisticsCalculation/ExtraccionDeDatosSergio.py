import PyPDF2


print("Insert the document you want to extract the data of")
print("Please specify the format of the document, example Document.pdf")


Document = input("Name of the document: ")
OutPut = open("OutPuts.txt", "w")
Values = open("Thermocouples Values.txt", 'w')
pdfNewFile = open(Document, 'rb')
pdfReader = PyPDF2.PdfFileReader(pdfNewFile)
pageObj2 = pdfReader.getPage(1)
pageObj = pdfReader.getPage(0)
text = pageObj.extractText()
text2 = pageObj2.extractText()  # Extraction of the data text page 2
numToWork = text2.find("#")  # The numeral is found to know where are the data.
toWork = text2[numToWork:]   # Variable called toWork is a string


index_PositiveSlope = toWork.index("PositiveSlope")  # We are founding words
index_PositiveSlopeTime = toWork.index("PositiveSlope Time")
index_TimeAboveLiquids = toWork.index("Time AboveLiquidus")
index_PeakTemperature = toWork.index("PeakTemperature")
index_Variable = 0
index_Lower = text.index("Lower")  # Index to find the Oven Temperature Data.


if "Time AbovePeak" in toWork:  # It mght be this string on the text or not
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
        Values.write(term)
        Values.write(" ")
        PositiveSlopeData = PositiveSlopeData[end:]
    OutPut.write("1")
    return True


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
        Values.write(term)
        Values.write(" ")
        TimeAboveLiquidsData = TimeAboveLiquidsData[end:]
    OutPut.write("1")
    return True


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
        Values.write(term)
        Values.write(" ")
        PeakTemperatureData = PeakTemperatureData[end:]
    OutPut.write("1")
    return True


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
            Values.write(GeneralData2[0])
            Values.write(" ")
            GeneralData2.remove(GeneralData2[0])
        return True
    else:
        TemperatureData = TemperatureData[2]
        TemperatureData = TemperatureData[TemperatureData.index("H"):]
        TemperatureData = TemperatureData.split(".")
        for i in range(10):
            for j in range(2):
                TemperatureData.remove(TemperatureData[0])
            Values.write(TemperatureData[0])
            Values.write(" ")
            TemperatureData.remove(TemperatureData[0])
        return True


ValuesPositiveSlope()
Values.write("\n")
ValuesTimeAboveLiquids()
Values.write("\n")
ValuesPeakTemperature()
Values.write("\n")
OvenTemperatureData()


OutPut.close()
Values.close()
pdfNewFile.close()
