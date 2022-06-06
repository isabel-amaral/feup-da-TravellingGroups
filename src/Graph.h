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
    /**
     * BFS algorithm implementation used to find a path from @param source to @param target and the
     * capacity of each stop in that that path.
     * @return true if there is path from the source to the destination stop, else false.
     * */
    bool bfsCapacity(const int& source, const int& target);
    /**
     * Computes the maximum capacity of a path according to its edges flow, i.e, the minimum of its edges flow.
     * @param path is the path whose capacity will be calculated.
     * @return the path capacity.
     * */
    int getPathMaxCapacity(const vector<int> &path);
    /**
     * Implementation of Edmounds-Karp algorithm to compute the maximum flow of a network, i.e., the maximum number of people
     * that can be transported, in each iteration, from a source to a destination stop, using all possible paths.
     * @param source is the source bus stop.
     * @param destination is the destination bus stop.
     * @param network is the network whose maximum flow will be calculated.
     * @return the maximum flow of @param network.
     * */
    int getMaxFlow(const int &source, const int &destination, Graph &network);
    /**
     * Auxiliary function to Edmounds-Karp algorithm that increases the capacity of the reverse edge from
     * @param a to @param b (i.e., the edge from @param b to @param a), by @param capacity units.
     * @param a is the source stop.
     * @param b is the destination stop.
     * @capacity is the capacity to be added to the edge @param b-> @param a.
     * */
    void increaseRevCapacity (const int &a, const int &b, const int &capacity);
    /**
     * Computes te path from @param source to @param destination according to the "prev" field
     * previously updated by the BFS algorithm.
     * @param source is the source bus stop.
     * @param destination is the destination bus stop.
     * @param maxCapacity is the path capacity that will be updated.
     * */
    vector<int> getPath (const int& source, const int& destination, int& maxCapacity);
    /**
     * Computes all possible paths from @param source to @param target using BFS.
     * @param source is the source bus stop.
     * @param target is the destination bus stop.
     * @param result is a vector that will be updated with all the paths from source to destination and
     * the capacity of each one of these paths.
     * */
    void getAllPaths (const int &source, const int &target, vector<pair<vector<int>,int>> &result);
    /**
     * Compares paths in descending order according to their capacity.
     * @param p1 path 1.
     * @param p2 path 2.
     * @return true if @param p1 is greater than @param p2, else returns false.
     */
    static bool comparePaths(const pair<vector<int>,int>& p1, const pair<vector<int>,int>& p2);
    /**
     * Auxiliary method to display a path in a user-friendly way.
     * @param path is the path that will be displayed.
     * */
    static void printPath(const vector<int> &path);
    /**
     * Computes the path that a group with a certain dimension should follow to reach their destination. If necessary,
     * the group can be divided in sub groups.
     * @param src is the source stop.
     * @param target is the destination stop.
     * @param dimension is the dimension of the group.
     * @param network is the network with all stops and the buses (edges) that connect these stops.
     * @param extra is the dimension of an additional group whose path should be calculated after
     *  computing the original group path.
     */
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