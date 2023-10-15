//
// Created by zan on 6/15/22.
//

#include "LinearSystem.h"
#include "Matrix.h"

namespace wwills2 {

    LinearSystem::LinearSystem() = default;
    LinearSystem::~LinearSystem() = default;

    void LinearSystem::addMatrix(const std::string &name, const int &rows, const int &cols) {
        m_matrices.insert(std::pair<std::string, Matrix>(name, Matrix(rows, cols)));
    }

    void LinearSystem::addMatrix(const std::string &name, const Matrix &matrixToAdd) {
        m_matrices.insert(std::pair<std::string, Matrix>(name, matrixToAdd));
    }

    void LinearSystem::removeMatrix(const std::string &name) {

        auto it = m_matrices.find(name);
        if (it != m_matrices.end()){
            m_matrices.erase(it);
        }
    }

    Matrix &LinearSystem::getMatrix(const std::string &name){

        auto it = m_matrices.find(name);
        if (it == m_matrices.end()){
            throw std::invalid_argument("matrix \"" + name + "\" does not exist");
        }
        return m_matrices[name];
    }

    int LinearSystem::getNumMatrices() {
        return (int) m_matrices.size();
    }
}