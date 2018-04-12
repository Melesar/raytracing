#pragma once

#include "transform.h"
#include "color.h"
#include <random>


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

class PointLight : public Light
{
	Vector3 position;

public:

	Vector3 getDirectionAt(const Vector3& point) const;
	double getIntensityAt(const Vector3& point) const;

	PointLight (const Vector3& position, double intensity = 1.0) 
		: Light(intensity), position(position) {}

};

class AreaLight : public Light
{
	Vector3 position;
	double radius;

	std::uniform_real_distribution<double> distribution;

public:

	Vector3 getDirectionAt(const Vector3& point) const;
	double getIntensityAt(const Vector3& point) const;

	AreaLight(const Vector3& position, double radius, double intensity = 5.0)
		: Light(intensity), position(position), radius (radius) 
	{ 
		std::random_device rd;
		std::mt19937 gen = std::mt19937(rd());
	}

private:

	Vector3 getPoint() const;
};