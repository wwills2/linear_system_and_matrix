//
// Created by zan on 6/15/22.
//

#include "LinearSystem.h"
#include "Matrix.h"

namespace wwills2 {
    LinearSystem::LinearSystem() {

        numMatrices = 1;
        matrices["A"];   //new templated elements called A
    }

    LinearSystem::~LinearSystem() = default;

    void LinearSystem::addMatrix(const std::string &name) {

        numMatrices++;
        matrices[name];   //new templated elements called A
    }

    void LinearSystem::addMatrix(const std::string &name, const int &rows, const int &cols) {

        numMatrices++;
        Matrix matrix(rows, cols);

        //perform a memory move into the map to reduce copy operation overhead
        matrices.insert(std::pair<std::string, Matrix>(name, std::move(matrix)));
    }

    Matrix &LinearSystem::operator[](const std::string &name) {
        return matrices[name];
    }
}