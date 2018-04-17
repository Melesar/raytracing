#pragma once

#include "material.h"

class ReflectiveMaterial : public Material
{

public:


	void print(std::ostream& stream) const override;
	bool getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay) override;
};