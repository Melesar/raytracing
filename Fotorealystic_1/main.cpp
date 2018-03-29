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
	std::cout << "Program started" << std::endl;

	Camera* cam = new PerspectiveCamera(60);
	Scene* scene = new Scene();

	Object* blueSphere = new Sphere(Vector3(1, 0, -40), 6);
	blueSphere->getMaterial().color = Color(0, 0, 1);
	blueSphere->getMaterial().specular = 1.2;
	blueSphere->getMaterial().diffuse = 1;
	blueSphere->getMaterial().setSpecularPower(10);

	Object* redSphere = new Sphere(Vector3(-8, 0, -40), 2);
	redSphere->getMaterial().color = Color(1, 0, 0);
	redSphere->getMaterial().setSpecularPower(120);
	redSphere->getMaterial().setSpecular(0.02);

	Plane* plane = new Plane(Vector3(0, 1, 0), Vector3(0, -20, 0));
	plane->getMaterial().color = Color(0.8, 0.56, 0.12);

	std::cout << "Creating a mesh" << std::endl;

	Mesh* wolf = new Mesh("Wolf.obj");

	wolf->getMaterial().color = Color(1, 1, 0);

	wolf->getTransform()->setPosition(Vector3(0, 0, -10));
	wolf->getTransform()->setRotation(Vector3(0, 240, 0));
	wolf->getTransform()->setScale(Vector3(10, 10, 10));

	std::cout << "Mesh is created" << std::endl;

	scene->addObject(blueSphere);
	scene->addObject(redSphere);
	//scene->addObject(wolf);
	scene->addObject(plane);

	Triangle* t = new Triangle();
	t->v0.pos = Vector3(-3, 0, -5);
	t->v0.normal = Vector3(0, 0, 1);
	t->v1.pos = Vector3(3, 0, -5);
	t->v1.normal = Vector3(0, 0, 1);
	t->v2.pos = Vector3(0, 3, -5);
	t->v2.normal = Vector3(0, 0, 1);

	t->getMaterial().color = Color(1, 0, 0);

	//scene->addObject(t);

	Light* directionalLight = new DirectionalLight(Vector3(1, -1, -1), 1);

	scene->addLight(directionalLight);

	Render r(800, 600, scene, cam, Color(0.12, 0.7, 0.4));

	std::cout << "Started rendering" << std::endl;
	
	r.render("perspective_60.bmp");
}
