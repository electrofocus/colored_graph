//
// Created by Amir Mullagaliev on 14-Oct-2019
//

#include "graph.h"

#pragma once

class Solver {
private:
    Graph &graph;
    std::map<std::pair<int, int>, Graph::Point>::iterator current_point;
    std::set<std::pair<int, int>>::iterator current_neighbour;
    std::set<int> colors;

    bool _is_solved;

public:
    explicit Solver(Graph &_graph);

    void step();

    void completely_solve();

    bool is_solved() {
        return _is_solved;
    }
};
