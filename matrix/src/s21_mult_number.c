#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;

  if (!A || !result) error = 1;
  if (!error) error = s21_check_matrix(A);

  if (!error) error = s21_check_nan(A);
  if (!error) error = s21_check_number(number);

  if (!error) {
    error = s21_create_matrix(A->rows, A->columns, result);

    int i = 0;
    for (; i < A->rows && !error; i++) {
      for (int j = 0; j < A->columns && !error; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        error = s21_check_nan(A);
      }
    }
  }

  return error;
}
