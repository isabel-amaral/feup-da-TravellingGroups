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

void Graph::reuniteGroup(int source, int dest, vector<vector<int>> paths) {
    int earliest = dest;
    int numStopsTillEnd = 0;
    bool reunite = true;
    while (reunite && earliest != source) {
        numStopsTillEnd++;
        int previousStop = paths[0][paths[0].size()-1-numStopsTillEnd];
        for (vector<int> v: paths) {
            if (v[v.size()-1-numStopsTillEnd] != previousStop) {
                reunite = false;
                break;
            }
        }
        if (reunite)
            earliest = previousStop;
    }
    cout << "All elements of the group may reunite at stop " << earliest;
    if (earliest == dest)
        cout << " (only at the end)";
    cout << endl;
}