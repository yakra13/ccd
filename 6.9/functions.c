#include <stdio.h>
#include <stdbool.h>

bool modify_output_parameter(int* output);
void get_input(char*);
int recursive_function(int value);

int main(void)
{
    int output_value = 0;

    if(modify_output_parameter(&output_value))
    {
        printf("Success -> %d\n", output_value);
    }
    else
    {
        printf("Fail -> %d\n", output_value);
    }
    
    //A function pointer
    void (*function_pointer)(char*) = &get_input;
    (*function_pointer)(NULL);
    (*function_pointer)("Custom prompt: \n");


    printf("The final value is %d\n", recursive_function(-1));
    printf("The final value is %d\n", recursive_function(15));

    return 0;
}

//A function that modifies an output parameter through a pointer
//Proper declaration for created functions
//A function that returns a value using a return statement
bool modify_output_parameter(int* output)
{
    if (output != NULL)
    {
        *output = 100;
        return true;
    }

    return false;
}

//A function that receives input from a user
//A function that does not return a value (i.e ., is declared void)
//A function that is passed an argument by value
//A function that takes a pointer argument
void get_input(char* prompt)
{
    int num;

    if (prompt != NULL)
    {
        printf(prompt);
    }
    else
    {
        printf("Enter an integer: \n");
    }

    scanf("%d", &num);
    printf("You entered %d\n", num);
}

//A recursive function
int recursive_function(int value)
{
    printf("The value is %d\f", value);

    if (value == 10)
        return value;

    if (value < 10)
        value++;
    else
        value--;

    return recursive_function(value);
}