#pragma once

#include "object.h"
#include "vector3.h"

class Ray;
class Intersection;

struct Triangle : public Object
{
	Vector3 v0, v1, v2;

	Triangle(const Vector3& v0 = Vector3(), const Vector3& v1 = Vector3(), const Vector3& v2 = Vector3())
		: v0(v0), v1(v1), v2(v2) 
	{
	}

	bool intersects(const Ray& ray, Intersection& intersection);

	bool inOutCheck(const Vector3& vertex, const Vector3& point, const Vector3& normal);
	Vector3 getNormal(const Vector3& position);
};