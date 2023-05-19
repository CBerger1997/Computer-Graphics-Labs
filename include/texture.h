#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

GLuint setup_texture (const char* filename);

GLuint setup_mipmaps (const char* filename[], int n);