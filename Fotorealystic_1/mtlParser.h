#pragma once

#include <map>

class PhongMaterial;

class MtlParser
{
public: 

	std::map<std::string, PhongMaterial*>* parse(const std::string& fileName);

private:

	PhongMaterial* currentMaterial;

	void swapMaterial(std::map<std::string, PhongMaterial*>& map, std::stringstream& stream);
	void loadDiffuseTexture(std::stringstream& stream);
};