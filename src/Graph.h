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
    int getMaxCapacity(const vector<int> &path);
    int getMaxFlow(const int &source, const int &destination, Graph &network);
    void increaseRevCapacity (const int &start, const int &end, const int &capacity);
    vector<int> getPath (const int& source, const int& destination, int& maxCapacity);
    void getAllPaths (const int &source, const int &target, vector<pair<vector<int>,int>> &result);
    static bool comparePaths(const pair<vector<int>,int>& a, const pair<vector<int>,int>& b);
    static void printPath(const vector<int> &path);
    void separateGroup(const int &src, const int &target, int dimension, Graph& network, int extra = 0);
};

#endif