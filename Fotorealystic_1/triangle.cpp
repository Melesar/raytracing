#include "triangle.h"
#include "ray.h"
#include "plane.h"

bool Triangle::intersects(const Ray & ray, Intersection & intersection)
{
	Vector3 N = getNormal(Vector3());

	if (ray.getDirection().dot(N) < 0.001) {
		return false;
	}

	Plane p(N, v0.pos);
	Intersection planeIntersec;
	if (!p.intersects(ray, planeIntersec)) {
		return false;
	}

	Vector3 P = planeIntersec.point;
	
	bool isIntersection =
		inOutCheck(v1.pos - v0.pos, P - v0.pos, N) &&
		inOutCheck(v2.pos - v1.pos, P - v1.pos, N) &&
		inOutCheck(v0.pos - v2.pos, P - v2.pos, N);

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
	Vector3 v01 = v1.pos - v0.pos;
	Vector3 v02 = v2.pos - v1.pos;
	return v01.cross(v02);
}
