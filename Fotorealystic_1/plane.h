#pragma once

#include "vector3.h"
#include "object.h"

class Ray;

class Plane : public Object
{
	Vector3 normal, point;

public:

	Plane(const Vector3& normal, const Vector3& point) : normal(normal.normalized()), point(point) {}

	Vector3 getNormal() const { return normal; }
	Vector3 getNormal(const Vector3& position) { return getNormal(); }

	bool intersects(const Ray& ray, Intersection& intersection);
};