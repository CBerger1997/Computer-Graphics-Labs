#pragma once

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>
#define _USE_MATH_DEFINES 
#include <math.h>
#define DEG2RAD(n)	n*(M_PI/180)

struct SCamera
{
	enum Camera_Movement
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;

	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	const float MovementSpeed = 0.5f;
	float MouseSensitivity = 1.0f;

	float cam_dist = 2.0f;

	bool isFreeCameraEnabled;

	bool isInitialCameraMovement = true;
	float startMousex;
	float startMousey;

	std::vector<glm::vec3> setCameraPositions;
	unsigned int curCamPosIndex;
};

inline void OrientCamera (SCamera& in, float xoffset, float yoffset)
{
	if (in.isInitialCameraMovement)
	{
		in.startMousex = xoffset;
		in.startMousey = yoffset;
		in.isInitialCameraMovement = false;
	}

	float newXoffset = (xoffset - in.startMousex) * in.MouseSensitivity;
	float newYoffset = (in.startMousey - yoffset) * in.MouseSensitivity;

	in.startMousex = xoffset;
	in.startMousey = yoffset;

	in.Yaw += newXoffset * in.MovementSpeed;
	in.Pitch += newYoffset * in.MovementSpeed;

	if (in.Pitch > 89.0f) in.Pitch = 89.0f;
	if (in.Pitch < -89.0f) in.Pitch = -89.0f;

	in.Front.x = cos (DEG2RAD (in.Yaw)) * cos (DEG2RAD (in.Pitch));
	in.Front.y = sin (DEG2RAD (in.Pitch));
	in.Front.z = sin (DEG2RAD (in.Yaw)) * cos (DEG2RAD (in.Pitch));

	in.Front = glm::normalize (in.Front);

	in.Right = glm::normalize (glm::cross (in.Front, in.WorldUp));

	in.Up = glm::normalize (glm::cross (in.Right, in.Front));
}

inline void MoveCamera (SCamera& in, float distance, float offset)
{
	in.Position += in.Front * distance * in.MovementSpeed;
	in.Position += glm::normalize (glm::cross (in.Front, in.WorldUp)) * offset * in.MovementSpeed;
}

inline void InitCamera (SCamera& in)
{
	in.Front = glm::vec3 (0.0f, 0.0f, -1.0f);
	in.Position = glm::vec3 (0.0f, 4.0f, 10.0f);
	in.Up = glm::vec3 (0.0f, 1.0f, 0.0f);
	in.WorldUp = in.Up;
	in.Right = glm::normalize (glm::cross (in.Front, in.WorldUp));

	in.Yaw = -90.f;
	in.Pitch = 0.f;

	in.setCameraPositions.push_back (glm::vec3 (0.0f, 4.0f, 10.0f));
	in.setCameraPositions.push_back (glm::vec3 (9.0f, 4.0f, 5.0f));
	in.setCameraPositions.push_back (glm::vec3 (9.0f, 4.0f, -5.0f));
	in.setCameraPositions.push_back (glm::vec3 (0.0f, 4.0f, -10.0f));
	in.setCameraPositions.push_back (glm::vec3 (-9.0f, 4.0f, -5.0f));
	in.setCameraPositions.push_back (glm::vec3 (-9.0f, 4.0f, 5.0f));

	in.curCamPosIndex = 1;
}



inline void SetCameraNextPosition (SCamera& in)
{
	in.Position = in.setCameraPositions[in.curCamPosIndex];
	in.curCamPosIndex++;

	if (in.curCamPosIndex >= in.setCameraPositions.size ())
	{
		in.curCamPosIndex = 0;
	}
}