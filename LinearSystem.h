//
// Created by zan on 6/15/22.
//

#ifndef MATRIX_OPERATIONS_LINEARSYSTEM_H
#define MATRIX_OPERATIONS_LINEARSYSTEM_H

#include <vector>
#include <map>
#include <iostream>

class TestLinearSystem;

namespace wwills {

    class LinearSystem;
    class Matrix;

    //holds the matrices and all other data about the linear system of equations and the problem to be solved
    class LinearSystem {

    public:
        friend TestLinearSystem;

        LinearSystem();
        ~LinearSystem();

        void printAll();

    private:

        //data members
        int numMatrices;
        std::map <std::string, Matrix> matrices;
    };


    class Matrix {
    public:

        Matrix();
        ~Matrix();

        void print();

    private:

        int numRows;        //num rows
        int numCols;        //num cols
        int numElements;    //number of elements in the matrix
        float **matrix;     //2d, dynamically allocated matrix

        friend LinearSystem;

        friend TestLinearSystem;
    };

} // wwills2

#endif //MATRIX_OPERATIONS_LINEARSYSTEM_H
