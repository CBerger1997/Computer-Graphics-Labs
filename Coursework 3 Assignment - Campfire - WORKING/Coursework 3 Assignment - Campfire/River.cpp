#include "River.h"
#include "GameObject.h"
#include "texture.h"

void River::LoadObject ()
{
	model = glm::mat4 (1.f);
	numVertices = 0;
	texture = setup_texture ("Seamless-Water.bmp");

	std::vector<glm::vec3> polyverts =
	{
		glm::vec3 (-0.02f, 0.0f, -0.08f),
		glm::vec3 (0.0f,  0.0f, -0.08f),
		glm::vec3 (-0.02f, 0.0f, -0.1f),
		glm::vec3 (0.0f,  0.0f, -0.08f),
		glm::vec3 (0.0f,  0.0f, -0.1f),
		glm::vec3 (-0.02f, 0.0f, -0.1f),
	};

	std::vector<glm::vec3> vertices;

	int vertIndex = 0;

	for (int z = 0; z < 1; z++)
	{
		for (int x = 0; x < 25; x++)
		{
			for (int p = 0; p < polyverts.size (); p++)
			{
				if (x > 0)
				{
					if (p == 0)
					{
						vertices.push_back (vertices[(x * 6) + p - 3]);
					}
					else if (p == 2)
					{
						vertices.push_back (vertices[(x * 6) + p - 4]);
					}
					else if (p == 3)
					{
						vertices.push_back (vertices[(x * 6) + p - 2]);
					}
					else if (p == 5)
					{
						vertices.push_back (vertices[(x * 6) + p - 3]);
					}
					else
					{
						float randomFloat = (float)(rand () % 2) - 1 / 10.0f;
						glm::vec3 newPoint = glm::vec3 (polyverts[p].x + (0.02f * x), randomFloat, polyverts[p].z + (0.02f * z));
						vertices.push_back (newPoint);
					}
				}
				else if (p == 3)
				{
					vertices.push_back (vertices[(x * 6) + p - 2]);
				}
				else if (p == 5)
				{
					vertices.push_back (vertices[(x * 6) + p - 3]);
				}
				else
				{
					float randomFloat = (float)(rand () % 3) - 1 / 10.0f;
					glm::vec3 newPoint = glm::vec3 (polyverts[p].x + (0.02f * x), randomFloat, polyverts[p].z + (0.02f * z));
					vertices.push_back (newPoint);
				}

				vertIndex++;
			}
		}
	}

	std::vector<glm::vec2> uvs;

	for (int i = 0; i < vertices.size (); i += 6)
	{
		uvs.push_back (glm::vec2 (0.0f, 0.0f));
		uvs.push_back (glm::vec2 (1.0f, 0.0f));
		uvs.push_back (glm::vec2 (0.0f, 1.0f));
		uvs.push_back (glm::vec2 (1.0f, 0.0f));
		uvs.push_back (glm::vec2 (1.0f, 1.0f));
		uvs.push_back (glm::vec2 (0.0f, 1.0f));
	}

	//std::vector<glm::vec3> normals;
	//std::vector<glm::vec3> colours;

	//for (int i = 0; i < vertices.size (); i += 3)
	//{
	//	glm::vec3 normal = glm::vec3 (0.0f, 1.0f, 0.0f);

	//	glm::vec3 p1, p2, p3;
	//	glm::vec3 A, B;

	//	p1 = vertices[i];
	//	p2 = vertices[i + 1];
	//	p3 = vertices[i + 2];

	//	A = p2 - p1;
	//	B = p3 - p1;

	//	normal.x = A.y * B.z - A.z * B.y;
	//	normal.y = A.z * B.x - A.x * B.z;
	//	normal.z = A.x * B.y - A.y * B.x;

	//	normals.push_back (normal);
	//	normals.push_back (normal);
	//	normals.push_back (normal);
	//	colours.push_back (glm::vec3 (0.0f, 0.0f, 1.0f));
	//	colours.push_back (glm::vec3 (0.0f, 0.0f, 1.0f));
	//	colours.push_back (glm::vec3 (0.0f, 0.0f, 1.0f));
	//}

	numVertices = 150;

	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);

	glCreateBuffers (1, &VBO[0]);
	glNamedBufferStorage (VBO[0], sizeof (float) * numVertices * 3, &vertices[0], 0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (0);

	glCreateBuffers (1, &VBO[1]);
	glNamedBufferStorage (VBO[1], sizeof (float) * numVertices * 2, &uvs[0], 0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (1);

	glBindBuffer (GL_ARRAY_BUFFER, 0);
	glBindVertexArray (0);

	SetTransformations (glm::vec3 (0.0f, 0.0f, 0.0f), glm::vec3 (0.0f, 0.0f, 0.0f), 0, glm::vec3 (1.0f, 1.0f, 1.0f));

	Move (glm::vec3 (0, -1, 0));
	Scale (glm::vec3 (150, 0.1, 150));
}

void River::Draw (GLuint shaderProgram)
{
	glBindTexture (GL_TEXTURE_2D, texture);

	GameObject::Draw (shaderProgram);
}