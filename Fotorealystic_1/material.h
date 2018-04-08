#pragma once

#include "color.h"
#include <memory>

class Vector3;
class Image;
class Light;

struct Material
{
	Color color;
	
	double getAlbedo() const;
	void setAlbedo(const double newAlbedo);

	Color getDiffuse() const;
	void setDiffuse(double d);
	void setDiffuse(const Color& diffuse);

	Color getSpecular() const;
	void setSpecular(double s);
	void setSpecular(const Color& specular);

	double getSpecularPower() const;
	void setSpecularPower(double sp);

	void setDiffuseMap(Image* diffuseMap);
	const Image& getDiffuseMap() const;

	Color getDiffuseColor(double u, double v) const;

	Material(const Color& color = Color(255, 255, 255), double albedo = 3.1415, double diffuse = 1, double specular = 0, double specularPower = 2)
		:	color(color),
			albedo(albedo),
			specularPower(specularPower)
	{
		setDiffuse(diffuse);
		setSpecular(specular);
	}

private:

	double albedo;
	Color diffuse, specular;

	std::shared_ptr<Image> diffuseMap;

	double specularPower;
};