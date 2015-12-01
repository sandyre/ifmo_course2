#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Interpolation.h"
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    void viewLegend();
    void GenerateData(std::function<double(double)> fx, std::function<double(double,double)> dfx);
    void setupCustomPlot();
    void DrawInterpolationLines();
    void CreateOriginalGraph(std::function<double(double)> fx);
    void viewDataTable(int index);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);
    
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Interpolation inter;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
