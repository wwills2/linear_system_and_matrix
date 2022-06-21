/*****************************************
** File:    main.cpp
** Project: Matrix operations program / library
** Author:  Zan Wills
** Date:    6/14/2022
**
** This file contains the driver for the matrix operations program
**
***********************************************/


#include <string>
#include <iostream>

#include "LinearSystem.h"

int main(int arg, char **argv) {

    if (arg == 2){

        //input file
        std::cout << "this is when i would call my input file\n";
    }else{

        std::string rawInput;           //input directly from command line
        int dimension;                  //temp var to hold value
        int **coefficientMatrix2D;      //holds the 2D coefficient matrix

        //take in input from cli
        std::cout << "enter # rows in coefficient matrix: \n";
        std::cin >> rawInput;
        dimension = rawInput[0] - 48;
        matrixDimensions[0] = dimension;

        std::cout << "enter # columns in coefficient matrix: \n";
        std::cin >> rawInput;
        dimension = rawInput[0] - 48;
        matrixDimensions[1] = dimension;

        *coefficientMatrix2D = new int[6];

        std::cout << "enter matrix row by row\n";
        for (int i = 0; i < matrixDimensions[0]; i++){


        }

    }

    return 0;
}
