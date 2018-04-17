#include "emissiveMaterial.h"

void EmissiveMaterial::print(std::ostream& stream) const
{
	stream << "Emissive material: color = " << color << ", intensity = " << intensity;
}

bool EmissiveMaterial::getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay)
{
	color = this->color * intensity;
	return false;
}
