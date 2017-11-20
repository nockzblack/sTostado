#ifndef AUXWINDOW_H
#define AUXWINDOW_H

#include <QMainWindow>

class auxwindow
{
public:
    auxwindow();
    auxwindow(QStringList values, QStringList controlLimits, QStringList limitsValues, QString title, int lenOfData, QString scale, QStringList charLimits);

    QWidget* getWindow();

private:
    QWidget *window;
};




#endif // AUXWINDOW_H
