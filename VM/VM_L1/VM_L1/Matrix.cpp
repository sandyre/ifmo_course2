//
//  Matrix.cpp
//  VM_L1
//
//  Created by Aleksandr Borzikh on 19.10.15.
//  Copyright © 2015 Aleksanteri. All rights reserved.
//

#include "Matrix.hpp"

vector<vector<double> > Matrix::E(int n)
{
    vector<vector<double> > E(n,vector<double>(n));
    for(auto i = 0; i < n; i++)
    {
        for(auto j = 0; j < n; j++)
        {
            if(i == j) E[i][j] = 1;
            else E[i][j] = 0;
        }
    }
    
    return E;
}
vector<vector<double> > Matrix::Add(vector<vector<double> > matrix1,
                            vector<vector<double> > matrix2)
{
    vector<vector<double> > result(matrix1.size(), vector<double>(matrix1[0].size()));
    for(auto i = 0; i < matrix1.size(); i++)
    {
        for(auto j = 0; j < matrix1[i].size(); j++)
        {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    
    return result;
}
vector<double> Matrix::Add(vector<double> matrix1, vector<double> matrix2)
{
    vector<double> result(matrix1.size());
    for(auto i = 0; i < matrix1.size(); i++)
    {
        result[i] = matrix1[i] + matrix2[i];
    }
    
    return result;
}
vector<vector<double> > Matrix::Mul(vector<vector<double> > matrix1, double x)
{
    for(auto i = 0; i < matrix1.size(); i++)
    {
        for(auto j = 0; j < matrix1[i].size(); i++)
        {
            matrix1[i][j] = matrix1[i][j] * x;
        }
    }
    
    return matrix1;
}
vector<double> Matrix::Mul(vector<double> matrix1, double x)
{
    for(auto i = 0; i < matrix1.size(); i++)
    {
        matrix1[i] = matrix1[i] * x;
    }
    
    return matrix1;
}
vector<vector<double> > Matrix::Mul(vector<vector<double> > matrix1,
                            vector<vector<double> > matrix2)
{
    vector<vector<double> > result(matrix1.size(), vector<double>(matrix1[0].size()));
    
    for(auto k = 0; k < matrix2[0].size(); k++)
    {
        for(auto j = 0; j < matrix1.size(); j++)
        {
            for(auto i = 0; i < matrix2.size(); i++)
            {
                if(i == 0) result[j][k] = matrix1[j][i] * matrix2[i][k];
                else result[j][k] += matrix1[j][i] * matrix2[i][k];
            }
        }
    }
    
    return result;
}
vector<double> Matrix::Mul(vector<vector<double> > matrix1, vector<double> matrix2)
{
    vector<double> result(matrix1.size());
    
    for(auto j = 0; j < matrix1.size(); j++)
    {
        for(auto i = 0; i < matrix2.size(); i++)
        {
            if(i == 0) result[j] = matrix1[j][i] * matrix2[i];
            else result[j] += matrix1[j][i] * matrix2[i];
        }
    }
    
    return result;
}
vector<double> Matrix::Mul(vector<double> matrix1, vector<double> matrix2)
{
    vector<double> result(matrix1.size());
    
    for(auto i = 0; i < matrix1.size(); i++)
    {
        result[i] = matrix1[i] * matrix2[i];
    }
    
    return result;
}