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

void isIntersects(Sphere& s, const Ray& r)
{
	Intersection intersection;
	bool isIntersection = s.intersects(r, intersection);

	if (isIntersection) {
		std::cout << "Ray intersects sphere at point " << intersection.point << std::endl;
	} else {
		std::cout << "Given sphere and ray do not intersect" << std::endl;
	}
}

void isIntersects(Plane& p, const Ray& r)
{
	Intersection intersection;
	bool isIntersection = p.intersects(r, intersection);

	if (isIntersection) {
		std::cout << "Ray intersects plane at point " << intersection.point << std::endl;
	}
	else {
		std::cout << "Given plane and ray do not intersect" << std::endl;
	}
}

int main()
{
	/*Sphere sph(Vector3(), 10);

	Vector3 raysOrigin(0, 0, -20);

	Ray r1(raysOrigin, Vector3(0, 0, 1));
	Ray r2(raysOrigin, Vector3(0, 1, 0));
	Ray r3(Vector3(0, 10, -20), Vector3(0, 0, 1));

	isIntersects(sph, r1);
	isIntersects(sph, r2);
	isIntersects(sph, r3);

	double yz = sqrt(2) / 2;
	Vector3 normal(0, yz, yz);
	Plane p(normal, Vector3());

	isIntersects(p, r2);

	std::cin.get();*/

	Camera* cam = new Camera(60.0, true);
	Scene* scene = new Scene();
	Object* sphere = new Sphere(Vector3(0, 0, -40), 10);
	sphere->getMaterial().color = Color(1, 1, 0);

	Plane* plane = new Plane(Vector3(0, 1, 0), Vector3(0, -20, 0));
	plane->getMaterial().color = Color(1, 0, 0);
	plane->getMaterial().setAlbedo(0.8);

	scene->addObject(sphere);
	scene->addObject(plane);

	Light* directionalLight = new DirectionalLight(Vector3(0, -1, -1), 5);

	scene->addLight(directionalLight);

	Render r(512, 512, scene, cam, Color(0, 0, 0.1));
	
	r.render("out");

}
