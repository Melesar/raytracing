#pragma once
#include "vector3.h"

class Material;

class AreaLightShape
{
public:

	virtual Vector3 getSamplePoint(double u, double v) = 0;
	virtual void setMaterial(Material* material) = 0;
};
