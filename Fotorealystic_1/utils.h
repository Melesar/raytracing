#pragma once

#include <string>
#include "vector3.h"

namespace Utils
{
	void replace(std::string& str, const std::string& pattern, const std::string& sub);
	Vector3 reflect(const Vector3& direction, const Vector3& normal);

	const double Pi = 3.1415;
	const double DoublePi = 2.0 * Pi;
	const double InvPi = 1.0 / Pi;
	const double InvDoublePi = 1.0 / DoublePi;
}