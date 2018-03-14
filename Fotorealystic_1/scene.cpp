#include "scene.h"
#include "ray.h"
#include "light.h"


void Scene::addObject(Object * newObject)
{
	objects.push_back(newObject);
}

void Scene::addLight(Light* newLight)
{
	lights.push_back(newLight);
}

void Scene::trace(Ray r,  Color& color, int maxBounce, double maxDistance)
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
		return;
	}

	int lightsCount = lights.size();
	Object* hitObject = intersec.object;
	Vector3 hitPoint = intersec.point;
	for (int lightIndex = 0; lightIndex < lightsCount; ++lightIndex) {
		Light* light = lights.at(lightIndex);

		double albedo = hitObject->getMaterial().getAlbedo() / 3.1415;
		double lightIntensity = light->getIntensityAt(hitPoint);
		Vector3 lightDirection = light->getDirectionAt(hitPoint);
		Vector3 hitNormal = hitObject->getNormal(hitPoint);
		double cosine = -lightDirection.dot(hitNormal);
		cosine = std::fmax(0.0, cosine);
	
		color = albedo * lightIntensity * light->color * cosine;
		color *= hitObject->getMaterial().color;
	}
}

Scene::~Scene()
{
	for (auto obj : objects) {
		delete obj;
	}
}
