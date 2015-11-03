//
//  main.cpp
//  VM_L2
//
//  Created by Aleksandr Borzikh on 31.10.15.
//  Copyright © 2015 sandyre. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <functional>
#include <cmath>
using namespace std;

class IntegrationMethods
{
public:
    static double TrapezeMethod(double a, double b, int &n_,
                                double eps, double &runge_estimation,function<double(double)> function_)
    {
        int iterations = 0;
        double h, x, s = 0.0, s_old = 0.0;
        int n = 100;
        
        do
        {
            n = n * 2;
            iterations++;
            h = (b - a) / (double)n;
            s_old = s;
            s = (function_(a)/2.0 + function_(b)/2.0);
            
            for(x = (a + h); x < (b - h); x += h)
            {
                s += function_(x);
            }
            s *= h;

            if(iterations > 10)
            {
                cout << "Too much iterations made. Break.";
                break;
            }
        } while(((abs(s_old - s)) > eps));
        
        runge_estimation = abs(s_old - s)/3.0;
        return s;
    }
};

class Functions
{
public:
    static double TripleSin(double x)
    {
        return 3*sin(x);
    }
    static double Log2(double x)
    {
        return log2(x);
    }
    static double SquaredX(double x)
    {
        return x*x + x + 5;
    }
    static double Sqrt(double x)
    {
        return sqrt(x);
    }
    static double Line(double x)
    {
        return 2*x - 5;
    }
};

int main(int argc, const char * argv[]) {
    int choice = -1, n = 10000;
    double a, b, eps, runge_estimation = 0, result = 0;
    a = b = eps = 0;
    
    do
    {
        a = b = eps = runge_estimation;
        
        cout << "Functions to integrate: \n1. 3sin(x)\n2. log2(x)\n3. x^2+x+5\n4. sqrt(x)\n5. 2x-5\nType 0 to exit.\n";        while(!(cin >> choice))
        {
            cout << "Wrong input. Write again: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        if(choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5)
        {
            cout << "Enter A: ";
            while(!(cin >> a))
            {
                cout << "Wrong input. Write A again: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
            cout << "Enter B: ";
            while(!(cin >> b))
            {
                cout << "Wrong input. Write B again: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
            if(a > b) swap(a,b); // swap limits
            
            cout << "Enter accuracy: ";
            while(!(cin >> eps))
            {
                cout << "Wrong input. Write accuracy again: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            
            switch(choice)
            {
                case 1:
                    result = IntegrationMethods::TrapezeMethod(a, b, n, eps, runge_estimation,Functions::TripleSin);
                    break;
                case 2:
                    result = IntegrationMethods::TrapezeMethod(a, b, n, eps, runge_estimation,Functions::Log2);
                    break;
                case 3:
                    result = IntegrationMethods::TrapezeMethod(a, b, n, eps, runge_estimation,Functions::SquaredX);
                    break;
                case 4:
                    result = IntegrationMethods::TrapezeMethod(a, b, n, eps, runge_estimation,Functions::Sqrt);
                    break;
                case 5:
                    result = IntegrationMethods::TrapezeMethod(a, b, n, eps, runge_estimation,Functions::Line);
                    break;
            }
            cout << "I = " << result << " N = " << n << " " << "Runge estimation = " << runge_estimation << endl;
        }
        else if(choice != 0)
        {
            cout << "Wrong command. Try again." << endl;
        }
    } while(choice != 0);
    return 0;
}