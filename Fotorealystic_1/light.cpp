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

void DirectionalLight::print(std::ostream & stream) const
{
	stream << "Directional light:\t" << "direction: " << direction << ", intensity: " << intensity;
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