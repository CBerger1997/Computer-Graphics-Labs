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
#include "object_loader.h"

glm::vec3 lightDirection = glm::vec3 (0.1f, -0.81f, -0.61f);
glm::vec3 lightPos = glm::vec3 (2.0f, 6.0f, 7.0f);

SCamera Camera;

#define NUM_BUFFERS 2
#define NUM_VAOS 2
GLuint Buffers[NUM_BUFFERS];
GLuint VAOs[NUM_VAOS];

#define WIDTH 1024
#define HEIGHT 768
#define SH_MAP_WIDTH 2048
#define SH_MAP_HEIGHT 2048

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

void drawFloorAndCubes (unsigned int shaderProgram)
{
	glBindVertexArray (VAOs[0]);

	//floor
	glm::mat4 floorModel = glm::mat4 (1.f);
	floorModel = glm::translate (floorModel, glm::vec3 (0, -1, 0));
	floorModel = glm::scale (floorModel, glm::vec3 (100, 0.1, 100));
	glUniformMatrix4fv (glGetUniformLocation (shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr (floorModel));
	glDrawArrays (GL_TRIANGLES, 0, 36);

	//campfire
	for (int i = 0; i < 6; i++)
	{
		glm::mat4 campfireModel = glm::mat4 (1.f);
		campfireModel = glm::rotate (campfireModel, (float)glm::radians (60.0f * i), glm::vec3 (0.0f, 1.0f, 0.0f));
		campfireModel = glm::translate (campfireModel, glm::vec3 (0.0f, 0.0f, 1.0f));
		campfireModel = glm::rotate (campfireModel, (float)glm::radians (45.0f), glm::vec3 (1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv (glGetUniformLocation (shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr (campfireModel));
		glDrawArrays (GL_TRIANGLES, 0, 36);
	}
}

void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose (window, true);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		lightDirection = Camera.Front;
	}

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
		cam_dist -= 0.1f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_F && action == GLFW_REPEAT)
	{
		cam_dist += 0.1f;
		cam_changed = true;
	}

	if (cam_changed)
	{
		MoveAndOrientCamera (Camera, glm::vec3 (0.0f, 0.0f, 0.0f), cam_dist, x_offset, y_offset);
	}
}

void SizeCallback (GLFWwindow* window, int w, int h)
{
	glViewport (0, 0, w, h);
}

void renderWithShadow (unsigned int renderShadowProgram, ShadowStruct shadow, glm::mat4 projectedLightSpaceMatrix)
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
	glUniform3f (glGetUniformLocation (renderShadowProgram, "lightColour"), 0.0f, 0.0f, 1.0f);
	glUniform3f (glGetUniformLocation (renderShadowProgram, "camPos"), Camera.Position.x, Camera.Position.y, Camera.Position.z);
	glUniform3f (glGetUniformLocation (renderShadowProgram, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	glm::mat4 view = glm::mat4 (1.f);
	view = glm::lookAt (Camera.Position, Camera.Position + Camera.Front, Camera.Up);
	glUniformMatrix4fv (glGetUniformLocation (renderShadowProgram, "view"), 1, GL_FALSE, glm::value_ptr (view));

	glm::mat4 projection = glm::mat4 (1.f);
	projection = glm::perspective (glm::radians (45.f), (float)WIDTH / (float)HEIGHT, .01f, 100.f);
	glUniformMatrix4fv (glGetUniformLocation (renderShadowProgram, "projection"), 1, GL_FALSE, glm::value_ptr (projection));

	drawFloorAndCubes (renderShadowProgram);
}

void generateDepthMap (unsigned int shadowShaderProgram, ShadowStruct shadow, glm::mat4 projectedLightSpaceMatrix)
{
	glViewport (0, 0, SH_MAP_WIDTH, SH_MAP_HEIGHT);

	glBindFramebuffer (GL_FRAMEBUFFER, shadow.FBO);
	glClear (GL_DEPTH_BUFFER_BIT);
	glUseProgram (shadowShaderProgram);
	glUniformMatrix4fv (glGetUniformLocation (shadowShaderProgram, "projectedLightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr (projectedLightSpaceMatrix));

	drawFloorAndCubes (shadowShaderProgram);
	glBindFramebuffer (GL_FRAMEBUFFER, 0);
}

int main (int argc, char** argv)
{
	glfwInit ();

	GLFWwindow* window = glfwCreateWindow (WIDTH, HEIGHT, "Lighting", NULL, NULL);
	glfwMakeContextCurrent (window);
	glfwSetKeyCallback (window, KeyCallback);
	glfwSetWindowSizeCallback (window, SizeCallback);

	gl3wInit ();

	glEnable (GL_DEBUG_OUTPUT);
	glDebugMessageCallback (DebugCallback, 0);

	ShadowStruct shadow = setup_shadowmap (SH_MAP_WIDTH, SH_MAP_HEIGHT);

	GLuint program = CompileShader ("phong.vert", "phong.frag");
	GLuint shadow_program = CompileShader ("shadow.vert", "shadow.frag");

	InitCamera (Camera);
	cam_dist = 5.f;
	MoveAndOrientCamera (Camera, glm::vec3 (0, 0, 0), cam_dist, 0.f, 0.f);

	// Read our .obj file
	std::vector< glm::vec3 > verts;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > norms; // Won't be used at the moment.

	GameObject tree;

	tree.LoadObject ("tree_obj.obj", verts, uvs, norms);

	glCreateBuffers (NUM_BUFFERS, Buffers);
	glNamedBufferStorage (Buffers[0], sizeof (vertices), vertices, 0);
	glNamedBufferStorage (Buffers[1], verts.size () * sizeof (glm::vec3), &verts[0], 0);
	glGenVertexArrays (NUM_VAOS, VAOs);
	glBindVertexArray (VAOs[0]);
	glBindBuffer (GL_ARRAY_BUFFER, Buffers[0]);
	glBindBuffer (GL_ARRAY_BUFFER, Buffers[1]);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof (float)), (void*)0);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof (float)), (void*)(3 * sizeof (float)));
	glEnableVertexAttribArray (1);
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof (float)), (void*)(6 * sizeof (float)));
	glEnableVertexAttribArray (2);

	glEnable (GL_DEPTH_TEST);

	while (!glfwWindowShouldClose (window))
	{
		float near_plane = 1.0f, far_plane = 70.5f;

		glm::mat4 lightProjection = glm::ortho (-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		glm::mat4 lightView = glm::lookAt (lightPos, lightPos + lightDirection, glm::vec3 (0.0f, 1.0f, 0.0f));
		glm::mat4 projectedLightSpaceMatrix = lightProjection * lightView;

		generateDepthMap (shadow_program, shadow, projectedLightSpaceMatrix);

		//saveShadowMapToBitmap (shadow.Texture, SH_MAP_WIDTH, SH_MAP_HEIGHT);

		renderWithShadow (program, shadow, projectedLightSpaceMatrix);

		tree.Draw ();

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	glfwDestroyWindow (window);
	glfwTerminate ();

	return 0;
}