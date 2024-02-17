#pragma once

#include "../../Primitives/Transform.h"

#include <math.h>
#include <algorithm>

class Collider {
public:
	Collider()
		: isTrigger(0)
	{}
	virtual bool Intersect(Collider*& other) = 0;

public:
	glm::vec3* position;
	bool isTrigger;
};