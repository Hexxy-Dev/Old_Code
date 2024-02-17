#pragma once

#include "Collider.h"

class AABB : public Collider {
public:
	bool Intersect(Collider*& other);

public:
	glm::vec3 min;
	glm::vec3 max;
};