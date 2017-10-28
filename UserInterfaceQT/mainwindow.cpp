#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>

#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

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

    //ui->buttomsLayout->setSizeConstraint(QLayout::SetFixedSize);
    //qDebug() << ui->familyCB->currentText();
    //ui->parametersTW->setHorizontalHeader(QHeaderView* );
    //ui->parametersTW->setHorizontalHeaderItem(0, new QTableWidgetItem("Prueba"));

    //ui->parametersTW->resizeRowsToContents();
    //ui->parametersTW->resizeColumnsToContents();
    //ui->parametersTW->adjustSize();

    // Set default values to parameters TW
    ui->parametersTW->resizeColumnToContents(0);
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

    QTableWidgetItem  *minimumTime = new QTableWidgetItem(values[0]);
    QTableWidgetItem  *maximumTime = new QTableWidgetItem(values[1]);
    QTableWidgetItem  *minimumPeak = new QTableWidgetItem(values[2]);
    QTableWidgetItem  *maximumPeak = new QTableWidgetItem(values[3]);
    QTableWidgetItem  *minimumRise = new QTableWidgetItem(values[4]);
    QTableWidgetItem  *maximumRise = new QTableWidgetItem(values[5]);

    ui->parametersTW->setItem(0,0, minimumTime);
    ui->parametersTW->setItem(0,1, maximumTime);
    ui->parametersTW->setItem(0,2, minimumPeak);
    ui->parametersTW->setItem(0,3, maximumPeak);
    ui->parametersTW->setItem(0,4, minimumRise);
    ui->parametersTW->setItem(0,5, maximumRise);
}
