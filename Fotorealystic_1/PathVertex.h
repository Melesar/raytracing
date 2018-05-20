#pragma once
#include "color.h"
#include "object.h"

class PathVertex
{
public:

	PathVertex(const Color& color, const Intersection& intersection) :
		color(color),
		intersection(intersection)
	{  }

	PathVertex(const Color& color, const Vector3& position) :
		color(color),
		intersection(Intersection{position})
	{
	}

	PathVertex() = default;

	Color color;
	Intersection intersection;
};
