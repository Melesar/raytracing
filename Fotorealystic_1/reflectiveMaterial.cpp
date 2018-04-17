#include "reflectiveMaterial.h"
#include "object.h"
#include "vector3.h"
#include "light.h"
#include "utils.h"
#include "ray.h"


void ReflectiveMaterial::print(std::ostream& stream) const
{
	stream << "Reflective material";
}

bool ReflectiveMaterial::getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay)
{
	Vector3 lightDirection = light->getDirectionAt(intersec.point);
	Vector3 normal = intersec.hitNormal;

	Vector3 rayDirection = -1 * Utils::reflect(lightDirection, normal);
	Vector3 rayOrigin = intersec.point + 0.04 * rayDirection;  //shift origin a bit forward to avoid intersection with the same object

	secondaryRay = Ray(rayOrigin, rayDirection);

	return true;
}
