//
//  sparseMatrix.h
//  sparsematrix
//
//  Created by jwkangmacpro on 2017. 5. 15..
//  Copyright © 2017년 jwkangmacpro. All rights reserved.
//


#ifndef sparseMatrix_h
#define sparseMatrix_h

#include <cstdio>
#include <cmath>
#include <memory>

const int INVAILD_VALUE = -999;


class sparseMatrix{
private:

    short** mSparseMatrixRepTable = NULL;
    
    const int mTableSize = 3;
    
    unsigned int mMatrixRowSize;
    unsigned int mMatrixColSize;
    unsigned int mNumOfNonZeros;
    
    void allocate(const unsigned  int numOfNonzeros_);
    void deAllocate(void);
    void showElemInMatrix(const int nonzeroIndex);

public:
    sparseMatrix();
    sparseMatrix(const unsigned int rowSize_, const unsigned int colSize_);
    sparseMatrix(const unsigned int rowSize_, const unsigned int colSize_, const unsigned int nonZeroNum_);

    ~sparseMatrix();
    
    void readMatrix(const char* inputfilename);
    void showMatrix();
    
    unsigned int getRowSize() const { return mMatrixRowSize;}
    unsigned int getColSize() const { return mMatrixColSize;}
    unsigned int getNumofNonZeros() const { return  mNumOfNonZeros;}
    
    unsigned int getRowIndex(const int nonzeroIndex) const { return mSparseMatrixRepTable[0][nonzeroIndex];}
    unsigned int getColIndex(const int nonzeroIndex) const { return mSparseMatrixRepTable[1][nonzeroIndex];}
    
    short getElemValue(const int nonzeroIndex) const { return mSparseMatrixRepTable[2][nonzeroIndex];}
    short getElemValue(const unsigned int rowIndex, const unsigned int colIndex);

    void setMatrix(short** table,const unsigned int rowSize_, const unsigned int colSize_, const unsigned int nonZeroNum_);
    
    int isNonZeroInRow(const unsigned int rowIndex);

    
};

/* sparse matrix multiplicatio:  A*B = C */
bool mulSparseMatrix(sparseMatrix* Ain, sparseMatrix* Bin, sparseMatrix* Cout);

#endif /* sparseMatrix_h */
