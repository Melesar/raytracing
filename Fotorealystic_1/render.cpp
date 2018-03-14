#include "render.h"
#include <fstream>
#include <string>

void Render::render(char * outputPath)
{
	std::ofstream* file = openImageFile(outputPath, imageWidth, imageHeight);

	for (int height = 0; height < imageHeight; ++height) {
		for (int width = 0; width < imageWidth; ++width) {
			Color result = backgroundColor;

			int raysCast = 0;
			samplePixel(width, height, result, raysCast);

			////Shoot multiple rays to apply antialiasing
			//int raysCast;
			//Ray* rays = camera->raycast(width, height, imageWidth, imageHeight, raysCast);
			//scene->trace(rays, raysCast, result);
			//delete[] rays;

			writePixel(file, result);
		}
	}

	file->close();
}

void Render::samplePixel(double x, double y, Color& resultColor, int& raysCast, int depthLevel)
{
	if (depthLevel > 1) {
		return;
	}

	Color result;

	SamplingInfo center = trace(x, y, result, raysCast);
	double midX, midY;
	double offset = 0.5 / (depthLevel + 1);

	SamplingInfo corners[4] {
		trace(x - offset, y - offset, result, raysCast),
		trace(x - offset, y + offset, result, raysCast),
		trace(x + offset, y - offset, result, raysCast),
		trace(x + offset, y + offset, result, raysCast),
	};
	
	for (int i = 0; i < 4; ++i) {
		SamplingInfo corner = corners[i];
		if (!corner.compare(center)) {
			corner.middle(center, midX, midY);
			samplePixel(midX, midY, result, raysCast, depthLevel + 1);
		}
	}

	if (depthLevel == 0) {
		result /= raysCast;
		resultColor = result;
	} else {
		resultColor += result;
	}
}

Render::SamplingInfo Render::trace(double x, double y, Color & result, int & raysCast)
{
	Color rayColor;
	Ray r = camera->raycast(x, y, imageWidth, imageHeight);
	scene->trace(r, rayColor);

	result += rayColor;
	raysCast += 1;

	SamplingInfo info;
	info.x = x;
	info.y = y;
	info.color = rayColor;

	return info;
}

Render::~Render()
{
	delete[] imageBuffer;

	delete camera;
	delete scene;
}

std::ofstream* Render::openImageFile(char * path, int width, int height) const
{
	std::string s(path);
	s.append(".ppm");

	std::ofstream* file = new std::ofstream(s.c_str(), std::ios::out | std::ios::binary);
	(*file) << "P6\n" << width << " " << height << "\n255\n";

	return file;
}

void Render::writePixel(std::ofstream * file, const Color & color) const
{
	(*file) << color;
}
