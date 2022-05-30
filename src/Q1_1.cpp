//
// Created by User on 29/05/2022.
//

#include <set>
#include "Q1_1.h"
#include "algorithm"

Q1_1::Q1_1(const Graph& graph1) : graph(graph1) {
    this->graph = graph1;
}

bool operator==(Graph::Node node1, Graph::Node node2) {
    if (node1.capacity == node2.capacity && node1.adj == node2.adj)
        return true;
    return false;
}

bool operator==(Graph::Edge edge1, Graph::Edge edge2) {
    if (edge1.capacity == edge2.capacity && edge1.dest == edge2.dest && edge1.duration == edge2.duration)
        return true;
    return false;
}
