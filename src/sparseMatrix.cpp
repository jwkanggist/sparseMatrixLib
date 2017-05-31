//
//  sparseMatrix.cpp
//  sparsematrix
//
//  Created by jwkangmacpro on 2017. 5. 15..
//  Copyright © 2017년 jwkangmacpro. All rights reserved.
//

#include "sparseMatrix.h"
#include <fstream>
#include <iostream>

sparseMatrix::sparseMatrix()
{
    mMatrixRowSize = 0;
    mMatrixColSize = 0;
    mNumOfNonZeros = 0;
    std::cout<<"------------------------------"<<std::endl;

    std::cout<<"[sparseMatrix] mMatrixRowSize = "<<mMatrixRowSize<<std::endl;
    std::cout<<"[sparseMatirx] mMatrixColSize = "<<mMatrixColSize<<std::endl;
}


sparseMatrix::sparseMatrix(const  unsigned int rowSize_, const  unsigned int colSize_)
{
    mMatrixRowSize = rowSize_;
    mMatrixColSize = colSize_;
    mNumOfNonZeros = 0;
    std::cout<<"------------------------------"<<std::endl;

    std::cout<<"[sparseMatrix] mMatrixRowSize = "<<mMatrixRowSize<<std::endl;
    std::cout<<"[sparseMatirx] mMatrixColSize = "<<mMatrixColSize<<std::endl;
}

sparseMatrix::sparseMatrix(const  unsigned int rowSize_, const  unsigned int colSize_, const  unsigned int nonZeroNum_)
{
    mMatrixRowSize = rowSize_;
    mMatrixColSize = colSize_;
    mNumOfNonZeros = nonZeroNum_;
    std::cout<<"------------------------------"<<std::endl;

    std::cout<<"[sparseMatrix] mMatrixRowSize = "<<mMatrixRowSize<<std::endl;
    std::cout<<"[sparseMatirx] mMatrixColSize = "<<mMatrixColSize<<std::endl;
    std::cout<<"[sparseMatirx] mNumOfNonZeros = "<<mNumOfNonZeros<<std::endl;

}

sparseMatrix::~sparseMatrix()
{
    // memory deallocation
    if ( mSparseMatrixRepTable != NULL)
    {
        deAllocate();
    }
}


void sparseMatrix::allocate(const  unsigned int numOfNonzeros_)
{
    // memory allocation and init
    // -- allocating memory by considering the maximum case of the nonzeros in the sparse matrix.

    mSparseMatrixRepTable = new short*[mTableSize];
    
    for (int i = 0 ; i < mTableSize ; i++)
    {
        mSparseMatrixRepTable[i] = new short[numOfNonzeros_];
        memset(mSparseMatrixRepTable[i],0,sizeof(short)*numOfNonzeros_);
    }
    std::cout<<"[sparseMatrix] Allocate [short: 3 x "<<numOfNonzeros_<<"] memory for matrix storage"<<std::endl;
    //std::cout<<"--- mSparseMatrixRepTable="<<mSparseMatrixRepTable<<std::endl;


}

void sparseMatrix::deAllocate(void)
{
    for (int i =0 ; i < mTableSize ; i++)
    {
        delete [] mSparseMatrixRepTable[i];
    }
    
    delete [] mSparseMatrixRepTable;
    mSparseMatrixRepTable = NULL;

    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"[sparseMatrix] deAllocate memory"<<std::endl;
    //std::cout<<"--- mSparseMatrixRepTable="<<mSparseMatrixRepTable<<std::endl;

}


void sparseMatrix::readMatrix(const char* inputfilename)
{
    short** tempSparseMatrixRepTable = NULL;
    
    tempSparseMatrixRepTable = new short*[mTableSize];
    
    for (int i = 0 ; i < mTableSize ; i++)
    {
        tempSparseMatrixRepTable[i] = new short[mMatrixColSize*mMatrixRowSize];
        memset(tempSparseMatrixRepTable[i],0,sizeof(short)*mMatrixColSize*mMatrixRowSize);
    }
    
    
    std::ifstream inputfile;
    short tempReadValue = 0;
    
    inputfile.open(inputfilename);
    unsigned int nonZerosCnt = 0;

    std::cout<<"[sparseMatrix] File read from "<<inputfilename<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"[sparseMatrix] Storing the sparse matrix via the triple representation method"<<std::endl;
    std::cout<<"Imported Matrix ="<<std::endl;
    for (int rowIndex = 0 ; rowIndex < mMatrixRowSize ; rowIndex++)
    {
        //std::cout<<"------- "<<rowIndex<<"-th row"<<" ----------"<<std::endl;
        for (int colIndex = 0 ; colIndex < mMatrixColSize ; colIndex++)
        {
            inputfile >> tempReadValue;
            //std::cout << "[sparseMatrix] tempReadValue = " <<  tempReadValue << std::endl;
            std::cout<<tempReadValue<<",";
            if (tempReadValue != 0)
            {
                tempSparseMatrixRepTable[0][nonZerosCnt] = rowIndex;
                tempSparseMatrixRepTable[1][nonZerosCnt] = colIndex;
                tempSparseMatrixRepTable[2][nonZerosCnt] = tempReadValue;
                nonZerosCnt++;
            }
        }
        std::cout<<std::endl;
    }
    inputfile.close();
    
    mNumOfNonZeros = nonZerosCnt;
    // memcpy and free the temporal memory
    allocate(mNumOfNonZeros);
    
    for (int i=0;i<mTableSize;i++)
    {
        memcpy(mSparseMatrixRepTable[i],tempSparseMatrixRepTable[i],sizeof(short)*mNumOfNonZeros);
        delete [] tempSparseMatrixRepTable[i];
    }
    
    delete [] tempSparseMatrixRepTable;
    tempSparseMatrixRepTable =NULL;
    
    
    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"--- Total matrix size: "<<mMatrixRowSize<<" X "<< mMatrixColSize<<" = "<<mMatrixRowSize*mMatrixColSize<<std::endl;
    std::cout<<"--- Total number of nonzeros = "<<nonZerosCnt<<std::endl;
    std::cout<<"--- Matrix sparsity = "<< (float)nonZerosCnt / (float)(mMatrixRowSize*mMatrixColSize) * 100.0 <<" %"<<std::endl;
    std::cout<<"--- Total number of memory slots for triple representation = 3 X "<<nonZerosCnt<<" = "<<nonZerosCnt*mTableSize<<std::endl;
    
}


void sparseMatrix::showMatrix()
{
    std::cout<<"------------------------------"<<std::endl;
    std::cout<<"[sparseMatrix] The triple representation of the sparse matrix"<<std::endl;
    std::cout<<"(rowIndex,colIndex), nonzerovalue"<<std::endl;

    
    for (int elemIndex = 0 ; elemIndex < mNumOfNonZeros ; elemIndex ++)
    {
        showElemInMatrix(elemIndex);
    }
    
}

void sparseMatrix::showElemInMatrix(const int nonzeroIndex)
{
    std::cout<<"("<<mSparseMatrixRepTable[0][nonzeroIndex]<<","<<mSparseMatrixRepTable[1][nonzeroIndex]<<"),"<<" "<<mSparseMatrixRepTable[2][nonzeroIndex]<<std::endl;
}

short sparseMatrix::getElemValue(const unsigned int rowIndex, const unsigned int colIndex)
{
    int firstElemRowIndex = isNonZeroInRow(rowIndex);
    int elemIndex = -1;
    if (firstElemRowIndex < 0)
    {
      //  std::cout<<"-- error -- The element index is invalid in the matrix"<<std::endl;
        return INVAILD_VALUE;
    }
    
    for (int i = firstElemRowIndex ; i < mNumOfNonZeros ; i++)
    {
        if (mSparseMatrixRepTable[1][i] == colIndex && mSparseMatrixRepTable[0][i] == rowIndex)
        {
            elemIndex = i;
            break;
        }
    }
    
    if (elemIndex < 0)
    {
      //  std::cout<<"-- error -- The element index is invalid in the matrix"<<std::endl;
        return INVAILD_VALUE;
    }
    else
    {
       // showElemInMatrix(elemIndex);
        return mSparseMatrixRepTable[2][elemIndex];
    }

}



int sparseMatrix::isNonZeroInRow(const unsigned int rowIndex)
{
    int firstElemIndex = -1;
    
    for (unsigned int i = 0 ; i < mNumOfNonZeros ; i++)
    {
        if (mSparseMatrixRepTable[0][i] == rowIndex)
        {
            firstElemIndex = i;
            break;
        }
    }
    
    return firstElemIndex;

}


void sparseMatrix::setMatrix(short** table,const unsigned int rowSize_, const unsigned int colSize_, const unsigned int nonZeroNum_)
{
    mMatrixColSize = colSize_;
    mMatrixRowSize = rowSize_;
    mNumOfNonZeros = nonZeroNum_;
    
    allocate(mNumOfNonZeros);
    
    std::cout<<"[sparseMatrix] mMatrixRowSize = "<<mMatrixRowSize<<std::endl;
    std::cout<<"[sparseMatirx] mMatrixColSize = "<<mMatrixColSize<<std::endl;
    std::cout<<"[sparseMatirx] mNumOfNonZeros = "<<mNumOfNonZeros<<std::endl;
    
    for (int i = 0 ; i < mTableSize ; i++)
    {
        memcpy(mSparseMatrixRepTable[i], table[i], sizeof(short)*mNumOfNonZeros);
    }
    
    
    showMatrix();
    
}


/* sparse matrix multiplicatio:  A*B = C */
bool mulSparseMatrix(sparseMatrix* Ain, sparseMatrix* Bin, sparseMatrix* Cout)
{
    
    //1 feasibility check!
    if (Ain->getColSize() != Bin->getRowSize())
    {
        std::cout<<"[sparseMatrix] Invalid matrix muliplication!"<<std::endl;
        return false;
    }
    
    unsigned int colSizeCout = Bin->getColSize();
    unsigned int rowSizeCout = Ain->getRowSize();
//    Ain->showMatrix();
//    Bin->showMatrix();
    
    const int tableSize = 3;
    short** tempTableForCout = NULL;
    
    // temporal memory allocation
    tempTableForCout = new short*[tableSize];
    for (int i = 0 ; i < tableSize ; i++)
    {
        tempTableForCout[i] = new short[colSizeCout*rowSizeCout];
        memset(tempTableForCout[i],0,sizeof(short)*colSizeCout*rowSizeCout);
    }
    
    // matrix multiplication
    int nonZeroCntForCout = 0;
    for (unsigned int i = 0 ; i < rowSizeCout; i++)
    {
        int firstNonZeroIndexInARow = -1;
        
        // check whether the i-th row of A contains nonzeros.
        firstNonZeroIndexInARow = Ain->isNonZeroInRow(i);
      //  std::cout<<"-----------"<< i <<"-th row-----"<<std::endl;
      //  std::cout<<"firstNonZeroIndexInARow = "<<firstNonZeroIndexInARow<<std::endl;
        
        if (firstNonZeroIndexInARow > -1)
        {
            for(unsigned int k = 0 ; k < colSizeCout; k++)
            {
              //  std::cout<<"----------- for C("<< i <<","<<k<<")"<<std::endl;

                unsigned int nonZeroIndexOfA = firstNonZeroIndexInARow;
                short elemCout = 0;
                short tempElemOfB = 0;
                
                // loop for inner product of vectors
                while(Ain->getRowIndex(nonZeroIndexOfA) == i)
                {
                   // std::cout<<"nonZeroIndexOfA ="<<nonZeroIndexOfA<<std::endl;
                    //std::cout<<"Ain->getRowIndex(nonZeroIndexOfA) = "<<Ain->getRowIndex(nonZeroIndexOfA)<<std::endl;

                    unsigned int colIndexOfA = Ain->getColIndex(nonZeroIndexOfA);
                    
                    tempElemOfB  = Bin->getElemValue(colIndexOfA,k);
                    
                  //  std::cout<<"colIndexOfA = "<<colIndexOfA<<std::endl;

                  //  std::cout<<"tempElemOfB = "<<tempElemOfB<<std::endl;
                 //   std::cout<<"tempElemOfA = "<<Ain->getElemValue(i, colIndexOfA) <<std::endl;
                    
                    //
                    if (tempElemOfB != INVAILD_VALUE)
                        elemCout = elemCout + Ain->getElemValue(i, colIndexOfA) * tempElemOfB;
                    nonZeroIndexOfA++;
                }
                
                if (elemCout != 0)
                {
                    tempTableForCout[0][nonZeroCntForCout] = i;
                    tempTableForCout[1][nonZeroCntForCout] = k;
                    tempTableForCout[2][nonZeroCntForCout] = elemCout;
                    nonZeroCntForCout++;
                }
            }
        }

    }
    
    Cout->setMatrix(tempTableForCout,rowSizeCout,colSizeCout,nonZeroCntForCout);
    
    
    // memory deallocation
    for (int i = 0 ; i <tableSize; i++)
    {
        delete [] tempTableForCout[i];
    }
    delete [] tempTableForCout;
    tempTableForCout = NULL;
    
    return true;
}
