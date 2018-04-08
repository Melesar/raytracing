#include "color.h"
#include "image.h"

bool Image::isSDLIntialized = false;

Image::Image(int width, int height) 
	: width(width), height(height)
{
	if (!isSDLIntialized) {
		InitSdl();
	}

	Uint32 amask = 0;
	Uint32 bmask = 0x00ff0000;
	Uint32 gmask = 0x0000ff00;
	Uint32 rmask = 0x000000ff;

	sdlImg = SDL_CreateRGBSurface(0, width, height, 24, rmask, gmask, bmask, amask);
	bytesPerPixel = sdlImg->format->BytesPerPixel;
}

Image::Image(std::string & fileName)
{
	if (!isSDLIntialized) {
		InitSdl();
	}

	sdlImg = IMG_Load(fileName.c_str());

	if (sdlImg == nullptr) {
		std::cout << "Error loading image: " << IMG_GetError() << std::endl;
		throw  -1;
	}

	width = sdlImg->w;
	height = sdlImg->h;
	bytesPerPixel = sdlImg->format->BytesPerPixel;
}

Image::~Image()
{
	SDL_FreeSurface(sdlImg);
}

void Image::write(int x, int y, Color c)
{
	c.normalize();

	unsigned char r = (unsigned char)(255 * c.r);
	unsigned char g = (unsigned char)(255 * c.g);
	unsigned char b = (unsigned char)(255 * c.b);

	Uint8 *p = (Uint8 *) sdlImg->pixels + y * sdlImg->pitch + x * bytesPerPixel;

	p[0] = r & 0xff;
	p[1] = g & 0xff;
	p[2] = b & 0xff;
}

Color Image::getColor(double u, double v) const
{
	int x = (int) ((width - 1) * u);
	int y = (int) ((height - 1) * v);

	return getColor(x, y);
}

Color Image::getColor(int x, int y) const
{
	if (x >= width || y >= height) {
		return Color(0, 0, 0);
	}

	Uint8 *p = (Uint8 *)sdlImg->pixels + y * sdlImg->pitch + x * bytesPerPixel;
	
	const double convert = 1.0 / 255;

	double red = p[0] * convert;
	double green = p[1] * convert;
	double blue = p[2] * convert;

	return Color(red, green, blue);
}

void Image::save(std::string& fileName)
{
	std::string ext = fileName.substr(fileName.find_last_of(".") + 1);

	if (ext == "jpg") {
		IMG_SaveJPG(sdlImg, fileName.c_str(), 50);
	} else if (ext == "bmp") {
		SDL_SaveBMP(sdlImg, fileName.c_str());
	} else {
		std::cout << "Failed to save an image. Unknown type: " << ext << std::endl;
	}
}


