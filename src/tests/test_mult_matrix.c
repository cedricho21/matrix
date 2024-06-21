#include "test.h"

START_TEST(mult_m_error_0) {
  matrix_t M;
  s21_create_matrix(3, 2, &M);
  M.matrix[0][0] = 1;
  M.matrix[0][1] = 4;
  M.matrix[1][0] = 2;
  M.matrix[1][1] = 5;
  M.matrix[2][0] = 3;
  M.matrix[2][1] = 6;
  matrix_t R;
  s21_create_matrix(2, 3, &R);
  R.matrix[0][0] = 1;
  R.matrix[0][1] = -1;
  R.matrix[0][2] = 1;
  R.matrix[1][0] = 2;
  R.matrix[1][1] = 3;
  R.matrix[1][2] = 4;

  matrix_t RESULT;

  int error = s21_mult_matrix(&M, &R, &RESULT);

  s21_remove_matrix(&M);
  s21_remove_matrix(&R);
  s21_remove_matrix(&RESULT);
  ck_assert_double_eq(error, 0);
}
END_TEST

START_TEST(mult_m_error_1) {
  matrix_t *M = NULL;
  matrix_t R;
  s21_create_matrix(2, 2, &R);
  R.matrix[0][0] = 1;
  R.matrix[0][1] = 3;
  R.matrix[1][0] = 2;
  R.matrix[1][1] = 4;

  matrix_t RESULT;

  int error = s21_mult_matrix(M, &R, &RESULT);

  s21_remove_matrix(&R);
  ck_assert_double_eq(error, 1);
}
END_TEST

START_TEST(mult_m_error_2) {
  matrix_t M;
  s21_create_matrix(2, 2, &M);
  M.matrix[0][0] = 1;
  M.matrix[0][1] = 3;
  M.matrix[1][0] = 2;
  M.matrix[1][1] = 4;
  matrix_t R;
  s21_create_matrix(1, 2, &R);
  R.matrix[0][0] = 1;
  R.matrix[0][1] = 3;

  matrix_t RESULT;

  int error = s21_mult_matrix(&M, &R, &RESULT);

  s21_remove_matrix(&M);
  s21_remove_matrix(&R);
  ck_assert_double_eq(error, 2);
}
END_TEST

Suite *test_mult_matrix(void) {
  Suite *s = suite_create("\033[1;3;5;42;31m-=S21_MULT_MATRIX=-\033[0m");
  TCase *tc = tcase_create("mult_m_tc");

  tcase_add_test(tc, mult_m_error_0);
  tcase_add_test(tc, mult_m_error_1);
  tcase_add_test(tc, mult_m_error_2);

  suite_add_tcase(s, tc);

  return s;
}