#pragma once

#include "GameObject.h"

class River : public GameObject
{
public:
	void LoadObject ();
	void Draw (GLuint);

private:
	GLuint texture;
};