#pragma once

#include "ray.h"
#include "transform.h"
#include "matrix4x4.h"
#include "printable.h"
#include <ostream>
#include "utils.h"

class Camera : public Printable
{
public:
	virtual Ray raycast(double x, double y, double screenWidth, double screenHeight) = 0;
	virtual Vector3 screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const = 0;
	virtual bool worldToScreenCoordinates(const Vector3& worldPosition, double screenWidth, double screenHeight, Vector3& screenPos) const = 0;

	virtual double evaluateWe(const Vector3& worldPosition, int imageWidth, int imageHeight) = 0;

	Camera()
	{
		transform = new Transform();
	}

	Transform& getTransform() const;


	void print(std::ostream& stream) const override = 0;
	virtual ~Camera();

	friend std::ostream& operator << (std::ostream& os, const Camera& obj)
	{
		obj.print(os);
		return os;
	}

protected:

	Transform* transform;
};

class PerspectiveCamera : public Camera
{
public:

	Ray raycast(double x, double y, double screenWidth, double screenHeight) override;
	Vector3 screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const override;
	bool worldToScreenCoordinates(const Vector3& worldPosition, double screenWidth, double screenHeight, Vector3& screenPos) const override;

	double evaluateWe(const Vector3& worldPosition, int imageWidth, int imageHeight) override;

	PerspectiveCamera(double fov, double aspectRatio) 
		:fieldOfView (fov), aspectRatio(aspectRatio)
	{
		view = Matrix4x4::lookAt(transform->getPosition(), transform->getPosition() + transform->forward(), transform->up());
		invView = view.inverse();

		double filmWorldHeight = 2.0f * focalLenght * tan(0.5f * fieldOfView * utils::Pi / 180);
		double filmWorldWidth = filmWorldHeight * aspectRatio;

		filmArea = filmWorldHeight * filmWorldWidth;
	}


	void print(std::ostream& stream) const override;

	

private:
	Matrix4x4 view;
	Matrix4x4 invView;

	const double focalLenght = 1.0;
	const double lensRadius = 0.0;

	double fieldOfView;
	double filmArea;
	double aspectRatio;
};

class OrthographicCamera : public Camera
{
public:

	virtual Ray raycast(double x, double y, double screenWidth, double screenHeight) override;
	virtual Vector3 screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const override;

	OrthographicCamera(double orthographicSize)
		: orthographicSize(orthographicSize) {}


	void print(std::ostream& stream) const override;
private:

	double orthographicSize;
};