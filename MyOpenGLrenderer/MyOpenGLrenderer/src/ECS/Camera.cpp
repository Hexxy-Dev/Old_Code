#include "Camera.h"

#include "../Profiler.h"

Camera::Camera()
	: FOV(45)
{
	Transform.Front = glm::vec3(0.0f, 0.0f, -1.0f);
	Transform.Up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::mat4 Camera::createViewMatrix() const
{
	PROFILE_FUNCTION();
	glm::mat4 view = glm::lookAt(
		Transform.Position,
		Transform.Position + Transform.Front,
		Transform.Up
	);

	return view;
}

glm::mat4 Camera::createPerspective() const
{
	PROFILE_FUNCTION();
	return glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 10.0f);
}