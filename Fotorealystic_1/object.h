#pragma once

#include "phongMaterial.h"
#include "material.h"
#include "vector3.h"

#include <ostream>

class Ray;
class Object;

struct Intersection
{
	Vector3 point;
	Object* object;
	Material* material;

	Vector3 hitNormal;
	Vector3 viewDirection;
	double distance;
	double u, v;
};

class Object
{
protected:

	Material* material;

public:

	Object(Material* material = new PhongMaterial()) : material(material) {}
	~Object();

	virtual void setMaterial(Material* newMaterial);
	virtual Material* getMaterial();
	virtual bool intersects(const Ray& ray, Intersection& intersection) = 0;
	virtual void onPreRender() = 0;

	friend std::ostream& operator << (std::ostream& stream, const Object& obj)
	{
		obj.print(stream);
		return stream;
	}

protected:

	virtual void print(std::ostream& stream) const = 0;
};