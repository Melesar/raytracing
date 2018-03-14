#pragma once

#include "material.h"
#include "vector3.h"

class Ray;
class Object;

struct Intersection
{
	Vector3 point;
	Object* object;
};

class Object
{
	Material material;

public:

	Object(const Material& material = Material()) : material(material) {}

	Material& getMaterial();
	virtual Vector3 getNormal(const Vector3& position) = 0;

	virtual bool intersects(const Ray& ray, Intersection& intersection) = 0;
};