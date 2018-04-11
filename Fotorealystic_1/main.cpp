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
#include "image.h"
#include "mesh.h"
#include "utils.h"

void createPrimitives(Scene& scene)
{
	Object* blueSphere = new Sphere(Vector3(1, 0, -40), 6);
	blueSphere->getMaterial().color = Color(0, 0, 1);
	blueSphere->getMaterial().setSpecular(1);
	blueSphere->getMaterial().setDiffuse(1);
	blueSphere->getMaterial().setSpecularPower(10);

	Image* sphereTexture = new Image(std::string("textures/sphere_texture.png"));
	blueSphere->getMaterial().setDiffuseMap(sphereTexture);

	Object* redSphere = new Sphere(Vector3(-8, 0, -40), 2);
	redSphere->getMaterial().color = Color(1, 0, 0);
	redSphere->getMaterial().setSpecular(0);
	redSphere->getMaterial().setDiffuse(1);

	Plane* plane = new Plane(Vector3(0, 1, 0), Vector3(50, -20, 50));
	plane->getMaterial().color = Color(0.8, 0.56, 0.12);

	Image* planeTexture = new Image(std::string("textures/sea.jpg"));
	plane->getMaterial().setDiffuseMap(planeTexture);

	scene.addObject(blueSphere);
	scene.addObject(redSphere);
	scene.addObject(plane);
}

void createMesh(Scene& scene)
{
	Mesh* model = new Mesh("acoustic guitar.obj");

	model->getMaterial().color = Color(1, 1, 0);

	model->getTransform()->setPosition(Vector3(0, 0, -10));
	model->getTransform()->setRotation(Vector3(0, 0, 0));
	model->getTransform()->setScale(Vector3(3, 3, 3));

	//scene.addObject(model);
}

void createTriangle(Scene& scene)
{
	Triangle* t = new Triangle();
	t->v0.pos = Vector3(-3, 0, -5);
	t->v0.normal = Vector3(0, 0, 1);
	t->v1.pos = Vector3(3, 0, -5);
	t->v1.normal = Vector3(0, 0, 1);
	t->v2.pos = Vector3(0, 3, -5);
	t->v2.normal = Vector3(0, 0, 1);

	t->getMaterial().color = Color(1, 0, 0);

	//scene.addObject(t);
}

void createLight(Scene& scene)
{
	Light* directionalLight = new DirectionalLight(Vector3(1, -1, -1), 1.5);
	scene.addLight(directionalLight);

	/*Light* pointLight = new PointLight(Vector3(-3, 1, -35), 10.0, 5.0);
	scene.addLight(pointLight);*/
}

int main(int argc, char** argv)
{
	std::cout << "Program started" << std::endl;

	Camera* cam = new PerspectiveCamera(60);
	Scene* scene = new Scene();

	createPrimitives(*scene);
	//createMesh(*scene);
	createTriangle(*scene);

	createLight(*scene);

	Render r(800, 600, scene, cam, Color(0.12, 0.7, 0.4));

	std::cout << "Started rendering" << std::endl;
	
	r.render("perspective_60.bmp");

	return 0;
}


