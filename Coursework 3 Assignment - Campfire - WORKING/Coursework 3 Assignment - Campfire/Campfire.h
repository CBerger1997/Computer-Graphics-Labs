#pragma once

#include "Log.h"
#include "FireParticle.h"
#include <vector>

class Campfire : public GameObject
{
public:
	Campfire ();

	void CreateObject ();
	void Draw (GLuint, float);
	void GenerateParticles ();
	void ChangeParticleColours (float, float, float);

	glm::vec3 particleColours;

	bool isRed;
	bool isGreen;
	bool isBlue;

private:
	std::vector<Log> logs;
	std::vector<Log> benches;

	std::vector<FireParticle> particles;
	unsigned int particleCount;
};