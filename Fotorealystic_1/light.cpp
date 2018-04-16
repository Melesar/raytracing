#include "light.h"
#include "ray.h"
#include "scene.h"

//------------ Directional light ----------

Vector3 DirectionalLight::getDirectionAt(const Vector3 & point) const
{
	return direction.normalized();
}

double DirectionalLight::getIntensityAt(const Vector3 & point) const
{
	return intensity;
}

void DirectionalLight::print(std::ostream & stream) const
{
	stream << "Directional light:\t" << "direction: " << direction << ", intensity: " << intensity;
}

double DirectionalLight::shade(const Vector3 & point, const Scene & scene) const
{
	return 1;
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

void PointLight::print(std::ostream & stream) const
{
	stream << "Point light:\t" << "position: " << position << ", intensity: " << intensity;
}

double PointLight::shade(const Vector3 & point, const Scene & scene) const
{
	Vector3 offset = position - point;
	Ray r(point, offset.normalized());

	Intersection i;
	return scene.traceForIntersection(r, i, offset.magnitude()) ? 0 : 1;
}

