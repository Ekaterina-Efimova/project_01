#include "s21_matrix_oop.h"
S21Matrix S21Matrix::Minor(int i, int j) {
  S21Matrix res(rows_ - 1, cols_ - 1);

  for (int k = 0; k < res.rows_; k++) {
    for (int l = 0; l < res.cols_; l++) {
      res.matrix_[k][l] = matrix_[k < i ? k : k + 1][l < j ? l : l + 1];
    }
  }

  return res;
}