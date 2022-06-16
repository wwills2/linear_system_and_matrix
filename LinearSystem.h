//
// Created by zan on 6/15/22.
//

#ifndef MATRIX_OPERATIONS_LINEARSYSTEM_H
#define MATRIX_OPERATIONS_LINEARSYSTEM_H

#include <vector>
#include <map>

namespace wwills {

    class LinearSystem;
    class Matrix;

    //holds the matrices and all other data about the linear system of equations and the problem to be solved
    class LinearSystem {
    public:
        LinearSystem();
        ~LinearSystem();

    private:

        //data members
        std::map <std::string, Matrix> matrices;

    };

    class Matrix {
    public:
        Matrix();
        ~Matrix();
    };

} // wwills2

#endif //MATRIX_OPERATIONS_LINEARSYSTEM_H
