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


	bool isReflective() const override;
	Ray sampleReflection(const Intersection& intersection, float& pdf) override;

	bool sendSecondaryRay(const Light& light, const Intersection& intersec, Ray& secondaryRay) override;
	Color illuminateDirectly(const Light& light, const Intersection& intersec) override;
	Color illuminateIndirectly(const Scene& scene, const Intersection& intersec, int numSamples, int maxBounces) override;

	void print(std::ostream& stream) const override;
	bool getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay) override;
};