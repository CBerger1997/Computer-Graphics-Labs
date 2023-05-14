#ifndef OBJECT_LOADER_H
#define OBJECT_LOADER_H

class GameObject
{
public:
	GameObject ();
	~GameObject ();

	void LoadObject (std::string, std::vector<glm::vec3>&, std::vector<glm::vec2>&, std::vector<glm::vec3>&);

	void Draw ();

private:
	GLuint VAO;
	unsigned int numVertices;

	std::vector<int> vertIndices, uvIndices, normIndices;
};

GameObject::GameObject ()
{
	VAO = 0;
	glGenVertexArrays (1, &VAO);
	numVertices = 0;
}

GameObject::~GameObject ()
{
	glDeleteVertexArrays (1, &VAO);
}

void GameObject::LoadObject (std::string path, std::vector<glm::vec3>& verts, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& norms)
{
	std::ifstream inputFile (path);

	if (inputFile.is_open ())
	{
		std::vector<glm::vec2> uvCoords;
		std::vector<glm::vec3> vertCoords;
		std::vector<glm::vec3> normCoords;

		std::vector<glm::vec2> tempUvCoords;
		std::vector<glm::vec3> tempVertCoords;
		std::vector<glm::vec3> tempNormCoords;

		std::string currentLine;

		while (std::getline (inputFile, currentLine))
		{
			std::stringstream currentLineStream (currentLine);

			float x;
			float y;
			float z;

			std::string ignoredData;

			if (!currentLine.substr (0, 2).compare (0, 2, "vt"))
			{
				currentLineStream >> ignoredData >> x >> y;
				tempUvCoords.push_back (glm::vec2 (x, y));
			}
			else if (!currentLine.substr (0, 2).compare (0, 2, "vn"))
			{
				currentLineStream >> ignoredData >> x >> y >> z;

				tempNormCoords.push_back (glm::vec3 (x, y, z));
			}
			else if (!currentLine.substr (0, 2).compare (0, 1, "v"))
			{
				currentLineStream >> ignoredData >> x >> y >> z;

				tempVertCoords.push_back (glm::vec3 (x, y, z));
			}
			else if (!currentLine.substr (0, 2).compare (0, 1, "f"))
			{
				std::string vertData[4];

				currentLineStream >> ignoredData >> vertData[0] >> vertData[1] >> vertData[2] >> vertData[3];

				if (vertData[3].empty ())
				{
					for (unsigned int i = 0; i < 3; i++)
					{
						std::stringstream currentSection (vertData[i]);

						unsigned int posID = 0;
						unsigned int uvID = 0;
						unsigned int normID = 0;

						if (vertData[i].find ('/') == std::string::npos)
						{
							currentSection >> posID;
						}
						else if (vertData[i].find ('/') == std::string::npos)
						{
							char ignoredData;
							currentSection >> posID >> ignoredData >> ignoredData >> normID;
						}
						else
						{
							char ignoredData;
							currentSection >> posID >> ignoredData >> uvID >> ignoredData >> normID;
						}

						if (posID > 0)
						{
							vertCoords.push_back (tempVertCoords[posID - 1]);
						}
						if (uvID > 0)
						{
							uvCoords.push_back (tempUvCoords[uvID - 1]);
						}
						if (normID > 0)
						{
							normCoords.push_back (tempNormCoords[normID - 1]);
						}
					}
				}
				else
				{
					std::cout << "Quad has been detected, the model needs to be triangulated" << std::endl;
					inputFile.close ();
				}
			}
		}

		inputFile.close ();

		//sets the amount of vertices
		numVertices = vertCoords.size ();

		//checks whether the amount of vertices is greater than 0
		if (numVertices > 0)
		{
			glBindVertexArray (VAO);
			GLuint posBuffer = 0;
			glGenBuffers (1, &posBuffer);
			glBindBuffer (GL_ARRAY_BUFFER, posBuffer);
			glBufferData (GL_ARRAY_BUFFER, sizeof (float) * numVertices * 3, &vertCoords[0], GL_STATIC_DRAW);
			glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray (0);

			if (normCoords.size () > 0)
			{
				GLuint normBuffer = 0;
				glGenBuffers (1, &normBuffer);
				glBindBuffer (GL_ARRAY_BUFFER, normBuffer);
				glBufferData (GL_ARRAY_BUFFER, sizeof (float) * numVertices * 3, &normCoords[0], GL_STATIC_DRAW);
				glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray (1);
			}
			if (uvCoords.size () > 0)
			{
				GLuint texBuffer = 0;
				glGenBuffers (1, &texBuffer);
				glBindBuffer (GL_ARRAY_BUFFER, texBuffer);
				glBufferData (GL_ARRAY_BUFFER, sizeof (float) * numVertices * 2, &uvCoords[0], GL_STATIC_DRAW);
				glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, 0, 0);
				glEnableVertexAttribArray (2);
			}
		}
	}
	else
	{
		std::cout << "The file was not found in directory: " << path << std::endl;
	}
}

void GameObject::Draw ()
{
	glBindVertexArray (VAO);
	glDrawArrays (GL_TRIANGLES, 0, numVertices);
	glBindVertexArray (0);
}

#endif // !OBJECT_LOADER_H