//
// Created by zan on 6/15/22.
//

#include "MatrixManager.h"
#include "Matrix.h"

namespace wwills2 {

    void MatrixManager::createMatrix(const std::string &name, const int &rows, const int &cols) {

        auto it = m_matrices.find(name);
        if (it != m_matrices.end()){
            throw std::invalid_argument("matrix \"" + name + "\" already exists");
        }

        Matrix matrix(rows, cols);
        m_matrices.emplace(name, matrix);
    }

    void MatrixManager::insertMatrix(const std::string &name, const Matrix &matrixToAdd) {

        auto it = m_matrices.find(name);
        if (it != m_matrices.end()){
            throw std::invalid_argument("matrix \"" + name + "\" already exists");
        }

        m_matrices.emplace(name, matrixToAdd);
    }

    void MatrixManager::removeMatrix(const std::string &name) {

        auto it = m_matrices.find(name);
        if (it != m_matrices.end()){
            m_matrices.erase(it);
        }
    }

    Matrix &MatrixManager::getMatrix(const std::string &name){

        auto it = m_matrices.find(name);
        if (it == m_matrices.end()){
            throw std::invalid_argument("matrix \"" + name + "\" does not exist");
        }
        return m_matrices[name];
    }

    int MatrixManager::getNumMatrices() {
        return (int) m_matrices.size();
    }
}