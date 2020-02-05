#include "interface.h"
#include "tester.h"
#include <cmath>
#include <windows.h>
#include <iostream>


int main() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int square = 100; //3249
    int points_number = 50; //3249
    Tester tester;
    std::set<Graph::Point> points = Tester::get_points(square, points_number);
    tester.build_graph(points);

    Solver solver(tester.graph);
    solver.completely_solve();

    std::set<Graph::Point> p = tester.graph.get_points();
    std::vector<std::vector<int>> mas((int) sqrt(square), std::vector<int>((int) sqrt(square), 0));

    for (auto &point: p) {
        mas[point.x][point.y] = point.color;
    }

    std::cout << "  ";

    for (int i = 0; i < (int) sqrt(square); i++) {
        std::cout << i % 10 << ' ';
    }

    std::cout << std::endl;

    for (int i = 0; i < (int) sqrt(square); i++) {
        std::cout << i % 10 << ' ';
        for (int j = 0; j < (int) sqrt(square); j++) {
            SetConsoleTextAttribute(hConsole, mas[i][j]);
            if (mas[i][j] != 0) {
                std::cout << 'o' << ' ';
            } else {
                std::cout << ' ' << ' ';
            }
        }
        std::cout << std::endl;
    }

    std::cout << std::endl << tester.graph.size() << " points" << std::endl;
    std::cout << "solution: " << tester.check_solution() << std::endl;

    return 0;
}