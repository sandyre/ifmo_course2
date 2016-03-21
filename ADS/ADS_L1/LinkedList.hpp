#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <string>
using namespace std;

struct Node
{
    Node *pNext = nullptr;
    string data;
};

class LinkedList
{
public:
    LinkedList() {}

    bool insert( string element );
    bool remove( string element );
    size_t contains( string element );
    size_t size() { return elements_count; }

private:
    size_t elements_count = 0;
    Node *root = nullptr;
    Node *tail = nullptr;
};

#endif
