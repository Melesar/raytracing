#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "matrix4x4.h"
#include "vector4.h"
#include "transform.h"
#include "camera.h"
#include "scene.h"
#include "render.h"
#include "light.h"
#include "triangle.h"

int main()
{
	Camera* cam = new Camera(60.0);
	Scene* scene = new Scene();
	Object* sphere = new Sphere(Vector3(0, 0, -40), 10);
	sphere->getMaterial().color = Color(1, 1, 0);

	Plane* plane = new Plane(Vector3(0, 1, 0), Vector3(0, -20, 0));
	plane->getMaterial().color = Color(0.8, 0.56, 0.12);
	plane->getMaterial().setAlbedo(0.8);

	scene->addObject(sphere);
	scene->addObject(plane);

	Light* directionalLight = new DirectionalLight(Vector3(0, -1, -1), 5);

	scene->addLight(directionalLight);

	Render r(512, 512, scene, cam, Color(0, 0, 0.4));
	
	r.render("out");

}
