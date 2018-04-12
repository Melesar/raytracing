#pragma once

#include "transform.h"
#include "color.h"
#include <random>
#include <time.h>

class Vector3;

class Light
{
public:

	Color color;

	Light(double intensity = 1.0) : transform(Transform()), intensity (intensity), color (Color(1, 1, 1)) {}

	virtual Vector3 getDirectionAt(const Vector3& point) const = 0;
	virtual double getIntensityAt(const Vector3& point) const = 0;

	Transform& getTransform() { return transform; };

	friend std::ostream& operator << (std::ostream& stream, const Light& light)
	{
		light.print(stream);
		return stream;
	}

protected:

	virtual void print(std::ostream& stream) const = 0;

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

protected:

	void print(std::ostream& stream) const;
};

class PointLight : public Light
{
	Vector3 position;

public:

	Vector3 getDirectionAt(const Vector3& point) const;
	double getIntensityAt(const Vector3& point) const;

	PointLight (const Vector3& position, double intensity = 1.0) 
		: Light(intensity), position(position) {}

protected:

	void print(std::ostream& stream) const;
};

class AreaLight : public Light
{
	Vector3 min, max;

public:

	Vector3 getDirectionAt(const Vector3& point) const;
	double getIntensityAt(const Vector3& point) const;

	AreaLight(const Vector3& min, const Vector3& max, double intensity = 5.0)
		: Light(intensity), min(min), max(max)
	{ 
		srand(unsigned(time(NULL)));
	}

private:

	Vector3 getPoint() const;

protected:

	void print(std::ostream& stream) const;
};