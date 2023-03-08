#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

int main()
{
    int i, x, y, sum, inputNum;

    clock_t t;

    t = clock();

    srand(time(NULL));
    x = rand() % 2 + 1;
    y = rand() % 2 + 1;
    sum = x + y;

    while (sum != inputNum)
    {
        printf("Add össze %d + %d -t!  Kérem a számot: ", x, y);
        scanf("%d", &inputNum);
        if (inputNum == sum)
        {
            printf("Gratulalok, eltalaltad a szamot!");
        }
    }

    t = clock() - t;

    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds

    printf("fun() took %f seconds to execute \n", time_taken);
    return 0;
}