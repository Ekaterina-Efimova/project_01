#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix::S21Matrix(3, 3) {}

S21Matrix::S21Matrix(int row, int col) : rows_(row), cols_(col) {
  S21Matrix::AllocateMatrix(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  S21Matrix::AllocateMatrix(other.rows_, other.cols_);

  for (int i = 0; i < rows_; ++i)
    for (int j = 0; j < cols_; ++j) matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  if (!other.GetRows()) throw std::out_of_range("Empty matrix.");

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}