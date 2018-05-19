#pragma once

#include "scene.h"
#include "camera.h"
#include "color.h"
#include "renderer.h"

class Pathtracer : public Renderer
{
	int maxSecondaryRays;

	Color backgroundColor;

	bool antialiasingEnabled = true;
	int indirectLightingSamples;

public:

	void render(char* outputPath) override;

	void setAntialiasing(bool isEnabled);

	void print(std::ostream& stream) const override;

	Pathtracer(int imageWidth, int imageHeight, Scene* scene, Camera* camera, const Color& backgroundColor = Color(0, 0, 0.4),
		int maxSecondaryRays = 1, int indirectLightingSamples = 16) 
	:
		Renderer(imageWidth, imageHeight, scene, camera),
		maxSecondaryRays(maxSecondaryRays),
		backgroundColor(backgroundColor),
		indirectLightingSamples(indirectLightingSamples)
	{
	}

	~Pathtracer();

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
	bool trace(const Ray& r, Color & color, int maxBounce = 1, double maxDistance = INFINITY) const;
};
