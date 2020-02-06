//
// Created by Amir Mullagaliev on 19-Nov-19.
//

#include <iostream>
#include <fstream>
#include <windows.h>
#include "tester.h"


class Interface {
private:
    Solver solver;
    Graph graph;
    Tester tester;
    int square;
    int points_number;

public:
    Interface() : solver(graph), square(0), points_number(0) {}

    void print_graph() {
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

    void start() {
        std::string command;
        while (true) {
            std::cout << "select mode:\n"
                         "  exit\n"
                         "  file\n"
                         "  tester\n" << std::endl;
            std::cin >> command;

            if (command == "file") {
                file();
            } else if (command == "tester") {
                test();
            } else if (command == "exit") {
                return;
            }
        }
    }

    void file() {
        std::string filename;
        std::cout << "reading graph from file.\nenter filename:\n ";
        std::cin >> filename;
        std::ifstream input(filename);
        if (!input.is_open()) {
            std::cout << "can't open file " << filename << std::endl;
            return;
        }
        int str[4];
        int nodes_number;
        input >> nodes_number;
        while (!input.eof()) {
            input >> str[0] >> str[1] >> str[2] >> str[3];
            Graph::Point a(str[0], str[1]);
            Graph::Point b(str[2], str[3]);
            graph.add_point(a);
            graph.add_point(b);
            graph.add_edge(a, b);
        }
        std::cout << "graph built from file" << std::endl;
        input.close();
    }

    void test() {
        std::cout << ">>> tester mode" << std::endl;
        std::string command;
        while (true) {
            std::cout << "options:\n"
                         "  skip\n"
                         "  run default test\n"
                         "  custom test" << std::endl;
            std::cin >> command;

            if (command == "run default test") {
                Tester::Result result = tester.time_test(5200, 5000);
                print_result(result);
                result = tester.time_test(5200, 4000);
                print_result(result);
                result = tester.time_test(5200, 3006);
                print_result(result);
                result = tester.time_test(5200, 2049);
                print_result(result);
                result = tester.time_test(5200, 1150);
                print_result(result);
            } else if (command == "custom test") {
                std::cout << "enter square: " << std::endl;
                std::cin >> square;
                std::cout << "enter points number: " << std::endl;
                std::cin >> points_number;
                Tester::Result result = tester.time_test(square, points_number);
                print_result(result);
                graph = tester.graph;
                print_graph();
            } else if (command == "skip") {
                return;
            }
        }
    }

    static void print_result(Tester::Result result) {
        std::cout << result.points << " points, " << result.steps << " steps, " << result.time
                  << " secs, (time/steps): " << (double) result.time / result.steps << std::endl;
    }

};
