#include "triangle.h"
#include "ray.h"
#include "plane.h"

bool Triangle::intersects(const Ray & ray, Intersection & intersection)
{
	Vector3 N = getNormal(Vector3());

	if (ray.getDirection().dot(N) < 0.001) {
		return false;
	}

	Plane p(N, v0);
	Intersection planeIntersec;
	if (!p.intersects(ray, planeIntersec)) {
		return false;
	}

	Vector3 P = planeIntersec.point;
	
	bool isIntersection =
		inOutCheck(v1 - v0, P - v0, N) &&
		inOutCheck(v2 - v1, P - v1, N) &&
		inOutCheck(v0 - v2, P - v2, N);

	if (!isIntersection) {
		return false;
	}

	intersection.object = this;

	return true;
}

bool Triangle::inOutCheck(const Vector3 & edge, const Vector3 & point, const Vector3 & normal)
{
	Vector3 C = edge.cross(point);
	return C.dot(normal) >= 0;
}

Vector3 Triangle::getNormal(const Vector3 & position)
{
	Vector3 v01 = v1 - v0;
	Vector3 v02 = v2 - v1;
	return v01.cross(v02);
}
