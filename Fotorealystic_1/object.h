#pragma once

#include "phongMaterial.h"
#include "emissiveMaterial.h"
#include "vector3.h"

#include <ostream>
#include "printable.h"

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

class Object : public Printable
{
protected:

	Material* material;

public:

	Object(Material* material = new PhongMaterial()) : material(material) {}
	virtual ~Object();

	virtual void setMaterial(Material* newMaterial);
	virtual Material* getMaterial();

	virtual bool intersects(const Ray& ray, Intersection& intersection) = 0;
	virtual void onPreRender() = 0;

	friend std::ostream& operator << (std::ostream& stream, const Object& obj)
	{
		obj.print(stream);
		return stream;
	}

	virtual void print(std::ostream& stream) const = 0;

};