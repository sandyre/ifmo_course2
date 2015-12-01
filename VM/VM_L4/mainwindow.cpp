#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include "odem.h"
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setupCustomPlot();
    // available parameters for Functions
    // cubex, squarex,
    // they are defined in Interpolation.h
    this->CreateOriginalGraph(Functions::squarex);
    this->GenerateData(Functions::squarex, Functions::dsquarex);
    this->DrawInterpolationLines();
    this->viewDataTable(0);
    this->viewLegend();
    ui->customplot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::GenerateData(std::function<double(double)> fx, std::function<double(double,double)> dfx)
{
    inter.source_datasets.clear();
    inter.calculated_datasets.clear();

    DataSet result = Milnes::Milnes_Method(LEFTBOUND, fx(LEFTBOUND),
                                           RIGHTBOUND, 0.01f, dfx, 0.3f);
    inter.source_datasets.push_back(result);
    inter.CalculateDatasetsFromSources();
}

void MainWindow::setupCustomPlot()
{
    ui->customplot->xAxis->setRange(LEFTBOUND, RIGHTBOUND);
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

void MainWindow::CreateOriginalGraph(std::function<double(double)> fx)
{
    QVector<double> x, y;
    double h = 0.001;
    for(double i = LEFTBOUND; i <= RIGHTBOUND; i+=h)
    {
        x.push_back(i);
        y.push_back(fx(i));
    }
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setName("real f(x)");
    ui->customplot->graph(0)->setData(x,y);
    ui->customplot->graph(0)->setPen(QPen(Qt::white));
}

void MainWindow::DrawInterpolationLines()
{
    ui->customplot->addGraph();
    ui->customplot->graph(1)->setName("inter. f(x) #1");
    ui->customplot->graph(1)->setPen(QPen(Qt::red));
    ui->customplot->graph(1)->setData(inter.calculated_datasets[0].x,
            inter.calculated_datasets[0].y);
    ui->customplot->addGraph();
    ui->customplot->graph(2)->setPen(QPen(Qt::red));
    ui->customplot->graph(2)->setData(inter.source_datasets[0].x,
            inter.source_datasets[0].y);
    ui->customplot->graph(2)->setLineStyle(QCPGraph::LineStyle::lsNone);
    ui->customplot->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    this->viewLegend();
}

void MainWindow::viewLegend()
{
    ui->customplot->legend->removeAt(2);

    ui->customplot->legend->setBrush(QBrush(Qt::gray));
    ui->customplot->legend->setVisible(true);
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
            GenerateData(Functions::squarex, Functions::dsquarex);
            CreateOriginalGraph(Functions::squarex);
            DrawInterpolationLines();
            viewDataTable(0);
            break;
        case 1:
            GenerateData(Functions::cubex, Functions::dcubex);
            CreateOriginalGraph(Functions::cubex);
            DrawInterpolationLines();
            viewDataTable(0);
            break;

    }

    if(ui->checkBox->isChecked())
    {
        ui->customplot->graph(1)->setVisible(true);
        ui->customplot->graph(2)->setVisible(true);
    }
    if(ui->checkBox_4->isChecked())
    {
        ui->customplot->graph(0)->setVisible(true);
    }

    ui->customplot->replot();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    this->viewDataTable(index);
}

void MainWindow::viewDataTable(int index)
{
    ui->datatable->setColumnWidth(0, 50);
    ui->datatable->setColumnCount(2);
    ui->datatable->setRowCount(inter.source_datasets[index].lenght);

    for(auto j = 0; j < inter.source_datasets[index].lenght; j++)
    {
        QTableWidgetItem *x = new QTableWidgetItem(QString("%1").arg(inter.source_datasets[index].x[j]));
        QTableWidgetItem *y = new QTableWidgetItem(QString("%1").arg(inter.source_datasets[index].y[j]));
        ui->datatable->setItem(j, 0, x);
        ui->datatable->setItem(j, 1, y);
    }
}

void MainWindow::on_pushButton_clicked()
{
    int index = ui->comboBox_2->currentIndex();
    for(auto i = 0; i < inter.source_datasets[index].lenght; i++)
    {
        inter.source_datasets[index].x[i] = ui->datatable->item(i, 0)->text().toDouble();
        inter.source_datasets[index].y[i] = ui->datatable->item(i, 1)->text().toDouble();
    }

    inter.calculated_datasets.clear();
    inter.CalculateDatasetsFromSources();
    ui->customplot->clearGraphs();

    int function = ui->comboBox->currentIndex();
    switch(function)
    {
        case 0:
            CreateOriginalGraph(Functions::cubex);
            DrawInterpolationLines();
            break;
    }

    // after repaint, check if graphics should be displayed
    if(ui->checkBox->isChecked())
    {
        ui->customplot->graph(1)->setVisible(true);
        ui->customplot->graph(2)->setVisible(true);
    }
    if(ui->checkBox_4->isChecked())
    {
        ui->customplot->graph(0)->setVisible(true);
    }
    ui->customplot->replot();
}

void MainWindow::on_pushButton_2_clicked()
{
    int index = ui->comboBox_2->currentIndex();
    QString input_x = ui->lineEdit_2->text();
    double answer = inter.NewtonGetInterpolationResult(index,input_x.toDouble());
    ui->lineEdit->setText(QString::number(answer));
}
