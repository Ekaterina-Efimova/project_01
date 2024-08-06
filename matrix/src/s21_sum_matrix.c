#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;

  if (!A || !B || !result) error = 1;
  if (!error) error = s21_check_matrix(A);
  if (!error) error = s21_check_matrix(B);

  if (!error && (A->rows != B->rows || A->columns != B->columns)) error = 2;
  if (!error) error = s21_check_nan(A);
  if (!error) error = s21_check_nan(B);

  if (!error) {
    s21_create_matrix(A->rows, A->columns, result);

    int i = 0;
    for (; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return error;
}
