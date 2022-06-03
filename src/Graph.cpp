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

// "Update" vector with new capacity value for a given node
void Graph::changeCapacity(vector<pair<int,int>> &q, int node, int capacity) const {
    for (auto& i: q)
        if (i.first == node)
            i.second = capacity;
}

// Get the path with maximum capacity from a given source node to a destination node
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

//get shortest path from a source node to a destination node
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
    cout << "Todos devem esperar pelo grupo " << lastGroup + 1 << endl;
    for (int i = 0; i < travelTime.size(); i++) {
        int waitTime = latestArrivingTime - travelTime[i];
        cout << "O grupo " << i + 1 << " vai esperar durante " << waitTime << " minutos";
        if (waitTime == 0)
            cout << " (vai ser o ultimo a chegar)";
        cout << endl;
    }
}

bool Graph::bfsCapacity(const int &source, const int &target) {
    queue<int> visited;

    for (int i = 1; i < nodes.size(); i++){
        nodes[i].visited = false;
        nodes[i].prev = -1;
    }

    nodes[source].visited = true;
    nodes[source].prev = 0;
    nodes[source].capacity = INT_MAX;
    visited.push(source);

    while (!visited.empty()) {
        int u = visited.front();
        visited.pop();
        for (auto e : nodes[u].adj) {
            int w = e.dest;

            if (e.capacity <= 0)
                continue;

            if (!nodes[w].visited) { // new node
                visited.push(w);
                nodes[w].visited = true;
                nodes[w].prev = u;
                nodes[w].capacity = min(nodes[u].capacity, e.capacity);
            }
            if (w == target)  return true;
        }
    }
    return false;
}

vector<int> Graph::getPath(const int &source, const int &destination, int& maxCapacity) {
        maxCapacity = INT_MAX;
        vector<int> path;
        int node = destination;

        do {
            path.insert(path.begin(), node);
            maxCapacity = min(maxCapacity, nodes[node].capacity);
            node = nodes[node].prev;
        } while (node != 0);
        return path;
}

int Graph::getMaxFlow(const int &source, const int &destination, Graph &network) {
    int criticalEdge;
    int maxFlow = 0;
    vector <int> path;

    for (int i=1; i<nodes.size(); i++) {
        nodes[i].capacity = 0;
        for (int j=0; j<nodes[i].adj.size(); j++) {
            network.nodes[i].adj[j].flow = 0;
        }

    }

    while (bfsCapacity(source, destination)) {  //while there is a path from source to destination
        path = getPath(source, destination, criticalEdge);

        for (int i=0; i<path.size()-1; i++) {
            int start = path[i];
            int end = path[i+1];

            for(int j=0; j<nodes[start].adj.size(); j++) {
                if (nodes[start].adj[j].dest == end) {
                    nodes[start].adj[j].capacity -= criticalEdge;
                    increaseRevCapacity(start, end, criticalEdge);
                    network.nodes[start].adj[j].flow += criticalEdge;
                    break;
                }
            }
        }
        maxFlow += criticalEdge;
    }
    return maxFlow;
}

void Graph::increaseRevCapacity(const int &start, const int &end, const int &capacity) {
    for (auto e: nodes[end].adj) {
        if (e.dest == start) {
            e.capacity += capacity;
            return;
        }
    }
    addEdge(end, start, capacity, 0);
}

void Graph::getAllPaths(const int &source, const int &target, vector<pair<vector<int>,int>> &result) {
    queue<vector<int>> paths;
    vector<int> currentPath;

    currentPath.push_back(source);
    paths.push(currentPath);

    while (!paths.empty()) {
        currentPath = paths.front();
        paths.pop();
        int last = currentPath.back();

        if (last == target)
            result.push_back(make_pair(currentPath, getMaxCapacity (currentPath)));

        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for (auto e: nodes[last].adj) {
            if (std::find(currentPath.begin(), currentPath.end(), e.dest) == currentPath.end() && e.flow > 0) {
                vector<int> newpath = currentPath;
                newpath.push_back(e.dest);
                paths.push(newpath);
            }
        }
    }
    sort(result.begin(), result.end(), comparePaths);
}

int Graph::getMaxCapacity(const vector<int> &path) {
    int maxCapacity = INT_MAX;

    for (int i=0; i<path.size()-1; i++) {
        int start = path[i];
        int end = path[i+1];

        for(auto e : nodes[start].adj) {
            if (e.dest == end && e.flow < maxCapacity)
                maxCapacity = e.flow;
        }
    }
    return maxCapacity;
}

bool Graph::comparePaths(const pair<vector<int>,int>& a, const pair<vector<int>,int>& b) {
    return a.second > b.second;
}

void Graph::separateGroup(const int &src, const int &target, int dimension, Graph& network, int extra)  {
    int maxFlow, maxCapacity, subGroupDimension, countGroups = 0;
    vector< pair<vector<int>,int> >  paths;

    maxFlow = getMaxFlow(src, target, network);
    network.getAllPaths(src, target, paths);

    if (paths.empty()){
        cout << "Nao ha caminho entre os dois pontos." << endl;
        return;
    }

    cout << "Fluxo maximo= " << maxFlow << endl;
    cout << "--------------------------------------------" << endl;

    int i = 0;
    while (dimension > 0) {
        maxCapacity = paths[i].second;
        subGroupDimension = min(dimension, maxCapacity);
        countGroups++;

        cout << "Group" << countGroups << " (n=" << subGroupDimension << "): ";
        printPath(paths[i].first);

        i = (i+1)%paths.size();
        dimension -= subGroupDimension;
    }

    if (extra > 0) {
        cout << "Corrigido: " << endl;

        if (dimension%maxFlow > 0) {    //if there is still space in the last subgroup
            i = (i> 0) ? i -1 : paths.size()-1;
            extra += subGroupDimension;
            countGroups --;
        }

        while (extra > 0) {
            subGroupDimension = min(extra, paths[i].second);
            countGroups++;

            cout << "Group" << countGroups << " (n=" << subGroupDimension << "): ";
            printPath(paths[i].first);

            i = (i+1)%paths.size();
            extra -= subGroupDimension;
        }
    }
}

void Graph::printPath(const vector<int> &path) {
    cout << path[0];
    for (int i=1; i<path.size(); i++)
        cout << " -> " << path[i];
    cout << endl;
}