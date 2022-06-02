#ifndef FEUP_DA_TRAVELLINGGROUPS_LOADDATA_H
#define FEUP_DA_TRAVELLINGGROUPS_LOADDATA_H

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class LoadData {
private:
    Graph transportNetwork;
public:
    LoadData();
    LoadData(Graph transportNetwork);
    bool loadNetwork(int fileID);
    const Graph& getNetwork() const;
};

#endif //FEUP_DA_TRAVELLINGGROUPS_LOADDATA_H
