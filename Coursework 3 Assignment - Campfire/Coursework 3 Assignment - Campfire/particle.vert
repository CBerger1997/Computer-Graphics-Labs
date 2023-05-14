#version 450 core

layout (location = 0) in vec4 vPos;

out vec2 texture;
out vec4 col;

uniform mat4 projection;
uniform vec2 offset;
uniform vec4 colour;

void main()
{
	float scale = 10.0f;
	texture = vPos.zw;
	col = colour;
	gl_Position = projection * vec4((vPos.xy * scale) + offset, 0.0f, 1.0f);
}