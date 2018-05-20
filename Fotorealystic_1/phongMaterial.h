#pragma once

#include "color.h"
#include "material.h"

#include <memory>
#include <random>

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


	bool sendSecondaryRay(const Light& light, const Intersection& intersec, Ray& secondaryRay) override;
	Color illuminateDirectly(const Light& light, const Intersection& intersec) override;
	Color illuminateIndirectly(const Scene& scene, const Intersection& intersec, int numSamples, int maxBounces) override;


	bool isReflective() const override;
	Ray sampleReflection(const Intersection& intersection, float& pdf) override;
	Color sampleBSDF(const Intersection& intersection, Ray& bounceRay, double& scatteringPdf) override;

	PhongMaterial(const Color& color = Color(255, 255, 255), double albedo = 0.8, double diffuse = 1, double specular = 0, double specularPower = 0)
		:	color(color),
			albedo(albedo),
			specularPower(specularPower)
	{
		resolutionX = 150;
		resolutionY = 75;

		setDiffuse(diffuse);
		setSpecular(specular);
	}

	void print(std::ostream& stream) const override;

private:

	double albedo;
	Color diffuseColor, specularColor;

	std::shared_ptr<Image> diffuseMap;
	std::default_random_engine randomEngine;

	Color diffuse(const Light & light, const Intersection& intersec) const;
	Color specular(const Light & light, const Intersection& intersec) const;

	double specularPower;
};