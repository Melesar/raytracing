#pragma once

#include "SDL2\SDL.h"
#include "SDL2\SDL_image.h"
#include <string>

class Color;

class Image
{
	SDL_Surface* sdlImg;

	int width, height;
	int bytesPerPixel;

	static bool isSDLIntialized;

	static void InitSdl()
	{
		int flagsInitialized = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		
		if (flagsInitialized > 0) {
			isSDLIntialized = true;
		} else {
			std::cout << "Error initializing SDL image: " << IMG_GetError() << std::endl;
		}
	}

public:

	Image(int width, int height);
	Image(std::string& fileName);

	virtual ~Image();

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	void write(int x, int y, Color c);
	Color getColor(double u, double v) const;
	Color getColor(int x, int y) const;

	void save(std::string& fileName);
};

