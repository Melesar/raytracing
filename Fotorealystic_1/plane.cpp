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
	intersection.hitNormal = getNormal();
	intersection.viewDirection = ray.getDirection();
	intersection.object = this;
	intersection.material = getMaterial();

	calculateUVs(intersection);

	return true;
}

void Plane::print(std::ostream & stream) const
{
	stream << "Point: " << point << ", " << "normal: " << normal;
}

void Plane::calculateUVs(Intersection & intersection)
{
	Material* mat = getMaterial();
	Vector3 intersectionPoint = intersection.point;

	double u = abs(intersectionPoint.x - point.x) / mat->getResolutionX();
	double v = abs(intersectionPoint.z - point.z) / mat->getResolutionY();

	intersection.u = u - (int)u;
	intersection.v = v - (int)v;
}
