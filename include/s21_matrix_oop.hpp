#ifndef S21_MATRIX_HPP_
#define S21_MATRIX_HPP_

class S21Matrix {
 private:
  int rows_, cols_;
  double *matrix_;

 public:
  static constexpr double EPS = 1e-6;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  S21Matrix &operator=(S21Matrix &&other) noexcept;

  ~S21Matrix();

  double *operator[](int row) const;
  double &operator()(int row, int col) const;

  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void set_rows(const int &new_rows);
  void set_cols(const int &new_cols);

  bool EqMatrix(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other) const noexcept;

  void SumMatrix(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);

  void SubMatrix(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix &operator-=(const S21Matrix &other);

  void MulMatrix(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix &operator*=(const S21Matrix &other);

  void MulNumber(double num);
  S21Matrix operator*(double num) const;
  S21Matrix &operator*=(double num);
  friend S21Matrix operator*(double num, const S21Matrix &matrix);

  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;
  double Determinant() const;
};

#endif  // S21_MATRIX_HPP_
