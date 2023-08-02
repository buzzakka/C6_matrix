#include "s21_matrix.h"

/*
**************************************************
*            create and remove matrix            *
**************************************************
*/

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int status = s21_OK;
  if (result) {
    result->columns = columns;
    result->rows = rows;
    if (rows > 0 && columns > 0) {
      result->matrix = (double **)calloc(rows, sizeof(double *));
      if (result->matrix != NULL) {
        for (int i = 0; i < rows; i++) {
          result->matrix[i] = (double *)calloc(columns, sizeof(double));
          if (result->matrix[i] == NULL) {
            for (int k = 0; k < i; k++) free(result->matrix[k]);
            status = s21_INCORRECT_MATRIX_ERROR;
          }
          if (status == s21_OK) {
            for (int j = 0; j < columns; j++) {
              result->matrix[i][j] = 0;
            }
          }
        }
      } else {
        status = s21_INCORRECT_MATRIX_ERROR;
      }
    } else {
      status = s21_INCORRECT_MATRIX_ERROR;
    }
  } else {
    status = s21_INCORRECT_MATRIX_ERROR;
  }
  return status;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->columns = 0;
    A->rows = 0;
    A = NULL;
  }
}

/*
**************************************************
*                  arithmetics                   *
**************************************************
*/

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = check_status(A, B);
  if (status == s21_OK) {
    status = s21_create_matrix(A->rows, A->columns, result);
    if (status == s21_OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return status;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = check_status(A, B);
  if (status == s21_OK) {
    status = s21_create_matrix(A->rows, A->columns, result);
    if (status == s21_OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return status;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int status = incorrect_matrix_check(A);
  if (status == s21_OK) {
    status = s21_create_matrix(A->rows, A->columns, result);
    if (status == s21_OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return status;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int status = incorrect_matrix_check(A) || incorrect_matrix_check(B);
  if (status == s21_OK && A->columns != B->rows) {
    status = S21_CALCULATION_ERROR;
  }
  if (status == s21_OK) {
    status = s21_create_matrix(A->rows, B->columns, result);
    if (status == s21_OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }
  return status;
}

/*
**************************************************
*                   comparison                   *
**************************************************
*/

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = !(incorrect_matrix_check(A) || incorrect_matrix_check(B));

  if (status == s21_SUCCESS) {
    if ((A->columns != B->columns) || (A->rows != B->rows)) {
      status = s21_FAILURE;
    }
    for (int i = 0; status == s21_SUCCESS && i < A->rows; i++) {
      for (int j = 0; status == s21_SUCCESS && j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-07) {
          status = s21_FAILURE;
        }
      }
    }
  }
  return status;
}

/*
**************************************************
*         determinant and alg. additions         *
**************************************************
*/

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = incorrect_matrix_check(A);

  if (status == s21_OK &&
      s21_create_matrix(A->rows, A->columns, result) == s21_OK) {
    if (A->rows == A->columns && A->rows > 1) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = get_minor(A, i, j) * pow(-1, i + j);
        }
      }
    } else {
      status = S21_CALCULATION_ERROR;
    }
  } else {
    status = s21_INCORRECT_MATRIX_ERROR;
  }
  return status;
}

int s21_determinant(matrix_t *A, double *result) {
  int status = incorrect_matrix_check(A) || !result;
  if (status == s21_OK && A->columns != A->rows) {
    status = S21_CALCULATION_ERROR;
  }
  if (status == s21_OK) {
    *result = 0;
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      matrix_t algebr_matrix = {0};
      s21_calc_complements(A, &algebr_matrix);
      for (int j = 0; j < A->columns; j++) {
        *result += A->matrix[0][j] * algebr_matrix.matrix[0][j];
      }
      s21_remove_matrix(&algebr_matrix);
    }
  }
  return status;
}

/*
**************************************************
*                   transform                    *
**************************************************
*/

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = incorrect_matrix_check(A) || !result;
  if (status == s21_OK) {
    if (A->columns == A->rows) {
      double det = 0.;
      int status = s21_determinant(A, &det);
      if (status == s21_OK && fabs(det) > 1e-6) {
        matrix_t alg_dop = {0};
        matrix_t alg_dop_transpose = {0};

        s21_calc_complements(A, &alg_dop);
        s21_transpose(&alg_dop, &alg_dop_transpose);
        status = s21_create_matrix(A->rows, A->columns, result);
        if (status == s21_OK) {
          for (int i = 0; i < result->rows; i++) {
            for (int j = 0; j < result->columns; j++) {
              result->matrix[i][j] = alg_dop_transpose.matrix[i][j] / det;
            }
          }
        } else {
          status = s21_INCORRECT_MATRIX_ERROR;
        }
        s21_remove_matrix(&alg_dop);
        s21_remove_matrix(&alg_dop_transpose);
      } else {
        status = S21_CALCULATION_ERROR;
      }
    } else {
      status = S21_CALCULATION_ERROR;
    }
  }
  return status;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int status = incorrect_matrix_check(A);

  if (status == s21_OK) {
    status = s21_create_matrix(A->columns, A->rows, result);

    if (status == s21_OK) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[j][i];
        }
      }
    }
  }
  return status;
}

/*
**************************************************
*                 other functions                *
**************************************************
*/

/*  Проверка на s21_INCORRECT_MATRIX_ERROR  */
int incorrect_matrix_check(matrix_t *A) {
  int result =
      (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) ? 1
                                                                          : 0;
  return result;
}

/*  Проверка статуса для операций сложения и вычитания  */
int check_status(matrix_t *A, matrix_t *B) {
  int status = incorrect_matrix_check(A) || incorrect_matrix_check(B);
  if (status == s21_OK) {
    status = (A->columns == B->columns && A->rows == B->rows) ? 0 : 2;
  }
  return status;
}

/*  Нахождение минора  */
double get_minor(matrix_t *A, int i, int j) {
  double minor = 0.;
  matrix_t minor_matrix = {0};
  s21_create_matrix(A->rows - 1, A->columns - 1, &minor_matrix);
  make_matrix_for_minor(A, i, j, &minor_matrix);
  s21_determinant(&minor_matrix, &minor);
  s21_remove_matrix(&minor_matrix);
  return minor;
}

/*  Создание матрицы для минора  */
void make_matrix_for_minor(matrix_t *A, int i, int j, matrix_t *result) {
  int new_i = 0;
  int new_j = 0;

  for (int k = 0; k < A->rows; k++) {
    if (k != i) {
      for (int l = 0; l < A->columns; l++) {
        if (l != j) {
          result->matrix[new_i][new_j++] = A->matrix[k][l];
        }
      }
      new_j = 0;
      new_i++;
    }
  }
}