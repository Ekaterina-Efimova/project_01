#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;

  if (!A || !result) error = 1;
  if (!error) error = s21_check_matrix(A);

  if (!error) {
    s21_create_matrix(A->columns, A->rows, result);

    int i = 0;
    for (; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  return error;
}
