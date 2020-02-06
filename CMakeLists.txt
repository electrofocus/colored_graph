cmake_minimum_required(VERSION 3.15)
project(colored_graph)

set(CMAKE_CXX_STANDARD 11)

add_executable(colored_graph main.cpp solver.h graph.h tester.h solver.cpp tester.cpp graph.cpp)