#include "render.h"
#include <fstream>
#include <string>

void Render::render(char * outputPath)
{
	std::ofstream* file = openImageFile(outputPath, imageWidth, imageHeight);

	for (int height = 0; height < imageHeight; ++height) {
		for (int width = 0; width < imageWidth; ++width) {
			Color result = backgroundColor;
			int raysCast;
			Ray* rays = camera->raycast(width, height, imageWidth, imageHeight, raysCast);
			scene->trace(rays, raysCast, result);

			writePixel(file, result);
			delete[] rays;
		}
	}

	file->close();
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
