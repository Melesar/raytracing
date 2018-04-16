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

//----------- Area light --------------------

Vector3 AreaLight::getDirectionAt(const Vector3 & point) const
{
	return (point - getPoint()).normalized();
}

double AreaLight::getIntensityAt(const Vector3 & point) const
{
	Vector3 lightPoint = getPoint();
	double distance = (lightPoint - point).magnitude();

	return intensity / distance;
}

Vector3 AreaLight::getPoint() const
{
	double xt = (double) rand() / RAND_MAX;
	double yt = (double) rand() / RAND_MAX;
	double zt = (double) rand() / RAND_MAX;

	double px = min.x + (max.x - min.x) * xt;
	double py = min.y + (max.y - min.y) * yt;
	double pz = min.z + (max.z - min.z) * zt;

	return Vector3(px, py, pz);
}

void AreaLight::print(std::ostream & stream) const
{
	stream << "Area light:\t" << "max: " << max << ", min: "<< min << ", intensity " << intensity;
}

double AreaLight::shade(const Vector3 & point, const Scene & scene) const
{
	return 0.0;
}
