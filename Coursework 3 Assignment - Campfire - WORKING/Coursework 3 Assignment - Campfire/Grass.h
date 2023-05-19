#pragma once

#include "GameObject.h"

class Grass : public GameObject
{
public:
	Grass (const char*);

	void LoadObject (const char*);
	void LoadMTL (const char*);

private:
	std::map<std::string, glm::vec3> mtl;
};
