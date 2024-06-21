#include "test.h"

START_TEST(inverse_1x1) {
  matrix_t M, R;
  s21_create_matrix(1, 1, &M);
  M.matrix[0][0] = 2;

  int error = s21_inverse_matrix(&M, &R);
  ck_assert_double_eq(error, 0);

  s21_remove_matrix(&M);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(inverse_3x3) {
  matrix_t M, R;
  s21_create_matrix(3, 3, &M);
  M.matrix[0][0] = 2;
  M.matrix[0][1] = 5;
  M.matrix[0][2] = 7;
  M.matrix[1][0] = 6;
  M.matrix[1][1] = 3;
  M.matrix[1][2] = 4;
  M.matrix[2][0] = 5;
  M.matrix[2][1] = -2;
  M.matrix[2][2] = -3;

  int error = s21_inverse_matrix(&M, &R);
  ck_assert_double_eq(error, 0);

  s21_remove_matrix(&M);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(inverse_error_1) {
  matrix_t *M = NULL;
  matrix_t R;

  int error = s21_inverse_matrix(M, &R);
  ck_assert_double_eq(error, 1);
}
END_TEST

START_TEST(inverse_error_2) {
  matrix_t M, R;
  s21_create_matrix(2, 3, &M);

  int error = s21_inverse_matrix(&M, &R);
  ck_assert_double_eq(error, 2);

  s21_remove_matrix(&M);
}
END_TEST

START_TEST(inverse_error_2_det_0) {
  matrix_t M, R;
  s21_create_matrix(3, 3, &M);
  M.matrix[0][0] = 1;
  M.matrix[0][1] = 2;
  M.matrix[0][2] = 3;
  M.matrix[1][0] = 4;
  M.matrix[1][1] = 5;
  M.matrix[1][2] = 6;
  M.matrix[2][0] = 7;
  M.matrix[2][1] = 8;
  M.matrix[2][2] = 9;

  int error = s21_inverse_matrix(&M, &R);
  ck_assert_double_eq(error, 2);

  s21_remove_matrix(&M);
}

Suite *test_inverse_matrix(void) {
  Suite *s = suite_create("\033[1;3;5;42;31m-=S21_INVERSE_MATRIX=-\033[0m");
  TCase *tc = tcase_create("inverse_tc");

  tcase_add_test(tc, inverse_1x1);
  tcase_add_test(tc, inverse_3x3);
  tcase_add_test(tc, inverse_error_1);
  tcase_add_test(tc, inverse_error_2);
  tcase_add_test(tc, inverse_error_2_det_0);

  suite_add_tcase(s, tc);

  return s;
}
