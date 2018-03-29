#pragma once

#include "Vector3.h"

#include <limits>

class Ray;

struct BoundingBox
{
	Vector3 max, min;


	BoundingBox(const Vector3& max, const Vector3& min)
		: max(max), min(min) {}

	BoundingBox()
	{
		double max = std::numeric_limits<double>::max();
		double min = std::numeric_limits<double>::min();

		this->max = Vector3(min, min, min);
		this->min = Vector3(max, max, max);
	}

	bool isIntersects(const Ray& ray) const;
};