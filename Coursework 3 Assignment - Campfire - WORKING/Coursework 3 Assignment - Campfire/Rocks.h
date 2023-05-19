#pragma once
#include "GameObject.h"

class Rock : public GameObject
{
public:
	Rock (const char*);

	void LoadObject (const char*);
	void LoadMTL (const char*);

private:
	std::map<std::string, glm::vec3> mtl;
};