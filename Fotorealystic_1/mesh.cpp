#include "mesh.h"
#include "parser.h"

Mesh::Mesh(const std::string & fileName)
{
	triangles = new std::vector<Triangle>();

	Parser p;
	p.parse(fileName, *triangles);
}

Mesh::~Mesh()
{
	triangles->clear();
	delete triangles;
}

Vector3 Mesh::getNormal(const Vector3 & position)
{
	return Vector3();
}

bool Mesh::intersects(const Ray & ray, Intersection & intersection)
{
	return false;
}
