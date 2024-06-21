#include "test.h"

START_TEST(create_1x1) {
  matrix_t M;
  int error = s21_create_matrix(1, 1, &M);
  M.matrix[0][0] = 2;

  ck_assert_double_eq(error, 0);

  s21_remove_matrix(&M);
}
END_TEST

START_TEST(create_error_1) {
  matrix_t M;
  int error = s21_create_matrix(-1, 66, &M);

  ck_assert_double_eq(error, 1);
}
END_TEST

Suite *test_create_matrix(void) {
  Suite *s = suite_create("\033[1;3;5;42;31m-=S21_CREATE_MATRIX=-\033[0m");
  TCase *tc = tcase_create("create_tc");

  tcase_add_test(tc, create_1x1);
  tcase_add_test(tc, create_error_1);

  suite_add_tcase(s, tc);

  return s;
}
