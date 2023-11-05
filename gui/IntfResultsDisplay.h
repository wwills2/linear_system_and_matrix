//
// Created by zan on 11/4/23.
//

#ifndef MATRIX_OPERATIONS_INTFRESULTSDISPLAY_H
#define MATRIX_OPERATIONS_INTFRESULTSDISPLAY_H

#include "../MatrixManager.h"

class IntfResultsDisplay {
public:

    ~IntfResultsDisplay() = default;
    virtual bool setResultsUiData(wwills2::MatrixManager &matrixManager) = 0;
};


#endif //MATRIX_OPERATIONS_INTFRESULTSDISPLAY_H
