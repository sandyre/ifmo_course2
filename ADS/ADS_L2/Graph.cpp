//
// Created by Aleksandr Borzikh on 15.05.16.
//

#include "Graph.h"
#include <random>

void Graph::CreateGraph ( size_t nVertexCount_, size_t nEdgesCount_, int dMinWeight, int dMaxWeight )
{
    this->nVertexCount = nVertexCount_;
    this->nEdgesCount = nEdgesCount_;

    aaMatrix = vector(nVertexCount, vector < int64_t >(nVertexCount, 0));

    random_device r;

    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist1(dMinWeight, dMaxWeight + 1);
    uniform_int_distribution<int> uniform_dist2(0, nVertexCount_ - 1);

    int64_t dWeight;
    for (auto i = 0; i < nVertexCount - 1; i++)
    {
        dWeight = uniform_dist1(e1);
        aaMatrix[i][i + 1] = dWeight;
        aaMatrix[i+1][i] = dWeight;
        nEdgesCount_--;
    }

    int v1 = 0;
    int v2 = 0;
    while ( nEdgesCount_ > 0 )
    {
        v1 = uniform_dist2(e1);
        v2 = uniform_dist2(e1);
        if ( v1 != v2 )
        {
            if ( aaMatrix[v1][v2] == 0 )
            {
                dWeight = uniform_dist1(e1);
                aaMatrix[v1][v2] = dWeight;
                aaMatrix[v2][v1] = dWeight;
                nEdgesCount_--;
            }
        }
    }
}

void Graph::CreateGraph ( size_t nVertexCount_, int dMinWeight, int dMaxWeight )
{
    this->nVertexCount = nVertexCount_;
    this->nEdgesCount = nVertexCount_ * nVertexCount_;

    aaMatrix = vector(nVertexCount_, vector < int64_t >(nVertexCount, 0));

    random_device r;

    default_random_engine e1(r());
    uniform_int_distribution<int> uniform_dist1(0, nVertexCount_ - 1);

    int64_t dWeight;
    for (auto i = 0; i < nVertexCount_; i++)
    {
        for ( auto j = i + 1; j < nVertexCount_; j++ )
        {
            dWeight = uniform_dist1(e1);
            aaMatrix[i][j] = dWeight;
            aaMatrix[j][i] = dWeight;
        }
    }
}