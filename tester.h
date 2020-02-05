//
// Created by Amir on 04-Dec-19.
//

#pragma once

#include "solver.h"
#include <random>
#include <ctime>


class Tester {
public:
    Graph graph;

    Tester() = default;

    static std::set<Graph::Point> get_points(int square, int points_number) {
        std::default_random_engine rng(std::random_device{}());
        int dimension = (int) sqrt(square) - 1;
        std::uniform_int_distribution<int> point_dist(0, dimension);

        std::set<Graph::Point> points;
        while (points.size() < points_number) {
            points.insert(Graph::Point(point_dist(rng), point_dist(rng)));
        }

        return points;
    }

    void build_graph(const std::set<Graph::Point> &points) {
        for (auto point_1 = points.begin(); point_1 != points.end(); point_1++) {
            for (auto point_2 = point_1; point_2 != points.end(); point_2++) {
                if ((abs(point_1->x - point_2->x) == 1 && abs(point_1->y - point_2->y) == 0) ||
                    (abs(point_1->x - point_2->x) == 0 && abs(point_1->y - point_2->y) == 1) ||
                    ((abs(point_1->x - point_2->x) == 1 && abs(point_1->y - point_2->y) == 1) &&
                     ((point_1->x > point_2->x && point_1->y > point_2->y &&
                       !graph.is_edge(Graph::Point(point_1->x - 1, point_1->y),
                                      Graph::Point(point_2->x + 1, point_2->y))) ||
                      (point_2->x > point_1->x && point_2->y > point_1->y &&
                       !graph.is_edge(Graph::Point(point_2->x - 1, point_2->y),
                                      Graph::Point(point_1->x + 1, point_1->y))) ||
                      (point_2->x > point_1->x && point_1->y > point_2->y &&
                       !graph.is_edge(Graph::Point(point_2->x - 1, point_2->y),
                                      Graph::Point(point_1->x + 1, point_1->y))) ||
                      (point_1->x > point_2->x && point_2->y > point_1->y &&
                       !graph.is_edge(Graph::Point(point_1->x - 1, point_1->y),
                                      Graph::Point(point_2->x + 1, point_2->y)))))) {
                    graph.add_point(*point_1);
                    graph.add_point(*point_2);
                    graph.add_edge(*point_1, *point_2);
                }
            }
        }
    }

    void time_test(int square, int points_number) {
        int steps = 0;
        build_graph(Tester::get_points(square, points_number));

        Solver solver(graph);
        while (!solver.is_solved()) {
            solver.step();
            steps++;
        }

        graph.reset_color();
        clock_t begin = clock();
        solver.completely_solve();
        clock_t end = clock();
        double time = (double) (end - begin) / CLOCKS_PER_SEC;
        std::cout << graph.size() << " points, " << steps << " steps, " << time
                  << " secs, (time/steps): " << (double) time / steps << std::endl;
        graph.clear();
    }

    void test() {
        int square = 5200;
        time_test(square, 5000);
        time_test(square, 4000);
        time_test(square, 3006);
        time_test(square, 2049);
        time_test(square, 1150);
    }

    bool check_solution() {
        for (auto &point: graph.points) {
            for (auto neighbour: point.second.neighbours) {
                auto neigh = graph.points.at(neighbour);
                if (neigh.color == point.second.color) {
                    return false;
                }
            }
        }
        return true;
    }
};

