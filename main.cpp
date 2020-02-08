#include "tester.h"


int main() {
    Tester tester;
    Tester::Result result = tester.time_test(5200, 5000, false);
    Tester::print_result(result);
    tester.graph.clear();
    result = tester.time_test(5200, 4000, false);
    Tester::print_result(result);
    tester.graph.clear();
    result = tester.time_test(5200, 3006, false);
    Tester::print_result(result);
    tester.graph.clear();
    result = tester.time_test(5200, 2049, false);
    Tester::print_result(result);
    tester.graph.clear();
    result = tester.time_test(5200, 1150, false);
    Tester::print_result(result);
    tester.graph.clear();

//    Tester::Result result = tester.time_test(3249, 2000, false);
//    Tester::print_result(result);
//    tester.print_graph(3249);


    return 0;
}