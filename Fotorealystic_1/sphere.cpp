#include "sphere.h"
#include "ray.h"

#include "utils.h"

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
	intersection.material = &getMaterial();

	calculateUVs(intersection);

	return true;
}

void Sphere::calculateUVs(Intersection & intersection) const
{
	Vector3 hitPoint = intersection.point;
	Vector3 center = this->center;

	Vector3 localPoint = (hitPoint - center).normalized();

	double theta = acos(localPoint.y);
	double phi = atan2(localPoint.x, localPoint.z);

	if (phi < 0) {
		phi += Utils::DoublePi;
	}

	static int debugOutputs;

	intersection.u = phi * Utils::InvDoublePi;
	intersection.v = 1.0 - theta * Utils::InvPi;
}
