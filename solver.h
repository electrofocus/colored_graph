//
// Created by Amir Mullagaliev on 14-Oct-2019
//

#pragma once

#include <vector>
#include <set>
#include <fstream>

using namespace std;

class Solver {
private:
    struct Node {
        int number;
        int color;
        std::vector<Node *> neighs;
    };

    vector<Node> nodes;
    set<int> colors;

    int cur_node;
    int cur_neigh;

    bool solved;

public:
    Solver(int nodes_num, vector<pair<int, int>> input) {
        cur_node = 0;
        cur_neigh = 0;

        solved = false;

        nodes = vector<Node>(nodes_num);

        for (int i = 0; i < nodes_num; i++) {
            int a, b;
            a = input[i].first;
            b = input[i].second;

            nodes[a].number = a;
            nodes[a].color = 0;
            nodes[a].neighs.push_back(&nodes[b]);

            nodes[b].number = b;
            nodes[b].color = 0;
            nodes[b].neighs.push_back(&nodes[a]);
        }

        colors = {1, 2, 3, 4, 5};
    }

    Solver() {
        cur_node = 0;
        cur_neigh = 0;

        solved = false;
    }

    void step() {
        colors.erase(nodes[cur_node].neighs[cur_neigh]->color);
        cur_neigh++;

        if (cur_neigh == nodes[cur_node].neighs.size()) {
            nodes[cur_node].color = *colors.begin();
            colors = {1, 2, 3, 4, 5};
            cur_neigh = 0;
            cur_node++;
        }

        if (cur_node == nodes.size()) {
            solved = true;
            cur_node = 0;
            cur_neigh = 0;
            return;
        }
    }

    void completely_solve() {
        for (auto &node : nodes) {
            colors = {1, 2, 3, 4, 5};
            for (auto neigh : node.neighs) {
                colors.erase(neigh->color);
            }
            node.color = *colors.begin();
        }
        solved = true;
    }

    vector<pair<int, int>> get_result() {
        vector<pair<int, int>> result;
        result.reserve(nodes.size());
        for (int i = 0; i < nodes.size(); i++) {
            result.emplace_back(i, nodes[i].color);
        }
        return result;
    }

    bool is_solved() {
        return solved;
    }

    int current_node() {
        if (cur_node < nodes.size()) {
            return cur_node;
        }
        return -1;
    }

    int current_neighbour() {
        if (cur_node < nodes.size() && cur_neigh < nodes[cur_node].neighs.size()) {
            return nodes[cur_node].neighs[cur_neigh]->number;
        }
        return -1;
    }

    int current_node_color() {
        if (cur_node < nodes.size()) {
            return nodes[cur_node].color;
        }
        return -1;
    }

    int current_neighbour_color() {
        if (cur_node < nodes.size() && cur_neigh < nodes[cur_node].neighs.size()) {
            return nodes[cur_node].neighs[cur_neigh]->color;
        }
        return -1;
    }

    set<int> available_colors() {
        return colors;
    }

    void reset_solution() {
        for (auto & node : nodes) {
            node.color = 0;
        }
        cur_node = 0;
        cur_neigh = 0;
        solved = false;
        colors = {1, 2, 3, 4, 5};
    }
};
