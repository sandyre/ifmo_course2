#ifndef __HASHTABLE_HPP__
#define __HASHTABLE_HPP__

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include "LinkedList.hpp"
using namespace std;

class Hashtable
{
public:
    Hashtable( size_t size, function < int ( string ) > hashFunc ) :
        hashfunction( hashFunc ), hashtable( vector < LinkedList> ( size ) )
    {
        cout << "Hashtable initialized with capacity of " << size << endl;
    }

    bool insert( string element );
    size_t contains( string element );
    void printstat();
private:
    vector < LinkedList > hashtable;
    function < int ( string ) > hashfunction;
};

#endif
