#include "Tree.h"

Tree::Tree (const char* path)
{
	glGenVertexArrays (1, &VAO);

	numVertices = 0;
	LoadMTL (path);
}

void Tree::LoadMTL (const char* path)
{
	std::ifstream mtlFile (path);

	std::string currentLine;
	std::string name;

	while (std::getline (mtlFile, currentLine))
	{
		std::stringstream currentLineStream (currentLine);
		std::string ignoredData;

		float x, y, z;

		if (!currentLine.substr (0, 6).compare (0, 6, "newmtl"))
		{
			currentLineStream >> ignoredData >> name;
		}
		else if (!currentLine.substr (0, 2).compare (0, 2, "Kd"))
		{
			currentLineStream >> ignoredData >> x >> y >> z;
			mtl.insert (std::pair<std::string, glm::vec3> (name, glm::vec3 (x, y, z)));
		}
	}
}

void Tree::LoadObject (const char* path, std::vector<glm::vec3>& verts, std::vector<glm::vec2>& uvs, std::vector<glm::vec3>& norms)
{
	std::ifstream inputFile (path);

	if (inputFile.is_open ())
	{
		std::vector<glm::vec2> uvCoords;
		std::vector<glm::vec3> vertCoords;
		std::vector<glm::vec3> normCoords;
		std::vector<glm::vec3> colourCoords;

		std::vector<glm::vec2> tempUvCoords;
		std::vector<glm::vec3> tempVertCoords;
		std::vector<glm::vec3> tempNormCoords;

		std::string currentLine;

		glm::vec3 iterationColours;

		while (std::getline (inputFile, currentLine))
		{
			std::stringstream currentLineStream (currentLine);

			float x;
			float y;
			float z;

			std::string ignoredData;


			//if (!currentLine.substr (0, 2).compare (0, 2, "vt"))
			//{
			//	currentLineStream >> ignoredData >> x >> y;
			//	tempUvCoords.push_back (glm::vec2 (x, y));
			//}
			/*else*/
			if (!currentLine.substr (0, 2).compare (0, 2, "vn"))
			{
				currentLineStream >> ignoredData >> x >> y >> z;

				tempNormCoords.push_back (glm::vec3 (x, y, z));
			}
			else if (!currentLine.substr (0, 2).compare (0, 1, "v"))
			{
				currentLineStream >> ignoredData >> x >> y >> z;

				tempVertCoords.push_back (glm::vec3 (x, y, z));
			}
			else if (!currentLine.substr (0, 6).compare (0, 6, "usemtl"))
			{
				std::string name;

				currentLineStream >> ignoredData >> name;

				iterationColours = mtl.at (name);
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
						/*					if (uvID > 0 && !isUsingMtl)
											{
												uvCoords.push_back (tempUvCoords[uvID - 1]);
											}*/
						if (normID > 0)
						{
							normCoords.push_back (tempNormCoords[normID - 1]);
						}

						colourCoords.push_back (iterationColours);
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

		numVertices = vertCoords.size ();

		if (numVertices > 0)
		{
			glBindVertexArray (VAO);

			glCreateBuffers (1, &VBO[0]);
			glNamedBufferStorage (VBO[0], sizeof (float) * numVertices * 3, &vertCoords[0], 0);
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
			glNamedBufferStorage (VBO[1], sizeof (float) * numVertices * 3, &colourCoords[0], 0);
			glBindBuffer (GL_ARRAY_BUFFER, VBO[1]);
			glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray (1);

			glCreateBuffers (1, &VBO[2]);
			glNamedBufferStorage (VBO[2], sizeof (float) * numVertices * 3, &normCoords[0], 0);
			glBindBuffer (GL_ARRAY_BUFFER, VBO[2]);
			glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray (2);

			glBindBuffer (GL_ARRAY_BUFFER, 0);
			glBindVertexArray (0);
		}
	}
	else
	{
		std::cout << "The file was not found in directory: " << path << std::endl;
	}
}