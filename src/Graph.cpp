#include "Graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num) : n(num), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int capacity, int duration) {
    if (src<1 || src>n || dest<1 || dest>n)
        return;
    nodes[src].adj.push_back({dest, capacity, duration});
}

// "Update" vector with new capacity value for a given node
void changeCapacity(vector<pair<int,double>> &q, int node, double capacity) {
    bool found = false;
    for (int i = 0; i < q.size(); i++) {
        if (q[i].first == node) {
            q[i].second = capacity;
            found = true;
        }
    }
    if (!found) {
        q.push_back({node,capacity});
    }
}

// Get the path and it's capacity from a source node to a destination node
int Graph::maxCapacity(int source, int goal) {  // O(E * log(V)) being E the number of edges and V the number of vertices(nodes)
    vector<pair<int,double>> q = {};
    for (int i = 1; i <= nodes.size(); i++) {
        nodes[i].capacity = INT_MIN;
        q.push_back({i, INT_MIN});
    }

    nodes[source].capacity = INT_MAX;
    changeCapacity(q,source, INT_MAX);
    nodes[source].pred = 0;

    while (!q.empty()) {

        pair<int,double> temp = {0,0};

        for (int i = 0;i < q.size(); i++) {
            if (q[i].second > temp.second)
                temp = q[i];
        }

        int u = temp.first;
        int cap = temp.second;

        q.erase(q.begin());

        if (cap == INT_MIN) {
            break;
        }

        for (Graph::Edge edge: nodes[u].adj) {

            int w = min(cap, edge.capacity);
            int neighbour = edge.dest;
            if (w > nodes[neighbour].capacity) {
                nodes[neighbour].capacity = w;
                nodes[neighbour].pred = u;
                changeCapacity(q, neighbour, nodes[neighbour].capacity);
            }
        }
    }

    int capacity = INT_MAX;                             //
                                                        //
    int u = goal;                                       //
    vector<int> path;                                   //
                                                        //
    while (u != 0) {                                    //
        capacity = min(nodes[u].capacity, capacity);    //
        path.push_back(u);                              //
        u = nodes[u].pred;                              //  This part of the code has complexity
    }                                                   //
                                                        //  O(V) where V is the number of vertices(nodes)
    reverse(path.begin(), path.end());                  //
                                                        //
    cout << "The path with max capacity is: ";          //
                                                        //
    for (int i = 0; i < path.size(); i++) {             //
        if (i == path.size()-1) {                       //
            cout << path[i] << endl;                    //
            break;                                      //
        }                                               //
        cout << path[i] << " -> ";                      //
    }                                                   //

    cout << endl << "Numero de transbordos: " << path.size()-1 << endl;
    cout << capacity << " people fit in the bus." << endl;

    return capacity;
}

//get shortest path from a source node to a destination node
void Graph::BFS(int source, int goal) { // TODO: complexity
    for (int v=1; v<=nodes.size(); v++) {
        nodes[v].visited = false;
    }
    queue<int> q; // queue of unvisited nodes

    q.push(source);
    nodes[source].visited=true;
    nodes[source].capacity = INT_MAX;
    nodes[source].pred = 0;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto edge : nodes[u].adj) {
            int w = edge.dest;

            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].pred = u;
                nodes[w].visited = true;
                nodes[w].capacity = min(nodes[u].capacity,edge.capacity);
            }

            if(w==goal) break;
        }
    }

    int u = goal;
    vector<int> path;

    int capacity = INT_MAX;

    while (u != 0) {
        capacity = min(nodes[u].capacity, capacity);
        path.push_back(u);
        u = nodes[u].pred;
    }
    reverse(path.begin(), path.end());
    cout << "The path with BFS is: ";

    for (int i = 0; i < path.size(); i++) {
        if (i == path.size() - 1)
            cout << path[i];
        else cout << path[i] << " -> ";
    }

    cout << endl << "Numero de transbordos: " << path.size()-1 << endl;
    cout << capacity << " people fit in the bus." << endl;
}
