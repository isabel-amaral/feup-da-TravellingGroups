#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "MinHeap.h"
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

class Graph {
public:
    struct Edge {
        int dest;     // Destination node
        int capacity; // An integer capacity
        int duration; // An integer duration
    };

    struct Node {
        vector<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int prev;
        int capacity;
        bool visited = false;
    };
    // Constructor: nr nodes and direction (default: undirected)
    explicit Graph(int nodes);
    // Add edge from source to destination with a certain weight
    void addEdge(int src, int dest, int capacity, int duration);
    void changeCapacity(vector<pair<int,int>> &q, int node, int capacity) const;
    void maxCapacity(int src, int dest);
    void minTranshipments(int src, int dest);

    int n;              // Graph size (vertices are numbered from 1 to n)
    vector<Node> nodes; // The list of nodes being represented
};

#endif