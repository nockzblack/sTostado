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

    void on_solderPasteCB_activated(int index);
    
    QStringList getRiseSlopeValues();

    QStringList getPeakTempValues();

    QStringList getTimeAboveValues();

    void on_positiveSlopePB_clicked();

    void on_TALPB_clicked();

    void on_peakTempPB_clicked();
   


private:
    Ui::MainWindow *ui;

    void updateTable(QStringList &value);
};

#endif // MAINWINDOW_H
