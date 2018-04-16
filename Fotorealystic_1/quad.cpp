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
	intersection.material = &getMaterial();
	intersection.u = u;
	intersection.v = v;

	return true;
	/*Vector3 d = ray.getDirection();

	//Check if ray is parallel to the quad
	double aCos = d.dot(normal);
	if (abs(aCos) < 1e-6) {
		return false;
	}

	double distance = -normal.dot(ray.getOrigin() - v1) / aCos;
	if (distance < 0) {
		return false;
	}

	Vector3 point = ray.getPoint(distance);
	Vector3 intP = point - ray.getOrigin();

	Vector3 v21 = v2 - v1;
	Vector3 v31 = v3 - v1;

	double width = v21.magnitude();
	double height = v31.magnitude();
	
	double u = intP.dot(v21);
	double v = intP.dot(v31);

	bool isIntersects =
		u >= 0 && u < width &&
		v >= 0 && v < height;

	if (!isIntersects) {
		return false;
	}

	intersection.point = point;
	intersection.hitNormal = normal;
	intersection.distance = distance;
	intersection.object = this;
	intersection.material = &getMaterial();
	intersection.u = u / width;
	intersection.v = v / height;

	return true;*/
}

void Quad::onPreRender()
{
}

void Quad::print(std::ostream & stream) const
{
}
