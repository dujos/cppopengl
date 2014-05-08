#include "Math.h"


const double Math::pi = 4 * std::atan(1.f);

const double pi2 = Math::pi*2;

int Math::degrees_to_radians(double degrees) {
	return degrees * (Math::pi/180);
}
	
double Math::radians_to_degrees(double radians) {
	return radians * (180/Math::pi);
}