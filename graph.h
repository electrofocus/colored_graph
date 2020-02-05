//
// Created by Amir on 2/4/2020.
//

#pragma once

#include <map>
#include <set>


class Graph {
public:
    struct Point {
        int x;
        int y;
        int color;
        std::set<std::pair<int, int>> neighbours;

        Point(int _x, int _y) : x(_x), y(_y), color(0) {}
    };

private:
    std::map<std::pair<int, int>, Point> points;

public:
    Graph() = default;

    void add_point(int x, int y) {
        if (points.find({x, y}) == points.end()) {
            points.insert({{x, y}, Point(x, y)});
        }
    }

    void add_point(const Point &point) {
        if (points.find({point.x, point.y}) == points.end()) {
            points.insert({{point.x, point.y}, point});
        }
    }

    void add_edge(const Point &a, const Point &b) {
        if (points.find({a.x, a.y}) != points.end() && points.find({b.x, b.y}) != points.end()) {
            points.at({a.x, a.y}).neighbours.insert({b.x, b.y});
            points.at({b.x, b.y}).neighbours.insert({a.x, a.y});
        }
    }

    bool is_edge(const Point &a, const Point &b) {
        if (points.find({a.x, a.y}) != points.end() && points.find({b.x, b.y}) != points.end()) {
            return !(points.at({a.x, a.y}).neighbours.find({b.x, b.y}) == points.at({a.x, a.y}).neighbours.end() ||
                     points.at({b.x, b.y}).neighbours.find({a.x, a.y}) == points.at({b.x, b.y}).neighbours.end());
        }
        return false;
    }

    std::set<Point> get_points() {
        std::set<Point> points_set;
        for (auto &point: points) {
            points_set.insert(point.second);
        }
        return points_set;
    }

    int size() {
        return points.size();
    }

    friend class Solver;

    friend class Tester;
};


bool operator<(const Graph::Point &a, const Graph::Point &b) {
    return a.x < b.x || a.y < b.y;
}
