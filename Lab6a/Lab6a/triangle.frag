#version 450 core

layout (location = 0) out vec4 fCol;

in vec3 col;

void main() {
	fCol = vec4(col, 1.0f);
}