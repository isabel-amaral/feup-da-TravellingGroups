#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "MinHeap.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class Graph {
    struct Edge {
        int dest;     // Destination node
        int capacity; // An integer capacity
        int duration; // An integer duration
    };

    struct Node {
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    vector<Node> nodes; // The list of nodes being represented

public:
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes);
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int capcity, int duration);
};

#endif
