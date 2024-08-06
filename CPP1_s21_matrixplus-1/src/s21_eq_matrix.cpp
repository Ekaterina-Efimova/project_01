#include <cmath>

#include "s21_matrix_oop.h"
bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool result = true;

  if (!other.rows_ || !other.cols_) throw std::out_of_range("Incorrect input");

  if (rows_ != other.rows_ || cols_ != other.cols_)
    result = false;

  else
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++)
        result =
            fabs(matrix_[i][j] - other.matrix_[i][j]) < 1E-7 ? true : false;

  return result;
}