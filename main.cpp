#include "interface.h"
#include <set>
#include <ctime>
#include <cmath>
#include <random>
#include <cstdlib>

using namespace std;

int main() {


    default_random_engine rng(random_device{}());

    int n = 36;

    uniform_int_distribution<int> dist(n / 2, n);

    int m = dist(rng);

    n = sqrt(n);

    uniform_int_distribution<int> pointDist(0, n);

    set<pair<int, int>> points;
    set<pair<pair<int, int>, pair<int, int>>> edges;

    while (points.size() < m) {
        points.insert({pointDist(rng), pointDist(rng)});
    }

    cout << m << endl;
    for (auto point_1 = points.begin(); point_1 != points.end(); point_1++) {
        for (auto point_2 = point_1; point_2 != points.end(); point_2++) {
            if ((abs(point_1->first - point_2->first) == 1 && abs(point_1->second - point_2->second) == 0) ||
                (abs(point_1->first - point_2->first) == 0 && abs(point_1->second - point_2->second) == 1)) {
                edges.insert({*point_1, *point_2});
            }
        }
    }

    cout << edges.size() << endl;
    vector<vector<char> > mas(n + 1, vector<char>(n + 1, ' '));

    cout << endl << endl;

    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            mas[i][j] = ' ';
        }
    }

    for (auto x: edges) {
        mas[x.first.first][x.first.second] = 'o';
        mas[x.second.first][x.second.second] = 'o';
    }

    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << mas[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}