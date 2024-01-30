#include <stdio.h>

int main(int argc, char** argv)
{
    // Print each argument supplied.
    for (; argc > 0; argc--)
    {
        printf("\n%s", *argv);
        argv++;
    }
    
    return 0;
}