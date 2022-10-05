//
// Created by zan on 6/24/22.
//

#ifndef MATRIX_OPERATIONS_MATRIX_H
#define MATRIX_OPERATIONS_MATRIX_H

#include <cstring>
#include "LinearSystem.h"

namespace wwills2{

    class Matrix {
    public:

        Matrix();
        ~Matrix();

        Matrix(int rows, int cols, bool isEchelon=false, bool isReducedEchelon=false);

        Matrix(const Matrix &rhs);

        void print();

        void makeEchelonForm();

        void makeReducedEchelonForm();

        const Matrix &operator=(const Matrix &rhs);

    private:

        void buildIdentityMxM();

        void buildIdentityMxMThread(const int &startRow, const int &numThreads);

        void buildIdentityNxN();

        void buildIdentityNxNThread(const int &startRow, const int &numThreads);

        double *operator[](const int &row);

        void addRows(const int &sourceRow, const int &destinationRow);

        void replaceRows(const int &sourceRow, const int &destinationRow, const double &sourceMultiple);

        void interchangeRows(const int &swapRow1, const int &swapRow2);

        void scaleRow(const int &row, const double &factor);

        bool makeFirstPivotNonZero(std::pair<int, int> &pivot);

        bool findAndSwapForPivot(std::pair<int, int> &pivot);

        int m_numRows;                                      //num rows
        int m_numCols;                                      //num cols
        int m_numElements;                                  //number of m_elements in the m_elements
        bool m_isEchelon;                                   //tracks if the matrix is in echelon form
        bool m_isReducedEchelon;                            //tracks if the matrix has been reduced
        std::vector<std::pair<int, int>> m_pivotPositions;  //the pivot positions of the matrix
        double **m_elements;                                 //2d, dynamically allocated, m_elements array
        double **m_mxmIdentity;                              //identity matrix #rows x #rows
        double **m_nxnIdentity;                              //identity matrix #cols x #cols

        friend LinearSystem;

        friend TestLinearSystem;
    };

} // wwills2

#endif //MATRIX_OPERATIONS_MATRIX_H
