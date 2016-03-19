#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "Hashtable.hpp"
#include "LinkedList.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    // Creating hashtable and passing hash function;
    Hashtable hashtable( ( size_t ) 256, [&] ( string argument )
    {
        // Empty string is handled inside hashtable.
        if ( argument.size() < 2 ) return (int)argument[1];
        return (int)argument[0] + (int)argument[1];
    });

    string inputstr;
    while ( cin >> inputstr && inputstr != "exit" )
    {
        if ( inputstr == "printstat" )
        {
            hashtable.printstat();
        }
        if ( inputstr == "insert" )
        {
            cin >> inputstr;
            cout << hashtable.insert( inputstr ) << endl;
        }
        else if ( inputstr == "contains" )
        {
            cin >> inputstr;
            cout << hashtable.contains( inputstr ) << endl;
        }
    }

    return 0;
}
