#include "mainwindow.h"
#include <QApplication>
#include <QLayout>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();





    return a.exec();
}
