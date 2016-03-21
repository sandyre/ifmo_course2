#include "LinkedList.hpp"

bool LinkedList::insert( string element )

{
    // Handling first element only. It optimizes the search and future insert very much.
    if( root == nullptr )
    {
        root = new Node();
        root->data = element;
        tail = root;

        ++elements_count;
        return true;
    }

    Node *pCurrentNode = tail;

    for ( size_t index = 0; ; ++index )
    {
        if ( pCurrentNode->data == element ) return false;

        if( pCurrentNode->pNext != nullptr )
        {
            pCurrentNode = pCurrentNode->pNext;
        }
        else
        {
            pCurrentNode->pNext = new Node();
            pCurrentNode->pNext->data = element;
            ++elements_count;
            return true;
        }
    }
}

size_t LinkedList::contains( string element )

{
    Node *pCurrentNode = root;

    for ( size_t index = 0; ; ++index )
    {
        if( pCurrentNode->data == element ) return index + 1;

        if( pCurrentNode->pNext != nullptr )
        {
            pCurrentNode = pCurrentNode->pNext;
        }
    }

    return 0;
}
