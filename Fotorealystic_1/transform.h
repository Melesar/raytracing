#pragma once

#include "vector3.h"
#include "matrix4x4.h"

class Transform
{
public:
	Transform(const Vector3& pos = Vector3(), const Vector3& rot = Vector3(),
		const Vector3& scale = Vector3(1, 1, 1))
		: pos(pos), rot(rot), scale(scale) {}

	Matrix4x4 GetModelMatrix() const;

	Vector3 forward();
	Vector3 up();
	Vector3 left();

	Vector3& position()
	{
		return pos;
	}

	void SetPosition(const Vector3& highp_vec3)
	{
		pos = highp_vec3;
	}

	Vector3& rotation()
	{
		return rot;
	}

	void SetRotation(const Vector3& highp_vec3)
	{
		rot = highp_vec3;
	}

	Vector3& scale1()
	{
		return scale;
	}

	void set_scale(const Vector3& highp_vec3)
	{
		scale = highp_vec3;
	}

private:
	Vector3 pos;
	Vector3 rot;
	Vector3 scale;


	Matrix4x4 rotationMatrix() const;
	Matrix4x4 translationMatrix() const;
	Matrix4x4 scaleMatrix() const;
};

