#include "quad.h"
#include "ray.h"

#include <iostream>

Quad::Quad(const Vector3& v1, const Vector3& v2, const Vector3& v3)
	: v1(v1), v2(v2), v3(v3)
{
	Vector3 v2v1 = v2 - v1;
	Vector3 v3v1 = v3 - v1;
	normal = v2v1.cross(v3v1).normalized();

	//std::cout << "Normal: " << normal << std::endl;
}

void Quad::invertNormal()
{
	normal = -1 * normal;
}

bool Quad::intersects(const Ray & ray, Intersection & intersection)
{
	//Copy-pasted from triangle.cpp with adjustments to (u + v) range
	Vector3 E1 = v2 - v1;
	Vector3 E2 = v3 - v1;
	Vector3 D = ray.getDirection();
	Vector3 O = ray.getOrigin();

	Vector3 P = D.cross(E2);
	double determinant = E1.dot(P);

	//Ray and triangle are parallel
	if (abs(determinant) < 0.001) {
		return false;
	}

	double invDeterminant = 1.0 / determinant;

	Vector3 T = O - v1;
	double u = T.dot(P) * invDeterminant;

	if (u < 0 || u > 1) {
		return false;
	}

	Vector3 Q = T.cross(E1);
	double v = D.dot(Q) * invDeterminant;

	if (v < 0 || v > 1 || u + v > 2) {
		return false;
	}

	double t = E2.dot(Q) * invDeterminant;

	intersection.object = this;
	intersection.point = ray.getPoint(t);
	intersection.distance = t;
	intersection.hitNormal = normal;
	intersection.viewDirection = D;
	intersection.material = getMaterial();
	intersection.u = u;
	intersection.v = v;

	return true;
}

void Quad::onPreRender()
{
}

void Quad::print(std::ostream & stream) const
{
}
