//
// Created by zan on 6/20/22.
//

#ifndef MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
#define MATRIX_OPERATIONS_TESTLINEARSYSTEM_H

#include "../LinearSystem.h"
#include "../Matrix.h"

class TestLinearSystem {

public:


    void matrixInit();                          //calls the elements constructor to initialize a generic elements
    void matrixAssignOp();                      //tests assigning one matrix to another
    void buildIdentityMxMTest();                //calls buildIdentityMxMTest
    void buildIdentityNxNTest();                //calls buildIdentityNxNTest
    void addRowsTest();                         //calls addRows(float *, float *)
    void matrixOverloadedElementOp();           //calls the Matrix overloaded [] operator
    void replaceRowsTest();                     //calls replaceRows(float *, float *, float)
    void echelonFormTest();                      //calls echelonFormTest()

    void linearSysInit();                       //calls the linear system constructor, generic linear system object
    void addMatrixTest();                       //calls both add matrix functions
    void sysOverloadedElementOp();              //calls the LinearSystem overloaded [] operator

    void dotVsOverloadBench();                  //see test file


};


#endif //MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
