/*10.3 Demonstrate the ability to use the following constructs

Objectives

- [ ] Signal handling
- [ ] Interrupts
*/

// #define FORCE_SEGMENTATION

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

volatile sig_atomic_t eflags = 0;
volatile sig_atomic_t sigint_count = 0;

const size_t malloc_size = 3;

int32_t* m1;
int32_t* m2;
int32_t* ptr;
int32_t dir = 1;

void handle_sigint(int);
void handle_sigsegv(int);

int main()
{
    // - [ ] Signal handling
    if (signal(SIGINT, handle_sigint) == SIG_ERR)
    {
        exit(1);
    }

    if (signal(SIGSEGV, handle_sigsegv) == SIG_ERR)
    {
        exit(1);
    }
    
    m1 = (int32_t*)malloc(malloc_size * sizeof(int32_t));
    m2 = (int32_t*)malloc(malloc_size * sizeof(int32_t));
    ptr = m1;

    printf("Address m1: 0x%p\n", m1);
    printf("Address m2: 0x%p\n", m2);

    // Assign default values to the malloced arrays.
    for (size_t i = 0; i < malloc_size; i++)
    {
        m1[i] = 1234;
        m2[i] = 4321;
    }

    // Track how many memory addresses we read between the two malloced addresses.
    int spots = 0;

    // Determine if we need to go up or down to reach the next malloced memory.
    #ifdef FORCE_SEGMENTATION
        if (m1 < m2)
            dir = -1;
    #else
        if (m1 > m2)
            dir = -1;
    #endif

    printf("Navigate from m1 memory location to m2 memory location.\n");

    for (;;)
    {
        // Debug to track the ptr
        // printf("ptr addr: 0x%p\n", ptr);

        // Note: There is a chance a random 4321 could be in memory before the m2 address.
        if (*ptr != 1234)
        {
            spots++;

            if(*ptr == 4321)
            {
                printf("Arrived at m2\n");
                printf("address m1(ptr): 0x%p\naddress m2     : 0x%p\n", ptr, m2);
                printf("spots: %d\n", spots);
                break;
            }
        }
        
        ptr += dir;
    }

    free(m1);
    free(m2);

    printf("If we made it here that means we looked at %d unallocated memory addresses.\n", spots);
    printf("So now provide 3 Ctrl+C interrupts to exit.\n");

    // - [ ] Interrupts
    while (sigint_count < 3)
    {
        if (eflags == 1)
        {
            printf("Ctrl+C has been pressed %d times.\n", sigint_count);
            eflags = 0;
        }
    }

    return 0;
}

// Handle interrupts. ie Ctrl+C
void handle_sigint(int sig)
{
    if (signal(SIGINT, handle_sigint) == SIG_ERR)
    {
        exit(1);
    }

    (void)sig;

    sigint_count++;
    eflags = 1;
}

// Handle segmentation faults/illegal memory accesses.
// To force this to happen uncomment line 9 #define
void handle_sigsegv(int sig)
{
    printf("Segmentation fault detected. Attempt to access: %p\n", ptr);
    printf("Aborting...\n");
    exit(139);
}