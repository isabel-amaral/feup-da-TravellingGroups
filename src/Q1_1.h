//
// Created by User on 29/05/2022.
//

#ifndef FEUP_DA_TRAVELLINGGROUPS_Q1_1_H
#define FEUP_DA_TRAVELLINGGROUPS_Q1_1_H

#include "Graph.h"

class Q1_1 {
    Graph graph;
public:
    explicit Q1_1(const Graph& graph1);
    int maxCapacity(int origin);
    static bool sortDescendingCapacity(pair<int,double> node1, pair<int,double> node2);
};


#endif //FEUP_DA_TRAVELLINGGROUPS_Q1_1_H
