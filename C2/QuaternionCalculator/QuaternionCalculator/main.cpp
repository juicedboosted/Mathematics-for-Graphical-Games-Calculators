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
	Quaternion quaternion1;
	Quaternion quaternion2;
	float scalar = 0.0f;
	ParseQuestionFile("./Quaternion.txt", quaternion1, quaternion2, scalar);

	// Print the initially loaded data
	std::cout << "Loaded data from file:" << std::endl;
	std::cout << "First quaternion:\t" << quaternion1 << std::endl;
	std::cout << "Second quaternion:\t" << quaternion2 << std::endl;
	std::cout << "Scalar:\t\t\t" << scalar << std::endl;

	std::cout << std::endl << std::endl << std::endl;

	// Plussing and minusing
	std::cout << quaternion1 << " + " << quaternion2 << " = " << quaternion1.Plus(quaternion2) << std::endl;
	std::cout << quaternion1 << " - " << quaternion2 << " = " << quaternion1.Minus(quaternion2) << std::endl;

	// Timesing and dividing
	std::cout << quaternion1 << " * " << quaternion2 << " = " << quaternion1.Times(quaternion2) << std::endl;
	std::cout << quaternion1 << " * " << scalar << " = " << quaternion1.Times(scalar) << std::endl;
	std::cout << quaternion1 << " / " << scalar << " = " << quaternion1.Divide(scalar) << std::endl;

	// Other stuff idk
	std::cout << "Dot product of " << quaternion1 << " and " << quaternion2 << " = " << quaternion1.GetDotProduct(quaternion2) << std::endl;
	std::cout << "Magnitude of " << quaternion1 << " = " << quaternion1.GetMagnitude() << std::endl;
	
	// Other other stuff
	std::cout << "Conjugate of " << quaternion1 << " = " << quaternion1.GetConjugate() << std::endl;
	std::cout << quaternion1 << " transformed around " << quaternion2 << " = " << quaternion1.Transform(quaternion2) << std::endl;
	std::cout << "Inverse of " << quaternion1 << " = " << quaternion1.GetInverse() << std::endl;

	
	return 0;
}