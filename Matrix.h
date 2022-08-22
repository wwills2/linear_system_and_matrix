//
// Created by zan on 6/24/22.
//

#ifndef MATRIX_OPERATIONS_MATRIX_H
#define MATRIX_OPERATIONS_MATRIX_H

#include <cstring>
#include "LinearSystem.h"

namespace wwills{

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

        Matrix buildIdentityMxM();

        void buildIdentityMxMThread(int startRow, int numThreads);

        Matrix buildIdentityNxN();

        void buildIdentityNxNThread();

        float *operator[](const int &row);

        void addRows(const int &sourceRow, const int &destinationRow);

        void replaceRows(const int &sourceRow, const int &destinationRow, const float &sourceMultiple);

        void interchangeRows(const int &swapRow1, const int &swapRow2);

        void scaleRow(float *row, const float &factor);

        int numRows;        //num rows
        int numCols;        //num cols
        int numElements;    //number of elements in the elements
        float **elements;   //2d, dynamically allocated, elements array
        float **MxM_identity;   //identity matrix #rows x #rows
        float **NxN_identity;   //identity matrix #cols x #cols

        friend LinearSystem;

        friend TestLinearSystem;
    };

} // wwills2

#endif //MATRIX_OPERATIONS_MATRIX_H
