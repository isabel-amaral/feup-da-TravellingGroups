#include "Graph.h"
#include "LoadData.h"
#include "Q1_1.h"
#include <iostream>

int main() {
    Graph g(0);
    LoadData data(g);
    data.loadNetwork(3);
    Graph network = data.getNetwork();
    network.maxCapacity(1, 4);
    cout << "------------" << endl;
    network.BFS(1, 4);
    return 0;
}
