#include "areaLight.h"
#include "emissiveMaterial.h"
#include "object.h"


void AreaLight::print(std::ostream & stream) const
{
}

Vector3 AreaLight::getDirectionAt(const Vector3 & point) const
{
	return Vector3();
}

double AreaLight::getIntensityAt(const Vector3 & point) const
{
	return 0.0;
}

double AreaLight::shade(const Vector3 & point, const Scene & scene) const
{
	return 0.0;
}

AreaLight::AreaLight(Object * shape, double intensity)
{
	this->shape = shape;

	EmissiveMaterial* material = new EmissiveMaterial();
	this->shape->setMaterial(material);
}

AreaLight::~AreaLight()
{
}
