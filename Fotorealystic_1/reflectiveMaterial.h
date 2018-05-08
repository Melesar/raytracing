#pragma once

#include "material.h"

class ReflectiveMaterial : public Material
{

public:


	bool sendSecondaryRay(const Light& light, const Intersection& intersec, Ray& secondaryRay) override;
	Color illuminateDirectly(const Light& light, const Intersection& intersec) override;
	Color illuminateIndirectly(const Scene& scene, const Intersection& intersec, int numSamples) override;

	void print(std::ostream& stream) const override;
	bool getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay) override;
};