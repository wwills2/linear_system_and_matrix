//
// Created by zan on 6/20/22.
//

#ifndef MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
#define MATRIX_OPERATIONS_TESTLINEARSYSTEM_H

#include "../LinearSystem.h"

class TestLinearSystem {

public:
    void matrixInit();                          //calls the elements constructor to initialize a generic elements
    void matrixAssignOP();                      //calls matrix overloaded assigment operator
    void matrixCopyInit();                      //calls matrix overloaded copy constructor
    void buildIdentityMxMTest();                //calls buildIdentityMxMTest
    void buildIdentityNxNTest();
    void linearSysInit();                       //calls the linear system constructor, generic linear system object


};


#endif //MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
