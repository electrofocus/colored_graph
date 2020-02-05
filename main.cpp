#include "interface.h"
#include "tester.h"
#include <cmath>
#include <windows.h>
#include <iostream>


int main() {
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int square = 9; //3249
    int points_number = 16; //3249
    Tester tester;
    auto points = Tester::get_points(square, points_number);
    tester.build_graph(points);

    Solver solver(tester.graph);

    solver.completely_solve();

    int k = 0;
//    while (!solver.is_solved()) {
//        solver.step();
//        k++;
//    }

    {
        auto p = tester.graph.get_points();

//    for (const auto& point: p) {
//        cout << '(' << point.x << ',' << point.y << ") color" << point.color << endl;
//    }

        std::vector<std::vector<int>> mas(square, std::vector<int>(square, 0));

        for (const auto &point: p) {
            mas[point.x][point.y] = point.color;
        }

        std::cout << "  ";

        for (int i = 0; i < sqrt(square) + 1; i++) {
            std::cout << i % 10 << ' ';
        }

        std::cout << std::endl;

        for (int i = 0; i < sqrt(square) + 1; i++) {
            std::cout << i % 10 << ' ';
            for (int j = 0; j < sqrt(square) + 1; j++) {
                SetConsoleTextAttribute(hConsole, mas[i][j]);
                if (mas[i][j] != 0) {
                    std::cout << 'o' << ' ';
                } else {
                    std::cout << ' ' << ' ';
                }
            }
            std::cout << std::endl;
        }
    }

    std::cout << std::endl << tester.graph.size() << " points" << std::endl;
    std::cout << k << " steps" << std::endl;

    return 0;
}