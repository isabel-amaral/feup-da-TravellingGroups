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
    nodes[src].adj.push_back({dest, capacity, duration, 0});
}

void Graph::initializeResidualNetwork(vector<Node>& residualNetwork) const {
   for (int i = 1; i <= n; i++) {
       for (Edge e: nodes[i].adj) {
           residualNetwork[i].adj.push_back({e.dest, e.capacity, e.duration, e.flow});
           residualNetwork[e.dest].adj.push_back({i, 0, e.duration, e.flow});
       }
   }
}

vector<int> Graph::findResidualNetworkPath(int src, int dest, vector<Node>& residualNetwork) const {
    for (Node& n: residualNetwork) {
        n.visited = false;
        n.prev = 0;
    }

    queue<int> q;
    q.push(src);
    residualNetwork[src].prev = 0;
    residualNetwork[src].visited = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (Edge e: residualNetwork[u].adj) {
            if (!residualNetwork[e.dest].visited && e.capacity != 0) {
                q.push(e.dest);
                residualNetwork[e.dest].prev = u;
                residualNetwork[e.dest].visited = true;
            }
        }
    }

    vector<int> path;
    int currentNode = dest;
    while (currentNode != 0) {
        path.push_back(currentNode);
        currentNode = residualNetwork[currentNode].prev;
    }
    reverse(path.begin(), path.end());
    return path;
}

int Graph::getMaxFlow(int src, int dest) {
    for (int i = 1; i <= n; i++)
        for (Edge e: nodes[i].adj)
            e.flow = 0;
    vector<Node> residualNetwork(n+1);
    initializeResidualNetwork(residualNetwork);

    vector<int> path;
    while ((path=findResidualNetworkPath(src, dest, residualNetwork)).size() > 1) {
        int minCapacity = INT_MAX;
        for (int i = 0; i < path.size()-1; i++) {
            int s = path[i], d = path[i+1];
            for (Edge e: residualNetwork[s].adj)
                if (e.dest == d && e.capacity < minCapacity)
                    minCapacity = e.capacity;
        }

        for (int i = 0; i < path.size()-1; i++) {
            int s = path[i], d = path[i+1];
            //int capacity;
            for (Edge& e: nodes[s].adj) {
                if (e.dest == d) {
                    e.flow += minCapacity;
                    //capacity = e.capacity;
                }
            }
            for (Edge& e: residualNetwork[s].adj)
                if (e.dest == d)
                    e.capacity -= minCapacity;
            for (Edge& e: residualNetwork[d].adj)
                if (e.dest == s)
                    e.capacity += minCapacity;
        }
    }

    int maxFlow = 0;
    for (Edge e: nodes[src].adj)
        maxFlow += e.flow;
    return  maxFlow;
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
    cout << "All elements of the group may reunite at stop " << earliest;
    if (earliest == dest)
        cout << " (only at the end)";
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
    cout << "All groups must wait for group " << lastGroup+1 << endl;
    for (int i = 0; i < travelTime.size(); i++) {
        int waitTime = latestArrivingTime - travelTime[i];
        cout << "Group " << i+1 << " will wait for " << waitTime << " minutes";
        if (waitTime == 0)
            cout << " (will be the last group to arrive)";
        cout << endl;
    }
}
