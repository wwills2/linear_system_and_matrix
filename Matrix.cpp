//
// Created by zan on 6/23/22.
//

#include "Matrix.h"

namespace wwills2{
    Matrix::Matrix() {

        m_numRows = 2;
        m_numCols = 3;
        m_numElements = m_numRows * m_numCols;
        m_isEchelon = false;
        m_isReducedEchelon = false;
        m_mxmIdentity = nullptr;
        m_nxnIdentity = nullptr;

        //allocate array of double array pointers
        m_elements = new double *[m_numRows];

        //initialize array and allocate individual m_elements
        double num = 1;

        for (int row = 0; row < m_numRows; row++){
            m_elements[row] = new double[m_numCols];
            for (int col = 0; col < m_numCols; col++){
                m_elements[row][col] = num;
                num++;
            }
        }

        //build this matrix's identity matrices
        buildIdentityMxM();
        buildIdentityNxN();

    }

    Matrix::~Matrix() {

        //zero and deallocate matrix data
        for (int row = 0; row < m_numRows; row++){
            for (int col = 0; col < m_numCols; col++){
                m_elements[row][col] = 0;
            }
        }

        for (int row = 0; row < m_numRows; row++){

            delete[] m_elements[row];
            m_elements[row] = nullptr;
        }

        delete[] m_elements;
        m_elements = nullptr;

        //deallocate MxM identity matrix
        for (int row = 0; row < m_numRows; row++){

            delete[] m_mxmIdentity[row];
            m_mxmIdentity[row] = nullptr;
        }

        delete[] m_mxmIdentity;
        m_mxmIdentity = nullptr;

        //deallocate NxN identity matrix
        for (int row = 0; row < m_numCols; row++){

            delete[] m_nxnIdentity[row];
            m_nxnIdentity[row] = nullptr;
        }

        delete[] m_nxnIdentity;
        m_nxnIdentity = nullptr;

    }

    Matrix::Matrix(int rows, int cols, bool isEchelon, bool isReducedEchelon) {

        m_numRows = rows;
        m_numCols = cols;
        m_numElements = m_numRows * m_numCols;
        m_isEchelon = isEchelon;
        m_isReducedEchelon = isReducedEchelon;
        m_mxmIdentity = nullptr;
        m_nxnIdentity = nullptr;

        //allocate array of double array pointers
        m_elements = new double *[m_numRows];

        //initialize array and allocate individual m_elements
        for (int row = 0; row < m_numRows; row++){
            m_elements[row] = new double[m_numCols];
            for (int col = 0; col < m_numCols; col++){
                m_elements[row][col] = 0;
            }
        }

        buildIdentityMxM();
        buildIdentityNxN();
    }

    Matrix::Matrix(const Matrix &rhs) {

        //self assignment guard
        if (this != &rhs) {

            //copy static members
            m_numRows = rhs.m_numRows;
            m_numCols = rhs.m_numCols;
            m_numElements = rhs.m_numElements;
            m_isEchelon = rhs.m_isEchelon;
            m_isReducedEchelon = rhs.m_isReducedEchelon;
            m_pivotPositions = rhs.m_pivotPositions;

            //dynamically initialize m_elements
            m_elements = new double *[m_numRows];

            for (int row = 0; row < m_numRows; row++) {
                m_elements[row] = new double[m_numCols];
                for (int col = 0; col < m_numCols; col++) {
                    m_elements[row][col] = rhs.m_elements[row][col];
                }
            }

            //allocate and copy MxM identity matrix
            m_mxmIdentity = new double *[m_numRows];

            for (int row = 0; row < m_numRows; row++){
                m_mxmIdentity[row] = new double[m_numRows];
                memcpy(m_mxmIdentity[row], rhs.m_mxmIdentity[row], sizeof (double) * m_numRows);
            }

            //allocate and copy NxN identity matrix
            m_nxnIdentity = new double *[m_numCols];

            for (int row = 0; row < m_numCols; row++){
                m_nxnIdentity[row] = new double[m_numCols];
                memcpy(m_nxnIdentity[row], rhs.m_nxnIdentity[row], sizeof (double) * m_numCols);
            }
        }
    }

    void Matrix::print() {

        std::cout << "Elements of Matrix at " << this << ":" << std::endl;
        for (int row = 0; row < m_numRows; row++){

            std::cout << "row " << row;

            if (row < 10){
                std::cout << ":  [ ";
            }else{
                std::cout << ": [ ";
            }

            for (int col = 0; col < m_numCols; col++){
                std::cout << m_elements[row][col];

                if (m_elements[row][col] < 10){
                    std::cout << "  ";
                }else{
                    std::cout << " ";
                }
            }

            std::cout << "]" << std::endl;
        }

        std::cout << std::endl;
    }

    void Matrix::makeEchelonForm() {

        if (!m_isEchelon && !m_isReducedEchelon){

            double rowScalar = 0;
            std::pair<int, int> pivot = {0, 0};

            //get non-zero into pivot position
            if (m_elements[pivot.first][pivot.second] == 0){

                if(!makeFirstPivotNonZero(pivot)){
                    return;
                }
            }

            m_pivotPositions.push_back(pivot);

            //set echelon var
            m_isEchelon = true;

            if (m_elements[pivot.first][pivot.second] != 0){

                //loop through all pivot positions and perform forward operations
                for (int i = 0; i < m_numRows; i++) {

                    //perform row operations to clear the pivot column
                    for (int row = pivot.first + 1; row < m_numRows; row++) {

                        if (m_elements[row][pivot.second] != 0) {

                            rowScalar = m_elements[row][pivot.second] / m_elements[pivot.first][pivot.second];

                            //make scalar negative if the sign is the same
                            if ((m_elements[row][pivot.second] < 0 &&
                                    (rowScalar * m_elements[pivot.first][pivot.second]) < 0) ||
                                (m_elements[row][pivot.second] > 0 &&
                                    (rowScalar * m_elements[pivot.first][pivot.second])> 0)) {
                                rowScalar *= -1;
                            }

                            replaceRows(pivot.first, row, rowScalar);

                            m_elements[row][pivot.second] = 0;
                        }
                    }

                    if (pivot.first + 1 < m_numRows){
                        pivot.first++;
                    }

                    if (pivot.second + 1 < m_numCols){
                        pivot.second++;
                    }


                    if (m_elements[pivot.first][pivot.second] == 0){

                        if (!findAndSwapForPivot(pivot)){
                            //no new pivot found, stop
                            return;
                        }
                    }

                    m_pivotPositions.push_back(pivot);
                }
            }
        }
    }

    void Matrix::makeReducedEchelonForm() {

        //get the matrix in echelon form;
        if (!m_isEchelon){

            makeEchelonForm();
        }

        double factor = 0;
        double rowScalar = 0;

        //loop through pivot positions starting with the last one added / rightmost
        for (auto currPivot : m_pivotPositions){

            if (m_elements[currPivot.first][currPivot.second] != 1){

                factor = 1 / m_elements[currPivot.first][currPivot.second];
                scaleRow(currPivot.first, factor);
            }

            //search up the pivot column and clear
            for (int row = currPivot.first; row >= 0; row--){

                if (m_elements[row][currPivot.second] != 0) {

                    rowScalar = m_elements[row][currPivot.second];

                    //make scalar negative if the sign is the same
                    //make scalar negative if the sign is the same
                    if ((m_elements[row][currPivot.second] < 0 &&
                         (rowScalar * m_elements[currPivot.first][currPivot.second]) < 0) ||
                        (m_elements[row][currPivot.second] > 0 &&
                         (rowScalar * m_elements[currPivot.first][currPivot.second])> 0)) {
                        rowScalar *= -1;
                    }

                    replaceRows(currPivot.first, row, rowScalar);
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
            if (m_numCols != rhs.m_numCols || m_numRows != rhs.m_numRows){

                rebuildIdentity = true;

                //delete current array
                for (int row = 0; row < m_numRows; row++){

                    delete[] m_elements[row];
                    m_elements[row] = nullptr;
                }
                delete[] m_elements;

                //realloc matrix to match rhs dimensions
                m_elements = new double*[rhs.m_numRows];
                for (int row = 0; row < rhs.m_numRows; row++){

                    m_elements[row] = new double[rhs.m_numCols];
                }

                //delete MxM identity matrix
                for (int row = 0; row < m_numRows; row++){

                    delete[] m_mxmIdentity[row];
                    m_mxmIdentity[row] = nullptr;
                }

                delete[] m_mxmIdentity;

                //delete NxN identity matrix
                for (int row = 0; row < m_numCols; row++){

                    delete[] m_nxnIdentity[row];
                    m_nxnIdentity[row] = nullptr;
                }
                delete[] m_nxnIdentity;
            }

            //copy static members
            m_numRows = rhs.m_numRows;
            m_numCols = rhs.m_numCols;
            m_numElements = rhs.m_numElements;
            m_isEchelon = rhs.m_isEchelon;
            m_isReducedEchelon = rhs.m_isReducedEchelon;
            m_pivotPositions = rhs.m_pivotPositions;

            //copy m_elements
            for (int row = 0; row < m_numRows; row++){
                memcpy(m_elements[row], rhs.m_elements[row], sizeof (double) * m_numCols);
            }

            if (rebuildIdentity){

                //reallocate and copy MxM identity matrix
                m_mxmIdentity = new double *[m_numRows];

                for (int row = 0; row < m_numRows; row++){
                    m_mxmIdentity[row] = new double[m_numRows];
                    memcpy(m_mxmIdentity[row], rhs.m_mxmIdentity[row], sizeof (double) * m_numRows);
                }

                //reallocate and copy NxN identity matrix
                m_nxnIdentity = new double *[m_numCols];

                for (int row = 0; row < m_numCols; row++){
                    m_nxnIdentity[row] = new double[m_numCols];
                    memcpy(m_nxnIdentity[row], rhs.m_nxnIdentity[row], sizeof (double) * m_numCols);
                }
            }

            return *this;
        }
    }

    //private + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +

    void Matrix::buildIdentityMxM() {

        //allocate array of double array pointers
        m_mxmIdentity = new double *[m_numRows];

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

        for (int row = startRow; row < m_numRows; row += numThreads){
            m_mxmIdentity[row] = new double[m_numRows]{};
            m_mxmIdentity[row][row] = 1;
        }
    }

    void Matrix::buildIdentityNxN() {

        //allocate array of double array pointers
        m_nxnIdentity = new double *[m_numCols];

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

        for (int row = startRow; row < m_numCols; row += numThreads){

            m_nxnIdentity[row] = new double[m_numCols]{};
            m_nxnIdentity[row][row] = 1;
        }
    }

    inline double *Matrix::operator[](const int &row) {
        return m_elements[row];
    }

    void Matrix::addRows(const int &sourceRow, const int &destinationRow) {

        for (int col = 0; col < m_numCols; col++){

            //add the source row index to the destination row index
            m_elements[destinationRow][col] += m_elements[sourceRow][col];

            if (m_elements[destinationRow][col] == (double) -0){
                m_elements[destinationRow][col] = 0;
            }
        }
    }

    void Matrix::replaceRows(const int &sourceRow, const int &destinationRow, const double &sourceMultiple) {

        //multiply entries in the source row and add them to the destination row
        for (int col = 0; col < m_numCols; col++){

            ///REMOVE
            double destElement = m_elements[destinationRow][col];
            double srcElement = m_elements[sourceRow][col];
            double scaledSrcElement = m_elements[sourceRow][col] * sourceMultiple;
            double result = destElement + scaledSrcElement;

            m_elements[destinationRow][col] += (m_elements[sourceRow][col] * sourceMultiple);

            if (m_elements[destinationRow][col] == (double) -0){
                m_elements[destinationRow][col] = 0;
            }
        }
    }

    void Matrix::interchangeRows(const int &swapRow1, const int &swapRow2) {

        //copy swap row 1 to temp location
        double *tempArray = new double[m_numCols];
        memcpy(tempArray, m_elements[swapRow1], sizeof (double) * m_numCols);

        //copy swap row 2 to swap row 1
        memcpy(m_elements[swapRow1], m_elements[swapRow2], sizeof (double) * m_numCols);

        //copy temp to swap row 2
        memcpy(m_elements[swapRow2], tempArray, sizeof (double) * m_numCols);

        delete[] tempArray;
    }

    void Matrix::scaleRow(const int &row, const double &factor) {

        for (int col = 0; col < m_numCols; col++){
            m_elements[row][col] *= factor;
        }
    }

    bool Matrix::makeFirstPivotNonZero(std::pair<int, int> &pivot) {

        for (int currCol = pivot.second; currCol < m_numCols; currCol++) {

            //search the current column for nonzero, swap if found
            for (int currRow = m_numRows - 1; currRow >= 0; currRow--){

                if (m_elements[currRow][currCol] != 0){

                    //swap the current row with nonzero, up to the row of hte current pivot
                    interchangeRows(currRow, pivot.first);
                    pivot.second = currCol;
                    return true;
                }
            }
        }

        return false;
    }

    bool Matrix::findAndSwapForPivot(std::pair<int, int> &pivot) {

        for (int currCol = pivot.second; currCol < m_numCols; currCol++) {

            //search the current column for nonzero, swap if found
            for (int currRow = pivot.first; currRow < m_numRows; currRow++) {

                if ((m_elements[currRow][currCol] != 0) && (currRow > pivot.first)){

                    //swap the current row with nonzero, up to the row of hte current pivot
                    interchangeRows(currRow, pivot.first);
                    pivot.second = currCol;
                    return true;
                }else if (m_elements[currRow][currCol] != 0){

                    pivot.second = currCol;
                    return true;
                }
            }
        }

        return false;
    }

} // wwills2

