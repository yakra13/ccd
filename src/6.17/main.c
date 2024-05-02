#include <stdio.h>
#include "vector3.h"

void PrintVectorInfo(Vector3* a, char* label);

int main (int argc, char** argv)
{
    Vector3 a = {1.5, 2.0, 2.0};
    Vector3 b = {2.5, 1.0, 0.0};

    PrintVectorInfo(&a, "a");
    PrintVectorInfo(&b, "b");

    printf("Add vector b to vector a\n");
    Add(&a, &b);
    PrintVectorInfo(&a, "a");

    printf("Scale vector a by 2\n");
    Scale(&a, 2.0);
    PrintVectorInfo(&a, "a");

    printf("Rotate 90 degrees on X axis\n");
    RotateOnXAxis(&a, 90.0);
    PrintVectorInfo(&a, "a");

    printf("Normalize vector a\n");
    Normalize(&a);
    PrintVectorInfo(&a, "a");

    return 0;
}

void PrintVectorInfo(Vector3* a, char* label)
{
    if (label != NULL)
        printf("Vector %s info:\n", label);
    else
        printf("Unspecified vector info:\n");

    printf("\t%.3f, %.3f, %.3f\n", a->x, a->y, a->z);
    printf("\tLength: %.3f\n", Magnitude(a));
}