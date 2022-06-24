//
// Created by zan on 6/15/22.
//

#ifndef MATRIX_OPERATIONS_LINEARSYSTEM_H
#define MATRIX_OPERATIONS_LINEARSYSTEM_H

#include <vector>
#include <map>
#include <iostream>
#include <string>

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

        void addMatrix(const std::string &name);

        void addMatrix(const std::string &name, const int &rows, const int &cols);

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

        Matrix(int rows, int cols);

        Matrix(const Matrix &rhs);

        void print();

        const Matrix &operator=(const Matrix &rhs);

    private:

        Matrix buildIdentityMxM();

        Matrix buildIdentityNxN();

        int numRows;        //num rows
        int numCols;        //num cols
        int numElements;    //number of elements in the elements
        float **elements;     //2d, dynamically allocated elements

        friend LinearSystem;

        friend TestLinearSystem;
    };

} // wwills2

#endif //MATRIX_OPERATIONS_LINEARSYSTEM_H
