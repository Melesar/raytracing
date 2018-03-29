#include "boundingbox.h"
#include "ray.h"

#include <algorithm>

bool BoundingBox::isIntersects(const Ray & ray) const
{
	Vector3 origin = ray.getOrigin();
	Vector3 inverseDirection = ray.getInverseDirection();

	double tx1 = (min.x - origin.x) * inverseDirection.x;
	double tx2 = (max.x - origin.x) * inverseDirection.x;

	double tmin = std::min(tx1, tx2);
	double tmax = std::max(tx1, tx2);

	double ty1 = (min.y - origin.y) * inverseDirection.y;
	double ty2 = (max.y - origin.y) * inverseDirection.y;

	tmin = std::max(tmin, std::min(ty1, ty2));
	tmax = std::min(tmax, std::max(ty1, ty2));

	double tz1 = (min.z - origin.z) * inverseDirection.z;
	double tz2 = (max.z - origin.z) * inverseDirection.z;

	tmin = std::max(tmin, std::min(tz1, tz2));
	tmax = std::min(tmax, std::max(tz1, tz2));

	return tmax >= tmin;
}
