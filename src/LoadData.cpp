#include "LoadData.h"

LoadData::LoadData() {}

LoadData::LoadData(Graph transportNetwork) : transportNetwork(transportNetwork) {}

bool LoadData::loadNetwork(int fileID) {
    string filename;
    if (fileID < 10)
        filename = "in0" + to_string(fileID) + ".txt";
    else
        filename = "in" + to_string(fileID) + ".txt";

    ifstream f;
    string line, aux;
    int numNodes, origin, destination, capacity, duration;

    f.open(filename);
    if (!f.is_open()) {
        cout << "O ficheiro nao exite." << endl;
        return false;
    }

    getline(f, line);
    stringstream s(line);
    s >> aux;
    numNodes = stoi(aux);
    transportNetwork = Graph(numNodes);

    while (getline(f, line)) {
        stringstream s(line);
        s >> aux;
        origin = stoi(aux);
        s >> aux;
        destination = stoi(aux);
        s >> aux;
        capacity = stoi(aux);
        s >> aux;
        duration = stoi(aux);

        transportNetwork.addEdge(origin, destination, capacity, duration);
    }

    f.close();
    return true;
}

const Graph &LoadData::getNetwork() const {
    return transportNetwork;
}