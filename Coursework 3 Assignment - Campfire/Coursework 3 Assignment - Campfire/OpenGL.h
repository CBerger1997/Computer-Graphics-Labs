#ifndef OPENGL_H
#define OPENGL_H

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include "error.h"
#include "shadow.h"
#include "camera.h"
#include "shader.h"

#define WIDTH 1024
#define HEIGHT 768
#define SH_MAP_WIDTH 2048
#define SH_MAP_HEIGHT 2048

class OpenGl {
public:
	OpenGl ();
	~OpenGl ();

	void Init ();
	void Deinit ();

private:
	GLFWwindow* window;
	ShadowStruct shadow;
	SCamera camera;

	GLuint standardShader;
	GLuint shadowShader;
};

OpenGl::OpenGl () {}

OpenGl::~OpenGl () {}

#endif // !OPENGL_H
