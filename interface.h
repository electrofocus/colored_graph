//
// Created by Amir Mullagaliev on 19-Nov-19.
//

#pragma once

#include <iostream>
#include "solver.h"

using namespace std;

class Interface {
    Solver problem;
    string output_path;
    int steps_counter;
public:
    Interface(const string &input_path, const string &output_path) {
        int nodes_num;
        steps_counter = 0;
        this->output_path = output_path;
        ifstream input(input_path);
        input >> nodes_num;
        vector<pair<int, int>> edges;

        for (int i = 0; !input.eof(); i++) {
            int a, b;
            input >> a >> b;
            edges.emplace_back(a, b);
        }
        input.close();
        problem = Solver(nodes_num, edges);
    }

    void start() {
        cout << "The problem solver interface has been launched. The problem is as follows:\n"
                "Implement an algorithm that colors the nodes of any planar graph in 5 colors so that any edge\n"
                "connects nodes of different colors.\n"
                "Input data - the number of nodes of a planar graph and a list of edges.\n"
                "The output is the colors of the nodes." << endl << endl;
        int command = 5;
        while (true) {
            if (command == 0) {
                return;
            } else if (command == 1) {
                this->step_by_step_solve();
                if (this->is_solved()) {
                    this->write_result();
                }
            } else if (command == 2) {
                completely_solve();
                if (this->is_solved()) {
                    this->write_result();
                }
            } else if (command == 3) {
                this->reset_solution();
                cout << "Solution cleared." << endl;
            } else if (command == 4) {
                print_result();
            } else if (command == 5) {
                cout << "Select an option:\n"
                        "0 - stop solving\n"
                        "1 - solve step by step\n"
                        "2 - completely solve\n"
                        "3 - reset solution\n"
                        "4 - print result\n"
                        "5 - call help" << endl;
            } else {
                cout << endl << "Unknown command. Type 5 to call help" << endl;
            }
            cout << endl;
            cin >> command;
        }
    }

    void step_by_step_solve() {
        int command = 2;
        cout << "Current node: " << problem.current_node() << endl;
        cout << "Current node color: " << problem.current_node_color() << endl << endl;

        while (true) {
            if (command == 0) {
                cout << "Solving is stopped." << endl;
                if (!problem.is_solved()) {
                    cout << "Problem is NOT solved. Solution cleared" << endl;
                    problem.reset_solution();
                }
                return;
            } else if (command == 1) {
                problem.step();
                if (problem.is_solved()) {
                    cout << "Problem is solved." << endl;
                    break;
                } else {
                    cout << "Step " << ++steps_counter << endl;
                    cout << "Current node: " << problem.current_node() << endl;
                }
            } else if (command == 2) {
                cout << "Select an option:\n"
                        "0 - stop solving\n"
                        "1 - make a step\n"
                        "2 - call help" << endl;
            } else {
                cout << endl << "Unknown command. Type 2 to call help" << endl;
            }
            cout << endl;
            cin >> command;
        }
    }

    void completely_solve() {
        problem.completely_solve();
        if (problem.is_solved()) {
            cout << "Completely solved." << endl;
        }
    }

    bool is_solved() {
        return problem.is_solved();
    }

    void write_result() {
        ofstream output(output_path);
        cout << "Result is in file output.txt" << endl;
        for (auto item : problem.get_result()) {
            output << item.first << ' ' << item.second << endl;
        }
        output.close();
    }

    void print_result() {
        cout << "Result: " << endl;
        for (auto item : problem.get_result()) {
            cout << item.first << ' ' << item.second << endl;
        }
    }

    void reset_solution() {
        steps_counter = 0;
        problem.reset_solution();
    }
};
