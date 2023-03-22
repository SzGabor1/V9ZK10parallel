#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int is_unique(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] == arr[j])
            {
                return 0; // van duplikátum
            }
        }
    }
    return 1; // minden elem egyedi
}

int main()
{
    srand(time(NULL)); // véletlen generáláshoz
    int size = 10;     // elemszám
    int arr[size];

    for (int i = 0; i < size; i++)
    {
        arr[i] = i + 1; // inicializálás
    }

    for (int i = 0; i < size; i++)
    {
        if (rand() % 2 == 0)
        {                          // 0.5 valószínűséggel duplikálás
            int j = rand() % size; // véletlen index
            arr[i] = arr[j];
        }
    }

    if (is_unique(arr, size))
    {
        printf("Minden elem egyedi.\n");
    }
    else
    {
        printf("Van duplikátum.\n");
    }

    return 0;
}
