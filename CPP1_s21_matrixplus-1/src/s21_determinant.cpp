#include <cmath>

#include "s21_matrix_oop.h"

double S21Matrix::Determinant() {
  if (!rows_) throw std::out_of_range("Empty matrix.");
  if (rows_ != cols_) throw std::out_of_range("Incorrect input");

  S21Matrix temp(rows_, cols_);
  double det = 0;
  int flag = 0;
  int swap = 0;

  if (!S21Matrix::IsTriangular()) {
    for (int i = 0; i < rows_; ++i)
      for (int j = 0; j < cols_; ++j) temp.matrix_[i][j] = matrix_[i][j];

    for (int i = 0; i < rows_; ++i) swap += temp.S21Matrix::NullColumn(i);
    flag = 1;
  }

  det = (flag ? temp : *this).S21Matrix::CalcDeterminant() * pow(-1, swap);

  return det;
}
