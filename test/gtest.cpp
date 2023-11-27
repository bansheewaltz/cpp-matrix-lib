#include "gtest/gtest.h"

#include "s21_matrix_oop.hpp"

TEST(constructor, default_) {
  const S21Matrix m;
  EXPECT_EQ(0, m.get_cols());
  EXPECT_EQ(0, m.get_rows());
}

TEST(constructor, parametrized) {
  const int r = 13, c = 17;
  const S21Matrix m(r, c);
  EXPECT_EQ(r, m.get_rows());
  EXPECT_EQ(c, m.get_cols());
  ASSERT_EQ(m(0, 0), 0);
}

TEST(constructor, pThrow) { EXPECT_ANY_THROW(S21Matrix(0, 1)); }

TEST(constructor, copy) {
  const int rc = 13;
  const S21Matrix m(rc, rc);
  const S21Matrix copy(m);
  EXPECT_EQ(copy.get_cols(), rc);
  EXPECT_EQ(copy.get_rows(), rc);
}

TEST(constructor, move) {
  const int rc = 13;
  S21Matrix m(rc, rc);
  S21Matrix moved(std::move(m));
  EXPECT_EQ(m.get_cols(), 0);
  EXPECT_EQ(m.get_rows(), 0);
  EXPECT_EQ(moved.get_cols(), rc);
  EXPECT_EQ(moved.get_rows(), rc);
}

TEST(operatorOL, parentheses) {
  S21Matrix m(6, 9);
  EXPECT_EQ(m(0, 0), 0);

  m(0, 1) = 69;
  EXPECT_EQ(m(0, 1), 69);

  m(5, 8) = 69.420;
  EXPECT_EQ(m(5, 8), 69.420);
}

TEST(operatorOL, parenthesesThrow) {
  S21Matrix m(3, 5);
  EXPECT_ANY_THROW(m(5, 7) = 1);
}

TEST(operatorOL, squareBrackets) {
  S21Matrix m(6, 9);
  EXPECT_EQ(m[0][0], 0);

  const int v = 13;
  m[5][5] = v;
  EXPECT_EQ(m[5][5], v);

  const float fv = 123.123;
  m[5][8] = fv;
  EXPECT_EQ(m[5][8], fv);
}

TEST(operatorOL, squareBracketsThrow) {
  S21Matrix m(3, 3);
  EXPECT_ANY_THROW(m[5][7] = 1);
}

TEST(setter, rowsUp) {
  S21Matrix m(2, 2);
  m[1][1] = 6.9;

  m.set_rows(5);
  EXPECT_EQ(m.get_rows(), 5);
  EXPECT_EQ(m[1][1], 6.9);
}

TEST(setter, rowsDown) {
  S21Matrix m(2, 2);
  m[0][0] = 6.9;

  m.set_rows(1);
  EXPECT_EQ(m.get_rows(), 1);
  EXPECT_EQ(m[0][0], 6.9);
}

TEST(setter, zeroRows) {
  S21Matrix m;
  EXPECT_ANY_THROW(m.set_rows(0));
}

TEST(setter, colsUp) {
  S21Matrix m(2, 2);
  m[1][1] = 6.9;

  m.set_cols(5);
  EXPECT_EQ(m.get_cols(), 5);
  EXPECT_EQ(m[1][1], 6.9);
}

TEST(setter, colsDown) {
  S21Matrix m(2, 2);
  m[0][0] = 6.9;

  m.set_cols(1);
  EXPECT_EQ(m.get_cols(), 1);
  EXPECT_EQ(m[0][0], 6.9);
}

TEST(setter, zeroColsThrow) {
  S21Matrix m;
  EXPECT_ANY_THROW(m.set_cols(0));
}

TEST(operatorOL, equal) {
  S21Matrix m;
  S21Matrix x(3, 6);
  x(1, 2) = 3;
  x(2, 2) = 3;

  m = x;

  EXPECT_EQ(m.get_rows(), 3);
  EXPECT_EQ(m.get_cols(), 6);
  EXPECT_EQ(m(1, 2), 3);
  EXPECT_EQ(m(2, 2), 3);
}

TEST(operatorOL, equalSame) {
  const int r = 3, c = 5;
  S21Matrix m(3, 5);
  m(1, 2) = 1;

  m = m;

  EXPECT_EQ(m.get_rows(), r);
  EXPECT_EQ(m.get_cols(), c);
  EXPECT_EQ(m(1, 2), 1);
}

TEST(test_overload, equal_rvalue) {
  S21Matrix m(2, 2);
  S21Matrix n;
  n = std::move(m);
  EXPECT_EQ(n.get_cols(), 2);
  EXPECT_EQ(n.get_rows(), 2);
}

TEST(operatorOL, comparisonDefaultInit) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);
  ASSERT_TRUE(m == n);
}

TEST(operatorOL, comparisonInit) {
  S21Matrix m(3, 2);
  S21Matrix n;
  m[0][1] = 69;
  n = m;
  ASSERT_TRUE(m == n);
}

TEST(sumMatrix, case1) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SumMatrix(n);

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(sumMatrix, throw_) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(rows, cols + 1);

  EXPECT_ANY_THROW(m + n);
}

TEST(operatorOL, sum) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m + n;

  EXPECT_EQ(m(0, 0), 2);
  EXPECT_EQ(m(1, 1), 2);
}

TEST(operatorOL, eqSum) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m += m + n;

  EXPECT_EQ(m(0, 0), 3);
  EXPECT_EQ(m(1, 1), 3);
}

TEST(subMatrix, case1) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m.SubMatrix(n);

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(subMatrix, throw_) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(rows, cols + 1);

  EXPECT_ANY_THROW(m - n);
}

TEST(operatorOL, eqSub) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m -= n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(operatorOL, sub) {
  S21Matrix m(2, 2);
  S21Matrix n(2, 2);

  m(0, 0) = 1;
  n(0, 0) = 1;

  m(1, 1) = 1;
  n(1, 1) = 1;

  m = m - n;

  EXPECT_EQ(m(0, 0), 0);
  EXPECT_EQ(m(1, 1), 0);
}

TEST(mulMatrix, case1) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) n[i][j] = c++;

  m.MulMatrix(n);

  S21Matrix res(2, 2);
  res[0][0] = 58;
  res[0][1] = 64;
  res[1][0] = 139;
  res[1][1] = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(mulMatrix, throw_) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(rows, cols);

  EXPECT_ANY_THROW(m * n);
}

TEST(operatorOL, eqMul) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) n[i][j] = c++;

  m *= n;

  S21Matrix res(2, 2);
  res[0][0] = 58;
  res[0][1] = 64;
  res[1][0] = 139;
  res[1][1] = 154;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(operatorOL, eqMulNum) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m[i][j] = c++;

  m *= 2;

  S21Matrix res(2, 3);
  res[0][0] = 2;
  res[0][1] = 4;
  res[0][2] = 6;
  res[1][0] = 8;
  res[1][1] = 10;
  res[1][2] = 12;

  ASSERT_TRUE(m.EqMatrix(res));
}

TEST(operatorOL, mul) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix n(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) n[i][j] = c++;

  m = m * n;

  S21Matrix res(2, 2);
  res[0][0] = 58;
  res[0][1] = 64;
  res[1][0] = 139;
  res[1][1] = 154;

  ASSERT_TRUE(m == res);
}

TEST(operatorOL, mulNumMat) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m[i][j] = c++;

  m = 2 * m;

  S21Matrix exp(2, 3);
  exp[0][0] = 2;
  exp[0][1] = 4;
  exp[0][2] = 6;
  exp[1][0] = 8;
  exp[1][1] = 10;
  exp[1][2] = 12;

  ASSERT_TRUE(m == exp);
}

TEST(operatorOL, mulMatNum) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) m[i][j] = c++;

  m = m * 2;

  S21Matrix exp(2, 3);
  exp[0][0] = 2;
  exp[0][1] = 4;
  exp[0][2] = 6;
  exp[1][0] = 8;
  exp[1][1] = 10;
  exp[1][2] = 12;

  ASSERT_TRUE(m == exp);
}

TEST(transpose, simple) {
  const int rows = 2;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix exp(cols, rows);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++, c++) {
      m[i][j] = c;
      exp[j][i] = c;
    }

  m = m.Transpose();
  ASSERT_TRUE(m == exp);
}

TEST(determinant, throw_) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m.Determinant());
}

TEST(determiannt, equal0) {
  const int size = 5;
  S21Matrix m(5, 5);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m[i][j] = j;

  ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(determinant, d5x5) {
  const int size = 5;
  const S21Matrix m(size, size);

  m[0][1] = 6;
  m[0][2] = -2;
  m[0][3] = -1;
  m[0][4] = 5;
  m[1][3] = -9;
  m[1][4] = -7;
  m[2][1] = 15;
  m[2][2] = 35;
  m[3][1] = -1;
  m[3][2] = -11;
  m[3][3] = -2;
  m[3][4] = 1;
  m[4][0] = -2;
  m[4][1] = -2;
  m[4][2] = 3;
  m[4][4] = -2;

  const double res = m.Determinant();
  ASSERT_NEAR(res, 2480, S21Matrix::EPS);
}

TEST(determinant, d3x3) {
  const int size = 3;
  S21Matrix m(size, size);

  m[0][0] = 2;
  m[0][1] = 3;
  m[0][2] = 1;
  m[1][0] = 7;
  m[1][1] = 4;
  m[1][2] = 1;
  m[2][0] = 9;
  m[2][1] = -2;
  m[2][2] = 1;

  const double res = m.Determinant();
  ASSERT_NEAR(res, -32, S21Matrix::EPS);
}

TEST(determinant, d2x2) {
  const int size = 2;
  S21Matrix m(size, size);

  m[0][0] = -5;
  m[0][1] = -4;
  m[1][0] = -2;
  m[1][1] = -3;

  double res = m.Determinant();
  ASSERT_NEAR(res, 7, S21Matrix::EPS);
}

TEST(complements, c3x3) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix mat(rows, cols);
  S21Matrix exp(rows, cols);

  exp[0][0] = 0;
  exp[0][1] = 10;
  exp[0][2] = -20;
  exp[1][0] = 4;
  exp[1][1] = -14;
  exp[1][2] = 8;
  exp[2][0] = -8;
  exp[2][1] = -2;
  exp[2][2] = 4;

  mat[0][0] = 1;
  mat[0][1] = 2;
  mat[0][2] = 3;
  mat[1][0] = 0;
  mat[1][1] = 4;
  mat[1][2] = 2;
  mat[2][0] = 5;
  mat[2][1] = 2;
  mat[2][2] = 1;

  S21Matrix res = mat.CalcComplements();

  ASSERT_TRUE(res == exp);
}

TEST(complements, throw_) {
  S21Matrix m(3, 12);
  EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(complements, c3x3_1) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix exp(rows, cols);

  m[0][0] = 1.0;
  m[0][1] = 2.0;
  m[0][2] = 3.0;
  m[1][0] = 0.0;
  m[1][1] = 4.0;
  m[1][2] = 2.0;
  m[2][0] = 5.0;
  m[2][1] = 2.0;
  m[2][2] = 1.0;

  exp[0][0] = 0.0;
  exp[0][1] = 10.0;
  exp[0][2] = -20.0;
  exp[1][0] = 4.0;
  exp[1][1] = -14.0;
  exp[1][2] = 8.0;
  exp[2][0] = -8.0;
  exp[2][1] = -2.0;
  exp[2][2] = 4.0;

  S21Matrix res = m.CalcComplements();

  ASSERT_TRUE(res == exp);
}

TEST(complements, c3x3_2) {
  const int rows = 3;
  const int cols = 3;

  S21Matrix m(rows, cols);
  S21Matrix exp(rows, cols);

  m[0][0] = 1;
  m[0][1] = 2;
  m[0][2] = 3;
  m[1][1] = 4;
  m[1][2] = 2;
  m[2][0] = 5;
  m[2][1] = 2;
  m[2][2] = 1;

  exp[0][1] = 10;
  exp[0][2] = -20;
  exp[1][0] = 4;
  exp[1][1] = -14;
  exp[1][2] = 8;
  exp[2][0] = -8;
  exp[2][1] = -2;
  exp[2][2] = 4;

  S21Matrix res = m.CalcComplements();
  ASSERT_TRUE(res == exp);
}

TEST(inverse, inv3x3) {
  const int size = 3;
  const S21Matrix m(size, size);
  const S21Matrix exp(size, size);

  exp[0][0] = 44300.0 / 367429.0;
  exp[0][1] = -236300.0 / 367429.0;
  exp[0][2] = 200360.0 / 367429.0;
  exp[1][0] = 20600.0 / 367429.0;
  exp[1][1] = 56000.0 / 367429.0;
  exp[1][2] = -156483.0 / 367429.0;
  exp[2][0] = 30900.0 / 367429.0;
  exp[2][1] = 84000.0 / 367429.0;
  exp[2][2] = -51010.0 / 367429.0;

  m[0][0] = 2.8;
  m[0][1] = 1.3;
  m[0][2] = 7.01;
  m[1][0] = -1.03;
  m[1][1] = -2.3;
  m[1][2] = 3.01;
  m[2][0] = 0;
  m[2][1] = -3;
  m[2][2] = 2;

  ASSERT_TRUE(m.InverseMatrix() == exp);
}

TEST(inverse, i3x3_1) {
  const int size = 3;
  S21Matrix m(size, size);
  S21Matrix exp(size, size);
  exp[0][0] = 1.0;
  exp[0][1] = -1.0;
  exp[0][2] = 1.0;
  exp[1][0] = -38.0;
  exp[1][1] = 41.0;
  exp[1][2] = -34.0;
  exp[2][0] = 27.0;
  exp[2][1] = -29.0;
  exp[2][2] = 24.0;

  m[0][0] = 2.0;
  m[0][1] = 5.0;
  m[0][2] = 7.0;
  m[1][0] = 6.0;
  m[1][1] = 3.0;
  m[1][2] = 4.0;
  m[2][0] = 5.0;
  m[2][1] = -2.0;
  m[2][2] = -3.0;

  ASSERT_TRUE(m.InverseMatrix() == exp);
}

TEST(inverse, throw_) {
  S21Matrix m(2, 3);
  EXPECT_ANY_THROW(m.InverseMatrix());

  S21Matrix n(2, 2);
  EXPECT_ANY_THROW(n.InverseMatrix());
}

TEST(inverse, i1x1) {
  S21Matrix m(1, 1);
  m[0][0] = 69.420;
  double exp = 1 / m[0][0];
  double result = m.InverseMatrix()[0][0];
  ASSERT_NEAR(exp, result, 1e-06);
}

TEST(inverse, i3x3_2) {
  const int size = 3;
  S21Matrix m(size, size);
  S21Matrix exp(size, size);

  m[0][0] = 2;
  m[0][1] = 5;
  m[0][2] = 7;
  m[1][0] = 6;
  m[1][1] = 3;
  m[1][2] = 4;
  m[2][0] = 5;
  m[2][1] = -2;
  m[2][2] = -3;

  exp[0][0] = 1;
  exp[0][1] = -1;
  exp[0][2] = 1;
  exp[1][0] = -38;
  exp[1][1] = 41;
  exp[1][2] = -34;
  exp[2][0] = 27;
  exp[2][1] = -29;
  exp[2][2] = 24;
  ASSERT_TRUE(m.InverseMatrix() == exp);
}

TEST(inverse, i3x3_3) {
  const int size = 3;
  S21Matrix m(size, size);
  S21Matrix exp(size, size);

  m[0][0] = 2;
  m[0][1] = 5;
  m[0][2] = 7;
  m[1][0] = 6;
  m[1][1] = 3;
  m[1][2] = 4;
  m[2][0] = 5;
  m[2][1] = -2;
  m[2][2] = -3;

  exp[0][0] = 1;
  exp[0][1] = -1;
  exp[0][2] = 1;
  exp[1][0] = -38;
  exp[1][1] = 41;
  exp[1][2] = -34;
  exp[2][0] = 27;
  exp[2][1] = -29;
  exp[2][2] = 24;

  ASSERT_TRUE(m.InverseMatrix() == exp);
}
