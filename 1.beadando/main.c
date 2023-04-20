#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

typedef struct
{
    int start;
    int end;
    int count;
} PrimeArgs;

bool is_prime(int n)
{
    if (n <= 1)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

void *count_primes(void *args)
{
    PrimeArgs *prime_args = (PrimeArgs *)args;
    int count = 0;
    for (int i = prime_args->start; i <= prime_args->end; i++)
    {
        if (is_prime(i))
            count++;
    }
    prime_args->count = count;

    return NULL;
}

int main()
{
    int limit = 0;
    printf("Add meg a prímszámok megszámlálásának határát: ");
    scanf("%d", &limit);

    PrimeArgs args1 = {1, limit / 2, 0};
    PrimeArgs args2 = {limit / 2 + 1, limit, 0};

    clock_t start_time, end_time;

    // Párhuzamos futtatás
    start_time = clock();
    pthread_t thread1;
    pthread_t thread2;

    if (pthread_create(&thread1, NULL, count_primes, (void *)&args1))
    {
        perror("pthread_create");
        return 1;
    }

    if (pthread_create(&thread2, NULL, count_primes, (void *)&args2))
    {
        perror("pthread_create");
        return 1;
    }

    if (pthread_join(thread1, NULL))
    {
        perror("pthread_join");
        return 1;
    }

    if (pthread_join(thread2, NULL))
    {
        perror("pthread_join");
        return 1;
    }

    end_time = clock();
    double parallel_duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    int total_count_parallel = args1.count + args2.count;

    // Szekvenciális futtatás
    start_time = clock();
    PrimeArgs args = {1, limit, 0};
    count_primes((void *)&args);
    end_time = clock();
    double sequential_duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    int total_count_sequential = args.count;

    printf("A prímszámok száma 1 és %d között (párhuzamosan): %d\n", limit, total_count_parallel);
    printf("A prímszámok száma 1 és %d között (szekvenciálisan): %d\n", limit, total_count_sequential);
    printf("Párhuzamos futtatás időtartama: %f másodperc\n", parallel_duration);
    printf("Szekvenciális futtatás időtartama: %f másodperc\n", sequential_duration);
    printf("Párhuzamosítással megtakarított idő: %f másodperc\n", sequential_duration - parallel_duration);

    return 0;
}