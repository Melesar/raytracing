#pragma once

#include "material.h"

class ReflectiveMaterial : public Material
{

public:

	virtual bool getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay) override;
};