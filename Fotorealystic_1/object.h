#pragma once

#include "material.h"
#include "vector3.h"

class Ray;
class Object;

struct Intersection
{
	Vector3 point;
	Object* object;
	Material* material;

	Vector3 hitNormal;
	double distance;
	double u, v;
};

class Object
{
protected:

	Material material;

public:

	Object(const Material& material = Material()) : material(material) {}

	virtual Material& getMaterial();
	virtual bool intersects(const Ray& ray, Intersection& intersection) = 0;
	virtual void onPreRender() = 0;
};