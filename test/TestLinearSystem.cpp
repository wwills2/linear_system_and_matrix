//
// Created by zan on 6/20/22.
//

#include "TestLinearSystem.h"

int main(){

    TestLinearSystem test;

    test.classInitAndPrint();

    return 0;
}



void TestLinearSystem::classInitAndPrint() {

    wwills::LinearSystem testSystem;
    testSystem.matrices["A"].print();
}
