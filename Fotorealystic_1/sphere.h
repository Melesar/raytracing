#pragma once

#include "vector3.h"
#include "object.h"

class Ray;

class Sphere : public Object
{
	Vector3 center;
	double radius;

public:

	Sphere(const Vector3& center, double radius) : center(center), radius(radius) {}

	Vector3 getCenter() const { return center; }
	double getRadius() const { return radius; }


	bool intersects(const Ray& ray, Intersection& intersection) override;
	void onPreRender() override {}

protected:

	virtual void print(std::ostream& stream) const;

private:

	void calculateUVs(Intersection& intersection) const;
};