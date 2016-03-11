#include "Interpolation.h"
#include <QtMath>
#include <QDebug>

Interpolation::Interpolation()
{
}

void Interpolation::FillWithData(std::function<double(double)> fx)
{
    this->ClearData();

    DataSet first;
    for(double i = 0; i <= 2*M_PI; i+=M_PI_2)
    {
        first.x.push_back(i);
        first.y.push_back(fx(i));
        first.lenght++;
    }

    this->source_datasets.push_back(first);

    DataSet second;
    for(double i = 0; i <= 2*M_PI; i+=M_PI_4)
    {
        second.x.push_back(i);
        second.y.push_back(fx(i));
        second.lenght++;
    }

    this->source_datasets.push_back(second);

    DataSet third;
    for(double i = 0; i <= M_PI*50; i+=M_PI*5)
    {
        third.x.push_back(i);
        third.y.push_back(fx(i));
        third.lenght++;
    }

    this->source_datasets.push_back(third);
}

DataSet Interpolation::NewtonGetDataSet(DataSet input_dataset)
{
    DataSet result;
    double step = 0.01;
    result.lenght = (std::abs(input_dataset.x[0]) + std::abs(input_dataset.x[input_dataset.lenght-1]))/step;
    double unknown_x = input_dataset.x[0];
    result.lenght = std::floorl(result.lenght);
    double F, den, res;
    for(auto iter = 0; iter <= result.lenght; iter++)
    {
        res = input_dataset.y[0];
        for(auto i = 1; i < input_dataset.lenght; i++)
        {
            F = 0;
            for(auto j = 0; j <= i; j++)
            {
                den = 1;
                for(auto k = 0; k <= i; k++)
                {
                    if(k != j) den *= (input_dataset.x[j] - input_dataset.x[k]);
                }
                F += input_dataset.y[j] / den;
            }
            // den = n! * h ^ n
            for(auto k = 0; k < i; k++)
                F *= (unknown_x - input_dataset.x[k]); // * (x - x0)(x - x1)..
            res += F;
        }

        result.x.push_back(unknown_x);
        result.y.push_back(res);

        unknown_x+=step;
    }
    return result;
}

void Interpolation::CalculateDatasetsFromSources()
{
    for(auto i = 0; i < this->source_datasets.size(); i++)
    {
        DataSet calculated = this->NewtonGetDataSet(source_datasets[i]);
        this->calculated_datasets.push_back(calculated);
    }
}

void Interpolation::ClearData()
{
    this->calculated_datasets.clear();
    this->source_datasets.clear();
}

double Interpolation::NewtonGetInterpolationResult(int index, double x)
{
    double result = source_datasets[index].y[0];
    double unknown_x = x;
    double F, den;
    for(auto i = 1; i < source_datasets[index].lenght; i++)
    {
        F = 0;
        for(auto j = 0; j <= i; j++)
        {
            den = 1;
            for(auto k = 0; k <= i; k++)
            {
                if(k != j) den *= (source_datasets[index].x[j] - source_datasets[index].x[k]);
            }
            F += source_datasets[index].y[j] / den;
        }
        for(auto k = 0; k < i; k++) F *= (unknown_x - source_datasets[index].x[k]);
        result += F;
    }
    return result;
}
