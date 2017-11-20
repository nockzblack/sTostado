#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "auxwindow.h"
#include "controlwindow.h"

#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <QTableWidget>
#include <QPalette>

#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>

#include <QProcess>
#include <QFileInfo>

QT_CHARTS_USE_NAMESPACE

int static familyIndex;

int static familyIndexControl;
// Types of Groups
QStringList static videoFamily = {"Select Group...","Rockstar","AGB","CAP1010","ME7K"};
QStringList static dsrFamily = {"Select Group...","Lead_free","Legacy_lead"};
QStringList static picsFamily = {"Select Group...", "Group.Pics"};
QStringList static e6milFamily = {"Select Group...", "Group_E6mil"};

// Types of Models
// Video Family
QStringList static videoRockstar = {"Select Model...","553945-001-00-345","553945-002-00-345","553946-001-00-345","553947-001-00-345"};
QStringList static videoAGB = {"Select Model...", "559635-001-00-345", "569695-002-00-345"};
QStringList static videoME7mil = {"Select Model...", "591400-001-00-345", "593467-001-00-345", "593562-001-00-345", "594707-001-00-345", "594707-002-00-345"};
QStringList static videoCAP = {"Select Model...","570882-001-00-345", "575621-001-00-345", "550679-001-00-345", "552484-001-00-345", "552508-001-00-345", "546027-001-00-345", "569687-001-00-345"};
// Dsr Family
QStringList static dsrLeadFree = {"Select Model...", "598020-002-00", "598036-002-00","594834-001-00","597466-001-00","586214-001-00","612181-001-00"};
QStringList static dsrLegacyLead = {"Select Model...", "573945-001-00", "573329-003-00", "572372-004-00", "591547-001-00", "573946-001-00", "581255-001-00", "581305-002-00", "524697-002-00"};
// Pics Family
QStringList static picsGroup_Pics = {"Select Model...", "ARCT03327", "ARCT04573", "ARCT04398", "ARCT03313", "ARCT03753", "ARCT03321", "ARCT02469", "ARCT03745", "ARCT04679", "ARCT04575", "ARCT03323", "ARCT02433", "ARCT03749", "ARCT04399", "ARCT04475"};
// E6mil Family
QStringList static e6milGroup_E6mil = {"Select Model...", "ARCT03477", "ARCT03309", "ARCT02473", "ARCT03999"};


QStringList static positiveSlopeValues = {};
QStringList static peakTemperatureValues = {};
QStringList static timeAboveValues = {};
QStringList static ovenTempValues = {};
QStringList static preControlLimits = {};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set default values and properties to precontrol tables widgets
    setDefaultParametersTW();
    setDefaultTempTW();
    // Set default values and properties to control tables widgets
    setDefaultParametersTWC();

    // Set solder paste combox boxes unenabled because this is selected automatically
    ui->solderPasteCB->setEnabled(false);
    ui->selectFilePB->setEnabled(false);
    ui->savePB->setEnabled(false);
    ui->positiveSlopePB->setEnabled(false);
    ui->peakTempPB->setEnabled(false);
    ui->TALPB->setEnabled(false);

    ui->solderPasteCBC->setEnabled(false);
    ui->peakTempPBC->setEnabled(false);
    ui->TALPBC->setEnabled(false);
}


MainWindow::~MainWindow()
{
    delete ui;
}



/* **************************************************
 * Start the code for the precontrol UI part
 *
 */


void MainWindow::on_savePB_clicked()
{
    bool info = saveInfo();
    ui->savePB->setEnabled(false);
    QMessageBox msgBox;

    if (info) {
        msgBox.setText("Data was succesfully saved");
        msgBox.exec();
    } else {
        msgBox.setText("An error occur trying to save data");
        msgBox.exec();
    }

}


bool MainWindow::saveInfo() {

    QDir dir(".");
    QString path = dir.absolutePath();
    path = path + "/preControlData.txt";

    QFile auxFile(path);

    if (!auxFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
        return false;
    }

    QTextStream out(&auxFile);
    out << currentTexts();

    auxFile.close();
    return true;
}


QString MainWindow::currentTexts() {
    QString auxStr = "";

    auxStr += ui->familyCB->currentText();
    auxStr += "/";
    auxStr += ui->groupCB->currentText();
    auxStr += "/";
    auxStr += ui->boardSideCB->currentText();
    auxStr += "/";
    auxStr += ui->modelCB->currentText();
    auxStr += "/";
    auxStr += ui->solderPasteCB->currentText();
    auxStr += "/";
    auxStr += ui->productionLineCB->currentText();
    auxStr += "/";

    for (int i=0; i<10; ++i) {
        auxStr += ui->tempTW->item(0,i)->text();
        auxStr += "/";
    }

    for (int i=0; i<6; ++i) {
        auxStr += ui->parametersTW->item(i,0)->text();
        auxStr += "/";
    }

    for (int i = 0; i<positiveSlopeValues.length(); ++i) {
        auxStr += positiveSlopeValues[i];
        auxStr += "/";
    }

    for (int i = 0; i<timeAboveValues.length(); ++i) {
        auxStr += timeAboveValues[i];
        auxStr += "/";
    }

    for (int i = 0; i<peakTemperatureValues.length(); ++i) {
        auxStr += peakTemperatureValues[i];
        auxStr += "/";
    }

    for (int i = 0; i<ovenTempValues.length(); ++i) {
        auxStr += ovenTempValues[i];
        auxStr += "/";
    }

    for (int i = 0; i<ovenTempValues.length(); ++i) {
        auxStr += ovenTempValues[i];
        auxStr += "/";
    }

    for (int i = 0; i<preControlLimits.length(); ++i) {
        auxStr += preControlLimits[i];
        auxStr += "/";
    }
    auxStr += "\n";

    return auxStr;
}


void MainWindow::setDefaultParametersTW() {
    // Set default values and properties to parameters TW on preControl tab
    QHeaderView *parameterHorHeader = ui->parametersTW ->horizontalHeader();
    parameterHorHeader->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *parametersVerHeader = ui->parametersTW ->verticalHeader();
    parametersVerHeader->setSectionResizeMode(QHeaderView::Stretch);
    ui->parametersTW->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList defaultlValuesPTW = {"","","","","",""};
    updateParametersTW(defaultlValuesPTW);
}



void MainWindow::setDefaultTempTW() {
    // Set default values and properties to temperature TW on preControl tab
    QHeaderView *tempHorHeader = ui->tempTW->horizontalHeader();
    tempHorHeader->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *tempVerHeader = ui->tempTW ->verticalHeader();
    tempVerHeader->setSectionResizeMode(QHeaderView::Stretch);
    ui->tempTW->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList defaultValuesTTW = {"","","","","","","","","",""};
    updateTempTW(defaultValuesTTW);
}


void MainWindow::arrangeStr(QString auxStr) {

    int bPos = auxStr.indexOf("B");
    int cPos = auxStr.indexOf("C");
    int dPos = auxStr.indexOf("D");
    int ePos = auxStr.indexOf("E");


    int difCB = cPos - bPos;
    int difDC = dPos - cPos;
    int difED = ePos - dPos;

    QString PSValues = auxStr.mid(0,bPos);
    QString TALValues = auxStr.mid(bPos,difCB);
    QString PTVAlues = auxStr.mid(cPos,difDC);
    QString OTValues = auxStr.mid(dPos,difED);
    QString preControlLimitsValues = auxStr.mid(ePos,auxStr.length()-ePos);


    positiveSlopeValues = getStringValues(PSValues);
    timeAboveValues = getStringValues(TALValues);
    peakTemperatureValues = getStringValues(PTVAlues);
    ovenTempValues = getStringValues(OTValues);
    preControlLimits = getStringValues(preControlLimitsValues);
}


QStringList MainWindow::getStringValues(QString& str) {
    QStringList  stringValues;
    bool intFlag = false;
    bool strFlag = false;

    QString auxStr = "";

    for (int i = 0; i<str.length(); ++i) {

        if (str[i].isDigit() or str[i] == '.') {
            intFlag = true;
            auxStr += str[i];
            strFlag = true;
        } else {
            intFlag = false;
        }


        if (intFlag == false and strFlag == true) {
            stringValues.append(auxStr);
            auxStr = "";
            strFlag = false;
        }
    }

    return stringValues;
}



void MainWindow::on_familyCB_activated(int index)
{
    /*
     * When the family combo box is clicked it is cleanead the group and model
     * combo box... The index that the user choose is assigned to the family index var
     * in order to add the correct items on the other combo boxes.
     *
     */

    ui->groupCB->clear();
    ui->modelCB->clear();

    switch (index) {

        case(1):
            ui->groupCB->addItems(videoFamily);
            familyIndex = index;
        break;

        case(2):
            ui->groupCB->addItems(dsrFamily);
            familyIndex = index;
        break;

        case(3):
            ui->groupCB->addItems(picsFamily);
            familyIndex = index;
        break;

        case(4):
            ui->groupCB->addItems(e6milFamily);
            familyIndex = index;
        break;
    }
}

void MainWindow::on_groupCB_activated(int index)
{
    /*
     * When the family combo box is clicked it is cleanead the model
     * combo box... The index that the user choose and with the family Index var value
     * it is added the right items on the model combo box
     *
     */

    ui->modelCB->clear();

    switch (familyIndex) {

    case(1):
        if (index == 1) {
            ui->modelCB->addItems(videoRockstar);
            setParameterTW(1);
            ui->solderPasteCB->setCurrentIndex(1);

        } else if (index == 2) {
            ui->modelCB->addItems(videoAGB);
            setParameterTW(1);
            ui->solderPasteCB->setCurrentIndex(1);

        } else if (index == 3) {
            ui->modelCB->addItems(videoCAP);
            setParameterTW(2);
            ui->solderPasteCB->setCurrentIndex(2);

        }else if (index == 4) {
            ui->modelCB->addItems(videoME7mil);
            setParameterTW(1);
            ui->solderPasteCB->setCurrentIndex(1);
        }
        break;

    case(2):
        if (index == 1){
            ui->modelCB->addItems(dsrLeadFree);
            setParameterTW(2);
            ui->solderPasteCB->setCurrentIndex(2);

        } else if (index==2){
            ui->modelCB->addItems(dsrLegacyLead);
            setParameterTW(5);
            ui->solderPasteCB->setCurrentIndex(5);
        }
       break;

    case(3):
        if (index == 1){
            ui->modelCB->addItems(picsGroup_Pics);
            setParameterTW(3);
            ui->solderPasteCB->setCurrentIndex(3);
        }
        break;
    case(4):
        if (index == 1){
            ui->modelCB->addItems(e6milGroup_E6mil);
            setParameterTW(4);
            ui->solderPasteCB->setCurrentIndex(4);
        }
        break;
    }
}

void MainWindow::on_selectFilePB_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,tr(""), "",tr("PDF (*.pdf)"));

    //Obtencion de parametros necesarios para el codigo python.
    QString Name = QFileInfo(fileName).fileName();
    QFileInfo  info(fileName);
    QString correctfileName = info.path();
    correctfileName.remove(0,2);
    QString paste = ui->solderPasteCB->currentText();

    if (fileName.isEmpty())
            return;
    else {
            //Codigo necesario para utilizar script python.
            //se obtiene el path de donde esta ubicada la aplicacion si se ponen los scripts python en el mismo lugar funciona,
            QString dir1(QCoreApplication::applicationDirPath ());
            QFileInfo info(dir1, "PreControProcessStatisticsCalculationCompleted.py");
            QProcess process;
            process.setProcessChannelMode(QProcess::MergedChannels);
            process.start("python.exe", QStringList()<< info.absoluteFilePath() << correctfileName << Name << paste);
            process.waitForFinished(-1);
            QString output(process.readAll());
            //qDebug() << output;
            arrangeStr(output);
            ui->directoryL->setText(correctfileName);
            updateTempTW(ovenTempValues);
    }
}



void MainWindow::setParameterTW(int index)
{
    /*
     * When the solder paste combo box change it is updated the values on the
     * acceptable parameter table widget, these values depens on the index that
     * it is clicked.
     *
     *
     */

    switch(index) {
        case 1:
        {
            QStringList actualValues = {"30","100","230","262","0.5","2.5"};
            updateParametersTW(actualValues);
        }
        break;


        case 2:
        {
            QStringList actualValues = {"30","100","230","262","0.5","2.5"};
            updateParametersTW(actualValues);
         }
        break;

        case 3:
        {
            QStringList actualValues = {"30","90","232","255","0.8","1.5"};
            updateParametersTW(actualValues);
         }
        break;

        case 4:
        {
            QStringList actualValues = {"45","90","230","250","0.5","3"};
            updateParametersTW(actualValues);
         }
        break;

        case 5:
        {
            QStringList actualValues = {"30","90","208","228","0.5","2"};
            updateParametersTW(actualValues);
         }
        break;
    }
}

void MainWindow::updateParametersTW(QStringList &values) {

    // This just create new items with the information on the list values and
    // put it into the table.
    for (int i = 0; i<6; i++) {
        QTableWidgetItem  *auxCellTWI = new QTableWidgetItem(values[i]);
        auxCellTWI->setTextAlignment(Qt::AlignCenter);
        ui->parametersTW->setItem(0,i, auxCellTWI);
    }
}


void MainWindow::updateTempTW(QStringList &values) {

    // This just create new items with the information on the list values and
    // put it into the table.
    for (int i = 0; i<10; i++) {
        QTableWidgetItem  *auxCellTWI = new QTableWidgetItem(values[i]);
        auxCellTWI->setTextAlignment(Qt::AlignCenter);
        ui->tempTW->setItem(0,i, auxCellTWI);
    }
}



QStringList MainWindow::getRiseSlopeValues() {

    //qDebug() << ui->parametersTW->item(4,0)->text();
    QString mimRise = ui->parametersTW->item(4,0)->text();
    QString maxRise = ui->parametersTW->item(5,0)->text();

    QStringList riseValues = {mimRise, maxRise};

    return riseValues;
}

QStringList MainWindow::getPeakTempValues() {

    QString mimPeakTemp = ui->parametersTW->item(2,0)->text();
    QString maxPeakTemp = ui->parametersTW->item(3,0)->text();

    QStringList peakTempValues = {mimPeakTemp, maxPeakTemp};

    return peakTempValues;
}

QStringList MainWindow::getTimeAboveValues() {

    QString mimTime = ui->parametersTW->item(0,0)->text();
    QString maxTime = ui->parametersTW->item(1,0)->text();

    QStringList timeValues = {mimTime, maxTime};

    return timeValues;
}


//Graph and table showed by clicking Positive Slopes Results Button
void MainWindow::on_positiveSlopePB_clicked()
{
    //auxwindow::auxwindow(QStringList values, QStringList controlLimits, QStringList limitsValues, QString title, int lenOfData, QString scale) {

    QStringList riseValues = getRiseSlopeValues(); // getting the actual data from the acceptable parameters table

    int len = positiveSlopeValues.length();

    QStringList chartlimits = {"0","3"};

    auxwindow myWindow(positiveSlopeValues, preControlLimits, riseValues, "Positive Slope Chart", len, "Measurements (Cº/sec)", chartlimits);

    QWidget *auxWindow = myWindow.getWindow();

    auxWindow->show();
}

//Graph and table showed by clicking TAL Results Button
void MainWindow::on_TALPB_clicked()
{

    QStringList timeValues = getTimeAboveValues(); //getting value from acceptable parameters.

    int len = timeAboveValues.length();

    QStringList chartlimits = {"0","120"};

    QStringList controlLimits = {preControlLimits[2], preControlLimits[3]};

    auxwindow myWindow(timeAboveValues, controlLimits, timeValues, "TAL Chart", len, "Measurements (sec)", chartlimits);

    QWidget *auxWindow = myWindow.getWindow();

    auxWindow->show();
}

//Graph and table showed by clicking Peak Temperature Results Button
void MainWindow::on_peakTempPB_clicked()
{
    QStringList peakTempValues = getPeakTempValues();

    int len = peakTemperatureValues.length();

    QStringList chartlimits = {"200","300"};

    QStringList controlLimits = {preControlLimits[4], preControlLimits[5]};

    auxwindow myWindow(peakTemperatureValues, controlLimits, peakTempValues, "Peak Temperature Chart", len, "Measurements (Cº)", chartlimits);

    QWidget *auxWindow = myWindow.getWindow();

    auxWindow->show();
}


void MainWindow::on_cleanPB_clicked()
{
    QStringList actualValuesPTW = {"","","","","",""};
    updateParametersTW(actualValuesPTW);

    QStringList actualValuesTTW = {"","","","","","","","","",""};
    updateTempTW(actualValuesTTW);

    ui->groupCB->clear();
    ui->modelCB->clear();
    ui->familyCB->setCurrentIndex(0);
    ui->boardSideCB->setCurrentIndex(0);
    ui->productionLineCB->setCurrentIndex(0);
    ui->selectFilePB->setEnabled(false);
    ui->positiveSlopePB->setEnabled(false);
    ui->peakTempPB->setEnabled(false);
    ui->TALPB->setEnabled(false);
}


void MainWindow::on_productionLineCB_activated(int index)
{
    if (ui->familyCB->currentIndex() != 0) {
        if (ui->groupCB->currentIndex() != 0) {
            if (ui->boardSideCB->currentIndex() != 0) {
                if (ui->modelCB->currentIndex() != 0) {
                    if (ui->solderPasteCB->currentIndex() != 0) {
                        if (index != 0) {
                            ui->selectFilePB->setEnabled(true);
                            ui->savePB->setEnabled(true);
                            ui->positiveSlopePB->setEnabled(true);
                            ui->peakTempPB->setEnabled(true);
                            ui->TALPB->setEnabled(true);
                        }
                    }
                }
            }
        }
    }
}



/* **************************************************
 * Start the code for the control UI part
 *
 */


//   A     B    C     D     E    F     G
//   0     1    2     3     4    5     6
// [CPK, LCLR, UCLR, CLR, UCLX, CLX, LCLX]
QStringList static individualValuesControl = {};
QStringList static XBarValues = {}; //para graficar en la primera grafica
QStringList static rangeValues = {}; //para graficar en la segunda grafica de variabilidad
QVector<QStringList> static tableMatrix;

void MainWindow::arrangeStrControl(QString auxStr) {

    int bPos = auxStr.indexOf("B");
    int cPos = auxStr.indexOf("C");
    int dPos = auxStr.indexOf("D");

    int difCB = cPos - bPos;
    int difDC = dPos - cPos;


    QString individualVars = auxStr.mid(0,bPos);
    QString XBarStr = auxStr.mid(bPos,difCB);
    QString rangeStr = auxStr.mid(cPos,difDC);
    QString tableData = auxStr.mid(dPos,auxStr.length()-dPos);

    individualValuesControl = getStringValues(individualVars);
    XBarValues = getStringValues(XBarStr);
    rangeValues = getStringValues(rangeStr);
    tableMatrix = getListValues(tableData);
}


QVector<QStringList> MainWindow::getListValues(QString& str) {
    QVector<QStringList> tableMatrix;
    QStringList auxList = {};
    bool intFlag = false;
    bool strFlag = false;

    QString auxStr = "";

    for (int i = 0; i<str.length(); ++i) {

        if (str[i] == ']'){
            tableMatrix.append(auxList);
            auxList.clear();
        }

        if (str[i].isDigit() or str[i] == '.') {
            intFlag = true;
            auxStr += str[i];
            strFlag = true;
        } else {
            intFlag = false;
        }


        if (intFlag == false and strFlag == true) {
            auxList.append(auxStr);
            auxStr = "";
            strFlag = false;
        }
    }

    return tableMatrix;
}


QStringList MainWindow::getControlPeakTempValues() {

    QString mimTime = ui->parametersTWC->item(2,0)->text();
    QString maxTime = ui->parametersTWC->item(3,0)->text();

    QStringList timeValues = {mimTime, maxTime};

    return timeValues;
}


QStringList MainWindow::getControlTimeAboveValues() {

    QString mimTime = ui->parametersTWC->item(0,0)->text();
    QString maxTime = ui->parametersTWC->item(1,0)->text();

    QStringList timeValues = {mimTime, maxTime};

    return timeValues;
}

void MainWindow::updateParametersTWC(QStringList &values) {

    // This just create new items with the information on the list values and
    // put it into the table.
    for (int i = 0; i<4; i++) {
        QTableWidgetItem  *auxCellTWI = new QTableWidgetItem(values[i]);
        auxCellTWI->setTextAlignment(Qt::AlignCenter);
        ui->parametersTWC->setItem(0,i, auxCellTWI);
    }
}


void MainWindow::updateHeaderParametersTWC(int index) {

    for (int i = 0; i<10; i++) {;

        if (i < index) {
            ui->profilesTWC->setRowHidden(i, false);
        } else {
            ui->profilesTWC->setRowHidden(i, true);
        }
    }
}

void MainWindow::updateProfilesTWC(QVector<QStringList> auxMatrix) {
    ui->profilesTWC->setRowCount(auxMatrix.length());
    ui->profilesTWC->setColumnCount(auxMatrix[0].length());

    for (int i=0; i<auxMatrix.length(); ++i) {
        for (int j=0; j<auxMatrix[i].length(); ++j) {
            QTableWidgetItem  *auxCellTWI = new QTableWidgetItem(auxMatrix[i][j]);
            auxCellTWI->setTextAlignment(Qt::AlignCenter);
            ui->profilesTWC->setItem(i,j, auxCellTWI);
        }
    }
}

void MainWindow::on_familyCBC_activated(int index)
{
    /*
     * When the family on control Tab combo box is clicked it is cleanead the group and model
     * combo box... The index that the user choose is assigned to the family index var
     * in order to add the correct items on the other combo boxes.
     *
     */

    ui->groupCBC->clear();
    ui->modelCBC->clear();

    switch (index) {

        case(1):
            ui->groupCBC->addItems(videoFamily);
            familyIndexControl = index;
        break;

        case(2):
            ui->groupCBC->addItems(dsrFamily);
            familyIndexControl = index;
        break;

        case(3):
            ui->groupCBC->addItems(picsFamily);
            familyIndexControl = index;
        break;

        case(4):
            ui->groupCBC->addItems(e6milFamily);
            familyIndexControl = index;
        break;
    }
}


void MainWindow::on_groupCBC_activated(int index)
{
    /*
     * When the family combo box is clicked it is cleanead the model
     * combo box... The index that the user choose and with the family Index var value
     * it is added the right items on the model combo box
     *
     */

    ui->modelCBC->clear();

    switch (familyIndexControl) {

    case(1):
        if (index == 1) {
            ui->modelCBC->addItems(videoRockstar);
            setParameterTWC(1);
            ui->solderPasteCBC->setCurrentIndex(1);

        } else if (index == 2) {
            ui->modelCBC->addItems(videoAGB);
            setParameterTWC(1);
            ui->solderPasteCBC->setCurrentIndex(1);

        } else if (index == 3) {
            ui->modelCBC->addItems(videoCAP);
            setParameterTWC(2);
            ui->solderPasteCBC->setCurrentIndex(2);

        }else if (index == 4) {
            ui->modelCBC->addItems(videoME7mil);
            setParameterTWC(1);
            ui->solderPasteCBC->setCurrentIndex(1);
        }
        break;

    case(2):
        if (index == 1){
            ui->modelCBC->addItems(dsrLeadFree);
            setParameterTWC(2);
            ui->solderPasteCBC->setCurrentIndex(2);

        } else if (index==2){
            ui->modelCBC->addItems(dsrLegacyLead);
            setParameterTWC(5);
            ui->solderPasteCBC->setCurrentIndex(5);
        }
       break;

    case(3):
        if (index == 1){
            ui->modelCBC->addItems(picsGroup_Pics);
            setParameterTWC(3);
            ui->solderPasteCBC->setCurrentIndex(3);
        }
        break;
    case(4):
        if (index == 1){
            ui->modelCBC->addItems(e6milGroup_E6mil);
            setParameterTWC(4);
            ui->solderPasteCBC->setCurrentIndex(4);
        }
        break;
    }
}


void MainWindow::on_profileCBC_activated(int index)
{
    if (index == 0) {
        updateHeaderParametersTWC(10);
    } else {
        updateHeaderParametersTWC(index + 3);
    }

    if (ui->familyCBC->currentIndex() != 0) {
        if (ui->groupCBC->currentIndex() != 0) {
            if (ui->boardSideCBC->currentIndex() != 0) {
                if (ui->modelCBC->currentIndex() != 0) {
                    if (ui->solderPasteCBC->currentIndex() != 0) {
                        if(ui->directoryL->text().length() > 1) {
                            if (index != 0) {
                                ui->peakTempPBC->setEnabled(true);
                                ui->TALPBC->setEnabled(true);
                            }
                        }
                    }
                }
            }
        }
    }
}



void MainWindow::setParameterTWC(int index)
{
    /*
     * When the solder paste combo box change it is updated the values on the
     * acceptable parameter table widget, these values depens on the index that
     * it is clicked.
     *
     *
     */

    switch(index) {
        case 1:
        {
            QStringList actualValues = {"30","100","230","262"};
            updateParametersTWC(actualValues);
        }
        break;


        case 2:
        {
            QStringList actualValues = {"30","100","230","262"};
            updateParametersTWC(actualValues);
         }
        break;

        case 3:
        {
            QStringList actualValues = {"30","90","232","255"};
            updateParametersTWC(actualValues);
         }
        break;

        case 4:
        {
            QStringList actualValues = {"45","90","230","250"};
            updateParametersTWC(actualValues);
         }
        break;

        case 5:
        {
            QStringList actualValues = {"30","90","208","228"};
            updateParametersTWC(actualValues);
         }
        break;
    }
}


void MainWindow::on_cleanPBC_clicked()
{
    QStringList actualValuesPTWC = {"","","","","",""};
    updateParametersTWC(actualValuesPTWC);

    ui->groupCBC->clear();
    ui->modelCBC->clear();
    ui->familyCBC->setCurrentIndex(0);
    ui->boardSideCBC->setCurrentIndex(0);
    ui->productionLineCBC->setCurrentIndex(0);
    ui->profileCBC->setCurrentIndex(0);

    ui->groupCBC->clear();
    ui->modelCBC->clear();
    ui->familyCBC->setCurrentIndex(0);
    ui->boardSideCBC->setCurrentIndex(0);
    ui->productionLineCBC->setCurrentIndex(0);
    ui->peakTempPBC->setEnabled(false);
    ui->TALPBC->setEnabled(false);
}


void MainWindow::on_TALPBC_clicked()
{
    QStringList argsRequired = {};
    // order: path, var, value, paste
    argsRequired.append(ui->directoryL->text());
    argsRequired.append("Time Above Liquidus");
    argsRequired.append(ui->profileCBC->currentText());
    argsRequired.append(ui->solderPasteCBC->currentText());

    bool proceed = extractData(argsRequired);

    if (proceed == false) {

        QMessageBox msgBox;
        msgBox.setText("An error occur trying to calculate");
        msgBox.exec();

    } else {
        updateProfilesTWC(tableMatrix);
        ui->CPKValueL->setText(individualValuesControl[0]);

        QStringList limits = {};
        limits.append(individualValuesControl[6]);
        limits.append(individualValuesControl[5]);
        limits.append(individualValuesControl[4]);

        limits.append(individualValuesControl[1]);
        limits.append(individualValuesControl[3]);
        limits.append(individualValuesControl[2]);

        QStringList chartLimits = {"25","85","0","30"};

        controlwindow auxwindow(XBarValues, rangeValues, limits, "Time Above Liquidus", chartLimits);
        QWidget *auxWindow = auxwindow.getWindow();
        auxWindow->show();
    }
}


void MainWindow::on_peakTempPBC_clicked()
{

    QStringList argsRequired = {};
    // order: path, var, value, paste
    argsRequired.append(ui->directoryL->text());
    argsRequired.append("Peak Temperature");
    argsRequired.append(ui->profileCBC->currentText());
    argsRequired.append(ui->solderPasteCBC->currentText());

    bool proceed = extractData(argsRequired);

    if (proceed == false) {

        QMessageBox msgBox;
        msgBox.setText("An error occur trying to calculate");
        msgBox.exec();

    } else {
        updateProfilesTWC(tableMatrix);
        ui->CPKValueL->setText(individualValuesControl[0]);

        QStringList limits = {};
        limits.append(individualValuesControl[6]);
        limits.append(individualValuesControl[5]);
        limits.append(individualValuesControl[4]);

        limits.append(individualValuesControl[1]);
        limits.append(individualValuesControl[3]);
        limits.append(individualValuesControl[2]);

        QStringList chartLimits = {"220","280","0","30"};

        controlwindow auxwindow(XBarValues, rangeValues, limits, "Peak Temperature", chartLimits);
        QWidget *auxWindow = auxwindow.getWindow();
        auxWindow->show();
    }
}


bool MainWindow::extractData(QStringList data) {

    QString dir(QCoreApplication::applicationDirPath ());
    QFileInfo info(dir, "ControlProcessStatisticsCalculationComplete.py");
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    process.start("python.exe", QStringList()<< info.absoluteFilePath() << data[0] << data[1] << data[2] << data[3]);
    process.waitForFinished(-1);
    QString output(process.readAll());
    qDebug() << output;
    arrangeStrControl(output);

    if (output.length() < 12) {
        return false;
    }

    return true;
}


void MainWindow::setDefaultParametersTWC() {
    // Set default values and properties to parameters TW on control tab
    QHeaderView *parametersControlHorHeader = ui->parametersTWC->horizontalHeader();
    parametersControlHorHeader->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *parametersControlVerHeader = ui->parametersTWC->verticalHeader();
    parametersControlVerHeader->setSectionResizeMode(QHeaderView::Stretch);
    ui->parametersTWC->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList defaultValuesPTWC = {"","","",""};
    updateParametersTWC(defaultValuesPTWC);
}



