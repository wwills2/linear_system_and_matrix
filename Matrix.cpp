//
// Created by zan on 6/23/22.
//

#include "Matrix.h"

namespace wwills{
    Matrix::Matrix() {

        numRows = 2;
        numCols = 3;
        numElements = numRows * numCols;

        //initialize elements
        float num = 1;

        for (int row = 0; row < numRows; row++){
            for (int col = 0; col < numCols; col++){
                elements[row][col] = num;
                num++;
            }
        }
    }

    Matrix::~Matrix() {

        //zero data
        for (int row = 0; row < numRows; row++){
            for (int col = 0; col < numCols; col++){
                elements[row][col] = 0;
            }
        }
    }

    Matrix::Matrix(int rows, int cols) {

        numRows = rows;
        numCols = cols;
        numElements = numRows * numCols;

        //initialize array and allocate individual elements
        for (int row = 0; row < numRows; row++){
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

            for (int row = 0; row < numRows; row++) {
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

            std::cout << "]" << std::endl;
        }

        std::cout << std::endl;
    }

    void Matrix::echelonForm() {

        float rowScalar = 0;
        std::pair<int, int> pivot = {0, 0};
        int tryRow = pivot.first;

        //get non-zero into pivot position
        while (elements[tryRow][pivot.second] == 0){

            tryRow++;

            //swap current tryRow if non-zero found
            if (elements[tryRow][pivot.second] != 0) {

                interchangeRows(elements[tryRow], elements[pivot.first]);
                tryRow = pivot.first;

            }else if (tryRow == numRows - 1){

                //move the pivot column over 1 and try to find a non-zero entry
                pivot.second += 1;
            }
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
                    if ((elements[row][pivot.second] < 0 && elements[pivot.first][pivot.second] > 0) ||
                        (elements[row][pivot.second] > 0 && elements[pivot.first][pivot.second] < 0)) {
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

            //find the next pivot position, if all entries in row are zero, then swap
            while ((elements[searchRow][searchCol] == 0) && (searchRow < numRows)){

                //move back to current pivot column if at the end of the row and there is another row
                if ((searchCol == numCols - 1) && (searchRow + 1 < numRows)){

                    searchCol = pivot.second;
                    rowSwapNeeded = true;
                    searchRow++;
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

            //copy static members
            numRows = rhs.numRows;
            numCols = rhs.numCols;
            numElements = rhs.numElements;

            elements = rhs.elements;

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

    inline std::vector<float> Matrix::operator[](const int row) {
        return elements[row];
    }

    void Matrix::addRows(const std::vector<float> &source, std::vector<float> &destination) {

        for (int col = 0; col < numCols; col++){

            //add the source row index to the destination row index
            destination[col] += source[col];
        }
    }

    void Matrix::replaceRows(const std::vector<float> &source, std::vector<float> &destination, const float sourceMultiple) {

        //multiply entries in the source row and add them to the destination row
        for (int col = 0; col < numCols; col++){
            destination[col] += (source[col] * sourceMultiple);
        }
    }

    void Matrix::interchangeRows(std::vector<float> &swap1, std::vector<float> &swap2) {

        //copy swap row 1 to temp location
        std::vector<float> tempArray;

        tempArray = swap1;
        swap1 = swap2;
        swap2 = tempArray;
    }

    void Matrix::scaleRow(std::vector<float> &row, float factor) {

        for (int col = 0; col < numCols; col++){
            row[col] *= factor;
        }
    }

} // wwills2

