#include "refractiveMaterial.h"

#include "vector3.h"
#include "light.h"
#include "object.h"
#include "color.h"
#include "ray.h"

bool RefractiveMaterial::getColorAndSendSecondaryRayIfNeeded(Light* light, const Intersection& intersec, Color& color, Ray& secondaryRay)
{
	Vector3 d = light->getDirectionAt(intersec.point);
	Vector3 n = intersec.hitNormal;
	double dn = d.dot(n);

	Vector3 t = (d - n * dn) / refractionFactor;
	t -= n * sqrt(1 - (1 - dn * dn) / (refractionFactor * refractionFactor));

	secondaryRay = Ray(intersec.point + 0.04 * t, t);

	return true;
}
