#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10
#define INTERVAL 100

int prime_count[NUM_THREADS];

int is_prime(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

void *count_primes(void *arg)
{
    int thread_id = *(int *)arg;
    int start = thread_id * INTERVAL;
    int end = start + INTERVAL - 1;
    for (int i = start; i <= end; i++)
    {
        if (is_prime(i))
            prime_count[thread_id]++;
    }
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, count_primes, &thread_args[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++)
    {
        printf("Interval [%d, %d] has %d prime numbers.\n", i * INTERVAL, (i + 1) * INTERVAL - 1, prime_count[i]);
    }
    return 0;
}