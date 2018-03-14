#include "ray.h"

Vector3 Ray::getPoint(double distance) const
{
	return origin + distance * direction;
}