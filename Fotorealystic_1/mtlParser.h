#pragma once

#include <map>

class Material;

class MtlParser
{
public: 

	std::map<std::string, Material*>* parse(const std::string& fileName);

private:

	Material* currentMaterial;

	void swapMaterial(std::map<std::string, Material*>& map, std::stringstream& stream);
	void loadDiffuseTexture(std::stringstream& stream);
};