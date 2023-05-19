#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Tree.h"
#include "Campfire.h"
#include "Ground.h"
#include "Render.h"

class Scene
{
public:
	Scene ();
	~Scene ();


	void Init ();
	void Deinit ();
	void RunScene ();

private:
	GLFWwindow* window;
	Render render;
	float deltaTime;
};