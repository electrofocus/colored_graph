//
// Created by Amir on 2/4/2020.
//

#include "solver.h"


Solver::Solver(Graph &_graph) : graph(_graph) {
    current_point = graph.points.begin();
    if (current_point != graph.points.end()) {
        current_neighbour = current_point->second.neighbours.begin();
    }
    _is_solved = false;
    colors = {1, 2, 3, 4, 5};
}

void Solver::step() {
    if (current_point == graph.points.end()) {
        _is_solved = true;
        return;
    }

    if (current_neighbour == current_point->second.neighbours.end()) {
        current_point->second.color = *colors.begin();
        colors = {1, 2, 3, 4, 5};
        current_point++;
        if (current_point != graph.points.end()) {
            current_neighbour = current_point->second.neighbours.begin();
        }
        return;
    }

    colors.erase(graph.points.at(*current_neighbour).color);
    current_neighbour++;

    if (current_neighbour == current_point->second.neighbours.end()) {
        current_point->second.color = *colors.begin();
        colors = {1, 2, 3, 4, 5};
        current_point++;
        if (current_point != graph.points.end()) {
            current_neighbour = current_point->second.neighbours.begin();
        } else {
            _is_solved = true;
            return;
        }
    }
}

void Solver::completely_solve() {
    for (auto &point : graph.points) {
        colors = {1, 2, 3, 4, 5};
        for (auto neighbour : point.second.neighbours) {
            colors.erase(graph.points.at(neighbour).color);
        }
        point.second.color = *colors.begin();
    }
    _is_solved = true;
}
