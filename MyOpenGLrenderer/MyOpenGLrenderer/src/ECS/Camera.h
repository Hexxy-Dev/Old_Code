#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "../Primitives/Transform.h"

class Camera {
public:

	Camera();

	glm::mat4 createViewMatrix() const;

	glm::mat4 createPerspective() const;

	Transform Transform;
	float FOV;

	short width;
	short height;
};