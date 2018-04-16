#pragma once

#include "material.h"

class RefractiveMaterial : public Material
{
	double refractionFactor;

public:

	RefractiveMaterial(double refractionFactor = 1.33) 
		: refractionFactor(refractionFactor) { }

	virtual bool getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay) override;
};
