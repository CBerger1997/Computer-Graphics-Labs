#include "Campfire.h"
#include <glm/glm.hpp>

Campfire::Campfire ()
{
	particleCount = 500;
	particleColours = glm::vec3 (1.0f, 1.0f, 0.3f);
}

void Campfire::CreateObject ()
{
	//Create Logs for the bonfire
	for (int i = 0; i < 6; i++)
	{
		Log log;

		log.LoadObject ();

		log.SetTransformations (position, glm::vec3 (0.0f, 1.0f, 0.0f), 0.0f, glm::vec3 (1.0f, 1.0f, 1.0f));

		log.Rotate (glm::vec3 (0.0f, 1.0f, 0.0f), 60.0f * i);
		log.Move (glm::vec3 (0.0f, 0.0f, 1.0f));
		log.Rotate (glm::vec3 (1.0f, 0.0f, 0.0f), 45.0f);

		logs.push_back (log);
	}

	//Create benches that surround the campfire
	for (int i = 0; i < 6; i++)
	{
		Log bench;

		bench.LoadObject ();

		bench.SetTransformations (position, glm::vec3 (0.0f, 1.0f, 0.0f), 0.0f, glm::vec3 (1.0f, 1.0f, 1.0f));

		bench.Rotate (glm::vec3 (0.0f, 1.0f, 0.0f), 60.0f * i);
		bench.Move (glm::vec3 (0.0f, 0.0f, 10.0f));
		bench.Rotate (glm::vec3 (0.0f, 1.0f, 0.0f), 90.0f);
		bench.Scale (glm::vec3 (3.0f, 3.0f, 3.0f));

		benches.push_back (bench);
	}

	GenerateParticles ();
}

void Campfire::GenerateParticles ()
{
	particleColours = glm::vec3 (1.0f, 1.0f, 0.3f);

	//Create particles for the flame effect of the campfire
	for (int i = 0; i < particleCount; i++)
	{
		FireParticle fireParticle;
		fireParticle.LoadObject ();
		particles.push_back (fireParticle);
	}
}

void Campfire::ChangeParticleColours (float r, float g, float b)
{
	particleColours = glm::vec3 (r, g, b);

	for (int i = 0; i < particleCount; i++)
	{
		particles[i].isRed = isRed;
		particles[i].isGreen = isGreen;
		particles[i].isBlue = isBlue;
		particles[i].ChangeParticleColour (r, g, b);
	}
}

void Campfire::Draw (GLuint shader, float deltaTime)
{
	for (int i = 0; i < 6; i++)
	{
		logs[i].Draw (shader);
	}

	for (int i = 0; i < 6; i++)
	{
		benches[i].Draw (shader);
	}

	for (int i = 0; i < particleCount; i++)
	{
		particles[i].UpdateParticle (deltaTime);

		if (particles[i].isActive)
		{
			particles[i].Draw (shader);
		}
	}
}