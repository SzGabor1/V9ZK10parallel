#ifndef PRIME_COUNTER_H
#define PRIME_COUNTER_H

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

bool is_prime(int n);

void *count_primes(void *args);

#endif /* PRIME_COUNTER_H */
