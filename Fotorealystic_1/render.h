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
			x = (x + other.x) / 2;
			y = (y + other.y) / 2;
		}
	};

	void samplePixel(double x, double y, Color& resultColor, int& raysCast, int depthLevel = 0);
	SamplingInfo trace(double x, double y, Color& result, int& raysCast);

	std::ofstream* openImageFile(char* path, int width, int height) const;
	void writePixel(std::ofstream* file, const Color& color) const;
};