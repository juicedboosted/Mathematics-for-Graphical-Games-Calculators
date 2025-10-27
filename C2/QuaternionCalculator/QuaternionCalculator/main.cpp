#include <iostream>
#include <string>
#include "quaternionCalculator.h"

// https://mylearn.torrens.edu.au/courses/13117/files/6678336?wrap=1
// https://mylearn.torrens.edu.au/courses/13117/files/6678339?wrap=1

int main()
{

	Quaternion::ParseFromString("1+2i+3j+4k").Print();
	Quaternion::ParseFromString("2-1i+1j-2k").Print();

	return 0;
}