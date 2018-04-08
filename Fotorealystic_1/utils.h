#pragma once

#include <string>

namespace Utils
{
	void replace(std::string& str, const std::string& pattern, const std::string& sub);

	const double Pi = 3.1415;
	const double DoublePi = 2.0 * Pi;
	const double InvPi = 1.0 / Pi;
	const double InvDoublePi = 1.0 / DoublePi;
}