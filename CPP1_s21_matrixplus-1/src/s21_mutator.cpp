#include "s21_matrix_oop.h"

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

double** S21Matrix::GetMatrix() const { return matrix_; }
void S21Matrix::SetRows(int new_rows_) {
  if (!rows_) throw std::out_of_range("Empty matrix.");
  if (new_rows_ <= 0) throw std::out_of_range("Invalid number of columns.");

  if (new_rows_ != rows_) {
    double** new_matrix = new double*[new_rows_];
    for (int i = 0; i < new_rows_; i++) {
      new_matrix[i] = new double[cols_];
      if (i < rows_)
        std::copy(matrix_[i], matrix_[i] + cols_, new_matrix[i]);
      else
        std::fill(new_matrix[i], new_matrix[i] + cols_, 0);
    }

    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;

    matrix_ = new_matrix;
    rows_ = new_rows_;
  }
}

void S21Matrix::SetCols(int new_cols_) {
  if (!rows_) throw std::out_of_range("Empty matrix.");
  if (new_cols_ <= 0) throw std::out_of_range("Invalid number of columns.");

  double** matrix = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix[i] = new double[new_cols_];
    for (int j = 0; j < new_cols_; ++j)
      matrix[i][j] = j < cols_ ? matrix_[i][j] : 0;
    delete[] matrix_[i];
  }
  delete[] matrix_;

  matrix_ = matrix;
  cols_ = new_cols_;
}

void SetMatrix(S21Matrix& matrix, double** new_matrix) {
  for (int i = 0; i < matrix.rows_; i++)
    for (int j = 0; j < matrix.cols_; j++)
      matrix.matrix_[i][j] = new_matrix[i][j];
}