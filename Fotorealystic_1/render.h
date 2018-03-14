#pragma once

#include "scene.h"
#include "camera.h"
#include "color.h"

class Render
{
	Scene* scene;
	Camera* camera;

	int imageWidth, imageHeight;
	Color* imageBuffer;
	Color backgroundColor;

public:

	void render(char* outputPath);

	Render(int imageWidth, int imageHeight, Scene* scene, Camera* camera, const Color& backgroundColor = Color(0, 0, 0.4)) :
		imageWidth(imageWidth),
		imageHeight(imageHeight),
		scene(scene),
		camera(camera),
		backgroundColor(backgroundColor)
	{
		imageBuffer = new Color [imageWidth * imageHeight];
	}

	~Render();

private:

	std::ofstream* openImageFile(char* path, int width, int height) const;
	void writePixel(std::ofstream* file, const Color& color) const;
};