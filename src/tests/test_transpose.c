#include "test.h"

START_TEST(transpose_error_0) {
  matrix_t M, R;
  s21_create_matrix(3, 3, &M);
  M.matrix[0][0] = 5;
  M.matrix[0][1] = 2;
  M.matrix[0][2] = 3;
  M.matrix[1][0] = 7.5;
  M.matrix[1][1] = 3.14;
  M.matrix[1][2] = 1;
  M.matrix[2][0] = 1;
  M.matrix[2][1] = 1;
  M.matrix[2][2] = 1;

  int error = s21_transpose(&M, &R);
  s21_remove_matrix(&M);
  s21_remove_matrix(&R);
  ck_assert_double_eq(error, 0);
}
END_TEST

START_TEST(transpose_error_0_1) {
  matrix_t M, R;
  s21_create_matrix(1, 3, &M);
  M.matrix[0][0] = 5;
  M.matrix[0][1] = 2;
  M.matrix[0][2] = 3;

  int error = s21_transpose(&M, &R);
  s21_remove_matrix(&M);
  s21_remove_matrix(&R);
  ck_assert_double_eq(error, 0);
}
END_TEST

START_TEST(transpose_error_1) {
  matrix_t *M = NULL, R;

  int error = s21_transpose(M, &R);
  ck_assert_double_eq(error, 1);
}
END_TEST

Suite *test_transpose(void) {
  Suite *s = suite_create("\033[1;3;5;42;31m-=S21_TRANSPOSE=-\033[0m");
  TCase *tc = tcase_create("transpose_tc");
  tcase_add_test(tc, transpose_error_0);
  tcase_add_test(tc, transpose_error_0_1);
  tcase_add_test(tc, transpose_error_1);

  suite_add_tcase(s, tc);

  return s;
}
