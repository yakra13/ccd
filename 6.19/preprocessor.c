/*6.19 Demonstrate skill in using the C preprocessor
Objectives

- N/A
*/

//The c preprocessor is basically anything starting with a #
//here the include statment adds the standard input output functions to this file
#include <stdio.h>
//here we define 'variables' during compilation the preprocessor will just replace all occurances of TRUE with 1 and FALSE with 0
#define TRUE 1
#define FALSE 0

//here we define a function like macro; see below for usage
#define SQUARE(x) (x * x)

//here an if defined macro is used to include different header files based on the type of system this is compiled on
#ifdef __unix__
#include <unistd.h>
#elif defined _WIN32
#include <windows.h>
#endif

int main(void)
{
    //this print statement will only be compiled if we defined TRUE as 1
    #if TRUE == 1
        printf("TRUE was defined as 1\n");
    #endif

    //This will be replaced with (5 * 5) by the preprocessor
    int x = SQUARE(5);

    return FALSE;
}