#pragma once
#include "printable.h"

class Renderer : public Printable
{

public:

	virtual void render(char* outputPath) = 0;

	Renderer (int imageWidth, int imageHeight, Scene* scene, Camera* camera) :
		imageWidth(imageWidth), imageHeight(imageHeight), scene(scene), camera(camera) {}

protected:

	int imageWidth;
	int imageHeight;
	Scene* scene;
	Camera* camera;
};