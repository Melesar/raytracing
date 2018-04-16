#pragma once

#include "scene.h"
#include "camera.h"
#include "color.h"

class Render
{
	Scene* scene;
	Camera* camera;

	int imageWidth, imageHeight;
	int maxSecondaryRays;

	Color* imageBuffer;
	Color backgroundColor;

public:

	void render(char* outputPath);

	Render(int imageWidth, int imageHeight, Scene* scene, Camera* camera, const Color& backgroundColor = Color(0, 0, 0.4), int maxSecondaryRays = 1) :
		imageWidth(imageWidth),
		imageHeight(imageHeight),
		scene(scene),
		camera(camera),
		backgroundColor(backgroundColor),
		maxSecondaryRays(maxSecondaryRays)
	{
		imageBuffer = new Color [imageWidth * imageHeight];
	}

	~Render();

private:

	struct SamplingInfo
	{
		double x, y;
		Color color;

		bool compare(const SamplingInfo& other)
		{
			return color == other.color;
		}

		void middle(const SamplingInfo& other, double& x, double& y)
		{
			x = (this->x + other.x) / 2;
			y = (this->y + other.y) / 2;
		}
	};

	const int MaxSamplingDepth = 1;

	void samplePixel(double x, double y, Color& resultColor, int depthLevel = 0);
	SamplingInfo trace(double x, double y);
};