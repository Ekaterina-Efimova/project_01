#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cstring>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

  void AllocateMatrix(int rows_, int cols_);
  bool IsTriangular() const;
  int NullColumn(int i);
  int Swap(int i);
  double CalcDeterminant();

 public:
  S21Matrix();
  S21Matrix(int rows_, int cols_);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  int GetRows() const;
  int GetCols() const;
  double** GetMatrix() const;

  void SetRows(int rows_);
  void SetCols(int cols_);
  friend void SetMatrix(S21Matrix& matrix, double** new_matrix);

  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  int operator==(const S21Matrix& other) const;
  int operator!=(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(const double num);
  double* operator[](int i);

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  S21Matrix Minor(int i, int j);
};

#endif
