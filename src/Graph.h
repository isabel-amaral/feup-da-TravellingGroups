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
     * @param capacity is the maximum number of people that can be transported.
     * @param duration is the travel time between two stops.
     * */
    void addEdge(int src, int dest, int capacity, int duration);

    // 1.1-------------------------------------------------------------------------------------
    /**
     * Updates the capacity of a certain node in a vector.
     * @param q vector to update capacity.
     * @param node number of the node whose capacity needs to be updated.
     * @param capacity new capacity of the node.
     */
    void changeCapacity(vector<pair<int,int>> &q, int node, int capacity) const;
    /**
     * Given an origin and a destination, finds the path with maximum capacity in a transportation network.\n
     * Variation of Dijkstra's algorithm, used to find the maximum capacity of a Graph.
     * @param src is the source stop.
     * @param dest is the destination stop.
     */
    void maxCapacity(int src, int dest);
    // 1.2-------------------------------------------------------------------------------------
    /**
     * Given an origin and a destination, finds the path with minimum transhipments, i.e minimum bus changes (shortest path).\n
     * BFS algorithm, used to determine shortest path from one node to another.
     * @param src is the source stop.
     * @param dest is the destinations stop.
     */
    void minTranshipments(int src, int dest);

    // 2.1/2.2---------------------------------------------------------------------------------
    /**
     * BFS algorithm implementation used to find a path from a source node to a destination node
     * and the capacity of each stop in that that path.
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
     * @return the maximum flow of network.
     * */
    int getMaxFlow(const int &source, const int &destination, Graph &network);
    /**
     * Auxiliary function to Edmounds-Karp algorithm that increases the capacity of the reverse edge from
     * a node a to another node b (i.e., the edge from b to a), by a number of units equal the capacity of the path being considered.
     * @param a is the source stop.
     * @param b is the destination stop.
     * @param capacity is the capacity to be added to the edge b -> a.
     * */
    void increaseRevCapacity (const int &a, const int &b, const int &capacity);
    /**
     * Computes te path from a source node to a destination node according to the "prev" field
     * previously updated by the BFS algorithm.
     * @param source is the source bus stop.
     * @param destination is the destination bus stop.
     * @param maxCapacity is the path capacity that will be updated.
     * */
    vector<int> getPath (const int& source, const int& destination, int& maxCapacity);
    /**
     * Computes all possible paths from a source node to a destination node using BFS.
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
     * @return true if p1 is greater than p2, else returns false.
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
    /**
     * Initializes the residual network of the current network being used.
     * @param residualNetwork is the graph to be initialized.
     */
    void initializeResidualNetwork(vector<Node>& residualNetwork) const;
    /**
     * Finds the shortest path from a source node to a destination node in the residual network, if a path exists.\n
     * BFS algorithm, used to determine shortest path from one node to another.
     * @param src is the source bus stop.
     * @param dest is the destination bus stop.
     * @param residualNetwork is the residual network of the curretn network being analized.
     * @return the shortest path from src to dest in the residual network.
     * If there isn't a path, a vector with size 1 is returned.
     */
    vector<int> findResidualNetworkPath(int src, int dest, vector<Node>& residualNetwork) const;
    /**
     * Finds the maximum flow in the transportation network.
     * @param src is the src bus stop.
     * @param dest is the destination bus stop.
     */
    void getMaxFlow(int src, int dest);

    // 2.4-------------------------------------------------------------------------------------
    /**
     * Finds the earliest stop where every group will be able to reunite. In the worst case, this happens in the destination stop.
     * @param source is the source bus stop.
     * @param dest is the destination bus stop.
     * @param paths is a vector of the paths being taken by each group.
     * @return
     */
    int reuniteGroup(int source, int dest, vector<vector<int>> paths) const;
    // 2.5-------------------------------------------------------------------------------------
    /**
     * Calculates how much time each group will have to wait at the meeting stop.
     * Every group must wait for the last group to arrive.
     * The last group to arrive will wait for 0 min.
     * @param source is the source bus stop.
     * @param reunite is the destination bus stop.
     * @param paths is a vector of the paths being taken by each group.
     */
    void waitTime(int source, int reunite, const vector<vector<int>>& paths) const;
};

#endif