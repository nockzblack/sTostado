#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <QTableWidget>

#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

int static familyIndex;

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
QStringList static dsrLeadFree = {"Select Model...", "598020-002", "598036-002","594834-001","597466-001","596516-001","612181-001"};
QStringList static dsrLegacyLead = {"Select Model...", "573945-001", "573329-003", "572372-004", "591547-001", "573946-001", "581255-001", "581305-001"};
// Pics Family
QStringList static picsGroup_Pics = {"Select Model...", "ARCT03327", "ARCT04573", "ARCT04398", "ARCT03313", "ARCT03753", "ARCT03321", "ARCT02469", "ARCT03745", "ARCT04679", "ARCT04575", "ARCT03323", "ARCT02433", "ARCT03749", "ARCT04399", "ARCT04475"};
// E6mil Family
QStringList static e6milGroup_E6mil = {"Select Model...", "ARCT03477", "ARCT03309", "ARCT02473", "ARCT03999"};




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //qDebug() << ui->familyCB->currentText();



    // Set default values to parameters TW
    QHeaderView *header = ui->parametersTW ->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *OtherHeader = ui->parametersTW ->verticalHeader();
    OtherHeader->setSectionResizeMode(QHeaderView::Stretch);
    ui->parametersTW->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList actualValues = {"***","***","***","***","***","***"};
    updateTable(actualValues);

}

MainWindow::~MainWindow()
{
    delete ui;
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
        } else if (index == 2) {
            ui->modelCB->addItems(videoAGB);
        } else if (index == 3) {
            ui->modelCB->addItems(videoME7mil);
        }else if (index == 4) {
            ui->modelCB->addItems(videoCAP);
        }
        break;

    case(2):
        if (index == 1){
            ui->modelCB->addItems(dsrLeadFree);
        } else if (index==2){
            ui->modelCB->addItems(dsrLegacyLead);
        }
       break;

    case(3):
        if (index == 1){
            ui->modelCB->addItems(picsGroup_Pics);
        }
        break;
    case(4):
        if (index == 1){
            ui->modelCB->addItems(e6milGroup_E6mil);
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

    if (fileName.isEmpty())
            return;
        else {

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

void MainWindow::on_solderPasteCB_activated(int index)
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
            updateTable(actualValues);
        }
        break;


        case 2:
        {
            QStringList actualValues = {"30","100","230","262","0.5","2.5"};
            updateTable(actualValues);
         }
        break;

        case 3:
        {
            QStringList actualValues = {"30","90","232","255","0.8","1.5"};
            updateTable(actualValues);
         }
        break;

        case 4:
        {
            QStringList actualValues = {"30","90","230","250","0.8","1.5"};
            updateTable(actualValues);
         }
        break;

        case 5:
        {
            QStringList actualValues = {"30","90","208","228","0.5","2"};
            updateTable(actualValues);
         }
        break;
    }
}

void MainWindow::updateTable(QStringList &values) {

    // This just create new items with the information on the list values and
    // put it into the table.
    for (int i = 0; i<6; i++) {
        QTableWidgetItem  *auxCellTWI = new QTableWidgetItem(values[i]);
        auxCellTWI->setTextAlignment(Qt::AlignCenter);
        ui->parametersTW->setItem(0,i, auxCellTWI);
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

void MainWindow::on_positiveSlopePB_clicked()
{
    QStringList riseValues = getRiseSlopeValues(); // getting the actual data from the acceptable parameters table

    //S etting the QLineSeries needed
    QFont labelFont("Helvetica", 15, QFont::Bold); // fonts for all the labels

    // Setting Specification Limits (LSL & USL)
    QPen pen(Qt::green);
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

//graph displayed by clicking TAL result button.
void MainWindow::on_TALPB_clicked()
{
     QStringList timeValues = getTimeAboveValues(); //getting value from acceptable parameters.

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
      LSLseries->append(1, timeValues[0].toDouble());
      LSLseries->append(5, timeValues[0].toDouble());

      //Upper limit
      QLineSeries *USLseries = new QLineSeries();
      USLseries->setName("USL");
      USLseries->setPen(pen);
      USLseries->setPointLabelsVisible(true);
      USLseries->setPointLabelsClipping(true);
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

//Graph showed by clicking PeakTemperature Button
void MainWindow::on_peakTempPB_clicked()
{
    QStringList peakTempValues = getPeakTempValues();

    //setting the font for the labels the font for all labels will be the same.
    QFont labelFont("Helvetica", 15, QFont::Bold); // fonts for all the labels

    //setting the color for the line in the graph also setting the width of this line.
    QPen pen(Qt::green);
    pen.setWidth(3);

    //Lower limit0
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


