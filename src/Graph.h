#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "MinHeap.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

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
    // Constructor: default
    Graph();
    // Constructor: nr nodes and direction (default: undirected)
    Graph(int nodes);
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int capcity, int duration);

    void reuniteGroup(int source, int dest, vector<vector<int>> paths) const;
    void waitTime(int source, int reunite, vector<vector<int>> paths) const;
};

#endif
