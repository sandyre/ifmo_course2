#ifndef ODEM_H
#define ODEM_H
#include "Interpolation.h"
#include "functional"

class Milnes
{
public:
    static DataSet Milnes_Method(double x0, double y0, double xn, double eps,
                                std::function<double(double,double)> func, double start_step);
};

#endif // ODEM_H
