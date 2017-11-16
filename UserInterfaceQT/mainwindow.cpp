#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <QTableWidget>
#include <QPalette>
#include <QProcess>
#include <QFileInfo>

#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

int static familyIndex;

int static familyIndexControl;

// Types of Groups
QStringList static videoFamily = {"Select Group...","Rockstar","AGB","CAP","ME7mil"};
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




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ui->centralWidget->setStyleSheet("background-color: rgb(217,217,217);");

    //qDebug() << ui->familyCB->currentText();

    // Set default values and properties to precontrol tables widgets
    setDefaultParametersTW();
    setDefaultTempTW();
    // Set default values and properties to control tables widgets
    setDefaultParametersTWC();

    // Set solder paste combox boxes unenabled because this is selected automatically
    ui->solderPasteCB->setEnabled(false);
    ui->solderPasteCBC->setEnabled(false);

    //ui->controlTabW->

}


MainWindow::~MainWindow()
{
    delete ui;
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
            ui->modelCB->addItems(videoME7mil);
            setParameterTW(2);
            ui->solderPasteCB->setCurrentIndex(2);

        }else if (index == 4) {
            ui->modelCB->addItems(videoCAP);
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

    /*
     * This is the method to select the pdf file...
     * It needs work on it...
     * Now it is just a sample
     *
     */

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Jajaja"), "/Users/Fer/Downloads",
        tr("All Files (*)"));
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
            qDebug() << correctfileName;
            qDebug() << Name;
            qDebug() << paste;
            QDir dir("C:/Users/Oliver y Ale/Desktop/sTostado-master/DAtaExtractionAndStatisticsCalculation");
            //se obtiene el path de donde esta ubicada la aplicacion si se ponen los scripts python en el mismo lugar funciona,
            QString dir1(QCoreApplication::applicationDirPath ());
            QFileInfo info(dir1, "PreControProcessStatisticsCalculationCompleted.py");
            qDebug() << dir.exists() << info.exists();
            QProcess process;
            process.setProcessChannelMode(QProcess::MergedChannels);
            process.start("python.exe", QStringList()<< info.absoluteFilePath() << correctfileName << Name << paste);
            qDebug() << process.atEnd();
            process.waitForFinished(-1);
            QString output(process.readAll());
            
            //Obtencion de datos del output del script python.
            int indexTempData = output.indexOf("Temperature Data: ",1);
            QString TempData = output.mid(indexTempData,68);
            QString TempData1 = TempData.mid(18,4);
            QString TempData2 = TempData.mid(23,4);
            QString TempData3 = TempData.mid(28,4);
            QString TempData4 = TempData.mid(33,4);
            QString TempData5 = TempData.mid(38,4);
            QString TempData6 = TempData.mid(43,4);
            QString TempData7 = TempData.mid(48,4);
            QString TempData8 = TempData.mid(53,4);
            QString TempData9 = TempData.mid(58,4);
            QString TempData10 = TempData.mid(63,4);

            int indexPositiveSl = output.indexOf("Positive Slope: ",1);
            QString PositiveSl = output.mid(indexPositiveSl,40);
            QString PositiveSl1 = PositiveSl.mid(16,4);
            QString PositiveSl2 = PositiveSl.mid(21,4);
            QString PositiveSl3 = PositiveSl.mid(26,4);
            QString PositiveSl4 = PositiveSl.mid(31,4);
            QString PositiveSl5 = PositiveSl.mid(36,4);

            int indexTimeAboveL = output.indexOf("Time Above Liquids: ",1);
            QString TimeAboveL = output.mid(indexTimeAboveL,50);
            QString TimeAboveL1 = TimeAboveL.mid(20,5);
            QString TimeAboveL2 = TimeAboveL.mid(26,5);
            QString TimeAboveL3 = TimeAboveL.mid(32,5);
            QString TimeAboveL4 = TimeAboveL.mid(38,5);
            QString TimeAboveL5 = TimeAboveL.mid(44,5);

            int indexPeakTemp = output.indexOf("Peak Temperature: ",1);
            QString PeakTemp = output.mid(indexPeakTemp,48);
            QString PeakTemp1 = PeakTemp.mid(18,5);
            QString PeakTemp2 = PeakTemp.mid(24,5);
            QString PeakTemp3 = PeakTemp.mid(30,5);
            QString PeakTemp4 = PeakTemp.mid(36,5);
            QString PeakTemp5 = PeakTemp.mid(42,5);

            /*qDebug() << PeakTemp;
            qDebug() << PeakTemp1;
            qDebug() << PeakTemp2;
            qDebug() << PeakTemp3;
            qDebug() << PeakTemp4;
            qDebug() << PeakTemp5;*/


            /*qDebug() << TimeAboveL;
            qDebug() << TimeAboveL1;
            qDebug() << TimeAboveL2;
            qDebug() << TimeAboveL3;
            qDebug() << TimeAboveL4;
            qDebug() << TimeAboveL5;*/

            /*qDebug() << PositiveSl1;
            qDebug() << PositiveSl2;
            qDebug() << PositiveSl3;
            qDebug() << PositiveSl4;
            qDebug() << PositiveSl5;*/

         /* qDebug() << TempData;
            qDebug() << TempData1;
            qDebug() << TempData2;
            qDebug() << TempData3;
            qDebug() << TempData4;
            qDebug() << TempData5;
            qDebug() << TempData6;
            qDebug() << TempData7;
            qDebug() << TempData8;
            qDebug() << TempData9;
            qDebug() << TempData10;*/
            qDebug() << output;
            ui->textEdit->setText(output);

            QFile file(fileName);

            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

            QTextStream in(&file);
            //auxGraph.node.clear();   // clear existing contacts

            while (!in.atEnd()) {
                //auxGraph.adj.clear();   // clear existing contacts
                //in >> auxGraph;
            }

            /*
            if (auxGraph.node.isEmpty()) {
                QMessageBox::information(this, tr("No grafo en el archivo"),
                    tr("The file you are attempting to open contains no info."));
            }
            */
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
            QStringList actualValues = {"30","90","230","250","0.8","1.5"};
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
    QStringList riseValues = getRiseSlopeValues(); // getting the actual data from the acceptable parameters table

    //S etting the QLineSeries needed
    QFont labelFont("Helvetica", 15, QFont::Bold); // fonts for all the labels

    // Setting Specification Limits (LSL & USL)
    QPen pen(Qt::yellow);
    pen.setWidth(3);

    // LSL line (Lower Specification Limit)
    QLineSeries *LSLseries = new QLineSeries();
    LSLseries->setName("LSL");
    LSLseries->setPen(pen);
    LSLseries->setPointLabelsVisible(true);
    LSLseries->setPointLabelsClipping(true);
    LSLseries->setPointLabelsFont(labelFont);
    LSLseries->setPointLabelsFormat("@yPoint");
    LSLseries->append(1, riseValues[0].toDouble());
    LSLseries->append(5, riseValues[0].toDouble());


    // USL line (Upper Specification Limit)
    QLineSeries *USLseries = new QLineSeries();
    USLseries->setName("USL");
    USLseries->setPen(pen);
    USLseries->setPointLabelsVisible(true);
    USLseries->setPointLabelsClipping(true);
    USLseries->setPointLabelsFont(labelFont);
    USLseries->setPointLabelsFormat("@yPoint");
    USLseries->append(1, riseValues[1].toDouble());
    USLseries->append(5, riseValues[1].toDouble());


    // Setting the axis for the chart
    // Axis X
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Termocouples");
    axisX->setRange(0, 6);
    axisX->setTickCount(7);
    axisX->setLabelFormat("%d");

    // Axis Y
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Measurements (Cº/sec)");
    axisY->setMax(3);
    axisY->setTickCount(5);
    axisY->setLabelFormat("%.1f");


    // Creating the chart
    QChart *PSChart = new QChart();
    PSChart->setTitle("Positive Slope Chart");
    PSChart->legend()->hide();
    // Adding the LSLseries
    PSChart->addSeries(LSLseries);
    PSChart->setAxisX(axisX,LSLseries);
    PSChart->setAxisY(axisY,LSLseries);
    // Adding the USLseries
    PSChart->addSeries(USLseries);
    PSChart->setAxisX(axisX,USLseries);
    PSChart->setAxisY(axisY,USLseries);

    // Initializing a chart view with our setted PSChart
    QChartView *positiveSlopeCV = new QChartView(PSChart);
    positiveSlopeCV->setRenderHint(QPainter::Antialiasing);


    QTableWidget *positiveSlopeTW = new QTableWidget(5, 6, this);
    QStringList tableHeadersTitles = {"Termo-\ncouple","Positive\n Slope","Minimum\nrise slope","Maximum\nrise slope","UPCL","LPCL"};
    positiveSlopeTW->setHorizontalHeaderLabels(tableHeadersTitles);
    positiveSlopeTW->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *positiveSlopeVHV = positiveSlopeTW->verticalHeader();
    positiveSlopeVHV->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *positiveSlopeHHV = positiveSlopeTW -> horizontalHeader();
    positiveSlopeHHV->setSectionResizeMode(QHeaderView::Stretch);


    QVBoxLayout *tableLabelLayout = new QVBoxLayout;
    QLabel *titleLabel = new QLabel;
    QFont titleFont("Helvetica", 16, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setText("Reflow Results");
    titleLabel->setAlignment(Qt::AlignCenter);

    tableLabelLayout->addWidget(titleLabel);
    tableLabelLayout->addWidget(positiveSlopeTW);

    //makeWindow();
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(positiveSlopeCV);
    layout->addLayout(tableLabelLayout);


    // Set layout in QWidget
    QWidget *posSlopeWindow = new QWidget();
    posSlopeWindow->setLayout(layout);
    posSlopeWindow->setWindowTitle("Positive Slope Results");
    posSlopeWindow->resize(800,360);
    posSlopeWindow->show();

}

//Graph and table showed by clicking TAL Results Button
void MainWindow::on_TALPB_clicked()
{
    QStringList timeValues = getTimeAboveValues(); //getting value from acceptable parameters.

     //setting the font for the labels the font for all labels will be the same.
     QFont labelFont("Helvetica", 15, QFont::Bold); // fonts for all the labels

     //setting the color for the line in the graph also setting the width of this line.
     QPen pen(Qt::yellow);
     pen.setWidth(3);

     //Lower limit
     QLineSeries *LSLseries = new QLineSeries();
     LSLseries->setName("LSL");
     LSLseries->setPen(pen);
     LSLseries->setPointLabelsVisible(true);
     LSLseries->setPointLabelsClipping(false);
     LSLseries->setPointLabelsFont(labelFont);
     LSLseries->setPointLabelsFormat("@yPoint");
     LSLseries->append(1, timeValues[0].toDouble());
     LSLseries->append(5, timeValues[0].toDouble());

     //Upper limit
     QLineSeries *USLseries = new QLineSeries();
     USLseries->setName("USL");
     USLseries->setPen(pen);
     USLseries->setPointLabelsVisible(true);
     USLseries->setPointLabelsClipping(false);
     USLseries->setPointLabelsFont(labelFont);
     USLseries->setPointLabelsFormat("@yPoint");
     USLseries->append(1, timeValues[1].toDouble());
     USLseries->append(5, timeValues[1].toDouble());

     //setting the label of the x axis and the domain.
     QValueAxis *axisX = new QValueAxis;
     axisX->setTitleText("Termocouples");
     axisX->setRange(0, 6);
     axisX->setTickCount(7);
     axisX->setLabelFormat("%d");

     // Setting the label of the y axis and the range
     QValueAxis *axisY = new QValueAxis;
     axisY->setTitleText("Measurements (sec)");
     axisY->setMax(120);
     axisY->setTickCount(5);
     axisY->setLabelFormat("%.1f");

     // setting the chart
     QChart *PSChart = new QChart();
     PSChart->setTitle("TAL chart");
     PSChart->legend()->hide();
     // Adding the LSLseries
     PSChart->addSeries(LSLseries);
     PSChart->setAxisX(axisX,LSLseries);
     PSChart->setAxisY(axisY,LSLseries);
     // Adding the USLseries
     PSChart->addSeries(USLseries);
     PSChart->setAxisX(axisX,USLseries);
     PSChart->setAxisY(axisY,USLseries);

     // Initializing a chart view so later we can add it and make it visible.
     QChartView *TALCV = new QChartView(PSChart);
     TALCV->setRenderHint(QPainter::Antialiasing);

     //creating new table next to the graph.
     QTableWidget *TALTW = new QTableWidget(5, 6, this);
     QStringList tableHeadersTitles = {"Termo-\ncouple","TAL","Minimum time\nabove liquid ","Maximum time\nabove liquid","UPCL","LPCL"};
     TALTW->setHorizontalHeaderLabels(tableHeadersTitles);
     TALTW->setEditTriggers(QAbstractItemView::NoEditTriggers);

     QHeaderView *TALVHV = TALTW->verticalHeader();
     TALVHV->setSectionResizeMode(QHeaderView::Stretch);
     QHeaderView *TALHHV = TALTW -> horizontalHeader();
     TALHHV->setSectionResizeMode(QHeaderView::Stretch);

     //Setting the labels for the chart next to the graph.
     QVBoxLayout *tableLabelLayout = new QVBoxLayout;
     QLabel *titleLabel = new QLabel;
     QFont titleFont("Helvetica", 16, QFont::Bold);
     titleLabel->setFont(titleFont);
     titleLabel->setText("Reflow Results");
     titleLabel->setAlignment(Qt::AlignCenter);

     tableLabelLayout->addWidget(titleLabel);
     tableLabelLayout->addWidget(TALTW);

     //makeWindow();
     QHBoxLayout *layout = new QHBoxLayout;
     layout->addWidget(TALCV);
     layout->addLayout(tableLabelLayout);

     // Set layout so we can se it in the interface.
     QWidget *posSlopeWindow = new QWidget();
     posSlopeWindow->setLayout(layout);
     posSlopeWindow->setWindowTitle("TAL Results");
     posSlopeWindow->resize(800,360);
     posSlopeWindow->show();

}

//Graph and table showed by clicking Peak Temperature Results Button
void MainWindow::on_peakTempPB_clicked()
{
    QStringList peakTempValues = getPeakTempValues();

    //setting the font for the labels the font for all labels will be the same.
    QFont labelFont("Helvetica", 15, QFont::Bold); // fonts for all the labels

    //setting the color for the line in the graph also setting the width of this line.
    QPen pen(Qt::green);
    pen.setWidth(3);

    //Lower limit
    QLineSeries *LSLseries = new QLineSeries();
    LSLseries->setName("LSL");
    LSLseries->setPen(pen);
    LSLseries->setPointLabelsVisible(true);
    LSLseries->setPointLabelsClipping(true);
    LSLseries->setPointLabelsFont(labelFont);
    LSLseries->setPointLabelsFormat("@yPoint");
    LSLseries->append(1, peakTempValues[0].toDouble());
    LSLseries->append(5, peakTempValues[0].toDouble());

    //Upper limit
    QLineSeries *USLseries = new QLineSeries();
    USLseries->setName("USL");
    USLseries->setPen(pen);
    USLseries->setPointLabelsVisible(true);
    USLseries->setPointLabelsClipping(true);
    USLseries->setPointLabelsFont(labelFont);
    USLseries->setPointLabelsFormat("@yPoint");
    USLseries->append(1, peakTempValues[1].toDouble());
    USLseries->append(5, peakTempValues[1].toDouble());


    //setting the label of the x axis and the domain.
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Termocouples");
    axisX->setRange(0, 6);
    axisX->setTickCount(7);
    axisX->setLabelFormat("%d");

    // Setting the label of the y axis and the range
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Measurements (Cº)");
    axisY->setMax(300);
    axisY->setMin(200);
    axisY->setTickCount(5);
    axisY->setLabelFormat("%.1f");

    // setting the chart
    QChart *PSChart = new QChart();
    PSChart->setTitle("Peak Temperature chart");
    PSChart->legend()->hide();

    // Adding the LSLseries
    PSChart->addSeries(LSLseries);
    PSChart->setAxisX(axisX,LSLseries);
    PSChart->setAxisY(axisY,LSLseries);

    // Adding the USLseries
    PSChart->addSeries(USLseries);
    PSChart->setAxisX(axisX,USLseries);
    PSChart->setAxisY(axisY,USLseries);

    // Initializing a chart view so later we can add it and make it visible.
    QChartView *PeakTempCV = new QChartView(PSChart);
    PeakTempCV->setRenderHint(QPainter::Antialiasing);

    //creating new table next to the graph.
    QTableWidget *PeakTempTW = new QTableWidget(5, 6, this);
    QStringList tableHeadersTitles = {"Termo-\ncouple","Peak Temperature","Minimum Peak\nTemperature ","Maximum peak\nTemperature","UPCL","LPCL"};
    PeakTempTW->setHorizontalHeaderLabels(tableHeadersTitles);
    PeakTempTW->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *PeakTempVHV = PeakTempTW->verticalHeader();
    PeakTempVHV->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *PeakTempHHV = PeakTempTW -> horizontalHeader();
    PeakTempHHV->setSectionResizeMode(QHeaderView::Stretch);

    //Setting the labels for the chart next to the graph.
    QVBoxLayout *tableLabelLayout = new QVBoxLayout;
    QLabel *titleLabel = new QLabel;
    QFont titleFont("Helvetica", 16, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setText("Reflow Results");
    titleLabel->setAlignment(Qt::AlignCenter);

    tableLabelLayout->addWidget(titleLabel);
    tableLabelLayout->addWidget(PeakTempTW);

    //makeWindow();
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(PeakTempCV);
    layout->addLayout(tableLabelLayout);


    // Set layout so we can se it in the interface.
    QWidget *posSlopeWindow = new QWidget();
    posSlopeWindow->setLayout(layout);
    posSlopeWindow->setWindowTitle("Peak Temperature Results");
    posSlopeWindow->resize(800,360);
    posSlopeWindow->show();
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
}



/* **************************************************
 * Start the code for the control UI part
 *
 */

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

    for (int i = 0; i<10; i++) {
        //ui.tableWidgetTextureLibrary->setHorizontalHeaderItem(0, new QTableWidgetItem("Prueba"));
        //ui.tableWidgetTextureLibrary->horizontalHeaderItem(0)->setText("Whatever");

        //QString value = QString::number(i);
        //QTableWidgetItem  *auxCellTWI = new QTableWidgetItem(value);
        //auxCellTWI->setTextAlignment(Qt::AlignCenter);

        if (i < index) {
            ui->profilesTWC->setRowHidden(i, false);
        } else {
            ui->profilesTWC->setRowHidden(i, true);
        }

        //qDebug() << auxCellTWI->text();
        //ui->profilesTWC->verticalHeaderItem(i)->setText(value);
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
            ui->modelCBC->addItems(videoME7mil);
            setParameterTWC(2);
            ui->solderPasteCBC->setCurrentIndex(2);

        }else if (index == 4) {
            ui->modelCBC->addItems(videoCAP);
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
    //QString value = ui->profileCBC->currentText();
    if (index == 0) {
        updateHeaderParametersTWC(10);
    } else {
        updateHeaderParametersTWC(index + 3);
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
            QStringList actualValues = {"30","90","230","250"};
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
}

