#pragma once

#include "transform.h"
#include "color.h"
#include <random>
#include "printable.h"

class Vector3;
class Scene;

class Light : public Printable
{
public:

	Color color;

	Light(double intensity = 1.0) : transform(Transform()), intensity (intensity), color (Color(1, 1, 1)) {}

	virtual Vector3 getDirectionAt(const Vector3& point) const = 0;
	virtual double getIntensityAt(const Vector3& point) const = 0;
	virtual double shade(const Vector3& point, const Scene& scene) const = 0;

	Transform& getTransform() { return transform; };

	virtual void print(std::ostream& stream) const = 0;

	friend std::ostream& operator << (std::ostream& stream, const Light& light)
	{
		light.print(stream);
		return stream;
	}

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

	virtual double shade(const Vector3 & point, const Scene & scene) const override;

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

	virtual double shade(const Vector3 & point, const Scene & scene) const override;

	PointLight (const Vector3& position, double intensity = 1.0) 
		: Light(intensity), position(position) {}

protected:

	void print(std::ostream& stream) const;

};

