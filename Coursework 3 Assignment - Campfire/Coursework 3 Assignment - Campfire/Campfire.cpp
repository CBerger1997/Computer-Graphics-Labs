#include "Campfire.h"

void Campfire::LoadObject ()
{
	float vertices[] =
	{
		//back face
		-0.25f, -0.25f, -1.5f,
		 0.25f, -0.25f, -1.5f,
		 0.25f,  0.25f, -1.5f,
		 0.25f,  0.25f, -1.5f,
		-0.25f,  0.25f, -1.5f,
		-0.25f, -0.25f, -1.5f,

		//front face
		-0.25f, -0.25f,  1.5f,
		 0.25f, -0.25f,  1.5f,
		 0.25f,  0.25f,  1.5f,
		 0.25f,  0.25f,  1.5f,
		-0.25f,  0.25f,  1.5f,
		-0.25f, -0.25f,  1.5f,

		//left face
		-0.25f,  0.25f,  1.5f,
		-0.25f,  0.25f, -1.5f,
		-0.25f, -0.25f, -1.5f,
		-0.25f, -0.25f, -1.5f,
		-0.25f, -0.25f,  1.5f,
		-0.25f,  0.25f,  1.5f,

		//right face
		0.25f,  0.25f,  1.5f,
		0.25f,  0.25f, -1.5f,
		0.25f, -0.25f, -1.5f,
		0.25f, -0.25f, -1.5f,
		0.25f, -0.25f,  1.5f,
		0.25f,  0.25f,  1.5f,

		//bottom face
		-0.25f, -0.25f, -1.5f,
		 0.25f, -0.25f, -1.5f,
		 0.25f, -0.25f,  1.5f,
		 0.25f, -0.25f,  1.5f,
		-0.25f, -0.25f,  1.5f,
		-0.25f, -0.25f, -1.5f,

		//top face
		-0.25f,  0.25f, -1.5f,
		 0.25f,  0.25f, -1.5f,
		 0.25f,  0.25f,  1.5f,
		 0.25f,  0.25f,  1.5f,
		-0.25f,  0.25f,  1.5f,
		-0.25f,  0.25f, -1.5f,
	};

	float normals[] =
	{
		//back face
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		//front face
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		//left face
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		//right face
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		//bottom face
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		//top face
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	float colours[] =
	{
		//back face
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,

		//front face
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,

		//left face
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,

		//right face
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,

		//bottom face
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,

		//top face
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
		0.6f, 0.3f, 0.0f,
	};

	glBindVertexArray (VAO);

	glCreateBuffers (1, &VBO[0]);
	glNamedBufferStorage (VBO[0], sizeof (float)* numVertices * 3, &vertices[0], 0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (0);

	//if (uvCoords.size () > 0 && !isUsingMtl)
	//{
	//	glGenBuffers (1, &VBO[1]);
	//	glBindBuffer (GL_ARRAY_BUFFER, VBO[1]);
	//	glBufferData (GL_ARRAY_BUFFER, sizeof (float) * numVertices * 2, &uvCoords[0], GL_STATIC_DRAW);
	//	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	//	glEnableVertexAttribArray (1);
	//}

	glCreateBuffers (1, &VBO[1]);
	glNamedBufferStorage (VBO[1], sizeof (float)* numVertices * 3, &normals[0], GL_STATIC_DRAW);
	glBindBuffer (GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (1);

	glCreateBuffers (1, &VBO[2]);
	glNamedBufferStorage (VBO[2], sizeof (float)* numVertices * 3, &colours[0], GL_STATIC_DRAW);
	glBindBuffer (GL_ARRAY_BUFFER, VBO[2]);
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (2);

	glBindBuffer (GL_ARRAY_BUFFER, 0);
	glBindVertexArray (0);
}

void Campfire::LoadMTL ()
{

}