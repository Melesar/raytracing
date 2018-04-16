#include "reflectiveMaterial.h"
#include "refractiveMaterial.h"
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

	PhongMaterial* faceMaterial = new PhongMaterial();
	faceMaterial->color = Color(0.4, 0.4, 0.4);
	faceMaterial->setSpecular(0.3);
	faceMaterial->setSpecularPower(1);

	faceQuad->setMaterial(faceMaterial);

	scene.addObject(faceQuad);

	Quad* bottomQuad = new Quad(
		Vector3(-20, -10, 0),  //bottom-left
		Vector3(-20, -10, -50), //bottom-right
		Vector3(20, -10, 0)    //top-left
	);

	bottomQuad->invertNormal();

	PhongMaterial* bottomMaterial = new PhongMaterial();
	bottomMaterial->color = Color(0.4, 0.4, 0.4);
	bottomMaterial->setSpecular(0.9);
	bottomMaterial->setSpecularPower(4);

	bottomQuad->setMaterial(bottomMaterial);

	scene.addObject(bottomQuad);

	Quad* leftQuad = new Quad(
		Vector3(20, -10, 0),  //bottom-left
		Vector3(20, -10, -50), //bottom-right
		Vector3(20, 25, 0)    //top-left
	);

	leftQuad->invertNormal();

	PhongMaterial* leftMaterial = new PhongMaterial();
	leftMaterial->color = Color(0.9, 0.1, 0.2);
	leftMaterial->setSpecular(0.9);
	leftMaterial->setSpecularPower(4);

	leftQuad->setMaterial(leftMaterial);

	scene.addObject(leftQuad);

	Quad* rightQuad = new Quad(
		Vector3(-20, -10, 0),  //bottom-left
		Vector3(-20, -10, -50), //bottom-right
		Vector3(-20, 25, 0)    //top-left
	);

	PhongMaterial* rightMaterial = new PhongMaterial();
	rightMaterial->color = Color(0.2, 0.1, 0.9);
	rightMaterial->setSpecular(0.9);
	rightMaterial->setSpecularPower(4);

	rightQuad->setMaterial(rightMaterial);

	scene.addObject(rightQuad);

	Quad* topQuad = new Quad(
		Vector3(-20, 25, 0),  //bottom-left
		Vector3(-20, 25, -50), //bottom-right
		Vector3(20, 25, 0)    //top-left
	);

	PhongMaterial* topMaterial = new PhongMaterial();
	topMaterial->color = Color(0.4, 0.4, 0.4);
	topMaterial->setSpecular(0.9);
	topMaterial->setSpecularPower(4);

	topQuad->setMaterial(topMaterial);

	scene.addObject(topQuad);

	Object* blueSphere = new Sphere(Vector3(3, -2, -30), 6);
	blueSphere->setMaterial(new ReflectiveMaterial());

	scene.addObject(blueSphere);

	Object* redSphere = new Sphere(Vector3(-8, -5, -20), 3);
	redSphere->setMaterial(new RefractiveMaterial());

	scene.addObject(redSphere);
}

void createLight(Scene& scene)
{
	Light* pointLight = new PointLight(Vector3(0, 20, -20), 60.0);
	scene.addLight(pointLight);
}

int main(int argc, char** argv)
{
	std::cout << "Program started" << std::endl;

	//Camera* cam = new OrthographicCamera(10);
	Camera* cam = new PerspectiveCamera(60);
	Scene* scene = new Scene();

	createPrimitives(*scene);
	createLight(*scene);

	Render r(800, 600, scene, cam, Color(0.12, 0.7, 0.4));

	std::cout << "Started rendering" << std::endl;
	
	//r.render("orthographic_10.bmp");
	r.render("perspective_60.bmp");

	return 0;
}


