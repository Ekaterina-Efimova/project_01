#include "s21_matrix_oop.h"

void S21Matrix::MulNumber(const double num) {
  if (!rows_) throw std::out_of_range("Empty matrix.");

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}