
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "file.h"

#include "Tree.h"

glm::vec3 lightDirection = glm::vec3 (0.1f, -0.81f, -0.61f);
glm::vec3 lightPos = glm::vec3 (2.0f, 6.0f, 7.0f);

std::vector<GameObject> trees;

float vertices[] =
{
	//back face
	//pos					//col				//normal
	-0.25f, -0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	0.0f, 0.0f, -1.0f,
	 0.25f, -0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	0.0f, 0.0f, -1.0f,
	 0.25f,  0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	0.0f, 0.0f, -1.0f,
	 0.25f,  0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	0.0f, 0.0f, -1.0f,
	-0.25f,  0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	0.0f, 0.0f, -1.0f,
	-0.25f, -0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	0.0f, 0.0f, -1.0f,

	//front face
	-0.25f, -0.25f,  1.5f,  	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,
	 0.25f, -0.25f,  1.5f,  	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,
	 0.25f,  0.25f,  1.5f,  	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,
	 0.25f,  0.25f,  1.5f,  	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,
	-0.25f,  0.25f,  1.5f,  	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,
	-0.25f, -0.25f,  1.5f,  	1.0f, 1.0f, 1.0f,	0.0f, 0.0f, 1.0f,

	//left face
	-0.25f,  0.25f,  1.5f,  	1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	-0.25f,  0.25f, -1.5f,  	1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	-0.25f, -0.25f, -1.5f,  	1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	-0.25f, -0.25f, -1.5f,  	1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	-0.25f, -0.25f,  1.5f,  	1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,
	-0.25f,  0.25f,  1.5f,  	1.0f, 1.0f, 1.0f,	-1.0f, 0.0f, 0.0f,

	//right face
	0.25f,  0.25f,  1.5f,  	1.f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f,
	0.25f,  0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f,
	0.25f, -0.25f, -1.5f, 	1.f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f,
	0.25f, -0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f,
	0.25f, -0.25f,  1.5f,  	1.f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f,
	0.25f,  0.25f,  1.5f,  	1.f, 1.0f, 1.0f,	1.0f, 0.0f, 0.0f,

	//bottom face
	-0.25f, -0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	 0.25f, -0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	 0.25f, -0.25f,  1.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	 0.25f, -0.25f,  1.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	-0.25f, -0.25f,  1.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	-0.25f, -0.25f, -1.5f,  	1.f, 1.0f, 1.0f,	0.0f, -1.0f, 0.0f,

	//top face
	-0.25f,  0.25f, -1.5f,  	1.0f, 1.f, 1.0f,	0.0f, 1.0f, 0.0f,
	 0.25f,  0.25f, -1.5f,  	1.0f, 1.f, 1.0f,	0.0f, 1.0f, 0.0f,
	 0.25f,  0.25f,  1.5f,  	1.0f, 1.f, 1.0f,	0.0f, 1.0f, 0.0f,
	 0.25f,  0.25f,  1.5f,  	1.0f, 1.f, 1.0f,	0.0f, 1.0f, 0.0f,
	-0.25f,  0.25f,  1.5f,  	1.0f, 1.f, 1.0f,	0.0f, 1.0f, 0.0f,
	-0.25f,  0.25f, -1.5f, 	1.0f, 1.f, 1.0f,	0.0f, 1.0f, 0.0f,
};

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

	glBindVertexArray (VAOs[0]);

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
	glUniform3f (glGetUniformLocation (renderShadowProgram, "camPos"), Camera.Position.x, Camera.Position.y, Camera.Position.z);
	glUniform3f (glGetUniformLocation (renderShadowProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glm::mat4 view = glm::mat4 (1.f);
	view = glm::lookAt (Camera.Position, Camera.Position + Camera.Front, Camera.Up);
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