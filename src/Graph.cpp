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
    for (auto& i: q)
        if (i.first == node)
            i.second = capacity;
}

// Get the path with maximum capacity from a given source node to a destination node
// O(E * log(V)) being E the number of edges and V the number of vertices(nodes)
int Graph::maxCapacity(int src, int dest) {
    vector<pair<int,double>> q = {};
    for (int i = 1; i < nodes.size(); i++) {
        nodes[i].capacity = INT_MIN;
        q.push_back({i, INT_MIN});
    }

    nodes[src].capacity = INT_MAX;
    changeCapacity(q, src, INT_MAX);
    nodes[src].pred = 0;
    while (!q.empty()) {
        pair<int,double> maxCapacity = {INT_MIN, INT_MIN};
        vector<pair<int, double>>::iterator it;
        for (int i = 0; i < q.size(); i++) {
            if (q[i].second > maxCapacity.second) {
                maxCapacity = q[i];
                it = q.begin()+i;
            }
        }
        int u = maxCapacity.first;
        int cap = maxCapacity.second;
        if (cap == INT_MIN)
            break;
        q.erase(it);

        for (Edge edge: nodes[u].adj) {
            int w = min(cap, edge.capacity);
            int neighbour = edge.dest;
            if (w > nodes[neighbour].capacity) {
                nodes[neighbour].capacity = w;
                nodes[neighbour].pred = u;
                changeCapacity(q, neighbour, nodes[neighbour].capacity);
            }
        }
    }

    int capacity = INT_MAX, u = dest;
    vector<int> path;
    // worst case (if path passes by every node): O(V) where V is the number of nodes/stops in the transport network
    while (u != 0) {
        capacity = min(nodes[u].capacity, capacity);
        path.push_back(u);
        u = nodes[u].pred;
    }
    reverse(path.begin(), path.end());
    if (path.size() == 1) {
        cout << "Nao ha caminho entre os dois pontos." << endl;
        return 0;
    }
    cout << "O caminho de capacidade maxima e: ";
    for (int i = 0; i < path.size(); i++) {
        if (i == path.size()-1) {
            cout << path[i] << endl;
            break;
        }
        cout << path[i] << " -> ";
    }
    cout << "Numero de transbordos: " << path.size()-1 << endl;
    cout << "A capacidade do percurso e de " << capacity << " pessoas." << endl;
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
