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

bool sortDescendingCapacity(pair<int,double> node1, pair<int,double> node2) {
    if (node1.second == node2.second) {
        return node1.first < node2.first;
    }
    return node1.second > node2.second;
}

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

int Graph::maxCapacity(int source, int goal) {  // O(E * log(V)) sendo E nº de edges e V nº de vertices(nodes)
    vector<pair<int,double>> q = {};
    for (int i = 1; i <= nodes.size(); i++) {
        nodes[i].capacity = INT_MIN;
        q.push_back({i, INT_MIN});
    }

    nodes[source].capacity = INT_MAX;
    changeCapacity(q,source, INT_MAX);
    nodes[source].pred = 0;

    /*
    for (int i = 0; i < q.size(); i++) {
        cout << q[i].second << endl;
    }
     */

    while (!q.empty()) {
        sort(q.begin(), q.end(), sortDescendingCapacity);

        /*
        for (int i = 0; i < q.size(); i++) {
            cout << q[i].first << " : " << q[i].second << endl;
        }

        cout << "---------------" << endl;
         */

        int u = q[0].first;
        int cap = q[0].second;

        //cout << q[0].first << " : " << q[0].second << endl;

        q.erase(q.begin());

        /*
        for (int i = 0; i < q.size(); i++) {
            cout << q[i].first << " : " << q[i].second << endl;
        }

        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
         */

        if (cap == INT_MIN) {
            //cout << "has hit INT_MIN" << endl;
            break;
        }

        for (Graph::Edge edge: nodes[u].adj) {


            int w = min(cap, edge.capacity);
            if (w > nodes[edge.dest].capacity) {
                nodes[edge.dest].capacity = w;
                nodes[edge.dest].pred = u;
                changeCapacity(q, edge.dest, nodes[edge.dest].capacity);
            }
        }
    }

    int capacity = INT_MAX;

    int u = goal;
    vector<int> path;

    while (u != 0) {
        capacity = min(nodes[u].capacity, capacity);
        path.push_back(u);
        u = nodes[u].pred;
    }

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << endl;
    }

    cout << "Capacity: " << capacity << endl;

    return capacity;
}