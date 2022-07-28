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

        void debugPrint();

        //! important: column zero must be non-zero to work properly
        void echelonForm();

        const Matrix &operator=(const Matrix &rhs);

    private:

        Matrix buildIdentityMxM();

        Matrix buildIdentityNxN();

        std::vector<float> operator[](const int row);

        void addRows(const std::vector<float> &source, std::vector<float> &destination);

        void replaceRows(const std::vector<float> &source, std::vector<float> &destination, const float sourceMultiple);

        void interchangeRows(std::vector<float> &swap1, std::vector<float> &swap2);

        void scaleRow(std::vector<float> &row, float factor);

        int numRows;        //num rows
        int numCols;        //num cols
        int numElements;    //number of elements in the elements
        std::vector< std::vector<float> > elements;   //2d, dynamically allocated, elements array

        friend LinearSystem;

        friend TestLinearSystem;
    };

} // wwills2

#endif //MATRIX_OPERATIONS_MATRIX_H
