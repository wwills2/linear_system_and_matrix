//
// Created by zan on 6/20/22.
//

#include <cassert>
#include <random>
#include "TestLinearSystem.h"

using std::cout;
using std::endl;

inline float *wwills2::Matrix::operator[](const int &row) {
    return m_elements[row];
}

//Note: This random class was written by the UMBC CSEE Dept.
enum RANDOM {UNIFORM, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORM) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 and standard deviation of 20
            m_normdist = std::normal_distribution<>(50,20);
        }
        else{
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
    }

    int getRandNum(){
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else{
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//uniform distribution

};

int main(){
    /*
    cout << "benchmark dot vs overloaded[] matrix operator" << endl;
    {
        TestLinearSystem test;
        test.dotVsOverloadBench();
    }
     */

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

    cout << "testing makeEchelonForm()" << endl;
    {
        TestLinearSystem test;
        test.echelonFormTest();
    }

    return 0;
}

void TestLinearSystem::dotVsOverloadBench() {

    /* benchmarks the performance of accessing matrix m_elements via matrix.m_elements[m][n] verses accessing m_elements
     * with an overloaded [] operator via matrix[m][n]
     */

    int numRows = 5000;
    int numCols = 10000;

    wwills2::Matrix matrix(numRows, numCols);
    float count = 1;

    //start counting clock cycles
    clock_t start = clock();
    clock_t stop;

    for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
            matrix.m_elements[i][j] = count;
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

wwills2::Matrix &TestLinearSystem::generateRandomMatrix(const int minRowCol, const int maxRowCol){

    Random randRowColAmnt(minRowCol, maxRowCol);
    Random randElement(0, 1000);
    Random makeZeroRow(1, 20);

    int matrixRows = randRowColAmnt.getRandNum();
    int matrixCols = randRowColAmnt.getRandNum();

    wwills2::Matrix newMatrix(matrixRows, matrixCols);

    for (int row = 0; row < matrixRows; row++){

        //randomly leave rows as 0, populate others.
        if (makeZeroRow.getRandNum() > 2){

            for (int col = 0; col < matrixCols; col++){
                newMatrix.m_elements[row][col] = randElement.getRandNum();
            }
        }
    }
}

void TestLinearSystem::matrixInit() {

    wwills2::Matrix testMatrix;
    testMatrix.print();
    assert(testMatrix.m_numElements == (testMatrix.m_numRows * testMatrix.m_numCols));
}

void TestLinearSystem::matrixAssignOp() {

    wwills2::Matrix *testMatrix = new wwills2::Matrix;

    testMatrix->m_elements[0][1] = 5.5;
    testMatrix->m_elements[1][0] = 6.5;

    wwills2::Matrix *copyMatrix = new wwills2::Matrix(10, 4);
    *copyMatrix = *testMatrix;

    assert(&copyMatrix != &testMatrix);
    assert(copyMatrix->m_elements != testMatrix->m_elements);

    delete testMatrix;

    assert(copyMatrix->m_elements[0][1] == 5.5);
    assert(copyMatrix->m_elements[1][0] == 6.5);

    copyMatrix->print();

    delete copyMatrix;
}

void TestLinearSystem::matrixCopyInit() {

    wwills2::Matrix *testMatrix = new wwills2::Matrix;

    testMatrix->m_elements[0][1] = 5.5;
    testMatrix->m_elements[1][0] = 6.5;

    wwills2::Matrix *copyMatrix = new wwills2::Matrix(*testMatrix);

    assert(&copyMatrix != &testMatrix);
    assert(copyMatrix->m_elements != testMatrix->m_elements);

    delete testMatrix;

    assert(copyMatrix->m_elements[0][1] == 5.5);
    assert(copyMatrix->m_elements[1][0] == 6.5);

    copyMatrix->print();

    delete copyMatrix;
}

void TestLinearSystem::buildIdentityMxMTest() {

    wwills2::Matrix testMatrix(30, 20);

    for (int row = 0; row < testMatrix.m_numRows; row++){
        for (int col = 0; col < testMatrix.m_numRows; col++){

            // assert 1 down the diagonal
            if (row == col){
                assert(testMatrix.m_mxmIdentity[row][col] == 1);
            }else{
                assert(testMatrix.m_mxmIdentity[row][col] == 0);
            }
        }
    }

    wwills2::Matrix testMatrixBig(10000, 9000);

    for (int row = 0; row < testMatrixBig.m_numRows; row++) {
        for (int col = 0; col < testMatrix.m_numRows; col++) {

            // assert 1 down the diagonal
            if (row == col) {
                assert(testMatrixBig.m_mxmIdentity[row][col] == 1);
            } else {
                assert(testMatrixBig.m_mxmIdentity[row][col] == 0);
            }
        }
    }
}

void TestLinearSystem::buildIdentityNxNTest() {

    wwills2::Matrix testMatrix(30, 20);

    for (int row = 0; row < testMatrix.m_numCols; row++){
        for (int col = 0; col < testMatrix.m_numCols; col++){

            // assert 1 down the diagonal
            if (row == col){
                assert(testMatrix.m_nxnIdentity[row][col] == 1);
            }else{
                //assert(testMatrix.m_nxnIdentity[row][col] == 0);

                if (testMatrix.m_nxnIdentity[row][col] != 0){
                    cout << "bad val std mat [" << row << "][" << col << "] = " << testMatrix.m_nxnIdentity[row][col] << endl;
                }
            }
        }
    }

    wwills2::Matrix testMatrixBig(10000, 9000);

    for (int row = 0; row < testMatrixBig.m_numCols; row++) {
        for (int col = 0; col < testMatrixBig.m_numCols; col++) {

            // assert 1 down the diagonal
            if (row == col) {
                assert(testMatrixBig.m_nxnIdentity[row][col] == 1);
            }else{
                //assert(testMatrixBig.m_nxnIdentity[row][col] == 0);

                if (testMatrixBig.m_nxnIdentity[row][col] != 0){
                    cout << "bad val [" << row << "][" << col << "] = " << testMatrixBig.m_nxnIdentity[row][col] << endl;
                }
            }
        }
    }
}

void TestLinearSystem::addRowsTest(){

    wwills2::Matrix testMatrix;

    testMatrix.addRows(0, 1);
    assert(testMatrix.m_elements[1][0] == 5);
    assert(testMatrix.m_elements[1][1] == 7);
    assert(testMatrix.m_elements[1][2] == 9);

    testMatrix.print();
}

void TestLinearSystem::matrixOverloadedElementOp() {

    wwills2::Matrix testMatrix;

    float *row = testMatrix[0];
    assert(row[0] == 1 && row[1] == 2 && row[2] == 3);

    wwills2::LinearSystem testSystem;

    testSystem.m_matrices["A"].print();
    assert(testSystem["A"][1][1] == 5);
}

void TestLinearSystem::replaceRowsTest() {

    wwills2::Matrix testMatrix;

    testMatrix.replaceRows(0, 1, -2);
    assert(testMatrix[1][0] == 2 && testMatrix[1][1] == 1 && testMatrix[1][2] == 0);
}

void TestLinearSystem::interchangeRowsTest() {

    wwills2::Matrix testMatrix;

    testMatrix.interchangeRows(0, 1);
    assert(testMatrix[0][0] == 4 && testMatrix[0][1] == 5 && testMatrix[0][2]);
    assert(testMatrix[1][0] == 1 && testMatrix[1][1] == 2 && testMatrix[1][2]);
}

void TestLinearSystem::echelonFormTest() {

    cout << "\tTextbook hardcoded samples" << endl;
    {
        //page 31

        int rows = 4;
        int cols = 6;

        float initialMatrix[24] = {0, 3, -6, 6, 4 ,-5,
                                   3, -7, 8, -5, 8, 9,
                                   0 , 0, 0, 0, 0, 0,
                                   3, -9, 12, -9, 6, 15};

        float initialEchelonMatrix[24] = {3, -9, 12, -9, 6, 15,
                                          0, 2, -4, 4, 2, -6,
                                          0, 0, 0, 0, 1, 4,
                                          0 , 0, 0, 0, 0, 0,};

        wwills2::Matrix testMatrix(4, 6);

        int i = 0;
        for (int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                testMatrix[row][col] = initialMatrix[i];
                i++;
            }
        }

        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;

        i = 0;
        for (int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                assert(testMatrix[row][col] == initialEchelonMatrix[i]);
                i++;
            }
        }
    }
    {
        // page 25

        int rows = 3;
        int cols = 4;

        float initialMatrix[12] = {1 ,5, 2, -6,
                                   0 ,4, -7, 2 ,
                                   0, 0 , 5, 0};

        float initialEchelonMatrix[12] = {1 ,5, 2, -6,
                                          0 ,4, -7, 2 ,
                                          0, 0 , 5, 0};

        wwills2::Matrix testMatrix(3, 4);

        int i = 0;
        for (int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                testMatrix[row][col] = initialMatrix[i];
                i++;
            }
        }

        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;

        i = 0;
        for (int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                assert(testMatrix[row][col] == initialEchelonMatrix[i]);
                i++;
            }
        }
    }
    {
        //page 30

        int rows = 4;
        int cols = 5;

        float initialMatrix[20] = {0, -3, -6, 4, 9,
                                   -1, -2 , -1, 3, 1,
                                   -2, -3, 0, 3, -1,
                                   1, 4, 5, -9, -7};

        float initialEchelonMatrix[20] = {1, 4, 5, -9, -7,
                                          0, 2, 4, -6, -6,
                                          0, 0 , 0, -5, 0,
                                          0, 0, 0, 0, 0};

        wwills2::Matrix testMatrix(4, 5);

        int i = 0;
        for (int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                testMatrix[row][col] = initialMatrix[i];
                i++;
            }
        }

        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;

        i = 0;
        for (int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                assert(testMatrix[row][col] == initialEchelonMatrix[i]);
                i++;
            }
        }
    }

    {
        // page 34 (top)

        int rows = 3;
        int cols = 4;

        float initialMatrix[12] = {1 ,0, -5, 1,
                                   0 ,1, 1, 4,
                                   0, 0 , 0, 0};

        float initialEchelonMatrix[12] = {1 ,0, -5, 1,
                                          0 ,1, 1, 4,
                                          0, 0 , 0, 0};

        wwills2::Matrix testMatrix(3, 4);

        int i = 0;
        for (int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                testMatrix[row][col] = initialMatrix[i];
                i++;
            }
        }

        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;

        i = 0;
        for (int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                assert(testMatrix[row][col] == initialEchelonMatrix[i]);
                i++;
            }
        }
    }
    {
        // page 34 (top) rearranged

        int rows = 3;
        int cols = 4;

        float initialMatrix[12] = {1, 0, -5, 1,
                                   0, 0, 0, 0,
                                   0, 1, 1, 4,};

        float initialEchelonMatrix[12] = {1, 0, -5, 1,
                                          0, 1, 1, 4,
                                          0, 0, 0, 0};

        wwills2::Matrix testMatrix(3, 4);

        int i = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                testMatrix[row][col] = initialMatrix[i];
                i++;
            }
        }

        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;

        i = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                assert(testMatrix[row][col] == initialEchelonMatrix[i]);
                i++;
            }
        }
    }
    {
        //page 34 (bottom)

        int rows = 5;
        int cols = 6;

        float initialMatrix[30] = {1, 6, 2, -5, -2, -4,
                                   0, 0, 0, 0, 0, 0,
                                   0, 0, 0, 0, 1, 7,
                                   0, 0, 0, 0, 0, 0,
                                   0, 0, 2, -8, -1, 3};

        float initialEchelonMatrix[30] = {1, 6, 2, -5, -2, -4,
                                          0, 0, 2, -8, -1, 3,
                                          0, 0, 0, 0, 1, 7,
                                          0, 0, 0, 0, 0, 0,
                                          0, 0, 0, 0, 0, 0};

        wwills2::Matrix testMatrix(5, 6);

        int i = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                testMatrix[row][col] = initialMatrix[i];
                i++;
            }
        }

        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;

        i = 0;
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                assert(testMatrix[row][col] == initialEchelonMatrix[i]);
                i++;
            }
        }
    }

    cout << "corner and edge cases" << endl;
    {
        wwills2::Matrix testMatrix(4, 6);
        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;
    }
    {
        wwills2::Matrix testMatrix;
        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;
    }
    {
        wwills2::Matrix testMatrix(1, 1);
        testMatrix[0][0] = 10;

        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;
    }
    {
        wwills2::Matrix testMatrix(2, 1);
        testMatrix[0][0] = 10;
        testMatrix[1][0] = 5;

        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;
    }
    {
        wwills2::Matrix testMatrix(1, 2);
        testMatrix[0][0] = 10;
        testMatrix[0][1] = 5;

        testMatrix.print();
        testMatrix.makeEchelonForm();
        testMatrix.print();
        cout << endl;
    }

    cout << "moving 1 echelon test" << endl;
    {
        int numRows = 6;
        int numCols = 5;

        for(int row = 0; row < numRows; row++){
            for(int col = 0; col < numCols; col++){

                wwills2::Matrix testMatrix(numRows, numCols);
                testMatrix[row][col] = 1;

                cout << "before reduction" << endl;
                testMatrix.print();
                testMatrix.makeEchelonForm();
                cout << "after reduction" << endl;
                testMatrix.print();


                //assert that the 1 has been moved into the first row in the correct col
                assert(testMatrix.m_elements[0][col] == 1);

                //verify all other rows are zero
                for(int i = 1; i < numRows; i++){
                    for(int j = 0; j < numCols; j++){
                        assert(testMatrix.m_elements[i][j] == 0);
                    }
                }
            }
        }
    }

    /*
    {
        cout << "\trandom generated test samples" << endl;

        int numTests = 100;
        int maxRowCol = 100;
        int minRowCol = 10;

        for (int testNum = 0; testNum < numTests; testNum++){

            //individual test scope
            {
                //auto testMatrix = generateRandomMatrix(minRowCol, maxRowCol);
                //!needs to be finished
            }
        }
    }
     */
}


//LinearSystem Tests + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +

void TestLinearSystem::addMatrixTest() {


    wwills2::LinearSystem testSystem;
    testSystem.addMatrix("testDefault");

    assert(testSystem.m_matrices["testDefault"].m_elements[0][0] == 1);

    testSystem.addMatrix("testArguments", 4, 5);

    for (int i = 0; i < testSystem.m_matrices["testArguments"].m_numRows; i++){
        for (int j = 0; j < testSystem.m_matrices["testArguments"].m_numCols; j++){
            assert(testSystem.m_matrices["testArguments"].m_elements[i][j] == 0);
        }
    }
}


void TestLinearSystem::linearSysInit() {

    wwills2::LinearSystem testSystem;
    assert(testSystem.m_numMatrices == 1);
    assert(testSystem.m_matrices["A"].m_numElements == 6);
    assert(testSystem.m_matrices["A"].m_elements[0][0] == 1);
}

void TestLinearSystem::sysOverloadedElementOp() {

    wwills2::LinearSystem testSystem;

    testSystem.addMatrix("test", 3, 1);
    assert(testSystem["test"].m_elements[2][0] == 0);
}
