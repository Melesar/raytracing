#include "areaLight.h"
#include "emissiveMaterial.h"
#include "object.h"
#include "ray.h"
#include "scene.h"


void AreaLight::print(std::ostream & stream) const
{

}

void AreaLight::getSamples()
{
	for (int x = 0; x < horizontalSamples; ++x) {
		for (int y = 0; y < verticalSamples; ++y) {
			double u = 1.0 / (horizontalSamples - x);
			double v = 1.0 / (verticalSamples - y);

			samples[x * horizontalSamples + y] = shape->getSamplePoint(u, v);
		}
	}
}

Vector3 AreaLight::getSamplePoint(const Vector3& point) const
{
	Vector3 result;
	for (int i = 0; i < totalSamples; ++i) {
		result += point - samples[i];
	}

	return result;
}

Vector3 AreaLight::getDirectionAt(const Vector3 & point) const
{
	return getSamplePoint(point).normalized();
}

double AreaLight::getIntensityAt(const Vector3 & point) const
{
	Vector3 distance = getSamplePoint(point) / totalSamples;
	return intensity / distance.magnitude();
}

double AreaLight::shade(const Vector3 & point, const Scene & scene) const
{
	const double shadingStep = 1.0 / totalSamples;

	double resultShading = 0;
	for (int i = 0; i < totalSamples; ++i) {
		Vector3 direction = samples[i] - point;
		Ray r(point, direction.normalized());

		Intersection intersec;
		if (!scene.traceForIntersection(r, intersec, direction.magnitude())) {
			resultShading += shadingStep;
		}
	}

	return resultShading;
}

AreaLight::AreaLight(AreaLightShape * shape, double intensity)
	: Light(intensity)
{
	this->shape = shape;

	EmissiveMaterial* material = new EmissiveMaterial();
	this->shape->setMaterial(material);

	samples = new Vector3[totalSamples];

	getSamples();
}

AreaLight::~AreaLight()
{
	delete shape;
	delete samples;
}
