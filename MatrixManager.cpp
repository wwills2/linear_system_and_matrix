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

        m_matrices.emplace(name, std::make_unique<Matrix>(Matrix(rows, cols)));
    }

    void MatrixManager::insertMatrix(const std::string &name, const Matrix &matrixToAdd) {

        auto it = m_matrices.find(name);
        if (it != m_matrices.end()){
            throw std::invalid_argument("matrix \"" + name + "\" already exists");
        }

        m_matrices.emplace(name, std::make_unique<Matrix>(matrixToAdd));
    }

    void MatrixManager::removeMatrix(const std::string &name) {

        auto it = m_matrices.find(name);
        if (it != m_matrices.end()){
            m_matrices.erase(it);
        }
    }

    bool MatrixManager::hasMatrix(const std::string &name) {

        auto it = m_matrices.find(name);
        if (it == m_matrices.end()){
            return false;
        }else{
            return true;
        }
    }

    std::shared_ptr<Matrix> & MatrixManager::getMatrix(const std::string &name){

        auto it = m_matrices.find(name);
        if (it == m_matrices.end()){
            throw std::invalid_argument("matrix \"" + name + "\" does not exist");
        }
        return it->second;
    }

    int MatrixManager::getNumMatrices() {
        return (int) m_matrices.size();
    }
}