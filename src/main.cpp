#include "Graph.h"
#include "LoadData.h"
#include "Q1_1.h"
#include <iostream>

int main() {
    Graph g(0);
    LoadData data(g);
    data.loadNetwork(12);
    Graph network = data.getNetwork();
    network.maxCapacity(1, 12);
    cout << "------------" << endl;
    network.minTranshipments(1, 12);
    cout << "------------" << endl;
    network.maxCapacity(10, 4);
    cout << "------------" << endl;
    network.minTranshipments(10, 4);
    return 0;
}
