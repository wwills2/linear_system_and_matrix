//
// Created by zan on 6/15/22.
//

#include "LinearSystem.h"
#include "Matrix.h"

namespace wwills {
    LinearSystem::LinearSystem() {

        numMatrices = 1;
        matrices["A"] = Matrix();   //new templated elements called A
    }

    LinearSystem::~LinearSystem() = default;

    void LinearSystem::addMatrix(const std::string &name) {

        numMatrices++;
        matrices[name] = Matrix();   //new templated elements called A
    }

    void LinearSystem::addMatrix(const std::string &name, const int &rows, const int &cols) {

        numMatrices++;
        matrices[name] = Matrix(rows, cols);
    }

    Matrix &LinearSystem::operator[](const std::string &name) {
        return matrices[name];
    }
}