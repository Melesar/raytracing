#include "parser.h"
#include <fstream>
#include <iostream>
#include <sstream>


void Parser::parse(const std::string & fileName, std::vector<Triangle>& triangles)
{
	std::ifstream file(fileName.c_str());
	std::string s;

	std::vector<Vector3> verticies, uvs, normals;
	while (std::getline(file, s)) {
		std::string token;
		std::stringstream sstream(s);

		sstream >> token;
		if (token == "v") {
			verticies.push_back(getVertex(sstream));
		} else if (token == "vt") {
			uvs.push_back(getUV(sstream));
		} else if (token == "vn") {
			normals.push_back(getNormal(sstream));
		} else if (token == "f") {
			parseFace(sstream, triangles, verticies, uvs, normals);
			//triangles.push_back(getTriangle(sstream, verticies, uvs, normals));
		}
	}
}

Vector3 Parser::getVertex(std::istream & stream)
{
	Vector3 result;
	stream >> result.x >> result.y >> result.z;

	return result;
}

Vector3 Parser::getUV(std::istream & stream)
{
	Vector3 uv;
	stream >> uv.x >> uv.y;

	return uv;
}

Vector3 Parser::getNormal(std::istream & stream)
{
	Vector3 normal = getVertex(stream);
	return normal.normalized();
}

Triangle Parser::getTriangle(std::stringstream & stream, const std::vector<Vector3>& verticies, const std::vector<Vector3>& uvs, const std::vector<Vector3>& normals)
{
	Triangle t;

	try	{
		t.v0 = getVertex(stream, verticies, uvs, normals);
		t.v1 = getVertex(stream, verticies, uvs, normals);
		t.v2 = getVertex(stream, verticies, uvs, normals);
	} catch (const int& err) {
		if (err == InvalidValue) {
			std::cout << "Failed to parse face " << stream.str() << std::endl;
		}
	}
	

	return t;
}


Vertex Parser::getVertex(std::istream & stream, const std::vector<Vector3>& verticies, const std::vector<Vector3>& uvs, const std::vector<Vector3>& normals)
{
	Vertex v;

	std::string vertString;
	stream >> vertString;

	char delim = '/';
	int pos = 0;
	int vectorIndex = 0;
	while (pos != std::string::npos) {
		pos = vertString.find('/');

		try	{
			int index = std::stoi(vertString.substr(0, pos)) - 1;
			if (vectorIndex == 0) {
				v.pos = verticies.at(index);
			} else if (vectorIndex == 1) {
				v.uv = uvs.at(index);
			} else if (vectorIndex == 2) {
				v.normal = normals.at(index);
			}
		} catch (const std::invalid_argument&)	{
		} catch (const std::out_of_range&) {
			throw InvalidValue;
		}

		vertString.erase(0, pos + 1);
		vectorIndex += 1;
	}

	return v;
}

void Parser::parseFace(std::stringstream & stream, std::vector<Triangle>& triangles, const std::vector<Vector3>& verticies, const std::vector<Vector3>& uvs, const std::vector<Vector3>& normals)
{
	try {
		std::vector<Vertex> faceVerticies;
		while (!stream.eof()) {
			faceVerticies.push_back(getVertex(stream, verticies, uvs, normals));
		}

		if (faceVerticies.size() < 3) {
			throw InvalidValue;
		}

		int trisCount = faceVerticies.size() - 2;
		for (size_t i = 0; i < trisCount; i++) {
			Triangle t;
			t.v0 = faceVerticies.at(0);
			t.v1 = faceVerticies.at(i + 1);
			t.v2 = faceVerticies.at(i + 2);

			triangles.push_back(t);
		}

	}
	catch (const int& err) {
		if (err == InvalidValue) {
			std::cout << "Failed to parse face " << stream.str() << std::endl;
		}
	}
}
