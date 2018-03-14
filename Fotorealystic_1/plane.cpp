#include "plane.h"
#include "ray.h"

bool Plane::intersects(const Ray & ray, Intersection& intersection)
{
	double d = -this->point.dot(normal);
	double np = normal.dot(ray.getOrigin());
	double nd = normal.dot(ray.getDirection());

	double distance = -(d + np) / nd;

	if (distance <= 0) {
		return false;
	}

	intersection.point = ray.getPoint(distance);
	intersection.object = this;

	return true;
}