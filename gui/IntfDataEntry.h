//
// Created by zan on 10/26/23.
//

#ifndef MATRIX_OPERATIONS_INTFDATAENTRY_H
#define MATRIX_OPERATIONS_INTFDATAENTRY_H

#include "../MatrixManager.h"

/**
 * interface to be implemented by views which take in data for a matrix operation
 */
class IntfDataEntry{
public:

    ~IntfDataEntry() = default;
    virtual bool loadUiData(wwills2::MatrixManager &matrixManager) = 0;
};


#endif //MATRIX_OPERATIONS_INTFDATAENTRY_H
