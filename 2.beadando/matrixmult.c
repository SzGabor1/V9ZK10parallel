#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

void sequential_matrix_multiply(int n, double *A, double *B, double *C)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i * n + j] = 0.0;
            for (k = 0; k < n; k++)
            {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void parallel_matrix_multiply(int n, double *A, double *B, double *C, int num_threads)
{
    int i, j, k;

#pragma omp parallel for num_threads(num_threads) private(j, k)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i * n + j] = 0.0;
            for (k = 0; k < n; k++)
            {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
}

void parallel_matrix_block_multiply(int n, double *A, double *B, double *C, int num_threads)
{
    int i, j, k;
    int block_size = n / 4; // block size

#pragma omp parallel for num_threads(num_threads) private(i, j, k)
    for (int ii = 0; ii < n; ii += block_size)
    {
        for (int jj = 0; jj < n; jj += block_size)
        {
            for (int kk = 0; kk < n; kk += block_size)
            {
                // Block indices
                int i_max = ii + block_size < n ? ii + block_size : n;
                int j_max = jj + block_size < n ? jj + block_size : n;
                int k_max = kk + block_size < n ? kk + block_size : n;

                // Compute matrix multiplication for block
                for (i = ii; i < i_max; i++)
                {
                    for (j = jj; j < j_max; j++)
                    {
                        double sum = 0.0;
                        for (k = kk; k < k_max; k++)
                        {
                            sum += A[i * n + k] * B[k * n + j];
                        }
                        C[i * n + j] += sum;
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv)
{

    FILE *output_file = fopen("output.txt", "w");
    if (!output_file)
    {
        perror("Error opening output file");
        return 1;
    }
    if (argc < 3)
    {
        printf("Usage: %s <matrix_size1> <matrix_size2> ... <num_threads>\n", argv[0]);
        return 1;
    }

    int num_threads = atoi(argv[argc - 1]);
    int i, j, k, n;

    for (i = 1; i < argc - 1; i++)
    {
        n = atoi(argv[i]);

        double *A = malloc(n * n * sizeof(double));
        double *B = malloc(n * n * sizeof(double));
        double *C = malloc(n * n * sizeof(double));

        srand(time(NULL));
        // Initialize A and B with random values
        for (j = 0; j < n; j++)
        {
            for (k = 0; k < n; k++)
            {
                A[j * n + k] = rand() / (double)RAND_MAX;
                B[j * n + k] = rand() / (double)RAND_MAX;
            }
        }

        // Multiply matrices sequentially and measure time
        clock_t start = clock();
        sequential_matrix_multiply(n, A, B, C);
        clock_t end = clock();
        double sequential_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Multiply matrices in parallel and measure time
        start = clock();
        parallel_matrix_multiply(n, A, B, C, num_threads);
        end = clock();
        double parallel_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Multiply matrices as separated blocks in parallel and measure time
        start = clock();
        parallel_matrix_block_multiply(n, A, B, C, num_threads);
        end = clock();
        double parallel_block_time = ((double)(end - start)) / CLOCKS_PER_SEC;

        printf("Matrix size: %d x %d\n", n, n);
        printf("Sequential time: %f seconds\n", sequential_time);
        printf("Parallel time: %f seconds\n", parallel_time);
        printf("Speedup sequential-paralell: %f\n", sequential_time / parallel_time);
        printf("Parallel block time: %f seconds\n", parallel_block_time);
        printf("Speedup paralell-block_paralell: %f\n", parallel_time / parallel_block_time);

        fprintf(output_file, "Matrix size: %d x %d\n", n, n);
        fprintf(output_file, "Sequential time: %f seconds\n", sequential_time);
        fprintf(output_file, "Parallel time: %f seconds\n", parallel_time);
        fprintf(output_file, "Speedup sequential-paralell: %f\n", sequential_time / parallel_time);
        fprintf(output_file, "Parallel block time: %f seconds\n", parallel_block_time);
        fprintf(output_file, "Speedup sequential-paralell: %f\n", sequential_time / parallel_time);

        free(A);
        free(B);
        free(C);
    }
    fclose(output_file);
    return 0;
}
