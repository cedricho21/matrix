#include "test.h"

START_TEST(sum_error_0) {
  matrix_t M;
  s21_create_matrix(2, 2, &M);
  M.matrix[0][0] = 1;
  M.matrix[0][1] = 3;
  M.matrix[1][0] = 2;
  M.matrix[1][1] = 4;
  matrix_t R;
  s21_create_matrix(2, 2, &R);
  R.matrix[0][0] = 1;
  R.matrix[0][1] = 3;
  R.matrix[1][0] = 2;
  R.matrix[1][1] = 4;

  matrix_t RESULT;

  int error = s21_sum_matrix(&M, &R, &RESULT);

  s21_remove_matrix(&M);
  s21_remove_matrix(&R);
  s21_remove_matrix(&RESULT);
  ck_assert_double_eq(error, 0);
}
END_TEST

START_TEST(sum_error_1) {
  matrix_t *M = NULL;
  matrix_t R;
  s21_create_matrix(2, 2, &R);
  R.matrix[0][0] = 1;
  R.matrix[0][1] = 3;
  R.matrix[1][0] = 2;
  R.matrix[1][1] = 4;

  matrix_t RESULT;

  int error = s21_sum_matrix(M, &R, &RESULT);

  s21_remove_matrix(&R);
  ck_assert_double_eq(error, 1);
}
END_TEST

START_TEST(sum_error_2) {
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

  int error = s21_sum_matrix(&M, &R, &RESULT);

  s21_remove_matrix(&M);
  s21_remove_matrix(&R);
  ck_assert_double_eq(error, 2);
}
END_TEST

Suite *test_sum_matrix(void) {
  Suite *s = suite_create("\033[1;3;5;42;31m-=S21_SUM_MATRIX=-\033[0m");
  TCase *tc = tcase_create("sum_tc");
  tcase_add_test(tc, sum_error_0);
  tcase_add_test(tc, sum_error_1);
  tcase_add_test(tc, sum_error_2);

  suite_add_tcase(s, tc);

  return s;
}
