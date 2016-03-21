#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <list>
#include <cmath>
#include <stdlib.h>
#include "Hashtable.hpp"
#include "LinkedList.hpp"
using namespace std;

void GenerateStrings ( const char * filename, size_t num )
{
    ofstream output ( filename, ios_base::out );

    std::random_device rd;
    std::mt19937 mt ( rd() );
    std::uniform_int_distribution < int > dist ( 33, 126 );

    for ( size_t i = 0; i < num; ++i )
    {
        for ( size_t j = 0; j < 32; ++j )
        {
            output << (char) dist ( mt );
        }
        output << endl;
    }
}

int main(int argc, char* argv[])
{
    for ( size_t i = 1; i <= 10; ++i )
    {
        string filename = "data_";
        filename += to_string( i * 1000 );
        filename += ".txt";
        GenerateStrings ( filename.c_str(), i * 1000 );
    }

    for ( size_t i = 1; i <= 10; ++i )
    {
        string filename = "data_";
        filename += to_string ( i * 1000 );
        filename += ".txt";

        ifstream input ( filename, ios_base::in );

        Hashtable hashtable( ( size_t ) 256, [&] ( string argument )
        {
            // Empty string is handled inside hashtable.
            if ( argument.size() < 2 ) return (int)argument[1];
            return (int)argument[0] + (int)argument[1];
        });

        string tmp;
        while ( input >> tmp )
        {
            hashtable.insert( tmp );
        }

        input.close();
        input.open(filename, ios_base::in);
        size_t comparisons = 0;
        while ( input >> tmp )
        {
            comparisons += hashtable.contains( tmp );
        }

        hashtable.printstat();
        cout << "Average comparisons: " << comparisons / (i * 1000) << endl << endl;
    }

    return 0;
}
