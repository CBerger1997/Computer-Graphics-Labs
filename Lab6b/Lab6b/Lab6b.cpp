
#include <GL/gl3w.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.h"
#include "file.h"
#include "error.h"
#include "shader.h"
#include "texture.h"

#include <iostream>

float vertices[] =
{
	//t1				
	//pos					//tex
   -0.9f, 0.9f, 0.f,		0.0f, 1.0f,		//tl
	0.9f, 0.9f, 0.f,		1.0f, 1.0f,		//tr
	0.9f,-0.9f, 0.f,		1.0f, 0.0f,		//br
	//t2					
	//pos					//tex
   -0.9f, 0.9f, 0.f,		0.0f, 1.0f,		//tl
	0.9f,-0.9f, 0.f,		1.0f, 0.0f,		//br
   -0.9f,-0.9f, 0.f,		0.0f, 0.0f,		//bl
};


SCamera Camera;

#define NUM_BUFFERS 1
#define NUM_VAOS 1
GLuint Buffers[NUM_BUFFERS];
GLuint VAOs[NUM_VAOS];

#define WIDTH 640
#define HEIGHT 480



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



int main (int argc, char** argv)
{
	glfwInit ();

	GLFWwindow* window = glfwCreateWindow (WIDTH, HEIGHT, "Texture", NULL, NULL);
	glfwMakeContextCurrent (window);
	glfwSetKeyCallback (window, KeyCallback);
	glfwSetWindowSizeCallback (window, SizeCallback);

	gl3wInit ();

	glEnable (GL_DEBUG_OUTPUT);
	glDebugMessageCallback (DebugCallback, 0);

	GLuint program = CompileShader ("triangle.vert", "triangle.frag");

	InitCamera (Camera);
	Camera.Yaw = -90.f;
	Camera.Pitch = 90.f;
	cam_dist = 3.f;
	MoveAndOrientCamera (Camera, glm::vec3 (0, 0, 0), cam_dist, 0.f, 0.f);

	//const char* files[11] = {
	//	"mipmaps/grid1024x1024.bmp",
	//	"mipmaps/grid512x512.bmp",
	//	"mipmaps/grid256x256.bmp",
	//	"mipmaps/grid128x128.bmp",
	//	"mipmaps/grid64x64.bmp",
	//	"mipmaps/grid32x32.bmp",
	//	"mipmaps/grid16x16.bmp",
	//	"mipmaps/grid8x8.bmp",
	//	"mipmaps/grid4x4.bmp",
	//	"mipmaps/grid2x2.bmp",
	//	"mipmaps/grid1x1.bmp"
	//};

	//GLuint texture = setup_mipmaps (files, 11);
	GLuint texture = setup_texture ("grid.bmp");

	glCreateBuffers (NUM_BUFFERS, Buffers);
	glNamedBufferStorage (Buffers[0], sizeof (vertices), vertices, 0);
	glGenVertexArrays (NUM_VAOS, VAOs);
	glBindVertexArray (VAOs[0]);
	glBindBuffer (GL_ARRAY_BUFFER, Buffers[0]);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, (5 * sizeof (float)), (void*)0);
	glEnableVertexAttribArray (0);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, (5 * sizeof (float)), (void*)(3 * sizeof (float)));
	glEnableVertexAttribArray (1);

	glEnable (GL_DEPTH_TEST);

	while (!glfwWindowShouldClose (window))
	{
		static const GLfloat bgd[] = { .8f, .8f, .8f, 1.f };
		glClearBufferfv (GL_COLOR, 0, bgd);
		glClear (GL_DEPTH_BUFFER_BIT);
		glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

		glUseProgram (program);

		glm::mat4 model = glm::mat4 (1.f);
		model = glm::rotate (model, glm::radians (90.f), glm::vec3 (1.f, 0.f, 0.f));
		glUniformMatrix4fv (glGetUniformLocation (program, "model"), 1, GL_FALSE, glm::value_ptr (model));

		glm::mat4 view = glm::mat4 (1.f);
		view = glm::lookAt (Camera.Position, Camera.Position + Camera.Front, Camera.Up);
		glUniformMatrix4fv (glGetUniformLocation (program, "view"), 1, GL_FALSE, glm::value_ptr (view));

		glm::mat4 projection = glm::mat4 (1.f);
		projection = glm::perspective (glm::radians (45.f), (float)WIDTH / (float)HEIGHT, .01f, 100.f);
		glUniformMatrix4fv (glGetUniformLocation (program, "projection"), 1, GL_FALSE, glm::value_ptr (projection));

		glBindTexture (GL_TEXTURE_2D, texture);
		glUseProgram (program);
		glBindVertexArray (VAOs[0]);
		glDrawArrays (GL_TRIANGLES, 0, 6);
		glBindVertexArray (0);

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}


	glfwDestroyWindow (window);
	glfwTerminate ();

	return 0;
}