#pragma once

#include "../Primitives/Transform.h"

struct RigidBody {
	RigidBody()
		: velocity(0.0f), force(0.0f), mass(0.0f)
	{}

	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
};