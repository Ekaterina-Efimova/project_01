#include "s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }

  S21Matrix res(rows_, cols_);
  res.SumMatrix(other);

  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }

  S21Matrix res(rows_, cols_);
  res.SubMatrix(other);

  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  if (cols_ != other.rows_ || rows_ != other.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }

  S21Matrix res(rows_, other.cols_);
  res.MulMatrix(other);

  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result *= num;
  return result;
}

int S21Matrix::operator==(const S21Matrix& other) const {
  int result = EqMatrix(other);

  return result;
}
int S21Matrix::operator!=(const S21Matrix& other) const {
  int result = EqMatrix(other);

  return !result;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (!other.S21Matrix::GetRows()) throw std::out_of_range("Empty matrix.");

  if (&other != this) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_]();
    for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();

    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
  }

  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

double* S21Matrix::operator[](int i) {
  if (i < 0 || i >= rows_) throw std::out_of_range("Invalid index.");

  return matrix_[i];
}