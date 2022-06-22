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

    cout << "testing LinearSystem constructor" << endl;
    {
        TestLinearSystem test;
        test.linearSysInit();
    }

    return 0;
}



void TestLinearSystem::matrixInit() {

    wwills::Matrix testMatrix;
    testMatrix.print();
    assert(testMatrix.numElements == (testMatrix.numRows * testMatrix.numCols));
}

void TestLinearSystem::linearSysInit() {

    wwills::LinearSystem testSystem;
    assert(testSystem.numMatrices == 1);
    assert(testSystem.matrices["A"].numElements == 6);
    assert(testSystem.matrices["A"].matrix[0][0] < 1.001 && testSystem.matrices["A"].matrix[0][0] > 0.999);

}
