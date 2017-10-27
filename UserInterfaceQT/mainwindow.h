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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
