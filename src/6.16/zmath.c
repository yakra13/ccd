#include "zmath.h"
#include <math.h>

double lerp(double start, double end, double t)
{
    if (t >= 1.0)
        return end;
    
    if (t <= 0.0)
        return start;

    double range = fabs(start) + fabs(end);

    // Check if the range is being treated in reverse
    if (start > end)
        range *= -1;

    return start + range * t;
}

double clamp(double min, double max, double value)
{
    if (value < min)
        return min;
    
    if (value > max)
        return max;

    return value;
}

double p_distance(Point a, Point b)
{
    double x = b.x - a.x;
    double y = b.y - a.y;

    return sqrt((x * x) + (y * y));
}


// ---Warfighting Capability Development Process---
// Concept Refinement:

// New requirement (CERF)
// Major modification
// Check Cyber Capability Registry (CCR)
// Enter in RMS

// Technology Development:

// R & D
// Assess Technology Readiness Level (TRL)
// Initial CCR entry
// Capability Champion

// Capability Development and Demonstration:

// Cape Development Milestone
// Design Readiness Milestone
// Developmental Test and Eval (DT&E)

// Production and Deployment:

// Initial Operational Capability
// Acceptance Test
// Operational Test and Eval (OT&E)

// Operations and Support:

// Full Ops Capability
// Status of Resources and Training (SORTS)
// Develop TTPs