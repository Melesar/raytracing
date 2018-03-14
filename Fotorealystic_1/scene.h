#pragma once

#include <vector>
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

	void trace(Ray* r, int raysCount, Color& color);

	~Scene();

	void trace(Ray r, Color& color, int maxBounce = 1, double maxDistance = INFINITY);

};