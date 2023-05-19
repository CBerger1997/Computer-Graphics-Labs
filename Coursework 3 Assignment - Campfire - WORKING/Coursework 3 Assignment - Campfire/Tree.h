#pragma once

#include "GameObject.h"

class Tree : public GameObject
{
public:
	Tree (const char*);

	void LoadObject (const char*);
	void LoadMTL (const char*);

private:
	std::map<std::string, glm::vec3> mtl;
};