#pragma once

#include "object.h"
#include "vector3.h"
#include <memory>

class Ray;
class Intersection;

struct Vertex
{
	Vector3 pos;
	Vector3 uv;
	Vector3 normal;

	Vertex() : pos(Vector3()), uv (Vector3()), normal(Vector3())
	{
	}
};

struct Triangle : public Object
{
	Vertex v0, v1, v2;

	Triangle()
	{
		triangleMaterial.reset(new PhongMaterial());
	}

	bool intersects(const Ray& ray, Intersection& intersection);
	Vector3 getNormal();
	void onPreRender() override {}

	void setMaterial(Material* material) override;
	Material* getMaterial() override;

protected:

	virtual void print(std::ostream& stream) const;
	
private:
	std::shared_ptr<Material> triangleMaterial;

	double inOutCheck(const Vector3& vertex, const Vector3& point, const Vector3& normal);
};