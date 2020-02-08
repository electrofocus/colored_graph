//
// Created by Amir on 2/4/2020.
//

#include "tester.h"


std::set<Graph::Point> Tester::get_points(int square, int points_number) {
    std::default_random_engine rng(std::random_device{}());
    int dimension = (int) sqrt(square) - 1;
    std::uniform_int_distribution<int> point_dist(0, dimension);

    std::set<Graph::Point> points;
    while (points.size() < points_number) {
        points.insert(Graph::Point(point_dist(rng), point_dist(rng)));
    }

    return points;
}

void Tester::build_graph(int square, int points_number) {
    std::set<Graph::Point> points = get_points(square, points_number);

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

Tester::Result Tester::time_test(int square, int points_number) {
    int steps = 0;
    build_graph(square, points_number);

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

    return {graph.size(), steps, time};
}

bool Tester::check_solution() {
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

void Tester::print_graph(int square) {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    std::set<Graph::Point> points = graph.get_points();
    std::vector<std::vector<int>> mas((int) sqrt(square), std::vector<int>((int) sqrt(square), -1));
    for (auto &point: points) {
        mas[point.x][point.y] = point.color;
    }
    std::cout << std::endl << "  ";

    for (int i = 0; i < (int) sqrt(square); i++) {
        std::cout << i % 10 << ' ';
    }

    std::cout << std::endl;

    for (int i = 0; i < (int) sqrt(square); i++) {
        std::cout << i % 10 << ' ';
        for (int j = 0; j < (int) sqrt(square); j++) {
            SetConsoleTextAttribute(hConsole, mas[i][j]);
            if (mas[i][j] != -1) {
                std::cout << 'o' << ' ';
            } else {
                std::cout << ' ' << ' ';
            }
        }
        std::cout << std::endl;
    }
}

void Tester::print_result(Result result) {
    std::cout << result.points << " points, " << result.steps << " steps, " << result.time
              << " secs, (secs/steps): " << result.time / result.steps << std::endl;
}
