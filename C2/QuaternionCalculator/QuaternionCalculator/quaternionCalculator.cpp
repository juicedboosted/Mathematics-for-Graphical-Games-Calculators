#include "quaternionCalculator.h"

#include <iostream>
#include <cmath>


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

Quaternion Quaternion::Plus(Quaternion &other)
{
	return Quaternion
	(
		X + other.X,
		Y + other.Y,
		Z + other.Z,
		W + other.W
	);
}

Quaternion Quaternion::Minus(Quaternion &other)
{
	return Quaternion
	(
		X - other.X,
		Y - other.Y,
		Z - other.Z,
		W - other.W
	);
}

Quaternion Quaternion::Times(Quaternion &other)
{
	// TODO: Maybe don't hardcode somehow
	return Quaternion
	(
		(W * other.X) + (X * other.W) + (Y * other.Z) - (Z * other.Y),
		(W * other.Y) - (X * other.Z) + (Y * other.W) + (Z * other.X),
		(W * other.Z) + (X * other.Y) - (Y * other.X) + (Z * other.W),
		(W * other.W) - (X * other.X) - (Y * other.Y) - (Z * other.Z)
	);
}

Quaternion Quaternion::Times(float scalar)
{
	return Quaternion
	(
		X * scalar,
		Y * scalar,
		Z * scalar,
		W * scalar
	);
}

float Quaternion::GetDotProduct(Quaternion &other)
{
	return (
		(X * other.X) +
		(Y * other.Y) +
		(Z * other.Z) +
		(W * other.W)
	);
}

float Quaternion::GetMagnitude()
{
	//? I assume I am allowed to use this square root method
	//? It's the only thing used from <cmath>
	return sqrt(
		(X * X) + 
		(Y * Y) + 
		(Z * Z) + 
		(W * W) 
	);
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