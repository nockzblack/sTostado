#include "auxwindow.h"
#include "ui_mainwindow.h"


#include <QStringList>
#include <QString>
#include <QtWidgets>
#include <QTableWidget>
#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>


QT_CHARTS_USE_NAMESPACE

auxwindow::auxwindow()
{

}


auxwindow::auxwindow(QStringList values, QStringList controlLimits, QStringList limitsValues, QString title, int lenOfData, QString scale, QStringList charLimits) {

    int len = lenOfData;


    //Setting the font for the labels
    QFont labelFont("Arial", 15, QFont::Bold);

    //Setting Pens
    QPen specificLimitPen(Qt::yellow);
    specificLimitPen.setWidth(2);

    QPen controlLimitPen(Qt::green);
    controlLimitPen.setWidth(2);

    QPen dataPen(Qt::blue);
    dataPen.setWidth(2);


    QLineSeries *dataSeries = new QLineSeries();
    dataSeries->setName("Results");
    dataSeries->setPen(dataPen);
    dataSeries->setPointLabelsVisible(true);
    dataSeries->setPointLabelsClipping(false);
    dataSeries->setPointLabelsFont(labelFont);
    dataSeries->setPointLabelsFormat("@yPoint");

    for(int i = 0; i<len; ++i) {
        dataSeries->append(i+1, values[i].toDouble());
    }


    QLineSeries *UPSLSeries = new QLineSeries();
    UPSLSeries->setName("UPSL");
    UPSLSeries->setPen(controlLimitPen);
    UPSLSeries->setPointLabelsVisible(false);
    UPSLSeries->setPointLabelsClipping(false);
    UPSLSeries->setPointLabelsFont(labelFont);
    UPSLSeries->setPointLabelsFormat("@yPoint");
    UPSLSeries->append(1, controlLimits[1].toDouble());
    UPSLSeries->append(len, controlLimits[1].toDouble());


    QLineSeries *LPSLSeries = new QLineSeries();
    LPSLSeries->setName("LPSL");
    LPSLSeries->setPen(controlLimitPen);
    LPSLSeries->setPointLabelsVisible(false);
    LPSLSeries->setPointLabelsClipping(false);
    LPSLSeries->setPointLabelsFont(labelFont);
    LPSLSeries->setPointLabelsFormat("@yPoint");
    LPSLSeries->append(1, controlLimits[0].toDouble());
    LPSLSeries->append(len, controlLimits[0].toDouble());


    // LSL line (Lower Specification Limit)
    QLineSeries *LSLseries = new QLineSeries();
    LSLseries->setName("LSL");
    LSLseries->setPen(specificLimitPen);
    LSLseries->setPointLabelsVisible(true);
    LSLseries->setPointLabelsClipping(false);
    LSLseries->setPointLabelsFont(labelFont);
    LSLseries->setPointLabelsFormat("@yPoint");
    LSLseries->append(1, limitsValues[0].toDouble());
    LSLseries->append(len, limitsValues[0].toDouble());


    // USL line (Upper Specification Limit)
    QLineSeries *USLseries = new QLineSeries();
    USLseries->setName("USL");
    USLseries->setPen(specificLimitPen);
    USLseries->setPointLabelsVisible(true);
    USLseries->setPointLabelsClipping(false);
    USLseries->setPointLabelsFont(labelFont);
    USLseries->setPointLabelsFormat("@yPoint");
    USLseries->append(1, limitsValues[1].toDouble());
    USLseries->append(len, limitsValues[1].toDouble());


    // Setting the axis for the chart
    // Axis X
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Thermocouples");
    axisX->setRange(0, len+1);
    axisX->setTickCount(len+2);
    axisX->setLabelFormat("%d");

    // Axis Y
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText(scale);
    axisY->setMin(charLimits[0].toInt());
    axisY->setMax(charLimits[1].toInt());
    axisY->setTickCount(5);
    axisY->setLabelFormat("%.1f");

    // Creating the chart
    QChart *auxChart = new QChart();
    auxChart->setTitle(title);
    auxChart->legend()->setAlignment(Qt::AlignBottom);

    // Adding Series
    auxChart->addSeries(LSLseries);
    auxChart->addSeries(USLseries);
    auxChart->addSeries(dataSeries);
    auxChart->addSeries(UPSLSeries);
    auxChart->addSeries(LPSLSeries);

    auxChart->setAxisX(axisX,dataSeries);
    auxChart->setAxisY(axisY,dataSeries);

    auxChart->setAxisX(axisX,LSLseries);
    auxChart->setAxisY(axisY,LSLseries);

    auxChart->setAxisX(axisX,USLseries);
    auxChart->setAxisY(axisY,USLseries);

    auxChart->setAxisX(axisX,UPSLSeries);
    auxChart->setAxisY(axisY,UPSLSeries);

    auxChart->setAxisX(axisX,LPSLSeries);
    auxChart->setAxisY(axisY,LPSLSeries);

    // Final settigs for the chart
    QChartView *auxChartView = new QChartView(auxChart);
    auxChartView->setRenderHint(QPainter::Antialiasing);


    // Creating a new QTableWidget
    QTableWidget *auxTableWidget = new QTableWidget(len, 6);

    QStringList tableHeadersTitles = {"Thermo-\ncouple","Positive\n Slope","Minimum\nrise slope","Maximum\nrise slope","UPCL","LPCL"};
    auxTableWidget->setHorizontalHeaderLabels(tableHeadersTitles);
    auxTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *auxTableVHV = auxTableWidget->verticalHeader();
    auxTableVHV->setSectionResizeMode(QHeaderView::Stretch);
    QHeaderView *auxTableHHV = auxTableWidget -> horizontalHeader();
    auxTableHHV->setSectionResizeMode(QHeaderView::Stretch);


    QStringList PSlParameters = {limitsValues[0],limitsValues[1], controlLimits[1], controlLimits[0]};

    for (int i = 0; i<len; ++i) {
        for (int j = 0; j<6; ++j) {
            QTableWidgetItem  *auxCellTWP = new QTableWidgetItem();
            if (j == 0) {
                QString value = QString::number(i+1);
                auxCellTWP->setText(value);
            } else if (j == 1) {
                auxCellTWP->setText(values[i]);
            } else {
                auxCellTWP->setText(PSlParameters[j-2]);
            }
            auxCellTWP->setTextAlignment(Qt::AlignCenter);
            auxTableWidget->setItem(i,j, auxCellTWP);
        }
    }

    // Making layout in order to make a organized window
    QVBoxLayout *tableLabelLayout = new QVBoxLayout;
    QLabel *titleLabel = new QLabel;
    QFont titleFont("Helvetica", 16, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setText("Reflow Results");
    titleLabel->setAlignment(Qt::AlignCenter);

    tableLabelLayout->addWidget(titleLabel);
    tableLabelLayout->addWidget(auxTableWidget);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(auxChartView);
    layout->addLayout(tableLabelLayout);

    QWidget *auxWindow = new QWidget();
    auxWindow->setLayout(layout);
    auxWindow->setWindowTitle(title);
    auxWindow->resize(900,450);

    window = auxWindow;
}


QWidget* auxwindow::getWindow() {
    return window;
}
