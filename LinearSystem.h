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
#include <stdexcept>

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

        void addMatrix(const std::string &name, const int &rows, const int &cols);

        void addMatrix(const std::string &name, const Matrix &matrixToAdd);

        void removeMatrix(const std::string &name);

        Matrix &getMatrix(const std::string &name);

        int getNumMatrices();

    private:
        std::map<std::string, Matrix> m_matrices;
    };
}

#endif //MATRIX_OPERATIONS_LINEARSYSTEM_H
