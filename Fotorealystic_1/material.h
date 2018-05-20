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

	/**
	 * Obsolete. Left here for reference
	 */
	virtual Color illuminateIndirectly(const Scene& scene, const Intersection& intersec, int numSamples, int maxBounces) = 0;

	virtual bool isReflective() const = 0;

	//TODO
	/**
	 * Used in path tracing. Pdf parameter accumulates scattering pdf with the albedo modifier.
	 * Kind of a workaround, should be refactored in future
	 */
	virtual Ray sampleReflection(const Intersection& intersection, float& pdf) = 0;

	/**
	 * Returns material's diffuse color and samples bounce direction
	 * Currently used in light tracing
	 */
	virtual Color sampleBSDF(const Intersection& intersection, Ray& bounceRay, double& scatteringPdf) = 0;

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
