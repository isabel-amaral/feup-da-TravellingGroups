#include "Graph.h"
#include "LoadData.h"
#include <iostream>

int main() {
    Graph g(0);
    LoadData data(g);
    data.loadNetwork(1);
    Graph network = data.getNetwork();
    return 0;
}
