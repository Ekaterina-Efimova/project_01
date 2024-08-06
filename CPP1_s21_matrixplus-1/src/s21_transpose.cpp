#include "s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() {
  if (!rows_) throw std::out_of_range("Empty matrix.");

  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
    }
  }
  return res;
}