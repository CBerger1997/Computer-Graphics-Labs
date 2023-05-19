#include "Scene.h"

#include "camera.h"
#include "error.h"

#define WIDTH 1024
#define HEIGHT 768
#define SH_MAP_WIDTH 2048
#define SH_MAP_HEIGHT 2048

SCamera Camera;

Scene::Scene ()
{

}

Scene::~Scene ()
{

}

void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose (window, true);
	}

	float offset = 0.0f;
	bool cam_changed = false;
	float changed_dist = 0.0f;

	if (key == GLFW_KEY_D && action == GLFW_REPEAT)
	{
		offset = 1.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_A && action == GLFW_REPEAT)
	{
		offset = -1.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_W && action == GLFW_REPEAT)
	{
		changed_dist += 1.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_S && action == GLFW_REPEAT)
	{
		changed_dist -= 1.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		Render::isDirectionalLight = Render::isDirectionalLight ? false : true;
		std::cout << Render::isDirectionalLight << std::endl;
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		SetCameraNextPosition (Camera);
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		Render::campfire->isRed = true;
		Render::campfire->isGreen = false;
		Render::campfire->isBlue = false;
		Render::campfire->ChangeParticleColours (1.0f, 1.0f, 0.3f);
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		Render::campfire->isRed = false;
		Render::campfire->isGreen = true;
		Render::campfire->isBlue = false;
		Render::campfire->ChangeParticleColours (0.3f, 1.0f, 1.0f);
	}

	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		Render::campfire->isRed = false;
		Render::campfire->isGreen = false;
		Render::campfire->isBlue = true;
		Render::campfire->ChangeParticleColours (1.0f, 0.3f, 1.0f);
	}

	if (cam_changed)
	{
		MoveCamera (Camera, changed_dist, offset);
	}
}

void CursorCallback (GLFWwindow* window, double xpos, double ypos)
{
	OrientCamera (Camera, xpos, ypos);
}

void SizeCallback (GLFWwindow* window, int w, int h)
{
	glViewport (0, 0, w, h);
}

//Setup and quit functions
#pragma region SETUPQUIT
void Scene::Init ()
{
	glfwInit ();

	window = glfwCreateWindow (WIDTH, HEIGHT, "Campfire Scene", NULL, NULL);
	glfwMakeContextCurrent (window);
	glfwSetKeyCallback (window, KeyCallback);
	glfwSetCursorPosCallback (window, CursorCallback);
	glfwSetWindowSizeCallback (window, SizeCallback);

	gl3wInit ();

	glEnable (GL_DEBUG_OUTPUT);
	glDebugMessageCallback (DebugCallback, 0);

	InitCamera (Camera);
	Camera.cam_dist = 5.f;
	//MoveAndOrientCamera (Camera, glm::vec3 (0, 0, 0), Camera.cam_dist, 0.f, 0.f);

	glEnable (GL_DEPTH_TEST);
}

void Scene::Deinit ()
{
	glfwDestroyWindow (window);
	glfwTerminate ();
}
#pragma endregion

void Scene::RunScene ()
{
	render.Init ();

	float pt = 0;

	while (!glfwWindowShouldClose (window))
	{
		deltaTime = 1.0f / (clock () - pt);
		pt = clock ();

		render.RenderScene (window, Camera, deltaTime);
		glfwPollEvents ();
	}
}