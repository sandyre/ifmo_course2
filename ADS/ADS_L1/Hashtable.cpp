#include "Hashtable.hpp"

bool Hashtable::insert( string element )

{
    if ( element.size() == 0 )
    {
        cout << "Empty string was passed. Error." << endl;
        return false;
    }

    size_t index = hashfunction( element );
    return hashtable [ index ].insert( element );
}

size_t Hashtable::contains( string element )
{
    if ( element.size() == 0 )
    {
        cout << "Empty string was passed. Error." << endl;
        return false;
    }

    size_t index = hashfunction( element );
    return hashtable [ index ].contains( element );
}

void Hashtable::printstat()
{
    size_t elements_count = 0;
    size_t hashes_count = 0;
    for ( size_t i = 0; i < hashtable.size(); ++i )
    {
        if( hashtable[ i ].size() != 0 ) ++hashes_count;
        elements_count += hashtable[ i ].size();
    }

    cout << "Total elements: " << elements_count << " Hashes used: " << hashes_count << endl;
    cout << "Collisions on average: " << elements_count / hashes_count << endl;
}
