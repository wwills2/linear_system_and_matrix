//
// Created by zan on 6/15/22.
//

#include "LinearSystem.h"

namespace wwills {
    LinearSystem::LinearSystem() {

        numMatrices = 1;
        Matrix matrix;
        matrices["A"] = matrix;   //new templated elements called A
    }

    LinearSystem::~LinearSystem() {

    }

    void LinearSystem::printAll() {

    }

    void LinearSystem::addMatrix(const std::string &name) {

        numMatrices++;
        Matrix matrix;
        matrices[name] = matrix;   //new templated elements called A
    }

    void LinearSystem::addMatrix(const std::string &name, const int &rows, const int &cols) {

        numMatrices++;
        Matrix matrix(rows, cols);
        matrices[name] = matrix;
    }
}