#include "image.h"
#include "color.h"

Image::Image(std::string fileName, int width, int height) 
	: fileName(fileName)
{
	img = new bitmap_image(width, height);
}

Image::~Image()
{
	delete img;
}

void Image::write(int x, int y, Color c)
{
	c.normalize();

	char r = (char)(255 * c.r);
	char g = (char)(255 * c.g);
	char b = (char)(255 * c.b);

	img->set_pixel(x, y, r, g, b);
}

void Image::save()
{
	img->save_image(fileName);
}


