#pragma once

#include "vector4.h"
#include "vector3.h"
#include <iostream>
#include <math.h>

class Vector3;

struct Matrix4x4
{
	double matrix[4][4];

	Matrix4x4();

	double trace() const;
	Matrix4x4 inverse();

	Matrix4x4 operator * (double value) const;
	friend Matrix4x4 operator - (Matrix4x4 left, const Matrix4x4& right);
	friend Matrix4x4 operator * (Matrix4x4 left, const Matrix4x4& right);
	friend std::ostream& operator << (std::ostream& stream, const Matrix4x4& matrix);

	Vector4 operator * (const Vector4& vect) const;

private:

	Matrix4x4 decomposeLU() const;

public:

	static Matrix4x4 identity()
	{
		Matrix4x4 E;
		for (int i = 0; i < 4; ++i) {
			E.matrix[i][i] = 1;
		}

		return E;
	}

	static Matrix4x4 rotateX(double angle)
	{
		Matrix4x4 res;
		double s = sin(angle);
		double c = cos(angle);

		res.matrix[1][1] = c;
		res.matrix[1][2] = -s;

		res.matrix[2][1] = s;
		res.matrix[2][2] = c;

		res.matrix[0][0] = res.matrix[3][3] = 1;

		return res;
	}

	static  Matrix4x4 rotateY(double angle)
	{
		Matrix4x4 res;
		double s = sin(angle);
		double c = cos(angle);

		res.matrix[0][0] = c;
		res.matrix[0][2] = s;

		res.matrix[2][0] = -s;
		res.matrix[2][2] = c;

		res.matrix[1][1] = res.matrix[3][3] = 1;

		return res;
	}

	static Matrix4x4 rotateZ(double angle)
	{
		Matrix4x4 res;
		double s = sin(angle);
		double c = cos(angle);

		res.matrix[0][0] = c;
		res.matrix[0][1] = -s;

		res.matrix[1][0] = s;
		res.matrix[1][1] = c;

		res.matrix[2][2] = res.matrix[3][3] = 1;

		return res;
	}

	static Matrix4x4 perspective(double fov, double near, double far, double aspect = 1.0)
	{
		Matrix4x4 m;

		double frustrumDepth = far - near;
		double oneOverDepth = 1.0 / frustrumDepth;

		m.matrix[1][1] = 1.0 / tan(0.5 * fov * 3.14 / 180);
		m.matrix[0][0] = m.matrix[1][1] / aspect;
		m.matrix[2][2] = -far * oneOverDepth;
		m.matrix[2][3] = (-far * near) * oneOverDepth;
		m.matrix[3][2] = -1;
		m.matrix[3][3] = 0;

		return m;
	}

	static Matrix4x4 lookAt(const Vector3 & from, const Vector3 & to, const Vector3 & up)
	{
		Vector3 forward = (to - from).normalized();
		Vector3 upN = up.normalized();
		Vector3 right = upN.cross(forward);

		Matrix4x4 camToWorld;

		camToWorld.matrix[0][0] = right.x;
		camToWorld.matrix[1][0] = right.y;
		camToWorld.matrix[2][0] = right.z;
		camToWorld.matrix[0][1] = upN.x;
		camToWorld.matrix[1][1] = upN.y;
		camToWorld.matrix[2][1] = upN.z;
		camToWorld.matrix[0][2] = forward.x;
		camToWorld.matrix[1][2] = forward.y;
		camToWorld.matrix[2][2] = forward.z;

		camToWorld.matrix[0][3] = from.x;
		camToWorld.matrix[1][3] = from.y;
		camToWorld.matrix[2][3] = from.z;
		camToWorld.matrix[3][3] = 1.0;

		return camToWorld;
	}

	
};

