#pragma once
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <vector>

#include "camera.h"
#include "shadow.h"
#include "Tree.h"
#include "Campfire.h"
#include "Ground.h"
#include "Rocks.h"
#include "Grass.h"
#include "Mushroom.h"
#include "Moon.h"
#include "River.h"

#define WIDTH 1024
#define HEIGHT 768
#define SH_MAP_WIDTH 2048
#define SH_MAP_HEIGHT 2048

class Render
{
public:
	void Init ();
	glm::vec3 CalculateTreePosition ();
	glm::vec3 CalculateRiverBoundary ();
	void DrawTreeObjects (unsigned int);
	void DrawRockObjects (unsigned int);
	void DrawGrassObjects (unsigned int);
	void DrawMushroomObjects (unsigned int);
	void DrawObjects (unsigned int, float);
	void CreateObjects ();
	void RenderDepthMap (glm::mat4, float);
	void RenderObjects (glm::mat4, SCamera, float);
	void RenderScene (GLFWwindow*, SCamera, float);
	void DrawTextureObjects (unsigned int);

	static std::vector<Tree> trees;
	static Campfire* campfire;
	static Ground* ground1;
	static Ground* ground2;
	static std::vector<Rock> rocks;
	static std::vector<Grass> grass;
	static std::vector<Mushroom> mushrooms;
	static Moon* moon;
	static River* river;

	static bool isDirectionalLight;
	static ShadowStruct shadow;
private:
	GLuint standardShader;
	GLuint shadowShader;
	GLuint textureShader;

	unsigned int treeCount = 500;
	unsigned int rockCount = 9;
	unsigned int grassCount = 1000;
	unsigned int mushroomCount = 100;


	glm::vec3 lightDirection = glm::vec3 (-0.1f, -0.81f, -0.61f);
	glm::vec3 lightPos = glm::vec3 (0.0f, 2.0f, 0.0f);
};