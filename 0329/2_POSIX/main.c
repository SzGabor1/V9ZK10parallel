#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void *thread_func(void *arg)
{
    clock_t start = clock(); // get start time
    while ((clock() - start) / CLOCKS_PER_SEC < 1)
        ; // perform 1 second of computation
    printf("Thread finished after 1 second of computation.\n");
    return NULL;
}

int main()
{
    int num_threads = 60;
    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&threads[i], NULL, thread_func, NULL); // creates threads with 1 second of computation
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");

    return 0;
}
