//
// Created by zan on 6/23/22.
//

#include "Matrix.h"

namespace wwills{
    Matrix::Matrix() {

        numRows = 2;
        numCols = 3;
        numElements = numRows * numCols;

        //allocate array of float array pointers
        elements = new float *[numRows];

        //initialize array and allocate individual elements
        float num = 1;

        for (int row = 0; row < numRows; row++){
            elements[row] = new float[numCols];
            for (int col = 0; col < numCols; col++){
                elements[row][col] = num;
                num++;
            }
        }
    }

    Matrix::~Matrix() {

        //zero and deallocate data
        for (int row = 0; row < numRows; row++){
            for (int col = 0; col < numCols; col++){
                elements[row][col] = 0;
            }
        }

        for (int row = 0; row < numRows; row++){

            delete[] elements[row];
            elements[row] = nullptr;
        }

        delete[] elements;
        elements = nullptr;
    }

    Matrix::Matrix(int rows, int cols) {

        numRows = rows;
        numCols = cols;
        numElements = numRows * numCols;

        //allocate array of float array pointers
        elements = new float *[numRows];

        //initialize array and allocate individual elements
        for (int row = 0; row < numRows; row++){
            elements[row] = new float[numCols];
            for (int col = 0; col < numCols; col++){
                elements[row][col] = 0;
            }
        }
    }

    Matrix::Matrix(const Matrix &rhs) {

        //self assignment guard
        if (this != &rhs) {

            //copy static members
            numRows = rhs.numRows;
            numCols = rhs.numCols;
            numElements = rhs.numElements;

            //dynamically initialize elements
            elements = new float *[numRows];

            for (int row = 0; row < numRows; row++) {
                elements[row] = new float[numCols];
                for (int col = 0; col < numCols; col++) {
                    elements[row][col] = rhs.elements[row][col];
                }
            }
        }
    }

    void Matrix::print() {

        for (int row = 0; row < numRows; row++){

            std::cout << "row " << row << ": [ ";

            for (int col = 0; col < numCols; col++){
                std::cout << elements[row][col] << " ";
            }

            std::cout << "]\n";
        }
    }

    const Matrix &Matrix::operator=(const Matrix &rhs) {

        //self assignment guard
        if (this == &rhs){
            return *this;
        }else{

            //reallocate array if dimensions are different
            if (numCols != rhs.numCols || numRows != rhs.numRows){

                for (int row = 0; row < numRows; row++){

                    delete[] elements[row];
                    elements[row] = nullptr;
                }

                delete[] elements;
                elements = new float*[rhs.numRows];
            }

            //copy static members
            numRows = rhs.numRows;
            numCols = rhs.numCols;
            numElements = rhs.numElements;

            //copy elements
            for (int row = 0; row < numRows; row++){

                elements[row] = new float[rhs.numCols];

                for (int col = 0; col < numCols; col++){
                    elements[row][col] = rhs.elements[row][col];
                }
            }

            return *this;
        }
    }

    //private + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +

    Matrix Matrix::buildIdentityMxM() {

        //build m x m matrix
        Matrix identity(numRows, numRows);


        for (int row = 0; row < numRows; row++){
            for (int col = 0; col < numRows; col++){

                // place 1 down the diagonal
                if (row == col){
                    identity.elements[row][col] = 1;
                }else{
                    identity.elements[row][col] = 0;
                }
            }
        }

        return identity;
    }

    Matrix Matrix::buildIdentityNxN() {

        //build n x n matrix
        Matrix identity(numCols, numCols);


        for (int row = 0; row < numCols; row++){
            for (int col = 0; col < numCols; col++){

                // place 1 down the diagonal
                if (row == col){
                    identity.elements[row][col] = 1;
                }else{
                    identity.elements[row][col] = 0;
                }
            }
        }

        return identity;
    }

    inline float *Matrix::operator[](const int row) {
        return elements[row];
    }

    void Matrix::addRows(const float *source, float *destination) {

        for (int col = 0; col < numCols; col++){

            //add the source row index to the destination row index
            destination[col] += source[col];
        }
    }

    void Matrix::replaceRows(const float *source, float *destination, const float sourceMultiple) {

        //multiply entries in the source row and add them to the destination row
        for (int col = 0; col < numCols; col++){
            destination[col] += (source[col] * sourceMultiple);
        }
    }

    void Matrix::interchangeRows(float *swap1, float *swap2) {

        //copy swap row 1 to temp location
        float *tempArray = new float[numCols];
        memcpy(tempArray, swap1, sizeof (float) * numCols);

        //copy swap row 2 to swap row 1
        memcpy(swap1, swap2, sizeof (float) * numCols);

        //copy temp to swap row 2
        memcpy(swap2, tempArray, sizeof (float) * numCols);

        delete[] tempArray;
    }

    void Matrix::scaleRow(float *row, float factor) {

        for (int col = 0; col < numCols; col++){
            row[col] *= factor;
        }
    }

} // wwills2

