#include "material.h"
#include "light.h"

double Material::getAlbedo() const
{
	return albedo;
}

void Material::setAlbedo(const double newAlbedo)
{
	albedo = newAlbedo;
}

Color Material::applyLight(const Vector3 & uv, const Vector3& worldPosition, const Light & light)
{
	Color c;

	Vector3 L = light.getDirectionAt(worldPosition);
	double lightIntensity = light.getIntensityAt(worldPosition);

	return c;
}
