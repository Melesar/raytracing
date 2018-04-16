#pragma once

#include "color.h"
#include "material.h"

#include <memory>

class Vector3;
class Image;
class Light;

class PhongMaterial : public Material
{
public:

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

	bool getColorAndSendSecondaryRayIfNeeded(Light* light, const Intersection& intersec, Color& color, Ray& secondaryRay) override;

	PhongMaterial(const Color& color = Color(255, 255, 255), double albedo = 3.1415, double diffuse = 1, double specular = 0, double specularPower = 2)
		:	color(color),
			albedo(albedo),
			specularPower(specularPower)
	{
		resolutionX = 150;
		resolutionY = 75;

		setDiffuse(diffuse);
		setSpecular(specular);
	}

private:

	double albedo;
	Color diffuseColor, specularColor;

	std::shared_ptr<Image> diffuseMap;

	Color diffuse(const Light & light, const Intersection& intersec) const;
	Color specular(const Light & light, const Intersection& intersec) const;

	double specularPower;
};