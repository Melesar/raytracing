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

bool Scene::traceForIntersection(const Ray& ray, Intersection& intersec, double maxDistance) const
{
	int objectsCount = objects.size();
	bool isObjectFound = false;

	double nearestDistance = 1e+10;
	for (int objIndex = 0; objIndex < objectsCount; ++objIndex) {
		Object* obj = objects.at(objIndex);
		if (obj->intersects(ray, intersec) && intersec.distance < nearestDistance && intersec.distance > MinIntersectionDistance) {
			nearestDistance = intersec.distance;
			isObjectFound = true;
		}
	}

	return isObjectFound && nearestDistance <= maxDistance;
}

void Scene::print(std::ostream& stream) const
{
	stream << *this;
}

bool Scene::trace(const Ray& r, Color & color, int maxBounce, double maxDistance) const
{
	Intersection intersec;

	if (!traceForIntersection(r, intersec, maxDistance)) {
		return false;
	}

	int lightsCount = lights.size();
	for (int lightIndex = 0; lightIndex < lightsCount; ++lightIndex) {
		Light* light = lights.at(lightIndex);

		Ray secondaryRay;
		if (intersec.material->sendSecondaryRay(*light, intersec, secondaryRay) && maxBounce > 0) {
			return trace(secondaryRay, color, maxBounce - 1, maxDistance);
		}

		color += intersec.material->illuminateDirectly(*light, intersec);

		/*if (!intersec.material->getColorAndSendSecondaryRayIfNeeded(light, intersec, materialColor, secondaryRay)) {
			color += light->shade(intersec.point, *this) * materialColor;
		} else if (maxBounce > 0) {
			return trace(secondaryRay, color, maxBounce - 1, maxDistance);
		}*/
	}

	return true;
}

std::ostream & operator<<(std::ostream & stream, const Scene& scene)
{
	stream << "\tObjects: " << std::endl;
	for (size_t i = 0; i < scene.objects.size(); i++) {
		stream << "\t\t" << *scene.objects.at(i) << std::endl;
	}

	stream << "\tLights:" << std::endl;

	for (size_t i = 0; i < scene.lights.size(); i++) {
		stream << "\t\t" << *scene.lights.at(i) << std::endl;
	}

	return stream;
}
