#pragma once

typedef struct
{
    float x;
    float y;
} Point;

float lerp(float start, float end, float t);
float clamp(float min, float max, float value);
float p_distance(Point a, Point b);
void p_lerp(Point start, Point end, float t, Point* point);