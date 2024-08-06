#include <math.h>

#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;

  if (!A || !B) {
    result = FAILURE;
  } else if (s21_check_matrix(A) || s21_check_matrix(B)) {
    result = FAILURE;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    result = FAILURE;
  } else if (s21_check_nan(A) || s21_check_nan(B)) {
    result = FAILURE;
  } else {
    for (int i = 0; i < A->rows && result; i++) {
      for (int j = 0; j < A->columns && result; j++) {
        result = A->matrix[i][j] == B->matrix[i][j] ||
                         fabs(A->matrix[i][j] - B->matrix[i][j]) < 1E-7
                     ? SUCCESS
                     : FAILURE;
      }
    }
  }
  return result;
}
