#include <iostream>
#include <string>
#include <fstream>
#include "quaternionCalculator.h"

// https://mylearn.torrens.edu.au/courses/13117/files/6678336?wrap=1
// https://mylearn.torrens.edu.au/courses/13117/files/6678339?wrap=1

void ParseQuestionFile(std::string path, Quaternion& quaternion1,  Quaternion& quaternion2, float& scalar)
{
	// Open the file
	std::ifstream file(path);
	if (file.is_open() == false)
	{
		std::cerr << "issue opening file (check path or something)" << std::endl;
		return;
	}

	// Loop over every line
	std::string line;
	int index = 0;
	while (std::getline(file, line))
	{
		// Get the first quaternion
		if (index == 0) quaternion1 = Quaternion::ParseFromString(line);

		// Get the second quaternion
		if (index == 2) quaternion2 = Quaternion::ParseFromString(line);

		// Get the scalar
		if (index == 4) scalar = std::stof(line);

		index++;
	}

	// Close the file (done)
	file.close(); 
}

int main()
{
	// Load all the data
	Quaternion a;
	Quaternion b;
	float scalar = 0.0f;
	ParseQuestionFile("./Quaternion.txt", a, b, scalar);

	// Print the initially loaded data
	std::cout << "Loaded data from file:" << std::endl;
	std::cout << "a:\t" << a << std::endl;
	std::cout << "b:\t" << b << std::endl;
	std::cout << "Scalar:\t" << scalar << std::endl << std::endl;
	std::cout << std::endl;

	// Print everything
	std::cout << "a + b = " << a.Plus(b) << std::endl;
	std::cout << "a - b = " << a.Minus(b) << std::endl;
	std::cout << "ab = " << a.Times(b) << std::endl;
	std::cout << "ba = " << b.Times(a) << std::endl;
	std::cout << "a.b = " << a.GetDotProduct(b) << std::endl;
	std::cout << "a* = " << a.GetConjugate() << std::endl;
	std::cout << "a^-1 = " << a.GetInverse() << std::endl;
	std::cout << "ta = " << a.Transform(b) << std::endl;
	std::cout << "|a| = " << a.GetMagnitude() << std::endl;
	std::cout << "a * scalar = " << a.Times(scalar) << std::endl;
	std::cout << "a / scalar = " << a.Divide(scalar) << std::endl;

	// Stop the console from closing
	std::cin.get();

	return 0;
}