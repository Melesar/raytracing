#pragma once
#include "renderer.h"
#include <vector>
#include "PathVertex.h"
#include "scene.h"

struct Intersection;
class Light;
class Camera;

class LightTracer : public Renderer
{

public:

	void print(std::ostream& stream) const override;
	void render(char* outputPath) override;


	LightTracer(int imageWidth, int imageHeight, Scene* scene, Camera* camera, int numPaths, int maxPathLength);

	~LightTracer()
	{
		delete[] imageBuffer;
		delete[] verticies;
	}

private:

	int buildLightPath();
	void calculatePathContribution(int verticiesCount);
	void addPathContribution(int x, int y, Color contribution) const;

	void writeImageBuffer(Image& image) const;

	std::default_random_engine randomEngine;

	PathVertex* verticies;

	int numPaths;
	int maxPathLength;

	Color* imageBuffer;
	Light* light;
};


