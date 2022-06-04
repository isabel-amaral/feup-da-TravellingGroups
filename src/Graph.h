#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

class Graph {
public:
    struct Edge {
        int dest;     // Destination node
        int capacity; // An integer capacity
        int duration; // An integer duration
        int flow;     // flow passing through an edge
    };

    struct Node {
        vector<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        int prev;
        int capacity;
        bool visited = false;
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

    // 1.1-------------------------------------------------------------------------------------
    void changeCapacity(vector<pair<int,int>> &q, int node, int capacity) const;
    void maxCapacity(int src, int dest);
    // 1.2-------------------------------------------------------------------------------------
    void minTranshipments(int src, int dest);

    // 2.3-------------------------------------------------------------------------------------
    void initializeResidualNetwork(vector<Node>& residualNetwork) const;
    vector<int> findResidualNetworkPath(int src, int dest, vector<Node>& residualNetwork) const;
    int getMaxFlow(int src, int dest);

    // 2.4-------------------------------------------------------------------------------------
    void reuniteGroup(int source, int dest, vector<vector<int>> paths) const;
    // 2.5-------------------------------------------------------------------------------------
    void waitTime(int source, int reunite, vector<vector<int>> paths) const;
};

#endif