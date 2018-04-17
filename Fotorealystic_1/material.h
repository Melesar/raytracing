#pragma once
#include "printable.h"
#include <ostream>

class Light;
class Intersection;
class Ray;
class Color;

class Material : public Printable
{
public:

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
