#pragma once

#include <GL/gl3w.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

class GameObject
{
public:
	GameObject ();
	GameObject (const char*);
	~GameObject ();

	void LoadObject (const char*, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&);
	void LoadMTL (const char*);
	void Draw ();

	glm::vec3 position;
	float rotation;

private:
	bool isUsingMtl;

	std::map<std::string, glm::vec3> mtl;
	GLuint VAO;
	GLuint VBO[3];
	unsigned int numVertices;
	std::vector<int> vertIndices, uvIndices, normIndices;
};