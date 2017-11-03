import os
import PyPDF2
import sys

carpeta = os.listdir("/Users/Victor Aguayo/Desktop/Perfiles")
ruta="/Users/Victor Aguayo/Desktop/Perfiles/"

def documents (carpeta):
    num=int(input("¿Cuantos archivos deseas agregar?"))
    if num==len(carpeta):
        return carpeta
    elif num<len(carpeta):
        PDF=carpeta[len(carpeta):(len(carpeta)-num-1):-1]
        return PDF
    else:
        print ("En la seccion seleccionada solo existen {0} archivos".format(len(carpeta)))
        sys.exit()

OutPut = open("OutPut.txt", "w")

for x in documents(carpeta):
    pdfNewFile = open(ruta+x,'rb')
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
                return 0
        while len(PositiveSlopeData) > 0:
            point = PositiveSlopeData.index(".")
            end = point + 3
            firstPart = PositiveSlopeData[0:point]
            secondPart = PositiveSlopeData[point:end]
            term = firstPart + secondPart
            PositiveSlopeDef.append(term)
            PositiveSlopeData = PositiveSlopeData[end:]
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
                return 0
        while len(TimeAboveLiquidsData) > 0:
            point = TimeAboveLiquidsData.index(".")
            end = point + 3
            firstPart = TimeAboveLiquidsData[0:point]
            secondPart = TimeAboveLiquidsData[point:end]
            term = firstPart + secondPart
            TimeAboveLiquidsDef.append(term)
            TimeAboveLiquidsData = TimeAboveLiquidsData[end:]
        return TimeAboveLiquidsDef


    PeakTemperatureDef = []
    def ValuesPeakTemperature():
        PeakTemperatureData = ""
        PeakTemperature = toWork[index_PeakTemperature:index_Variable]
        for i in PeakTemperature:
            if i in "0123456789.":
                PeakTemperatureData += i
            elif i in "*":
                return 0
        while len(PeakTemperatureData) > 0:
            point = PeakTemperatureData.index(".")
            end = point + 2
            firstPart = PeakTemperatureData[0:point]
            secondPart = PeakTemperatureData[point:end]
            term = firstPart + secondPart
            PeakTemperatureDef.append(term)
            PeakTemperatureData = PeakTemperatureData[end:]
        return PeakTemperatureDef


    TemperatureDataDef = []
    TemperatureDataDef2 = []
    def OvenTemperatureData():
        GeneralData = text[index_Lower:]
        TemperatureData = GeneralData.split(" ")
        TemperatureData2 = []
        GeneralData2 = ""
        if "Zona" in GeneralData: # Language of the document modify the format
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
                TemperatureDataDef.append(GeneralData2[0])
                GeneralData2.remove(GeneralData2[0])
            return TemperatureDataDef
        else:
            TemperatureData = TemperatureData[2]
            TemperatureData = TemperatureData[TemperatureData.index("H"):]
            TemperatureData = TemperatureData.split(".")
            for i in range(10):
                for j in range(2):
                    TemperatureData.remove(TemperatureData[0])
                TemperatureDataDef2.append(TemperatureData[0])
                TemperatureData.remove(TemperatureData[0])
            return TemperatureDataDef2

    OutPut.write("\n"+str(ValuesPositiveSlope())+"\n")
    OutPut.write(str(ValuesTimeAboveLiquids())+"\n")
    OutPut.write(str(ValuesPeakTemperature())+"\n")
    OutPut.write(str(OvenTemperatureData())+"\n")

OutPut.close()
pdfNewFile.close()
