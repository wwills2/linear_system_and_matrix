cmake_minimum_required(VERSION 3.22)
project(matrix_operations)

set(CMAKE_CXX_STANDARD 14)

add_executable(matrix_operations main.cpp LinearSystem.h LinearSystem.cpp)

add_executable(testLinearSystem LinearSystem.cpp LinearSystem.h test/TestLinearSystem.cpp test/TestLinearSystem.h)
