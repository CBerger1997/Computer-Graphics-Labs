#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "error.h"
#include "file.h"
#include "shader.h"


#define NUM_BUFFERS 1
#define NUM_VAOS 1
GLuint Buffers[NUM_BUFFERS];
GLuint VAOs[NUM_VAOS];



float vertices[] =
{
//TL
	//pos					//col			
	//v1
   -1.0f, 0.0f,-1.0f,  		1.0f, 0.0f, 0.0f,

	//v2
	0.0f, 1.0f, 0.0f,		1.0f, 0.0f, 0.0f,

	//v3
   -1.0f, 0.0f, 1.0f,		1.0f, 0.0f, 0.0f,

//TB
	//pos					//col			
	//v1
   -1.0f, 0.0f,-1.0f,		0.0f, 1.0f, 0.0f,

	//v2
	0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 0.0f,

	//v3
	1.0f, 0.0f,-1.0f,		0.0f, 1.0f, 0.0f,

//TR
	//pos					//col			
	//v1
	1.0f, 0.0f,-1.0f,		0.0f, 0.0f, 1.0f,

	//v2
	0.0f, 1.0f, 0.0f,		0.0f, 0.0f, 1.0f,

	//v3
	1.0f, 0.0f, 1.0f,		0.0f, 0.0f, 1.0f,

//TF
	//pos					//col			
	//v1
	1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 0.0f,
	 
	//v2
	0.0f, 1.0f, 0.0f,		1.0f, 1.0f, 0.0f,

	//v3
   -1.0f, 0.0f, 1.0f,		1.0f, 1.0f, 0.0f,

//BL
	//pos					//col			
	//v1
   -1.0f, 0.0f, 1.0f,		1.0f, 0.0f, 1.0f,

	//v2
	0.0f,-1.0f, 0.0f,		1.0f, 0.0f, 1.0f,

	//v3
   -1.0f, 0.0f,-1.0f,		1.0f, 0.0f, 1.0f,

//BB
	//pos					//col			
	//v1
   -1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,

	//v2
	0.0f,-1.0f, 0.0f,		0.0f, 1.0f, 1.0f,

	//v3
	1.0f, 0.0f, 1.0f,		0.0f, 1.0f, 1.0f,

//BR
	//pos					//col			
	//v1
	1.0f, 0.0f, 1.0f,		0.5f, 0.0f, 0.0f,

	//v2
	0.0f,-1.0f, 0.0f,		0.5f, 0.0f, 0.0f,

	//v3
	1.0f, 0.0f,-1.0f,		0.5f, 0.0f, 0.0f,

//BF
	//pos					//col			
	//v1
    1.0f, 0.0f,-1.0f,		0.0f, 0.5f, 0.0f,

	//v2
	0.0f,-1.0f, 0.0f,		0.0f, 0.5f, 0.0f,

	//v3
   -1.0f, 0.0f,-1.0f,		0.0f, 0.5f, 0.0f,

};

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

}

void ResizeCallback(GLFWwindow*, int w, int h)
{
	glViewport(0, 0, w, h);
}


glm::vec3 oct_pos = glm::vec3(0.0f, 0.0f, -5.0f);
glm::vec3 cam_pos = glm::vec3(0.0f, 0.5f, 0.0f);

int main(int argc, char** argv)
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "3D modelling", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetWindowSizeCallback(window, ResizeCallback);

	gl3wInit();

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(DebugCallback, 0);

	unsigned int shaderProgram = CompileShader("triangle.vert", "triangle.frag");



	glCreateBuffers(NUM_BUFFERS, Buffers);
	glGenVertexArrays(NUM_VAOS, VAOs);

	glNamedBufferStorage(Buffers[0], sizeof(vertices), vertices, 0);
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	glEnable(GL_DEPTH_TEST);


	while (!glfwWindowShouldClose(window))
	{
		static const GLfloat bgd[] = { 1.f, 1.f, 1.f, 1.f };
		glClearBufferfv(GL_COLOR, 0, bgd);
		glClear(GL_DEPTH_BUFFER_BIT);


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


		glUseProgram(shaderProgram);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, oct_pos);
		model = glm::rotate(model, (float)glfwGetTime() / 2, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
		
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, -cam_pos);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(90.0f), 640.0f / 480.0f, 1.0f, 10.0f);
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 8*3);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}