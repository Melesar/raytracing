#include "camera.h"


Ray PerspectiveCamera::raycast(double x, double y, double screenWidth, double screenHeight)
{
	Vector3 pixelCoords = screenToWorldCoordinates(x, y, screenWidth, screenHeight);
	Vector3 origin = transform->getPosition();

	return Ray(origin, pixelCoords - origin);
}


Transform & Camera::getTransform() const
{
	return *transform;
}

Vector3 PerspectiveCamera::screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const
{
	double aspect = screenWidth / screenHeight;

	double px = (2.0 * (x + 0.5) / screenWidth - 1.0) * tan(fieldOfView / 2 * 3.1415 / 180.0) * aspect;
	double py = (1.0 - 2.0 * (y + 0.5) / screenHeight) * tan(fieldOfView / 2 * 3.1415 / 180.0);

	Matrix4x4 lookAt = Matrix4x4::lookAt(transform->getPosition(), transform->getPosition() + transform->forward(), transform->up());
	Vector4 pixelWorld = lookAt * Vector4(px, py, 1, 1);

	return Vector3(pixelWorld.x, pixelWorld.y, pixelWorld.z);
}

Camera::~Camera()
{
	delete transform;
}

Matrix4x4 PerspectiveCamera::getViewProjection() const
{
	Vector3 pos = transform->getPosition();
	return perspective * Matrix4x4::lookAt(pos, pos + transform->forward(), transform->up());
}

Ray OrthographicCamera::raycast(double x, double y, double screenWidth, double screenHeight)
{
	Vector3 origin = screenToWorldCoordinates(x, y, screenWidth, screenHeight);
	Vector3 direction = transform->forward();

	return Ray(origin, direction);
}

Vector3 OrthographicCamera::screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const
{
	double aspect = screenWidth / screenHeight;
	double px = (2.0 * (x + 0.5) / screenWidth - 1.0) * orthographicSize * aspect;
	double py = (1.0 - 2.0 * (y + 0.5) / screenHeight) * orthographicSize;

	Matrix4x4 lookAt = Matrix4x4::lookAt(transform->getPosition(), transform->getPosition() + transform->forward(), transform->up());
	Vector4 pixelWorld = lookAt * Vector4(px, py, 1, 1);
	
	return Vector3(pixelWorld.x, pixelWorld.y, pixelWorld.z);
}
