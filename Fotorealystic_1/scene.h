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

public:

	void addObject(Object* newObject);
	void addLight(Light* light);

	void onPreRender();

	~Scene();

	bool trace(Ray r, Color& color, int maxBounce = 1, double maxDistance = INFINITY);

	Color diffuse(const Light& light, const Intersection& intersec) const;
	Color specular(const Light& light, const Vector3& viewDirection, const Intersection& intersec) const;

	friend std::ostream& operator << (std::ostream& stream, const Scene& scene);
};