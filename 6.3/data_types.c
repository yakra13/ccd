#include <stdio.h>
#include <limits.h>
#define _USE_MATH_DEFINES
#include <math.h>

int main(void)
{
    int integerType = INT_MAX;
    long longType = LONG_MAX;
    long long longlongType = LLONG_MAX;
    float floatType = M_PI;
    double doubleType = M_E;
    long double longdoubleType = M_SQRT1_2;
    char charType = 'a';
    short shortType = SHRT_MAX;

    printf("TYPE\tBytes\tValue\n");
    printf("int\t%zu\t%d\n", sizeof(integerType), integerType);
    printf("long\t%zu\t%ld\n", sizeof(longType), longType);
    printf("llong\t%zu\t%lld\n", sizeof(longlongType), longlongType);
    printf("float\t%zu\t%.2f\n", sizeof(floatType), floatType);
    printf("double\t%zu\t%.4lf\n", sizeof(doubleType), doubleType);
    printf("ldouble\t%zu\t%.8Lf\n", sizeof(longdoubleType), longdoubleType);
    printf("char\t%zu\t%c\n", sizeof(charType), charType);
    printf("short\t%zu\t%hi\n", sizeof(shortType), shortType);

    return 0;
}