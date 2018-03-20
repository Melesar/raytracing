#pragma once

#include <vector>

#include "object.h"
#include "triangle.h"

class Mesh : public Object
{
	std::vector<Triangle>* triangles;

public: 

	Mesh() : triangles(new std::vector<Triangle>())  {}
	Mesh(std::vector<Triangle>& triangles) : triangles(&triangles) {}
	Mesh(const std::string& fileName);

	virtual ~Mesh();

	virtual Vector3 getNormal(const Vector3 & position) override;
	virtual bool intersects(const Ray & ray, Intersection & intersection) override;
};
