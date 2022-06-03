#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "MinHeap.h"
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
        int flow = 0;
        int duration; // An integer duration
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

    void changeCapacity(vector<pair<int,int>> &q, int node, int capacity) const;
    void maxCapacity(int src, int dest);
    void minTranshipments(int src, int dest);

    void reuniteGroup(int source, int dest, vector<vector<int>> paths) const;
    void waitTime(int source, int reunite, vector<vector<int>> paths) const;

    bool bfsCapacity(const int& source, const int& target);
    int getMaxCapacity(vector<int> path);
    int getMaxFlow(int source, int destination, Graph &network);
    void increaseRevCapacity (int start, int end, int capacity);
    vector<int> getPath (const int& source, const int& destination, int& maxCapacity);
    void getAllPaths (int source, int target, vector<pair<vector<int>,int>> &result);
    static bool comparePaths(pair<vector<int>,int> a, pair<vector<int>,int> b);
    void printPath(vector<int> path);
    void separateGroup(int src, int target, int dimension, Graph& network, int extra = 0);
};

#endif