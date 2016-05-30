//
// Created by Aleksandr Borzikh on 15.05.16.
//

#ifndef ADS_L2_GRAPH_H
#define ADS_L2_GRAPH_H

#include <vector>
#include <cstdint>
using namespace std;

class Edge
{
public:
    Edge ( int v1_, int v2_, int dWeight_ ) :
            v1(v1_), v2(v2_), dWeight(dWeight_)
    {

    }
    Edge () : v1(0), v2(0), dWeight(0)
    {

    }

    bool Equals ( Edge& another )
    {
        return (    (v1 == another.v1) &&
                    (v2 == another.v2) &&
                    (dWeight == another.dWeight));
    }

    int dWeight;
    int v1;
    int v2;
};

class Graph
{
public:
    Graph()
    {}

    void CreateGraph ( size_t nVertexCount, size_t nEdgesCount, int dMinWeight, int dMaxWeight );

    void CreateGraph ( size_t nVertexCount, int dMinWeight, int dMaxWeight );



    vector < vector < int64_t > > aaMatrix;
    vector < Edge > astResult;
    size_t nVertexCount;
    size_t nEdgesCount;
};


#endif //ADS_L2_GRAPH_H
