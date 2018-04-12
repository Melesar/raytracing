#include "triangle.h"
#include "ray.h"
#include "plane.h"
#include <math.h>

bool Triangle::intersects(const Ray & ray, Intersection & intersection)
{
	//Moller-Trumbore algorythm
	//Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection

	Vector3 E1 = v1.pos - v0.pos;
	Vector3 E2 = v2.pos - v0.pos;
	Vector3 D = ray.getDirection();
	Vector3 O = ray.getOrigin();

	Vector3 P = D.cross(E2);
	double determinant = E1.dot(P);

	//Ray and triangle are parallel
	if (abs(determinant) < 0.001) {
		return false;
	}

	double invDeterminant = 1.0 / determinant;

	Vector3 T = O - v0.pos;
	double u = T.dot(P) * invDeterminant;

	if (u < 0 || u > 1) {
		return false;
	}

	Vector3 Q = T.cross(E1);
	double v = D.dot(Q) * invDeterminant;

	if (v < 0 || u + v > 1) {
		return false;
	}

	double t = E2.dot(Q) * invDeterminant;

	intersection.object = this;
	intersection.point = ray.getPoint(t);
	intersection.distance = t;
	intersection.hitNormal = (1 - u - v) * v0.normal + u * v1.normal + v * v2.normal;
	intersection.material = &getMaterial();
	intersection.u = (1 - u - v) * v0.uv.x + u * v1.uv.x + v * v2.uv.x;
	intersection.v = (1 - u - v) * v0.uv.y + u * v1.uv.y + v * v2.uv.y;

	return true;
}

double Triangle::inOutCheck(const Vector3 & edge, const Vector3 & point, const Vector3 & normal)
{
	Vector3 C = edge.cross(point);
	return C.dot(normal);
}

Vector3 Triangle::getNormal()
{
	Vector3 v01 = v1.pos - v0.pos;
	Vector3 v02 = v2.pos - v1.pos;
	return v01.cross(v02);
}

void Triangle::setMaterial(Material * material)
{
	triangleMaterial.reset(material);
}

Material & Triangle::getMaterial()
{
	return *triangleMaterial.get();
}
