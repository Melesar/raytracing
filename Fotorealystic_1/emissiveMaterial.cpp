#include "emissiveMaterial.h"
#include "ray.h"

bool EmissiveMaterial::isReflective() const
{
	return false;
}

Ray EmissiveMaterial::sampleReflection(const Intersection& intersection, float& pdf)
{
	return Ray();
}

Color EmissiveMaterial::sampleBSDF(const Intersection& intersection, Ray& bounceRay, double& scatteringPdf)
{
	return Color();
}

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
