#include "light.h"

Vector3 DirectionalLight::getDirectionAt(const Vector3 & point) const
{
	return direction;
}

double DirectionalLight::getIntensityAt(const Vector3 & point) const
{
	return intensity;
}
