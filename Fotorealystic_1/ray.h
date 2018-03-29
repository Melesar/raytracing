#pragma once

#include "vector3.h"

class Ray
{
	Vector3 origin, direction;
	Vector3 invDirection;

public:
	Ray(const Vector3& origin = Vector3(), const Vector3& direction = Vector3(0, 0, -1)) 
		: origin(origin), direction(direction.normalized())
	{
		invDirection.x = 1.0 / direction.x;
		invDirection.y = 1.0 / direction.y;
		invDirection.z = 1.0 / direction.z;

		//invDirection = invDirection.normalized();
	}

	Vector3 getOrigin() const { return origin; }
	Vector3 getDirection() const { return direction; }
	Vector3 getInverseDirection() const { return invDirection; }

	Vector3 getPoint(double distance) const;
};