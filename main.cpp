//
//  main.cpp
//  sparsematrix
//
//  Created by jwkangmacpro on 2017. 5. 15..
//  Copyright © 2017년 jwkangmacpro. All rights reserved.
//

#include <iostream>
#include "src/sparseMatrix.h"

//#define DATASET1
//#define DATASET2
//#define DATASET3
#define DATASET_FOR_MUL

int main(void)
{
    std::cout<<"# [Main]  Title: Qualcomm Programming Assignment: Problem # 1"<<std::endl;

# ifdef DATASET1
    const int rowSize0 = 4;
    const int colSize0 = 5;
    const char* intputfilename = "./testdata/matrix_input.txt";
    
    sparseMatrix mat0(rowSize0,colSize0);
    mat0.readMatrix(intputfilename);
    mat0.showMatrix();
#endif

#ifdef DATASET2
    const int rowSize0 = 20;
    const int colSize0 = 10;
    const char* intputfilename = "./testdata/matrix_input2.txt";
    
    sparseMatrix mat0(rowSize0,colSize0);
    mat0.readMatrix(intputfilename);
    mat0.showMatrix();
#endif

#ifdef DATASET3
    const int rowSize0 = 20;
    const int colSize0 = 20;
    const char* intputfilename = "./testdata/matrix_input3.txt";
    
    sparseMatrix mat0(rowSize0,colSize0);
    mat0.readMatrix(intputfilename);
    mat0.showMatrix();
#endif
    
    
    
#ifdef DATASET_FOR_MUL
    const int rowSize0 = 4;
    const int colSize0 = 5;
    const char* intputfilename = "./testdata/matrix_input.txt";

    const int rowSize1 = 5;
    const int colSize1 = 4;
    const char* intputfilename1 = "./testdata/matrix_input4.txt";
    std::cout<<"============================================================="<<std::endl;
    std::cout<<"# [Main] Reading the first Matrix, denoted by A, from a file"<<std::endl;
    
    sparseMatrix mat0(rowSize0,colSize0);
    mat0.readMatrix(intputfilename);
    mat0.showMatrix();
    
    std::cout<<"============================================================="<<std::endl;
    std::cout<<"# [Main] Reading the second Matrix, denoted by B, from a file"<<std::endl;
    
    sparseMatrix mat1(rowSize1,colSize1);
    mat1.readMatrix(intputfilename1);
    //mat1.showMatrix();
    
    sparseMatrix matOut;
    std::cout<<"============================================================="<<std::endl;
    std::cout<<"# [Main] Sparse Matrix mutiplications, denoted by C=A*B"<<std::endl;
    //    matOut =  mat0 * mat1
    mulSparseMatrix(&mat0, &mat1, &matOut);
    
#endif

    
    return 0;
}
