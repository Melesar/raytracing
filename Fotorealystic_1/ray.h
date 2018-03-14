#pragma once

#include "vector3.h"

class Ray
{
	Vector3 origin, direction;

public:
	Ray(const Vector3& origin = Vector3(), const Vector3& direction = Vector3(0, 0, -1)) 
		: origin(origin), direction(direction.normalized()) {}

	Vector3 getOrigin() const { return origin; }
	Vector3 getDirection() const { return direction; }

	Vector3 getPoint(double distance) const;
};