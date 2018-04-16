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

	double nearestDistance = 1e+10;
	for (int objIndex = 0; objIndex < objectsCount; ++objIndex) {
		Object* obj = objects.at(objIndex);
		if (obj->intersects(r, intersec) && intersec.distance < nearestDistance) {
			nearestDistance = intersec.distance;
			isObjectFound = true;
		}
	}

	if (!isObjectFound) {
		return false;
	}

	int lightsCount = lights.size();
	for (int lightIndex = 0; lightIndex < lightsCount; ++lightIndex) {
		Light* light = lights.at(lightIndex);

		Ray secondaryRay;
		Color materialColor;
		if (!intersec.material->getColorAndSendSecondaryRayIfNeeded(light, intersec, materialColor, secondaryRay)) {
			color += materialColor;
		} else {
			//trace secondary ray
		}
	}

	return true;
}

std::ostream & operator<<(std::ostream & stream, const Scene& scene)
{
	stream << "Objects: [" << std::endl;
	for (size_t i = 0; i < scene.objects.size(); i++) {
		stream << "\t" << *scene.objects.at(i) << std::endl;
	}
	stream << "]" << std::endl;

	stream << "Lights: [" << std::endl;

	for (size_t i = 0; i < scene.lights.size(); i++) {
		stream << "\t" << *scene.lights.at(i) << std::endl;
	}

	stream << "]" << std::endl;

	return stream;
}
