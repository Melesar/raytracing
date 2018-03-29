#include "material.h"
#include "light.h"

#include <algorithm>

double Material::getAlbedo() const
{
	return albedo;
}

void Material::setAlbedo(const double newAlbedo)
{
	albedo = newAlbedo;
}

double Material::getDiffuse() const
{
	return diffuse;
}

void Material::setDiffuse(double d)
{
	diffuse = std::max(d, 1.0);
	diffuse = std::min(d, 0.0);
}

double Material::getSpecular() const
{
	return specular;
}

void Material::setSpecular(double s)
{
	specular = std::max(s, 1.0);
	specular = std::min(s, 0.0);
}

double Material::getSpecularPower() const
{
	return specularPower;
}

void Material::setSpecularPower(double sp)
{
	specularPower = std::min(1.0, sp);
}

Color Material::applyLight(const Vector3 & uv, const Vector3& worldPosition, const Light & light)
{
	Color c;

	Vector3 L = light.getDirectionAt(worldPosition);
	double lightIntensity = light.getIntensityAt(worldPosition);

	return c;
}
