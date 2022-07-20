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

    void Matrix::echelonForm() {

        float rowScalar = 0;
        std::pair<int, int> pivot = {0, 0};

        tryNextColumn:      //this label is used by the goto statement ~20 lines down

        //get non-zero into pivot position
        int tryRow = pivot.first;

        //get non-zero into pivot position
        while ((elements[tryRow][pivot.second] == 0) && (tryRow < numRows)){
            tryRow++;
        }

        //swap current tryRow if non-zero found
        if (elements[pivot.first][pivot.second] != 0) {

            interchangeRows(elements[tryRow], elements[pivot.first]);
        }else{

            //move the pivot column over 1 and try to find a non-zero entry
            pivot.second += 1;
            goto tryNextColumn;     //resolves the edge case that column 0 has no non-zero entries
        }


        int searchCol = 0;
        int searchRow = 0;      //used when searching for pivot
        bool rowSwapNeeded = false;

        //loop through all pivot positions and perform forward operations
        for (int i = 0; i < numRows; i++){

            //perform row operations to clear the pivot column
            for (int row = pivot.first + 1; row < numRows; row++) {

                if (elements[row][pivot.second] != 0) {

                    rowScalar = elements[row][pivot.second] / elements[pivot.first][pivot.second];

                    //make scalar negative if the sign is the same
                    if ((elements[row][pivot.second] > 0 && elements[pivot.first][pivot.second] > 0) ||
                        (elements[row][pivot.second] < 0 && elements[pivot.first][pivot.second] < 0)) {
                        rowScalar *= -1;
                    }

                    replaceRows(elements[pivot.first], elements[row], rowScalar);
                }
            }

            pivot.first++;
            pivot.second++;

            searchRow = pivot.first;
            searchCol = pivot.second;
            rowSwapNeeded = false;

            //find the next pivot position if adjacent pivot is zero, then swap
            while ((elements[searchRow][searchCol] == 0) && (searchRow < numRows)){

                //move back to current pivot column if at the end of the row and there is another row
                if ((searchCol == numCols - 1) && (searchRow + 1 < numRows)){

                    searchCol = pivot.second;
                    searchRow++;
                    rowSwapNeeded = true;
                }

                searchCol++;
            }

            if (rowSwapNeeded){
                //move the new pivot row up via swap
                interchangeRows(elements[pivot.first], elements[searchRow]);
            }

            pivot.second = searchCol;
        }
    }


    const Matrix &Matrix::operator=(const Matrix &rhs) {

        //self assignment guard
        if (this == &rhs){
            return *this;
        }else{

            //reallocate array if dimensions are different
            if (numCols != rhs.numCols || numRows != rhs.numRows){

                //delete current array
                for (int row = 0; row < numRows; row++){

                    delete[] elements[row];
                    elements[row] = nullptr;
                }
                delete[] elements;

                //realloc to match rhs dimensions
                elements = new float*[rhs.numRows];
                for (int row = 0; row < rhs.numRows; row++){

                    elements[row] = new float[rhs.numCols];
                }
            }

            //copy static members
            numRows = rhs.numRows;
            numCols = rhs.numCols;
            numElements = rhs.numElements;

            //copy elements
            for (int row = 0; row < numRows; row++){
                memcpy(elements[row], rhs.elements[row], sizeof (float) * numCols);
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

