#ifndef __GRAPH
#define __GRAPH

#include <vector>

#include <sparse_matrix.hpp>

template <
    class T
> graph {
private:
    vector<T> _nodes;
    sparse_matrix<int> _edges;

public:
};

#endif // __GRAPH