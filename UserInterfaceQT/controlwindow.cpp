#include "controlwindow.h"


#include <QStringList>
#include <QString>
#include <QtWidgets>
#include <QTableWidget>
#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>


QT_CHARTS_USE_NAMESPACE

controlwindow::controlwindow()
{

}


controlwindow::controlwindow(QStringList XValues, QStringList RValues, QStringList controlLimits, QString title, QStringList charLimits)
{

    //setting the font for the labels the font for all labels will be the same.
    QFont labelFont("Arial", 15, QFont::Bold); // fonts for all the labels

    //setting the color for the line in the graph also setting the width of this line.
    QPen UCLPen(Qt::red);
    UCLPen.setWidth(3);
    QPen CLPen(Qt::green);
    CLPen.setWidth(3);
    QPen LCLPen(Qt::magenta);
    LCLPen.setWidth(3);
    QPen dataPen(Qt::blue);
    dataPen.setWidth(3);


    // Making X-Bar Chart

    int len = XValues.length();

    //Upper Limit Serie
    QLineSeries *UCLXSerie = new QLineSeries();
    UCLXSerie->setName("UCLX");
    UCLXSerie->setPen(UCLPen);
    UCLXSerie->setPointLabelsVisible(true);
    UCLXSerie->setPointLabelsClipping(false);
    UCLXSerie->setPointLabelsFont(labelFont);
    UCLXSerie->setPointLabelsFormat("@yPoint");
    UCLXSerie->append(1, controlLimits[2].toDouble());
    UCLXSerie->append(len, controlLimits[2].toDouble());


    //Lower Limit Serie
    QLineSeries *LCLXSerie = new QLineSeries();
    LCLXSerie->setName("LCLX");
    LCLXSerie->setPen(LCLPen);
    LCLXSerie->setPointLabelsVisible(true);
    LCLXSerie->setPointLabelsClipping(false);
    LCLXSerie->setPointLabelsFont(labelFont);
    LCLXSerie->setPointLabelsFormat("@yPoint");
    LCLXSerie->append(1, controlLimits[0].toDouble());
    LCLXSerie->append(len, controlLimits[0].toDouble());


    //Central Limit Serie
    QLineSeries *CLXSerie = new QLineSeries();
    CLXSerie->setName("CLX");
    CLXSerie->setPen(CLPen);
    CLXSerie->setPointLabelsVisible(false);
    CLXSerie->setPointLabelsClipping(false);
    CLXSerie->setPointLabelsFont(labelFont);
    CLXSerie->setPointLabelsFormat("@yPoint");
    CLXSerie->append(1, controlLimits[1].toDouble());
    CLXSerie->append(len, controlLimits[1].toDouble());


    // Data Series
    QLineSeries *dataXSerie = new QLineSeries();
    dataXSerie->setName("Peak Temp. Aver.");
    dataXSerie->setPen(dataPen);
    dataXSerie->setPointLabelsVisible(true);
    dataXSerie->setPointLabelsClipping(false);
    dataXSerie->setPointLabelsFont(labelFont);
    dataXSerie->setPointLabelsFormat("@yPoint");

    for (int i=0; i<len; ++i) {
        dataXSerie->append(i+1, XValues[i].toDouble());
    }

    //setting the label of the x axis and the domain.
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Profiles");
    axisX->setRange(0, len+1);
    axisX->setTickCount(len+2);
    axisX->setLabelFormat("%d");

    // Setting the label of the y axis and the range
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText(title);
    axisY->setMin(charLimits[0].toInt());
    axisY->setMax(charLimits[1].toInt());
    axisY->setTickCount(5);
    axisY->setLabelFormat("%.1f");

    // setting the chart
    QChart *TALChart = new QChart();
    TALChart->setTitle(title);
    TALChart->legend()->setAlignment(Qt::AlignBottom);

    // Adding Series
    TALChart->addSeries(UCLXSerie);
    TALChart->addSeries(CLXSerie);
    TALChart->addSeries(LCLXSerie);
    TALChart->addSeries(dataXSerie);

    TALChart->setAxisX(axisX,UCLXSerie);
    TALChart->setAxisY(axisY,UCLXSerie);

    TALChart->setAxisX(axisX,CLXSerie);
    TALChart->setAxisY(axisY,CLXSerie);

    TALChart->setAxisX(axisX,LCLXSerie);
    TALChart->setAxisY(axisY,LCLXSerie);

    TALChart->setAxisX(axisX,dataXSerie);
    TALChart->setAxisY(axisY,dataXSerie);


    // Initializing a chart view so later we can add it and make it visible.
    QChartView *TALCV = new QChartView(TALChart);
    TALCV->setRenderHint(QPainter::Antialiasing);




    // Making Variability Chart

    int varLen = RValues.length();

    //Upper Limit Serie
    QLineSeries *UCLRSerie = new QLineSeries();
    UCLRSerie->setName("UCLR");
    UCLRSerie->setPen(UCLPen);
    UCLRSerie->setPointLabelsVisible(true);
    UCLRSerie->setPointLabelsClipping(false);
    UCLRSerie->setPointLabelsFont(labelFont);
    UCLRSerie->setPointLabelsFormat("@yPoint");
    UCLRSerie->append(1, controlLimits[5].toDouble());
    UCLRSerie->append(varLen, controlLimits[5].toDouble());


    //Lower Limit Series
    QLineSeries *LCLRSerie = new QLineSeries();
    LCLRSerie->setName("LCLR");
    LCLRSerie->setPen(LCLPen);
    LCLRSerie->setPointLabelsVisible(true);
    LCLRSerie->setPointLabelsClipping(false);
    LCLRSerie->setPointLabelsFont(labelFont);
    LCLRSerie->setPointLabelsFormat("@yPoint");
    LCLRSerie->append(1, controlLimits[3].toDouble());
    LCLRSerie->append(varLen, controlLimits[3].toDouble());


    //Central Limit Series
    QLineSeries *CLRSerie = new QLineSeries();
    CLRSerie->setName("CLR");
    CLRSerie->setPen(CLPen);
    CLRSerie->setPointLabelsVisible(false);
    CLRSerie->setPointLabelsClipping(false);
    CLRSerie->setPointLabelsFont(labelFont);
    CLRSerie->setPointLabelsFormat("@yPoint");
    CLRSerie->append(1, controlLimits[4].toDouble());
    CLRSerie->append(varLen, controlLimits[4].toDouble());


    // Data Series
    QLineSeries *dataRSerie = new QLineSeries();
    dataRSerie->setName("Deviation");
    dataRSerie->setPen(dataPen);
    dataRSerie->setPointLabelsVisible(true);
    dataRSerie->setPointLabelsClipping(false);
    dataRSerie->setPointLabelsFont(labelFont);
    dataRSerie->setPointLabelsFormat("@yPoint");

    for (int i=0; i<varLen; ++i) {
        dataRSerie->append(i+1, RValues[i].toDouble());
    }


    //setting the label of the x axis and the domain.
    QValueAxis *axisXR = new QValueAxis;
    axisXR->setTitleText("Profiles");
    axisXR->setRange(0, varLen+1);
    axisXR->setTickCount(varLen+2);
    axisXR->setLabelFormat("%d");

    // Setting the label of the y axis and the range
    QValueAxis *axisYR = new QValueAxis;
    axisYR->setTitleText("Variability");
    axisYR->setMin(charLimits[2].toDouble());
    axisYR->setMax(charLimits[3].toDouble());
    axisYR->setTickCount(5);
    axisYR->setLabelFormat("%.1f");

    // setting the chart
    QChart *varChart = new QChart();
    varChart->setTitle("Variability (R Chart)");
    varChart->legend()->setAlignment(Qt::AlignBottom);


    // Adding Series
    varChart->addSeries(UCLRSerie);
    varChart->addSeries(CLRSerie);
    varChart->addSeries(LCLRSerie);
    varChart->addSeries(dataRSerie);

    varChart->setAxisX(axisXR,UCLRSerie);
    varChart->setAxisY(axisYR,UCLRSerie);

    varChart->setAxisX(axisXR,CLRSerie);
    varChart->setAxisY(axisYR,CLRSerie);

    varChart->setAxisX(axisXR,LCLRSerie);
    varChart->setAxisY(axisYR,LCLRSerie);

    varChart->setAxisX(axisXR,dataRSerie);
    varChart->setAxisY(axisYR,dataRSerie);


    // Initializing a chart view so later we can add it and make it visible.
    QChartView *varCV = new QChartView(varChart);
    varCV->setRenderHint(QPainter::Antialiasing);


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(varCV);
    layout->addWidget(TALCV);

    // Set layout so we can se it in the interface.
    QWidget *auxWindow = new QWidget();
    auxWindow->setLayout(layout);
    auxWindow->setWindowTitle(title);
    auxWindow->resize(800,360);

    myWindow = auxWindow;

}


QWidget* controlwindow::getWindow() {
    return  myWindow;
}
