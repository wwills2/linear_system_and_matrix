//
// Created by zan on 6/20/22.
//

#ifndef MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
#define MATRIX_OPERATIONS_TESTLINEARSYSTEM_H

#include <random>
#include <algorithm>
#include "MatrixManager.h"
#include "Matrix.h"

#define LOG_FILE "./test_output.txt"
class Random;

class TestLinearSystem {

public:

    static void matrixInit();                          //calls the m_elements constructor to initialize a generic m_elements
    static void matrixAssignOp();                      //calls matrix overloaded assigment operator
    static void matrixCopyInit();                      //calls matrix overloaded copy constructor
    static void buildIdentityMxMTest();                //calls buildIdentityMxMTest
    static void buildIdentityNxNTest();                //calls buildIdentityNxNTest
    static void addRowsTest();                         //calls addRows(float *, float *)
    static void matrixOverloadedElementOp();           //calls the Matrix overloaded [] operator
    static void replaceRowsTest();                     //calls replaceRows(float *, float *, float)
    static void interchangeRowsTest();                 //calls interchangeRows (float *, float *)
    static void echelonFormTest();                     //calls echelonFormTest()
    static void reducedEchelonFormTest();              //calls makeReducedEchelonForm()

    static void linearSysInit();                       //calls the linear system constructor, generic linear system object
    static void sysGetMatrix();                        //calls the MatrixManager getMatrix(std::string &) method

    void dotVsOverloadBench();                  //see test file

    //builds a random matrix
    static auto generateRandomMatrix(const int minRowCol, const int maxRowCol);

    //builds random reduced matrix
    static wwills2::Matrix generateRandomReducedMatrix(const int matrixRows, const int matrixCols, Random &randElement);

    //randomizes reduced matrix with random row operations
    static void matrixRandomize(wwills2::Matrix &toRandomize, Random &randRowOP, Random &randRowNum,
                                Random &randScalar, const int numIterations);
};


#endif //MATRIX_OPERATIONS_TESTLINEARSYSTEM_H
