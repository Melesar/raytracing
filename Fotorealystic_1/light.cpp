#include "light.h"
#include "ray.h"
#include "scene.h"
#include "utils.h"

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
	stream << "Directional light:" << "direction = " << direction << ", intensity = " << intensity;
}

Vector3 PointLight::samplePosition(Vector3& surfaceNormal, double& pdf)
{
	pdf = 2 * utils::DoublePi * intensity;
	return position;
}

Vector3 PointLight::sampleDirection(const Vector3& surfaceNormal, double u, double v, double& pdf)
{
	pdf = 0.5 * utils::InvDoublePi;
	return utils::sampleSphere(u, v);
}

//TODO implement directional light shading
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

	return distance < 0.0001 ? intensity : intensity / distance;
}

Color PointLight::evaluate(const Intersection& intersection)
{
	return Color(getIntensityAt(intersection.point));
}

void PointLight::print(std::ostream & stream) const
{
	stream << "Point light:" << "position = " << position << ", intensity = " << intensity;
}

double PointLight::shade(const Vector3 & point, const Scene & scene) const
{
	Vector3 offset = position - point;
	Ray r(point, offset.normalized());

	Intersection i;
	return scene.traceForIntersection(r, i, offset.magnitude()) ? 0 : 1;
}

