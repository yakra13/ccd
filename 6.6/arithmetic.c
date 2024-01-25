#include <stdio.h>

int main(void)
{
    int integerDivision = 10 / 4;
    float floatDivision = 10.0f / 4.0f;
    printf("int vs float division 10 / 4 -> %d : %.1f\n", integerDivision, floatDivision);


    int remainder = 10 % 4;
    printf("Remainder of 10 / 4 -> %d\n", remainder);

    // Pre incremenet/decrement happens prior to being printed. Post will occur after printing.
    int baseNumber = 10;
    printf("pre-increment vs post-increment of 10 -> %d : %d\n", ++baseNumber, baseNumber++);
    baseNumber = 10;
    printf("pre-decrement vs post-decrement of 10 -> %d : %d\n", --baseNumber, baseNumber--);

    float pemdas = 5.0f + (3.0f * 2.0f) / (3.0f - 1.0f);
    printf("5 + (3 * 2) / (3 - 1) = %.1f", pemdas);

    return 0;
}