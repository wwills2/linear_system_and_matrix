//
// Created by zan on 6/15/22.
//

#ifndef MATRIX_OPERATIONS_LINEARSYSTEM_H
#define MATRIX_OPERATIONS_LINEARSYSTEM_H

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <thread>

class TestLinearSystem;

namespace wwills2 {

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

        Matrix &operator[](const std::string &name);

    private:

        //data members
        int m_numMatrices;
        std::map<std::string, Matrix> m_matrices;
    };
}

#endif //MATRIX_OPERATIONS_LINEARSYSTEM_H
