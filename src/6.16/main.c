/*6.16 Demonstrate skill in compiling, linking, and debugging

Objectives

- [ ] Execute a program in a debugger to perform general debugging actions
- [ ] Create a program using the compilation and linking process
- [ ] Compile position-independent code using a cross-compiler

*/

#include <stdio.h>
#include "zmath.h"

// - [ ] Create a program using the compilation and linking process
// - [ ] Compile position-independent code using a cross-compiler
// See the makefile for these objectives

int main()
{
    Point pointA = { .x = 0.0f, .y = 0.0f };
    Point pointB = { .x = 30.0f, .y = -20.0f };

    Point midpoint = { .x = 0.0f, .y = 0.0f };

    // Find length of the line AB
    float lineLength = p_distance(pointA, pointB);

    // Find mid point of line AB
    p_lerp(pointA, pointB, 0.5f, &midpoint);

    printf("Point A: %.2f, %.2f\n", pointA.x, pointA.y);
    printf("Point B: %.2f, %.2f\n", pointB.x, pointB.y);
    printf("Length: %.2f\n", lineLength);
    printf("Midpoint: %.2f, %.2f\n", midpoint.x, midpoint.y);

    return 0;
}

// - [ ] Execute a program in a debugger to perform general debugging actions
/*
Debugging was performed in vscode.
This is fairly simple code and did not require actual debugging however I created a fake bug 
where midpoint was null and used the debugger to step thru and find the issue.
Actions used such as setting a break point. Stepping line by line to check values as they
were updated. Other possible actions in a debugger are viewing the call stack, setting watches
on variables, memory monitoring, disassembly view, etc.
*/