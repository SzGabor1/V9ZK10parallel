#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 100
#define NUM_TRIALS 10
#define FILENAME "matrix_mult_times.csv"

void matrix_mult_serial(double a[N][N], double b[N][N], double result[N][N])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            double sum = 0.0;
            for (int k = 0; k < N; ++k)
            {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
}

void matrix_mult_parallel(double a[N][N], double b[N][N], double result[N][N])
{
#pragma omp parallel for
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            double sum = 0.0;
            for (int k = 0; k < N; ++k)
            {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
}

void fill_matrix(double matrix[N][N])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            matrix[i][j] = rand() % 100;
        }
    }
}

int main()
{
    double a[N][N], b[N][N], result[N][N];
    double serial_time, parallel_time;
    FILE *file = fopen(FILENAME, "w");

    srand(time(NULL));
    fill_matrix(a);
    fill_matrix(b);

    fprintf(file, "trial,serial_time,parallel_time\n");

    for (int trial = 0; trial < NUM_TRIALS; ++trial)
    {
        double start_serial = omp_get_wtime();
        matrix_mult_serial(a, b, result);
        double end_serial = omp_get_wtime();
        serial_time = end_serial - start_serial;

        double start_parallel = omp_get_wtime();
        matrix_mult_parallel(a, b, result);
        double end_parallel = omp_get_wtime();
        parallel_time = end_parallel - start_parallel;

        fprintf(file, "%d,%f,%f\n", trial + 1, serial_time, parallel_time);
    }

    fclose(file);

    return 0;
}