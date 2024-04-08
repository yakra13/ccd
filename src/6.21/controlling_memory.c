/*6.21 Demonstrate skill in controlling memory

Objectives

- [x] With attention given to implementation defined behavior, compare and contrast standard memory allocation functions (e.g ., malloc () calloc(), realloc ( ), and free ())
- [x] Demonstrate appropriate error checking when managing memory allocations
- [x] Describe programming techniques that reduce the occurrence of memory leaks (e.g ., behaviors that reinforce a clear ownership model)
- [x] Demonstrate effective use of Valgrind with --leak-check=full to identify memory leaks
- [x] Given code samples, identify and remove memory leaks
*/

#include <stdio.h>
#include <stdlib.h>

// - [ ] With attention given to implementation defined behavior, compare and contrast standard memory allocation functions
//(e.g ., malloc () calloc(), realloc ( ), and free ()
// - [ ] Demonstrate appropriate error checking when managing memory allocations
int main(int argc, char** argv)
{
    int* values;

    printf("malloc 20 ints\n");
    values = (int*)malloc(sizeof(int) * 20);

    if (values == NULL)
    {
        printf("Failed to malloc memory.\n");
        exit(0);
    }

    printf("\nEach int will have some random value based on whatever data was left in those memory addresses.\n");
    for (size_t i = 0; i < 20; i++)
    {
        printf("%d ", values[i]);
    }

    printf("\nFree those values.\n");
    printf("Memory address before free(): %p\n", values);
    free(values);
    printf("Memory address after free(): %p\n", values);

    values = (int*)calloc(20, sizeof(int));

    if (values == NULL)
    {
        printf("Failed to calloc memory.\n");
        exit(0);
    }

    printf("Memory address after calloc() using the same variable: %p\n", values);
    printf("Calloc() initializes the values to 0.\n");
    for (size_t i = 0; i < 20; i++)
    {
        printf("%d ", values[i]);
    }

    printf("\nRealloc that array of ints to include 30 items.\n");
    //NOTE: we assign the return value of realloc to a temp pointer to check if it failed.
    //This way we can hold on to the original memory if necessary.
    int* temp = realloc(values, 30);
    if (temp == NULL)
    {
        printf("Failed to realloc.\n");
        exit(0);
    }
    else
    {
        values = temp;
    }

    for (size_t i = 0; i < 30; i++)
    {
        printf("%d ", values[i]);
    }

    printf("\nNote that realloc will attempt to extended the memory if there is space on the heap.\n" \
           "If not it will reallocate to a different address where there is space.\n" \
           "In either situation the values will not be set to 0.");



    return 0;
}


//- [ ] Describe programming techniques that reduce the occurrence of memory leaks (e.g ., behaviors that reinforce a clear ownership model)
/* If possible always pair a free() with malloc()/calloc() within the same function.
Avoid working directly with the original pointer particularly in larger more complex code bases.
This means assigning to a 'temp' pointer that way when doing operations like pointer arithmetic you won't
lose the original memory location of the allocated memory when it comes time to free it.
*/

// - [ ] Demonstrate effective use of Valgrind with --leak-check=full to identify memory leaks
/*Note Valgrind is a linux utility thus a different method will be needed for windows, ie MemCheck, etc.

1.) verify valgrind is installed: sudo apt install valgrind (or whatever appropriate for your flavor of linux)

2.) run valgrind on your compiled executable
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.log ./executable params

3.) for more accurate information compile the program with debug flags ie -ggdb3
*/


//- [ ] Given code samples, identify and remove memory leaks
/* See 6.8 
https://gitlab.90cos.cdl.af.mil/90cos/virtual-job-qualification-records/current-bccd/ssgt-ziebarth-joshua/ccd-basic-jqr-air-force/-/merge_requests/30

Corrected a handful ofmemory leaks (primarily missing free()s)
*/