#include <math.h>

#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;

  if (!A || !result) error = 1;
  if (!error) error = s21_check_matrix(A);

  if (!error && (A->rows != A->columns)) error = 2;

  if (!error && A->rows == 1) {
    error = s21_create_matrix(A->rows, A->columns, result);
    if (!error) result->matrix[0][0] = A->matrix[0][0];

  } else if (!error) {
    error = s21_create_matrix(A->rows, A->columns, result);

    int i = 0;
    for (; i < A->rows && !error; i++) {
      for (int j = 0; j < A->columns && !error; j++) {
        matrix_t minor_matrix;
        // double d = 0;

        error = s21_create_matrix(A->rows - 1, A->columns - 1, &minor_matrix);
        s21_minor(A, &minor_matrix, i, j);

        if (!error)
          error = s21_determinant(&minor_matrix, &result->matrix[i][j]);
        if (!error) error = s21_check_number(result->matrix[i][j]);
        if (!error) result->matrix[i][j] *= pow(-1, i + j);

        s21_remove_matrix(&minor_matrix);
      }
    }

    if (i < A->rows) {
      error = 1;
      s21_remove_matrix(result);
    }
  }

  return error;
}
