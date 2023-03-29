#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *arg)
{
    int *time = (int *)arg;
    sleep(*time); // thread sleeps for specified time
    printf("Thread finished after %d seconds of computation.\n", *time);
    return NULL;
}

int main()
{
    pthread_t tid1, tid2;
    int time1 = 8, time2 = 4;
    pthread_create(&tid1, NULL, thread_func, &time1); // creates first thread with 8 seconds of computation
    pthread_create(&tid2, NULL, thread_func, &time2); // creates second thread with 4 seconds of computation
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("Main thread finished.\n");
    return 0;
}
