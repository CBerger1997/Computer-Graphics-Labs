#define _USE_MATH_DEFINES 

#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "error.h"
#include "file.h"
#include "shader.h"



#define NUM_BUFFERS 1
#define NUM_VAOS 1
GLuint Buffers[NUM_BUFFERS];
GLuint VAOs[NUM_VAOS];

void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose (window, true);

}

void ResizeCallback (GLFWwindow*, int w, int h) {
	glViewport (0, 0, w, h);
}


#define DEG2RAD(n)	n*(M_PI/180)

float* CreateCircle (int num_segments, float radius) {

	float* vertices = (float*)malloc (sizeof (float) * 3 * 3 * num_segments);
	float offset = 360.0f / num_segments;
	float angle = 0;

	for (int i = 0; i < num_segments; i++) {

		vertices[i * 9] = 0;
		vertices[(i * 9) + 1] = 0;
		vertices[(i * 9) + 2] = 0;

		vertices[(i * 9) + 3] = sin (DEG2RAD (angle)) * radius;
		vertices[(i * 9) + 4] = cos (DEG2RAD (angle)) * radius;
		vertices[(i * 9) + 5] = 0;

		vertices[(i * 9) + 6] = sin (DEG2RAD ((angle + offset))) * radius;
		vertices[(i * 9) + 7] = cos (DEG2RAD ((angle + offset))) * radius;
		vertices[(i * 9) + 8] = 0;

		angle += offset;
	}

	return vertices;
}

int main () {
	glfwInit ();

	GLFWwindow* window = glfwCreateWindow (640, 480, "2D modelling", NULL, NULL);
	glfwMakeContextCurrent (window);
	glfwSetKeyCallback (window, KeyCallback);
	glfwSetWindowSizeCallback (window, ResizeCallback);

	gl3wInit ();


	GLuint program = CompileShader ("triangle.vert", "triangle.frag");

	int num_segs = 32;
	float* verts = CreateCircle (num_segs, 0.5f);

	//for (int i = 0; i < 36; i++) {
	//	std::cout << verts[i] << std::endl;
	//}

	glEnable (GL_DEBUG_OUTPUT);
	glDebugMessageCallback (DebugCallback, 0);

	glCreateBuffers (NUM_BUFFERS, Buffers);
	glNamedBufferStorage (Buffers[0], (sizeof (float) * 3 * 3 * num_segs), verts, 0);
	glGenVertexArrays (NUM_VAOS, VAOs);
	glBindVertexArray (VAOs[0]);
	glBindBuffer (GL_ARRAY_BUFFER, Buffers[0]);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, (3 * sizeof (float)), (void*)0);
	glEnableVertexAttribArray (0);

	while (!glfwWindowShouldClose (window)) {
		static const GLfloat bgd[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glClearBufferfv (GL_COLOR, 0, bgd);

		glUseProgram (program);
		glBindVertexArray (VAOs[0]);
		glDrawArrays (GL_TRIANGLES, 0, 3 * num_segs);
		glBindVertexArray (0);

		glfwSwapBuffers (window);
		glfwPollEvents ();
	}

	free (verts);

	glfwDestroyWindow (window);
	glfwTerminate ();
}