#include "Vector3.hpp"

void Vector3::truncate(double max) {
	if (vectorMag(*this) > max)
	{
	this->normalize();

	*this *= max;
	} 
}