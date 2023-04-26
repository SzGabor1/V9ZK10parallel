#include "prime.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Helyes hasznalat: %s <határ> <szálak száma>\n", argv[0]);
        return 1;
    }

    int limit = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    if (num_threads < 1)
    {
        printf("A szálak számának legalább 1-nek kell lennie.\n");
        return 1;
    }

    PrimeArgs args[num_threads];
    pthread_t threads[num_threads];

    int chunk_size = limit / num_threads;
    int remainder = limit % num_threads;

    int start = 1;
    int end = start + chunk_size - 1;

    clock_t start_time, end_time;

    // Parhuzamos futtatas
    start_time = clock();

    for (int i = 0; i < num_threads; i++)
    {
        args[i].start = start;
        args[i].end = end + (i == num_threads - 1 ? remainder : 0);
        args[i].count = 0;

        if (pthread_create(&threads[i], NULL, count_primes, (void *)&args[i]))
        {
            perror("pthread_create");
            return 1;
        }

        start = end + 1;
        end = start + chunk_size - 1;
    }

    int total_count_parallel = 0;

    for (int i = 0; i < num_threads; i++)
    {
        if (pthread_join(threads[i], NULL))
        {
            perror("pthread_join");
            return 1;
        }

        total_count_parallel += args[i].count;
    }

    end_time = clock();
    double parallel_duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // Szekvencialis futtatas
    start_time = clock();
    PrimeArgs args_seq = {1, limit, 0};
    count_primes((void *)&args_seq);
    end_time = clock();
    double sequential_duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    int total_count_sequential = args_seq.count;

    printf("A primszamok szama 1 es %d kozott (parhuzamosan): %d\n", limit, total_count_parallel);
    printf("A primszamok szama 1 es %d kozott (szekvencialisan): %d\n", limit, total_count_sequential);
    printf("Parhuzamos futtatas idotartama: %f masodperc\n", parallel_duration);
    printf("Szekvencialis futtatas idotartama: %f masodperc\n", sequential_duration);
    printf("Parhuzamositasal megtakaritott ido: %f masodperc\n", sequential_duration - parallel_duration);

    return 0;
}

bool is_prime(int n)
{
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
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