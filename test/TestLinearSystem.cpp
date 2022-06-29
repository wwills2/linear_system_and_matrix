//
// Created by zan on 6/20/22.
//

#include <cassert>

#include "TestLinearSystem.h"

using std::cout;
using std::endl;


int main(){

    cout << "testing Matrix constructor" << endl;
    {
        TestLinearSystem test;
        test.matrixInit();
    }

    cout << "testing Matrix assignment operator" << endl;
    {
        TestLinearSystem test;
        test.matrixAssignOp();
    }

    cout << "testing Matrix assignment operator" << endl;
    {
        TestLinearSystem test;
        test.matrixCopyInit();
    }

    cout << "testing Matrix buildIdentityMxM()" << endl;
    {
        TestLinearSystem test;
        test.buildIdentityMxMTest();
    }

    cout << "testing Matrix buildIdentityNxN()" << endl;
    {
        TestLinearSystem test;
        test.buildIdentityNxNTest();
    }

    cout << "testing LinearSystem constructor" << endl;
    {
        TestLinearSystem test;
        test.linearSysInit();
    }

    cout << "testing addMatrix() and addMatrix(rows, cols)" << endl;
    {
        TestLinearSystem test;
        test.addMatrixTest();
    }

    return 0;
}



void TestLinearSystem::matrixInit() {

    wwills::Matrix testMatrix;
    testMatrix.print();
    assert(testMatrix.numElements == (testMatrix.numRows * testMatrix.numCols));
}

void TestLinearSystem::matrixAssignOp() {

    wwills::Matrix testMatrix;

    testMatrix.elements[0][1] = 5.5;
    testMatrix.elements[1][0] = 6.5;

    wwills::Matrix copyMatrix;
    copyMatrix = testMatrix;

    assert(&copyMatrix != &testMatrix);
    assert(copyMatrix.elements != testMatrix.elements);
    assert(copyMatrix.elements[0][1] == 5.5);
    assert(copyMatrix.elements[1][0] == 6.5);

    copyMatrix.print();
}

void TestLinearSystem::matrixCopyInit() {

    wwills::Matrix testMatrix;

    testMatrix.elements[0][1] = 5.5;
    testMatrix.elements[1][0] = 6.5;

    wwills::Matrix copyMatrix = testMatrix;

    assert(&copyMatrix != &testMatrix);
    assert(copyMatrix.elements != testMatrix.elements);
    assert(copyMatrix.elements[0][1] == 5.5);
    assert(copyMatrix.elements[1][0] == 6.5);

    copyMatrix.print();
}

void TestLinearSystem::buildIdentityMxMTest() {

    wwills::Matrix testMatrix;
    wwills::Matrix I = testMatrix.buildIdentityMxM();

    assert(I.numElements == (testMatrix.numRows * testMatrix.numRows));
    assert(I.elements[0][0] == 1);
    assert(I.elements[1][1] == 1);
    assert(I.elements[0][1] == 0);
    assert(I.elements[1][0] == 0);

    I.print();
}

void TestLinearSystem::buildIdentityNxNTest() {

    wwills::Matrix testMatrix;
    wwills::Matrix I = testMatrix.buildIdentityNxN();

    assert(I.numElements == (testMatrix.numCols * testMatrix.numCols));
    assert(I.elements[0][0] == 1);
    assert(I.elements[1][1] == 1);
    assert(I.elements[2][2] == 1);
    assert(I.elements[0][1] == 0);
    assert(I.elements[1][0] == 0);

    I.print();
}

void TestLinearSystem::addMatrixTest() {


    wwills::LinearSystem testSystem;
    testSystem.addMatrix("testDefault");

    assert(testSystem.matrices["testDefault"]->elements[0][0] == 1);

    testSystem.addMatrix("testArguments", 4, 5);

    for (int i = 0; i < testSystem.matrices["testArguments"]->numRows; i++){
        for (int j = 0; j < testSystem.matrices["testArguments"]->numCols; j++){
            assert(testSystem.matrices["testArguments"]->elements[i][j] == 0);
        }
    }
}


void TestLinearSystem::linearSysInit() {

    wwills::LinearSystem testSystem;
    assert(testSystem.numMatrices == 1);
    assert(testSystem.matrices["A"]->numElements == 6);
    assert(testSystem.matrices["A"]->elements[0][0] == 1);
}

void TestLinearSystem::overloadedElementOp() {

    wwills::LinearSystem testSystem;

    testSystem.addMatrix("test", 3, 1);
    assert(testSystem["test"].)
}




