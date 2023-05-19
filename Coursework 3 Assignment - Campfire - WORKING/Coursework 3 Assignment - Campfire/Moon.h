#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "GameObject.h"


class Moon : public GameObject
{
public:
	//Moon (const char*);

	void LoadObject (const char*);
	void Draw (GLuint);
private:
	GLuint texture;
};