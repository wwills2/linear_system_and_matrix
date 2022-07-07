cmake_minimum_required(VERSION 3.20)
project(matrix_operations)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -pedantic -g3)

add_executable(matrix_operations main.cpp LinearSystem.h LinearSystem.cpp Matrix.cpp Matrix.h)

add_executable(testLinearSystem LinearSystem.cpp LinearSystem.h test/TestLinearSystem.cpp test/TestLinearSystem.h
        Matrix.cpp Matrix.h)

