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
        test.matrixAssignOP();
    }

    cout << "testing LinearSystem constructor" << endl;
    {
        TestLinearSystem test;
        //test.linearSysInit();
    }

    return 0;
}



void TestLinearSystem::matrixInit() {

    wwills::Matrix testMatrix;
    testMatrix.print();
    assert(testMatrix.numElements == (testMatrix.numRows * testMatrix.numCols));
}

void TestLinearSystem::matrixAssignOP() {
    wwills::Matrix testMatrix;

    testMatrix.elements[0][1] = 5.5;
    testMatrix.elements[1][0] = 6.5;

    wwills::Matrix copyMatrix;
    copyMatrix = testMatrix;

    assert(&copyMatrix != &testMatrix);
    assert(copyMatrix.elements != testMatrix.elements);
    assert(copyMatrix.elements[0][1] == 5.5);
    assert(copyMatrix.elements[1][0] == 6.5);
}

void TestLinearSystem::linearSysInit() {

    wwills::LinearSystem testSystem;
    assert(testSystem.numMatrices == 1);
    assert(testSystem.matrices["A"].numElements == 6);
    assert(testSystem.matrices["A"].elements[0][0] == 1);

}


