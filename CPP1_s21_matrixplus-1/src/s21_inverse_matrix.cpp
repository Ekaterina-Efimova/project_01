#include "s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() {
  if (!rows_) throw std::out_of_range("Empty matrix.");

  double det = S21Matrix::Determinant();
  if (!det) throw std::out_of_range("Incorrect determinant");
  S21Matrix res(rows_, cols_);

  if (rows_ == 1) {
    res.matrix_[0][0] = 1.0 / matrix_[0][0];

  } else {
    res = S21Matrix::CalcComplements();
    res = res.S21Matrix::Transpose();
    res.S21Matrix::MulNumber(1.0 / det);
  }

  return res;
}