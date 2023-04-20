#include "main.h"

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
    printf("Add meg a primszamok megszamlalasanak hatarat: ");
    scanf("%d", &limit);

    PrimeArgs args1 = {1, limit / 2, 0};
    PrimeArgs args2 = {limit / 2 + 1, limit, 0};

    clock_t start_time, end_time;

    // Parhuzamos futtatas
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

    // Szekvencialis futtatas
    start_time = clock();
    PrimeArgs args = {1, limit, 0};
    count_primes((void *)&args);
    end_time = clock();
    double sequential_duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    int total_count_sequential = args.count;

    printf("A primszamok szama 1 es %d kozott (parhuzamosan): %d\n", limit, total_count_parallel);
    printf("A primszamok szama 1 es %d kozott (szekvencialisan): %d\n", limit, total_count_sequential);
    printf("Parhuzamos futtatas idotartama: %f masodperc\n", parallel_duration);
    printf("Szekvencialis futtatas idotartama: %f masodperc\n", sequential_duration);
    printf("Parhuzamositasal megtakaritott ido: %f masodperc\n", sequential_duration - parallel_duration);

    return 0;
}
