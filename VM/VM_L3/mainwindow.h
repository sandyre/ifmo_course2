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
    void GenerateData(std::function<double(double)> fx = qSin);
    void setupCustomPlot();
    void DrawInterpolationLines(std::function<double(double)> fx);
    void CreateOriginalGraph(int el_count = 100,
                             std::function<double(double)> = qSin);
    void viewDataTable(int index);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);
    
    void on_pushButton_clicked();

private:
    Interpolation inter;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
