#pragma once

#include <vector>
#include <ostream>

#include "object.h"
#include "color.h"

class Light;
class Ray;

class Scene
{
	std::vector<Object*> objects;
	std::vector<Light*> lights;

	const double MinIntersectionDistance = 0.0001;

public:

	void addObject(Object* newObject);
	void addLight(Light* light);

	void onPreRender();

	~Scene();

	bool trace(const Ray& r, Color& color, int maxBounce = 1, double maxDistance = INFINITY) const;
	bool traceForIntersection(const Ray& ray, Intersection& intersec, double maxDistance) const;

	friend std::ostream& operator << (std::ostream& stream, const Scene& scene);
};