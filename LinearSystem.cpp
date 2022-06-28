//
// Created by zan on 6/15/22.
//

#include "LinearSystem.h"
#include "Matrix.h"

namespace wwills {
    LinearSystem::LinearSystem() {

        numMatrices = 1;
        matrices["A"] = new Matrix;   //new templated elements called A
    }

    LinearSystem::~LinearSystem() {

        for (auto itr = matrices.begin(); itr != matrices.end(); itr++){
            delete itr->second;
        }
    }

    void LinearSystem::addMatrix(const std::string &name) {

        numMatrices++;
        matrices[name] = new Matrix;   //new templated elements called A
    }

    void LinearSystem::addMatrix(const std::string &name, const int &rows, const int &cols) {

        numMatrices++;
        matrices[name] = new Matrix(rows, cols);
    }
}