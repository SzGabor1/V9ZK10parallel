#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int lower, upper, num;

    srand(time(NULL));

    printf("Enter lower bound: ");
    scanf("%d", &lower);
    printf("Enter upper bound: ");
    scanf("%d", &upper);

    num = (rand() % (upper - lower + 1)) + lower;
    printf("Random number between %d and %d: %d\n", lower, upper, num);

    return 0;
}
