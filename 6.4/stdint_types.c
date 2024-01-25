// Include stdint to access the types
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    // Declare and initialize the variables.
    int8_t int8Type = -8;
    uint8_t uint8Type = 8;
    int16_t int16Type = -16;
    uint16_t uint16Type = 16;
    int32_t int32Type = -32;
    uint32_t uint32Type = 32;
    int64_t int64Type = -64;
    uint64_t uint64Type = 64;

    printf("Size: %zu; value: %hi\n", sizeof(int8Type), int8Type);
    printf("Size: %zu; value: %hu\n", sizeof(uint8Type), uint8Type);

    printf("Size: %zu; value: %d\n", sizeof(int16Type), int16Type);
    printf("Size: %zu; value: %i\n", sizeof(uint16Type), uint16Type);

    printf("Size: %zu; value: %ld\n", sizeof(int32Type), int32Type);
    printf("Size: %zu; value: %lu\n", sizeof(uint32Type), uint32Type);

    printf("Size: %zu; value: %lli\n", sizeof(int64Type), int64Type);
    printf("Size: %zu; value: %llu\n", sizeof(uint64Type), uint64Type);

    return 0;
}