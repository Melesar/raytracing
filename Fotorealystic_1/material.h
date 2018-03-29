#pragma once

#include "color.h"

class Vector3;
class Light;

struct Material
{
	Color color;
	
	double getAlbedo() const;
	void setAlbedo(const double newAlbedo);

	double getDiffuse() const;
	void setDiffuse(double d);

	double getSpecular() const;
	void setSpecular(double s);

	double getSpecularPower() const;
	void setSpecularPower(double sp);

	Color applyLight(const Vector3& uv, const Vector3& worldPosition, const Light& light);

	Material(const Color& color = Color(255, 255, 255), double albedo = 3.1415, double diffuse = 1, double specular = 0, double specularPower = 2)
		:	color(color),
			albedo(albedo),
			diffuse(diffuse),
			specular(specular),
			specularPower(specularPower)
	{}

	double albedo;
	double diffuse, specular;

	double specularPower;
};