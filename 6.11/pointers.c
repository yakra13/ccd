#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 10

void print_and_sort(int*, int, int (*sort)(const void *, const void *));
int sort_high_low(const void * a, const void * b);
int sort_low_high(const void * a, const void * b);

int main(void)
{
    srand(1234);

    //Declaring an integer pointer
    int* int_array;
    int_array = (int*)malloc(sizeof(int) * ARRAY_SIZE);

    int* ptr = int_array;
    for (size_t i = 0; i < ARRAY_SIZE; i++)
    {
        //Assigning a value to a pointer
        *ptr = rand();
        //Make effective use of pointer arithmetic to traverse an array
        ptr++;
    }
    // - [ ] Printing the address of the variable
    printf("Sorting the array at address: %p\n", int_array);

    printf("Sort descending\n");
    print_and_sort(int_array, ARRAY_SIZE, &sort_high_low);
    printf("Sort ascending\n");
    print_and_sort(int_array, ARRAY_SIZE, &sort_low_high);

    return 0;
}

void print_and_sort(int* array, int size, int (*sort)(const void *, const void *))
{
    printf("Before sort: \n");
    for (size_t i = 0; i < size; i++)
    {
        //Dereferencing a variable to get its value
        printf("%d ", *(array + i));
    }
    //Make use of a function pointer to call another function
    qsort(array, size, sizeof(int), (sort));

    printf("\nAfter sort: \n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int sort_high_low(const void * a, const void * b)
{
    return (*(int*)b - *(int*)a);
}

int sort_low_high(const void * a, const void * b)
{
    return (*(int*)a - *(int*)b);;
}