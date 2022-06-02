#include "Graph.h"

Graph::Graph() : n(0), nodes(1) {

}

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(int num) : n(num), nodes(num+1) {
}

// Add edge from source to destination with a certain weight
void Graph::addEdge(int src, int dest, int capacity, int duration) {
    if (src<1 || src>n || dest<1 || dest>n)
        return;
    nodes[src].adj.push_back({dest, capacity, duration});
}

void Graph::reuniteGroup(int source, int dest, vector<vector<int>> paths) const {
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
    cout << "Todos os elementos do grupo podem-se reunir na paragem " << earliest;
    if (earliest == dest)
        cout << " (apenas no fim do percurso)";
    cout << endl;
}

void Graph::waitTime(int source, int reunite, vector<vector<int>> paths) const {
    vector<int> travelTime;
    for (vector<int> v: paths) {
        int time = 0;
        int stopIndex = 0;
        int stop = source;
        while (stop != reunite) {
            stopIndex++;
            for (Edge e: nodes[stop].adj) {
                if (e.dest == v[stopIndex]) {
                    time += e.duration;
                    break;
                }
            }
            stop = v[stopIndex];
        }
        travelTime.push_back(time);
    }

    // group which will arrive last to the meeting stop
    // all other groups must wait a certain amount of time
    int latestArrivingTime = INT_MIN;
    int lastGroup;
    for (int i = 0; i < travelTime.size(); i++) {
        if (travelTime[i] > latestArrivingTime) {
            latestArrivingTime = travelTime[i];
            lastGroup = i;
        }
    }
    cout << "Todos devem esperar pelo grupo " << lastGroup+1 << endl;
    for (int i = 0; i < travelTime.size(); i++) {
        int waitTime = latestArrivingTime - travelTime[i];
        cout << "O grupo " << i+1 << " vai esperar durante " << waitTime << " minutos";
        if (waitTime == 0)
            cout << " (vai ser o ultimo a chegar)";
        cout << endl;
    }
}

void Graph::bfsCapacity(const int& source, const int& destination) {
    queue<int> visited;

    for (int i = 1; i < nodes.size(); i++){
        nodes[i].visited = false;
        nodes[i].parent = -1;
    }

    nodes[source].visited = true;
    nodes[source].parent = 0;
    visited.push(source);

    while (!visited.empty()) {
        int u = visited.front();
        visited.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited && e.capacity > 0) { // new node
                visited.push(w);
                nodes[w].visited = true;
                nodes[w].parent = u;
            }

            if (w == destination)
                return;
        }
    }
}