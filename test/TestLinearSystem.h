//
// Created by zan on 6/20/22.
//

#ifndef MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
#define MATRIX_OPERATIONS_TESTLINEARSYSTEM_H

#include "../LinearSystem.h"
#include "../Matrix.h"

class TestLinearSystem {

public:

    /*
    static void debugMatrixPrint(wwills::Matrix &matrix){

        for (int row = 0; row < matrix.numRows; row++){

            std::cout << "row " << row << ": [ ";

            for (int col = 0; col < matrix.numCols; col++){
                std::cout << elements[row][col] << " ";
            }

            std::cout << "]\n";
        }
    }
    */

    void matrixInit();                          //calls the elements constructor to initialize a generic elements
    void matrixAssignOp();                      //calls matrix overloaded assigment operator
    void matrixCopyInit();                      //calls matrix overloaded copy constructor
    void buildIdentityMxMTest();                //calls buildIdentityMxMTest
    void buildIdentityNxNTest();                //calls buildIdentityNxNTest
    void addRowsTest();                         //calls addRows(float *, float *)
    void matrixOverloadedElementOp();           //calls the Matrix overloaded [] operator
    void replaceRowsTest();                     //calls replaceRows(float *, float *, float)
    void interchangeRowsTest();                 //calls interchangeRows (float *, float *)
    void echelonFormTest();                      //calls echelonFormTest()

    void linearSysInit();                       //calls the linear system constructor, generic linear system object
    void addMatrixTest();                       //calls both add matrix functions
    void sysOverloadedElementOp();              //calls the LinearSystem overloaded [] operator

    void dotVsOverloadBench();                  //see test file


};


#endif //MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
