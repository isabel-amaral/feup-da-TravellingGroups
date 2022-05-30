#include "Graph.h"
#include "LoadData.h"
#include "Q1_1.h"
#include <iostream>

int main() {
    Graph g(0);
    LoadData data(g);
    data.loadNetwork(11);
    Graph network = data.getNetwork();
    network.maxCapacity(1, 40);
    return 15;
}
