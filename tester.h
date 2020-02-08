//
// Created by Amir on 04-Dec-19.
//

#include "solver.h"
#include <random>
#include <ctime>
#include <iostream>
#include <windows.h>

#pragma once


class Tester {
private:
    static std::set<Graph::Point> get_points(int square, int points_number);

public:
    struct Result {
        int points;
        int steps;
        double time;
    };

    Graph graph;

    Tester() = default;

    void build_graph(int square, int points_number);

    Result time_test(int square, int points_number);

    bool check_solution();

    void print_graph(int square);

    static void print_result(Result result);
};
