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

// 1.1 helper-----------------------------------------------------------------------
// "Update" vector with new capacity value for a given node
void Graph::changeCapacity(vector<pair<int,int>> &q, int node, int capacity) const {
    for (auto& i: q)
        if (i.first == node)
            i.second = capacity;
}

// 1.1--------------------------------------------------------------------------
// O(E * log(V)) being E the number of edges and V the number of vertices(nodes)
void Graph::maxCapacity(int src, int dest) {
    vector<pair<int, int>> q = {};
    for (int i = 1; i < nodes.size(); i++) {
        nodes[i].capacity = INT_MIN;
        q.push_back({i, INT_MIN});
        nodes[i].prev = 0;
    }

    nodes[src].capacity = INT_MAX;
    changeCapacity(q, src, INT_MAX);
    nodes[src].prev = 0;
    while (!q.empty()) {
        pair<int, int> maxCapacity = {INT_MIN, INT_MIN};
        vector<pair<int, int>>::iterator it;
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
                nodes[neighbour].prev = u;
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
        u = nodes[u].prev;
    }
    reverse(path.begin(), path.end());
    if (path.size() == 1) {
        cout << "Nao ha caminho entre os dois pontos." << endl;
        return;
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
}

// 1.2---------------------------------------------------------------
void Graph::minTranshipments(int src, int dest) { // TODO: complexity
    for (int v = 1; v < nodes.size(); v++)
        nodes[v].visited = false;

    queue<int> q; // queue of unvisited nodes
    q.push(src);
    nodes[src].visited = true;
    nodes[src].capacity = INT_MAX;
    nodes[src].prev = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto edge : nodes[u].adj) {
            int w = edge.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].prev = u;
                nodes[w].visited = true;
                nodes[w].capacity = min(nodes[u].capacity,edge.capacity);
            }
            if (w == dest)
                break;
        }
    }

    int u = dest;
    vector<int> path;
    int capacity = INT_MAX;
    while (u != 0) {
        capacity = min(nodes[u].capacity, capacity);
        path.push_back(u);
        u = nodes[u].prev;
    }
    reverse(path.begin(), path.end());
    if (path.size() == 1) {
        cout << "Nao ha caminho entre os dois pontos." << endl;
        return;
    }
    cout << "O caminho com menor numero de transbordos e: ";
    for (int i = 0; i < path.size(); i++) {
        if (i == path.size() - 1)
            cout << path[i];
        else cout << path[i] << " -> ";
    }
    cout << endl << "Numero de transbordos: " << path.size()-1 << endl;
    cout << "A capacidade do percurso e de " << capacity << " pessoas." << endl;
}

// 2.3 helper---------------------------------------------------------------
void Graph::initializeResidualNetwork(vector<Node>& residualNetwork) const {
    for (int i = 1; i <= n; i++) {
        for (Edge e: nodes[i].adj) {
            residualNetwork[i].adj.push_back({e.dest, e.capacity, e.duration, e.flow});
            residualNetwork[e.dest].adj.push_back({i, 0, e.duration, e.flow});
        }
    }
}

// 2.3 helper----------------------------------------------------------------------------------------
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

// 2.3------------------------------------
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

// 2.4---------------------------------------------------------------------------
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

// 2.5--------------------------------------------------------------------------
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
    cout << "Todos devem esperar pelo grupo " << lastGroup + 1 << endl;
    for (int i = 0; i < travelTime.size(); i++) {
        int waitTime = latestArrivingTime - travelTime[i];
        cout << "O grupo " << i + 1 << " vai esperar durante " << waitTime << " minutos";
        if (waitTime == 0)
            cout << " (vai ser o ultimo a chegar)";
        cout << endl;
    }
}
