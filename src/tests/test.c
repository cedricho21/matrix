#include "test.h"

void run() {
  Suite *tests[] = {
      test_create_matrix(),
      test_eq_matrix(),
      test_sum_matrix(),
      test_sub_matrix(),
      test_mult_number(),
      test_mult_matrix(),
      test_transpose(),
      test_calc_complements(),
      test_determinant(),
      test_inverse_matrix(),
      NULL,
  };

  int total = 0, failed = 0;

  for (Suite **current = tests; *current; current++) {
    SRunner *sr = srunner_create(*current);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    total += srunner_ntests_run(sr);
    failed += srunner_ntests_failed(sr);

    srunner_free(sr);
  }

  printf(
      "\n"
      " total: %d "
      " failed: %d "
      " success: %d "
      "\n",
      total, failed, total - failed);
}

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

int main() {
  run();
  return 0;
}
