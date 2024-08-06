#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;

  if (!A || !result || !A->matrix) error = 1;
  if (!error && (A->rows != A->columns)) error = 2;

  if (!error) {
    double det = 0;
    error = s21_determinant(A, &det);

    if (!error && det == 0) error = 2;

    if (!error) {
      if (A->rows == 1) {
        error = s21_create_matrix(A->rows, A->columns, result);
        if (!error) result->matrix[0][0] = 1.0 / A->matrix[0][0];

      } else {
        matrix_t temp_matrix = {0};
        matrix_t matrix_transpose = {0};
        error = s21_calc_complements(A, &temp_matrix);

        if (!error) error = s21_transpose(&temp_matrix, &matrix_transpose);
        if (!error)
          error = s21_mult_number(&matrix_transpose, 1.0 / det, result);

        s21_remove_matrix(&temp_matrix);
        s21_remove_matrix(&matrix_transpose);
      }
    }
  }
  return error;
}
