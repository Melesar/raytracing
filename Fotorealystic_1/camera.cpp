#include "camera.h"
#include "utils.h"


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

	double toCanvasSpace = tan(fieldOfView / 2 * utils::Pi / 180.0);
	double px = (2.0 * (x + 0.5) / screenWidth - 1.0) * toCanvasSpace * aspect;
	double py = (1.0 - 2.0 * (y + 0.5) / screenHeight) * toCanvasSpace;

	Matrix4x4 lookAt = Matrix4x4::lookAt(transform->getPosition(), transform->getPosition() + transform->forward(), transform->up());
	Vector4 pixelWorld = lookAt * Vector4(px, py, 1, 1);

	return Vector3(pixelWorld.x, pixelWorld.y, pixelWorld.z);
}

void PerspectiveCamera::print(std::ostream& stream) const
{
	stream << "\tPerspective camera: fov = " << fieldOfView;
}

Camera::~Camera()
{
	delete transform;
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

void OrthographicCamera::print(std::ostream& stream) const
{
	stream << "\Orthographic camera: orthosize = " << orthographicSize;
}
