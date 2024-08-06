#include <gtest/gtest.h>

#include <cmath>

#include "../s21_matrix_oop.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

bool almost_equal(double a, double b) { return std::fabs(a - b) < 1E-7; }

bool is_matrix_equal(S21Matrix &m, double reference[][4]) {
  double **m_raw = m.S21Matrix::GetMatrix();
  bool result = true;

  for (long i = 0; i < m.GetRows() && !result; ++i) {
    for (long j = 0; j < m.GetCols() && !result; ++j)
      if (!almost_equal(m_raw[i][j], reference[i][j])) {
        result = false;
      }
  }

  return result;
}
bool is_matrix_equal(S21Matrix &m, double reference[][3]) {
  double **m_raw = m.S21Matrix::GetMatrix();
  bool result = true;

  for (long i = 0; i < m.GetRows() && !result; ++i) {
    for (long j = 0; j < m.GetCols() && !result; ++j)
      if (!almost_equal(m_raw[i][j], reference[i][j])) {
        result = false;
      }
  }

  return result;
}

bool is_matrix_equal(S21Matrix &m, double reference[][2]) {
  double **m_raw = m.S21Matrix::GetMatrix();
  bool result = true;

  for (long i = 0; i < m.GetRows() && !result; ++i) {
    for (long j = 0; j < m.GetCols() && !result; ++j)
      if (!almost_equal(m_raw[i][j], reference[i][j])) {
        result = false;
      }
  }

  return result;
}

double identity_4_by_4[4][4] = {
    {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

double identity_2_by_3[2][3] = {{1, 0, 0}, {0, 1, 0}};

TEST(Constructor, Default) {
  S21Matrix m;

  EXPECT_EQ(m.GetRows(), 3);
  EXPECT_EQ(m.GetCols(), 3);

  EXPECT_TRUE(is_matrix_equal(m, identity_4_by_4));
}

TEST(Constructor, RowsCols) {
  S21Matrix m(2, 3);

  EXPECT_EQ(m.GetRows(), 2);
  EXPECT_EQ(m.GetCols(), 3);

  EXPECT_TRUE(is_matrix_equal(m, identity_2_by_3));
}

TEST(Constructor, PreAllocatedMatrix) {
  double m_raw[4][4]{
      {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  S21Matrix m(4, 4);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) {
      m[i][j] = m_raw[i][j];
    }

  EXPECT_EQ(m.GetRows(), 4);
  EXPECT_EQ(m.GetCols(), 4);

  EXPECT_TRUE(is_matrix_equal(m, m_raw));
}

TEST(Constructor, Move) {
  S21Matrix m1(2, 3);
  S21Matrix m2 = m1;
  S21Matrix m3(std::move(m1));

  EXPECT_EQ(m1.S21Matrix::GetMatrix(), nullptr);
  EXPECT_NE(m2.S21Matrix::GetMatrix(), m3.S21Matrix::GetMatrix());

  EXPECT_EQ(m2.GetRows(), 2);
  EXPECT_EQ(m2.GetCols(), 3);

  EXPECT_EQ(m3.GetRows(), 2);
  EXPECT_EQ(m3.GetCols(), 3);
}

TEST(ConstructorTest, DefaultConstructor) {
  S21Matrix A;
  ASSERT_EQ(3, A.GetRows());
  ASSERT_EQ(3, A.GetCols());
  ASSERT_EQ(0, A[0][0]);
}

TEST(ConstructorTest, ParameterizedConstructor1) {
  S21Matrix A(1, 1);
  ASSERT_EQ(1, A.GetRows());
  ASSERT_EQ(1, A.GetCols());
  ASSERT_EQ(0, A[0][0]);
}

TEST(ConstructorTest, ParameterizedConstructor2) {
  S21Matrix A(2, 4);
  ASSERT_EQ(2, A.GetRows());
  ASSERT_EQ(4, A.GetCols());
  ASSERT_EQ(0, A[0][0]);
  ASSERT_EQ(0, A[0][1]);
  ASSERT_EQ(0, A[0][2]);
  ASSERT_EQ(0, A[0][3]);
  ASSERT_EQ(0, A[1][0]);
  ASSERT_EQ(0, A[1][1]);
  ASSERT_EQ(0, A[1][2]);
  ASSERT_EQ(0, A[1][3]);
}

TEST(ConstructorTest, ParameterizedConstructorInvalid) {
  ASSERT_THROW(S21Matrix A(0, 4), std::exception);
}

TEST(ConstructorTest, CopyConstructor) {
  S21Matrix B(2, 4);
  for (int i = 0; i < B.GetRows(); ++i)
    for (int j = 0; j < B.GetCols(); ++j) B[i][j] = i + j;
  S21Matrix A(B);
  ASSERT_EQ(true, A.EqMatrix(B));
}

TEST(ConstructorTest, MoveConstructor) {
  S21Matrix B(2, 4);
  for (int i = 0; i < B.GetRows(); ++i)
    for (int j = 0; j < B.GetCols(); ++j) B[i][j] = i + j;
  S21Matrix A(std::move(B));

  ASSERT_EQ(2, A.GetRows());
  ASSERT_EQ(4, A.GetCols());
  ASSERT_EQ(0, A[0][0]);
  ASSERT_EQ(1, A[0][1]);
  ASSERT_EQ(2, A[0][2]);
  ASSERT_EQ(3, A[0][3]);
  ASSERT_EQ(1, A[1][0]);
  ASSERT_EQ(2, A[1][1]);
  ASSERT_EQ(3, A[1][2]);
  ASSERT_EQ(4, A[1][3]);
  ASSERT_THROW(B[0], std::exception);
}

TEST(Function, SumMatrix) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 3);

  m1.SumMatrix(m2);
  double reference[2][3] = {{2, 0, 0}, {0, 2, 0}};
  EXPECT_TRUE(is_matrix_equal(m1, reference));

  S21Matrix m3(3, 3);
  EXPECT_THROW(m1.SumMatrix(m3), std::exception);
}

TEST(SumMatrixTest, SumMatrixCorrect) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  B[0][0] = 5;
  B[0][1] = 6;
  B[1][0] = 7;
  B[1][1] = 8;

  A.SumMatrix(B);

  ASSERT_EQ(A[0][0], 6.0);
  ASSERT_EQ(A[0][1], 8.0);
  ASSERT_EQ(A[1][0], 10.0);
  ASSERT_EQ(A[1][1], 12.0);
}

TEST(SumMatrixTest, SumMatrixDifferentSizes) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);

  ASSERT_THROW(A.SumMatrix(B), std::exception);
}

TEST(Function, SubMatrix) {
  S21Matrix m1(2, 3);
  S21Matrix m2(2, 3);

  m1.SubMatrix(m2);
  double reference[2][3] = {{0, 0, 0}, {0, 0, 0}};
  EXPECT_TRUE(is_matrix_equal(m1, reference));

  S21Matrix m3(3, 3);
  EXPECT_THROW(m1.SubMatrix(m3), std::exception);
}
TEST(SubMatrixTest, SubMatrixCorrect) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  B[0][0] = 5;
  B[0][1] = 6;
  B[1][0] = 7;
  B[1][1] = 8;

  A.SubMatrix(B);

  ASSERT_EQ(A[0][0], -4.0);
  ASSERT_EQ(A[0][1], -4.0);
  ASSERT_EQ(A[1][0], -4.0);
  ASSERT_EQ(A[1][1], -4.0);
}

TEST(SubMatrixTest, SubMatrixDifferentSizes) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);

  ASSERT_THROW(A.SubMatrix(B), std::exception);
}

TEST(Function, MulNumber) {
  S21Matrix m(2, 3);

  m.MulNumber(42);
  double reference[2][3] = {{42, 0, 0}, {0, 42, 0}};
  EXPECT_TRUE(is_matrix_equal(m, reference));
}
TEST(MulNumberTest, MulNumberCorrect) {
  S21Matrix A(2, 2);

  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  double num = 2;

  A.MulNumber(num);

  ASSERT_EQ(A[0][0], 2);
  ASSERT_EQ(A[0][1], 4);
  ASSERT_EQ(A[1][0], 6);
  ASSERT_EQ(A[1][1], 8);
}

TEST(MulNumberTest, MulNumberZero) {
  S21Matrix A(2, 2);

  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  double num = 0;

  A.MulNumber(num);

  ASSERT_EQ(A[0][0], 0);
  ASSERT_EQ(A[0][1], 0);
  ASSERT_EQ(A[1][0], 0);
  ASSERT_EQ(A[1][1], 0);
}

TEST(MulMatrixTest, MulMatrixCorrect) {
  S21Matrix A(2, 4);
  S21Matrix B(4, 1);

  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 3;
  A[0][3] = 4;
  A[1][0] = 5;
  A[1][1] = 6;
  A[1][2] = 7;
  A[1][3] = 8;

  B[0][0] = 9;
  B[1][0] = 10;
  B[2][0] = 11;
  B[3][0] = 12;

  A.MulMatrix(B);

  ASSERT_EQ(A[0][0], 110.0);
  ASSERT_EQ(A[1][0], 278.0);
}

TEST(MulMatrixTest, MulMatrixIncorrectSizes) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);

  ASSERT_THROW(A.MulMatrix(B), std::exception);
}

TEST(Function, MulMatrix) {
  double m1_raw[2][3]{{2, 3, 4}, {5, 6, 7}};
  double m2_raw[3][2]{{3, 7}, {11, 13}, {23, 0}};

  S21Matrix m1(2, 3);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) m1[i][j] = m1_raw[i][j];

  S21Matrix m2(3, 2);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 2; j++) m2[i][j] = m2_raw[i][j];

  m1.MulMatrix(m2);
  EXPECT_EQ(m1.GetRows(), 2);
  EXPECT_EQ(m1.GetCols(), 2);

  double reference[2][2] = {{131, 53}, {242, 113}};
  EXPECT_TRUE(is_matrix_equal(m1, reference));

  EXPECT_THROW(m1.MulMatrix(m2), std::exception);
}

TEST(Function, Transpose) {
  double m_raw[2][3]{{2, 3, 4}, {5, 6, 7}};

  S21Matrix m(2, 3);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 3; j++) m[i][j] = m_raw[i][j];

  S21Matrix transposed = m.Transpose();
  EXPECT_EQ(transposed.GetRows(), 3);
  EXPECT_EQ(transposed.GetCols(), 2);

  double reference[3][2] = {{2, 5}, {3, 6}, {4, 7}};
  EXPECT_TRUE(is_matrix_equal(transposed, reference));
}
TEST(TransposeTest, TransposeCorrect) {
  S21Matrix A(2, 3);

  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 3;
  A[1][0] = 4;
  A[1][1] = 5;
  A[1][2] = 6;

  S21Matrix B = A.Transpose();

  ASSERT_EQ(B.GetRows(), 3);
  ASSERT_EQ(B.GetCols(), 2);

  ASSERT_EQ(B[0][0], 1);
  ASSERT_EQ(B[0][1], 4);
  ASSERT_EQ(B[1][0], 2);
  ASSERT_EQ(B[1][1], 5);
  ASSERT_EQ(B[2][0], 3);
  ASSERT_EQ(B[2][1], 6);
}

TEST(Function, Determinant) {
  double **m_raw = new double *[3];
  m_raw[0] = new double[3]{1, 2, -3};
  m_raw[1] = new double[3]{4, -5, 6};
  m_raw[2] = new double[3]{7, 8, -9};

  S21Matrix m(3, 3);
  SetMatrix(m, m_raw);
  for (int i = 0; i < 3; i++) {
    delete[] m_raw[i];
  }
  delete[] m_raw;

  EXPECT_TRUE(almost_equal(m.Determinant(), -48));

  m.SetRows(2);
  EXPECT_THROW(m.Determinant(), std::exception);
}

TEST(DeterminantTest, Square1x1) {
  S21Matrix A(1, 1);
  A[0][0] = 2;
  double determinant = A.Determinant();
  ASSERT_EQ(determinant, 2);
}

TEST(DeterminantTest, NonSquare) {
  S21Matrix A(2, 3);
  ASSERT_THROW(A.Determinant(), std::exception);
}

TEST(DeterminantTest, Square2x2) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;
  double determinant = A.Determinant();
  ASSERT_NEAR(-2, determinant, 1E-7);
}

TEST(DeterminantTest, Square3x3) {
  S21Matrix A(3, 3);
  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 3;
  A[1][0] = 4;
  A[1][1] = 5;
  A[1][2] = 6;
  A[2][0] = 7;
  A[2][1] = 8;
  A[2][2] = 9;
  double determinant = A.Determinant();
  ASSERT_EQ(determinant, 0);
}

TEST(DeterminantTest, Square3x3NotNull) {
  S21Matrix A(3, 3);
  A[0][0] = 2;
  A[0][1] = 4;
  A[0][2] = -1;
  A[1][0] = 7;
  A[1][1] = 3;
  A[1][2] = 1;
  A[2][0] = -3;
  A[2][1] = 5;
  A[2][2] = 6;
  double determinant = A.Determinant();
  ASSERT_NEAR(-198, determinant, 1E-7);
}

TEST(DeterminantTest, Square3x3Swap) {
  S21Matrix A(3, 3);
  A[0][0] = 0;
  A[0][1] = 4;
  A[0][2] = -1;
  A[1][0] = 7;
  A[1][1] = 3;
  A[1][2] = 1;
  A[2][0] = -3;
  A[2][1] = 5;
  A[2][2] = 6;
  double determinant = A.Determinant();
  ASSERT_NEAR(-224, determinant, 1E-7);
}

TEST(DeterminantTest, Square3x3Swap2) {
  S21Matrix A(3, 3);
  A[0][0] = 2;
  A[0][1] = 4;
  A[0][2] = -1;
  A[1][0] = 7;
  A[1][1] = 14;
  A[1][2] = 1;
  A[2][0] = -3;
  A[2][1] = 5;
  A[2][2] = 6;
  double determinant = A.Determinant();
  ASSERT_NEAR(-99, determinant, 1E-7);
}

TEST(DeterminantTest, Square3x3SwapNull) {
  S21Matrix A(3, 3);
  A[0][0] = 2;
  A[0][1] = 4;
  A[0][2] = -1;
  A[1][0] = 7;
  A[1][1] = 14;
  A[1][2] = 1;
  A[2][0] = -3;
  A[2][1] = -6;
  A[2][2] = 6;
  double determinant = A.Determinant();
  ASSERT_EQ(0, determinant);
}

TEST(Function, CalcComplements) {
  double m_raw[3][3]{{2, 2, 1}, {7, 8, 2}, {5, 3, 2}};

  S21Matrix m(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) m[i][j] = m_raw[i][j];

  S21Matrix complements = m.S21Matrix::CalcComplements();
  double reference[3][3] = {{10, -4, -19}, {-1, -1, 4}, {-4, 3, 2}};
  EXPECT_TRUE(is_matrix_equal(complements, reference));

  m.SetRows(2);
  EXPECT_THROW(m.CalcComplements(), std::exception);
}

TEST(CalcComplementsTest, Square1x1) {
  S21Matrix A(1, 1);
  A[0][0] = 2;

  S21Matrix complement = A.CalcComplements();

  ASSERT_EQ(complement.GetRows(), 1);
  ASSERT_EQ(complement.GetCols(), 1);

  ASSERT_EQ(complement[0][0], 1);
}

TEST(CalcComplementsTest, NonSquare) {
  S21Matrix A(2, 3);

  ASSERT_THROW(A.CalcComplements(), std::exception);
}

TEST(CalcComplementsTest, Square2x2) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix complement = A.CalcComplements();

  ASSERT_EQ(complement.GetRows(), 2);
  ASSERT_EQ(complement.GetCols(), 2);

  ASSERT_EQ(complement[0][0], 4);
  ASSERT_EQ(complement[0][1], -3);
  ASSERT_EQ(complement[1][0], -2);
  ASSERT_EQ(complement[1][1], 1);
}

TEST(EqMatrixTest, HandlesEqCase) {
  S21Matrix B(2, 4);
  for (int i = 0; i < B.GetRows(); ++i)
    for (int j = 0; j < B.GetCols(); ++j) B[i][j] = i + j;
  S21Matrix A(B);
  ASSERT_TRUE(A.EqMatrix(B));
}

TEST(EqMatrixTest, HandlesUneqCase) {
  S21Matrix B(2, 4);
  S21Matrix A(2, 4);
  for (int i = 0; i < B.GetRows(); ++i)
    for (int j = 0; j < B.GetCols(); ++j) B[i][j] = i + j;
  ASSERT_FALSE(A.EqMatrix(B));
}

TEST(EqMatrixTest, HandlesDifferentSizes) {
  S21Matrix B(2, 4);
  S21Matrix A(2, 2);
  ASSERT_FALSE(A.EqMatrix(B));
}

TEST(InverseMatrixTest, Square1x1) {
  S21Matrix A(1, 1);
  A[0][0] = 2;

  S21Matrix result = A.InverseMatrix();

  ASSERT_EQ(result.GetRows(), 1);
  ASSERT_EQ(result.GetCols(), 1);
  ASSERT_NEAR(result[0][0], 0.5, 1e-7);
}

TEST(InverseMatrixTest, Square2x2) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 3;
  A[1][1] = 4;

  S21Matrix result = A.InverseMatrix();

  ASSERT_EQ(result.GetRows(), 2);
  ASSERT_EQ(result.GetCols(), 2);
  ASSERT_NEAR(result[0][0], -2, 1e-7);
  ASSERT_NEAR(result[0][1], 1, 1e-7);
  ASSERT_NEAR(result[1][0], 1.5, 1e-7);
  ASSERT_NEAR(result[1][1], -0.5, 1e-7);
}

TEST(InverseMatrixTest, Square3x3Eq) {
  S21Matrix A(3, 3);
  A[0][0] = 1;
  A[0][1] = 0;
  A[0][2] = 0;
  A[1][0] = 0;
  A[1][1] = 1;
  A[1][2] = 0;
  A[2][0] = 0;
  A[2][1] = 0;
  A[2][2] = 1;

  S21Matrix result = A.InverseMatrix();

  ASSERT_EQ(result.GetRows(), 3);
  ASSERT_EQ(result.GetCols(), 3);
  ASSERT_NEAR(result[0][0], 1, 1e-7);
  ASSERT_NEAR(result[0][1], 0, 1e-7);
  ASSERT_NEAR(result[0][2], 0, 1e-7);
  ASSERT_NEAR(result[1][0], 0, 1e-7);
  ASSERT_NEAR(result[1][1], 1, 1e-7);
  ASSERT_NEAR(result[1][2], 0, 1e-7);
  ASSERT_NEAR(result[2][0], 0, 1e-7);
  ASSERT_NEAR(result[2][1], 0, 1e-7);
  ASSERT_NEAR(result[2][2], 1, 1e-7);
}

TEST(InverseMatrixTest, SingularMatrix) {
  S21Matrix A(2, 2);
  A[0][0] = 1;
  A[0][1] = 2;
  A[1][0] = 2;
  A[1][1] = 4;

  ASSERT_THROW(A.InverseMatrix(), std::exception);
}

TEST(InverseMatrixTest, NonSquareMatrix) {
  S21Matrix A(2, 3);
  A[0][0] = 1;
  A[0][1] = 2;
  A[0][2] = 3;
  A[1][0] = 4;
  A[1][1] = 5;
  A[1][2] = 6;

  ASSERT_THROW(A.InverseMatrix(), std::exception);
}

TEST(InverseMatrixTest, Square3x3) {
  S21Matrix A(3, 3);
  A[0][0] = 2;
  A[0][1] = 4;
  A[0][2] = -1;
  A[1][0] = 7;
  A[1][1] = 3;
  A[1][2] = 1;
  A[2][0] = -3;
  A[2][1] = 5;
  A[2][2] = 6;

  S21Matrix result = A.InverseMatrix();

  ASSERT_EQ(result.GetRows(), 3);
  ASSERT_EQ(result.GetCols(), 3);
  ASSERT_NEAR(result[0][0], -13.0 / 198, 1e-7);
  ASSERT_NEAR(result[0][1], 29.0 / 198, 1e-7);
  ASSERT_NEAR(result[0][2], -7.0 / 198, 1e-7);
  ASSERT_NEAR(result[1][0], 5.0 / 22, 1e-7);
  ASSERT_NEAR(result[1][1], -1.0 / 22, 1e-7);
  ASSERT_NEAR(result[1][2], 1.0 / 22, 1e-7);
  ASSERT_NEAR(result[2][0], -2.0 / 9, 1e-7);
  ASSERT_NEAR(result[2][1], 1.0 / 9, 1e-7);
  ASSERT_NEAR(result[2][2], 1.0 / 9, 1e-7);
}

TEST(Function, Inverse) {
  double m_raw[3][3]{{2, 2, 1}, {7, 8, 2}, {5, 3, 2}};

  S21Matrix m1(3, 3);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) m1[i][j] = m_raw[i][j];

  S21Matrix inverse = m1.S21Matrix::InverseMatrix();
  double reference[3][3] = {{-10.0 / 7, 1.0 / 7, 4.0 / 7},
                            {4.0 / 7, 1.0 / 7, -3.0 / 7},
                            {19.0 / 7, -4.0 / 7, -2.0 / 7}};
  EXPECT_TRUE(is_matrix_equal(inverse, reference));

  m1.SetRows(2);
  EXPECT_THROW(m1.InverseMatrix(), std::exception);

  S21Matrix m2(3, 3);
  EXPECT_THROW(m1.InverseMatrix(), std::exception);
}

TEST(Operator, Plus) {
  double m_raw1[2][2]{{1, 2}, {3, 4}};
  double m_raw2[2][2]{{41, 42}, {43, 44}};

  S21Matrix m1(2, 2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) m1[i][j] = m_raw1[i][j];
  S21Matrix m2(2, 2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) m2[i][j] = m_raw2[i][j];

  S21Matrix m3 = m1 + m2;
  double reference[2][2] = {{42, 44}, {46, 48}};
  EXPECT_TRUE(is_matrix_equal(m3, reference));

  m1 += m2;
  EXPECT_TRUE(is_matrix_equal(m1, reference));

  m1.SetRows(3);
  EXPECT_THROW({ m1 += m2; }, std::exception);
  EXPECT_THROW({ S21Matrix m4 = m1 + m2; }, std::exception);
}

TEST(Operator, Minus) {
  double m_raw1[2][2]{{1, 2}, {3, 4}};
  double m_raw2[2][2]{{41, 42}, {43, 44}};

  S21Matrix m1(2, 2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) m1[i][j] = m_raw2[i][j];
  S21Matrix m2(2, 2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) m2[i][j] = m_raw1[i][j];

  S21Matrix m3 = m1 - m2;
  double reference[2][2] = {{40, 37}, {33, 29}};
  EXPECT_TRUE(is_matrix_equal(m3, reference));

  m1 -= m2;
  EXPECT_TRUE(is_matrix_equal(m1, reference));

  m1.SetRows(3);
  EXPECT_THROW({ m1 -= m2; }, std::exception);
  EXPECT_THROW({ S21Matrix m4 = m1 - m2; }, std::exception);
}

TEST(Operator, MultiplyByNumber) {
  double m_raw[2][2]{{1, -2}, {3, -4}};

  S21Matrix m1(2, 2);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) m1[i][j] = m_raw[i][j];

  S21Matrix m2 = m1 * 2;
  double reference[2][2] = {{2, -4}, {6, -8}};
  EXPECT_TRUE(is_matrix_equal(m2, reference));

  m1 *= 2;
  EXPECT_TRUE(is_matrix_equal(m1, reference));
}

TEST(Operator, MultiplyByMatrix) {
  double **m_raw1 = new double *[2];
  m_raw1[0] = new double[2]{1, 2};
  m_raw1[1] = new double[2]{3, 4};

  double **m_raw2 = new double *[2];
  m_raw2[0] = new double[2]{-3, 4};
  m_raw2[1] = new double[2]{-5, 6};

  S21Matrix m1(2, 2);
  SetMatrix(m1, m_raw1);
  S21Matrix m2(2, 2);
  SetMatrix(m2, m_raw2);

  for (int i = 0; i < 2; i++) {
    delete[] m_raw1[i];
  }
  delete[] m_raw1;

  for (int i = 0; i < 2; i++) {
    delete[] m_raw2[i];
  }
  delete[] m_raw2;

  S21Matrix m3 = m1 * m2;
  double reference[2][2] = {{-13, 16}, {-29, 36}};
  EXPECT_TRUE(is_matrix_equal(m3, reference));

  m1 *= m2;
  EXPECT_TRUE(is_matrix_equal(m1, reference));

  m1.SetCols(3);
  EXPECT_THROW({ m1 *= m2; }, std::exception);
  EXPECT_THROW({ S21Matrix m4 = m1 * m2; }, std::exception);
}
TEST(Operator, Equal) {
  S21Matrix B(2, 4);
  S21Matrix A(2, 4);
  for (int i = 0; i < B.GetRows(); ++i)
    for (int j = 0; j < B.GetCols(); ++j) {
      B[i][j] = i + j;
      A[i][j] = i + j;
    }
  ASSERT_TRUE(A == B);
}

TEST(Operator, NotEqual) {
  S21Matrix B(2, 4);
  S21Matrix A(2, 2);
  ASSERT_TRUE(A != B);
}
