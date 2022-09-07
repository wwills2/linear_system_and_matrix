//
// Created by zan on 6/23/22.
//

#include "Matrix.h"

namespace wwills2{
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

        //build this matrix's identity matrices
        buildIdentityMxM();
        buildIdentityNxN();

    }

    Matrix::~Matrix() {

        //zero and deallocate matrix data
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

        //deallocate MxM identity matrix
        for (int row = 0; row < numRows; row++){

            delete[] mxmIdentity[row];
            mxmIdentity[row] = nullptr;
        }

        delete[] mxmIdentity;
        mxmIdentity = nullptr;

        //deallocate NxN identity matrix
        for (int row = 0; row < numCols; row++){

            delete[] nxnIdentity[row];
            nxnIdentity[row] = nullptr;
        }

        delete[] nxnIdentity;
        nxnIdentity = nullptr;

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

        buildIdentityMxM();
        buildIdentityNxN();
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

            //allocate and copy MxM identity matrix
            mxmIdentity = new float *[numRows];

            for (int row = 0; row < numRows; row++){
                mxmIdentity[row] = new float[numRows];
                memcpy(mxmIdentity[row], rhs.mxmIdentity[row], sizeof (float) * numRows);
            }

            //allocate and copy NxN identity matrix
            nxnIdentity = new float *[numCols];

            for (int row = 0; row < numCols; row++){
                nxnIdentity[row] = new float[numCols];
                memcpy(nxnIdentity[row], rhs.nxnIdentity[row], sizeof (float) * numCols);
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
        int tryRow = numRows - 1;

        //get non-zero into pivot position
        while ((pivot.second != numCols) && (elements[pivot.first][pivot.second] == 0)){

            //swap current row with first row if non-zero found
            if (elements[tryRow][pivot.second] != 0) {

                interchangeRows(tryRow, pivot.first);

            }else if (tryRow == numRows - 1) {

                //move the pivot column over 1 and try to find a non-zero entry
                pivot.second++;
                tryRow = numRows - 1;

            }else if ((tryRow + 1) < numRows){

                tryRow--;
            }
        }

        if (elements[pivot.first][pivot.second] != 0){

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
                        if ((elements[row][pivot.second] < 0 && rowScalar < 0) ||
                            (elements[row][pivot.second] > 0 && rowScalar > 0)) {
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
                    while ((searchRow < numRows) && (elements[searchRow][searchCol] == 0)){

                        //move back to current pivot column if at the end of the row and there is another row
                        if ((searchCol == numCols - 1) && (searchRow + 1 < numRows)){

                            searchCol = pivot.second;
                            rowSwapNeeded = true;
                            searchRow++;
                        }else if (searchCol + 1 < numCols){

                            searchCol++;
                        }else{

                            //at the end of a column and there are no more rows to search, end
                            searchRow = numRows;
                        }
                    }

                    //swap rows to move non-zero into pivot
                    if (rowSwapNeeded){

                        //move the new pivot row up via swap
                        interchangeRows(pivot.first, searchRow);
                    }

                    pivot.second = searchCol;
                }
            }
        }
    }


    const Matrix &Matrix::operator=(const Matrix &rhs) {

        bool rebuildIdentity = false;

        //self assignment guard
        if (this == &rhs){
            return *this;
        }else{

            //reallocate array if dimensions are different
            if (numCols != rhs.numCols || numRows != rhs.numRows){

                rebuildIdentity = true;

                //delete current array
                for (int row = 0; row < numRows; row++){

                    delete[] elements[row];
                    elements[row] = nullptr;
                }
                delete[] elements;

                //realloc matrix to match rhs dimensions
                elements = new float*[rhs.numRows];
                for (int row = 0; row < rhs.numRows; row++){

                    elements[row] = new float[rhs.numCols];
                }

                //delete MxM identity matrix
                for (int row = 0; row < numRows; row++){

                    delete[] mxmIdentity[row];
                    mxmIdentity[row] = nullptr;
                }

                delete[] mxmIdentity;

                //delete NxN identity matrix
                for (int row = 0; row < numCols; row++){

                    delete[] nxnIdentity[row];
                    nxnIdentity[row] = nullptr;
                }
                delete[] nxnIdentity;
            }

            //copy static members
            numRows = rhs.numRows;
            numCols = rhs.numCols;
            numElements = rhs.numElements;

            //copy elements
            for (int row = 0; row < numRows; row++){
                memcpy(elements[row], rhs.elements[row], sizeof (float) * numCols);
            }

            if (rebuildIdentity){

                //reallocate and copy MxM identity matrix
                mxmIdentity = new float *[numRows];

                for (int row = 0; row < numRows; row++){
                    mxmIdentity[row] = new float[numRows];
                    memcpy(mxmIdentity[row], rhs.mxmIdentity[row], sizeof (float) * numRows);
                }

                //reallocate and copy NxN identity matrix
                nxnIdentity = new float *[numCols];

                for (int row = 0; row < numCols; row++){
                    nxnIdentity[row] = new float[numCols];
                    memcpy(nxnIdentity[row], rhs.nxnIdentity[row], sizeof (float) * numCols);
                }
            }

            return *this;
        }
    }

    //private + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +

    void Matrix::buildIdentityMxM() {

        //allocate array of float array pointers
        mxmIdentity = new float *[numRows];

        //build m x m matrix
        std::vector<std::thread> threads;
        const unsigned int numThreads = std::thread::hardware_concurrency() - 1;

        for (unsigned int i = 0; i < numThreads; i++){
            threads.emplace_back(&Matrix::buildIdentityMxMThread, this, i, numThreads);
        }

        for (unsigned int i = 0; i < numThreads; i++){
            threads[i].join();
        }
    }

    void Matrix::buildIdentityMxMThread(const int &startRow, const int &numThreads) {

        for (int row = startRow; row < numRows; row += numThreads){
            mxmIdentity[row] = new float[numRows]{};
            mxmIdentity[row][row] = 1;
        }
    }

    void Matrix::buildIdentityNxN() {

        //allocate array of float array pointers
        nxnIdentity = new float *[numCols];

        //build n x n matrix
        std::vector<std::thread> threads;
        const unsigned int numThreads = std::thread::hardware_concurrency();

        for (unsigned int i = 0; i < numThreads; i++){
            threads.emplace_back(&Matrix::buildIdentityNxNThread, this, i, numThreads);
        }

        for (unsigned int i = 0; i < numThreads; i++){
            threads[i].join();
        }
    }

    void Matrix::buildIdentityNxNThread(const int &startRow, const int &numThreads) {

        for (int row = startRow; row < numCols; row += numThreads){

            nxnIdentity[row] = new float[numCols]{};
            nxnIdentity[row][row] = 1;
        }
    }

    inline float *Matrix::operator[](const int &row) {
        return elements[row];
    }

    void Matrix::addRows(const int &sourceRow, const int &destinationRow) {

        for (int col = 0; col < numCols; col++){

            //add the source row index to the destination row index
            elements[destinationRow][col] += elements[sourceRow][col];
        }
    }

    void Matrix::replaceRows(const int &sourceRow, const int &destinationRow, const float &sourceMultiple) {

        //multiply entries in the source row and add them to the destination row
        for (int col = 0; col < numCols; col++){
            elements[destinationRow][col] += (elements[sourceRow][col] * sourceMultiple);
        }
    }

    void Matrix::interchangeRows(const int &swapRow1, const int &swapRow2) {

        //copy swap row 1 to temp location
        float *tempArray = new float[numCols];
        memcpy(tempArray, elements[swapRow1], sizeof (float) * numCols);

        //copy swap row 2 to swap row 1
        memcpy(elements[swapRow1], elements[swapRow2], sizeof (float) * numCols);

        //copy temp to swap row 2
        memcpy(elements[swapRow2], tempArray, sizeof (float) * numCols);

        delete[] tempArray;
    }

    void Matrix::scaleRow(float *row, const float &factor) {

        for (int col = 0; col < numCols; col++){
            row[col] *= factor;
        }
    }

} // wwills2

