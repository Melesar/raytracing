#include "sphere.h"
#include "ray.h"

Vector3 Sphere::getNormal(const Vector3 & position)
{
	return position - center;
}

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
		return true;
	}

	double t1 = -b + descr;
	double t2 = -b - descr;

	intersection.point = ray.getPoint(t1 < t2 ? t1 : t2);

	return true;
}