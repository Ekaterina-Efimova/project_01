#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;

  if (!A || !B || !result) error = 1;
  if (!error) error = s21_check_matrix(A);
  if (!error) error = s21_check_matrix(B);

  if (!error && (A->columns != B->rows)) error = 2;
  if (!error) error = s21_check_nan(A);
  if (!error) error = s21_check_nan(B);

  if (!error) {
    error = s21_create_matrix(A->rows, B->columns, result);

    int i = 0;
    for (; i < result->rows && !error; i++) {
      for (int j = 0; j < result->columns && !error; j++) {
        double temp = 0;
        for (int k = 0; k < B->rows; k++) {
          temp += A->matrix[i][k] * B->matrix[k][j];
        }

        result->matrix[i][j] = temp;
        error = s21_check_nan(result);
      }
    }
  }

  return error;
}