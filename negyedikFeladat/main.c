#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int i;
    float num;
    //
    srand(time(NULL));
    for (i = 0; i < 10; i++)
    {
        num = ((float)rand() / RAND_MAX) * 500 + 500;
        printf("%f\n", num);
    }

    return 0;
}
