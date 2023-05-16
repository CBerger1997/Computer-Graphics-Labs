#include "OpenGL.h"

void KeyCallback (GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose (window, true);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		lightDirection = Camera.Front;
	}

	float x_offset = 0.0f;
	float y_offset = 0.0f;
	bool cam_changed = false;

	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {
		x_offset = 1.0f;
		y_offset = 0.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT) {
		x_offset = -1.0f;
		y_offset = 0.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
		x_offset = 0.0f;
		y_offset = -1.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
		x_offset = 0.0f;
		y_offset = 1.0f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_R && action == GLFW_REPEAT) {
		cam_dist -= 0.5f;
		cam_changed = true;
	}

	if (key == GLFW_KEY_F && action == GLFW_REPEAT) {
		cam_dist += 0.5f;
		cam_changed = true;
	}

	if (cam_changed) {
		MoveAndOrientCamera (camera, glm::vec3 (0.0f, 0.0f, 0.0f), cam_dist, x_offset, y_offset);
	}
}

void SizeCallback (GLFWwindow* window, int w, int h) {
	glViewport (0, 0, w, h);
}

void OpenGl::Init () {
	glfwInit ();

	window = glfwCreateWindow (WIDTH, HEIGHT, "Campfire Scene", NULL, NULL);
	glfwMakeContextCurrent (window);
	glfwSetKeyCallback (window, KeyCallback);
	glfwSetWindowSizeCallback (window, SizeCallback);

	gl3wInit ();

	glEnable (GL_DEBUG_OUTPUT);
	glDebugMessageCallback (DebugCallback, 0);

	shadow = setup_shadowmap (SH_MAP_WIDTH, SH_MAP_HEIGHT);

	standardShader = CompileShader ("phong.vert", "phong.frag");
	shadowShader = CompileShader ("shadow.vert", "shadow.frag");

	InitCamera (camera);
	cam_dist = 5.f;
	MoveAndOrientCamera (camera, glm::vec3 (0, 0, 0), cam_dist, 0.f, 0.f);


	//TODO: 
	//MOVE THIS TO A CAMPFIRE OBJECT
	


	//glCreateBuffers (NUM_BUFFERS, Buffers);
	//glNamedBufferStorage (Buffers[0], sizeof (vertices), vertices, 0);
	//glGenVertexArrays (NUM_VAOS, VAOs);

	//glBindVertexArray (VAOs[0]);
	//glBindBuffer (GL_ARRAY_BUFFER, Buffers[0]);
	//glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, (9 * sizeof (float)), (void*)0);
	//glEnableVertexAttribArray (0);
	//glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, (9 * sizeof (float)), (void*)(3 * sizeof (float)));
	//glEnableVertexAttribArray (1);
	//glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, (9 * sizeof (float)), (void*)(6 * sizeof (float)));
	//glEnableVertexAttribArray (2);
	//glBindVertexArray (0);

	glEnable (GL_DEPTH_TEST);
}

void OpenGl::Deinit () {
	glfwDestroyWindow (window);
	glfwTerminate ();
}