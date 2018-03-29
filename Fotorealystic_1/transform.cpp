#include "Transform.h"


Matrix4x4 Transform::getModelMatrix() const
{
	return translationMatrix() * rotationMatrix() * scaleMatrix();
}

Vector3 Transform::forward()
{
	Vector4 result = rotationMatrix() * Vector4(0, 0, -1, 0);
	return Vector3(result.x, result.y, result.z);
}

Vector3 Transform::up()
{
	Vector4 result = rotationMatrix() * Vector4(0, 1, 0, 0);
	return Vector3(result.x, result.y, result.z);
}

Vector3 Transform::left()
{
	Vector4 result = rotationMatrix() * Vector4(1, 0, 0, 0);
	return Vector3(result.x, result.y, result.z);
}

Matrix4x4 Transform::rotationMatrix() const
{
	return Matrix4x4::rotate(rot);
}

Matrix4x4 Transform::translationMatrix() const
{
	Matrix4x4 m;

	m.matrix[0][0] = m.matrix[1][1] = m.matrix[2][2] = m.matrix[3][3] = 1;
	m.matrix[0][3] = pos.x;
	m.matrix[1][3] = pos.y;
	m.matrix[2][3] = pos.z;

	return m;
}

Matrix4x4 Transform::scaleMatrix() const
{
	Matrix4x4 m;

	m.matrix[0][0] = scale.x;
	m.matrix[1][1] = scale.y;
	m.matrix[2][2] = scale.z;
	m.matrix[3][3] = 1;

	return m;
}
