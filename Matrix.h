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

        Matrix(int rows, int cols);

        Matrix(const Matrix &rhs);

        void print();

        //! important: column zero must be non-zero to work properly
        void echelonForm();

        const Matrix &operator=(const Matrix &rhs);

    private:

        void buildIdentityMxM();

        void buildIdentityMxMThread(const int &startRow, const int &numThreads);

        void buildIdentityNxN();

        void buildIdentityNxNThread(const int &startRow, const int &numThreads);

        float *operator[](const int &row);

        void addRows(const int &sourceRow, const int &destinationRow);

        void replaceRows(const int &sourceRow, const int &destinationRow, const float &sourceMultiple);

        void interchangeRows(const int &swapRow1, const int &swapRow2);

        void scaleRow(float *row, const float &factor);

        int numRows;        //num rows
        int numCols;        //num cols
        int numElements;    //number of elements in the elements
        float **elements;   //2d, dynamically allocated, elements array
        float **mxmIdentity;   //identity matrix #rows x #rows
        float **nxnIdentity;   //identity matrix #cols x #cols

        friend LinearSystem;

        friend TestLinearSystem;
    };

} // wwills2

#endif //MATRIX_OPERATIONS_MATRIX_H
