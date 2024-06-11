#pragma once
#include <math.h>

typedef struct Vector3
{
    double x, y, z;
} Vector3;

void Add(Vector3* a, Vector3* b);
void Subtract(Vector3* a, Vector3* b);

void Scale(Vector3* a, double s);

double Magnitude(Vector3* a);

void Normalize(Vector3* a);

void RotateOnXAxis(Vector3* a, double d);
void RotateOnYAxis(Vector3* a, double d);
void RotateOnZAxis(Vector3* a, double d);

double DegToRad(double d);
double RadToDeg(double d);