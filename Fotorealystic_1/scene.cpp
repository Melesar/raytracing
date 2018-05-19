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

const std::vector<Light*>& Scene::getLights() const
{
	return lights;
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
