//
// Created by zan on 6/20/22.
//

#include <cassert>
#include "TestLinearSystem.h"

using std::cout;
using std::endl;

inline float *wwills::Matrix::operator[](const int row) {
    return elements[row];
}

int main(){

    cout << "benchmark dot vs overloaded[] matrix operator" << endl;
    {
        TestLinearSystem test;
        test.dotVsOverloadBench();
    }

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

    cout << "testing addRows(float *, float *)" << endl;
    {
        TestLinearSystem test;
        test.addRowsTest();
    }

    cout << "testing LinearSystem overloaded [] operator" << endl;
    {
        TestLinearSystem test;
        test.sysOverloadedElementOp();
    }

    cout << "testing Matrix overloaded [] operator" << endl;
    {
        TestLinearSystem test;
        test.matrixOverloadedElementOp();
    }

    cout << "testing replaceRows(float *, float *, float)" << endl;
    {
        TestLinearSystem test;
        test.replaceRowsTest();
    }

    cout << "testing interchangeRows(float *, float *)" << endl;
    {
        TestLinearSystem test;
        test.interchangeRowsTest();
    }

    return 0;
}

void TestLinearSystem::dotVsOverloadBench() {

    /* benchmarks the performance of accessing matrix elements via matrix.elements[m][n] verses accessing elements
     * with an overloaded [] operator via matrix[m][n]
     */

    int numRows = 5000;
    int numCols = 10000;

    wwills::Matrix matrix(numRows, numCols);
    float count = 1;

    //start counting clock cycles
    clock_t start = clock();
    clock_t stop;

    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            matrix.elements[i][j] = count;
            count++;
        }
    }

    stop = clock();

    float time = ((float)(stop - start)) / CLOCKS_PER_SEC;
    cout << "\tdot operator: " << time << " seconds" << endl;

    //start counting clock cycles
    start = clock();

    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            matrix[i][j] = count;
            count++;
        }
    }

    stop = clock();

    time = ((float)(stop - start)) / CLOCKS_PER_SEC;
    cout << "\toverloaded [] operator: " << time << " seconds" << endl;
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

void TestLinearSystem::addRowsTest(){

    wwills::Matrix testMatrix;

    testMatrix.addRows(testMatrix.elements[0], testMatrix.elements[1]);
    assert(testMatrix.elements[1][0] == 5);
    assert(testMatrix.elements[1][1] == 7);
    assert(testMatrix.elements[1][2] == 9);

    testMatrix.print();
}

void TestLinearSystem::matrixOverloadedElementOp() {

    wwills::Matrix testMatrix;

    float *row = testMatrix[0];
    assert(row[0] == 1 && row[1] == 2 && row[2] == 3);

    wwills::LinearSystem testSystem;
    assert(testSystem["A"][0][1][0] == 4);
}

void TestLinearSystem::replaceRowsTest() {

    wwills::Matrix testMatrix;

    testMatrix.replaceRows(testMatrix[0], testMatrix[1], -2);
    assert(testMatrix[1][0] == 2 && testMatrix[1][1] == 1 && testMatrix[1][2] == 0);
}

void TestLinearSystem::interchangeRowsTest() {

    wwills::Matrix testMatrix;

    testMatrix.interchangeRows(testMatrix[0], testMatrix[1]);
    assert(testMatrix[0][0] == 4 && testMatrix[0][1] == 5 && testMatrix[0][2]);
    assert(testMatrix[1][0] == 1 && testMatrix[1][1] == 2 && testMatrix[1][2]);
}

//LinearSystem Tests + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +

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

void TestLinearSystem::sysOverloadedElementOp() {

    wwills::LinearSystem testSystem;

    testSystem.addMatrix("test", 3, 1);
    assert(testSystem["test"]->elements[2][0] == 0);
}








