//
// Created by Amir on 2/6/2020.
//

#include "graph.h"


bool operator<(const Graph::Point &a, const Graph::Point &b) {
    return a.x < b.x || (b.x >= a.x && a.y < b.y);
}