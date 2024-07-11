#include <stdio.h>

// Forward declaration.
void print_array(char*, size_t);

int main(void)
{
    // Single dimensional array.
    char arr[4] = {'a', 'b', 'c', 'd'};
    // Mult-dimensional array.
    char m_arr[3][2] = { {'e', 'f'}, {'g', 'h'}, {'i', 'j'}};

    print_array(arr, 4);
    print_array(*m_arr, 6);

    return 0;
}

/// @brief Print out the contents of any sized array.
/// @param array Pointer to the array.
/// @param total_elements The total number of elements in the array. 
void print_array(char* array, size_t total_elements)
{
    while (total_elements > 0)
    {
        printf("%c\n", *array);
        array++;
        total_elements--;      
    }

    printf("\n");
}