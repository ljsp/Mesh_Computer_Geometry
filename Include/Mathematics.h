//
// Created by lucas on 02/10/23.
//

#ifndef MESH_COMPUTATIONAL_GEOMETRY_MATHEMATICS_H
#define MESH_COMPUTATIONAL_GEOMETRY_MATHEMATICS_H

#include <cmath>
#include <vector>
#include <iostream>

#include "Structures.h"

class Math
{
public:
    static constexpr double Clamp(double, double = 0.0, double = 1.0);

    // Minimum and maximum
    static constexpr double Min(double, double);
    static constexpr double Max(double, double);
    static constexpr double Min(double, double, double);
    static constexpr double Max(double, double, double);
    static constexpr double Lerp(double, double, double);

    static constexpr double DegreeToRadian(double);
    static constexpr double RadianToDegree(double);

    static double Dot(Point a, Point b);
    static Point Cross(Point a, Point b);
    static double Norm(Point);
    static Point Normalize(Point);

};

inline constexpr double Math::Clamp(double value, double min, double max)
{
    return (value < min) ? min : (value > max) ? max : value;
}

inline constexpr double Math::Min(double a, double b)
{
    return (a < b) ? a : b;
}

inline constexpr double Math::Max(double a, double b)
{
    return (a > b) ? a : b;
}

inline constexpr double Math::Min(double a, double b, double c)
{
    return (a < b) ? ((a < c) ? a : c) : ((b < c) ? b : c);
}

inline constexpr double Math::Max(double a, double b, double c)
{
    return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
}

inline constexpr double Math::Lerp(double a, double b, double t)
{
    return a + (b - a) * t;
}

inline constexpr double Math::DegreeToRadian(double degree)
{
    return degree * M_PI / 180.0;
}

inline constexpr double Math::RadianToDegree(double radian)
{
    return radian * 180.0 / M_PI;
}

inline double Math::Dot(Point a, Point b)
{
    return a._x * b._x + a._y * b._y + a._z * b._z;
}

inline Point Math::Cross(Point a, Point b)
{
    return Point(a._y * b._z - a._z * b._y,
                 a._z * b._x - a._x * b._z,
                 a._x * b._y - a._y * b._x);
}

inline double Math::Norm(Point a)
{
    return sqrt(Dot(a, a));
}

inline Point Math::Normalize(Point a)
{
    double norm = Norm(a);
    return Point(a._x / norm, a._y / norm, a._z / norm);
}

#endif //MESH_COMPUTATIONAL_GEOMETRY_MATHEMATICS_H




