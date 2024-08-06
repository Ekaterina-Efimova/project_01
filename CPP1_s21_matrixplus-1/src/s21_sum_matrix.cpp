#include "s21_matrix_oop.h"

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!other.cols_ || !other.rows_) throw std::out_of_range("Incorrect input");
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}