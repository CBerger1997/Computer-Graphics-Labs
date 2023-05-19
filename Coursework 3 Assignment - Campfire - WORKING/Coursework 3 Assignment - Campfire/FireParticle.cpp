#include "FireParticle.h"
#include "casteljau.h"
#include <time.h>

FireParticle::FireParticle ()
{
	lifetime = (float)((rand () % 15) + 10) / float (10.0f);
	startOffset = (float)((rand () % 40)) / float (10.0f);
	curLifetime = 0.0f;
	isActive = false;
	curveIndex = 0;
	moveSpeed = 0.5f;
	colour = glm::vec3 (1.0f, 0.3f, 0.3f);
	isRed = true;
	isGreen = false;
	isBlue = false;
}

void FireParticle::LoadObject ()
{
	float vertices[] =
	{
		//back face
	   -0.5f, 0.5f, 0.0f,
	   -0.5f,-0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f,-0.5f, 0.0f,
	   -0.5f,-0.5f, 0.0f,

	   //front face
	  -0.5f, 0.5f, 0.1f,
	  -0.5f,-0.5f, 0.1f,
	   0.5f, 0.5f, 0.1f,
	   0.5f, 0.5f, 0.1f,
	   0.5f,-0.5f, 0.1f,
	  -0.5f,-0.5f, 0.1f,

	  //left face
	 -0.5f, 0.5f, 0.0f,
	 -0.5f, 0.5f, 0.1f,
	 -0.5f,-0.5f, 0.0f,
	 -0.5f, 0.5f, 0.1f,
	 -0.5f,-0.5f, 0.1f,
	 -0.5f,-0.5f, 0.0f,

	 //right face
	 0.5f, 0.5f, 0.0f,
	 0.5f, 0.5f, 0.1f,
	 0.5f,-0.5f, 0.0f,
	 0.5f, 0.5f, 0.1f,
	 0.5f,-0.5f, 0.1f,
	 0.5f,-0.5f, 0.0f,

	 //bottom face
	 0.5f,-0.5f, 0.0f,
	 0.5f,-0.5f, 0.1f,
	-0.5f,-0.5f, 0.0f,
	 0.5f,-0.5f, 0.1f,
	-0.5f,-0.5f, 0.1f,
	-0.5f,-0.5f, 0.0f,

	//top face
	0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.1f,
   -0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.1f,
   -0.5f, 0.5f, 0.1f,
   -0.5f, 0.5f, 0.0f,
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

	//back face
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));

	//front face
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));

	//left face
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));

	//right face
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));

	//bottom face
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));

	//top face
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));
	colours.push_back (glm::vec3 (1.0f, 1.0f, 0.3f));

	numVertices = 36;

	glGenVertexArrays (1, &VAO);
	glBindVertexArray (VAO);

	glCreateBuffers (1, &VBO[0]);
	glNamedBufferStorage (VBO[0], sizeof (float) * numVertices * 3, &vertices[0], 0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO[0]);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (0);

	glCreateBuffers (1, &VBO[1]);
	glNamedBufferStorage (VBO[1], sizeof (float) * numVertices * 3, &colours[0], 0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO[1]);
	glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (1);

	glCreateBuffers (1, &VBO[2]);
	glNamedBufferStorage (VBO[2], sizeof (float) * numVertices * 3, &normals[0], 0);
	glBindBuffer (GL_ARRAY_BUFFER, VBO[2]);
	glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (2);

	glBindBuffer (GL_ARRAY_BUFFER, 0);
	glBindVertexArray (0);

	GenerateRandomValues ();

	//free (vertices);
	//free (normals);
}

void FireParticle::GenerateRandomValues ()
{
	//Set random positions for spawning
	SetTransformations (glm::vec3 (
		(float)((rand () % 20) - 10) / float (10.0f),
		(float)((rand () % 10)) / float (10.0f),
		(float)((rand () % 20) - 10) / float (10.0f)),
		glm::vec3 (0.0f, 1.0f, 0.0f),
		0.0f,
		glm::vec3 (0.2f, 0.2f, 0.1f));
	ApplyTransformations ();

	//Create 3 randomised ctrl points that adds on to the previous ctrl point
	std::vector<point> ctrl_points;
	ctrl_points.push_back (point (
		(float)((rand () % 3) - 1) / float (100.0f),
		(float)((rand () % 5) + 2) / float (10.0f),
		(float)((rand () % 3) - 1) / float (100.0f)));

	for (int i = 0; i < 6; i++)
	{
		ctrl_points.push_back (point (
			ctrl_points[i].x + (float)((rand () % 30) - 10) / float (100.0f),
			ctrl_points[i].y + (float)((rand () % 3)) / float (10.0f),
			ctrl_points[i].z + (float)((rand () % 30) - 10) / float (100.0f)));
	}

	int num_evaluations = 128;
	curve = EvaluateBezierCurve (ctrl_points, num_evaluations);
}

void FireParticle::ChangeParticleColour (float r, float g, float b)
{
	for (int i = 0; i < 36; i++)
	{
		colours[i].r = r;
		colours[i].g = g;
		colours[i].b = b;
	}
}

void FireParticle::UpdateParticle (float deltaTime)
{
	if (!isActive)
	{
		startOffset -= deltaTime;
		if (startOffset <= 0)
		{
			isActive = true;
		}
		else
		{
			return;
		}
	}
	if (curveIndex < curve.size ())
	{
		Rotate (glm::vec3 (0.0f, 1.0f, 0.0f), 10.0f);
		Move (glm::vec3 (curve[curveIndex].x, curve[curveIndex].y, curve[curveIndex].z) * moveSpeed);

		if (isRed)
		{
			if (colour.g > 0.0f)
			{
				ChangeParticleColour (colour.r, colour.g, colour.b);
				colour.g -= deltaTime * 0.75f;
			}
		}
		else if (isGreen)
		{
			if (colour.b > 0.0f)
			{
				ChangeParticleColour (colour.r, colour.g, colour.b);
				colour.b -= deltaTime * 0.75f;
			}
		}
		else if (isBlue)
		{
			if (colour.r > 0.0f)
			{
				ChangeParticleColour (colour.r, colour.g, colour.b);
				colour.r -= deltaTime * 0.75f;
			}
		}

		curveIndex++;

		curLifetime += deltaTime;
	}

	if (curLifetime >= lifetime || curveIndex >= curve.size ())
	{
		SetTransformations (glm::vec3 (
			(float)((rand () % 20) - 10) / float (10.0f),
			(float)((rand () % 10)) / float (10.0f),
			(float)((rand () % 20) - 10) / float (10.0f)),
			glm::vec3 (0.0f, 1.0f, 0.0f), 0.0f, glm::vec3 (0.2f, 0.2f, 0.1f));

		ApplyTransformations ();

		curLifetime = 0;
		curveIndex = 0;

		if (isRed)
		{
			colour.r = 1.0f;
			colour.g = 1.0f;
			ChangeParticleColour (colour.r, colour.g, colour.b);
		}
		else if (isGreen)
		{
			colour.g = 1.0f;
			colour.b = 1.0f;
			ChangeParticleColour (colour.r, colour.g, colour.b);
		}
		else if (isBlue)
		{
			colour.b = 1.0f;
			colour.r = 1.0f;
			ChangeParticleColour (colour.r, colour.g, colour.b);
		}
	}


}