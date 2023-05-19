#include "Render.h"

#include <time.h>

#include "file.h"
#include "shader.h"
#include "camera.h"

#define WIDTH 1024
#define HEIGHT 768
#define SH_MAP_WIDTH 2048
#define SH_MAP_HEIGHT 2048

Campfire* Render::campfire = new Campfire ();
Ground* Render::ground1 = new Ground ();
Ground* Render::ground2 = new Ground ();
Moon* Render::moon = new Moon ();
River* Render::river = new River ();

std::vector<Tree> Render::trees = std::vector<Tree> ();
std::vector<Rock> Render::rocks = std::vector<Rock> ();
std::vector<Grass> Render::grass = std::vector<Grass> ();
std::vector<Mushroom> Render::mushrooms = std::vector<Mushroom> ();


bool Render::isDirectionalLight = false;
ShadowStruct Render::shadow = ShadowStruct ();

void Render::Init ()
{
	//Initialise the shadow
	Render::shadow = setup_shadowmap (SH_MAP_WIDTH, SH_MAP_HEIGHT);

	standardShader = CompileShader ("phong.vert", "phong.frag");
	shadowShader = CompileShader ("shadow.vert", "shadow.frag");
	textureShader = CompileShader ("texture.vert", "texture.frag");

	CreateObjects ();
}

void Render::DrawTreeObjects (unsigned int shaderProgram)
{
	for (int i = 0; i < treeCount; i++)
	{
		Render::trees[i].Draw (shaderProgram);
	}
}

void Render::DrawRockObjects (unsigned int shaderProgram)
{
	for (int i = 0; i < rockCount; i++)
	{
		Render::rocks[i].Draw (shaderProgram);
	}
}

void Render::DrawGrassObjects (unsigned int shaderProgram)
{
	for (int i = 0; i < grassCount; i++)
	{
		Render::grass[i].Draw (shaderProgram);
	}
}

void Render::DrawMushroomObjects (unsigned int shaderProgram)
{
	for (int i = 0; i < mushroomCount; i++)
	{
		Render::mushrooms[i].Draw (shaderProgram);
	}
}

void Render::DrawObjects (unsigned int shaderProgram, float deltaTime)
{
	DrawTreeObjects (shaderProgram);

	DrawRockObjects (shaderProgram);

	DrawGrassObjects (shaderProgram);

	DrawMushroomObjects (shaderProgram);

	Render::campfire->Draw (shaderProgram, deltaTime);
}

void Render::DrawTextureObjects (unsigned int shaderProgram)
{
	Render::ground1->Draw (shaderProgram);
	Render::ground2->Draw (shaderProgram);
}

glm::vec3 Render::CalculateTreePosition ()
{
	//Ensure that position is not within the boundary of the campfire to clear the space
	while (true)
	{
		glm::vec3 randomPos = glm::vec3 ((rand () % 100) - 50, -1, (rand () % 100) - 50);

		if ((randomPos.x >= 17.0f || randomPos.x <= -17.0f) || (randomPos.z >= 17.0f || randomPos.z <= -17.0f))
		{
			if (randomPos.z <= -18.0f || randomPos.z >= -10.0f)
			{
				return randomPos;
			}
		}
		else if ((randomPos.x >= 15.0f || randomPos.x <= -15.0f) && (randomPos.z >= 15.0f || randomPos.z <= -15.0f))
		{
			if (randomPos.z <= -18.0f || randomPos.z >= -10.0f)
			{
				return randomPos;
			}
		}
	}
}

glm::vec3 Render::CalculateRiverBoundary ()
{
	//Ensure that position is not within the boundary of the campfire to clear the space
	while (true)
	{
		glm::vec3 randomPos = glm::vec3 ((rand () % 100) - 50, -1, (rand () % 100) - 50);

		if (randomPos.z <= -18.0f || randomPos.z >= -10.0f)
		{
			return randomPos;
		}
	}
}

void Render::CreateObjects ()
{
	Tree tree ("tree.mtl");
	tree.LoadObject ("tree.obj");

	for (int i = 0; i < treeCount; i++)
	{
		float size = (float)(rand () % 8 + 3) / float (10.0f);
		glm::vec3 position = CalculateTreePosition ();
		tree.SetTransformations (position, glm::vec3 (0, 1, 0), rand () % 360, glm::vec3 (size, size, size));
		tree.ApplyTransformations ();
		Render::trees.push_back (tree);
	}

	Rock rock ("Rock.mtl");
	rock.LoadObject ("Rock.obj");

	for (int i = 0; i < rockCount; i++)
	{
		rock.SetTransformations (glm::vec3 (0.0f, -1.0f, 0.0f), glm::vec3 (0.0f, 1.0f, 0.0f), 0.0f, glm::vec3 (1.5f, 1.5f, 1.5f));
		rock.ApplyTransformations ();
		rock.Rotate (glm::vec3 (0.0f, 1.0f, 0.0f), (360.0f / rockCount) * i);
		rock.Move (glm::vec3 (0.0f, 0.0f, 1.25f));
		rock.Rotate (glm::vec3 (0.0f, 1.0f, 0.0f), (rand () % 360));

		Render::rocks.push_back (rock);
	}

	Grass grass ("Grass.mtl");
	grass.LoadObject ("Grass.obj");

	for (int i = 0; i < grassCount; i++)
	{
		grass.SetTransformations (CalculateRiverBoundary (), glm::vec3 (0.0f, 1.0f, 0.0f), (rand () % 360), glm::vec3 (1.0f, 1.0f, 1.0f));
		grass.ApplyTransformations ();
		Render::grass.push_back (grass);
	}

	Mushroom mushroom ("Mushroom.mtl");
	mushroom.LoadObject ("Mushroom.obj");

	for (int i = 0; i < grassCount; i++)
	{
		mushroom.SetTransformations (CalculateRiverBoundary (), glm::vec3 (0.0f, 1.0f, 0.0f), (rand () % 360), glm::vec3 (1.0f, 1.0f, 1.0f));
		mushroom.ApplyTransformations ();
		Render::mushrooms.push_back (mushroom);
	}


	Render::campfire->CreateObject ();
	Render::ground1->LoadObject ();

	Render::ground1->Scale (glm::vec3 (150, 10, 100));
	Render::ground1->Move (glm::vec3 (0, -0.59f, 0.38f));

	Render::ground2->LoadObject ();

	Render::ground2->Scale (glm::vec3 (150, 10, 100));
	Render::ground2->Move (glm::vec3 (0, -0.59f, -0.65f));

	Render::moon->LoadObject ("Moon.obj");

	Render::moon->Move (glm::vec3 (-20.0f, 50.0f, -50.0f));
	Render::moon->Scale (glm::vec3 (20.0f, 20.0f, 20.0f));

	Render::river->LoadObject ();
	Render::river->Move (glm::vec3 (-0.5f, 0.0f, 0.0f));
	Render::river->Scale (glm::vec3 (2.0f, 1.0f, 1.0f));
}

void Render::RenderDepthMap (glm::mat4 projectedLightSpaceMatrix, float deltaTime)
{
	glViewport (0, 0, SH_MAP_WIDTH, SH_MAP_HEIGHT);

	glBindFramebuffer (GL_FRAMEBUFFER, Render::shadow.FBO);
	glClear (GL_DEPTH_BUFFER_BIT);
	glUseProgram (shadowShader);
	glUniformMatrix4fv (glGetUniformLocation (shadowShader, "projectedLightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr (projectedLightSpaceMatrix));

	DrawObjects (shadowShader, deltaTime);

	DrawTextureObjects (shadowShader);

	glBindFramebuffer (GL_FRAMEBUFFER, 0);
}

void Render::RenderObjects (glm::mat4 projectedLightSpaceMatrix, SCamera camera, float deltaTime)
{
	glViewport (0, 0, WIDTH, HEIGHT);

	static const GLfloat bgd[] = { 0.0f, 0.0f, 0.0f, 1.f };
	glClearBufferfv (GL_COLOR, 0, bgd);
	glClear (GL_DEPTH_BUFFER_BIT);
	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);

	glUseProgram (standardShader);

	//glBindTexture (GL_TEXTURE_2D, Render::shadow.Texture);

	//Set uniforms
	glUniformMatrix4fv (glGetUniformLocation (standardShader, "projectedLightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr (projectedLightSpaceMatrix));
	glUniform3f (glGetUniformLocation (standardShader, "lightDirection"), lightDirection.x, lightDirection.y, lightDirection.z);
	glUniform3f (glGetUniformLocation (standardShader, "lightColour"), Render::campfire->particleColours.x, Render::campfire->particleColours.y, Render::campfire->particleColours.z);
	glUniform3f (glGetUniformLocation (standardShader, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f (glGetUniformLocation (standardShader, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	glUniform1i (glGetUniformLocation (standardShader, "isDirectionalLight"), Render::isDirectionalLight);

	if (!Render::isDirectionalLight)
	{
		//Randomise ambient for a flickering effect on the fire
		glUniform1f (glGetUniformLocation (standardShader, "ambient"), (float)((rand () % 3) + 1) / (float)(10.0f));
	}

	glm::mat4 view = glm::mat4 (1.f);
	view = glm::lookAt (camera.Position, camera.Position + camera.Front, camera.Up);
	glUniformMatrix4fv (glGetUniformLocation (standardShader, "view"), 1, GL_FALSE, glm::value_ptr (view));

	glm::mat4 projection = glm::mat4 (1.f);
	projection = glm::perspective (glm::radians (45.f), (float)WIDTH / (float)HEIGHT, .01f, 100.f);
	glUniformMatrix4fv (glGetUniformLocation (standardShader, "projection"), 1, GL_FALSE, glm::value_ptr (projection));

	DrawObjects (standardShader, deltaTime);

	DrawTextureObjects (standardShader);

	glUseProgram (textureShader);
	glUniformMatrix4fv (glGetUniformLocation (textureShader, "view"), 1, GL_FALSE, glm::value_ptr (view));
	glUniformMatrix4fv (glGetUniformLocation (textureShader, "projection"), 1, GL_FALSE, glm::value_ptr (projection));

	Render::moon->Draw (textureShader);
	Render::river->Draw (textureShader);
}

void Render::RenderScene (GLFWwindow* window, SCamera camera, float deltaTime)
{
	float near_plane = 0.1f, far_plane = 70.5f;

	glm::mat4 projectedLightSpaceMatrix;

	if (Render::isDirectionalLight)
	{
		lightPos = glm::vec3 (2.0f, 6.0f, 7.0f);
		glm::mat4 lightProjection = glm::ortho (-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		glm::mat4 lightView = glm::lookAt (lightPos, lightPos + lightDirection, glm::vec3 (0.0f, 1.0f, 0.0f));
		projectedLightSpaceMatrix = lightProjection * lightView;
	}
	else
	{
		lightPos = glm::vec3 (0.0f, 2.0f, 0.0f);
		glm::mat4 lightProjection = glm::perspective (glm::radians (90.0f), (float)WIDTH / (float)HEIGHT, near_plane, far_plane);
		glm::mat4 lightView = glm::lookAt (lightPos, lightPos + lightDirection, glm::vec3 (0.0f, 1.0f, 0.0f));
		projectedLightSpaceMatrix = lightProjection * lightView;
	}

	RenderDepthMap (projectedLightSpaceMatrix, deltaTime);

	saveShadowMapToBitmap (Render::shadow.Texture, SH_MAP_WIDTH, SH_MAP_HEIGHT);

	RenderObjects (projectedLightSpaceMatrix, camera, deltaTime);

	glfwSwapBuffers (window);
}