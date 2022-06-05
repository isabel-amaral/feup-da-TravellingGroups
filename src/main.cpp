#include "Menu.h"

int main() {
/*  testing 1.1/1.2
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
    network.minTranshipments(10, 4); */

/*  testing 2.1/ 2.2
    Graph g(0);
    LoadData data(g);
    data.loadNetwork(16);
    Graph network = data.getNetwork();

    Graph residualNetwork;

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 18,network);    //maxFlow =21

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 21,network);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 24,network);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 12,network, 3);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 18,network, 2);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 17,network, 3);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 9,network, 1);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 1,network, 1);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 22,network, 1);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 21,network, 1);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 20,network, 2);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 20,network, 1);

    residualNetwork = network;
    residualNetwork.separateGroup(1, 5, 12,network, 15);*/

/*  testing 2.3
    Graph g1;
    LoadData data1(g1);
    data1.loadNetwork(14);
    g1 = data1.getNetwork();
    g1.getMaxFlow(1, 6);

    Graph g2;
    LoadData data2(g2);
    data2.loadNetwork(15);
    g2 = data2.getNetwork();
    g2.getMaxFlow(1, 6); */

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
    network.reuniteGroup(1, 12, paths2); */

    Menu();
    return 0;
}
