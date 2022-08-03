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

            elements.emplace_back(std::vector<float>(numCols));

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

            elements.emplace_back(std::vector<float>(numCols));

            for (int col = 0; col < numCols; col++){
                elements[row][col] = 0;
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
        bool matrixIsNonZero = false;
        int tryRow = numRows - 1;

        //get non-zero into pivot position
        while (pivot.second != numCols && elements[pivot.first][pivot.second] == 0){

            //swap current row with first row if non-zero found
            if (elements[tryRow][pivot.second] != 0) {

                elements[tryRow].swap(elements[pivot.first]);
                matrixIsNonZero = true;

            }else if (tryRow == numRows - 1) {

                //move the pivot column over 1 and try to find a non-zero entry
                pivot.second++;
                tryRow = numRows - 1;

            }else if ((tryRow + 1) < numRows){

                tryRow--;
            }
        }

        if (matrixIsNonZero){

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
                        if ((elements[row][pivot.second] < 0 && elements[pivot.first][pivot.second] < 0) ||
                            (elements[row][pivot.second] > 0 && elements[pivot.first][pivot.second] > 0)) {
                            rowScalar *= -1;
                        }

                        replaceRows(pivot.first, row, rowScalar);
                    }
                }

                pivot.first++;
                pivot.second++;

                //find next pivot if not in the last column
                if (pivot.second < numCols - 1){

                    searchRow = pivot.first;
                    searchCol = pivot.second;
                    rowSwapNeeded = false;

                    //find the next pivot position, if all entries in row are zero, then swap
                    while (searchRow < numRows && elements[searchRow][searchCol] == 0){

                        //move back to current pivot column if at the end of the row and there is another row
                        if ((searchCol == numCols - 1) && (searchRow + 1 < numRows)){

                            searchCol = pivot.second;
                            rowSwapNeeded = true;
                            searchRow++;
                        }else if (searchCol + 1 < numCols){

                            searchCol++;
                        }
                    }

                    //swap rows to move non-zero into pivot
                    if (rowSwapNeeded){

                        //move the new pivot row up via swap
                        elements[pivot.first].swap(elements[searchRow]);
                    }

                    pivot.second = searchCol;
                }
            }
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

    inline std::vector<float> &Matrix::operator[](const int &row) {
        return elements[row];
    }

    void Matrix::addRows(const int &source, const int &destination) {

        for (int col = 0; col < numCols; col++){

            //add the source row index to the destination row index
            elements[destination][col] += elements[source][col];
        }
    }

    void Matrix::replaceRows(const int &source, const int &destination, const float &sourceMultiple) {

        //multiply entries in the source row and add them to the destination row
        for (int col = 0; col < numCols; col++){
            elements[destination][col] += (elements[source][col] * sourceMultiple);
        }
    }

    void Matrix::scaleRow(const int &row, float &factor) {

        for (int col = 0; col < numCols; col++){
            elements[row][col] *= factor;
        }
    }

} // wwills2

