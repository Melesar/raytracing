#pragma once

#include <iostream>

struct Vector4
{
	double x, y, z, w;

	Vector4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}
	Vector4(int index, double value);
	Vector4() : x(0), y(0), z(0), w(0) {}

	void setIndex(int index, double value);
	double getIndex(int index);

	double magnitude() const;
	Vector4 normalized() const;

	double dot(const Vector4& other) const;
	Vector4 cross(const Vector4& other) const;

	friend Vector4 operator + (Vector4 left, const Vector4& right);
	Vector4& operator += (const Vector4& addition);

	friend Vector4 operator - (Vector4 left, const Vector4& right);
	Vector4& operator -= (const Vector4& substruction);

	Vector4 operator * (double value) const;
	friend Vector4 operator * (double value, const Vector4& vect);

	Vector4 operator / (double value) const;

	friend std::ostream& operator << (std::ostream& stream, const Vector4& vect);
};