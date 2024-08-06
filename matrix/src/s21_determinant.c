#include <math.h>

#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;

  if (!A || !result) error = 1;
  if (!error) error = s21_check_matrix(A);
  if (!error && (A->rows != A->columns)) error = 2;

  if (!error) {
    matrix_t temp = {0};
    int swap = 0;

    if (!s21_is_triangle(A, &error) && !error) {
      s21_create_matrix(A->rows, A->columns, &temp);

      for (int i = 0; i < A->rows; ++i)
        for (int j = 0; j < A->columns; ++j)
          temp.matrix[i][j] = A->matrix[i][j];
      for (int i = 0; i < A->rows; ++i) swap += s21_null_column(&temp, i);
    }

    if (!error) {
      *result =
          s21_calculate_determinant(temp.matrix ? &temp : A) * pow(-1, swap);
      if (temp.matrix) s21_remove_matrix(&temp);
    }
  }

  return error;
}
