#pragma once

#include "color.h"

class Vector3;
class Light;

struct Material
{
	Color color;
	
	double getAlbedo() const;
	void setAlbedo(const double newAlbedo);

	Color applyLight(const Vector3& uv, const Vector3& worldPosition, const Light& light);

	Material(const Color& color = Color(255, 255, 255), double albedo = 0.18)
		:color(color), albedo(albedo) {}

private:

	double albedo;
};