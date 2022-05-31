#include "Graph.h"
#include "LoadData.h"
#include <iostream>

int main() {
    Graph g(0);
    LoadData data(g);
    data.loadNetwork(12);
    Graph network = data.getNetwork();

    vector<vector<int>> paths1;
    vector<int> v1 = {1,2,4,8,10,12};
    vector<int> v2 = {1,3,5,9,10,12};
    //necessário corrigir para este caso
    vector<int> v3 = {1,2,4,8,10,11,12};
    paths1.push_back(v1);
    paths1.push_back(v2);
    network.reuniteGroup(1, 12, paths1);
    paths1.push_back(v3);
    network.reuniteGroup(1, 12, paths1);

    vector<vector<int>> paths2;
    vector<int> v4 = {1,2,4,8,10,12};
    vector<int> v5 = {1,2,4,8,10,12};
    paths2.push_back(v4);
    paths2.push_back(v5);
    network.reuniteGroup(1, 12, paths2);
    return 0;
}
