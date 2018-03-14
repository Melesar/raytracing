#pragma once

#include "ray.h"
#include "transform.h"
#include "matrix4x4.h"

class Camera
{

public:
	Ray raycast(double x, double y, double screenWidth, double screenHeight);

	Camera(double fov, bool isOrthographic = false) :
		fieldOfView(fov),
		isOrthgraphic(isOrthgraphic)
	{
		transform = new Transform();
	}

	Transform& getTransform() const;

	~Camera();

private:

	Vector3 screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const;

	Transform* transform;

	Matrix4x4 perspective;

	double fieldOfView;
	bool isOrthgraphic;

	Matrix4x4 getViewProjection() const;
};