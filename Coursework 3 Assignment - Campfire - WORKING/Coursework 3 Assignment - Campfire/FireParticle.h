#pragma once

#include "GameObject.h"
#include <vector>
#include <glm/glm.hpp>
#include "point.h"

class FireParticle : public GameObject
{
public:
	FireParticle ();

	void LoadObject ();
	void UpdateParticle (float);
	void GenerateRandomValues ();
	void ChangeParticleColour (float r, float g, float b);

	bool isActive;

	bool isRed;
	bool isGreen;
	bool isBlue;

private:
	float moveSpeed;
	float lifetime;
	float curLifetime;
	float startOffset;
	std::vector<point> curve;
	int curveIndex;
	glm::vec3 colour;
};