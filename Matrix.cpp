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

        //allocate array of float array pointers
        m_elements = new float *[m_numRows];

        //initialize array and allocate individual m_elements
        float num = 1;

        for (int row = 0; row < m_numRows; row++){
            m_elements[row] = new float[m_numCols];
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

        //allocate array of float array pointers
        m_elements = new float *[m_numRows];

        //initialize array and allocate individual m_elements
        for (int row = 0; row < m_numRows; row++){
            m_elements[row] = new float[m_numCols];
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

            //dynamically initialize m_elements
            m_elements = new float *[m_numRows];

            for (int row = 0; row < m_numRows; row++) {
                m_elements[row] = new float[m_numCols];
                for (int col = 0; col < m_numCols; col++) {
                    m_elements[row][col] = rhs.m_elements[row][col];
                }
            }

            //allocate and copy MxM identity matrix
            m_mxmIdentity = new float *[m_numRows];

            for (int row = 0; row < m_numRows; row++){
                m_mxmIdentity[row] = new float[m_numRows];
                memcpy(m_mxmIdentity[row], rhs.m_mxmIdentity[row], sizeof (float) * m_numRows);
            }

            //allocate and copy NxN identity matrix
            m_nxnIdentity = new float *[m_numCols];

            for (int row = 0; row < m_numCols; row++){
                m_nxnIdentity[row] = new float[m_numCols];
                memcpy(m_nxnIdentity[row], rhs.m_nxnIdentity[row], sizeof (float) * m_numCols);
            }
        }
    }

    void Matrix::print() {

        std::cout << "Elements of Matrix at " << this << ":" << std::endl;
        for (int row = 0; row < m_numRows; row++){

            std::cout << "row " << row << ": [ ";

            for (int col = 0; col < m_numCols; col++){
                std::cout << m_elements[row][col] << " ";
            }

            std::cout << "]" << std::endl;
        }

        std::cout << std::endl;
    }

    void Matrix::makeEchelonForm() {

        float rowScalar = 0;
        std::pair<int, int> pivot = {0, 0};
        int tryRow = m_numRows - 1;

        //get non-zero into pivot position
        while ((pivot.second != m_numCols) && (m_elements[pivot.first][pivot.second] == 0)){

            //swap current row with first row if non-zero found
            if (m_elements[tryRow][pivot.second] != 0) {

                interchangeRows(tryRow, pivot.first);

            }else if (tryRow == m_numRows - 1) {

                //move the pivot column over 1 and try to find a non-zero entry
                pivot.second++;
                tryRow = m_numRows - 1;

            }else if ((tryRow + 1) < m_numRows){

                tryRow--;
            }
        }

        if(pivot.second >= m_numCols){
            return;
        }

        if (m_elements[pivot.first][pivot.second] != 0){

            //loop through all pivot positions and perform forward operations
            for (int i = 0; i < m_numRows; i++) {

                //perform row operations to clear the pivot column
                for (int row = pivot.first + 1; row < m_numRows; row++) {

                    if (m_elements[row][pivot.second] != 0) {

                        rowScalar = m_elements[row][pivot.second] / m_elements[pivot.first][pivot.second];

                        //make scalar negative if the sign is the same
                        if ((m_elements[row][pivot.second] < 0 && rowScalar < 0) ||
                            (m_elements[row][pivot.second] > 0 && rowScalar > 0)) {
                            rowScalar *= -1;
                        }

                        replaceRows(pivot.first, row, rowScalar);
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
                m_elements = new float*[rhs.m_numRows];
                for (int row = 0; row < rhs.m_numRows; row++){

                    m_elements[row] = new float[rhs.m_numCols];
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

            //copy m_elements
            for (int row = 0; row < m_numRows; row++){
                memcpy(m_elements[row], rhs.m_elements[row], sizeof (float) * m_numCols);
            }

            if (rebuildIdentity){

                //reallocate and copy MxM identity matrix
                m_mxmIdentity = new float *[m_numRows];

                for (int row = 0; row < m_numRows; row++){
                    m_mxmIdentity[row] = new float[m_numRows];
                    memcpy(m_mxmIdentity[row], rhs.m_mxmIdentity[row], sizeof (float) * m_numRows);
                }

                //reallocate and copy NxN identity matrix
                m_nxnIdentity = new float *[m_numCols];

                for (int row = 0; row < m_numCols; row++){
                    m_nxnIdentity[row] = new float[m_numCols];
                    memcpy(m_nxnIdentity[row], rhs.m_nxnIdentity[row], sizeof (float) * m_numCols);
                }
            }

            return *this;
        }
    }

    //private + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +

    void Matrix::buildIdentityMxM() {

        //allocate array of float array pointers
        m_mxmIdentity = new float *[m_numRows];

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
            m_mxmIdentity[row] = new float[m_numRows]{};
            m_mxmIdentity[row][row] = 1;
        }
    }

    void Matrix::buildIdentityNxN() {

        //allocate array of float array pointers
        m_nxnIdentity = new float *[m_numCols];

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

            m_nxnIdentity[row] = new float[m_numCols]{};
            m_nxnIdentity[row][row] = 1;
        }
    }

    inline float *Matrix::operator[](const int &row) {
        return m_elements[row];
    }

    void Matrix::addRows(const int &sourceRow, const int &destinationRow) {

        for (int col = 0; col < m_numCols; col++){

            //add the source row index to the destination row index
            m_elements[destinationRow][col] += m_elements[sourceRow][col];
        }
    }

    void Matrix::replaceRows(const int &sourceRow, const int &destinationRow, const float &sourceMultiple) {

        //multiply entries in the source row and add them to the destination row
        for (int col = 0; col < m_numCols; col++){
            m_elements[destinationRow][col] += (m_elements[sourceRow][col] * sourceMultiple);
        }
    }

    void Matrix::interchangeRows(const int &swapRow1, const int &swapRow2) {

        //copy swap row 1 to temp location
        float *tempArray = new float[m_numCols];
        memcpy(tempArray, m_elements[swapRow1], sizeof (float) * m_numCols);

        //copy swap row 2 to swap row 1
        memcpy(m_elements[swapRow1], m_elements[swapRow2], sizeof (float) * m_numCols);

        //copy temp to swap row 2
        memcpy(m_elements[swapRow2], tempArray, sizeof (float) * m_numCols);

        delete[] tempArray;
    }

    void Matrix::scaleRow(float *row, const float &factor) {

        for (int col = 0; col < m_numCols; col++){
            row[col] *= factor;
        }
    }

    bool Matrix::findAndSwapForPivot(std::pair<int, int> &pivot) {

        for (int currCol = pivot.second; currCol < m_numCols; currCol++) {

            //search the current column for nonzero, swap if found
            for (int currRow = pivot.first + 1; currRow < m_numRows; currRow++) {

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

} // wwills2

