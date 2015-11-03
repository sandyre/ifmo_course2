//
//  Matrix.hpp
//  VM_L1
//
//  Created by Aleksandr Borzikh on 19.10.15.
//  Copyright © 2015 Aleksanteri. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <vector>
#include <cmath>
using namespace std;

class Matrix
{
public:
    static vector<vector<double> > E(int n);
    static vector<vector<double> > Add(vector<vector<double> > matrix1,
                                       vector<vector<double> > matrix2);
    static vector<double> Add(vector<double> matrix1, vector<double> matrix2);
    static vector<vector<double> > Mul(vector<vector<double> > matrix1, double x);
    static vector<double> Mul(vector<double> matrix1, double x);
    static vector<vector<double> > Mul(vector<vector<double> > matrix1,
                                       vector<vector<double> > matrix2);
    static vector<double> Mul(vector<vector<double> > matrix1, vector<double> matrix2);
    static vector<double> Mul(vector<double> matrix1, vector<double> matrix2);
};
#endif /* Matrix_hpp */
