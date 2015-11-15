#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setupCustomPlot();
    this->CreateOriginalGraph(DOTCOUNT, qSin);
    this->DrawInterpolationLines(qSin);
    ui->customplot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupCustomPlot()
{
    ui->customplot->xAxis->setRange(LEFTBOUND, RIGHTBOUND);
    ui->customplot->yAxis->setRange(LOWERBOUND, UPPERBOUND);
    ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->customplot->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);

    //backgroundcolor
    QLinearGradient plotGrad;
    plotGrad.setStart(0,0);
    plotGrad.setFinalStop(0,350);
    plotGrad.setColorAt(0,QColor(80,80,80));
    plotGrad.setColorAt(1,QColor(50,50,50));
    ui->customplot->setBackground(plotGrad);
    //

    ui->customplot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->customplot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customplot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setTickLabelColor(Qt::white);
    ui->customplot->yAxis->setTickLabelColor(Qt::white);

    ui->customplot->xAxis->grid()->setPen(QPen(QColor(140,140,140), 1, Qt::DotLine));
    ui->customplot->yAxis->grid()->setPen(QPen(QColor(140,140,140), 1, Qt::DotLine));
    ui->customplot->xAxis->grid()->setSubGridPen(QPen(QColor(80,80,80), 1, Qt::DotLine));
    ui->customplot->yAxis->grid()->setSubGridPen(QPen(QColor(80,80,80), 1, Qt::DotLine));
    ui->customplot->xAxis->grid()->setSubGridVisible(true);
    ui->customplot->yAxis->grid()->setSubGridVisible(true);

    ui->customplot->xAxis->setLabelColor(Qt::white);
    ui->customplot->yAxis->setLabelColor(Qt::white);
}

void MainWindow::CreateOriginalGraph(int el_count, std::function<double(double)> fx)
{
    QVector<double> x, y;
    double h = (ui->customplot->xAxis->range().size())/(double)el_count;
    for(int i = -el_count/2; i <= el_count/2; i++)
    {
        x.push_back(i*h);
        y.push_back(fx(i*h));
    }
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setData(x,y);
    ui->customplot->graph(0)->setPen(QPen(Qt::white));
}

void MainWindow::DrawInterpolationLines(std::function<double(double)> fx)
{
    inter.FillWithData(fx);
    inter.CalculateDatasetsFromSources();
    ui->customplot->addGraph();
    ui->customplot->graph(1)->setPen(QPen(Qt::red));
    ui->customplot->graph(1)->setData(inter.calculated_datasets[0].x,
            inter.calculated_datasets[0].y);
    ui->customplot->addGraph();
    ui->customplot->graph(2)->setPen(QPen(Qt::red));
    ui->customplot->graph(2)->setData(inter.source_datasets[0].x,
            inter.source_datasets[0].y);
    ui->customplot->graph(2)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui->customplot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    ui->customplot->addGraph();
    ui->customplot->graph(3)->setPen(QPen(Qt::green));
    ui->customplot->graph(3)->setData(inter.calculated_datasets[1].x,
            inter.calculated_datasets[1].y);
    ui->customplot->addGraph();
    ui->customplot->graph(4)->setPen(QPen(Qt::green));
    ui->customplot->graph(4)->setData(inter.source_datasets[1].x,
            inter.source_datasets[1].y);
    ui->customplot->graph(4)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui->customplot->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    ui->customplot->addGraph();
    ui->customplot->graph(5)->setPen(QPen(Qt::magenta));
    ui->customplot->graph(5)->setData(inter.calculated_datasets[2].x,
            inter.calculated_datasets[2].y);
    ui->customplot->addGraph();
    ui->customplot->graph(6)->setPen(QPen(Qt::magenta));
    ui->customplot->graph(6)->setData(inter.source_datasets[2].x,
            inter.source_datasets[2].y);
    ui->customplot->graph(6)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui->customplot->graph(6)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == false)
    {
        ui->customplot->graph(1)->setVisible(false);
        ui->customplot->graph(2)->setVisible(false);
    }
    else
    {
        ui->customplot->graph(1)->setVisible(true);
        ui->customplot->graph(2)->setVisible(true);
    }
    ui->customplot->replot();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == false)
    {
        ui->customplot->graph(3)->setVisible(false);
        ui->customplot->graph(4)->setVisible(false);
    }
    else
    {
        ui->customplot->graph(3)->setVisible(true);
        ui->customplot->graph(4)->setVisible(true);
    }
    ui->customplot->replot();
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1 == false)
    {
        ui->customplot->graph(5)->setVisible(false);
        ui->customplot->graph(6)->setVisible(false);
    }
    else
    {
        ui->customplot->graph(5)->setVisible(true);
        ui->customplot->graph(6)->setVisible(true);
    }
    ui->customplot->replot();
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1 == false)
    {
        ui->customplot->graph(0)->setVisible(false);
    }
    else
    {
        ui->customplot->graph(0)->setVisible(true);
    }
    ui->customplot->replot();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->customplot->clearGraphs();
    switch(index)
    {
        case 0:
            CreateOriginalGraph(DOTCOUNT, qSin);
            DrawInterpolationLines(qSin);
            break;
        case 1:
            CreateOriginalGraph(DOTCOUNT, qCos);
            DrawInterpolationLines(qCos);
            break;
        case 2:
            CreateOriginalGraph(DOTCOUNT, qTan);
            DrawInterpolationLines(qTan);
            break;
    }
    ui->customplot->repaint();
}
