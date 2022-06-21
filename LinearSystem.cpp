//
// Created by zan on 6/15/22.
//

#include "LinearSystem.h"

namespace wwills {
    LinearSystem::LinearSystem() {

        numMatrices = 1;
        matrices["A"] = Matrix();   //new templated matrix called A
    }

    LinearSystem::~LinearSystem() {

    }

    void LinearSystem::printAll() {

    }

    Matrix::Matrix() {

        numRows = 2;
        numCols = 3;
        numElements = numRows * numCols;

        //allocate array of float array pointers
        matrix = new float *[numRows];

        //initialize array and allocate individual elements
        for (int row = 0; row < numRows; row++){
            for (int col = 0; col < numCols; col++){
                matrix[col] = new float;
                matrix[row][col] = (float) row + (float) col;
            }
        }
    }

    Matrix::~Matrix() {

        //zero and deallocate data
        for (int row = 0; row < numRows; row++){
            for (int col = 0; col < numCols; col++){
                matrix[row][col] = 0;
            }
        }

        for (int row = 0; row < numRows; row++){
            delete[] matrix[row];
            matrix[row] = nullptr;
        }

        delete[] matrix;
        matrix = nullptr;
    }

    void Matrix::print() {

        for (int row = 0; row < numRows; row++){

            std::cout << "row " << row << ": [";

            for (int col = 0; col < 0; col++){
                std::cout << matrix[row][col];
            }

            std::cout << "]\n";
        }
    }

} // wwills2