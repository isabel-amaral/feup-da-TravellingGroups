#include "Menu.h"

int main() {
/*  testing 2.3
    Graph g1;
    LoadData data1(g1);
    data1.loadNetwork(14);
    g1 = data1.getNetwork();
    cout << g1.getMaxFlow(1, 6) << endl;

    Graph g2;
    LoadData data2(g2);
    data2.loadNetwork(15);
    g2 = data2.getNetwork();
    cout << g2.getMaxFlow(1, 6) << endl; */

/*  testing 2.4/2.5
    Graph g(0);
    LoadData data(g);
    data.loadNetwork(12);
    Graph network = data.getNetwork();

    vector<vector<int>> paths1;
    vector<int> v1 = {1,2,4,8,10,12}; // 22 till node 10, 28 till node 12
    vector<int> v2 = {1,3,5,9,10,12}; // 27 till node 10, 33 till node 12
    vector<int> v3 = {1,2,4,8,10,11,12}; //27 till node 12
    paths1.push_back(v1);
    paths1.push_back(v2);
    network.reuniteGroup(1, 12, paths1);
    network.waitTime(1, 10, paths1);
    cout << endl;
    paths1.push_back(v3);
    network.reuniteGroup(1, 12, paths1);
    network.waitTime(1, 12, paths1);
    cout << endl;

    vector<vector<int>> paths2;
    vector<int> v4 = {1,2,4,8,10,12};
    vector<int> v5 = {1,2,4,8,10,12};
    paths2.push_back(v4);
    paths2.push_back(v5);
    network.reuniteGroup(1, 12, paths2);*/

    Menu();
    return 0;
}
