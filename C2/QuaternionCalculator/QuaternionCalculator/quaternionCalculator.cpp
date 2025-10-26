#include "quaternionCalculator.h"

#include <iostream>

Quaternion::Quaternion(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

Quaternion Quaternion::ParseFromString(std::string stringifiedQuaternion)
{
	Quaternion newQuaternion;


}

void Quaternion::Print()
{
	std::cout << "{ " << X << ", " << Y << ", " << Z << ", " << W << " }\n";
}
