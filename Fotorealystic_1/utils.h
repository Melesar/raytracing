#pragma once

#include <string>
#include "vector3.h"
#include "ray.h"

namespace utils
{
	void replace(std::string& str, const std::string& pattern, const std::string& sub);
	Vector3 reflect(const Vector3& direction, const Vector3& normal);
	Ray shiftedRay(const Vector3& origin, const Vector3& direction);

	void createCoordnateSystem(const Vector3& normal, Vector3& Nt, Vector3& Nb);

	Vector3 transformHemisphere(const Vector3& hemisphereSample, const Vector3& normal);
	Vector3 sampleHemisphere(double r1, double r2, int power);
	Vector3 sampleHemisphere(double r1, double r2, const Vector3& normal, const Vector3& Nt, const Vector3& Nb);

	const double Pi = 3.1415;
	const double DoublePi = 2.0 * Pi;
	const double InvPi = 1.0 / Pi;
	const double InvDoublePi = 1.0 / DoublePi;
}