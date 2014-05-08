#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <cmath>

class Math {

public:
	static const double pi;
	static const double pi2;

	static int degrees_to_radians(double degrees);
	static double radians_to_degrees(double radians);
};

#endif