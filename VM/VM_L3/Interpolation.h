#ifndef INTERPOLATION_H
#define INTERPOLATION_H
#include "consts.h"
#include <QtMath>
#include <QVector>
#include <functional>
struct DataSet
{
    DataSet()
    {
    }

    DataSet(QVector<double> x_, QVector<double> y_)
    {
        lenght = x_.size();
        x = x_;
        y = y_;
    }

    int lenght = 0;
    QVector<double> x;
    QVector<double> y;
};

class Functions
{
public:
    static double sin(double x)
    {
        return sin(x);
    }
    static double cos(double x)
    {
        return cos(x);
    }
    static double tg(double x)
    {
        return tg(x);
    }
    static double ctg(double x)
    {
        return ctg(x);
    }
};

class Interpolation
{
public:
    Interpolation();

    void FillWithData(std::function<double(double)> fx = sin);
    void ClearData();

    DataSet NewtonGetDataSet(DataSet input_dataset, double leftbound = LEFTBOUND,
                             double rightbound = RIGHTBOUND, int N = DOTCOUNT);

    void CalculateDatasetsFromSources();
    QVector<DataSet> source_datasets;
    QVector<DataSet> calculated_datasets;
};

#endif // INTERPOLATION_H
