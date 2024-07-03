#include "zmath.h"
#include <math.h>

float lerp(float start, float end, float t)
{
    // ((1 - t) * start) + (end * t) // slower more precise
    return start + (end - start) * t;
}

float clamp(float min, float max, float value)
{
    if (value < min)
        return min;
    
    if (value > max)
        return max;

    return value;
}

float p_distance(Point a, Point b)
{
    float x = b.x - a.x;
    float y = b.y - a.y;

    return sqrt((x * x) + (y * y));
}

void p_lerp(Point start, Point end, float t, Point* point)
{
    float x = lerp(start.x, end.x, t);
    float y = lerp(start.y, end.y, t);

    point->x = x;
    point->y = y;
}