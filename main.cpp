#include "tester.h"


int main() {
    int square = 81;
    Tester tester;
//    Tester::Result result = tester.time_test(5200, 5000, false);
    Tester::Result result = tester.time_test(square, 40, false);

//    tester.graph.clear();
//    result = tester.time_test(5200, 4000);
//    tester.graph.clear();
//    result = tester.time_test(5200, 3006);
//    tester.graph.clear();
//    result = tester.time_test(5200, 2049);
//    tester.graph.clear();
//    result = tester.time_test(5200, 1150);
//    tester.graph.clear();

    std::cout.precision(5);
    Tester::print_result(result);

    tester.print_graph(square);

    return 0;
}