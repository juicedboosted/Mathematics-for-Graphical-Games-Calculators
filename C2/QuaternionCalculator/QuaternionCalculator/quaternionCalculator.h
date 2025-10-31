#pragma once

#include <string>

class Quaternion
{
public:
	// TODO: Maybe switch to getters/setters if we're not allowed this
	float X;
	float Y;
	float Z;
	float W;

	Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	static Quaternion ParseFromString(std::string stringifiedQuaternion); // M
	static std::string AsString(const Quaternion& quaternion); // M

	Quaternion Plus(Quaternion& other); // M
	Quaternion Minus(Quaternion& other); // M

	Quaternion Times(const Quaternion& other); // M
	Quaternion Times(float scalar); // M
	Quaternion Divide(float scalar); // M

	float GetDotProduct(Quaternion& other); // M
	Quaternion GetConjugate(); // J
	Quaternion Transform(Quaternion& other); // J
	Quaternion GetInverse(); // J
	float GetMagnitude(); // J

	void Print(); // M

private:
	// TODO: Put in a utils class
	static bool RemoveIfEndsWith(std::string& string, std::string ending); // M
};

std::ostream& operator<<(std::ostream& stream, const Quaternion& quaternion);