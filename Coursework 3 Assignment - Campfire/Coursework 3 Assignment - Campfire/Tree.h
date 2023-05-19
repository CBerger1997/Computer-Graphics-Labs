#pragma once

#include "GameObject.h"

class Tree : public GameObject {
public:
	Tree (const char*);
	
	void LoadObject (const char*, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&);
	void LoadMTL (const char*);

private:
	std::map<std::string, glm::vec3> mtl;
};