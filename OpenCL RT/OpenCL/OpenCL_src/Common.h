#ifndef COMMON_H
#define COMMON_H


double infinity = 1.7976931348623158e+308;
double pi = 3.1415926535897932385;

// Utility Functions

double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

// Common Headers

#include "Ray.h"
#include "Vec3.h"

#endif