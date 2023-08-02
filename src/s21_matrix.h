#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Результат выполнения операции (кроме сравнения):
    s21_OK - ОК
    s21_INCORRECT_MATRIX_ERROR - ошибка, некорректная матрица
    S21_CALCULATION_ERROR - Ошибка вычисления (несовпадающие размеры матриц;
   матрица, для которой нельзя провести вычисления и т.д.)
*/
#define s21_OK 0
#define s21_INCORRECT_MATRIX_ERROR 1
#define S21_CALCULATION_ERROR 2

/*
    Результат сравнения матриц
*/
#define s21_SUCCESS 1
#define s21_FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

double get_minor(matrix_t *A, int i, int j);
void make_matrix_for_minor(matrix_t *A, int i, int j, matrix_t *result);

int incorrect_matrix_check(matrix_t *A);
int check_status(matrix_t *A, matrix_t *B);

#endif  // SRC_S21_MATRIX_H_