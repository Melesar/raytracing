#include "refractiveMaterial.h"

#include "vector3.h"
#include "light.h"
#include "object.h"
#include "color.h"
#include "ray.h"
#include "utils.h"

bool RefractiveMaterial::sendSecondaryRay(const Light& light, const Intersection& intersec, Ray& secondaryRay)
{
	return false;
}

Color RefractiveMaterial::illuminateDirectly(const Light& light, const Intersection& intersec)
{
	return Color();
}

Color RefractiveMaterial::illuminateIndirectly(const Scene& scene, const Intersection& intersec, int numSamples, int maxBounces)
{
	return Color();
}

void RefractiveMaterial::print(std::ostream& stream) const
{
	stream << "Refractive material: refractive factor = " << refractionFactor;
}

bool RefractiveMaterial::getColorAndSendSecondaryRayIfNeeded(Light* light, const Intersection& intersec, Color& color, Ray& secondaryRay)
{
	Vector3 d = light->getDirectionAt(intersec.point);
	Vector3 n = intersec.hitNormal;
	double dn = d.dot(n);

	Vector3 t = (d - n * dn) / refractionFactor;
	t -= n * sqrt(1 - (1 - dn * dn) / (refractionFactor * refractionFactor));

	secondaryRay = Utils::shiftedRay(intersec.point, t);

	return true;
}
