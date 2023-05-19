#pragma once

#include "GameObject.h"

class Mushroom : public GameObject
{
public:
	Mushroom (const char*);

	void LoadObject (const char*);
	void LoadMTL (const char*);

private:
	std::map<std::string, glm::vec3> mtl;
};