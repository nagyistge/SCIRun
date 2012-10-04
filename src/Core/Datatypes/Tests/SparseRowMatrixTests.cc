/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

#include <gtest/gtest.h>

#include <Core/Datatypes/DenseMatrix.h>
#include <Core/Datatypes/SparseRowMatrix.h>
#include <Core/Datatypes/MatrixIO.h>
#include <Core/Datatypes/MatrixComparison.h>

using namespace SCIRun::Core::Datatypes;
//using namespace TestUtils;

namespace
{
  SparseRowMatrix matrix1()
  {
    SparseRowMatrix m(3,4);
    m.insert(0,0) = 1;
    m.insert(1,2) = -2;
    m.insert(2,3) = 0.5;
    return m;
  }
}

#define PRINT_MATRIX(x) std::cout << #x << " = \n" << (x) << std::endl
#define PRINT_MATRIX_BASE(x) std::cout << #x << " = \n" << static_cast<const MatrixBase<double>&>((x)) << std::endl


TEST(SparseRowMatrixTest, CanCreateBasicMatrix)
{
  SparseRowMatrix m(matrix1());
  PRINT_MATRIX_BASE(m);
}

TEST(SparseRowMatrixTest, CanPrintInLegacyFormat)
{
  SparseRowMatrix m(matrix1());
  std::string legacy = matrix_to_string(0.5 * m);
  std::cout << legacy << std::endl;
  EXPECT_EQ("0.5 0 0 0 \n0 0 -1 0 \n0 0 0 0.25 \n", legacy);
}

TEST(SparseRowMatrixTest, CanDetermineSize)
{
  SparseRowMatrix m(matrix1());
  EXPECT_EQ(3, m.rows());
  EXPECT_EQ(4, m.cols());
}

TEST(SparseRowMatrixTest, CanCopyConstruct)
{
  SparseRowMatrix m(matrix1());
  SparseRowMatrix m2(m);
  EXPECT_EQ(m, m2);
  m.coeffRef(1,2) += 1;
  PRINT_MATRIX_BASE(m);
  PRINT_MATRIX_BASE(m2);
  EXPECT_NE(m, m2);
}

TEST(SparseRowMatrixTest, CanAssign)
{
  SparseRowMatrix m(matrix1());
  
  SparseRowMatrix m2;
  EXPECT_NE(m, m2);
  m2 = m;
  EXPECT_EQ(m, m2);
  m.coeffRef(1,2) += 1;
  EXPECT_NE(m, m2);
}

TEST(SparseRowMatrixUnaryOperationTests, CanNegate)
{
  SparseRowMatrix m(matrix1());

  PRINT_MATRIX_BASE(m);
  PRINT_MATRIX(-m);

  SparseRowMatrix n = - -m;
  EXPECT_EQ(m, n);
  //EXPECT_EQ(m + (-m), Zero);
  EXPECT_TRUE(false);
}

TEST(SparseRowMatrixUnaryOperationTests, CanScalarMultiply)
{
  SparseRowMatrix m(matrix1());

  PRINT_MATRIX_BASE(m);
  PRINT_MATRIX(2*m);
  PRINT_MATRIX(m*2);
  SparseRowMatrix x = 2*m;
  SparseRowMatrix y = m*2;
  EXPECT_EQ(x,y);
}

TEST(SparseRowMatrixUnaryOperationTests, CanTranspose)
{
  SparseRowMatrix m(matrix1());

  PRINT_MATRIX_BASE(m);
  PRINT_MATRIX(m.transpose());

  SparseRowMatrix mtt = m.transpose().transpose();
  EXPECT_EQ(m,mtt);
}

TEST(SparseRowMatrixBinaryOperationTests, CanMultiply)
{
  SparseRowMatrix m(matrix1());

  PRINT_MATRIX_BASE(m);
  PRINT_MATRIX(m * m.transpose());
  //EXPECT_EQ(Zero * m, Zero);
  EXPECT_TRUE(false);
}

TEST(SparseRowMatrixBinaryOperationTests, CanAdd)
{
  SparseRowMatrix m(matrix1());

  PRINT_MATRIX_BASE(m);
  PRINT_MATRIX(m + m);
  SparseRowMatrix m2a = m + m;
  SparseRowMatrix m2b = 2*m;
  EXPECT_EQ(m2a, m2b);
}

TEST(SparseRowMatrixBinaryOperationTests, CanSubtract)
{
  SparseRowMatrix m(matrix1());

  PRINT_MATRIX_BASE(m);
  PRINT_MATRIX(m - m);
  //EXPECT_EQ(m - m, Zero);
  EXPECT_TRUE(false);
}

//TODO: compare to v4.
//TEST(SparseRowMatrixBinaryOperationTests, WhatHappensWhenYouAddDifferentSizes)
//{
//  SparseRowMatrix sum = matrix1() + matrix1();
//  std::cout << sum.rows() << std::endl;
//  std::cout << sum.cols() << std::endl;
//  PRINT_MATRIX(sum);
//}
