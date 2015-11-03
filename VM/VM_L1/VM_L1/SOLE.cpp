//
//  SOLE.cpp
//  VM_L1
//
//  Created by Aleksandr Borzikh on 06.10.15.
//  Copyright © 2015 Aleksanteri. All rights reserved.
//

#include "SOLE.hpp"

SOLE::SOLE(vector<vector<double> > A, vector<double> b,
    double accuracy)
{
    this->_A = A;
    this->_b = b;
    this->_accuracy = accuracy;
    
    _DiagonalDominance = getDiagonalDominance();
}
void SOLE::Solve()
{
    vector<vector<double> > B(_A.size(),
                              vector<double>(_A[0].size()));
    for(auto i = 0; i < _A.size(); i++)
    {
        for(auto j = 0; j < _A[i].size();j++)
        {
            if(i == j) B[i][j] = 0;
            else B[i][j] = _A[i][j] / _A[i][i]*-1;
        }
        _b[i] = _b[i] / _A[i][i];
    }
    
    vector<double> x0 = _b;
    
    while(_IterationsMade < MAX_ITERATIONS_COUNT)
    {
        _IterationsMade++;
        
        vector<double> x1 = Matrix::Add(Matrix::Mul(B,x0), _b);
        
        bool statement = true;
        
        for(auto i = 0; i < x0.size(); i++)
        {
            statement = statement && abs(x0[i]-x1[i]) < _accuracy;
        }
        
        if(statement)
        {
            _errors = Matrix::Add(x1, Matrix::Mul(x0, -1));
            
            _X = x1;
            
            return;
        }
        else x0 = x1;
    }
}
bool SOLE::getDiagonalDominance()
{
    for(auto i = 0; i < _A.size(); i++)
    {
        double sum = 0;
        for(auto j = 0; j < _A.size(); j++)
        {
            if(i != j) sum += abs(_A[i][j]);
        }
        if(sum >= abs(_A[i][i])) return false;
    }
    
    return true;
}
