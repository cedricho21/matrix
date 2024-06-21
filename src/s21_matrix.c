#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error = 0;
  if ((rows < 1) || (columns < 1) || result == NULL)
    error = 1;
  else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
  }
  return error;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = SUCCESS;
  if (A == NULL || B == NULL || A->rows <= 0 || A->columns <= 0 ||
      A->matrix == NULL || B->rows <= 0 || B->columns <= 0 ||
      B->matrix == NULL || A->rows != B->rows || A->columns != B->columns)
    result = FAILURE;
  else {
    for (int i = 0; i < A->rows && result; i++) {
      for (int j = 0; j < A->columns && result; j++) {
        if (fabs((A->matrix[i][j]) - (B->matrix[i][j])) > s21_eps)
          result = FAILURE;
      }
    }
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A == NULL || B == NULL || A->columns < 1 || B->columns < 1 ||
      A->rows < 1 || B->rows < 1 || A->matrix == NULL || B->matrix == NULL)
    error = 1;
  else if ((A->rows != B->rows) || (A->columns != B->columns))
    error = 2;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return error;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A == NULL || B == NULL || A->columns < 1 || B->columns < 1 ||
      A->rows < 1 || B->rows < 1 || A->matrix == NULL || B->matrix == NULL)
    error = 1;
  else if ((A->rows != B->rows) || (A->columns != B->columns))
    error = 2;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return error;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1 || A->matrix == NULL)
    error = 1;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return error;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = 0;
  if (A == NULL || B == NULL || A->columns < 1 || B->columns < 1 ||
      A->rows < 1 || B->rows < 1 || A->matrix == NULL || B->matrix == NULL)
    error = 1;
  else if (A->columns != B->rows)
    error = 2;
  else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int p = 0; p < A->columns; p++)
          result->matrix[i][j] += A->matrix[i][p] * B->matrix[p][j];
      }
    }
  }
  return error;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1 || A->matrix == NULL)
    error = 1;
  else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return error;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1 || A->matrix == NULL)
    error = 1;
  else if (A->rows != A->columns)
    error = 2;
  else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t sub;
        s21_create_matrix(A->rows - 1, A->columns - 1, &sub);
        s21_matrix_minor(A, &sub, i, j);
        double det = 0.0;
        error = s21_determinant(&sub, &det);
        double sign = pow(-1, i + j);
        result->matrix[i][j] = det * sign;
        s21_remove_matrix(&sub);
      }
    }
  }
  return error;
}

int s21_determinant(matrix_t *A, double *result) {
  int error = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1 || A->matrix == NULL)
    error = 1;
  else if (A->rows != A->columns)
    error = 2;
  else if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else {
    matrix_t B;
    B.rows = A->rows - 1;
    B.columns = A->columns - 1;
    s21_create_matrix(B.rows, B.columns, &B);
    double sign = 1.0;
    double det = 0.0;
    for (int f = 0; f < A->columns; f++) {
      s21_matrix_minor(A, &B, 0, f);
      double sub_det = 0.0;
      s21_determinant(&B, &sub_det);
      det += sign * A->matrix[0][f] * sub_det;
      sign = -sign;
    }
    *result = det;
    s21_remove_matrix(&B);
  }
  return error;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = 0;
  if (A == NULL || A->rows < 1 || A->columns < 1 || A->matrix == NULL)
    error = 1;
  else if (A->rows != A->columns)
    error = 2;
  else {
    double det = 0.0;
    matrix_t B;
    matrix_t C;
    error = s21_determinant(A, &det);
    if (fabs(det) < s21_eps)
      error = 2;
    else {
      if (A->rows == 1) {
        s21_create_matrix(A->rows, A->columns, result);
        result->matrix[0][0] = 1. / A->matrix[0][0];
      } else {
        double new_det = 1. / det;
        error = s21_calc_complements(A, &B);
        error = s21_transpose(&B, &C);
        error = s21_mult_number(&C, new_det, result);
        s21_remove_matrix(&B);
        s21_remove_matrix(&C);
      }
    }
  }
  return error;
}

void s21_matrix_minor(matrix_t *A, matrix_t *B, int p, int q) {
  int i = 0, j = 0;
  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      if (row != p && col != q) {
        B->matrix[i][j++] = A->matrix[row][col];
        if (j == A->columns - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}
