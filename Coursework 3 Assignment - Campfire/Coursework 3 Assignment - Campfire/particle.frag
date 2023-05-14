#version 450 core

in vec2 texture;
in vec4 col;

out vec4 colour;

unfirom sampler2D sprite;

void main()
{
	colour = (texture ( sprite, texture) * col);
}