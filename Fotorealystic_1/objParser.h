#pragma once

#include <string>
#include <vector>
#include "vector3.h"
#include "triangle.h"
#include "mesh.h"
#include <map>


class ObjParser
{
public:

	void parse(const std::string& fileName, std::vector<Triangle>& triangles);

	void setCurrentMaterial(std::stringstream &sstream);

	void parseMtl(std::stringstream &sstream);

	~ObjParser();

private:

	const int InvalidValue = -13;

	std::map<std::string, Material*>* materialsMap;
	Material* currentMaterial;

	Vector3 getVertex(std::istream& stream);
	Vector3 getUV(std::istream& stream);
	Vector3 getNormal(std::istream& stream);
	Vertex getVertex (std::istream& stream, const std::vector<Vector3>& verticies, const std::vector<Vector3>& uvs, const std::vector<Vector3>& normals);
	void parseFace(std::stringstream& stream, std::vector<Triangle>& triangles, const std::vector<Vector3>& verticies, const std::vector<Vector3>& uvs, const std::vector<Vector3>& normals);
};