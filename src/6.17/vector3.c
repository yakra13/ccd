#include "vector3.h"

double DegToRad(double d)
{
    return d * M_PI / 180.0;
}

double RadToDeg(double d)
{
    return d * 180.0 / M_PI;
}

void Add(Vector3* a, Vector3* b)
{
    a->x += b->x;
    a->y += b->y;
    a->z += b->z;
}

void Subtract(Vector3* a, Vector3* b)
{
    a->x -= b->x;
    a->y -= b->y;
    a->z -= b->z;
}

void Scale(Vector3* a, double s)
{
    a->x *= s;
    a->y *= s;
    a->z *= s;
}

double Magnitude(Vector3* a)
{
    return sqrt(a->x * a->x + 
                a->y * a->y + 
                a->z * a->z);
}

void Normalize(Vector3* a)
{
    double m = Magnitude(a);

    a->x /= m;
    a->y /= m;
    a->z /= m;
}

void RotateOnXAxis(Vector3*a, double d)
{
    d = DegToRad(d);
    double c = cos(d);
    double s = sin(d);

    double y = a->y * c + a->z * -s;
    double z = a->y * s + a->z * c;

    a->y = y;
    a->z = z;
}

void RotateOnYAxis(Vector3*a, double d)
{
    d = DegToRad(d);
    double c = cos(d);
    double s = sin(d);

    double x =  a->x * c + a->z * s;
    double z = -a->x * s + a->z * c;

    a->x = x;
    a->z = z;
}

void RotateOnZAxis(Vector3*a, double d)
{
    d = DegToRad(d);
    double c = cos(d);
    double s = sin(d);

    double x = a->x * c + a->y * -s;
    double y = a->x * s + a->y * c;

    a->x = x;
    a->y = y;
}