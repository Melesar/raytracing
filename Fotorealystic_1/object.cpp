#include "object.h"

Object::~Object()
{
	delete material;
}

void Object::setMaterial(Material * newMaterial)
{
	delete material;
	material = newMaterial;
}

Material* Object::getMaterial()
{
	return material;
}

