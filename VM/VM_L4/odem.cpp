#include "odem.h"
#include <QtMath>
#include <functional>

DataSet Milnes::Milnes_Method(double x0, double y0, double xn, double eps,
                            std::function<double(double,double)> func, double start_step)
{
    DataSet result;

    double n_points = (xn - x0) / start_step;
    n_points = std::floorf(n_points);

    double step = start_step;

    if(n_points < 4)
    {
        step = (std::abs(x0) + std::abs(xn)) / 4;
        n_points = 4;
    }


    double y_pred, y_cor; // y_pred - y predictor, y_cor - y corrector

    bool its_calculated = false;
    bool need_reduce_step = false;

    while(!its_calculated)
    {
        need_reduce_step = false;
        its_calculated = true;

        QVector<double> k(4);
        QVector<double> y(n_points + 1);
        QVector<double> x(n_points + 1);
        QVector<double> f(n_points + 1);

        y[0] = y0;
        x[0] = x0;

        // calculate first 4 elements using Runge-Kutta formulas

        for(auto i = 0; i < 3; i++)
        {
            k[0] = func(x[i], y[i]);
            k[1] = func(x[i] + step/2, y[i] + k[0] / 2);
            k[2] = func(x[i] + step/2, y[i] + k[1] / 2);
            k[3] = func(x[i] + step, y[i] + k[2]);

            y[i + 1] = (y[i] + step * (k[0] + 2 * k[1] + 2 * k[2] + k[3])/6.0);
            x[i + 1] = x[i] + step;
            f[i] = (func(x[i], y[i]));
        }
        f[3] = func(x[3], y[3]);

        // calculate others using Milne's formulas

        for(auto i = 4; i <= n_points; i++)
        {
            x[i] = x[i - 1] + step;
            y_pred = (y[i-4] + (4 * step/3) * (2 * f[i - 3] - f[i - 2] + 2 * f[i - 1]));
            f[i] = (func(x[i], y_pred));
            y_cor = (y[i - 2] + step / 3 * (f[i - 2] + 4 * f[i - 1] + f[i]));
            if(std::abs((y_cor - y_pred)/29) > eps) // check accuracy
            {
                step = step / 2; // reduce step
                n_points = n_points * 2; // and increase n of points
                need_reduce_step = true;
                break;
            }
            else
            {
                y[i] = y_cor;
                f[i] = func(x[i], y[i]);
            }
        }

        if(need_reduce_step)
        {
            its_calculated = false;
        }

        result.x = x;
        result.y = y;
        result.lenght = x.size();
    }

    return result;
}

//DataSet Milnes::Milnes_Method(double x0, double y0, double xn, double eps,
//                            std::function<double(double,double)> func, double start_step)
//{
//    DataSet result;

//    double default_step = start_step; // default step
//    double n_points = (xn - x0) / start_step;
//    n_points = std::floorf(n_points);
//    double step = (xn - x0) / n_points;
//    double y_pred, y_cor;

//    bool its_calculated = false;
//    bool need_reduce_step = false;

//    while(its_calculated == false)
//    {
//        need_reduce_step = false;
//        its_calculated = true;
//        QVector<double> k(4);
//        QVector<double> y(n_points + 1);
//        QVector<double> x(n_points + 1);
//        QVector<double> f(n_points + 1);

//        y[0] = y0;
//        x[0] = x0;

//        // calculate first 4 elements using Runge-Kutta formulas

//        for(auto i = 0; i < 3; i++)
//        {
//            k[0] = (step * func(x[i], y[i]));
//            k[1] = (step * func(x[i] + step/2, y[i] + k[0] / 2));
//            k[2] = (step * func(x[i] + step/2, y[i] + k[1] / 2));
//            k[3] = (step * func(x[i] + step, y[i] + k[2]));

//            y[i + 1] = (y[i] + (1.0 / 0.6) * (k[0] + 2 * k[1] + 2 * k[2] + k[3]));
//            x[i + 1] = x[i] + step;
//            f[i] = (func(x[i], y[i]));
//        }
//        f[3] = func(x[3], y[3]);

//        // calculate others using Milne's formulas

//        for(auto i = 4; i <= n_points; i++)
//        {
//            x[i] = x[i - 1] + step;
//            y_pred = (y[i-4] + (4 * step/3) * (2 * f[i - 3] - f[i - 2] + 2 * f[i - 1]));
//            f[i] = (func(x[i], y_pred));
//            y_cor = (y[i - 2] + step / 3 * (f[i - 2] + 4 * f[i - 1] + f[i]));
//            if(std::abs((y_cor - y_pred)/29) > eps) // check accuracy
//            {
//                step = step / 2; // reduce step
//                n_points = n_points * 2; // and increase n_points of points
//                need_reduce_step = true;
//                break;
//            }
//            else
//            {
//                y[i] = y_cor;
//                f[i] = func(x[i], y[i]);
//            }
//        }

//        if(need_reduce_step == true)
//        {
//            its_calculated = false;
//        }

//        result.x = x;
//        result.y = y;
//        result.lenght = x.size();
//    }

//    return result;
//}

