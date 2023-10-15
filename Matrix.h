//
// Created by zan on 6/24/22.
//

#ifndef MATRIX_OPERATIONS_MATRIX_H
#define MATRIX_OPERATIONS_MATRIX_H

#include <cstring>
#include <algorithm>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <gmpxx.h>
#include "LinearSystem.h"

namespace wwills2{

    struct matrix_dimensions{
        int numRows;
        int numColumns;
    };

    class Matrix {
    public:

        class Iterator;

        Matrix();
        ~Matrix();

        Matrix(int rows, int cols, bool isEchelon=false, bool isReducedEchelon=false);

        Matrix(const Matrix &rhs);

        std::unique_ptr<matrix_dimensions> getDimensions() const;

        void print(std::ostream &output = std::cout);

        void makeEchelonForm();

        void makeReducedEchelonForm();

        Matrix &operator=(const Matrix &rhs);

        Iterator begin();

        Iterator end();

    private:

        void buildIdentityMxM();

        void buildIdentityMxMThread(const int &startRow, const int &numThreads);

        void buildIdentityNxN();

        void buildIdentityNxNThread(const int &startRow, const int &numThreads);

        mpq_class *operator[](const int &row);

        void addRows(const int &sourceRow, const int &destinationRow);

        void replaceRows(const int &sourceRow, const int &destinationRow, const mpq_class &sourceMultiple);

        void interchangeRows(const int &swapRow1, const int &swapRow2);

        void scaleRow(const int &row, const mpq_class &factor);

        bool makeFirstPivotNonZero(std::pair<int, int> &pivot);

        bool findAndSwapForPivot(std::pair<int, int> &pivot);

        int m_numRows;                                      //num rows
        int m_numCols;                                      //num cols
        int m_numElements;                                  //number of m_elements in the m_elements
        bool m_isEchelon;                                   //tracks if the matrix is in echelon form
        bool m_isReducedEchelon;                            //tracks if the matrix has been reduced
        std::vector<std::pair<int, int>> m_pivotPositions;  //the pivot positions of the matrix
        mpq_class **m_elements;                                 //2d, dynamically allocated, m_elements array
        mpq_class **m_mxmIdentity;                              //identity matrix #rows x #rows
        mpq_class **m_nxnIdentity;                              //identity matrix #cols x #cols

        friend LinearSystem;
        friend Iterator;

        friend TestLinearSystem;
    };

    //read only, forward iterator
    class Matrix::Iterator {
    public:
        explicit Iterator(Matrix *matrix);

        Iterator &operator++();

        const mpq_class &operator*() const;

        bool operator==(const Matrix::Iterator &rhs) const;

        bool operator!=(const Matrix::Iterator &rhs) const;

    private:
        friend Matrix::Iterator Matrix::end();
        explicit Iterator(Matrix *matrix, int row, int col);

        Matrix *m_matrix;
        int m_row;
        int m_col;
    };

} // wwills2

#endif //MATRIX_OPERATIONS_MATRIX_H
