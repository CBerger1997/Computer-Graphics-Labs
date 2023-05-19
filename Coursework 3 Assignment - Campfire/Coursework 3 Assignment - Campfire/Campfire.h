#pragma once

#include "GameObject.h"
#include <vector>

class Campfire : GameObject
{
public:
	//Campfire ();
	//~Campfire ();

	void LoadObject ();
	void LoadMTL ();

private:
	//VAO and VBO Parameters
	GLuint VAO;
	GLuint VBO[3];
};