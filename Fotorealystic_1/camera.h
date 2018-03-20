#pragma once

#include "ray.h"
#include "transform.h"
#include "matrix4x4.h"

class Camera
{
public:
	virtual Ray raycast(double x, double y, double screenWidth, double screenHeight) = 0;
	virtual Vector3 screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const = 0;

	Camera()
	{
		transform = new Transform();
	}

	Transform& getTransform() const;

	virtual ~Camera();

protected:

	Transform* transform;
};

class PerspectiveCamera : public Camera
{
public:

	virtual Ray raycast(double x, double y, double screenWidth, double screenHeight) override;
	virtual Vector3 screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const override;

	PerspectiveCamera(double fov) 
		:fieldOfView (fov)
	{}

private:

	double fieldOfView;
	Matrix4x4 perspective;

	Matrix4x4 getViewProjection() const;
};

class OrthographicCamera : public Camera
{
public:

	virtual Ray raycast(double x, double y, double screenWidth, double screenHeight) override;
	virtual Vector3 screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const override;

	OrthographicCamera(double orthographicSize)
		: orthographicSize(orthographicSize) {}

private:

	double orthographicSize;
};