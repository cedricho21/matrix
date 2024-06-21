#include "test.h"

START_TEST(mult_n_error_0) {
  matrix_t M, R;
  s21_create_matrix(1, 1, &M);
  M.matrix[0][0] = 1;

  double number = 0;
  int error = s21_mult_number(&M, number, &R);
  ck_assert_double_eq(error, 0);

  s21_remove_matrix(&M);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(mult_n_error_1) {
  matrix_t *M = NULL;
  matrix_t R;
  double number = 0;
  int error = s21_mult_number(M, number, &R);
  ck_assert_double_eq(error, 1);
}
END_TEST

Suite *test_mult_number(void) {
  Suite *s = suite_create("\033[1;3;5;42;31m-=S21_MULT_NUMBER=-\033[0m");
  TCase *tc = tcase_create("mult_n_tc");

  tcase_add_test(tc, mult_n_error_0);
  tcase_add_test(tc, mult_n_error_1);

  suite_add_tcase(s, tc);

  return s;
}
