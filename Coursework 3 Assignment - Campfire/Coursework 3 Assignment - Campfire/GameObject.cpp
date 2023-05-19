#include "GameObject.h"

GameObject::GameObject ()
{
	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);
	numVertices = 0;
}

GameObject::~GameObject ()
{
	//glDeleteVertexArrays (1, &VAO);
	//glDeleteBuffers (3, VBO);
}

void GameObject::SetTransformations (glm::vec3 pos, glm::vec3 rot, float deg, glm::vec3 sc)
{
	position = pos;
	rotation = rot;
	scale = sc;
	rotationDegrees = deg;
}

void GameObject::ApplyTransformations ()
{
	model = glm::translate (model, position);
	model = glm::rotate (model, (float)glm::radians (rotationDegrees), rotation);
	model = glm::scale (model, scale);
}

void GameObject::Move (glm::vec3 posVals)
{
	position += posVals;

	model = glm::translate (model, position);
}

void GameObject::Rotate (glm::vec3 rotVals, float degrees)
{
	rotation = rotVals;
	rotationDegrees = degrees;

	model = glm::rotate (model, (float)glm::radians (rotationDegrees), rotation);
}

void GameObject::Scale (glm::vec3 scVals)
{
	scale += scVals;

	model = glm::scale (model, scale);
}

void GameObject::Draw (GLuint shader)
{
	glUniformMatrix4fv (glGetUniformLocation (shader, "model"), 1, GL_FALSE, glm::value_ptr (model));

	glBindVertexArray (VAO);
	glDrawArrays (GL_TRIANGLES, 0, numVertices);
	glBindVertexArray (0);
}