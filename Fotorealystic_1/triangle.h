#pragma once

#include "object.h"
#include "vector3.h"

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

	bool intersects(const Ray& ray, Intersection& intersection);
	Vector3 getNormal();
	void onPreRender() override {}
	
private:

	double inOutCheck(const Vector3& vertex, const Vector3& point, const Vector3& normal);
};