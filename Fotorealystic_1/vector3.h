#pragma once

#include <iostream>


struct Vector3
{
	double x, y, z;

	Vector3(double x, double y, double z) : x(x), y(y), z(z) {}
	Vector3() : x(0), y(0), z(0) {}

	double magnitude() const;
	double distanceTo(const Vector3& other) const;
	Vector3 normalized() const;

	double dot(const Vector3& other) const;
	Vector3 cross(const Vector3& other) const;

	friend Vector3 operator + (Vector3 left, const Vector3& right);
	Vector3& operator += (const Vector3& addition);

	friend Vector3 operator - (Vector3 left, const Vector3& right);
	Vector3& operator -= (const Vector3& substruction);

	Vector3 operator * (double value) const;
	friend Vector3 operator * (double value, const Vector3& vect);

	Vector3 operator / (double value) const;

	friend std::ostream& operator << (std::ostream& stream, const Vector3& vect);

	static Vector3 lerp(const Vector3& v1, const Vector3& v2, double t)
	{
		if (t <= 0) {
			return v1;
		}

		if (t >= 1) {
			return v2;
		}

		return v1 + (v2 - v1) * t;
	}
};