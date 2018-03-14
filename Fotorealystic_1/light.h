#pragma once

#include "transform.h"
#include "color.h"

class Vector3;


class Light
{
public:

	Color color;

	Light(double intensity = 1.0) : transform(Transform()), intensity (intensity), color (Color(1, 1, 1)) {}

	virtual Vector3 getDirectionAt(const Vector3& point) const = 0;
	virtual double getIntensityAt(const Vector3& point) const = 0;

	Transform& getTransform() { return transform; };

protected:

	Transform transform;
	double intensity;
};

class DirectionalLight : public Light
{
	Vector3 direction;

public:
	Vector3 getDirectionAt(const Vector3& point) const;
	double getIntensityAt(const Vector3& point) const;

	DirectionalLight(const Vector3& direction, double intensity = 1.0) : Light(intensity), direction(direction.normalized()) {}
};