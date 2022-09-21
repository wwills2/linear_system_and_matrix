//
// Created by zan on 6/20/22.
//

#ifndef MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
#define MATRIX_OPERATIONS_TESTLINEARSYSTEM_H

#include "../LinearSystem.h"
#include "../Matrix.h"

class TestLinearSystem {

public:

    void matrixInit();                          //calls the m_elements constructor to initialize a generic m_elements
    void matrixAssignOp();                      //calls matrix overloaded assigment operator
    void matrixCopyInit();                      //calls matrix overloaded copy constructor
    void buildIdentityMxMTest();                //calls buildIdentityMxMTest
    void buildIdentityNxNTest();                //calls buildIdentityNxNTest
    void addRowsTest();                         //calls addRows(float *, float *)
    void matrixOverloadedElementOp();           //calls the Matrix overloaded [] operator
    void replaceRowsTest();                     //calls replaceRows(float *, float *, float)
    void interchangeRowsTest();                 //calls interchangeRows (float *, float *)
    void echelonFormTest();                     //calls echelonFormTest()

    void linearSysInit();                       //calls the linear system constructor, generic linear system object
    void addMatrixTest();                       //calls both add matrix functions
    void sysOverloadedElementOp();              //calls the LinearSystem overloaded [] operator

    void dotVsOverloadBench();                  //see test file

    //builds a random matrix
    wwills2::Matrix generateRandomMatrix(const int matrixRows, const int matrixCols);

    //builds random reduced matrix
    wwills2::Matrix generateRandomReducedMatrix(const int matrixRows, const int matrixCols);


};


#endif //MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
