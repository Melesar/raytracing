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
#include "quad.h"

void createPrimitives(Scene& scene)
{
	Quad* faceQuad = new Quad(
		Vector3(20, -10, -50),  //bottom-left
		Vector3(-20, -10, -50), //bottom-right
		Vector3(20, 25, -50)    //top-left
	);
	
	faceQuad->invertNormal();

	faceQuad->getMaterial().color = Color(0.4, 0.4, 0.4);
	faceQuad->getMaterial().setSpecular(0.3);
	faceQuad->getMaterial().setSpecularPower(1);

	scene.addObject(faceQuad);

	Quad* bottomQuad = new Quad(
		Vector3(-20, -10, 0),  //bottom-left
		Vector3(-20, -10, -50), //bottom-right
		Vector3(20, -10, 0)    //top-left
	);

	bottomQuad->invertNormal();

	bottomQuad->getMaterial().color = Color(0.4, 0.4, 0.4);
	bottomQuad->getMaterial().setSpecular(0.9);
	bottomQuad->getMaterial().setSpecularPower(4);

	scene.addObject(bottomQuad);

	Quad* leftQuad = new Quad(
		Vector3(20, -10, 0),  //bottom-left
		Vector3(20, -10, -50), //bottom-right
		Vector3(20, 25, 0)    //top-left
	);

	leftQuad->invertNormal();

	leftQuad->getMaterial().color = Color(0.9, 0.1, 0.2);
	leftQuad->getMaterial().setSpecular(0.9);
	leftQuad->getMaterial().setSpecularPower(4);

	scene.addObject(leftQuad);

	Quad* rightQuad = new Quad(
		Vector3(-20, -10, 0),  //bottom-left
		Vector3(-20, -10, -50), //bottom-right
		Vector3(-20, 25, 0)    //top-left
	);

	rightQuad->getMaterial().color = Color(0.2, 0.1, 0.9);
	rightQuad->getMaterial().setSpecular(0.9);
	rightQuad->getMaterial().setSpecularPower(4);

	scene.addObject(rightQuad);

	Quad* topQuad = new Quad(
		Vector3(-20, 25, 0),  //bottom-left
		Vector3(-20, 25, -50), //bottom-right
		Vector3(20, 25, 0)    //top-left
	);

	topQuad->getMaterial().color = Color(0.4, 0.4, 0.4);
	topQuad->getMaterial().setSpecular(0.9);
	topQuad->getMaterial().setSpecularPower(4);

	scene.addObject(topQuad);

	Object* blueSphere = new Sphere(Vector3(8, -2, -30), 6);
	blueSphere->getMaterial().color = Color(0, 0, 1);
	blueSphere->getMaterial().setSpecular(1);
	blueSphere->getMaterial().setDiffuse(1);
	blueSphere->getMaterial().setSpecularPower(10);

	/*Image* sphereTexture = new Image(std::string("textures/sphere_texture.png"));
	blueSphere->getMaterial().setDiffuseMap(sphereTexture);*/
	scene.addObject(blueSphere);

	Object* redSphere = new Sphere(Vector3(-3, -5, -25), 3);
	redSphere->getMaterial().color = Color(1, 0, 0);
	redSphere->getMaterial().setSpecular(0);
	redSphere->getMaterial().setDiffuse(1);
	scene.addObject(redSphere);

	/*Plane* plane = new Plane(Vector3(0, 1, 0), Vector3(50, -20, 50));
	plane->getMaterial().color = Color(0.8, 0.56, 0.12);

	Image* planeTexture = new Image(std::string("textures/sea.jpg"));
	plane->getMaterial().setDiffuseMap(planeTexture);
	scene.addObject(plane);*/
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
	/*Light* directionalLight = new DirectionalLight(Vector3(1, -1, -1), 1.5);
	scene.addLight(directionalLight);*/

	Light* pointLight = new PointLight(Vector3(0, 20, -20), 60.0);
	scene.addLight(pointLight);

	/*Light* areaLight = new AreaLight(Vector3(-3, 8, -40), Vector3(1, 8, -30), 25.0);
	scene.addLight(areaLight);*/
}

int main(int argc, char** argv)
{
	std::cout << "Program started" << std::endl;

	//Camera* cam = new OrthographicCamera(10);
	Camera* cam = new PerspectiveCamera(60);
	Scene* scene = new Scene();

	createPrimitives(*scene);
	//createMesh(*scene);
	createTriangle(*scene);

	createLight(*scene);

	/*Object* q = new Quad(Vector3(2, -2, -30), Vector3(-2, -2, -30), Vector3(2, 2, -30));
	scene->addObject(q);*/

	Render r(800, 600, scene, cam, Color(0.12, 0.7, 0.4));

	std::cout << "Started rendering" << std::endl;
	
	//r.render("orthographic_10.bmp");
	r.render("perspective_60.bmp");

	return 0;
}


