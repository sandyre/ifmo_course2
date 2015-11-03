//
//  RGenerator.cpp
//  VM_L1
//
//  Created by Aleksandr Borzikh on 06.10.15.
//  Copyright © 2015 Aleksanteri. All rights reserved.
//

#include "RGenerator.hpp"
#include <ctime>
#include <cstdlib>

RGenerator::RGenerator()
{
}

RGenerator::~RGenerator()
{
    this->filestream_.close();
}

void RGenerator::CreateFile(const char* filename, int N)
{
    filestream_.open(filename,ios_base::out);
    srand(time(0));
    
    vector<vector<double> > matrix_A(N, vector<double>(N));
    vector<double> matrix_B(N);
    
    double random = 0.0;
    
    filestream_ << N << endl;
    for(auto i = 0; i < N; i++)
    {
        for(auto j = 0; j < N+1; j++)
        {
            if(i == j)
            {
                random = (rand() % 10) / 10.0;
                random += N * 1.0;
            }
            else random = (rand() % 10) / 10.0;
            filestream_ << random << " ";
        }
        filestream_ << endl;
    }
    
}
