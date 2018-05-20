#pragma once
#include "printable.h"

class Camera;

class Renderer : public Printable
{

public:

	virtual void render(char* outputPath) = 0;

	Renderer (int imageWidth, int imageHeight, Scene* scene, Camera* camera) :
		imageWidth(imageWidth), imageHeight(imageHeight), scene(scene), camera(camera) {}

	virtual ~Renderer()
	{ }

protected:

	int imageWidth;
	int imageHeight;
	Scene* scene;
	Camera* camera;
};