#include "utils.h"

void utils::replace(std::string & str, const std::string & pattern, const std::string & sub)
{
	int start = str.find(pattern);
	int len = pattern.length();

	while (start != std::string::npos) {
		str.replace(start, len, sub);
		start = str.find(pattern);
	}
}

Vector3 utils::reflect(const Vector3 & direction, const Vector3 & normal)
{
	return (2 * normal.dot(direction) * normal - direction).normalized();
}

Ray utils::shiftedRay(const Vector3& origin, const Vector3& direction)
{
	return Ray(origin + 0.04 * direction, direction);
}

void utils::createCoordnateSystem(const Vector3& normal, Vector3& Nt, Vector3& Nb)
{
	if (std::fabs(normal.x) > std::fabs(normal.y)) {
		Nt = Vector3(normal.z, 0, -normal.x) / sqrtf(normal.x * normal.x + normal.z * normal.z);
	} else {
		Nt = Vector3(0, -normal.z, normal.y) / sqrtf(normal.y * normal.y + normal.z * normal.z);
	}

	Nb = normal.cross(Nt);
}

Vector3 utils::sampleHemisphere(double r1, double r2, const Vector3& normal, const Vector3& Nt, const Vector3& Nb)
{
	float sinTheta = sqrtf(1 - r1 * r1);
	float phi = DoublePi * r2;
	float x = sinTheta * cosf(phi);
	float z = sinTheta * sinf(phi);

	Vector3 localSample = Vector3(x, r1, z);

	return Vector3(
		localSample.x * Nb.x + localSample.y * normal.x + localSample.z * Nt.x,
		localSample.x * Nb.y + localSample.y * normal.y + localSample.z * Nt.y,
		localSample.x * Nb.z + localSample.y * normal.z + localSample.z * Nt.z);
}


