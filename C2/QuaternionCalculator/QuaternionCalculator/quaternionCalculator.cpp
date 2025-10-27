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

	// Loop over every character in the string and
	// figure out what bit is what component
	std::string currentComponent;
	for (int i = 1; i < stringifiedQuaternion.length(); i++)
	{
		char& token = stringifiedQuaternion[i];
		char& previousToken = stringifiedQuaternion[i - 1];

		// Check for if we're looking at a 'control character'
		if (token == '+')
		{
			// If there was no previous component
			// then use the previous token
			if (currentComponent.empty()) currentComponent += previousToken;

			// Get the component as a number
			float value = std::stof(currentComponent);

			// Save our component to the correct value
			if (previousToken == 'i') newQuaternion.X = value;
			if (previousToken == 'j') newQuaternion.Y = value;
			if (previousToken == 'k') newQuaternion.Z = value;
			else newQuaternion.W = value;

			// Clear the component for the next one
			currentComponent.clear();
		}
		else
		{
			// Add the new symbol/number to the component
			currentComponent += previousToken;
		}		
	}

	return newQuaternion;
}

void Quaternion::Print()
{
	std::cout << "{ " << X << ", " << Y << ", " << Z << ", " << W << " }\n";
}