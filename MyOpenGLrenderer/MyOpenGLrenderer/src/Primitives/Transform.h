#pragma once

#include "glm.hpp"

struct Transform {
	Transform()
		: Scale(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), Position(0.0f, 0.0f, 0.0f)
	{}

	glm::vec3 Position;
	union
	{
		glm::vec3 Rotation; // IN EULER ANGLES!!!!
		glm::vec3 Front;
	};
	union
	{
		glm::vec3 Scale;
		glm::vec3 Up;
	};
};