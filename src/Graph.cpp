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
    nodes[src].adj.push_back({dest, capacity, 0, duration});
}

// 1.1 helper-----------------------------------------------------------------------
// "Update" vector with new capacity value for a given node
void Graph::changeCapacity(vector<pair<int,int>> &q, int node, int capacity) const {
    for (auto& i: q)
        if (i.first == node)
            i.second = capacity;
}

// 1.1--------------------------------------------------------------------------
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

// 2.1/2.2 helper----------------------------------------------
// time complexity: O(V + E), V being the number of nodes and E being the number of edges
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

// 2.1/2.2 helper------------------------------------------------------------------------
// time complexity: O(V), V being the number of nodes
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

// 2.1/2.2---------------------------------------------------------------------------------
// time complexity: O(V * E^2), V being the number of nodes and E being the number of edges
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

// 2.1/2.2 helper-----------------------------------------------------------------------
// time complexity: O(E), E being the number of edges
void Graph::increaseRevCapacity(const int &a, const int &b, const int &capacity) {
    for (auto e: nodes[b].adj) {
        if (e.dest == a) {
            e.capacity += capacity;
            return;
        }
    }
    addEdge(b, a, capacity, 0);
}

// 2.1/2.2 helper-------------------------------------------------------------------------------------
// time complexity: O(V ^ V), V being the number of nodes
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
            result.push_back(make_pair(currentPath, getPathMaxCapacity(currentPath)));

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

//2.1/2.2 helper------------------------------------
// time complexity: O(V + E), V being the number of nodes and E being the number of edges
int Graph::getPathMaxCapacity(const vector<int> &path) {
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

// 2.1/2.2 sorting function---------------------------------------------------------------
bool Graph::comparePaths(const pair<vector<int>,int>& p1, const pair<vector<int>,int>& p2) {
    return p1.second > p2.second;
}

// 2.1/2.2--------------------------------------------------------------------------------------------------------------
// time complexity: O(V ^ V), V being the number of nodes and E being the number of edges
// space complexity: O (V ^ V), V being the number of nodes- space occupied by all paths from src to target
vector<vector<int>> Graph::separateGroup(const int &src, const int &target, int dimension, Graph& network, int extra)  {
    int maxFlow, maxCapacity, subGroupDimension, countGroups = 0, availableSeats;
    vector< pair<vector<int>,int> >  paths;
    vector <vector<int>> usedPaths;

    maxFlow = getMaxFlow(src, target, network); // O (V * E^2)
    availableSeats = maxFlow;
    network.getAllPaths(src, target, paths);    // O (V^V)

    if (paths.empty()){
        cout << "\nNao ha caminho entre os dois pontos." << endl;
        return usedPaths;
    }

    cout << "\nFluxo maximo= " << maxFlow << endl;
    if (dimension > maxFlow || (dimension == maxFlow && extra > 0))
        cout << "Apenas " << maxFlow << " pessoas podem ser transportadas."  << endl;
    cout << "--------------------------------------------" << endl;

    int pathIndex = 0;
    while (availableSeats > 0 && dimension > 0) {
        maxCapacity = paths[pathIndex].second;
        subGroupDimension = min(dimension, maxCapacity);
        countGroups++;

        cout << "Group" << countGroups << " (n=" << subGroupDimension << "): ";
        printPath(paths[pathIndex].first);

        dimension -= subGroupDimension;
        availableSeats -= subGroupDimension;
        usedPaths.push_back(paths[pathIndex].first);
        pathIndex++;
    }

    if (availableSeats == 0 || extra == 0)
        return usedPaths;

    if (extra > availableSeats)
        cout << "\nSo e possivel transportar mais " << availableSeats << " pessoa(s): " << endl;

    if (paths[pathIndex - 1].second > subGroupDimension) { //if there is still available space on the last used path
        extra += subGroupDimension;
        availableSeats += subGroupDimension;
        pathIndex--;
        usedPaths.pop_back();
    }
    else
        countGroups++;

    cout << "\nCorrigido: " << endl;
    while (availableSeats > 0 && extra > 0) {
        subGroupDimension = min(extra, paths[pathIndex].second);

        cout << "Grupo" << countGroups << " (n=" << subGroupDimension << "): ";
        printPath(paths[pathIndex].first);

        extra -= subGroupDimension;
        availableSeats -= subGroupDimension;
        usedPaths.push_back(paths[pathIndex].first);
        pathIndex++;
        countGroups++;
    }
    return usedPaths;
}

// 2.1 helper-----------------------------------
void Graph::printPath(const vector<int> &path) {
    cout << path[0];
    for (int i=1; i<path.size(); i++)
        cout << " -> " << path[i];
    cout << endl;
}

// 2.3 helper---------------------------------------------------------------
// time complexity: O(V + E), V being the number of nodes and E being the number of edges
void Graph::initializeResidualNetwork(vector<Node>& residualNetwork) const {
    for (int i = 1; i <= n; i++) { // O(V) every node will be visited
        for (Edge e: nodes[i].adj) { // O(E) after all iterations (after visiting every node, every edge was visited)
            residualNetwork[i].adj.push_back({e.dest, e.capacity, e.duration, e.flow});
            residualNetwork[e.dest].adj.push_back({i, 0, e.duration, e.flow});
        }
    }
}

// 2.3 helper----------------------------------------------------------------------------------------
// time complexity: O(V + E), V being the number of nodes and E being the number of edges
vector<int> Graph::findResidualNetworkPath(int src, int dest, vector<Node>& residualNetwork) const {
    for (Node& n: residualNetwork) { // O(V), every node is initialized as unvisited and its prev being 0
        n.visited = false;
        n.prev = 0;
    }

    queue<int> q;
    q.push(src);
    residualNetwork[src].prev = 0;
    residualNetwork[src].visited = true;
    // O(V + E)
    while (!q.empty()) { // O(V), every node must be visited
        int u = q.front();
        q.pop();
        for (Edge e: residualNetwork[u].adj) { // O(E) after all iterations (after visiting every node, every edge was visited)
            if (!residualNetwork[e.dest].visited && e.capacity != 0) {
                q.push(e.dest);
                residualNetwork[e.dest].prev = u;
                residualNetwork[e.dest].visited = true;
            }
        }
    }

    vector<int> path;
    int currentNode = dest;
    // O(V) in worst case (if the minimum path from src to dest passes by every node)
    while (currentNode != 0) {
        path.push_back(currentNode);
        currentNode = residualNetwork[currentNode].prev;
    }
    // O(v)
    reverse(path.begin(), path.end());
    return path;
}

// 2.3------------------------------------
// time complexity: O(E^2 * V), V being the number of nodes and E being the number of edges
// space complexity: O(V), V being the number os nodes - space occupied by the residual graph
void Graph::getMaxFlow(int src, int dest) {
    for (int i = 1; i <= n; i++)
        for (Edge& e: nodes[i].adj)
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
            for (Edge& e: nodes[s].adj) {
                if (e.dest == d) {
                    e.flow += minCapacity;
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
    cout << "No maximo e possivel transportar um grupo de " << maxFlow << " pessoas." << endl;
}

// 2.4---------------------------------------------------------------------------
// time complexity: O(V), V being the number of nodes
// space complexity: O(1)
int Graph::reuniteGroup(int source, int dest, vector<vector<int>> paths) const {
    int earliest = dest;
    int numStopsTillEnd = 0;
    bool reunite = true;
    while (reunite && earliest != source) { // O(V) in worst case (is all the paths are the same and if the path passes by every node)
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
    return earliest;
}

// 2.5--------------------------------------------------------------------------
// time complexity: O(P * E), P being the number of different groups (which are all taking one path) and E being the number of edges
// space complexity: O(P)
void Graph::waitTime(int source, int reunite, const vector<vector<int>>& paths) const {
    vector<int> travelTime;
    // O(P * E) in worst case
    for (vector<int> v: paths) { // O(P)
        int time = 0;
        int stopIndex = 0;
        int stop = source;
        while (stop != reunite) {
            stopIndex++;
            for (Edge e: nodes[stop].adj) { //O(E) in worst case (if we need to analyze every edge)
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
    // O(P)
    for (int i = 0; i < travelTime.size(); i++) {
        if (travelTime[i] > latestArrivingTime) {
            latestArrivingTime = travelTime[i];
            lastGroup = i;
        }
    }
    cout << "Todos devem esperar pelo grupo " << lastGroup + 1 << endl;
    // O(P)
    for (int i = 0; i < travelTime.size(); i++) {
        int waitTime = latestArrivingTime - travelTime[i];
        cout << "O grupo " << i + 1 << " vai esperar durante " << waitTime << " minutos";
        if (waitTime == 0)
            cout << " (vai ser o ultimo a chegar)";
        cout << endl;
    }
}
