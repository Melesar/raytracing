#include "light.h"

//------------ Directional light ----------

Vector3 DirectionalLight::getDirectionAt(const Vector3 & point) const
{
	return direction.normalized();
}

double DirectionalLight::getIntensityAt(const Vector3 & point) const
{
	return intensity;
}

//----------- Point light -----------------


Vector3 PointLight::getDirectionAt(const Vector3 & point) const
{
	return (point - position).normalized();
}

double PointLight::getIntensityAt(const Vector3 & point) const
{
	double distance = (point - position).magnitude();

	return intensity / distance;
}
