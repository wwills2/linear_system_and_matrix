//
// Created by zan on 6/15/22.
//

#include "LinearSystem.h"
#include "Matrix.h"

namespace wwills2 {
    LinearSystem::LinearSystem() {

        m_numMatrices = 1;
        m_matrices["A"];   //new templated m_elements called A
    }

    LinearSystem::~LinearSystem() = default;

    void LinearSystem::addMatrix(const std::string &name) {

        m_numMatrices++;
        m_matrices[name];   //new templated m_elements called A
    }

    void LinearSystem::addMatrix(const std::string &name, const int &rows, const int &cols) {

        m_numMatrices++;
        Matrix matrix(rows, cols);

        //perform a memory move into the map to reduce copy operation overhead
        m_matrices.insert(std::pair<std::string, Matrix>(name, std::move(matrix)));
    }

    Matrix &LinearSystem::operator[](const std::string &name) {
        return m_matrices[name];
    }
}