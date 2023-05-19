#pragma once

#include <GL/gl3w.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>

class GameObject
{
public:
	GameObject ();

	~GameObject ();

	virtual void LoadObject (const char*, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&) {};
	virtual void LoadMTL (const char*) {};

	void Draw (GLuint);
	void SetTransformations (glm::vec3, glm::vec3, float, glm::vec3);
	void ApplyTransformations ();
	void Rotate (glm::vec3, float);
	void Move (glm::vec3);
	void Scale (glm::vec3);

protected:
	//Model Parameters
	glm::mat4 model;

	//Transformation Parameters
	glm::vec3 scale;
	glm::vec3 position;
	glm::vec3 rotation;
	float rotationDegrees;

	//VAO / VBO Parameters
	GLuint VAO;
	GLuint VBO[3];

	//Vertex Data Parameters
	unsigned int numVertices;
};