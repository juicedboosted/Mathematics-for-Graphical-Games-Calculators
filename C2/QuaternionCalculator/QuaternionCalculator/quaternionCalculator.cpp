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
	for (int i = stringifiedQuaternion.length() - 1; i >= 0; i--)
	{
		char& token = stringifiedQuaternion[i];

		// Check for if we've finished a component
		if (token == '+' || token == '-' || i == 0)
		{
			// Special case for the last character
			if (i == 0)
			{
				currentComponent = token + currentComponent;
				newQuaternion.W = std::stof(currentComponent);
			}

			// Set the X, Y, and Z
			if (RemoveIfEndsWith(currentComponent, "i")) newQuaternion.X = std::stof(currentComponent);
			else if (RemoveIfEndsWith(currentComponent, "j")) newQuaternion.Y = std::stof(currentComponent);
			else if (RemoveIfEndsWith(currentComponent, "k")) newQuaternion.Z = std::stof(currentComponent);

			// Clear the component for the next one
			currentComponent = "";
		}
		else
		{
			// Add the token to the front of the current
			// component since we're looping through backwards
			currentComponent = token + currentComponent;
		}
	}

	return newQuaternion;
}

void Quaternion::Print()
{
	std::cout << "{ " << X << ", " << Y << ", " << Z << ", " << W << " }\n";
}



// TODO: Put in a utils class
bool Quaternion::RemoveIfEndsWith(std::string& string, std::string ending)
{
	// The ending must be able to 'fit' inside
	// the string it's being searched for in
	if (ending.length() > string.length()) return false;
 
	// 'trim' the string and check for if
	// the end string is in it
	bool endsWith = (string.compare(
		string.length() - ending.length(),
		ending.length(),
		ending
	) == 0);

	// If it ends with the thing then remove it
	if (endsWith) string.pop_back();
	return endsWith;
}