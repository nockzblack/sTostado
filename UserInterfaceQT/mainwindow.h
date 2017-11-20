#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_familyCB_activated(int index);

    void on_groupCB_activated(int index);

    void on_selectFilePB_clicked();

    void on_positiveSlopePB_clicked();

    void on_TALPB_clicked();

    void on_peakTempPB_clicked();

    void on_cleanPB_clicked();

    void on_familyCBC_activated(int index);

    void on_groupCBC_activated(int index);

    void on_profileCBC_activated(int index);

    void on_cleanPBC_clicked();

    void on_TALPBC_clicked();

    void on_peakTempPBC_clicked();

    void on_productionLineCB_activated(int index);

    void on_savePB_clicked();

private:
    Ui::MainWindow *ui;

    void updateParametersTW(QStringList &value);
    void updateParametersTWC(QStringList &value);
    void updateHeaderParametersTWC(int index);
    void updateTempTW(QStringList &value);

    void setParameterTW(int index);
    void setParameterTWC(int index);


    void setDefaultParametersTW();
    void setDefaultParametersTWC();
    void setDefaultTempTW();

    QStringList getRiseSlopeValues();
    QStringList getPeakTempValues();
    QStringList getTimeAboveValues();

    QStringList getControlPeakTempValues();
    QStringList getControlTimeAboveValues();

    void arrangeStr(QString auxStr);
    void arrangeStrControl(QString auxStr);

    bool saveInfo();
    QString currentTexts();

    bool extractData(QStringList data);

    QStringList getStringValues(QString& strNonFilter);
    QVector<QStringList>  getListValues(QString& str);
    void updateProfilesTWC(QVector<QStringList> auxMatrix);

};

#endif // MAINWINDOW_H
