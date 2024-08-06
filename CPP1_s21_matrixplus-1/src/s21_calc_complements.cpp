#include <cmath>

#include "s21_matrix_oop.h"
S21Matrix S21Matrix::CalcComplements() {
  if (!rows_) throw std::out_of_range("Empty matrix.");
  if (rows_ != cols_) throw std::out_of_range("Incorrect input");

  S21Matrix res(rows_, cols_);
  if (rows_ == 1)
    res[0][0] = 1;
  else
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor = S21Matrix::Minor(i, j);
        res.matrix_[i][j] = minor.S21Matrix::Determinant() * pow(-1, i + j);
      }

  return res;
}
