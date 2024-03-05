#include <stdio.h>

void sort(int array[], int length);

int main(void)
{
    int array[] = {1, 3, 7, 2, 1};
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\nsorted\n");

    sort(array, sizeof(array) / sizeof(array[0]));
    for (size_t i = 0; i < 5; i++)
    {
        printf("%d ", array[i]);
    }
}

void sort(int array[], int length)
{
    int x, j;
    for (int i = 1; i < length; i++)
    {
        x = array[i];
        j = i - 1;

        while (j >= 0 && array[j] > x)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }

        array[j + 1] = x;
    }
    
}