#pragma once

#include "object.h"
#include "AreaLightShape.h"

class Quad : public Object, public AreaLightShape
{
	Vector3 v1, v2, v3;
	Vector3 normal;

public:

	Quad(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	void invertNormal();

	Vector3 getSamplePoint(double u, double v) override;
	void setMaterial(Material* material) override;

	Vector3 getCenter() const;
	double getWidth() const;
	double getHeight() const;

	bool intersects(const Ray& ray, Intersection & intersection) override;
	void onPreRender() override;
	void print(std::ostream& stream) const override;
};
