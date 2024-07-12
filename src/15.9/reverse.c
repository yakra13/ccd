#include <stdio.h>

typedef struct 
{
    char charVar;
    int intVar;
    char charVar2;
} SampleStruct;


char get_char(int num)
{
    char c = num % 255;
    return c;
}

int main()
{
    SampleStruct s = {0};
    s.charVar = get_char(300);
    s.intVar = 0xABCD;
    s.charVar2 = 'A';

    printf("Struct contents:\n%c\n0x%x\n%c\n", s.charVar, s.intVar, s.charVar2);

    return 0;
}