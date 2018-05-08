#include "emissiveMaterial.h"

bool EmissiveMaterial::sendSecondaryRay(const Light& light, const Intersection& intersec, Ray& secondaryRay)
{
	return false;
}

Color EmissiveMaterial::illuminateDirectly(const Light& light, const Intersection& intersec)
{
	return color * intensity;
}

Color EmissiveMaterial::illuminateIndirectly(const Scene& scene, const Intersection& intersec, int numSamples, int maxBounces)
{
	return Color();
}

void EmissiveMaterial::print(std::ostream& stream) const
{
	stream << "Emissive material: color = " << color << ", intensity = " << intensity;
}

bool EmissiveMaterial::getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay)
{
	color = this->color * intensity;
	return false;
}
