#include <check.h>

#include "s21_matrix.h"

// Create and remove
START_TEST(s21_create_and_remove_matrix_test) {
  int res = 0;
  matrix_t A = {0};

  // 1
  res = s21_create_matrix(-3, 1, &A);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 2
  res = s21_create_matrix(1, -3, &A);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 3
  res = s21_create_matrix(-3, -3, &A);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 4
  res = s21_create_matrix(0, 2, &A);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 5
  res = s21_create_matrix(1, 1, &A);
  ck_assert_int_eq(A.rows, 1);
  ck_assert_int_eq(A.columns, 1);
  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);

  // 6
  res = s21_create_matrix(3, 5, &A);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 5);
  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);

  // 7
  s21_remove_matrix(NULL);

  // 8
  res = s21_create_matrix(3, 5, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
}
END_TEST

// eq
START_TEST(s21_eq_matrix_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  // 1
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, s21_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 2
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(2, 2, &B);
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, s21_FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 3
  s21_create_matrix(1, 2, &A);
  s21_create_matrix(2, 1, &B);
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, s21_FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 4
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 3;

  B.matrix[0][0] = 0;
  B.matrix[0][1] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3.001;
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, s21_FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 5
  s21_create_matrix(5, 3, &A);
  s21_create_matrix(5, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = A.rows + j - i;
      B.matrix[i][j] = A.rows + j - i;
    }
  }
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, s21_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 6
  s21_create_matrix(3, 3, &A);
  res = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(res, s21_FAILURE);
  s21_remove_matrix(&A);

  // 7
  s21_create_matrix(3, 3, &B);
  res = s21_eq_matrix(NULL, &B);
  ck_assert_int_eq(res, s21_FAILURE);
  s21_remove_matrix(&B);

  // 8
  res = s21_eq_matrix(NULL, NULL);
  ck_assert_int_eq(res, s21_FAILURE);

  // 9
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = A.rows + j - i;
      B.matrix[i][j] = A.rows + j - i;
    }
  }
  A.matrix[0][0] += 0.000000015;
  res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, s21_SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// sum
START_TEST(s21_sum_matrix_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  // 1
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  res = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(C.matrix[0][0], 0);
  ck_assert_int_eq(C.matrix[0][1], 0);
  ck_assert_int_eq(C.matrix[1][0], 0);
  ck_assert_int_eq(C.matrix[1][1], 0);
  ck_assert_int_eq(C.rows, 2);
  ck_assert_int_eq(C.columns, 2);
  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  // 2
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);
  res = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(res, S21_CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 3
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2.0015;
  A.matrix[1][1] = 3;

  B.matrix[0][0] = 11;
  B.matrix[0][1] = 0.13;
  B.matrix[1][0] = 22.22;
  B.matrix[1][1] = -15;
  res = s21_sum_matrix(&A, &B, &C);

  ck_assert_int_eq(C.matrix[0][0], 11);
  ck_assert_int_eq(C.matrix[0][1], 1.13);
  ck_assert_int_eq(C.matrix[1][0], 24.2215);
  ck_assert_int_eq(C.matrix[1][1], -12);

  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  // 4
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 0, &B);
  res = s21_sum_matrix(&A, &B, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 5
  s21_create_matrix(3, 3, &A);
  res = s21_sum_matrix(&A, NULL, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 6
  s21_create_matrix(3, 3, &A);
  res = s21_sum_matrix(NULL, &A, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 7
  res = s21_sum_matrix(NULL, NULL, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 8
  res = s21_sum_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 9
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  res = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 10
  s21_create_matrix(3, 3, &A);
  res = s21_sum_matrix(&A, NULL, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 11
  s21_create_matrix(3, 3, &A);
  res = s21_sum_matrix(NULL, &A, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// sub
START_TEST(s21_sub_matrix_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  // 1
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  res = s21_sub_matrix(&A, &B, &C);
  ck_assert_double_eq(C.matrix[0][0], 0);
  ck_assert_double_eq(C.matrix[0][1], 0);
  ck_assert_double_eq(C.matrix[1][0], 0);
  ck_assert_double_eq(C.matrix[1][1], 0);
  ck_assert_int_eq(C.rows, 2);
  ck_assert_int_eq(C.columns, 2);
  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  // 2
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);
  res = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(res, S21_CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 3
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2.0015;
  A.matrix[1][1] = 3;

  B.matrix[0][0] = 11;
  B.matrix[0][1] = 0.13;
  B.matrix[1][0] = 22.22;
  B.matrix[1][1] = -15;
  res = s21_sub_matrix(&A, &B, &C);

  ck_assert_double_eq(C.matrix[0][0], -11);
  ck_assert_double_eq(C.matrix[0][1], 0.87);
  ck_assert_double_eq(C.matrix[1][0], -20.2185);
  ck_assert_double_eq(C.matrix[1][1], 18);

  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  // 4
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 0, &B);
  res = s21_sub_matrix(&A, &B, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 5
  s21_create_matrix(3, 3, &A);
  res = s21_sub_matrix(&A, NULL, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 6
  s21_create_matrix(3, 3, &A);
  res = s21_sub_matrix(NULL, &A, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 7
  res = s21_sub_matrix(NULL, NULL, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 8
  res = s21_sub_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 9
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  res = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 10
  s21_create_matrix(3, 3, &A);
  res = s21_sub_matrix(&A, NULL, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 11
  s21_create_matrix(3, 3, &A);
  res = s21_sub_matrix(NULL, &A, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

// mult number
START_TEST(s21_mult_number_test) {
  int res = 0;
  matrix_t A = {0};
  double num = 0;
  matrix_t C = {0};

  // 1
  s21_create_matrix(2, 2, &A);
  num = 10.;
  res = s21_mult_number(&A, num, &C);
  ck_assert_double_eq(C.matrix[0][0], 0);
  ck_assert_double_eq(C.matrix[0][1], 0);
  ck_assert_double_eq(C.matrix[1][0], 0);
  ck_assert_double_eq(C.matrix[1][1], 0);
  ck_assert_int_eq(C.rows, 2);
  ck_assert_int_eq(C.columns, 2);
  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);

  // 2
  num = 0.5;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 2.3;
  A.matrix[1][1] = 3;
  res = s21_mult_number(&A, num, &C);
  ck_assert_double_eq(C.matrix[0][0], 0);
  ck_assert_double_eq(C.matrix[0][1], 0.5);
  ck_assert_double_eq(C.matrix[1][0], 1.15);
  ck_assert_double_eq(C.matrix[1][1], 1.5);
  ck_assert_int_eq(C.rows, 2);
  ck_assert_int_eq(C.columns, 2);
  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);

  // 3
  s21_create_matrix(3, 0, &A);
  res = s21_mult_number(&A, num, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 4
  s21_create_matrix(3, 3, &A);
  res = s21_mult_number(&A, num, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 5
  res = s21_mult_number(NULL, num, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 6
  res = s21_mult_number(NULL, num, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
}
END_TEST

// mult matrix
START_TEST(s21_mult_matrix_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};

  // 1
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  res = s21_mult_matrix(&A, &B, &C);
  ck_assert_double_eq(C.matrix[0][0], 0);
  ck_assert_double_eq(C.matrix[0][1], 0);
  ck_assert_double_eq(C.matrix[1][0], 0);
  ck_assert_double_eq(C.matrix[1][1], 0);
  ck_assert_int_eq(C.rows, 2);
  ck_assert_int_eq(C.columns, 2);
  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  // 2
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);
  res = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(res, S21_CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 3
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = -1;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = -4;

  B.matrix[0][0] = -1;
  B.matrix[0][1] = -2.13;
  B.matrix[1][0] = 1.1;
  B.matrix[1][1] = -15;
  res = s21_mult_matrix(&A, &B, &C);

  ck_assert_double_eq(C.matrix[0][0], -1.1);
  ck_assert_double_eq(C.matrix[0][1], 15);
  ck_assert_double_eq(C.matrix[1][0], -7.4);
  ck_assert_double_eq(C.matrix[1][1], 53.61);

  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);

  // 4
  s21_create_matrix(3, 0, &A);
  s21_create_matrix(3, 2, &B);
  res = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&B);

  // 5
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(0, 3, &B);
  res = s21_mult_matrix(&A, &B, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 6
  s21_create_matrix(3, 3, &A);
  res = s21_mult_matrix(&A, NULL, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 7
  s21_create_matrix(3, 3, &A);
  res = s21_mult_matrix(NULL, &A, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 8
  s21_create_matrix(3, 3, &A);
  res = s21_mult_matrix(&A, &A, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 9
  res = s21_mult_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
}
END_TEST

// calc complements
START_TEST(s21_calc_complements_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t C = {0};

  // 1
  s21_create_matrix(2, 1, &A);
  res = s21_calc_complements(&A, &C);
  ck_assert_int_eq(res, S21_CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);

  // 2
  s21_create_matrix(2, 0, &A);
  res = s21_calc_complements(&A, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 3
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  res = s21_calc_complements(&A, &C);
  ck_assert_double_eq(C.matrix[0][0], 0);
  ck_assert_double_eq(C.matrix[0][1], 10);
  ck_assert_double_eq(C.matrix[0][2], -20);
  ck_assert_double_eq(C.matrix[1][0], 4);
  ck_assert_double_eq(C.matrix[1][1], -14);
  ck_assert_double_eq(C.matrix[1][2], 8);
  ck_assert_double_eq(C.matrix[2][0], -8);
  ck_assert_double_eq(C.matrix[2][1], -2);
  ck_assert_double_eq(C.matrix[2][2], 4);

  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);

  // 4
  s21_create_matrix(5, 1, &A);
  res = s21_calc_complements(&A, &C);
  ck_assert_int_eq(res, S21_CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);

  // 5
  res = s21_calc_complements(NULL, &C);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 6
  s21_create_matrix(5, 1, &A);
  res = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 7
  res = s21_calc_complements(NULL, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
}
END_TEST

// determinant
START_TEST(s21_determinant_test) {
  int res = 0;
  double result = 0.;
  matrix_t A = {0};

  // 1
  s21_create_matrix(2, 1, &A);
  res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, S21_CALCULATION_ERROR);
  s21_remove_matrix(&A);

  // 2
  s21_create_matrix(2, 0, &A);
  res = s21_determinant(&A, &result);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 3
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  res = s21_determinant(&A, &result);
  ck_assert_double_eq(result, 0.);

  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);

  // 4
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = 14;
  A.matrix[1][1] = 1.13;
  A.matrix[1][2] = 6.015;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 18.23;
  A.matrix[2][2] = 9.00006;

  res = s21_determinant(&A, &result);
  ck_assert_double_eq_tol(result, -854.973382, pow(10, -6));

  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);

  // 5
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = -15.88;
  res = s21_determinant(&A, &result);
  ck_assert_double_eq_tol(result, -15.88, pow(10, -6));
  s21_remove_matrix(&A);

  // 6
  s21_create_matrix(1, 1, &A);
  res = s21_determinant(&A, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 7
  res = s21_determinant(NULL, &result);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 8
  res = s21_determinant(NULL, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
}
END_TEST

// transpose
START_TEST(s21_transpose_test) {
  int res = 0;
  matrix_t A = {0};
  matrix_t B = {0};

  // 1
  s21_create_matrix(2, 0, &A);
  res = s21_transpose(&A, &B);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&B);

  // 2
  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 6;
  res = s21_transpose(&A, &B);
  ck_assert_int_eq(B.matrix[0][0], 1);
  ck_assert_int_eq(B.matrix[0][1], 3);
  ck_assert_int_eq(B.matrix[0][2], 5);
  ck_assert_int_eq(B.matrix[1][0], 2);
  ck_assert_int_eq(B.matrix[1][1], 4);
  ck_assert_int_eq(B.matrix[1][2], 6);

  ck_assert_int_eq(res, s21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 3
  s21_create_matrix(2, 3, &A);
  res = s21_transpose(&A, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 4
  res = s21_transpose(NULL, &B);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 5
  res = s21_transpose(NULL, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
}
END_TEST

// inverse_matrix
START_TEST(s21_inverse_matrix_test) {
  int res = 0;
  matrix_t A;
  matrix_t B;

  // 1
  s21_create_matrix(2, 0, &A);
  res = s21_inverse_matrix(&A, &B);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 2
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  res = s21_inverse_matrix(&A, &B);

  ck_assert_double_eq(B.matrix[0][0], 1);
  ck_assert_double_eq(B.matrix[0][1], -1);
  ck_assert_double_eq(B.matrix[0][2], 1);
  ck_assert_double_eq(B.matrix[1][0], -38);
  ck_assert_double_eq(B.matrix[1][1], 41);
  ck_assert_double_eq(B.matrix[1][2], -34);
  ck_assert_double_eq(B.matrix[2][0], 27);
  ck_assert_double_eq(B.matrix[2][1], -29);
  ck_assert_double_eq(B.matrix[2][2], 24);

  ck_assert_int_eq(res, s21_OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);

  // 3
  s21_create_matrix(3, 3, &A);
  res = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
  s21_remove_matrix(&A);

  // 4
  res = s21_inverse_matrix(NULL, &B);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);

  // 5
  res = s21_inverse_matrix(NULL, NULL);
  ck_assert_int_eq(res, s21_INCORRECT_MATRIX_ERROR);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, s21_create_and_remove_matrix_test);
  tcase_add_test(tc1_1, s21_eq_matrix_test);
  tcase_add_test(tc1_1, s21_sum_matrix_test);
  tcase_add_test(tc1_1, s21_sub_matrix_test);
  tcase_add_test(tc1_1, s21_mult_number_test);
  tcase_add_test(tc1_1, s21_mult_matrix_test);
  tcase_add_test(tc1_1, s21_calc_complements_test);
  tcase_add_test(tc1_1, s21_determinant_test);
  tcase_add_test(tc1_1, s21_transpose_test);
  tcase_add_test(tc1_1, s21_inverse_matrix_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
