#include "emissiveMaterial.h"

bool EmissiveMaterial::getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay)
{
	color = this->color * intensity;
	return false;
}
