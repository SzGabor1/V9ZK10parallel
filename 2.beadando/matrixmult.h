#ifndef MATRIX_MULT_H
#define MATRIX_MULT_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 100
#define NUM_TRIALS 10
#define FILENAME "matrix_mult_times.csv"

void matrix_mult_serial(double a[N][N], double b[N][N], double result[N][N]);
void matrix_mult_parallel(double a[N][N], double b[N][N], double result[N][N]);
void fill_matrix(double matrix[N][N]);

#endif
