#version 450 core

layout (location = 0) out vec4 fCol;

in vec3 col;

uniform vec3 uCol;

void main() {
	fCol = vec4(uCol, 1.0f);
}