#include "camera.h"

Ray* Camera::raycast(double x, double y, double screenWidth, double screenHeight, int& raysCast)
{
	Ray* rays = new Ray[5];
	raysCast = 5;

	Vector3 origin = transform->position();
	Vector3 pixelCoords0 = screenToWorldCoordinates(x, y, screenWidth, screenHeight);
	Vector3 pixelCoords1 = screenToWorldCoordinates(x - 0.5, y - 0.5, screenWidth, screenHeight);
	Vector3 pixelCoords2 = screenToWorldCoordinates(x + 0.5, y - 0.5, screenWidth, screenHeight);
	Vector3 pixelCoords3 = screenToWorldCoordinates(x - 0.5, y + 0.5, screenWidth, screenHeight);
	Vector3 pixelCoords4 = screenToWorldCoordinates(x + 0.5, y + 0.5, screenWidth, screenHeight);

	rays[0] = Ray(origin, pixelCoords0 - origin);
	rays[1] = Ray(origin, pixelCoords1 - origin);
	rays[2] = Ray(origin, pixelCoords2 - origin);
	rays[3] = Ray(origin, pixelCoords3 - origin);
	rays[4] = Ray(origin, pixelCoords4 - origin);

	 return rays;
}


Transform & Camera::getTransform() const
{
	return *transform;
}

Vector3 Camera::screenToWorldCoordinates(int x, int y, double screenWidth, double screenHeight) const
{
	double aspect = screenWidth / screenHeight;

	double px = (2.0 * (x + 0.5) / screenWidth - 1.0) * tan(fieldOfView / 2 * 3.1415 / 180.0) * aspect;
	double py = (1.0 - 2.0 * (y + 0.5) / screenWidth) * tan(fieldOfView / 2 * 3.1415 / 180.0);

	Matrix4x4 lookAt = Matrix4x4::lookAt(transform->position(), transform->position() + transform->forward(), transform->up());
	Vector4 pixelWorld = lookAt * Vector4(px, py, 1, 1);

	return Vector3(pixelWorld.x, pixelWorld.y, pixelWorld.z);
}

Camera::~Camera()
{
	delete transform;
}

Matrix4x4 Camera::getViewProjection() const
{
	Vector3 pos = transform->position();
	return perspective * Matrix4x4::lookAt(pos, pos + transform->forward(), transform->up());
}
