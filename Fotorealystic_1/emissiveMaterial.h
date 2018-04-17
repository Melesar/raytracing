#pragma once

#include "material.h"
#include "color.h"

class EmissiveMaterial : public Material
{
	Color color;
	double intensity;

public:

	EmissiveMaterial (const Color& color = Color(1, 1, 1), double intensity = 5.0)
		: color(color), intensity(intensity) {}


	void print(std::ostream& stream) const override;
	bool getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay) override;
};