#include "render.h"
#include "image.h"
#include <fstream>
#include <string>
#include "logger.h"

void Render::render(char * outputPath)
{
	Image img(imageWidth, imageHeight);
	Logger logger(scene);

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

void Render::setAntialiasing(bool isEnabled)
{
	antialiasingEnabled = isEnabled;
}

void Render::samplePixel(double x, double y, Color& resultColor, int depthLevel)
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

Render::SamplingInfo Render::trace(double x, double y)
{
	Color rayColor;
	Ray r = camera->raycast(x, y, imageWidth, imageHeight);
	bool isHit = scene->trace(r, rayColor, maxSecondaryRays);

	SamplingInfo info;
	info.x = x;
	info.y = y;
	info.color = isHit ? rayColor : backgroundColor;

	return info;
}

Render::~Render()
{
	delete[] imageBuffer;

	delete camera;
	delete scene;
}
