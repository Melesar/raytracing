#include "material.h"
#include "light.h"

#include <algorithm>
#include "image.h"

double Material::getAlbedo() const
{
	return albedo;
}

void Material::setAlbedo(const double newAlbedo)
{
	albedo = newAlbedo;
}

Color Material::getDiffuse() const
{
	return diffuse;
}

void Material::setDiffuse(double d)
{
	double df = std::min(d, 1.0);
	df = std::max(df, 0.0);

	diffuse.set(df, df, df);
}

void Material::setDiffuse(const Color & diffuse)
{
	this->diffuse = diffuse;
}

Color Material::getSpecular() const
{
	return specular;
}

void Material::setSpecular(double s)
{
	double sp = std::min(s, 1.0);
	sp = std::max(sp, 0.0);

	specular.set(sp, sp, sp);
}

void Material::setSpecular(const Color & specular)
{
	this->specular = specular;
}

double Material::getSpecularPower() const
{
	return specularPower;
}

void Material::setSpecularPower(double sp)
{
	specularPower = std::max(1.0, sp);
}

void Material::setDiffuseMap(Image* diffuseMap)
{
	this->diffuseMap.reset(diffuseMap);
}

const Image & Material::getDiffuseMap() const
{
	return *diffuseMap.get();
}

Color Material::getDiffuseColor(double u, double v) const
{
	Image* diffuseTexture = diffuseMap.get();

	return diffuseTexture != nullptr ? diffuseTexture->getColor(u, v) : color;
}

