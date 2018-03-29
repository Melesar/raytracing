#include "scene.h"
#include "ray.h"
#include "light.h"

#include <algorithm>


void Scene::addObject(Object * newObject)
{
	objects.push_back(newObject);
}

void Scene::addLight(Light* newLight)
{
	lights.push_back(newLight);
}

void Scene::trace(Ray* r, int raysCount, Color& color)
{
	Color res;
	for (int i = 0; i < raysCount; ++i) {
		Color rayColor;
		trace(r[i], rayColor);

		res += rayColor;
	}

	res /= (double) raysCount;
	color = res;
}

void Scene::onPreRender()
{
	for (auto obj : objects) {
		obj->onPreRender();
	}
}

Scene::~Scene()
{
	for (auto obj : objects) {
		delete obj;
	}
}

bool Scene::trace(Ray r, Color & color, int maxBounce, double maxDistance)
{
	int objectsCount = objects.size();
	bool isObjectFound = false;
	Intersection intersec;

	for (int objIndex = 0; objIndex < objectsCount; ++objIndex) {
		Object* obj = objects.at(objIndex);
		if (obj->intersects(r, intersec)) {
			isObjectFound = true;
			break;
		}
	}

	if (!isObjectFound) {
		return false;
	}

	Material& m = intersec.object->getMaterial();
	float Kd = m.getDiffuse(), Ks = m.getSpecular();
	int lightsCount = lights.size();
	for (int lightIndex = 0; lightIndex < lightsCount; ++lightIndex) {
		Light* light = lights.at(lightIndex);

		Color diff = diffuse(*light, intersec);
		Color spec = specular(*light, r.getDirection(), intersec);
		color = Kd * diff + Ks * spec;
	}

	return true;
}

Color Scene::diffuse(const Light & light, const Intersection& intersec) const
{
	Vector3 hitPoint = intersec.point;
	Material& material = intersec.object->getMaterial();

	double albedo = material.getAlbedo() / 3.1415;
	double lightIntensity = light.getIntensityAt(hitPoint);
	Vector3 lightDirection = light.getDirectionAt(hitPoint);
	Vector3 hitNormal = intersec.hitNormal;
	double cosine = -lightDirection.dot(hitNormal);
	cosine = std::fmax(0.0, cosine);

	Color color = albedo * lightIntensity * light.color * cosine;
	color *= material.color;

	return color;
}

Color Scene::specular(const Light & light, const Vector3& viewDirection, const Intersection& intersec) const
{
	Vector3 hitPoint = intersec.point;
	Material& material = intersec.object->getMaterial();

	Vector3 L = light.getDirectionAt(hitPoint);
	Vector3 N = intersec.hitNormal;
	Vector3 R = (2 * N.dot(L) * N - L).normalized();

	double S = std::pow(std::max(0.0, R.dot(viewDirection)), material.getSpecularPower());

	Color color = light.getIntensityAt(hitPoint) * light.color * S;
	return color;
}
