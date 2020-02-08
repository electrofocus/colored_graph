#include "tester.h"


int main() {
    Tester tester;

    Tester::Result result;

    result = tester.time_test(7000, 5000);
    Tester::print_result(result);
    tester.graph.clear();

    result = tester.time_test(8000, 6000);
    Tester::print_result(result);
    tester.graph.clear();

    result = tester.time_test(9000, 7000);
    Tester::print_result(result);
    tester.graph.clear();

    result = tester.time_test(10000, 8000);
    Tester::print_result(result);
    tester.graph.clear();

    result = tester.time_test(11000, 9000);
    Tester::print_result(result);
    tester.graph.clear();

    result = tester.time_test(12000, 10000);
    Tester::print_result(result);
    tester.graph.clear();

    result = tester.time_test(13000, 11000);
    Tester::print_result(result);
    tester.graph.clear();

    result = tester.time_test(14000, 12000);
    Tester::print_result(result);
    tester.graph.clear();


//    Tester::Result result = tester.time_test(18, 10);
//    Tester::print_result(result);
//    tester.print_graph(18);



    return 0;
}