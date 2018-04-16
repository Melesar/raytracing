#pragma once

#include "light.h"
#include "vector3.h"

class Object;

class AreaLight : public Light
{
	Object* shape;

public:

	Vector3 getDirectionAt(const Vector3& point) const;
	double getIntensityAt(const Vector3& point) const;

	virtual double shade(const Vector3 & point, const Scene & scene) const override;

	AreaLight(Object* shape, double intensity = 5.0);
	~AreaLight();

protected:

	void print(std::ostream& stream) const;

};