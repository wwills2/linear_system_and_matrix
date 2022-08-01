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

        void print();

        //! important: column zero must be non-zero to work properly
        void echelonForm();


    private:

        Matrix buildIdentityMxM();

        Matrix buildIdentityNxN();

        std::vector<float> &operator[](const int &row);

        void addRows(const int &source, const int &destination);

        void replaceRows(const int &source, const int &destination, const float sourceMultiple);

        void scaleRow(const int &row, float factor);

        int numRows;        //num rows
        int numCols;        //num cols
        int numElements;    //number of elements in the elements
        std::vector< std::vector<float> > elements;   //2d, dynamically allocated, elements array

        friend LinearSystem;

        friend TestLinearSystem;
    };

} // wwills2

#endif //MATRIX_OPERATIONS_MATRIX_H
