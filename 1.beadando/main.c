// Header files
#include <pthread.h> // for pthread_t, pthread_create, pthread_join, pthread_exit
#include <stdio.h> // for printf, NULL
#include <sys/time.h> // for time_t, struct timeval, gettimeofday
#include <math.h> // for sqrt
#include <stdlib.h> // for exit
#include <time.h> // for time

// Define maximum number of threads
#define NUM_THREADS 2000
// Define number of iterations for each thread
#define N 10

// Define global variables
int amount;

// Define thread function
void *calcPI(void *id) {
    // Generate seed based on thread ID
    srand(time(NULL)+ id);
    int i;
    double x,y;

    for (i = 0; i < N; i++) {
        // generate a random number between -1.0 and +1.0
        x = ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;
        y = ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;
    }

    // Output generated coordinates
    printf("X: %lf, Y: %lf\n", x, y);

    // Check if point is inside unit circle
    if ( sqrt((x*x) + (y*y)) < 1.0 ){
        amount++;
    }

    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    amount = 0; // Set global variable to 0
    srand((unsigned)time(NULL)); // Seed random number generator

    int rc;
    long i;
    pthread_t threads[NUM_THREADS]; // Define thread ID array

    // Create threads
    for(i=0; i < NUM_THREADS; i++){
        rc = pthread_create(&threads[i], NULL, calcPI, (void *)i);

        if(rc){
            printf("RC from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to complete
    for(i=0; i < NUM_THREADS; i++){
        rc = pthread_join(threads[i], NULL);

        if(rc){
            printf("RC from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    // Calculate estimated value of pi based on generated coordinates
    float picalc = (float)4.0*((float)amount/(float)NUM_THREADS);

    // Output results
    printf("\nNumber of threads: %d", NUM_THREADS );
    printf("\nNumber in circle: %d", amount );
    printf("\nNumber out of circle: %d", (NUM_THREADS-amount) );
    printf("\nPI Calc: %lf\n", picalc);

    return 0;
}
