#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "camera.h"
#include "file.h"
#include "error.h"
#include "shader.h"
#include "shadow.h"
#include "Tree.h"

#define WIDTH 1024
#define HEIGHT 768
#define SH_MAP_WIDTH 2048
#define SH_MAP_HEIGHT 2048

glm::vec3 lightDirection = glm::vec3 (0.1f, -0.81f, -0.61f);
glm::vec3 lightPos = glm::vec3 (2.0f, 6.0f, 7.0f);

std::vector<GameObject> trees;

SCamera camera;
GLFWwindow* window;
ShadowStruct shadow;

GLuint standardShader;
GLuint shadowShader;

void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose (window, true);

	float x_offset = 0.0f;
	float y_offset = 0.0f;
	bool cam_changed = false;

	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
	{
		x_offset = 1.0f;
		y_offset = 0.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
	{
		x_offset = -1.0f;
		y_offset = 0.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
	{
		x_offset = 0.0f;
		y_offset = -1.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
	{
		x_offset = 0.0f;
		y_offset = 1.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_R && action == GLFW_REPEAT)
	{
		cam_dist -= 0.5f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_F && action == GLFW_REPEAT)
	{
		cam_dist += 0.5f;
		cam_changed = true;
	}

	if (cam_changed)
	{
		MoveAndOrientCamera (camera, glm::vec3 (0.0f, 0.0f, 0.0f), cam_dist, x_offset, y_offset);
	}
}

void SizeCallback (GLFWwindow* window, int w, int h)
{
	glViewport (0, 0, w, h);
}

void DrawTreeObjects (unsigned int shader)
{
	for (int i = 0; i < trees.size(); i++)
	{
		trees[i].Draw (shader);
	}
}

void DrawObjects (unsigned int shader)
{
	DrawTreeObjects (shader);

	//floor
	glm::mat4 floorModel = glm::mat4 (1.f);
	floorModel = glm::translate (floorModel, glm::vec3 (0, -1, 0));
	floorModel = glm::scale (floorModel, glm::vec3 (150, 0.1, 50));
	glUniformMatrix4fv (glGetUniformLocation (shader, "model"), 1, GL_FALSE, glm::value_ptr (floorModel));
	glDrawArrays (GL_TRIANGLES, 0, 36);

	//campfire
	for (int i = 0; i < 6; i++)
	{
		glm::mat4 campfireModel = glm::mat4 (1.f);
		campfireModel = glm::rotate (campfireModel, (float)glm::radians (60.0f * i), glm::vec3 (0.0f, 1.0f, 0.0f));
		campfireModel = glm::translate (campfireModel, glm::vec3 (0.0f, 0.0f, 1.0f));
		campfireModel = glm::rotate (campfireModel, (float)glm::radians (45.0f), glm::vec3 (1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv (glGetUniformLocation (shader, "model"), 1, GL_FALSE, glm::value_ptr (campfireModel));
		glDrawArrays (GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray (0);
}

void CreateObjects ()
{
	std::vector<glm::vec3> vects;
	std::vector<glm::vec3> norms;
	std::vector<glm::vec2> uv;

	Tree tree ("tree.mtl");
	tree.LoadObject ("tree.obj", vects, uv, norms);

	for (int i = 0; i < 100; i++)
	{
		tree.Move (glm::vec3 ((rand () % 100) - 50, -1, (rand () % 100) - 50));
		tree.Rotate (glm::vec3 (0.0f, 1.0f, 0.0f), (float)(rand () % 360));
		trees.push_back (tree);
	}
}

//Setup and quit functions
#pragma region SETUPQUIT
void Init ()
{
	glfwInit ();

	window = glfwCreateWindow (WIDTH, HEIGHT, "Campfire Scene", NULL, NULL);
	glfwMakeContextCurrent (window);
	glfwSetKeyCallback (window, KeyCallback);
	glfwSetWindowSizeCallback (window, SizeCallback);

	gl3wInit ();

	glEnable (GL_DEBUG_OUTPUT);
	glDebugMessageCallback (DebugCallback, 0);

	InitCamera (camera);
	cam_dist = 5.f;
	MoveAndOrientCamera (camera, glm::vec3 (0, 0, 0), cam_dist, 0.f, 0.f);

	glEnable (GL_DEPTH_TEST);

	shadow = setup_shadowmap (SH_MAP_WIDTH, SH_MAP_HEIGHT);

	standardShader = CompileShader ("phong.vert", "phong.frag");
	shadowShader = CompileShader ("shadow.vert", "shadow.frag");
}

void Deinit ()
{
	glfwDestroyWindow (window);
	glfwTerminate ();
}
#pragma endregion

//Functions for rendering
#pragma region RENDER
void RenderDepthMap (unsigned int shadowShaderProgram, ShadowStruct shadow, glm::mat4 projectedLightSpaceMatrix)
{
	glViewport (0, 0, SH_MAP_WIDTH, SH_MAP_HEIGHT);

	glBindFramebuffer (GL_FRAMEBUFFER, shadow.FBO);
	glClear (GL_DEPTH_BUFFER_BIT);
	glUseProgram (shadowShaderProgram);
	glUniformMatrix4fv (glGetUniformLocation (shadowShaderProgram, "projectedLightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr (projectedLightSpaceMatrix));

	DrawObjects (shadowShaderProgram);
	glBindFramebuffer (GL_FRAMEBUFFER, 0);
}

void RenderShadows (unsigned int renderShadowProgram, ShadowStruct shadow, glm::mat4 projectedLightSpaceMatrix)
{
	glViewport (0, 0, WIDTH, HEIGHT);

	static const GLfloat bgd[] = { .8f, .8f, .8f, 1.f };
	glClearBufferfv (GL_COLOR, 0, bgd);
	glClear (GL_DEPTH_BUFFER_BIT);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	glUseProgram (renderShadowProgram);

	glBindTexture (GL_TEXTURE_2D, shadow.Texture);

	glUniformMatrix4fv (glGetUniformLocation (renderShadowProgram, "projectedLightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr (projectedLightSpaceMatrix));
	glUniform3f (glGetUniformLocation (renderShadowProgram, "lightDirection"), lightDirection.x, lightDirection.y, lightDirection.z);
	glUniform3f (glGetUniformLocation (renderShadowProgram, "lightColour"), 1.0f, 1.0f, 1.0f);
	glUniform3f (glGetUniformLocation (renderShadowProgram, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f (glGetUniformLocation (renderShadowProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glm::mat4 view = glm::mat4 (1.f);
	view = glm::lookAt (camera.Position, camera.Position + camera.Front, camera.Up);
	glUniformMatrix4fv (glGetUniformLocation (renderShadowProgram, "view"), 1, GL_FALSE, glm::value_ptr (view));

	glm::mat4 projection = glm::mat4 (1.f);
	projection = glm::perspective (glm::radians (45.f), (float)WIDTH / (float)HEIGHT, .01f, 100.f);
	glUniformMatrix4fv (glGetUniformLocation (renderShadowProgram, "projection"), 1, GL_FALSE, glm::value_ptr (projection));

	DrawObjects (renderShadowProgram);
}

void Render ()
{
	float near_plane = 1.0f, far_plane = 70.5f;

	glm::mat4 lightProjection = glm::ortho (-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	glm::mat4 lightView = glm::lookAt (lightPos, lightPos + lightDirection, glm::vec3 (0.0f, 1.0f, 0.0f));
	glm::mat4 projectedLightSpaceMatrix = lightProjection * lightView;

	RenderDepthMap (shadowShader, shadow, projectedLightSpaceMatrix);

	saveShadowMapToBitmap (shadow.Texture, SH_MAP_WIDTH, SH_MAP_HEIGHT);

	RenderShadows (standardShader, shadow, projectedLightSpaceMatrix);

	glfwSwapBuffers (window);
}
#pragma endregion

void RunScene ()
{
	while (!glfwWindowShouldClose (window))
	{
		Render ();
		glfwPollEvents ();
	}
}

int main (int argc, char** argv)
{
	Init ();

	CreateObjects ();

	RunScene ();

	Deinit ();

	return 0;
}