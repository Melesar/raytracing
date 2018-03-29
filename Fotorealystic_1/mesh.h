#pragma once

#include <vector>

#include "object.h"
#include "triangle.h"
#include "boundingbox.h"

class Transform;
class Vertex;

class Mesh : public Object
{
	std::vector<Triangle>* triangles;
	Transform* transform;
	BoundingBox aabb;

public: 

	Mesh(const std::string& fileName);

	Transform* getTransform() { return transform; }

	virtual ~Mesh();

	virtual bool intersects(const Ray & ray, Intersection & intersection) override;
	virtual void onPreRender() override;

private:

	void applyTransform();
	void calculateAABB();
	void processVertex(const Vertex& v);
};
