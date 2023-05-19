#include "Moon.h"

#include "texture.h"

void Moon::LoadObject (const char* path)
{
	glGenVertexArrays (1, &VAO);
	model = glm::mat4 (1.f);
	numVertices = 0;

	texture = setup_texture ("Moon.bmp");

	std::ifstream inputFile (path);

	if (inputFile.is_open ())
	{
		std::vector<glm::vec3> vertCoords;
		std::vector<glm::vec3> normCoords;
		std::vector<glm::vec2> uvCoords;

		std::vector<glm::vec3> tempVertCoords;
		std::vector<glm::vec3> tempNormCoords;
		std::vector<glm::vec2> tempUVCoords;

		std::string currentLine;

		glm::vec3 iterationColours;

		while (std::getline (inputFile, currentLine))
		{
			std::stringstream currentLineStream (currentLine);

			glm::vec3 data;

			std::string rejectedData;

			if (!currentLine.substr (0, 2).compare (0, 2, "vn"))
			{
				currentLineStream >> rejectedData >> data.x >> data.y >> data.z;

				tempNormCoords.push_back (data);
			}
			else if (!currentLine.substr (0, 2).compare (0, 2, "vt"))
			{
				currentLineStream >> rejectedData >> data.x >> data.y;

				tempUVCoords.push_back (data);
			}
			else if (!currentLine.substr (0, 2).compare (0, 1, "v"))
			{
				currentLineStream >> rejectedData >> data.x >> data.y >> data.z;

				tempVertCoords.push_back (data);
			}
			else if (!currentLine.substr (0, 2).compare (0, 1, "f"))
			{
				std::string vertData[4];

				currentLineStream >> rejectedData >> vertData[0] >> vertData[1] >> vertData[2] >> vertData[3];

				for (unsigned int i = 0; i < 3; i++)
				{
					std::stringstream currentSection (vertData[i]);

					unsigned int vertID = 0;
					unsigned int uvID = 0;
					unsigned int normID = 0;

					char ignoredData;
					currentSection >> vertID >> ignoredData >> uvID >> ignoredData >> normID;

					if (vertID > 0)
					{
						vertCoords.push_back (tempVertCoords[vertID - 1]);
					}
					if (normID > 0)
					{
						normCoords.push_back (tempNormCoords[normID - 1]);
					}
					if (uvID > 0)
					{
						uvCoords.push_back (tempUVCoords[uvID - 1]);
					}
				}
			}
		}

		inputFile.close ();

		numVertices = vertCoords.size ();

		if (numVertices > 0)
		{
			glBindVertexArray (VAO);

			glCreateBuffers (1, &VBO[0]);
			glNamedBufferStorage (VBO[0], sizeof (float) * numVertices * 3, &vertCoords[0], 0);
			glBindBuffer (GL_ARRAY_BUFFER, VBO[0]);
			glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray (0);

			glCreateBuffers (1, &VBO[1]);
			glNamedBufferStorage (VBO[1], sizeof (float) * numVertices * 2, &uvCoords[0], 0);
			glBindBuffer (GL_ARRAY_BUFFER, VBO[1]);
			glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray (1);

			//glCreateBuffers (1, &VBO[2]);
			//glNamedBufferStorage (VBO[2], sizeof (float) * numVertices * 3, &normCoords[0], 0);
			//glBindBuffer (GL_ARRAY_BUFFER, VBO[2]);
			//glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, 0);
			//glEnableVertexAttribArray (2);

			//glBindBuffer (GL_ARRAY_BUFFER, 0);
			//glBindVertexArray (0);
		}
	}
	else
	{
		std::cout << "The file was not found in directory: " << path << std::endl;
	}
}

void Moon::Draw (GLuint shaderProgram)
{
	glBindTexture (GL_TEXTURE_2D, texture);

	GameObject::Draw(shaderProgram);
}