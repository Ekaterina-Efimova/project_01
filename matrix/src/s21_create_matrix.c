#include <malloc.h>
#include <stddef.h>

#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;

  if (!result) error = 1;

  if (!error && (rows <= 0 || columns <= 0)) {
    result->matrix = NULL;
    error = 1;
  }

  if (!error) {
    result->rows = rows;
    result->columns = columns;

    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (!result->matrix) error = 1;

    if (!error) {
      for (int i = 0; i < rows && !error; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (!result->matrix[i]) error = 1;
      }

      if (error) {
        for (int i = 0; i < rows; i++) free(result->matrix[i]);
        free(result->matrix);
      }
    }
  }
  return error;
}
