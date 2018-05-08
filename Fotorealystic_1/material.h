#pragma once
#include "printable.h"
#include <ostream>

class Scene;
class Light;
class Intersection;
class Ray;
class Color;

class Material : public Printable
{
public:

	virtual bool sendSecondaryRay(const Light& light, const Intersection& intersec, Ray& secondaryRay) = 0;

	virtual Color illuminateDirectly(const Light& light, const Intersection& intersec) = 0;
	virtual Color illuminateIndirectly(const Scene& scene, const Intersection& intersec, int numSamples) = 0;

	//Returns true if material generates secondary ray
	virtual bool getColorAndSendSecondaryRayIfNeeded(Light* light, const Intersection& intersec, Color& color, Ray& secondaryRay) = 0;

	double getResolutionX() const { return resolutionX; }
	double getResolutionY() const { return resolutionY; }

	void print(std::ostream& stream) const override = 0;


	friend std::ostream& operator<<(std::ostream& os, const Material& obj)
	{
		obj.print(os);
		return os;
	}

protected:

	virtual Ray generateSecondaryRay(const Intersection& intersec);

	double resolutionX, resolutionY;
};
