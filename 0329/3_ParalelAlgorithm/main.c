#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void sequential_prefix(int *arr, int n)
{
    for (int i = 1; i < n; i++)
    {
        arr[i] += arr[i - 1];
    }
}

void crew_prefix(int *arr, int n)
{
    int log_n = log2(n);
    for (int i = 0; i < log_n; i++)
    {
        int offset = 1 << (i + 1);
#pragma omp parallel for
        for (int j = offset - 1; j < n; j += offset)
        {
            arr[j] += arr[j - (1 << i)];
        }
    }
}

void erew_prefix(int *arr, int n)
{
    int log_n = log2(n);
    for (int i = 0; i < log_n; i++)
    {
        int offset = 1 << (i + 1);
#pragma omp parallel for
        for (int j = offset - 1; j < n; j += offset)
        {
            int t = arr[j - (1 << i)];
            arr[j - (1 << i)] = arr[j];
            arr[j] += t;
        }
    }
}

void optimal_prefix(int *arr, int n)
{
    int log_n = log2(n);
    for (int i = 0; i < log_n; i++)
    {
        int offset = 1 << (i + 1);
        int num_threads = n / offset;
#pragma omp parallel for num_threads(num_threads)
        for (int j = offset - 1; j < n; j += offset)
        {
            int t = arr[j - (1 << i)];
            arr[j - (1 << i)] = arr[j];
            arr[j] += t;
        }
    }
}

void print_array(int *arr)
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int n = 10;
    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }
    printf("Original array:\n");
    print_array(arr);
    printf("Sequential prefix sum:\n");
    sequential_prefix(arr, n);
    print_array(arr);

    printf("Crew prefix sum:\n");
    crew_prefix(arr, n);
    print_array(arr);

    printf("Erew prefix sum:\n");
    erew_prefix(arr, n);
    print_array(arr);

    printf("Optimal prefix sum:\n");
    optimal_prefix(arr, n);
    print_array(arr);

    free(arr);
    return 0;
}