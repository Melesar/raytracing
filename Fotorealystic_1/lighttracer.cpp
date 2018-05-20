#include "object.h"
#include "lighttracer.h"
#include "scene.h"
#include "logger.h"
#include "image.h"
#include "camera.h"
#include "areaLight.h"

void LightTracer::render(char* outputPath)
{
	Logger logger(this);

	logger.start();
	scene->onPreRender();

	for (int i = 0; i < numPaths; ++i) {
		int verticiesBuilt = buildLightPath();
		calculatePathContribution(verticiesBuilt);
	}

	logger.output();

	Image img(imageWidth, imageHeight);
	writeImageBuffer(img);
	img.save(std::string(outputPath));
}

LightTracer::LightTracer(int imageWidth, int imageHeight, Scene* scene, Camera* camera, int numPaths,
                         int maxPathLength):
	Renderer(imageWidth, imageHeight, scene, camera),
	numPaths(numPaths),
	maxPathLength(maxPathLength)
{
	light = scene->getLights()[0];

	int bufferLength = imageWidth * imageHeight;
	imageBuffer = new Color[bufferLength];
	for (int i = 0; i < bufferLength; ++i) {
		imageBuffer[i] = Color();
	}

	verticies = new PathVertex[maxPathLength];
}


int LightTracer::buildLightPath()
{
	double lightPdf;
	Vector3 lightSurfaceNormal;
	Vector3 lightPosition = light->samplePosition(lightSurfaceNormal, lightPdf);
	PathVertex v0(Color(1 / lightPdf), lightPosition);


	verticies[0] = v0;

	std::uniform_real_distribution<double> distribution;
	double pdfLightDirection;
	Vector3 lightDirection = light->sampleDirection(lightSurfaceNormal, distribution(randomEngine), distribution(randomEngine), pdfLightDirection);

	Color throughput = verticies[0].color /** abs(lightSurfaceNormal.dot(lightDirection))*/ / pdfLightDirection;

	Ray ray(lightPosition, lightDirection);
	for (int vertexIndex = 1; vertexIndex < maxPathLength; ++vertexIndex) {
		Intersection intersection;
		if (!scene->traceForIntersection(ray, intersection)) {
			return vertexIndex + 1;
		}

		verticies[vertexIndex] = PathVertex(throughput, intersection);
		double materialPdf;
		Color f = intersection.material->sampleBSDF(intersection, ray, materialPdf);

		throughput *= f * abs(intersection.hitNormal.dot(ray.getDirection())) / materialPdf;
	}

	return maxPathLength;
}

void LightTracer::calculatePathContribution(int verticiesCount)
{
	for (int s = 1; s < verticiesCount; ++s) {
		PathVertex v = verticies[s - 1];
		Vector3 screenPosition;
		if (!camera->worldToScreenCoordinates(v.intersection.point, imageWidth, imageHeight, screenPosition)) {
			continue;
		}

		Vector3 vToCam = camera->getTransform().getPosition() - v.intersection.point;
		double occludeDistance = vToCam.magnitude();
		Ray occlusionRay(v.intersection.point, vToCam.normalized());

		if (scene->traceForIntersection(occlusionRay, Intersection(), occludeDistance)) {
			continue;
		}

		Color fsl;
		Vector3 wo = vToCam.normalized();
		if (s > 1) {
			Vector3 wi = (verticies[s - 2].intersection.point - v.intersection.point).normalized();
			double bsdf;
			Color f = v.intersection.material->sampleBSDF(v.intersection, Ray(), bsdf);
			fsl = f * light->evaluate(v.intersection);
		} else {
			fsl = light->evaluate(v.intersection);
		}

		double fse = camera->evaluateWe(v.intersection.point, imageWidth, imageHeight);
		double len = (v.intersection.point - camera->getTransform().getPosition()).magnitude();
		double G = abs(v.intersection.hitNormal.dot(wo))
			* abs(camera->getTransform().forward().dot(wo))
			/ (len * len);

		Color pathContribution = fsl * fse * G * v.color;

		addPathContribution(screenPosition.x, screenPosition.y, pathContribution);
	}
}


void LightTracer::addPathContribution(int x, int y, Color contribution) const
{
	imageBuffer[y * imageWidth + x] += contribution;
}

void LightTracer::writeImageBuffer(Image& image) const
{
	for (int height = 0; height < imageHeight; ++height) {
		for (int width = 0; width < imageWidth; ++width) {
			Color pixelColor = imageBuffer[height * imageWidth + width];
			image.write(width, height, pixelColor);
		}
	}
}


void LightTracer::print(std::ostream& stream) const
{
	stream << "Light tracer renderer:" << std::endl;
	stream << "\tImage size: " << imageWidth << " x " << imageHeight << std::endl;
	stream << "\tPaths number: " << numPaths << std::endl;
	stream << "\tPath lenghtr: " << maxPathLength << std::endl;


	stream << "Camera: " << std::endl << *camera << std::endl;
	stream << "Scene: " << std::endl << *scene << std::endl;
}
