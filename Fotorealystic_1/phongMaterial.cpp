#include "phongMaterial.h"
#include "light.h"

#include "object.h"

#include <algorithm>
#include "image.h"

bool PhongMaterial::getColorAndSendSecondaryRayIfNeeded(Light * light, const Intersection & intersec, Color & color, Ray & secondaryRay)
{
	Color Kd = getDiffuse(), Ks = getSpecular();
	Color diff = diffuse(*light, intersec);
	Color spec = specular(*light, intersec);

	color += Kd * diff + Ks * spec;
	return false;
}

Color PhongMaterial::diffuse(const Light & light, const Intersection& intersec) const
{
	Vector3 hitPoint = intersec.point;

	double albedo = this->albedo / 3.1415;
	double lightIntensity = light.getIntensityAt(hitPoint);
	Vector3 lightDirection = light.getDirectionAt(hitPoint);
	Vector3 hitNormal = intersec.hitNormal;
	double cosine = -lightDirection.dot(hitNormal);
	cosine = std::fmax(0.0, cosine);

	Color color = albedo * lightIntensity * light.color * cosine;
	color *= getDiffuseColor(intersec.u, intersec.v);

	return color;
}

Color PhongMaterial::specular(const Light & light, const Intersection& intersec) const
{
	Vector3 hitPoint = intersec.point;

	Vector3 L = light.getDirectionAt(hitPoint);
	Vector3 N = intersec.hitNormal;
	Vector3 R = (2 * N.dot(L) * N - L).normalized();

	double S = std::pow(std::max(0.0, R.dot(intersec.viewDirection)), getSpecularPower());

	Color color = light.getIntensityAt(hitPoint) * light.color * S;
	return color;
}

double PhongMaterial::getAlbedo() const
{
	return albedo;
}

void PhongMaterial::setAlbedo(const double newAlbedo)
{
	albedo = newAlbedo;
}

Color PhongMaterial::getDiffuse() const
{
	return diffuseColor;
}

void PhongMaterial::setDiffuse(double d)
{
	double df = std::min(d, 1.0);
	df = std::max(df, 0.0);

	diffuseColor.set(df, df, df);
}

void PhongMaterial::setDiffuse(const Color & diffuse)
{
	this->diffuseColor = diffuse;
}

Color PhongMaterial::getSpecular() const
{
	return specularColor;
}

void PhongMaterial::setSpecular(double s)
{
	double sp = std::min(s, 1.0);
	sp = std::max(sp, 0.0);

	specularColor.set(sp, sp, sp);
}

void PhongMaterial::setSpecular(const Color & specular)
{
	this->specularColor = specular;
}

double PhongMaterial::getSpecularPower() const
{
	return specularPower;
}

void PhongMaterial::setSpecularPower(double sp)
{
	specularPower = std::max(1.0, sp);
}

void PhongMaterial::setDiffuseMap(Image* diffuseMap)
{
	this->diffuseMap.reset(diffuseMap);
}

const Image & PhongMaterial::getDiffuseMap() const
{
	return *diffuseMap.get();
}

Color PhongMaterial::getDiffuseColor(double u, double v) const
{
	Image* diffuseTexture = diffuseMap.get();

	return diffuseTexture != nullptr ? diffuseTexture->getColor(u, v) : color;
}



