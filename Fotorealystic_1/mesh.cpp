#include "mesh.h"
#include "objParser.h"
#include "ray.h"
#include "transform.h"

#include <limits>
#include <algorithm>
#include <iostream>

Mesh::Mesh(const std::string & fileName)
{
	transform = new Transform();
	triangles = new std::vector<Triangle>();

	ObjParser p;
	p.parse(fileName, *triangles);
	calculateAABB();
}

Mesh::~Mesh()
{
	triangles->clear();
	delete triangles;
}


bool Mesh::intersects(const Ray & ray, Intersection & intersection)
{
	if (!aabb.isIntersects(ray)) {
		return false;
	}

	Material* material;
	Vector3 nearestIntesection, hitNormal;
	double u, v;
	double nearestDistance = std::numeric_limits<double>::infinity();
	bool isIntersection = false;
	for (int i = 0; i < triangles->size(); ++i) {
		Triangle t = triangles->at(i);
		Intersection tIntersec;
		if (t.intersects(ray, tIntersec)) {
			isIntersection = true;
			double distance = tIntersec.distance;
			if (distance < nearestDistance) {
				nearestDistance = distance;
				nearestIntesection = tIntersec.point;
				hitNormal = tIntersec.hitNormal;
				u = tIntersec.u;
				v = tIntersec.v;
				material = tIntersec.material;
			}
		}
	}

	if (!isIntersection) {
		return false;
	}

	intersection.object = this;
	intersection.point = nearestIntesection;
	intersection.hitNormal = hitNormal;
	intersection.distance = nearestDistance;
	intersection.material = material;
	intersection.u = u;
	intersection.v = v;

	return true;
}

void Mesh::onPreRender()
{
	applyTransform();
}

void Mesh::print(std::ostream & stream) const
{
	stream << "Triangles count: " << triangles->size();
}

void Mesh::applyTransform()
{
	Matrix4x4 modelMatrix = transform->getModelMatrix();
	Matrix4x4 rotationMatrix = Matrix4x4::rotate(transform->getRotation());

	for (int i = 0; i < triangles->size(); ++i) {
		Triangle &t = triangles->at(i);

		t.v0.pos = modelMatrix * t.v0.pos;
		t.v1.pos = modelMatrix * t.v1.pos;
		t.v2.pos = modelMatrix * t.v2.pos;

		t.v0.normal = rotationMatrix * t.v0.normal;
		t.v1.normal = rotationMatrix * t.v1.normal;
		t.v2.normal = rotationMatrix * t.v2.normal;
	}

	aabb.max = modelMatrix * aabb.max;
	aabb.min = modelMatrix * aabb.min;
}

void Mesh::calculateAABB()
{
	int trisNum = triangles->size();
	for (int i = 0; i < trisNum; ++i) {
		Triangle t = triangles->at(i);

		processVertex(t.v0);
		processVertex(t.v1);
		processVertex(t.v2);
	}
}

void Mesh::processVertex(const Vertex & v)
{
	Vector3 vPos = v.pos;

	aabb.min.x = std::min(vPos.x, aabb.min.x);
	aabb.min.y = std::min(vPos.y, aabb.min.y);
	aabb.min.z = std::min(vPos.z, aabb.min.z);

	aabb.max.x = std::max(vPos.x, aabb.max.x);
	aabb.max.y = std::max(vPos.y, aabb.max.y);
	aabb.max.z = std::max(vPos.z, aabb.max.z);
}
