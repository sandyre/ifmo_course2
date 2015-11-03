//
//  main.cpp
//  VM_L1
//
//  Created by Aleksandr Borzikh on 06.10.15.
//  Copyright © 2015 Aleksanteri. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Matrix.hpp"
#include "SOLE.hpp"
#include "RGenerator.hpp"
void PrintMenu();
void LoadFromFile();
void LoadWithConsole();
void GenerateData();

int main(int argc, const char * argv[]) {
    PrintMenu();
    string command;
    cin >> command;
    while(command != "exit")
    {
        if(command == "1")
            LoadFromFile();
        if(command == "2")
            LoadWithConsole();
        if(command == "3")
            GenerateData();
        PrintMenu();
        cin >> command;
    }
}

void PrintMenu()
{
    cout << "Simple iteration method.\n";
    cout << "1. Load data from file\n";
    cout << "2. Enter data with console\n";
    cout << "3. Generate random matrix\n";
    cout << "Type command (1-3)\n";
}

void LoadFromFile()
{
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    
    ifstream in(filename, ios::ios_base::in);
    int N;
    in >> N;
    vector<vector<double> > A(N, vector<double>(N));
    vector<double> b(N);
    try {
    for(auto i = 0; i < N; i++)
    {
        for(auto j = 0; j < N+1; j++)
        {
            if(j == N) in >> b[i];
            else in >> A[i][j];
        }
    }
    }catch(exception e)
    {
        cout << "Wrong data format!" << endl;
        return;
    }
    in.close();
    
    cout << "Enter accuracy: ";
    double accuracy = 0.00001;
    cin >> accuracy;
    if(accuracy == 0) accuracy = 0.00000001;
    if(accuracy < 0) accuracy = abs(accuracy);
    
    SOLE *system = new SOLE(A, b, accuracy);
    system->Solve();
    
    vector<double> results = system->getResult();
    if(results.size() == 0)
    {
        cout << "Diagonal dominance: " << (system->getDiagonalDominance()? "true" : "false") << endl;
        cout << "Results cannot be found\n";
    }
    else
    {
        cout << "Source matrix:\n";
        for(auto i = 0; i < N; i++)
        {
            for(auto j = 0; j < N+1; j++)
            {
                if(j == N) cout << "[" << b[i] << "]\n";
                else cout << A[i][j] << " ";
            }
        }
        cout << "Diagonal dominance: " << (system->getDiagonalDominance()? "true" : "false") << endl;
        cout << "Accuracy: " << accuracy << endl;
        cout << "Results:\n";
        for(auto i = 0; i < results.size(); i++)
        {
            cout << "X" << i << " = " << results[i] << endl;
        }
        for(auto i = 0; i < results.size(); i++)
        {
            cout << "dX" << i << " = " << system->_errors[i] << endl;
        }
        cout << "Iterations made: " << system->getIterationsCount();
    }
    cout << endl;
}

void LoadWithConsole()
{
    int N;
    cout << "Enter number of equations: ";
    cin >> N;
    cout << "Enter equations matrix (one row per string):\n";
    vector<vector<double> > A(N, vector<double>(N));
    vector<double> b(N);
    double accuracy = 0.00000001;
    for(auto i = 0; i < N; i++)
    {
        for(auto j = 0; j < N+1; j++)
        {
            if(j == N) cin >> b[i];
            else cin >> A[i][j];
        }
    }
    cout << "\nEnter accuracy: ";
    cin >> accuracy;
    
    SOLE *system = new SOLE(A, b, accuracy);
    system->Solve();
    
    vector<double> results = system->getResult();
    
    if(results.size() == 0)
    {
        cout << "Diagonal dominance: " << (system->getDiagonalDominance()? "true" : "false") << endl;
        cout << "Results cannot be found\n";
    }
    else
    {
        cout << "Source matrix:\n";
        for(auto i = 0; i < N; i++)
        {
            for(auto j = 0; j < N+1; j++)
            {
                if(j == N) cout << "[" << b[i] << "]\n";
                else cout << A[i][j] << " ";
            }
        }
        cout << "Diagonal dominance: " << (system->getDiagonalDominance()? "true" : "false") << endl;
        cout << "Accuracy: " << accuracy << endl;
        cout << "Results:\n";
        for(auto i = 0; i < results.size(); i++)
        {
            cout << "X" << i << " = " << results[i] << endl;
        }
        for(auto i = 0; i < results.size(); i++)
        {
            cout << "dX" << i << " = " << system->_errors[i] << endl;
        }
        cout << "Iterations made: " << system->getIterationsCount();
    }
    cout << endl;
}

void GenerateData()
{
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    int N;
    cout << "Enter N: ";
    cin >> N;
    RGenerator generator;
    generator.CreateFile(filename.c_str(), N);
    return;
}