#version 450 core

layout (location = 0) out vec4 fCol;

in vec2 tex;

uniform sampler2D Texture;

void main() 
{
	fCol = texture(Texture, tex);
}