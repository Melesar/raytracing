#include "reflectiveMaterial.h"
#include "refractiveMaterial.h"
#include "ray.h"
#include "sphere.h"
#include "plane.h"
#include "matrix4x4.h"
#include "camera.h"
#include "scene.h"
#include "render.h"
#include "light.h"
#include "triangle.h"
#include "image.h"
#include "mesh.h"
#include "utils.h"
#include "quad.h"
#include "areaLight.h"

void createPrimitives(Scene& scene)
{
	Quad* faceQuad = new Quad(
		Vector3(20, -10, -50),  //bottom-left
		Vector3(-20, -10, -50), //bottom-right
		Vector3(20, 10, -50)    //top-left
	);
	
	faceQuad->invertNormal();

	PhongMaterial* faceMaterial = new PhongMaterial();
	faceMaterial->color = Color(0.4, 0.4, 0.4);
	//faceMaterial->setSpecular(0.3);
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
	//bottomMaterial->setSpecular(0.9);
	bottomMaterial->setSpecularPower(4);

	bottomQuad->setMaterial(bottomMaterial);

	scene.addObject(bottomQuad);

	Quad* leftQuad = new Quad(
		Vector3(20, -10, 0),  //bottom-left
		Vector3(20, -10, -50), //bottom-right
		Vector3(20, 10, 0)    //top-left
	);

	leftQuad->invertNormal();

	PhongMaterial* leftMaterial = new PhongMaterial();
	leftMaterial->color = Color(0.9, 0.1, 0.2);
	leftMaterial->setSpecular(0.5);
	leftMaterial->setSpecularPower(4);

	leftQuad->setMaterial(leftMaterial);

	scene.addObject(leftQuad);

	Quad* rightQuad = new Quad(
		Vector3(-20, -10, 0),  //bottom-left
		Vector3(-20, -10, -50), //bottom-right
		Vector3(-20, 10, 0)    //top-left
	);

	PhongMaterial* rightMaterial = new PhongMaterial();
	rightMaterial->color = Color(0.2, 0.1, 0.9);
	//rightMaterial->setSpecular(0.9);
	rightMaterial->setSpecularPower(4);

	rightQuad->setMaterial(rightMaterial);

	scene.addObject(rightQuad);

	Quad* topQuad = new Quad(
		Vector3(-20, 10, 0),  //bottom-left
		Vector3(-20, 10, -50), //bottom-right
		Vector3(20, 10, 0)    //top-left
	);

	PhongMaterial* topMaterial = new PhongMaterial();
	topMaterial->color = Color(0.4, 0.4, 0.4);
	//topMaterial->setSpecular(0.9);
	topMaterial->setSpecularPower(4);

	topQuad->setMaterial(topMaterial);

	scene.addObject(topQuad);

	Object* blueSphere = new Sphere(Vector3(3, -2, -30), 6);
	PhongMaterial* mat = new PhongMaterial(Color(0, 0, 0.87));
	mat->setAlbedo(0.8);
	mat->setDiffuse(1);
	//mat->setSpecular(0);
	mat->setSpecularPower(10);
	blueSphere->setMaterial(mat);

	scene.addObject(blueSphere);

	Object* redSphere = new Sphere(Vector3(-8, -5, -20), 3);
	redSphere->setMaterial(new PhongMaterial(Color(0.87, 0, 0)));
	//redSphere->setMaterial(new RefractiveMaterial(2.5));

	scene.addObject(redSphere);
}

void createLight(Scene& scene)
{
	Light* pointLight = new PointLight(Vector3(0, 9.5, -22), 100.0);
	scene.addLight(pointLight);

	/*Quad* areaLightShape = new Quad(Vector3(5, 10, -30), Vector3(-5, 10, -30), Vector3(5, 10, -25));
	areaLightShape->invertNormal();

	Light* areaLight = new AreaLight(areaLightShape, 100);

	scene.addLight(areaLight);
	scene.addObject(areaLightShape);*/
}

void traceDebug (int x, int y, int imageWidth, int imageHeight, Scene& scene, Camera& cam)
{
	Color rayColor;
	Ray r = cam.raycast(x, y, imageWidth, imageHeight);
	scene.trace(r, rayColor, 2, 32);

	std::cout << rayColor << std::endl;
	std::cin.get();
}

int main(int argc, char** argv)
{
	Camera* cam = new PerspectiveCamera(75);
	Scene* scene = new Scene();

	createPrimitives(*scene);
	createLight(*scene);
//
//#ifdef _DEBUG
//	traceDebug(373, 137, 800, 600, *scene, *cam);
//	return 0;
//#endif

	Render r(800, 600, scene, cam, Color(1, 1, 1), 2, 256);
	r.setAntialiasing(false);

	r.render("pathtracing_final.bmp");

	return 0;
}


