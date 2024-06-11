#include <stdio.h>

int main(int argc, char** argv)
{
    int count = 0;

    //if/else if/else statement
    if (argc == 1)
    {
        printf("Not enough arguments.\n");
        goto exit;
    }
    else if (argc == 2)
    {
        printf("Enough arguments, heres some loops.\n");
        goto loops;
    }
    else
    {
        printf("Lots of arguments, heres some conditionals.\n");
        goto conditionals;
    }

    loops:
    //do while loop
    do
    {
        printf("This will print exactly once.\n");
    } while (count < 0);

    //while loop
    while (count < 0)
    {
        printf("This should not print.\n");
        goto exit;
    }

    //for loop
    for (int i = 10; i != count; --i)
    {
        //if statement
        if (i % 2 == 0)
            printf("Our count is: %d\n", count);
        
        count++;
    }

    goto exit;

    conditionals:
    //switch statement
    switch (count)
    {
        case 0:
            printf("If this prints our goto worked.\n");
            break;
        case 4:
            printf("If this prints our label didn't work.\n");
            goto exit;
        default:
            printf("If this prints who knows what happened!\n");
            goto exit;
    }
    
    //if/else statement
    if (argc < 3)
    {
        printf("We should never see this message.\n");
    }
    else
    {
        printf("This concludes our conditional statements.\n");
    }


    //effective use of goto labels to construct a single exit point within a function
    exit:
    printf("We are exiting with our exit message.\n");
    return 0;
}