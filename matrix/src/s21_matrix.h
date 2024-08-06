#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

//создание и удаление матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result);
int s21_remove_matrix(matrix_t *A);

//сравнениe матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// арифметика матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

//транспорирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);

//алгебраическое дополнение
int s21_calc_complements(matrix_t *A, matrix_t *result);

//определитель
int s21_determinant(matrix_t *A, double *result);

//обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

//прочее
void s21_minor(matrix_t *A, matrix_t *minor_matrix, int row, int colum);
int s21_check_nan(const matrix_t *A);
int s21_check_number(double num);
int s21_check_matrix(const matrix_t *A);
double s21_calculate_determinant(matrix_t *A);
int s21_null_column(matrix_t *A, int j);
int s21_swap(matrix_t *A, int row);
int s21_is_triangle(matrix_t *A, int *error);

#endif