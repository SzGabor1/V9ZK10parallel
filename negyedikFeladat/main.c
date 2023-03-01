#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i;
    float num;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Generate and print 10 random floating-point numbers between 500 and 1000
    for (i = 0; i < 10; i++)
    {
        num = ((float)rand() / RAND_MAX) * 500 + 500;
        printf("%f\n", num);
    }

    return 0;
}
