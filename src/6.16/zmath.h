#pragma once
typedef struct
{
    double x;
    double y;
} Point;

double lerp(double start, double end, double t);
double clamp(double min, double max, double value);
double p_distance(Point a, Point b);