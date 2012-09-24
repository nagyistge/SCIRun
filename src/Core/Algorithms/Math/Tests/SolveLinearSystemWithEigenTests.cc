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

#include <fstream>
#include <Core/Algorithms/Math/SolveLinearSystemWithEigen.h>
#include <Core/Datatypes/DenseMatrix.h>
#include <Core/Datatypes/MatrixComparison.h>
#include <Core/Datatypes/MatrixIO.h>

using namespace SCIRun::Core::Datatypes;
using namespace SCIRun::Core::Algorithms::Math;

//namespace
//{
//  DenseMatrixHandle matrix1a()
//  {
//    DenseMatrixHandle m(new DenseMatrix(3, 3));
//    for (int i = 0; i < m->rows(); ++ i)
//      for (int j = 0; j < m->cols(); ++ j)
//        (*m)(i, j) = (3.0 * i*i - 2*j*j + 2 + (i == j ? 1 : 0))/1;
//    return m;
//  }
//}

TEST(SolveLinearSystemWithEigenAlgorithmTests, CanSolveBasicSmallDenseSystem)
{
  DenseMatrix m1(3,3);
  m1 << 1,2,3, 
    -3,-2,-1,
    0,0,1;
  std::cout << m1 << std::endl;

  auto det = m1.determinant();
  std::cout << det << std::endl;

  auto inv = m1.inverse();
  std::cout << inv << std::endl;

  EXPECT_TRUE(false);
}
