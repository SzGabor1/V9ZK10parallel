#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int *array;
int array_size;
int num_threads;
int *sums;

void *calculate_sum(void *arg)
{
    int thread_id = *(int *)arg;
    int start = thread_id * (array_size / num_threads);
    int end = MIN((thread_id + 1) * (array_size / num_threads), array_size);
    for (int i = start; i < end; i++)
    {
        sums[thread_id] += array[i];
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <array size> <number of threads>\n", argv[0]);
        return 1;
    }
    array_size = atoi(argv[1]);
    num_threads = atoi(argv[2]);
    array = malloc(array_size * sizeof(int));
    sums = calloc(num_threads, sizeof(int));
    for (int i = 0; i < array_size; i++)
    {
        array[i] = rand() % 10;
    }
    pthread_t threads[num_threads];
    int thread_args[num_threads];
    for (int i = 0; i < num_threads; i++)
    {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, calculate_sum, &thread_args[i]);
    }
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }
    int total_sum = 0;
    for (int i = 0; i < num_threads; i++)
    {
        total_sum += sums[i];
    }
    printf("Total sum: %d\n", total_sum);
    free(array);
    free(sums);
    return 0;
}