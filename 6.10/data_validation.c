#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Incorrect usage: Enter a single capitol letter as an argument.\n");
    }

    if (strlen(argv[1]) > 1)
    {
        printf("You did not enter a single letter.\n");
        return -1;
    }

    if (argv[1][0] >= 'A' && argv[1][0] <= 'Z')
    {
        printf("Looks good.\n");
    }
    else
    {
        printf("You did not enter a capitol letter.\n");
        return -1;
    }

    return 0;
}