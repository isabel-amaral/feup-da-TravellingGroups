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
        /**
         * Destination stop.
         * */
        int dest;
        /**
         * Maximum number of people that can be transported between two stops.
         * */
        int capacity;
        /**
         * Number of people being transported in a bus.
         * */
        int flow = 0;
        /**
         * Travel time between two stops.
         * */
        int duration;
    };

    /**
     * Each node represents a bus stop.
     * */
    struct Node {
        /**
         * The list of outgoing edges (to adjacent stops).
         * */
        vector<Edge> adj;
        /**
         * Auxiliary attribute of BFS algorithm:
         * used to compute the path from a given source and destination.
         * */
        int prev;
        /**
         * Auxiliary attribute of algorithm to find the path with max capacity: used to save the best
         * capacity found up until a certain moment in a path that passes by this node.
         */
        int capacity;
        /**
         * Auxiliary attribute of BFS algorithm.
         * */
        bool visited = false;
    };

    /**
     * Network size.
     * Stops are numbered from 1 to n.
     * */
    int n;
    /**
     * List of stops being represented.
     */
    vector<Node> nodes;

public:
    /**
     * Constructor: default.
     * */
    Graph();
    /**
     * Constructor: nr nodes and direction (default: undirected).
     * */
    Graph(int nodes);
    /**
     * Add an edge from a source stop to a destination stop.
     * @param src is the source stop.
     * @param dest is the destinations stop.
     * @param capcity is the maximum number of people that can be transported.
     * @param duration is the travel time between two stops.
     * */
    void addEdge(int src, int dest, int capcity, int duration);

    // 1.1-------------------------------------------------------------------------------------
    /**
     * Update the capacity of a certain node in a vector.
     * @param q vector to update capacity.
     * @param node number of node to update capacity value.
     * @param capacity new capacity to insert in vector.
     */
    void changeCapacity(vector<pair<int,int>> &q, int node, int capacity) const;
    /**
     * Related to Dijkstra algorithm, used to find the maximum capacity of a certain path.
     * @param src is the source stop.
     * @param dest is the destinations stop.
     */
    void maxCapacity(int src, int dest);
    // 1.2-------------------------------------------------------------------------------------
    /**
     * BFS algorithm, used to determine shortest path from one node to another.
     * @param src is the source stop.
     * @param dest is the destinations stop.
     */
    void minTranshipments(int src, int dest);

    // 2.1/2.2---------------------------------------------------------------------------------
    bool bfsCapacity(const int& source, const int& target);
    int getMaxCapacity(const vector<int> &path);
    int getMaxFlow(const int &source, const int &destination, Graph &network);
    void increaseRevCapacity (const int &start, const int &end, const int &capacity);
    vector<int> getPath (const int& source, const int& destination, int& maxCapacity);
    void getAllPaths (const int &source, const int &target, vector<pair<vector<int>,int>> &result);
    static bool comparePaths(const pair<vector<int>,int>& a, const pair<vector<int>,int>& b);
    static void printPath(const vector<int> &path);
    vector<vector<int>> separateGroup(const int &src, const int &target, int dimension, Graph& network, int extra = 0);

    // 2.3-------------------------------------------------------------------------------------
    void initializeResidualNetwork(vector<Node>& residualNetwork) const;
    vector<int> findResidualNetworkPath(int src, int dest, vector<Node>& residualNetwork) const;
    void getMaxFlow(int src, int dest);

    // 2.4-------------------------------------------------------------------------------------
    int reuniteGroup(int source, int dest, vector<vector<int>> paths) const;
    // 2.5-------------------------------------------------------------------------------------
    void waitTime(int source, int reunite, const vector<vector<int>>& paths) const;
};

#endif