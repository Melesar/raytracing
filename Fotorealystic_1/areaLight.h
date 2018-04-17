#pragma once

#include "light.h"
#include "vector3.h"
#include "AreaLightShape.h"

class Object;

class AreaLight : public Light
{
	AreaLightShape* shape;
	Vector3* samples;

	const int horizontalSamples = 8;
	const int verticalSamples = 8;
	const int totalSamples = horizontalSamples * verticalSamples;

public:

	Vector3 getDirectionAt(const Vector3& point) const override;
	double getIntensityAt(const Vector3& point) const override;

	double shade(const Vector3 & point, const Scene & scene) const override;

	AreaLight(AreaLightShape* shape, double intensity = 5.0);
	~AreaLight();

protected:

	void print(std::ostream& stream) const override;

private:

	void getSamples();
	Vector3 getSamplePoint(const Vector3& point) const;
};