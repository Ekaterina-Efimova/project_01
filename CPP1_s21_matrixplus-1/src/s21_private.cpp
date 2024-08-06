#include "s21_matrix_oop.h"

void S21Matrix::AllocateMatrix(int rows_, int cols_) {
  if (rows_ <= 0 || cols_ <= 0) throw std::runtime_error("Invalid parameters.");

  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();
}

bool S21Matrix::IsTriangular() const {
  int res = true;

  for (int i = 0; i < rows_ && matrix_[i] && res; i++)
    for (int j = -0; j < i && res; j++) res = (matrix_[i][j] ? false : true);

  return res;
}

int S21Matrix::NullColumn(int j) {
  int i = j + 1;
  int swap;
  int count = 0;

  while (i < rows_) {
    if (matrix_[j][j]) {
      double temp = matrix_[i][j] / matrix_[j][j];

      for (int k = j; k < cols_; ++k) {
        matrix_[i][k] -= temp * matrix_[j][k];
      }
      ++i;

    } else if ((swap = S21Matrix::Swap(j)) != j) {
      for (int l = 0; l < cols_; ++l) {
        double temp = matrix_[j][l];
        matrix_[j][l] = matrix_[swap][l];
        matrix_[swap][l] = temp;
      }
      ++count;

    } else
      i = rows_;
  }

  return count;
}

int S21Matrix::Swap(int i) {
  int j = i;
  int swap = i;

  for (; j < rows_ && swap == i; j++) swap = matrix_[j][i] ? j : swap;

  return swap;
}

double S21Matrix::CalcDeterminant() {
  double result = 1;

  for (int i = 0; i < rows_; ++i) result *= matrix_[i][i];

  return result;
}
