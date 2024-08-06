#include <math.h>
#include <stdio.h>
#include <string.h>

#include "s21_matrix.h"

void s21_minor(matrix_t *A, matrix_t *minor_matrix, int row, int colum) {
  for (int i = 0; i < minor_matrix->rows; i++) {
    for (int j = 0; j < minor_matrix->columns; j++) {
      minor_matrix->matrix[i][j] =
          A->matrix[i < row ? i : i + 1][j < colum ? j : j + 1];
    }
  }
}

int s21_check_nan(const matrix_t *A) {
  int error = 0;
  for (int i = 0; i < A->rows && !error; i++) {
    for (int j = 0; j < A->columns && !error; j++) {
      if (isnan(A->matrix[i][j])) error = 2;
    }
  }
  return error;
}

int s21_check_number(double num) {
  int error = 0;
  if (isnan(num)) error = 2;
  return error;
}

int s21_check_matrix(const matrix_t *A) {
  int error = 0;

  if (!A->matrix) error = 1;
  if (!error) {
    for (int i = 0; i < A->rows && !error; i++) {
      if (A->matrix[i] == NULL) error = 1;
    }
  }
  return error;
}

double s21_calculate_determinant(matrix_t *A) {
  double result = 1;
  for (int i = 0; i < A->rows; ++i) result *= A->matrix[i][i];
  return result;
}

int s21_null_column(matrix_t *A, int j) {
  int i = j + 1;
  int swap;
  int count = 0;

  while (i < A->rows) {
    if (A->matrix[j][j]) {
      double temp = A->matrix[i][j] / A->matrix[j][j];

      for (int k = j; k < A->columns; ++k) {
        A->matrix[i][k] -= temp * A->matrix[j][k];
      }
      ++i;

    } else if ((swap = s21_swap(A, j)) != j) {
      for (int l = 0; l < A->columns; ++l) {
        double temp = A->matrix[j][l];
        A->matrix[j][l] = A->matrix[swap][l];
        A->matrix[swap][l] = temp;
      }
      ++count;

    } else
      i = A->rows;
  }

  return count;
}

int s21_is_triangle(matrix_t *A, int *error) {
  int res = 1;

  int i = 0;
  for (; i < A->rows && A->matrix[i] && res; i++) {
    for (int j = -0; j < i && res; j++) res = A->matrix[i][j] ? 0 : 1;
  }

  if (i < A->rows && !A->matrix[i]) *error = 1;

  return res;
}

int s21_swap(matrix_t *A, int row) {
  int i = row;
  int swap = row;

  for (; i < A->rows && swap == row; i++) swap = A->matrix[i][row] ? i : swap;

  return swap;
}
