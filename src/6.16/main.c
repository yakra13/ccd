/*6.16 Demonstrate skill in compiling, linking, and debugging

Objectives

- [ ] Execute a program in a debugger to perform general debugging actions
- [ ] Create a program using the compilation and linking process
- [ ] Compile position-independent code using a cross-compiler

*/
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
// #include <unistd.h> // For usleep function
#include "zmath.h"

// double get_time_in_miliseconds() 
// {
//     return (double)clock() / CLOCKS_PER_SEC * 1000;
// }

double get_elapsed_time(clock_t startTime) 
{
    return ((double)(clock() - startTime) / CLOCKS_PER_SEC) * 1000.0;
}

double get_time_in_milliseconds()
 {
    struct timespec spec;
    clock_gettime(CLOCK_MONOTONIC, &spec);
    return spec.tv_sec * 1000 + spec.tv_nsec / 1000000;
}

int main()
{
    Point startingPosition = { .x = 0.0f, .y = 0.0f };
    Point endingPosition = { .x = 30.0f, .y = -20.0f };

    Point point = { .x = 0.0f, .y = 0.0f };

    // clock_t startTime = clock();

    double duration = 5000.0; // in ms
    double elapsedTime = 0.0;

    double preTime = get_time_in_milliseconds();
    double curTime = get_time_in_milliseconds();

    double deltaTime = curTime - preTime;

    // Get the start time
    // double e =  get_elapsed_time(startTime);

    float t = 0.0f;
    printf("\n");
    while (elapsedTime / 1000 < duration)
    {
         // Get the current time
        curTime = get_time_in_milliseconds();
        

        // Calculate the elapsed time
        t = (float)(elapsedTime / duration);
        // double frm = get_elapsed_time(startTime);

        p_lerp(startingPosition, endingPosition, t, &point);

        // printf("\r\033[A%02.0f:%02.0f  \nX: %.5f Y: %.5f",
        //     elapsedTime / 1000 / 60, elapsedTime / 1000,
        //     point.x, point.y); //duration / 1000
        
        // frm = get_elapsed_time(startTime) - frm;
        // printf(" frame time: %.10f", frm);
        // Flush the output to ensure it is printed immediately
        printf("\rcur: %.5f   ", elapsedTime);
        fflush(stdout);
        
        // e =  get_elapsed_time(startTime);
        deltaTime = curTime - preTime;
        elapsedTime += deltaTime;
        // Update the previous time
        preTime = curTime;

        // usleep(2000000); // Sleep for 2,000,000 microseconds (2 seconds)
    }

    printf("\n");

    return 0;
}