#include "vector4.h"

std::ostream& operator << (std::ostream& stream, const Vector4& vect)
{
	stream << "(" << vect.x << ", " << vect.y << ", " << vect.z << ", " << vect.w << ")";
	return stream;
}

double Vector4::dot(const Vector4& other) const
{
	return other.x * x + other.y * y + other.z * z + other.w * w;
}

Vector4& Vector4::operator += (const Vector4& addition)
{
	x += addition.x;
	y += addition.y;
	z += addition.z;
	w += addition.w;

	return *this;
}

Vector4 operator + (Vector4 left, const Vector4& right)
{
	left += right;
	return left;
}

Vector4& Vector4::operator -= (const Vector4& substruction)
{
	x -= substruction.x;
	y -= substruction.y;
	z -= substruction.z;
	w -= substruction.w;

	return *this;
}

Vector4 operator - (Vector4 left, const Vector4& right)
{
	left -= right;
	return left;
}

Vector4 Vector4::operator * (double value) const
{
	Vector4 result;
	result.x = x * value;
	result.y = y * value;
	result.z = z * value;
	result.w = w * value;

	return result;
}

Vector4 Vector4::operator/(double value) const
{
	return Vector4(x / value, y / value, z / value, w / value);
}

Vector4 operator * (double value, const Vector4& vect)
{
	return vect * value;
}

Vector4::Vector4(int index, double value)
	: x(0), y(0), z(0), w(0)
{
	setIndex(index, value);
}

void Vector4::setIndex(int index, double value)
{
	switch (index) {
	case 0:
		x = value;
		break;
	case 1:
		y = value;
		break;
	case 2:
		z = value;
		break;
	case 3:
		w = value;
		break;
	}
}

double Vector4::getIndex(int index)
{
	switch (index) {
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}
}

double Vector4::magnitude() const
{
	double m = x * x + y * y + z * z + w * w;
	return sqrt(m);
}

Vector4 Vector4::normalized() const
{
	return (*this) / magnitude();
}
