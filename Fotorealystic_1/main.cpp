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
#include "parser.h"

int main(int argc, char** argv)
{
	Camera* cam = new PerspectiveCamera(60.0);
	Scene* scene = new Scene();

	Object* blueSphere = new Sphere(Vector3(1, 0, -40), 6);
	blueSphere->getMaterial().color = Color(0, 0, 1);

	Object* redSphere = new Sphere(Vector3(-8, 0, -40), 2);
	redSphere->getMaterial().color = Color(1, 0, 0);

	Plane* plane = new Plane(Vector3(0, 1, 0), Vector3(0, -20, 0));
	plane->getMaterial().color = Color(0.8, 0.56, 0.12);
	plane->getMaterial().setAlbedo(0.8);

	scene->addObject(blueSphere);
	scene->addObject(redSphere);
	scene->addObject(plane);

	Light* directionalLight = new DirectionalLight(Vector3(0, -1, -1), 5);

	scene->addLight(directionalLight);

	Render r(512, 512, scene, cam, Color(0.12, 0.7, 0.4));
	
	r.render("perspective_60.bmp");
    /*Mesh m("Wolf.obj");
	
	std::cin.get();*/
}
