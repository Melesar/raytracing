#include "phongMaterial.h"
#include "light.h"

#include "object.h"
#include "utils.h"
#include "image.h"
#include "ray.h"
#include "scene.h"

#include <algorithm>
#include <random>


bool PhongMaterial::sendSecondaryRay(const Light& light, const Intersection& intersec, Ray& secondaryRay)
{
	return false;
}

Color PhongMaterial::illuminateDirectly(const Light& light, const Intersection& intersec)
{
	Color Kd = getDiffuse(), Ks = getSpecular();
	Color diff = diffuse(light, intersec);
	Color spec = specular(light, intersec);

	return Kd * diff + Ks * spec;
}

Color PhongMaterial::illuminateIndirectly(const Scene& scene, const Intersection& intersec, int numSamples, int maxBounces)
{
	if (maxBounces == 0) {
		return Color(0, 0, 0);
	}

	std::uniform_real_distribution<double> distribution(0, 1);

	Color color;
	double invPdf = utils::DoublePi;
	for (int i = 0; i < numSamples; ++i) {
		double r1 = distribution(randomEngine);
		double r2 = distribution(randomEngine);

		Vector3 hemisphereSample = utils::sampleHemisphere(r1, r2, specularPower);
		Vector3 sample = utils::transformHemisphere(hemisphereSample, intersec.hitNormal);

		Ray bounceRay = Ray(intersec.point, sample);
		Color bounceColor;
		/*if (scene.trace(bounceRay, bounceColor, maxBounces - 1, numSamples)) {
			color += r1 * bounceColor * invPdf;
		}*/
	}

	color *= albedo * utils::InvPi;
	color /= numSamples;

	return color;
}

bool PhongMaterial::isReflective() const
{
	return true;
}

Ray PhongMaterial::sampleReflection(const Intersection& intersection, float& pdf)
{
	std::uniform_real_distribution<double> distribution(0, 1);

	double r1 = distribution(randomEngine);
	double r2 = distribution(randomEngine);

	Vector3 hemisphereSample = utils::sampleHemisphere(r1, r2, specularPower);
	Vector3 sample = utils::transformHemisphere(hemisphereSample, intersection.hitNormal);
	
	Ray bounceRay = Ray(intersection.point, sample);

	pdf = 2 * r1 * albedo;

	return bounceRay;
}

Color PhongMaterial::sampleBSDF(const Intersection& intersection, Ray& bounceRay, double& scatteringPdf)
{
	std::uniform_real_distribution<double> distribution(0, 1);

	double r1 = distribution(randomEngine);
	double r2 = distribution(randomEngine);

	Vector3 hemisphereSample = utils::sampleHemisphere(r1, r2, specularPower);
	Vector3 sample = utils::transformHemisphere(hemisphereSample, intersection.hitNormal);

	bounceRay = Ray(intersection.point, sample);
	scatteringPdf = r1 * utils::InvPi;

	return color * albedo * utils::InvPi;
}


void PhongMaterial::print(std::ostream& stream) const
{
	stream << "Phong material: diffuse = " << diffuseColor << ", specular = " << specularColor << ", specular power = " << specularPower;
}

Color PhongMaterial::diffuse(const Light & light, const Intersection& intersec) const
{
	Vector3 hitPoint = intersec.point;

	double albedo = this->albedo * utils::InvPi;
	double lightIntensity = light.getIntensityAt(hitPoint);
	Vector3 lightDirection = light.getDirectionAt(hitPoint);
	Vector3 hitNormal = intersec.hitNormal;
	double cosine = -lightDirection.dot(hitNormal);
	cosine = std::fmax(0.0, cosine);

	Color color = albedo * lightIntensity * light.color * cosine;
	color *= getDiffuseColor(intersec.u, intersec.v);

	return color;
}

Color PhongMaterial::specular(const Light & light, const Intersection& intersec) const
{
	Vector3 hitPoint = intersec.point;

	Vector3 L = light.getDirectionAt(hitPoint);
	Vector3 N = intersec.hitNormal;
	Vector3 R = utils::reflect(L, N);

	double S = std::pow(std::max(0.0, R.dot(intersec.viewDirection)), getSpecularPower());

	Color color = light.getIntensityAt(hitPoint) * light.color * S;
	return color;
}

double PhongMaterial::getAlbedo() const
{
	return albedo;
}

void PhongMaterial::setAlbedo(const double newAlbedo)
{
	albedo = newAlbedo;
}

Color PhongMaterial::getDiffuse() const
{
	return diffuseColor;
}

void PhongMaterial::setDiffuse(double d)
{
	double df = std::min(d, 1.0);
	df = std::max(df, 0.0);

	diffuseColor.set(df, df, df);
}

void PhongMaterial::setDiffuse(const Color & diffuse)
{
	this->diffuseColor = diffuse;
}

Color PhongMaterial::getSpecular() const
{
	return specularColor;
}

void PhongMaterial::setSpecular(double s)
{
	double sp = std::min(s, 1.0);
	sp = std::max(sp, 0.0);

	specularColor.set(sp, sp, sp);
}

void PhongMaterial::setSpecular(const Color & specular)
{
	this->specularColor = specular;
}

double PhongMaterial::getSpecularPower() const
{
	return specularPower;
}

void PhongMaterial::setSpecularPower(double sp)
{
	specularPower = std::max(1.0, sp);
}

void PhongMaterial::setDiffuseMap(Image* diffuseMap)
{
	this->diffuseMap.reset(diffuseMap);
}

const Image& PhongMaterial::getDiffuseMap() const
{
	return *diffuseMap;
}

Color PhongMaterial::getDiffuseColor(double u, double v) const
{
	Image* diffuseTexture = diffuseMap.get();

	return diffuseTexture != nullptr ? diffuseTexture->getColor(u, v) : color;
}



