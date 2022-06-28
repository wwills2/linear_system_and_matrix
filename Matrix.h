//
// Created by zan on 6/24/22.
//

#ifndef MATRIX_OPERATIONS_MATRIX_H
#define MATRIX_OPERATIONS_MATRIX_H

#include "LinearSystem.h"

namespace wwills{

    class Matrix {
    public:

        Matrix();
        ~Matrix();

        Matrix(int rows, int cols);

        Matrix(const Matrix &rhs);

        void print();

        const Matrix &operator=(const Matrix &rhs);

    private:

        Matrix buildIdentityMxM();

        Matrix buildIdentityNxN();

        void addRows(const float *source, float *destination);

        void replaceRows(const float *source, float *destination);

        void interchangeRows(float *swap1, float *swap2);

        void scaleRow(float *row);

        int numRows;        //num rows
        int numCols;        //num cols
        int numElements;    //number of elements in the elements
        float **elements;     //2d, dynamically allocated elements

        friend LinearSystem;

        friend TestLinearSystem;
    };

} // wwills2

#endif //MATRIX_OPERATIONS_MATRIX_H
