#include "vector3.h"

std::ostream& operator << (std::ostream& stream, const Vector3& vect)
{
	stream << "(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
	return stream;
}

double Vector3::dot(const Vector3& other) const 
{
	return other.x * x + other.y * y + other.z * z;
}

Vector3 Vector3::cross(const Vector3 & other) const
{
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	);
}

Vector3& Vector3::operator += (const Vector3& addition)
{
	x += addition.x;
	y += addition.y;
	z += addition.z;

	return *this;
}

Vector3 operator + (Vector3 left, const Vector3& right)
{
	left += right;
	return left;
}

Vector3& Vector3::operator -= (const Vector3& substruction)
{
	x -= substruction.x;
	y -= substruction.y;
	z -= substruction.z;

	return *this;
}

Vector3 operator - (Vector3 left, const Vector3& right)
{
	left -= right;
	return left;
}

Vector3 Vector3::operator * (double value) const
{
	Vector3 result;
	result.x = x * value;
	result.y = y * value;
	result.z = z * value;

	return result;
}

Vector3 Vector3::operator/(double value) const
{
	return Vector3(x / value, y / value, z / value);
}

Vector3 operator * (double value, const Vector3& vect)
{
	return vect * value;
}

double Vector3::magnitude() const
{
	double m = x * x + y * y + z * z;
	return sqrt(m);
}

double Vector3::distanceTo(const Vector3 & other) const
{
	return (*this - other).magnitude();
}

Vector3 Vector3::normalized() const
{
	return (*this) / magnitude();
}
