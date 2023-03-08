#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    char str[100];
    int piece;

    printf("File: ");

    scanf("%[^\n]s", str);

    printf("Piece: ");

    scanf("%d", &piece);

    clock_t t;

    t = clock();

    FILE *filePointer;

    filePointer = fopen(str, "w");

    srand(time(NULL));

    for (int i = 0; i < piece; i++)
    {
        int szam = (rand() % (1000 - 500 + 1)) + 500;
        fprintf(filePointer, "%d ", szam);
    }

    fclose(filePointer);

    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
    printf("Random number, file create time: %.lf secounds!", time_taken);

    return 0;
}
