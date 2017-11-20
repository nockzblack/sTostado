#include "mainwindow.h"
#include "auxwindow.h"
#include <QApplication>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Plexus Project");
    w.resize(850,550);
    w.show();

    return a.exec();
}
