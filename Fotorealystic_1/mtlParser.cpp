#include "mtlParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "image.h"

#include "phongMaterial.h"
#include "utils.h"


std::map<std::string, PhongMaterial*>* MtlParser::parse(const std::string & fileName)
{
	std::map<std::string, PhongMaterial*>* materialsMap = new std::map<std::string, PhongMaterial*>();

	std::string s;
	std::ifstream file(fileName.c_str());

	while (std::getline(file, s)) {
		std::string token;
		std::stringstream sstream(s);

		sstream >> token;
		if (token == "newmtl") {
			//Create new material and put it in the map
			swapMaterial(*materialsMap, sstream);
		} else if (token == "Ns") {
			//Set specular exponent of the material
			double specularPower;
			sstream >> specularPower;
			currentMaterial->setSpecularPower(specularPower);
		} else if (token == "Kd") {
			//Set diffuse color of the material
			Color diffuseColor;
			sstream >> diffuseColor;
			currentMaterial->setDiffuse(diffuseColor);
		} else if (token == "Ks") {
			//Set specular color of the material
			Color specularColor;
			sstream >> specularColor;
			currentMaterial->setSpecular(specularColor);
		} else if (token == "map_Kd") {
			//Parse and load diffuse texture of the material
			loadDiffuseTexture(sstream);
		}
	}

	return materialsMap;
}

void MtlParser::swapMaterial(std::map<std::string, PhongMaterial*> & map, std::stringstream & stream)
{
	std::string materialName;
	stream >> materialName;

	currentMaterial = new PhongMaterial();
	std::pair<std::string, PhongMaterial*> pair(materialName, currentMaterial);
	map.insert(pair);
}

void MtlParser::loadDiffuseTexture(std::stringstream & stream)
{
	//For now we only get the texture itself, ignoring all the modifiers
	std::string streamContents = stream.str();
	int lastSpacePos = streamContents.find_last_of(' ');
	std::string texturePath = streamContents.substr(lastSpacePos + 1);
	
	Utils::replace(texturePath, "\\", "/");

	try {
		Image* diffuseTexture = new Image(texturePath);
		currentMaterial->setDiffuseMap(diffuseTexture);
	} catch (const int&) {
		std::cout << "Failed to load diffuse texture from the path: " << texturePath << std::endl;
	}
	
}
