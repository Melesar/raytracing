#include "reflectiveMaterial.h"
#include "object.h"
#include "vector3.h"
#include "light.h"
#include "utils.h"
#include "ray.h"


bool ReflectiveMaterial::sendSecondaryRay(const Light& light, const Intersection& intersec, Ray& secondaryRay)
{
	Vector3 lightDirection = light.getDirectionAt(intersec.point);
	Vector3 normal = intersec.hitNormal;

	Vector3 rayDirection = -1 * Utils::reflect(lightDirection, normal);

	secondaryRay = Utils::shiftedRay(intersec.point, rayDirection);

	return true;
}

Color ReflectiveMaterial::illuminateDirectly(const Light& light, const Intersection& intersec)
{
	return Color();
}

Color ReflectiveMaterial::illuminateIndirectly(const Scene& scene, const Intersection& intersec, int numSamples, int maxBounces)
{
	return Color();
}

void ReflectiveMaterial::print(std::ostream& stream) const
{
	stream << "Reflective material";
}

bool ReflectiveMaterial::getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay)
{
	Vector3 lightDirection = light->getDirectionAt(intersec.point);
	Vector3 normal = intersec.hitNormal;

	Vector3 rayDirection = -1 * Utils::reflect(lightDirection, normal);

	secondaryRay = Utils::shiftedRay(intersec.point, rayDirection);

	return true;
}
