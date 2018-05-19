#include "image.h"
#include <string>
#include "logger.h"
#include "pathtracer.h"

void Pathtracer::render(char * outputPath)
{
	Image img(imageWidth, imageHeight);
	Logger logger(this);

	logger.start();
	scene->onPreRender();

	for (int height = 0; height < imageHeight; ++height) {
		for (int width = 0; width < imageWidth; ++width) {
			Color result;
			samplePixel(width, height, result, 0);

			img.write(width, height, result);
		}
	}

	logger.output();
	img.save(std::string(outputPath));
}

void Pathtracer::setAntialiasing(bool isEnabled)
{
	antialiasingEnabled = isEnabled;
}

void Pathtracer::samplePixel(double x, double y, Color& resultColor, int depthLevel)
{
	if (!antialiasingEnabled) {
		resultColor = trace(x, y).color;
		return;
	}

	if (depthLevel > MaxSamplingDepth) {
		return;
	}

	SamplingInfo center = trace(x, y);
	double midX, midY;
	double offset = 0.5 / (depthLevel + 1);

	SamplingInfo corners[4] {
		trace(x - offset, y - offset),
		trace(x - offset, y + offset),
		trace(x + offset, y - offset),
		trace(x + offset, y + offset),
	};
	
	for (int i = 0; i < 4; ++i) {
		SamplingInfo corner = corners[i];
		if (!corner.compare(center)) {
			corner.middle(center, midX, midY);

			Color sampleColor;
			samplePixel(midX, midY, sampleColor, depthLevel + 1);
			resultColor += sampleColor;
		} else {
			resultColor += (center.color + corner.color) * 0.5;
		}
	}

	resultColor *= 0.25;
}

Pathtracer::SamplingInfo Pathtracer::trace(double x, double y)
{
	Color rayColor;
	Ray r = camera->raycast(x, y, imageWidth, imageHeight);
	bool isHit = trace(r, rayColor, maxSecondaryRays);

	SamplingInfo info;
	info.x = x;
	info.y = y;
	info.color = isHit ? rayColor : backgroundColor;

	return info;
}

bool Pathtracer::trace(const Ray& r, Color& color, int maxBounce, double maxDistance) const
{
	if(maxBounce < 0) {
		return false;
	}

	Intersection intersec;

	if (!scene->traceForIntersection(r, intersec, maxDistance)) {
		return false;
	}

	auto lights = scene->getLights();
	int lightsCount = lights.size();
	Material& material = *intersec.material;
	for (int lightIndex = 0; lightIndex < lightsCount; ++lightIndex) {
		Light* light = lights.at(lightIndex);

		Ray secondaryRay;
		if (material.sendSecondaryRay(*light, intersec, secondaryRay)) {
			return trace(secondaryRay, color, maxBounce - 1, maxDistance);
		}

		color += /*light->shade(intersec.point, *this) **/ material.illuminateDirectly(*light, intersec);
	}

	if (!material.isReflective() || maxBounce == 0) {
		return true;
	}

	Color indirectIllumination;
	for (int i = 0; i < indirectLightingSamples; ++i) {
		float pdf;
		Color sampleColor;
		Ray sampleRay = material.sampleReflection(intersec, pdf);

		if (trace(sampleRay, sampleColor, maxBounce - 1, maxDistance)) {
			indirectIllumination += pdf * sampleColor;
		}
	}

	indirectIllumination /= indirectLightingSamples;
	color += indirectIllumination;

	//color += intersec.material->illuminateIndirectly(*scene, intersec, indirectLightingSamples, maxBounce);

	return true;
}


Pathtracer::~Pathtracer()
{
	delete camera;
	delete scene;
}

void Pathtracer::print(std::ostream& stream) const
{
	stream << "Renderer configuration:" << std::endl;
	stream << "\tImage size: " << imageWidth << " x " << imageHeight << std::endl;

	stream << "\tAntialiasing: ";
	if (antialiasingEnabled) {
		stream << "max sampling depth is " << MaxSamplingDepth << std::endl;
	} else {
		stream << "disabled" << std::endl;
	}

	stream << "\tNumber of secondary rays: " << maxSecondaryRays << std::endl;
	stream << "\tIndirect lighting samples: " << indirectLightingSamples << std::endl;

	stream << "Camera: " << std::endl << *camera << std::endl;
	stream << "Scene: " << std::endl << *scene << std::endl;
}
