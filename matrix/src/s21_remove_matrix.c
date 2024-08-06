#include <stdlib.h>

#include "s21_matrix.h"

int s21_remove_matrix(matrix_t *A) {
  int error = 0;

  if (!A) error = 1;
  if (!error) error = s21_check_matrix(A);

  if (!error) {
    for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
    free(A->matrix);

    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }

  return error;
}