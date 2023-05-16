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

class GameObject {
public:
	explicit GameObject ();
	explicit GameObject (const char*);

	~GameObject ();

	void LoadObject (const char*, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&);
	void LoadMTL (const char*);
	void Draw (GLuint);
	virtual void SetTransformations (glm::vec3, glm::vec3, float, glm::vec3) {};
	virtual void ApplyTransformations () {};
	virtual void Rotate (glm::vec3, float) {};
	virtual void Move (glm::vec3) {};
	virtual void Scale (glm::vec3) {};

protected:
	//Model Parameters
	glm::mat4 model;

	//Transformation Parameters
	glm::vec3 scale;
	glm::vec3 position;
	glm::vec3 rotation;
	float rotationDegrees;

private:
	//VAO and VBO Parameters
	GLuint VAO;
	GLuint VBO[3];

	//Vertex Data Parameters
	unsigned int numVertices;

	//Material Parameters
	bool isUsingMtl;
	std::map<std::string, glm::vec3> mtl;
};