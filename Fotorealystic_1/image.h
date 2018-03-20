#pragma once

#include "bitmap_image.hpp"
#include <string>

class Color;

class Image
{
	bitmap_image* img;
	std::string fileName;

public:

	Image(std::string fileName, int width, int height);

	virtual ~Image();

	void write(int x, int y, Color c);
	void save();
};