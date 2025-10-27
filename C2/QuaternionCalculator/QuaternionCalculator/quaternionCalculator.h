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

	Quaternion Plus(Quaternion& other); // M
	Quaternion Minus(Quaternion& other); // M
	Quaternion Times(Quaternion& other); // M
	Quaternion Times(float scalar); // M
	float GetDotProduct(Quaternion& other); // M
	Quaternion Conjugate(Quaternion& other);
	Quaternion Transform(Quaternion& other);
	Quaternion Inverse();
	float GetMagnitude();

	void Print(); // M
};