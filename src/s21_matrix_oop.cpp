#include "s21_matrix_oop.hpp"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <utility>

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}
S21Matrix::~S21Matrix() { delete[] matrix_; }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::length_error("Matrix size can't be non-positive");
  }
  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_),
      cols_(other.cols_),
      matrix_(new double[rows_ * cols_]()) {
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) {
    return *this;
  }
  delete[] matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double[rows_ * cols_]();
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
  return *this;
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = std::exchange(other.rows_, 0);
  cols_ = std::exchange(other.cols_, 0);
  matrix_ = std::exchange(other.matrix_, nullptr);
}
S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

double *S21Matrix::operator[](int row) const {
  if (row >= rows_ || row < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return row * cols_ + matrix_;
}

double &S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row * cols_ + col];
}

int S21Matrix::get_rows() const noexcept { return rows_; }
int S21Matrix::get_cols() const noexcept { return cols_; }

void S21Matrix::set_rows(const int &new_rows) {
  if (new_rows <= 0) {
    throw std::length_error("Array size can't be zero");
  }
  S21Matrix tmp(new_rows, cols_);
  for (int i = 0; i < (rows_ < new_rows ? rows_ : new_rows); ++i)
    for (int j = 0; j < cols_; ++j) tmp[i][j] = (*this)[i][j];
  *this = std::move(tmp);
}

void S21Matrix::set_cols(const int &new_cols) {
  if (new_cols <= 0) {
    throw std::length_error("Array size can't be zero");
  }
  S21Matrix tmp(rows_, new_cols);
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < (cols_ < new_cols ? cols_ : new_cols); ++j)
      tmp[i][j] = (*this)[i][j];
  *this = std::move(tmp);
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.get_rows() || cols_ != other.get_cols()) return false;

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j)
      if (std::fabs((*this)[i][j] - other[i][j]) > S21Matrix::EPS) return false;

  return true;
}
bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  return EqMatrix(other);
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.get_rows() || cols_ != other.get_cols()) {
    throw std::logic_error(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) (*this)[i][j] += other[i][j];
}
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix res{*this};
  return res += other;
}
S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.get_rows() || cols_ != other.get_cols()) {
    throw std::logic_error(
        "Incorrect input, matrices should have the same size");
  }
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) (*this)[i][j] -= other[i][j];
}
S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix res{*this};
  res.SubMatrix(other);
  return res;
}
S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) (*this)[i][j] *= num;
}
S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix res{*this};
  res.MulNumber(num);
  return res;
}
S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}
S21Matrix operator*(const double num, const S21Matrix &matrix) {
  S21Matrix res{matrix};
  return res *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.get_rows() || rows_ != other.get_cols()) {
    throw std::logic_error("Dimensions don't fit for the multiplication");
  }

  S21Matrix res(this->rows_, other.get_cols());

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < other.get_cols(); ++j)
      for (int k = 0; k < cols_; k++) {
        res[i][j] += (*this)[i][k] * other[k][j];
      }

  *this = std::move(res);
}
S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix res{*this};
  res.MulMatrix(other);
  return res;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      res[j][i] = (*this)[i][j];
    }
  }
  return res;
}

namespace {
void get_cofactor(const S21Matrix &m, S21Matrix &tmp, int skip_row,
                  int skip_col, int size) {
  for (int i = 0, row = 0; row < size; row++) {
    for (int j = 0, col = 0; col < size; col++) {
      if (row != skip_row && col != skip_col) {
        tmp[i][j] = m[row][col];
        ++j;
        if (j == size - 1) {
          j = 0;
          ++i;
        }
      }
    }
  }
}

double det(const S21Matrix &m, int size) {
  if (size == 1) {
    return m[0][0];
  }

  S21Matrix tmp(size, size);

  double res = 0;
  int sign = 1;
  for (int i = 0; i < size; ++i) {
    get_cofactor(m, tmp, 0, i, size);
    res += sign * m[0][i] * det(tmp, size - 1);
    sign = -sign;
  }

  return res;
}

S21Matrix adjoint(const S21Matrix &m) {
  const int rows = m.get_rows();
  const int cols = m.get_cols();

  if (rows == 1) {
    m[0][0] = 1;
    return m;
  }

  S21Matrix tmp(rows, cols);
  S21Matrix res(rows, cols);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      get_cofactor(m, tmp, i, j, rows);
      const int sign = ((i + j) % 2 == 0) ? 1 : -1;
      res[i][j] = sign * det(tmp, rows - 1);
    }
  }
  return res;
}
}  // namespace

double S21Matrix::Determinant() const {
  if (this->rows_ != this->cols_) {
    throw std::logic_error("The matrix is not square to calculate determinant");
  }
  return det(*this, rows_);
}

S21Matrix S21Matrix::CalcComplements() const {
  if (this->rows_ != this->cols_) {
    throw std::logic_error(
        "The matrix is not square to calculate the complements");
  }
  return adjoint(*this);
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::logic_error("The matrix is not square to calculate the inverse");
  }

  const double det = Determinant();
  if (std::fabs(det) < S21Matrix::EPS) {
    throw std::logic_error("Determinant can't be zero to calculate inverse");
  }

  const S21Matrix adjoint_transposed = CalcComplements().Transpose();
  S21Matrix res(rows_, cols_);

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) res[i][j] = adjoint_transposed[i][j] / det;

  return res;
}
