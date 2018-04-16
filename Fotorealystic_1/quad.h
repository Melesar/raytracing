#pragma once

#include "object.h"

class Quad : public Object
{
	Vector3 v1, v2, v3;
	Vector3 normal;

public:

	Quad(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	void invertNormal();

	virtual bool intersects(const Ray& ray, Intersection & intersection) override;
	virtual void onPreRender() override;
	virtual void print(std::ostream& stream) const override;
};