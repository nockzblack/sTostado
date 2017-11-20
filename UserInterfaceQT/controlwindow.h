#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>

class controlwindow
{
public:
    controlwindow();
    controlwindow(QStringList XValues, QStringList RValues, QStringList controlLimits, QString scale, QStringList charLimits);
    QWidget* getWindow();

private:
    QWidget* myWindow;
};

#endif // CONTROLWINDOW_H


