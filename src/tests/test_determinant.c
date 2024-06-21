#include "test.h"

START_TEST(det_1) {
  matrix_t M;
  s21_create_matrix(1, 1, &M);
  M.matrix[0][0] = 1;

  double det = 0;
  s21_determinant(&M, &det);
  s21_remove_matrix(&M);
  ck_assert_double_eq(det, 1);
}
END_TEST

START_TEST(det_2) {
  matrix_t M;
  s21_create_matrix(2, 2, &M);
  M.matrix[0][0] = 1;
  M.matrix[0][1] = 3;
  M.matrix[1][0] = 2;
  M.matrix[1][1] = 4;

  double det = 0;
  s21_determinant(&M, &det);
  s21_remove_matrix(&M);
  ck_assert_double_eq(det, -2);
}
END_TEST

START_TEST(det_3_1) {
  matrix_t M;
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

  double det = 0;
  s21_determinant(&M, &det);
  s21_remove_matrix(&M);
  ck_assert_double_eq(det, 0);
}
END_TEST

START_TEST(det_3_2) {
  matrix_t M;
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

  double det = 0;
  s21_determinant(&M, &det);
  s21_remove_matrix(&M);
  ck_assert_double_eq(det, 10.78);
}
END_TEST

START_TEST(det_error_0) {
  matrix_t M;
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

  double det = 0;
  int error = s21_determinant(&M, &det);
  s21_remove_matrix(&M);
  ck_assert_double_eq(error, 0);
}
END_TEST

START_TEST(det_error_1) {
  matrix_t *M = NULL;

  double det = 0;
  int error = s21_determinant(M, &det);
  ck_assert_double_eq(error, 1);
}
END_TEST

START_TEST(det_error_2) {
  matrix_t M;
  s21_create_matrix(1, 3, &M);
  M.matrix[0][0] = 5;
  M.matrix[0][1] = 2;
  M.matrix[0][2] = 3;

  double det = 0;
  int error = s21_determinant(&M, &det);
  s21_remove_matrix(&M);
  ck_assert_double_eq(error, 2);
}
END_TEST

Suite *test_determinant(void) {
  Suite *s = suite_create("\033[1;3;5;42;31m-=S21_DETERMINANT=-\033[0m");
  TCase *tc = tcase_create("det_tc");

  tcase_add_test(tc, det_1);
  tcase_add_test(tc, det_2);
  tcase_add_test(tc, det_3_1);
  tcase_add_test(tc, det_3_2);
  tcase_add_test(tc, det_error_0);
  tcase_add_test(tc, det_error_1);
  tcase_add_test(tc, det_error_2);

  suite_add_tcase(s, tc);

  return s;
}
