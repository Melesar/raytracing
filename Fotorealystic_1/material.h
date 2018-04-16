#pragma once

class Light;
class Intersection;
class Ray;
class Color;

class Material
{
public:

	//Returns true if material generates secondary ray
	virtual bool getColorAndSendSecondaryRayIfNeeded(Light* light, const Intersection& intersec, Color& color, Ray& secondaryRay) = 0;

	double getResolutionX() const { return resolutionX; }
	double getResolutionY() const { return resolutionY; }

protected:

	virtual Ray generateSecondaryRay(const Intersection& intersec);

	double resolutionX, resolutionY;
};
