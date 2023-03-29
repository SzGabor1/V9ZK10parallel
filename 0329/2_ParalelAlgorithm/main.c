#include <stdio.h>

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int even_count = 0;
    int odd_count = 0;
    int zero_count = 0;
    int positive_count = 0;
    int negative_count = 0;

    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        if (arr[i] % 2 == 0)
            even_count++;
        else
            odd_count++;

        if (arr[i] == 0)
            zero_count++;

        if (arr[i] > 0)
            positive_count++;
        else if (arr[i] < 0)
            negative_count++;
    }

    printf("Even numbers: %d\n", even_count);
    printf("Odd numbers: %d\n", odd_count);
    printf("Zeroes: %d\n", zero_count);
    printf("Positive numbers: %d\n", positive_count);
    printf("Negative numbers: %d\n", negative_count);

    return 0;
}