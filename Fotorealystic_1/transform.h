#pragma once

#include "vector3.h"
#include "matrix4x4.h"

class Transform
{
public:
	Transform(const Vector3& pos = Vector3(), const Vector3& rot = Vector3(),
		const Vector3& scale = Vector3(1, 1, 1))
		: pos(pos), rot(rot), scale(scale) {}

	Matrix4x4 getModelMatrix() const;

	Vector3 forward();
	Vector3 up();
	Vector3 left();

	Vector3& getPosition()
	{
		return pos;
	}

	void setPosition(const Vector3& newPosition)
	{
		pos = newPosition;
	}

	Vector3& getRotation()
	{
		return rot;
	}

	void setRotation(const Vector3& newRotation)
	{
		rot = newRotation;
	}

	Vector3& getScale()
	{
		return scale;
	}

	void setScale(const Vector3& newScale)
	{
		scale = newScale;
	}

private:
	Vector3 pos;
	Vector3 rot;
	Vector3 scale;


	Matrix4x4 rotationMatrix() const;
	Matrix4x4 translationMatrix() const;
	Matrix4x4 scaleMatrix() const;
};

