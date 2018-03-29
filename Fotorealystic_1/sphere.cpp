#include "sphere.h"
#include "ray.h"

bool Sphere::intersects(const Ray& ray, Intersection& intersection)
{
	Vector3 d = ray.getDirection();
	Vector3 v = ray.getOrigin() - center;
	double b = d.dot(v);
	
	double descr = b * b - d.dot(d) * (v.dot(v) - radius * radius);

	if (descr < 0) {
		return false;
	}

	intersection.object = this;

	descr = sqrt(descr);

	if (descr == 0) {
		intersection.point = ray.getPoint(-b);
		intersection.distance = -b;
	} else {
		double t1 = -b + descr;
		double t2 = -b - descr;

		double distance = t1 < t2 ? t1 : t2;
		intersection.point = ray.getPoint(distance);
		intersection.distance = distance;
	}

	intersection.hitNormal = (intersection.point - center).normalized();

	return true;
}