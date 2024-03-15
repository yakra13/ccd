/*6.20 Demonstrate skill in accessing environment variables
Objectives

- N/A
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    //The name of the variable we want to print
    char* envvar = "PATH";

    //using the getenv function we can retrieve the env variable based on its name.
    //Verify the variable exists
    if(!getenv(envvar)){
        printf("The environment variable %s was not found.\n", envvar);
        return -1;
    }

    //Just print the contents of the variable
    printf("PATH: %s\n", getenv(envvar));

    return 0;
}