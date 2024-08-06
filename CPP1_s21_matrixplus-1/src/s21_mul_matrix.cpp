#include "s21_matrix_oop.h"

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!other.GetCols() || !other.GetRows())
    throw std::out_of_range("Incorrect input");
  if (cols_ != other.S21Matrix::GetRows())
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");

  S21Matrix res(rows_, other.GetCols());

  for (int i = 0; i < res.S21Matrix::GetRows(); i++)
    for (int j = 0; j < res.S21Matrix::GetCols(); j++) {
      double temp = 0;
      for (int k = 0; k < other.S21Matrix::GetRows(); k++) {
        temp += matrix_[i][k] * other.matrix_[k][j];
      }

      res.matrix_[i][j] = temp;
    }

  *this = res;
}
